#!/usr/bin/env bash
# SIDBOX Applet V2 Stage 5A — builds TWO hardware heap test applets.
# Works from the real IDE/tests/stage5 location or from an extracted ZIP.
# It DOES NOT modify firmware, an existing project, or installed libraries.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IDE="$(cd "$HERE/../.." && pwd)"
OUT="$HERE/host-build"
mkdir -p "$OUT"
for cmd in clang ld.lld g++ cc sed; do
  command -v "$cmd" >/dev/null || { echo "ERROR: missing $cmd" >&2; exit 1; }
done

if [[ -n "${SIDBOX_IDELIBS:-}" ]]; then
  SDK="$SIDBOX_IDELIBS"
elif [[ -f "$IDE/idelibs/gui_v2.ld" ]]; then
  SDK="$IDE/idelibs"
else
  SDK="$HERE/bundled"
fi

if [[ -f "$SDK/api/graphics/graphics.h" ]]; then
  API="$SDK/api"
else
  API="$HERE/bundled/sdk_api"
fi
if [[ -n "${SIDBOX_SYSCALLS_SOURCE:-}" ]]; then
  SYS_SOURCE="$SIDBOX_SYSCALLS_SOURCE"
elif [[ -f "$SDK/api/syscalls.c" ]]; then
  SYS_SOURCE="$SDK/api/syscalls.c"
else
  SYS_SOURCE="$HERE/bundled/syscalls.c"
fi
if [[ -f "$IDE/v2_packer.cpp" ]]; then
  PACKER_CPP="$IDE/v2_packer.cpp"
elif [[ -f "$IDE/tools/v2_packer.cpp" ]]; then
  PACKER_CPP="$IDE/tools/v2_packer.cpp"
else
  PACKER_CPP="$HERE/bundled/v2_packer.cpp"
fi

[[ -f "$SDK/gui_v2.ld" ]] || { echo "ERROR: no gui_v2.ld in $SDK" >&2; exit 1; }
[[ -f "$SYS_SOURCE" ]] || { echo "ERROR: no SDK syscalls.c in $SYS_SOURCE" >&2; exit 1; }
[[ -f "$API/apis.h" ]] || { echo "ERROR: no CoderGirl SDK at $API" >&2; exit 1; }
# Only use a V2-aware SDK _sbrk; do NOT accidentally test the old V1 allocator.
grep -q 'SIDBOX_APPLET_V2' "$SYS_SOURCE" || { echo "ERROR: selected syscalls.c lacks SIDBOX_APPLET_V2 support" >&2; exit 1; }
grep -q 'section(".text.applet_entry")' "$SYS_SOURCE" || {
  echo "ERROR: SDK startup section changed; inspect build script before testing" >&2; exit 1;
}
printf 'V2 Stage 5A: SDK=%s\n                syscalls=%s\n                packer=%s\n' "$SDK" "$SYS_SOURCE" "$PACKER_CPP"

# Compile the *real* SDK allocator, not a hand-written copy. The SDK also
# defines a second applet_entry, which would conflict with the test. Rename
# that ENTRY FUNCTION ONLY and remove its forced KEEP linker section in this
# temporary copy. _sbrk and initMalloc are otherwise byte-for-byte unchanged.
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

g++ -std=c++17 -O2 -Wall -Wextra -Werror -pedantic \
    "$PACKER_CPP" -o "$OUT/sidbox-v2-packer"
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic \
    -I"$HERE" "$HERE/v2_format_test.c" -o "$OUT/v2_format_test"
for variant in A B; do
  lower="$(printf %s "$variant" | tr '[:upper:]' '[:lower:]')"
  base="$OUT/v2-heap-$lower"
  clang "${COMMON[@]}" -DSTAGE5_APP_"$variant" \
    -c "$HERE/heap_test.c" -o "$base.o"
  ld.lld -pie -Bsymbolic --no-undefined -nostdlib --gc-sections \
    --entry=applet_entry -T "$SDK/gui_v2.ld" \
    "$base.o" "$OUT/syscalls.o" -o "$base.elf"
  "$OUT/sidbox-v2-packer" "$base.elf" "$base.app" --heap 16384
  "$OUT/v2_format_test" "$base.app"
  if [[ "$(od -An -tu4 -j48 -N4 "$base.app" | tr -d '[:space:]')" != 16384 ]]; then
    echo "ERROR: applet header's heap_size != 16384" >&2
    exit 1
  fi
  grep -aq "$variant: HEAP BOUNDS PASS" "$base.app" || {
    echo "ERROR: success text missing in $variant" >&2; exit 1;
  }
done
cmp -s "$OUT/v2-heap-a.app" "$OUT/v2-heap-b.app" && {
    echo 'ERROR: both applets have identical images' >&2; exit 1;
}
printf '\nPASS: two separate ARM V2 heap tests built with the REAL SDK _sbrk().\n'
printf 'Host relocation/CRC tests passed. Hardware heap boundaries NOT YET verified.\n'
printf 'Copy to SIDBOX:\n  %s/v2-heap-a.app\n  %s/v2-heap-b.app\n' "$OUT" "$OUT"
