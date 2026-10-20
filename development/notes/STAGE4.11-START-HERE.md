GamerGirl Stage 4.11 — World Object Tags & Tilemap Paint Toolbar
Based on user archive: IDE - 20-10-2026-0839.tar.gz

CHANGED FILES (IDE source root)
  gamedesigner.cpp
  gametilemap.cpp
  gametilemap.h
Added source-only test:
  development/tests/test_stage411_tilemap_paint_modes.py

1. WORLD EDITOR: yellow Game Object name tags now have a 2.5px black
   outline. This affects displayed name labels only, not rendered assets.

2. TILEMAP EDITOR: yellow F (draw in front of player) markers in both
   the map canvas and Tile Stamp editor have a black outline. Better
   contrast against complex backgrounds.

3. TILE ATLAS (LEFT SIDEBAR): removed the visible Paint Graphic combo.
   Added three 16x16 themed, checkable icon glyphs directly above the
   atlas grid:
      NO ENTRY: Don't change graphic (-1), preserve existing tile artwork
      ERASE: Paint graphic ID 0 (empty/no artwork)
      ATLAS: Paint selected atlas tile (1)
   Tooltips explain each mode. The selected mode is highlighted.
   Clicking an atlas tile still automatically switches to ATLAS mode.

4. MAIN TILEMAP TOOLBAR: moved Paint Collision combo beside the flags.
   Immediately before that combo are two 24x24 checkable shortcuts:
      NO ENTRY: Don't change collision (-1)
      ERASE: Paint collision type 0 (empty/non-solid)
   Choosing any other collision type in the combo deselects both shortcuts.
   Name Zone / Custom is solid only appear for custom collision types.
   Existing flip X/Y, stamp flips, front flags, player overlay toggles,
   QSettings and brush semantics are unchanged.

INSTALLATION
   Replace all three source files listed above in your existing IDE root,
   then rebuild your Qt6 IDE. The test script is optional.

TESTING
   Source-level regression checks Stage 4.00 through 4.11: PASSED.
   Native Qt6 build/actual editor interactions: NOT YET TESTED here
   (Qt6 dev libraries aren't installed in this environment).
   Please confirm icon buttons, live mode updates, theme colors,
   painting, and custom zone controls on your Fedora system.

NO CHANGE TO
   STM32 firmware, platformer engine, .sbgm/.map serialization,
   project resource paths, sprite/player spawn, or 2048KB syntax limit.
