#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"
SDK="${SIDBOX_IDELIBS:-$ROOT/../../ide/idelibs}"
if [[ ! -d "$SDK/api" && -d "$ROOT/../source/ide/idelibs/api" ]]; then
    SDK="$ROOT/../source/ide/idelibs"
fi
if [[ ! -d "$SDK/api" && -d "$ROOT/../ide/idelibs/api" ]]; then
    SDK="$ROOT/../ide/idelibs"
fi
[[ -f "$SDK/gui_v2.ld" ]] || { echo "ERROR: gui_v2.ld not found in $SDK" >&2; exit 1; }
INCLUDE_API="$SDK/api"
if [[ ! -f "$INCLUDE_API/graphics/graphics.h" ]]; then
    INCLUDE_API="$ROOT/sdk_api" # self-contained copy of SDK public headers for this test
fi
[[ -f "$INCLUDE_API/graphics/graphics.h" ]] || {
    echo "ERROR: missing complete applet SDK headers; set SIDBOX_IDELIBS=/path/to/idelibs" >&2
    exit 1
}
OUT="$ROOT/host-build"
mkdir -p "$OUT"
command -v clang >/dev/null || { echo "ERROR: install clang" >&2; exit 1; }
command -v ld.lld >/dev/null || { echo "ERROR: install lld" >&2; exit 1; }
clang --target=armv7em-none-eabihf -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard \
  -std=gnu11 -Oz -Wall -Wextra -Werror -ffreestanding -fno-builtin -fPIC -fPIE -fdata-sections -ffunction-sections   -DSIDBOX_APPLET_V2 \
  -I"$ROOT/include" -I"$INCLUDE_API" -c "$ROOT/gui_button_demo.c" -o "$OUT/gui_button_demo.o"
ld.lld -pie -Bsymbolic --no-undefined -nostdlib --gc-sections --entry=applet_entry \
  -T "$SDK/gui_v2.ld" "$OUT/gui_button_demo.o" -o "$OUT/gui_button_demo.elf"
python3 "$SDK/tools/v2_packer.py" "$OUT/gui_button_demo.elf" "$OUT/gui_button_demo-v2.app" --heap 16384
cc -std=c11 -Wall -Wextra -Werror -pedantic -I"$ROOT"   "$ROOT/v2_format_test.c" -o "$OUT/v2_format_test"
"$OUT/v2_format_test" "$OUT/gui_button_demo-v2.app"
python3 "$ROOT/check_gui_image.py" "$OUT/gui_button_demo-v2.app"
printf '\nGENERATED: %s\n' "$OUT/gui_button_demo-v2.app"
