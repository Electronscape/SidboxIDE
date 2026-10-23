# CoderGirl Stage 5.41: Shared HUD palettes, collectible persistence, inventory artwork, array paste and viewport placement

**Build:** `5.41.231026` (23 October 2026). Based on Stage 5.40.

## Changes

1. **One HUD palette source governs the entire HUD.** The selected foreground palette (.pal, .act, or indexed .ppb) provides colour indices for text, decorative HUD tiles, and collectible icons. The generator uses each icon's **original PPB**, remapping its source colours to the selected 256-colour palette (exact RGB matches first; nearest available colour otherwise; index 0 remains transparent). It does not borrow tile pixels or their indices from the HUD background atlas. The editor preview and generator use the same remapping rule.
2. **Inventory item icon atlas choice.** In Advanced Platformer > Adventure Editor > Inventory Items, choose a row and pick an **Icon Atlas** and **Stamp Cell Size** above the list. The available resources include both tile atlases and sprite PPBs registered in the current world. Each item saves `iconAtlasId` and `iconTileSize`. The world generated Adventure setup binds the item's own PPB and renders its configured single-cell or 2x2 stamp. Unmodified items still use the dialogue atlas. **If the same icon should appear in another world, register the same PPB there and choose it for that world's matching inventory item.** A generated cross-world item with no destination icon assignment uses a safe placeholder until configured.
3. **Persistent collectables** checkbox under Game Object Properties > Collectable. It is opt-in and disables automatic respawn for that placed object. The generated world helper retains the collected state across unloading/re-entering a world, but doesn't treat initially hidden rewards as collected. World inventory quantities already move by matching **item name**; Stage 5.41 additionally generates definitions for persistent Show in Inventory item types in other *saved* worlds, so their quantities can be shown after travel. It appends these generated items without changing NPC/quest index assignments in existing designs. Persistent values live in RAM for the running game, not in a TFCard save file.
4. **Array-aware copy/paste names.** A placed object named `Fright[0]` pasted into the same world becomes `Fright[1]` (or the next free higher index); the next paste becomes `Fright[2]`. Non-array names retain their `_copy[n]` scheme.
5. **Resource import position.** Dragging/importing artwork from project files into Game Resources starts at the centre of the *visible World Designer viewport*, not the origin/camera top-left.

## Updating the project

- Install the changed source files over Stage 5.40 and rebuild the IDE.
- Mark intended collectibles **Persistent**, **Show in Inventory** (and **Show in HUD** if needed), then save their `.sbgm` world designs.
- Ensure corresponding inventory item **names** agree between worlds. Names, not world-local numeric indices, are the shared inventory keys.
- Select the appropriate PPB in each world's inventory item icon atlas picker; ensure that graphics file is loaded by that world and present on the TFCard.
- Run **Update Game Project for every world** so each world's generated Adventure data includes the shared inventory types. Accept updated generated helper versions with backups where prompted, then rebuild the game. The shared HUD source updates from the saved HUD design.
- Set the HUD palette source to the foreground CLUT actually active in the game. SIDBOX has one active foreground palette; picking a different CLUT in the HUD editor **does not** switch the hardware palette during rendering. If the selected bank lacks exact icon colours, the nearest available index is chosen.
- **`main.c`, authored game files, sprite resources and saved levels are not modified by this IDE source patch.** No new TFCard publishing warning or checklist was added.

## Checks and limitations

- Source-contract checks for all requested editor/runtime wiring pass, including C++ string literal validation.
- A strict GCC test of a mocked two-world pickup/inventory/HUD transition passes; existing Stage 5.37 pickup, Stage 5.34 NPC, Stage 5.34.2 FIRE1, Stage 5.38 HUD and Stage 5.36 shared-player tests pass.
- The earlier Stage 5.4i world-style test fixture hard-codes an older renderer rule and stops on the newly introduced template placeholders; it has not been updated in this stage.
- **Full Qt6 compilation and real SIDBOX acceptance testing have not been completed in this environment.**
- This is a RAM-only world-travel persistence feature, not power-cycle persistence. Destination-world copies of inventory definitions receive placeholders unless a local icon atlas is set. Persistent items must be saved in `.sbgm` files before other worlds are regenerated.
