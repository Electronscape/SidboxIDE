# Stage 5.14: Linked Enemy Rewards -> Adventure Inventory on Cross-World Paste

**Base:** Stage 5.13 (confirmed on SIDBOX by user).

## What changed

When copying an Enemy or Breakable with a **linked Collectable** reward from one world into another world in the **same** game project:

- The clipboard now includes the source world's Adventure data at Copy time, even if its tab later closes.
- The paste checks the linked collectable's pickup type and destination Adventure Inventory **before modifying** any resources.
- If the destination already has an inventory row with that pickup type, the entry is reused and no popup appears.
- For custom pickup types (5..255), names are matched case-insensitively. If the source numeric ID is already occupied by a different type, a free ID is assigned and the pasted collectable's pickupKind is remapped. The destination custom-type definition is included.
- When the type does not yet have an inventory item, a **Yes / No / Cancel** question asks whether to register the reward. Yes creates a destination Adventure item (source name and capacity, start quantity 0); No copies the object and its reward without inventory registration; Cancel aborts the paste entirely.
- No question for a game object without a linked collectable reward, for same-world duplication, or if the matching item is already in destination inventory.
- The icon is intentionally **No icon** (65535), since Adventure icon indices refer to the *destination* world's Dialogue Box Tile Atlas, not the enemy's sprite PPB. Choose an icon later in Adventure Editor.
- Source and destination Adventure payloads belong to `.sbgm` world files; normal Save Design persists the new item. Ctrl+Z/Ctrl+Y includes Adventure metadata, imported resources, and splines as one action.
- The SIDBOX runtime, main.c, project stamping, and world code generator are unchanged.

## Why the original Forest test had no inventory reward

`world1.sbgm` defines custom pickup `MagicFlower` (ID 5) and Inventory Item `Flower` (capacity 1). The original `forest.sbgm` has **no** matching Adventure inventory row. The original test `main.c` already invokes `game_adventure_collect(item->kind)` in its `on_pickup` callback, so the runtime hook is present. It could not find a matching inventory entry in Forest.

## Test steps

1. Build the Qt6 IDE with these changed files on top of Stage 5.13.
2. In World 1, copy `baguy` (it is linked to `magicFlower[0]`); paste it into Forest. Choose **Yes** on the inventory popup.
3. Open Forest -> Adventure Editor -> Inventory Items: confirm **Flower** exists, with the appropriate custom pickup type and capacity.
4. Save Forest's design, Update/Regenerate the game, compile and run it on SIDBOX. Defeat the enemy and collect the flower; it should increment Adventure inventory.
5. Paste `baguy` again: no popup and no duplicate Flower inventory row.
6. Test **No** and **Cancel** in a fresh world, and test copying an ordinary no-reward game object (no popup).
7. Test Ctrl+Z/Ctrl+Y after the first paste, and Save/Reopen the world.
8. Optional: create a destination pickup type 5 with a *different* name first. The pasted MagicFlower should be remapped to an unused custom pickup ID rather than hijacking type 5.

**Existing pasted enemy:** The question is prompted on *new cross-world paste*, not retroactively. To test with Forest, delete the previously pasted enemy and reward (or use a new blank test world) before pasting again. Alternatively add the item manually in Adventure Editor.

## Validation

- Stage 5.14 source-contract test: PASS (linked-reward gating, type mapping, inventory check, Undo, persistence and original demo metadata).
- Stage 5.13 cross-world paste test: PASS.
- Stage 5.10 project stamp persistence, Stage 5.11 duplicate-helper cleanup, Stage 5.7 / 5.8 tile stamps, Stage 5.4i Adventure runtime source test, shared player source test: PASS.
- Qt6 compilation and real hardware GUI/runtime tests: **not performed in this environment**.

## Files changed

- `gamedesigner.cpp`: clipboard Adventure snapshot, on-paste linked reward metadata, optional inventory item + custom type, Undo integration.
- `gamedesigner.h`: shared clipboard Adventure and per-transaction Adventure Undo/Redo snapshots.
- `gamedesigner_project.cpp`: clear Adventure Undo/Redo state on project/world load.
- `development/tests/test_stage514_reward_inventory_paste.py`: regression assertions and demo fixture checks.
