#!/usr/bin/env bash
# Applet-local PIC malloc/calloc/realloc/free over the REAL SDK V2 _sbrk().
# Experimental host build; never writes firmware or existing applets.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IDE="$(cd "$HERE/../.." && pwd)"
OUT="$HERE/host-build"
mkdir -p "$OUT"
rm -f "$OUT/v2-pic-malloc-a.app" "$OUT/v2-pic-malloc-b.app"
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
[[ -f "$SDK/gui_v2.ld" ]] || fail "Missing V2 linker script in $SDK"
[[ -f "$API/apis.h" ]] || fail "Missing SDK apis.h"
[[ -f "$SYS_SOURCE" ]] || fail "Missing syscalls.c"
grep -q 'SIDBOX_APPLET_V2' "$SYS_SOURCE" || fail "Selected _sbrk is not V2-aware"
grep -q 'section(".text.applet_entry")' "$SYS_SOURCE" || fail "SDK applet entry marker changed"
printf 'SIDBOX V2 Stage 5C — applet-local PIC malloc test\n  SDK=%s\n  syscalls=%s\n' "$SDK" "$SYS_SOURCE"
sed 's/section(".text.applet_entry")/section(".text.unused_sdk_entry_for_test")/' \
    "$SYS_SOURCE" > "$OUT/syscalls_test_compile.c"
COMMON=(--target=armv7em-none-eabihf -mcpu=cortex-m7 -mthumb
    -mfpu=fpv5-d16 -mfloat-abi=hard -std=gnu11 -Oz -Wall -Wextra
    -Werror -ffreestanding -fno-builtin -fPIC -fPIE -fvisibility=hidden
    -fdata-sections -ffunction-sections -DSIDBOX_APPLET_V2
    -DSIDBOX_V2_HEAP_BYTES=16384 -I"$HERE/include" -I"$API")
clang "${COMMON[@]}" -Wno-unused-parameter -Wno-unused-function \
    -DSIDBOX_STARTUP_HEADER_IN_ASM -Dapplet_entry=sdk_entry_not_used \
    -c "$OUT/syscalls_test_compile.c" -o "$OUT/syscalls.o"
clang "${COMMON[@]}" -c "$HERE/v2_pic_malloc.c" -o "$OUT/v2_pic_malloc.o"
clang "${COMMON[@]}" -c "$HERE/arm_eabi_mem.c" -o "$OUT/arm_eabi_mem.o"
g++ -std=c++17 -O2 -Wall -Wextra -Werror -pedantic \
    "$PACKER_SOURCE" -o "$OUT/sidbox-v2-packer"
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic -I"$HERE" \
    "$HERE/v2_format_test.c" -o "$OUT/v2_format_test"
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic \
    -Dmalloc=sb_malloc -Dfree=sb_free -Dcalloc=sb_calloc -Drealloc=sb_realloc \
    -c "$HERE/v2_pic_malloc.c" -o "$OUT/host_pic_malloc.o"
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic \
    "$HERE/host_allocator_test.c" "$OUT/host_pic_malloc.o" -o "$OUT/host_allocator_test"
"$OUT/host_allocator_test"
for variant in A B; do
    lower="$(printf %s "$variant" | tr '[:upper:]' '[:lower:]')"
    base="$OUT/v2-pic-malloc-$lower"
    clang "${COMMON[@]}" -DSTAGE5B_APP_"$variant" \
        -c "$HERE/malloc_test.c" -o "$base.o"
    ld.lld -pie -Bsymbolic --no-undefined -nostdlib --gc-sections \
        --entry=applet_entry -T "$SDK/gui_v2.ld" \
        "$base.o" "$OUT/v2_pic_malloc.o" "$OUT/arm_eabi_mem.o" "$OUT/syscalls.o" \
        -o "$base.elf"
    "$OUT/sidbox-v2-packer" "$base.elf" "$base.app.tmp" --heap 16384
    "$OUT/v2_format_test" "$base.app.tmp"
    [[ "$(od -An -tu4 -j48 -N4 "$base.app.tmp" | tr -d '[:space:]')" == 16384 ]] || fail 'Incorrect V2 heap reservation'
    mv "$base.app.tmp" "$base.app"
    printf 'PASS: V2 PIC allocator applet %s built and validated\n' "$variant"
done
cmp -s "$OUT/v2-pic-malloc-a.app" "$OUT/v2-pic-malloc-b.app" && fail 'A/B images unexpectedly identical'
printf '\nPASS: HOST build completed with our PIC allocator. NOT stock Newlib.\n'
printf 'Hardware behaviour still UNTESTED. Applets:\n  %s\n  %s\n' "$OUT/v2-pic-malloc-a.app" "$OUT/v2-pic-malloc-b.app"
