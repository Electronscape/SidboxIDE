# CoderGirl IDE Stage 5.43.231026 — 23 October 2026

## Fixes

1. **Inventory icon artwork now selects its PPB atlas in the same dialog as the
   single-cell / 2x2 stamp picker.** All registered sprite PPBs and tile-atlas
   PPBs are offered; default still means the dialogue atlas for compatibility.
   Cell size is selectable for explicit PPBs. Selecting a different PPB or cell
   size resets draft indices to cell 0, because they belong to the new sheet.
   OK saves `iconAtlasId`, `iconTileSize`, icon index and stamp cells together
   for that inventory row. No new PPB files are created. The top-of-table atlas
   selector continues to work as an alternative.

2. **Inventory DROP chooses the PPB assigned to the inventory item**, via the
   existing `gameadventuregen.cpp` lookup and runtime `game_adventure_item_atlas`
   registration. The wrong image reported in `world1.sbgm` was explainable:
   both Flower and Kim Health had no `iconAtlasId`, so the runtime intentionally
   fell back to the dialogue atlas. Stage 5.43 lets the user set that property
   where artwork is edited. Existing projects aren't silently guessed/rewritten.

3. **Game Objects tree remains selected when editing a managed sprite.** The
   editor now ignores scene-selection change events during `rebuildScene`, and
   explicitly reselects the Game Objects alias when object edits are committed.
   The Sprites alias is still available separately.

4. **HUD palette indices are never remapped.** Both 8-bit tile indices and icon
   indices copy from the PPB unchanged into generated `gamehud.c`. The palette
   selector changes only the preview colour table and text-colour swatches; it
   does not match RGB colours or rewrite PPB palette entries. At runtime the
   HUD uses the active foreground CLUT configured by the world.

## Finding from the uploaded Platformer3Testing project

`world1.sbgm` contains an inventory item named `Kim Health`, pickup kind 2,
icon cell 74, with no `iconAtlasId`. The placed `kim` collectibles use
`graphics/kim.ppb`, but the dialogue's selected tile atlas uses
`graphics/tilemap.ppb`. The previous generated fallback therefore drew the
wrong sheet after pickup or DROP.

## On your project

Open Adventure Editor > Inventory Items > double-click Icon artwork. Choose
`kim.ppb` from the new "Icon PPB atlas" drop-down, check the cell size and
pick the required artwork from that atlas. Do this for each inventory row that
needs a different PPB. Save, then run **Update Game Project** to regenerate
`gameadventure.c`, `gameassets.c` and `gamehud.c` from the updated saved data.
No PPBs need to be copied except your original graphics on the TFCard.

## Validation

- `development/tests/test_stage543_editor_contracts.py`: PASS (includes a
  native `cc -Wall -Wextra -Werror` test for custom inventory and dropped PPB,
  missing-PPB failure fallback, plus editor/HUD source checks).
- `development/tests/test_stage542_stamps_and_inventory.py`: PASS.
- `development/tests/test_stage536_integrated.py`: PASS.
- A full Qt6 compile and STM32 hardware acceptance are **not** verified here:
  this environment lacks Qt6 headers and a SIDBOX.
- Some old stage-specific tests hardcode old splash versions or use outdated
  C initializer layouts and therefore do not constitute current pass/fail tests.
