# GamerGirl Stage 3.74 — Choose PNG Transparency from Source Palette

## Purpose

Replace the troublesome generic "Choose colour..." picker with colour swatches taken from the actual source PNG. You can select a source colour (for example magenta) and have it mapped to transparent output index 0, **before** generating the foreground palette in any selected range.

## Where

Game Designer -> Import PNG Image -> Import PNG to SIDBOX Indexed PPB.

### Using a 256-colour indexed PNG
1. Select Foreground CLUT.
2. Set Palette mode: Generate colours in selected range.
3. Set the range to 224 through 255.
4. Leave "Start with a blank palette" unchecked if you want to preserve all other foreground CLUT entries.
5. At the bottom, find the **Source PNG colours** swatches. Hover a swatch to see its **original PNG palette index**, exact RGB and number of pixels.
6. Click the magenta swatch. The "One PNG colour is transparent" checkbox turns on automatically, and the key preview updates.
7. The converted preview and source-colour count refresh automatically. Every matching magenta pixel is written as index 0. The colour does **not** consume any index within 224-255.
8. Continue to save the PPB and shared CLUT as usual.

The source swatch remains visible for reselecting; it is **removed from generated palette colours**, not deleted from the original PNG. The original PNG is never edited.

### Other PNG formats
- True-colour PNGs show up to the first 512 used RGB colours.
- **Ctrl+left-click** a pixel in the **Original PNG** preview to select *any* exact source RGB (including colours not listed among those 512). Ordinary dragging still pans the image.
- Existing alpha transparency (<50%) still maps to output index 0.
- Click the checkbox off to disable the colour key without losing your selection.

## Changes
- `pngpaletteimport.h`
- `pngpaletteimport.cpp`
- `development/tests/test_stage374_png_transparency.cpp` (new Qt6 conversion regression test)

No modifications to `.map`, `.sbgm`, game physics, SIDBOX runtime helpers, or palette file formats.

## Installation
Replace the two `pngpaletteimport` source files in the IDE source root and rebuild in Qt Creator. There are no CMake changes.

## Checks and limitations
- Static importer integration checks passed.
- Existing Stage 3.67 slippery slope and Stage 3.72 loop-entry C regressions passed.
- **Qt6 GUI build and the new Qt6 conversion test require your machine**, because Qt6 development libraries are not installed in this environment.
- To run the optional conversion test from the IDE source root with Qt6 development packages installed:

  `g++ -std=c++17 -fPIC -I. development/tests/test_stage374_png_transparency.cpp pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) -o /tmp/gg_png_transparency_test && /tmp/gg_png_transparency_test`
