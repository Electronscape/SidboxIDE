# Stage 5.62.231026 — HUD Designer native SIDBOX font preview

## Issue

The HUD Designer `gamehudeditor.cpp::previewText()` was rendering a desktop
`QFontDatabase::FixedFont` and stretching it into the SIDBOX 8×16 character
bounds. The cell size looked right but the font glyphs did not match the
SIDBOX graphical system font shown in GUI Designer and Title Screen Designer.

## Change

- HUD `previewText()` now calls `GuiDesignerDetail::drawCoderGirlText()` from
  `guidesigner_graphics.cpp` via `guidesigner_detail.h`. This uses the existing
  canonical `kCoderGirlSystemFont[256][8]` glyph table, with rows doubled to
  8×16 pixels.
- All text drawn through `previewText()` is covered: HUD labels, numeric
  health/lives/score/custom stats, and collectable counters.
- Existing foreground CLUT display colours and optional 1-pixel outlines are
  preserved; the preview still responds to HUD zoom.
- Embedded newlines in the preview are allocated enough glyph rows.
- No new font data or graphics file is introduced.

## Files modified

- `gamehudeditor.cpp`
- `splashscreenwidget.cpp` — `Build: 5.62.231026`
- `README.md`
- New test: `development/tests/test_stage562_hud_sidbox_glyphs.py`

## Scope

This is an **IDE preview-only** correction. No change to game HUD project
files, generated C, `gfx_drawtext()`, PPBs, palettes, SIDBOX runtime or TFCard.
No game-project regeneration is necessary.

## Validation

`python3 development/tests/test_stage562_hud_sidbox_glyphs.py`: PASS.
It verifies the canonical 256-glyph table and the three HUD preview call sites.
The full Qt6 build and physical visual comparison have **not** been run in this
environment (Qt6 development libraries are not installed).
