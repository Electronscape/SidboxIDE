# Stage 5.61.1.231026 — Title Screen uses native SIDBOX glyph preview

The Title Screen Designer previously approximated the 8x16 SIDBOX system font by rasterising the local desktop's fixed-width Qt font and stretching it to 8x16. This produced shapes that didn't match the real SIDBOX GUI font.

`gametitlescreeneditor.cpp::textImage()` now renders through `GuiDesignerDetail::drawCoderGirlText()`, the same drawing routine used by the GUI Designer. Its canonical `kCoderGirlSystemFont[256][8]` glyph data lives in `guidesigner_graphics.cpp`; each 8x8 glyph source row is doubled to reach 8x16. No separate font file, duplicate font table or runtime code is introduced.

The existing foreground palette colour, optional outline, independent X/Y size selectors (1x/2x/4x/8x) and previously saved title-screen design files are preserved. This update changes only the **design-time preview**, not the actual SIDBOX game runtime font.

## Files changed
- `gametitlescreeneditor.cpp`
- `splashscreenwidget.cpp` (Build: 5.61.1.231026)
- `development/tests/test_stage5611_title_font_preview.py`
- `README.md`

## Validation
The font source regression passes, confirming use of the exact GUI Designer drawing function and the complete 256-character table. The previous selection-crash regression also passes. This environment has no Qt6 development headers, so a full Qt6 compile and visual confirmation remain to be done on Fedora.

## Hardware API note
The scaling currently describes design-time X/Y scaling; runtime title-screen generation is not yet implemented. Its eventual `gfx_drawtextf` sizing semantics must be checked against the SIDBOX runtime implementation before generating production code.
