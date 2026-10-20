# GamerGirl / SIDBOX IDE — Stage 4.10: Compact Tilemap Flag Toolbar

Built on the **complete Stage 4.09 source tree**. Presentation-only changes to the Tilemap Editor.

## Installation

From the **changed-files** archive, copy these two source files into your IDE source root:

- `gametilemap.cpp`
- `gametilemap.h`

Rebuild the Qt6 IDE as normal. The `development/tests/*.py` files in the archive are optional source-level regression checks and do not need copying to build the IDE.

Alternatively unpack the full IDE archive and rebuild it.

## New toolbar (left to right)

`[Apply tile flags ▼] [Cell Flip X] [Cell Flip Y] [Stamp Flip X] [Stamp Flip Y] | [Draw in front] [Stamp: use Draw Front setting] | [Show player reference] [Show player hitbox]`

- Every switch is a **checkable button with a custom 24×24 icon** inside a square 38×36 button frame.
- Checked state uses the existing game-editor theme's selected colour. Icons switch between the selected contrast colour and normal theme text colour. No external icon assets or fonts.
- Hover to see a descriptive tooltip. Button accessibility names are populated too.
- The player buttons and their divider are hidden when no valid `player` sprite resource is available.
- The stamp X/Y buttons remain disabled on the Collision Stamps tab, exactly as before.
- Painting/mirroring, flags, QSettings preferences and player-overlay code are unchanged; only the UI widgets and their connections were adapted to `QToolButton`.
- Removed the extra standalone Stamp Front and two player-toggle rows to free vertical space.

## Regression tests

42 of 46 applicable Stage 3.x–4.10 Python structural/source checks passed. Four older source checks (`test_stage371_guidesigner_refactor.py`, `test_stage376_tile_atlas_resources.py`, `test_stage384_animation_editor_structure.py`, `test_stage385_animation_drag_cards.py`) already fail in the **unmodified Stage 4.09 source tree**, because their assertions refer to much older implementation details. The new Stage 4.10 check and the Stage 4.03–4.09 checks pass.

Qt6 development headers were unavailable in this environment, so a native Qt build and visual inspection on Fedora are still required.

## Quick visual test on Fedora

1. Open an `.sbgm` Tilemap Editor. Confirm one compact flags toolbar appears (instead of old checkbox rows), with a dropdown on the left and 24px icons.
2. Click each toggle: the button must stay highlighted while enabled. Hover to read the tooltip; dark and light themes must both be legible.
3. Paint a cell with X/Y flips and front/back, then change the flag dropdown. Save/reopen: painting settings must behave exactly as before.
4. Paint a stamp with both mirrors; test the Stamp front override. Try switching to the Collision Stamps tab (mirrors should disable).
5. If a `player` sprite exists, toggle its two overlays, drag the reference, press Space with your mouse over the map, and check the coloured hitbox clearance.

No firmware update. No runtime, exporter, `.map` or `.sbgm` format changes.
