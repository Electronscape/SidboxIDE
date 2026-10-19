# GamerGirl Stage 3.73 — PNG Transparency Key Import

## What changed

This stage updates the PNG palette importer so one exact source RGB colour can be treated as transparency and mapped to palette index 0.

### New importer UI
- Checkbox: **One source colour is meant to be transparent (map to index 0)**
- Button: **Choose colour...**
- Preview swatch showing the selected key colour (defaults to `#FF00FF`)

### Behaviour
- Alpha below 50% still becomes index 0 as before.
- When the new transparency-key option is enabled, every source pixel matching the chosen RGB colour is also mapped to index 0.
- Those pixels are excluded from palette generation, which frees one extra palette slot in the selected range.
- This works for both **Generate colours in selected range** and **Match existing palette colours** modes.

## Files changed
- `pngpaletteimport.cpp`
- `pngpaletteimport.h`

## Installation
Replace the two source files in the IDE tree, rebuild in Qt Creator, then test **Import PNG Image** from Game Designer.

Suggested first test:
1. Import a PNG that uses magenta (`#FF00FF`) for transparency.
2. Choose **Foreground CLUT**.
3. Choose **Generate colours in selected range**.
4. Set the range to `224–255`.
5. Tick **One source colour is meant to be transparent**.
6. Leave the colour at `#FF00FF` or choose another exact colour.
7. Confirm the preview shows the magenta pixels as transparent and the status text reports the generated colour count.

No game runtime files changed in this stage.
