# GamerGirl Stage 3.77 — Protect PNG Colours During Quantisation

## Why this change exists
When reducing a 32-bit PNG to 32 CLUT entries, weighted median-cut can merge tiny accents, such as the player's blue eyes, into surrounding hues. Transparency-key selection already handles magenta/index 0; this update lets you reserve exact source RGB colours too.

## How to use
1. Open **Game Designer → Import PNG**.
2. Choose **Foreground CLUT**, **Generate colours in selected range**, and range **224–255**.
3. Leave **Start with a blank palette** unchecked to preserve the rest of your project CLUT.
4. Click magenta in the source-colour palette to make it transparent at index 0.
5. Hold **Shift** and click the first blue in the source-colour palette. A star appears on the swatch.
6. **Shift+click** the second blue. You now have two protected exact colours.
7. The 32 available palette slots include these two colours; the quantiser automatically fills up to the other 30. Preview and confirm, then save normally.

Shortcuts:
- Click a swatch: choose transparent colour (existing behaviour).
- Shift+click a swatch: protect/unprotect exact source RGB for the output CLUT.
- Ctrl+click the Original PNG preview: choose transparency colour.
- Ctrl+Shift+click the Original PNG preview: protect/unprotect exact colour at that pixel. Useful if the swatch list shows only the first 512 colours.

## Constraints and semantics
- Protected colours must be present in the source PNG to be useful; they remain exact, including when dithering is enabled.
- The selected transparent RGB cannot simultaneously be protected; selecting it as transparent removes it from the protect list.
- Protected entries are generated at the first indices in the selected range (two pinned colours in 224–255 go to indices 224 and 225); the rest of the range is quantised normally.
- Colours outside the selected CLUT range are preserved. Index 0 remains transparent.
- Matching an existing palette does not use protected colours, because it must not modify the palette.
- Unmarked PNG imports behave like Stage 3.76.
- This changes palette/index allocation, not runtime map, hitboxes, animation, SIDBOX graphics, or physics.

## Files changed
- `pngpaletteimport.cpp`
- `pngpaletteimport.h`
- `development/tests/test_stage377_png_protected_colours.cpp` (Qt6 regression; requires Qt6 development files)
- `development/tests/test_stage377_png_protection_structure.py` (source guard)
- Updated two old source-layout checks to allow the intentional converter change.

## Build/test
Rebuild the IDE using Qt Creator. The new Qt6 regression can be run on your Fedora machine from the IDE source root using:

```
g++ -std=c++17 -fPIC -I. development/tests/test_stage377_png_protected_colours.cpp \
    pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) -o /tmp/gg_png_protect_test
QT_QPA_PLATFORM=offscreen /tmp/gg_png_protect_test
```

The existing source, slope handoff, loop entry and animation-generated-C regressions were run on the host. Qt6 is not installed in this build environment, so the Qt GUI compilation and the Qt6 colour-conversion regression remain for workstation testing.
