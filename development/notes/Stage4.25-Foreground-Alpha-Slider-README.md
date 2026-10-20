# GamerGirl Stage 4.25 — Foreground Palette Alpha Slider

Based on **Stage 4.24** complete IDE source. This release only changes Qt editor code.

## Installation

EITHER extract `IDE-GamerGirl-Stage4.25-Full.tar.gz` as a complete IDE source tree, OR extract `IDE-GamerGirl-Stage4.25-Changed-Files.tar.gz` over your existing Stage 4.24 source, preserving relative paths. Rebuild your Qt6 IDE.

Changed production files:
- `gamepaletteeditor.cpp`
- `gamepaletteeditor.h`
- `gamedesigner.cpp`
- `gamedesigner.h`
- `gamedesigner_project.cpp`

## Palette Editor

The **Alpha** slider sits under the selected index/ARGB colour row.
- Foreground indices 1–255: slider edits 0–255 alpha of *only the selected entry*, preserving RGB.
- Foreground index 0: slider is disabled (reserved transparent for SIDBOX graphics).
- Background palette: slider disabled, alpha is always 255.
- The selected entry's 0xAARRGGBB hex value, checkerboard swatch and 16×16 atlas of palette entries update as you move the slider.
- `Pick Colour...` and manual hex edits update the slider as soon as their changes are applied.
- Changing alpha marks the palette modified; **Save** writes the .pal and closes on success (Stage 4.23 behaviour). **Save As** still stays open.
- Existing .pal single-bank (1024 bytes) and two-bank (2048 bytes) serialisation is unchanged: each colour is stored as four bytes, including alpha.
- The existing zero-alpha repair prompt remains opt-in. If alpha 0 on nonzero indices is intentional, don't choose the repair option.

## World Designer

**Game Resources → Force preview CLUTs → Preview palette alpha** is a new checkbox (default OFF).
- OFF: preserves the previous forced-CLUT colour preview (foreground index 0 transparent, all other indices visually opaque).
- ON: renders actual foreground alpha bytes from the selected foreground CLUT; background is still fully opaque. The preview applies to sprites, tilemap overlay, and the Game Object editor's sprite preview.
- The checkbox is available only when *Force preview CLUTs* is selected.
- The preview toggle is saved as `previewPaletteAlpha` in `.sbgm`. Existing projects default to OFF.
- The setting changes preview rendering only; no PPB pixels, generated game runtime or CLUT contents are modified by toggling it.
- Independent foreground/background colour cycles continue to rotate full ARGB entries, including alpha.

## Suggested smoke test

1. Make a backup of a foreground `.pal`. Open it in Game Resources → palette editor.
2. Select foreground index 42, note the ARGB hex value, and move Alpha from 255 to 128. Verify only AA changes, and the checkerboard shows a semitransparent colour.
3. Change bank to Background and verify Alpha cannot be edited. Switch back; index 42 still reads 128.
4. Save. Reopen the .pal and confirm index 42 still reads `0x80RRGGBB`.
5. In World Designer, turn on **Force preview CLUTs**, then **Preview palette alpha**. An indexed sprite using index 42 should become translucent. Turn off preview and it should appear opaque again.
6. Save and reopen the `.sbgm`: preview preference should persist. Run a colour cycle that contains differently transparent entries and verify the transparency rotates along with the RGB colours.
7. Verify actual SIDBOX transparency/blending using the saved palette on hardware; this release doesn't change the firmware.

## Validation

27 Stage 4.00–4.25 source regression checks passed. A native Qt6 build and hardware/visual checks must still be performed on the user's Fedora machine; Qt6 development libraries are not present in the packaging environment.
