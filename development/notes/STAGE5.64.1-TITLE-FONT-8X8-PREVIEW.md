# Stage 5.64.1 — Native SIDBOX 8×8 title font preview

23 October 2026

## Hardware observation

The real SIDBOX `gfx_drawtextf(..., size_x=1, size_y=1)` renders its
system glyphs at **8×8 pixels**. The GUI Designer intentionally doubles the
8 bitmap rows to 16 display rows for GUI previews. The Title Screen Designer
was reusing that stretched version, so its text preview was twice as tall as
the actual title-screen runtime.

## Fix

- `gametitlescreeneditor.cpp::textImage()` still calls the canonical
  `GuiDesignerDetail::drawCoderGirlText()` for exactly the right SIDBOX glyphs.
  It then reduces the GUI-only 16-row representation to the original 8-row
  source using nearest-neighbour (`Qt::FastTransformation`) before applying
  **Font Size X** and **Font Size Y** independently.
- Native glyph height at Y=1 is now 8 px; Y=2 is 16 px. Larger values retain
  the previously implemented stage scaling pending further hardware tests.
- The internal preview's two-pixel outline padding is retained (image bounds
  include one transparent/outline pixel on each edge when appropriate).
- The font-size control now describes the native 8×8 font.
- `idelibs/codehelpers/game/gametitle-runtime.rulec::title_height()` uses an
  8 px baseline, so filled rectangle and underline selectors fit title text
  correctly. It does not change `gfx_drawtextf` parameters or glyph data.
- The splash build string is `Build: 5.64.1.231026`.

## Compatibility and integration

Existing `.sidbox-title-screen.json` coordinates, artwork, outline colours,
fontSizeX/fontSizeY, menu definitions and PPBs do not change. No changes to
the GUI Designer or HUD Designer, whose deliberately 8×16 previews are separate.

Rebuild the Qt IDE and reopen the title design to see the corrected text size.
**Regenerate the title runtime/game helper once** when convenient so its menu
selector height uses the new 8 px baseline; copy regenerated main integration
only if you actually need it. CoderGirl must never overwrite your `main.c`.

## Tests

Run from the root of the IDE source:

```
python3 development/tests/test_stage5641_title_font_native8.py
python3 development/tests/test_stage5611_title_font_preview.py
python3 development/tests/test_stage5601_title_preview_crash.py
python3 development/tests/test_stage564_title_runtime.py
```

These are static source regressions, not a substitute for the Fedora Qt6 build
or actual STM32H743 screen test.
