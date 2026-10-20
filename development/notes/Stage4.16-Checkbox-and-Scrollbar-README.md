# GamerGirl / CoderGirl Stage 4.16 — Checkbox and Scrollbar Hotfix

Base: Stage 4.15 full IDE source.

## Changes

1. **Unchecked checkboxes no longer change shape.** Both checked and unchecked indicators are now cached as full 16 x 16 PNGs in the central `ideglobaltheme.h`. All indicator states use the same 16 x 16 size, with no separate CSS border adding 2 px to the unchecked box. The existing `icons/checkbox_tick.png` still supplies the checked mark, and both icons regenerate when the theme or custom tick changes. Nothing new is required in the `icons/` directory.
2. **Qt/KDE scrollbar width is now explicit.** Vertical scrollbars use 10 px width, horizontal scrollbars use 10 px height, including the popup scrollbar in the Tilemap collision dropdown. The drag handle remains at least 18 px long in its scrolling direction.
3. **No other GUI changes.** Tree alternating-row colours and other Stage 4.15 fixes remain unchanged.

## Installation

Replace **`ideglobaltheme.h`** in the IDE source root and rebuild; no CMake regeneration required.

Or extract the complete Stage 4.16 source archive into a separate location.

Included automated tests:
- `development/tests/test_stage416_checkbox_scrollbar.py` (new)
- `development/tests/test_stage414_global_theme.py` (updated old image naming check)
- `development/tests/test_stage401_shared_control_theme.py` (updated placeholder expansion check for the new unchecked image).

The selected Stage 4.00–4.16 source tests passed. The native Qt6 build is not available in this environment, so final compilation and visual testing on Fedora KDE are still required.

## Quick visual test

- Open Player Animation Editor and toggle Loop and Ping-pong, checking both remain square and 16 x 16 with a visible tick only when checked.
- Open Tilemap Editor > Collision dropdown. Its right-hand scrollbar should be roughly 10px wide, instead of the former wide KDE-style bar.
- Try another editor scrollbar and a light and dark IDE theme.

No firmware changes, no game-engine changes, no resource-format changes.
