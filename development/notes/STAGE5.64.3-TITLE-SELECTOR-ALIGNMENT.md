# Stage 5.64.3 — Title selector rectangle alignment

Date: 23 October 2026

## Hardware feedback

On the actual SIDBOX STM32H743, the filled menu selection rectangle appears
approximately **6 pixels below** its intended position relative to the menu
text, while its left and right edges look correct. The editor title preview
also puts the glyph 1 pixel below the stored Y, because of a permanently
inserted 1px transparent image margin.

## Changes

- `idelibs/codehelpers/game/gametitle-runtime.rulec`: move **only** the
  filled selection rectangle 6 px upward (`y-2` to `y-8`). Keep its X and
  width unchanged. This is an **empirical offset**, pending confirmation on
  hardware, not an undocumented claim about `gfx_rectf` or `gfx_drawtextf`.
- `gametitlescreeneditor.cpp::textImage()`: text images without outline
  contain exactly the native 8x8 glyph multiplied by the independent X/Y
  scales. There is no +1px transparent border that shifts X/Y.
- Outlined text has 1px border added **after** scaling, like the runtime's
  `gfx_drawtextf` calls at +/-1 pixel. `QGraphicsPixmapItem::setOffset(-1,-1)`
  anchors the glyph at the actual saved X/Y even with that border.
- The preview filled selector uses the actual glyph rectangle rather than
  outline-padded scene bounds; it retains x-3 and width+6, as on hardware.
  The fill has no Qt stroke/half-pixel border.
- Splash label: `Build: 5.64.3.231026`.

## Integration and tests

Existing title-screen `.sidbox-title-screen.json` data is untouched.
Regenerate `gamehelpers/gametitle.c` to pick up the runtime change, then
rebuild the game. The correction does not require changing protected `main.c`.

Run: `python3 development/tests/test_stage5643_selector_alignment.py`
Regression tests cover static source contracts, not actual hardware pixels.
The six-pixel calibration must be visually checked on SIDBOX.
