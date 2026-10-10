#!/usr/bin/env bash
# Stage 5B — REAL GNU Arm Newlib malloc/free/calloc/realloc applet experiment.
# Requires the IDE's private ARM GCC with Newlib. Does NOT flash hardware.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IDE="$(cd "$HERE/../.." && pwd)"
OUT="$HERE/host-build"
mkdir -p "$OUT"
# Do not leave stale, apparently valid Stage 5B test applets after failed runs.
rm -f "$OUT/v2-malloc-a.app" "$OUT/v2-malloc-b.app" \
      "$OUT/v2-malloc-a.app.tmp" "$OUT/v2-malloc-b.app.tmp"

fail() { printf 'ERROR: %s\n' "$*" >&2; exit 1; }
for program in ld.lld g++ cc readelf; do
  command -v "$program" >/dev/null || fail "Missing $program. On Fedora: sudo dnf install lld gcc gcc-c++ binutils"
done

if [[ -n "${SIDBOX_IDELIBS:-}" ]]; then
  SDK="$SIDBOX_IDELIBS"
elif [[ -f "$IDE/idelibs/gui_v2.ld" ]]; then
  SDK="$IDE/idelibs"
else
  SDK="$HERE/bundled"
fi
if [[ -f "$SDK/api/apis.h" ]]; then
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
  PACKER_SOURCE="$IDE/v2_packer.cpp"
else
  PACKER_SOURCE="$HERE/bundled/v2_packer.cpp"
fi

# GCC is deliberately not required on PATH; IDE ships its private copy.
if [[ -n "${SIDBOX_ARM_GCC:-}" ]]; then
  GCC="$SIDBOX_ARM_GCC"
elif [[ -x "$SDK/tools/bin/arm-none-eabi-gcc" ]]; then
  GCC="$SDK/tools/bin/arm-none-eabi-gcc"
elif [[ -x /home/kbox/sidbox-applet-compiler/tools/bin/arm-none-eabi-gcc ]]; then
  GCC=/home/kbox/sidbox-applet-compiler/tools/bin/arm-none-eabi-gcc
elif command -v arm-none-eabi-gcc >/dev/null; then
  GCC="$(command -v arm-none-eabi-gcc)"
else
  fail "ARM GCC/Newlib unavailable. Set SIDBOX_ARM_GCC=/absolute/path/to/arm-none-eabi-gcc (no PATH changes needed)."
fi
[[ -x "$GCC" ]] || fail "ARM GCC executable not found: $GCC"
[[ -f "$SDK/gui_v2.ld" ]] || fail "Missing gui_v2.ld in $SDK"
[[ -f "$API/apis.h" ]] || fail "Missing CoderGirl applet headers: $API/apis.h"
[[ -f "$SYS_SOURCE" ]] || fail "Missing SDK syscalls.c: $SYS_SOURCE"
grep -q 'SIDBOX_APPLET_V2' "$SYS_SOURCE" || fail "Your syscalls.c is not V2-aware; do not substitute a legacy _sbrk()"

ARCH=(-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard)
NEWLIB="$($GCC "${ARCH[@]}" --specs=nano.specs -print-file-name=libc_nano.a)"
LIBGCC="$($GCC "${ARCH[@]}" -print-file-name=libgcc.a)"
if [[ ! -f "$NEWLIB" || "$NEWLIB" == libc_nano.a ]]; then
  fail "ARM Newlib Nano library absent. GCC must provide libc_nano.a; got '$NEWLIB'."
fi
[[ -f "$LIBGCC" && "$LIBGCC" != libgcc.a ]] || fail "ARM libgcc.a missing; got '$LIBGCC'"

printf 'SIDBOX V2 Stage 5B — REAL Newlib test\n'
printf '  ARM GCC: %s\n  Newlib:  %s\n  SDK:     %s\n  syscalls: %s\n' \
    "$GCC" "$NEWLIB" "$SDK" "$SYS_SOURCE"

# Retain the real SDK _sbrk unchanged; remove its alternate applet_entry
# from this test-only copy (the test owns the entry/callback).
if ! grep -q 'section(".text.applet_entry")' "$SYS_SOURCE"; then
  fail 'SDK startup section changed: inspect syscalls.c before testing'
fi
sed 's/section(".text.applet_entry")/section(".text.unused_sdk_entry_for_test")/' \
  "$SYS_SOURCE" > "$OUT/syscalls_test_compile.c"

COMMON=("${ARCH[@]}" -std=gnu11 -Os -Wall -Wextra -ffreestanding
  -fno-builtin -ffunction-sections -fdata-sections -fPIC -fPIE
  -fvisibility=hidden -DSIDBOX_APPLET_V2 -DSIDBOX_V2_HEAP_BYTES=16384
  -I"$API")
"$GCC" "${COMMON[@]}" -Wno-unused-parameter -Wno-unused-function \
  -DSIDBOX_STARTUP_HEADER_IN_ASM -Dapplet_entry=sdk_entry_not_used \
  -c "$OUT/syscalls_test_compile.c" -o "$OUT/syscalls.o"

g++ -std=c++17 -O2 -Wall -Wextra -Werror -pedantic \
  "$PACKER_SOURCE" -o "$OUT/sidbox-v2-packer"
cc -std=c11 -O2 -Wall -Wextra -Werror -pedantic -I"$HERE" \
  "$HERE/v2_format_test.c" -o "$OUT/v2_format_test"

for variant in A B; do
  lower="$(printf %s "$variant" | tr '[:upper:]' '[:lower:]')"
  base="$OUT/v2-malloc-$lower"
  "$GCC" "${COMMON[@]}" -DSTAGE5B_APP_"$variant" \
    -c "$HERE/malloc_test.c" -o "$base.o"

  # The linker may reject the system Newlib archive because it was built
  # without PIC. NEVER pretend a nonrelocatable image is safe to flash.
  if ! ld.lld -pie -Bsymbolic --no-undefined --gc-sections \
      --entry=applet_entry -T "$SDK/gui_v2.ld" \
      "$base.o" "$OUT/syscalls.o" \
      --start-group "$NEWLIB" "$LIBGCC" --end-group \
      -o "$base.elf" >"$base.link.log" 2>&1; then
    cat "$base.link.log" >&2
    fail "The stock GNU Newlib build cannot yet link as a V2 PIE. NO flashable applet produced. Send the errors; we will address its relocation/startup requirements."
  fi
  readelf -rW "$base.elf" > "$base.relocations.txt"
  if ! "$OUT/sidbox-v2-packer" "$base.elf" "$base.app.tmp" --heap 16384; then
    rm -f "$base.app.tmp"
    fail "V2 packer rejected the Newlib PIE; inspect '$base.relocations.txt'. NO flashable applet produced."
  fi
  "$OUT/v2_format_test" "$base.app.tmp"
  # These symbols MUST come from real Newlib, not test definitions.
  SYMBOLS="$OUT/$lower-symbols.txt"
  readelf -sW "$base.elf" > "$SYMBOLS"
  for fn in malloc free realloc calloc _sbrk; do
    grep -Eq "[[:space:]]${fn}(\$|[[:space:]])" "$SYMBOLS" || fail "Missing $fn symbol in linked applet"
  done
  mv "$base.app.tmp" "$base.app"
  printf 'PASS: applet %s linked Newlib malloc/free/realloc/calloc and passed V2 validation\n' "$variant"
done
cmp -s "$OUT/v2-malloc-a.app" "$OUT/v2-malloc-b.app" && fail 'A and B are identical; expected independent variants'
printf '\nBOTH NEWLIB TESTS COMPILED. Firmware execution NOT YET verified.\n'
printf 'Copy to SIDBOX SD:\n  %s/v2-malloc-a.app\n  %s/v2-malloc-b.app\n' "$OUT" "$OUT"
