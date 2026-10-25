# CoderGirl Stage 5.99.2: Player reply font scaling

**Source baseline:** Stage 5.99.1, including its Qt6 `std::max` compilation fix.

## What changed

- `idelibs/codehelpers/game/adventureruntime.rulec`:
  - The player's spoken reply bubble (dialogue state 3, drawn near the player) now uses `ga_dialog_scale_x` and `ga_dialog_scale_y`, matching the main dialogue.
  - Reply wrapping uses 8 × X-scale glyph widths; successive lines advance by 8 × Y-scale pixels (plus 4 when outlines are on).
  - Large X scales allow a wider bubble. Reply heights are bounded to the 480×320 LCD, and high scales show only as many lines as can safely fit.
  - The legacy 1×2 reply layout keeps its original 205/280-pixel widths, five-line limit and `gfx_drawtext` rendering path.
  - Inventory menus, item names, USE/DROP/DESTROY commands, and destroy confirmations remain on the original font renderer.
- `splashscreenwidget.cpp`: `Build: 5.99.2.251026`.
- `development/tests/`: new native reply-scale test and updated version expectations for the 5.98/5.99 pipeline guards.

## Install

Copy the ZIP contents over the **IDE source root**, preserving the paths, then rebuild the IDE. Because this is an engine template, open your game and run **Update Game Project** before rebuilding the game. No edits to the user's `main.c` are needed.

## Native verification

- Stage 5.99.2 reply scaling (1×1, 1×2, 2×4, 8×8), row spacing, LCD bounds, unscaled inventory: PASS
- Stage 5.98 thought bubbles: PASS
- Stage 5.99 typography/z-order: PASS
- Stage 5.97 message sequences: PASS
- Stage 5.96 dialogue modes: PASS
- Stage 5.94 trigger/reward guard: PASS
- Stage 5.98/5.99 editor pipeline checks: PASS

**Not verified:** Qt6 IDE compilation and actual STM32 SIDBOX rendering. Extremely large glyphs necessarily fit fewer characters/lines in a 480×320 reply bubble.
