# CoderGirl Stage 5.88: Logic Flow relationship audit

## Why

The design-time Logic Flow graph had not been updated with all of Stage 5.81–5.87's inventory/pickup semantics. It could show misleading edges even while the game itself behaved correctly.

## Changes (`gamefloweditor.cpp`)

1. **Collectible pickup output is determined by the saved `pickupShowInventory` flag.** When true, its node connects to matching Adventure inventory definition(s) by the same *world-local* pickup kind. The edge says `Adds to backpack (capacity checked)`. A missing definition gets a diagnostic node. When false, the pickup no longer falsely points to a backpack item.
2. **Direct stat pickups** show `Immediate stat pickup: +N (no backpack)` to a Player Stat node for Health, Lives, Score or `stat:<custom-name>`, including the backward-compatible default of Health for kind 2. The amount reads `gameObject.value`, matching the project's actual saved format. "Persistent collectible" is described as **placed-object persistence**, not backpack persistence.
3. **Shared backpack inventory across worlds** is represented with two labelled directional links between inventory items whose names match **exactly**. This follows the real `gameworlds` save/restore scheme (`strcmp` of item name). Same spelling with different case produces a diagnostic instead of a false share link. Item artwork is intentionally *not* synchronised.
4. Inventory cards now display **Can Drop**, **Can Discard**, and whether USE consumes the item. The existing USE effect-to-stat edges remain.
5. Enabled dialogue exchanges now include wrong-item repetition destinations **first, second, third, later**, plus the tracked item and any repeat-triggered object action. These are explicitly labelled conditional branches. Existing next, missing, wrong and partial branches remain.
6. Dialogue choice NPC appearance actions link to their **NPC nodes** by sprite ID, not to game-object nodes (NPC sprites may be decorations). A missing NPC sprite produces a diagnostic. Choice cards also describe `once` and `completeNpc` settings.

## Intentionally unchanged

- This is a **design-time view of SAVED `.sbgm` world definitions**, not a live runtime debugger. It cannot discover custom code callbacks, infer current player state, or evaluate runtime conditions.
- No game engine, code generation, asset files, player's `main.c`, saved worlds, or stored diagram layouts were changed.
- Stage 5.77–5.82 grouping, drag-out, reciprocal red/green wires, themes and click-to-front code remains unchanged.
- No automatic world synchronization or artwork copying was added.

## Tests performed

- Ran `development/tests/test_stage588_logic_flow.py`: **28 checks passed**, including the supplied Forest/World1 project, its different Flower icons and the real Future Kim wrong-offering dialogue branches.
- Verified only `gamefloweditor.cpp` and `splashscreenwidget.cpp` differ from Stage 5.87 among root-level executable sources.
- Qt6 headers/libraries are not installed in this environment, so the GUI has **not** been compiled here. Fedora Qt6 build and interactive flowchart check are required.

## Fedora test

1. Replace the two files at your IDE source root. Rebuild the IDE.
2. Save Forest and World1 and open Game Designer > Logic Flow > Reload Saved Worlds.
3. Check a Health collectible with **Show in Inventory OFF**: it should point to Health, not the backpack.
4. Check a collectible with **Show in Inventory ON**: it should point to its Adventure Inventory item.
5. Select Flower in either world: the Flow graph should show two separate red-to-green directional wires connecting the Flower inventory cards in Forest and World1. Different artwork stays independent.
6. Check Future Kim's `Can I get past?` choice: the wrong-item first/second/third/later results and NPC appearance action should be visible. Group/un-group and try dragging the array back out as before.

**Build:** `5.88.241026`.
