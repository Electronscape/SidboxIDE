# Stage 5.15 - Restore Adventure Inventory Icon Previews

Baseline: CoderGirl IDE Stage 5.14.

## Problem
The Adventure Editor stored each inventory item's icon `Cell ID` in the world Adventure JSON, but only created the table's `QIcon` when a user double-clicked and picked the cell. Reopening the editor showed the saved cell number without its image.

## Changes
- `gameadventureeditor.cpp`, function `editGameAdventure()`: rebuild visible Inventory Item icons from the saved per-item Cell IDs using the current Dialogue Box Atlas, tile size, and foreground palette.
- Rebuild previews immediately after the atlas controls are initialised.
- Refresh previews when the Dialogue Box Atlas or tile size changes and after choosing a new inventory icon.
- Missing atlases, invalid cell numbers and the 65535 no-icon sentinel clear only the *UI image*; the saved cell number stays untouched.
- No new project fields, no changes to game world files, no runtime changes.

## Installation
Replace only `gameadventureeditor.cpp` in the IDE source and rebuild the Qt6 IDE. Alternatively apply `CoderGirl-Stage515-Against-Stage514.patch` from the source root.

## Test
1. Open a world with an Adventure Inventory item, such as World 1's `Flower` icon (cell 517).
2. In Adventure Editor > Inventory Items, check its image appears beside the Cell ID.
3. Close the editor using OK, reopen, verify the icon is still visible.
4. Save the project, quit and restart the IDE, reopen the world and editor, verify again.
5. Change the Dialogue Box Atlas or tile size to confirm icons redraw. Returning to the original selection should restore the correct image.
6. Verify `No icon` stays blank. If an atlas is unavailable, the cell number should remain unchanged and its preview stay blank until the atlas is available.
7. Verify cross-world enemy + reward Paste still offers inventory registration and survives save/reopen.

Tests: Stage 5.15 source check, Stage 5.14 reward import check and Stage 5.10 project persistence check passed. Not compiled with Qt6 in this environment; no SIDBOX hardware verification performed.
