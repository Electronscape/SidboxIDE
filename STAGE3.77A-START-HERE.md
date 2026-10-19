# GamerGirl Stage 3.77a — PNG Pixel Picker Crosshair

## Changes
- Hover the **Original PNG** preview and hold **Ctrl**: the mouse becomes a crosshair for accurate source-pixel selection.
- Ctrl+click still sets the transparency/key colour.
- Ctrl+Shift+click still protects/unprotects that exact source RGB colour (blue eyes, small accents, etc.).
- Let go of Ctrl and the usual pan/hand cursor returns.
- Only the original preview changes; the converted PPB preview remains a pan/zoom view.
- Works when the keyboard focus is elsewhere in the import dialog, e.g. the source-colour swatches.

## Safety
No alterations to PNG quantisation, CLUT assignment, colour protection, file formats, game code generation, physics, animation or tilemaps. Square-corner styling retained.

## Install
Use the full source archive or copy `pngpaletteimport.cpp` over the same-named file in your current Stage 3.77 IDE source root. There are no header changes. Rebuild the IDE with Qt Creator.

## Tests
The source-level structural checks and prior Python regressions can run without Qt. A Qt6 functional cursor regression is included at `development/tests/test_stage377a_png_picker_cursor.cpp`; it must be compiled on a machine with Qt6 dev packages. From the source root:

```
g++ -std=c++17 -fPIC -I. development/tests/test_stage377a_png_picker_cursor.cpp \
    pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) \
    -o /tmp/gg_png_cursor_test
QT_QPA_PLATFORM=offscreen /tmp/gg_png_cursor_test
```

This build environment does not have Qt6 installed; Qt compilation and mouse/keyboard behaviour require workstation verification.
