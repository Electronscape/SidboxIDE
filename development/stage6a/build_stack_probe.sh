#!/usr/bin/env bash
# Stage 6A: verify actual execution stack registers on hardware.
# No firmware modifications, no application stack switching.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IDE="$(cd "$HERE/../.." && pwd)"
OUT="$HERE/host-build"
mkdir -p "$OUT"
fail() { printf 'ERROR: %s\n' "$*" >&2; exit 1; }
for cmd in clang ld.lld g++ cc sed od; do
    command -v "$cmd" >/dev/null || fail "Missing $cmd"
done
if [[ -n "${SIDBOX_IDELIBS:-}" ]]; then SDK="$SIDBOX_IDELIBS"
elif [[ -f "$IDE/idelibs/gui_v2.ld" ]]; then SDK="$IDE/idelibs"
else SDK="$HERE/bundled"; fi
if [[ -f "$SDK/api/apis.h" ]]; then API="$SDK/api"
else API="$HERE/bundled/sdk_api"; fi
if [[ -n "${SIDBOX_SYSCALLS_SOURCE:-}" ]]; then SYS_SOURCE="$SIDBOX_SYSCALLS_SOURCE"
elif [[ -f "$SDK/api/syscalls.c" ]]; then SYS_SOURCE="$SDK/api/syscalls.c"
else SYS_SOURCE="$HERE/bundled/syscalls.c"; fi
if [[ -f "$IDE/v2_packer.cpp" ]]; then PACKER_SOURCE="$IDE/v2_packer.cpp"
else PACKER_SOURCE="$HERE/bundled/v2_packer.cpp"; fi
[[ -f "$SDK/gui_v2.ld" ]] || fail "Missing GUI V2 linker script: $SDK/gui_v2.ld"
[[ -f "$API/apis.h" ]] || fail "Missing applet SDK headers: $API"
[[ -f "$SYS_SOURCE" ]] || fail "Missing syscalls.c: $SYS_SOURCE"
grep -q 'SIDBOX_APPLET_V2' "$SYS_SOURCE" || fail "Selected syscalls.c lacks V2 support"
grep -q 'section(".text.applet_entry")' "$SYS_SOURCE" || fail "Cannot locate SDK entry annotation"
# Require 8 KiB reserved stack for the canary probe. Never reconfigure
# someone's project linker silently; make a dedicated local test copy.
cp "$SDK/gui_v2.ld" "$OUT/stack_probe.ld"
sed -i -E 's/^_v2_stack_bytes[[:space:]]*=.*$/_v2_stack_bytes = 0x2000;/' "$OUT/stack_probe.ld"
printf 'Stage 6A: Stack mapping (no stack switching)\n  SDK: %s\n' "$SDK"
sed 's/section(".text.applet_entry")/section(".text.unused_sdk_entry_for_test")/' \
    "$SYS_SOURCE" > "$OUT/syscalls_test_compile.c"
COMMON=(--target=armv7em-none-eabihf -mcpu=cortex-m7 -mthumb \
    -mfpu=fpv5-d16 -mfloat-abi=hard -std=gnu11 -Oz -Wall -Wextra \
    -Werror -ffreestanding -fno-builtin -fPIC -fPIE -fvisibility=hidden \
    -fdata-sections -ffunction-sections -DSIDBOX_APPLET_V2 \
    -DSIDBOX_V2_HEAP_BYTES=4096 -I"$HERE/include" -I"$API")
clang "${COMMON[@]}" -Wno-unused-parameter -Wno-unused-function \
    -DSIDBOX_STARTUP_HEADER_IN_ASM -Dapplet_entry=sdk_entry_not_used \
    -c "$OUT/syscalls_test_compile.c" -o "$OUT/syscalls.o"
clang "${COMMON[@]}" -c "$HERE/arm_eabi_mem.c" -o "$OUT/arm_eabi_mem.o"
g++ -std=c++17 -O2 -Wall -Wextra -Werror -pedantic \
    "$PACKER_SOURCE" -o "$OUT/sidbox-v2-packer"
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic -I"$HERE" \
    "$HERE/v2_format_test.c" -o "$OUT/v2_format_test"
for variant in A B; do
    lower="$(printf %s "$variant" | tr '[:upper:]' '[:lower:]')"
    base="$OUT/v2-stack-$lower"
    clang "${COMMON[@]}" -DS6_APP_"$variant" \
        -c "$HERE/stack_probe.c" -o "$base.o"
    ld.lld -pie -Bsymbolic --no-undefined -nostdlib --gc-sections \
        --entry=applet_entry -T "$OUT/stack_probe.ld" \
        "$base.o" "$OUT/arm_eabi_mem.o" "$OUT/syscalls.o" -o "$base.elf"
    "$OUT/sidbox-v2-packer" "$base.elf" "$base.app.tmp" --heap 4096
    "$OUT/v2_format_test" "$base.app.tmp"
    mv "$base.app.tmp" "$base.app"
    printf 'PASS: Applet %s built and validated\n' "$variant"
done
cmp -s "$OUT/v2-stack-a.app" "$OUT/v2-stack-b.app" && fail "A and B binaries should differ"
printf '\nHOST PASS. Hardware stack behaviour still untested.\nCopy to SD card:\n %s\n %s\n' \
    "$OUT/v2-stack-a.app" "$OUT/v2-stack-b.app"
