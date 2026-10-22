# GamerGirl Stage 5.4f — NPC Item Picker & Hidden Backpack Entries

Based on **Stage 5.4e**, the working Player Editor Qt compiler hotfix. This is a focused V1 GamerGirl change. V2 GUI Designer and user-owned `main.c` remain untouched.

## What was added

1. **Create / Edit Player → Inventory → Add Item for NPC...** discovers saved `.sbgm` files throughout the project and offers the names of items genuinely required by reachable NPC dialogue choices (`Requires this item`). The selection shows the world and NPC names to explain where an item is used. Select an item to add it with a starting quantity of zero, then change the quantity as desired. Existing matching rows are selected rather than duplicated. It does not alter the NPC's Adventure Editor definitions or make up items.
2. A new **Hide from inventory window** checkbox on each player inventory row. It is stored as the optional `hidden` boolean inside each existing `{name,initial}` entry of `players/player.sbpi`. Old `.sbpi` entries default to visible; quantities are unchanged.
3. **Generated `gameplayer.c/.h`** now exposes `gameplayer_inventory_visible(const char *name)` and the new display flag as optional metadata in the generated starting inventory array.
4. **Adventure runtime** accepts an optional item visibility callback. The inventory panel skips hidden entries in both drawing and scrolling. NPC `Requires`, `Give`, `Take`, pickups, and world-persistent quantities continue to use the FULL underlying inventory; hiding an entry is visual only.
5. **World manager** registers the shared player's visibility callback after a world is activated, only when a `.sbpi` exists and at least one world uses Adventure. A project without an `.sbpi` or without Adventure keeps the old all-visible behaviour.

## Files changed

- `gamedesigner.cpp` (Qt Player Editor)
- `gamenpcitemindex.h` (new Qt design-time NPC item index)
- `gameplayerprofile.h` (optional `.sbpi` hidden field generation)
- `gameworldsnapshot.h` (conditional callback integration)
- `idelibs/codehelpers/game/gameplayer.rulec`, `gameplayer.ruleh`
- `idelibs/codehelpers/game/adventureruntime.rulec`, `adventureruntime.ruleh`
- `idelibs/codehelpers/game/gameworlds.rulec`
- `development/tests/test_stage54f_inventory_visibility.c`, `.py`, `test_stage54f_world_player_integration.py` (new)
- Updated older test fixtures to support the new optional fields/conditional.

## Test in your game

1. Install the changed files, rebuild the IDE.
2. Save any edited Adventure/NPC conversations in all your `.sbgm` worlds first (the picker scans saved files only).
3. Open **Create / Edit Player → Inventory → Add Item for NPC...**. Choose an item requested by an NPC in either `world1` or `forest`, and set its starting quantity.
4. Tick **Hide from inventory window** on a quest/secret item, leave another visible, and **Save** the player.
5. Run **Update Game Project** / F5 to regenerate **all** published worlds and the shared `gameplayer.c` plus `gameworlds.c`.
6. On SIDBOX, open the inventory panel (FIRE2+UP away from an NPC). Hidden items should be absent, without blank lines; visible items should scroll normally. Test an NPC's requirement for a hidden item: it should still work normally.

The original Player Start preview, animations, hitbox, physics, stats, springs and runtime world-switching APIs are unchanged. This stage does NOT automatically add an item definition to NPC Adventure Editor lists—an NPC must already have a `Requires this item` selection. Exact item spelling should match between Adventure and the shared player list.

## Verification

Host GCC strict `-Wall -Wextra -Werror` simulations passed for: no custom stats/items, populated shared player, visibility predicate, Adventure inventory drawing and scrolling, unchanged inventory amounts, and two-world manager callback registration. Stage 5.2 runtime and Stage 5.4d shared-player checks pass. Source checks cover the Qt editor integration and cross-world NPC scan; **Qt6 IDE compilation and SIDBOX hardware execution still require your real-system acceptance test.**
