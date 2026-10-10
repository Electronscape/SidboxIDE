#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(cd "$ROOT/../.." && pwd)"
# Works inside the installed IDE tree and inside the original Stage 4 archive.
if [[ -n "${SIDBOX_IDELIBS:-}" ]]; then
  SDK="$SIDBOX_IDELIBS"
elif [[ -f "$PROJECT_ROOT/idelibs/gui_v2.ld" ]]; then
  SDK="$PROJECT_ROOT/idelibs"
else
  SDK="$PROJECT_ROOT/ide/idelibs"
fi
if [[ ! -f "$SDK/gui_v2.ld" ]]; then
  printf 'ERROR: gui_v2.ld not found in %s\n' "$SDK" >&2
  printf 'From IDE root, run: SIDBOX_IDELIBS="$PWD/idelibs" bash tests/stage4/build_dual_test.sh\n' >&2
  exit 1
fi
if [[ -f "$SDK/api/graphics/graphics.h" ]]; then
  INCLUDES="$SDK/api"
else
  INCLUDES="$ROOT/../stage3/sdk_api"
fi
for cmd in clang ld.lld g++ cc; do
  command -v "$cmd" >/dev/null || { echo "ERROR: missing $cmd" >&2; exit 1; }
done
OUT="$ROOT/host-build"
mkdir -p "$OUT"
# Build native packer from the EXACT same source that CMake compiles for the IDE.
# Prefer the new IDE-root source; accept older archived locations as fallbacks.
if [[ -f "$PROJECT_ROOT/v2_packer.cpp" ]]; then
  PACKER_SOURCE="$PROJECT_ROOT/v2_packer.cpp"
elif [[ -f "$PROJECT_ROOT/tools/v2_packer.cpp" ]]; then
  PACKER_SOURCE="$PROJECT_ROOT/tools/v2_packer.cpp"
elif [[ -f "$PROJECT_ROOT/ide/tools/v2_packer.cpp" ]]; then
  PACKER_SOURCE="$PROJECT_ROOT/ide/tools/v2_packer.cpp"
else
  echo "ERROR: v2_packer.cpp not found in the IDE root or old tools layout" >&2
  exit 1
fi
g++ -std=c++17 -O2 -Wall -Wextra -Werror -pedantic "$PACKER_SOURCE" -o "$OUT/sidbox-v2-packer"
for variant in A B; do
  name="v2-dual-$(echo "$variant" | tr '[:upper:]' '[:lower:]')"
  clang --target=armv7em-none-eabihf -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard \
    -std=gnu11 -Oz -Wall -Wextra -Werror -ffreestanding -fno-builtin -fPIC -fPIE \
    -fdata-sections -ffunction-sections -DSIDBOX_APPLET_V2 -DSTAGE4_APP_"$variant" \
    -I"$ROOT/../stage3/include" -I"$INCLUDES" -c "$ROOT/dual_gui_demo.c" -o "$OUT/$name.o"
  ld.lld -pie -Bsymbolic --no-undefined -nostdlib --gc-sections --entry=applet_entry \
    -T "$SDK/gui_v2.ld" "$OUT/$name.o" -o "$OUT/$name.elf"
  "$OUT/sidbox-v2-packer" "$OUT/$name.elf" "$OUT/$name.app" --heap 16384
  cc -std=c11 -Wall -Wextra -Werror -pedantic -I"$ROOT/../stage3" \
    "$ROOT/../stage3/v2_format_test.c" -o "$OUT/v2_format_test"
  "$OUT/v2_format_test" "$OUT/$name.app"
  grep -aq "APP $variant CALLBACK OK!" "$OUT/$name.app" || { echo "Missing $variant callback string" >&2; exit 1; }
done
cmp -s "$OUT/v2-dual-a.app" "$OUT/v2-dual-b.app" && { echo "ERROR: applets not distinct" >&2; exit 1; }
printf '\nPASS: two distinct relocatable applets; separate titles and callbacks, native C++ packer, V2 format tests.\n'
printf 'Copy BOTH files to SIDBOX SD:\n  %s\n  %s\n' "$OUT/v2-dual-a.app" "$OUT/v2-dual-b.app"
