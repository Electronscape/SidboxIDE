#!/usr/bin/env bash
# Stage 6D close-from-private-stack test. Uses *test-local* stack-metadata packer, not installed IDE tools.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IDE="$(cd "$HERE/../.." && pwd)"
OUT="$HERE/host-build"
mkdir -p "$OUT"
fail(){ printf 'ERROR: %s\n' "$*" >&2; exit 1; }
for exe in clang ld.lld g++ cc; do command -v "$exe" >/dev/null || fail "Missing $exe"; done
if [[ -n "${SIDBOX_IDELIBS:-}" ]]; then SDK="$SIDBOX_IDELIBS"
elif [[ -f "$IDE/idelibs/gui_v2.ld" ]]; then SDK="$IDE/idelibs"
else SDK="$HERE/bundled"; fi
if [[ -f "$SDK/api/apis.h" ]]; then API="$SDK/api"; else API="$HERE/bundled/sdk_api"; fi
if [[ -f "$SDK/api/syscalls.c" ]]; then SYSCALLS="$SDK/api/syscalls.c"; else SYSCALLS="$HERE/bundled/syscalls.c"; fi
[[ -f "$SDK/gui_v2.ld" ]] || fail "Can't find gui_v2.ld at $SDK"
[[ -f "$API/apis.h" ]] || fail "Can't find SDK at $API"
[[ -f "$SYSCALLS" ]] || fail "Can't find syscalls at $SYSCALLS"
grep -q 'SIDBOX_APPLET_V2' "$SYSCALLS" || fail 'SDK syscalls.c lacks V2 support'
# The test deliberately uses its own packer with --stack metadata. It does not
# replace the user's installed production packer or their IDE project.
g++ -std=c++17 -O2 -Wall -Wextra -Werror -pedantic \
    "$HERE/bundled/v2_packer_stage6c.cpp" -o "$OUT/sidbox-v2-packer-stage6c"
cp "$SDK/gui_v2.ld" "$OUT/psp_stage6d.ld"
sed -i -E 's/^_v2_stack_bytes[[:space:]]*=.*$/_v2_stack_bytes = 0x2000;/' "$OUT/psp_stage6d.ld"
sed 's/section(".text.applet_entry")/section(".text.unused_sdk_entry_for_test")/' \
    "$SYSCALLS" > "$OUT/syscalls_test_compile.c"
COMMON=(--target=armv7em-none-eabihf -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 \
    -mfloat-abi=hard -std=gnu11 -Oz -Wall -Wextra -Werror -ffreestanding \
    -fno-builtin -fPIC -fPIE -fvisibility=hidden -fdata-sections \
    -ffunction-sections -DSIDBOX_APPLET_V2 -DSIDBOX_V2_HEAP_BYTES=4096 \
    -I"$HERE/include" -I"$API")
clang "${COMMON[@]}" -Wno-unused-parameter -Wno-unused-function \
    -DSIDBOX_STARTUP_HEADER_IN_ASM -Dapplet_entry=sdk_entry_not_used \
    -c "$OUT/syscalls_test_compile.c" -o "$OUT/syscalls.o"
clang "${COMMON[@]}" -c "$HERE/arm_eabi_mem.c" -o "$OUT/arm_eabi_mem.o"
for variant in A B; do
    lower="$(printf %s "$variant" | tr '[:upper:]' '[:lower:]')"
    base="$OUT/v2-self-close-$lower"
    clang "${COMMON[@]}" -DS6D_APP_"$variant" \
        -c "$HERE/close_self_test.c" -o "$base.o"
    ld.lld -pie -Bsymbolic --no-undefined -nostdlib --gc-sections \
        --entry=applet_entry -T "$OUT/psp_stage6d.ld" \
        "$base.o" "$OUT/arm_eabi_mem.o" "$OUT/syscalls.o" -o "$base.elf"
    "$OUT/sidbox-v2-packer-stage6c" "$base.elf" "$base.app.tmp" \
        --heap 4096 --stack 8192
    mv "$base.app.tmp" "$base.app"
done
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic -I"$HERE" \
    "$HERE/check_headers.c" -o "$OUT/check_headers"
"$OUT/check_headers" "$OUT/v2-self-close-a.app" "$OUT/v2-self-close-b.app"
printf '\nHOST BUILD PASS (NOT HARDWARE VERIFIED)\nUse with your working Stage 6C PSP-enabled firmware:\n  %s/v2-self-close-a.app\n  %s/v2-self-close-b.app\n' "$OUT" "$OUT"
