# CoderGirl Stage 5.71.241026: Adventure NPC visibility & dialogue actions

## Purpose

Allow a world to remove an Adventure NPC after a dialogue, show an initially hidden replacement, and remember the change when the player leaves/re-enters that world. The design uses **placed Sprite resources tagged as Adventure NPCs**; it does not change PPB palettes, the audio mixer, or handwritten `main.c`.

## Editor

### Adventure Editor → NPCs

- New **Initially visible** checkbox for each NPC. Checked by default on old saved projects (including NPCs with no new JSON property).
- Untick for an NPC that should appear only after a quest or dialogue. It is hidden *and cannot be talked to*.
- In **World Editor**, keep placing the two sprites as usual; add them to the Adventure NPC table if both should be conversational.
- NPCs are still identified by their existing placed Sprite ID; adding duplicate NPC rows for the same sprite is prevented in the new-NPC picker. Removing an NPC clears any linked dialogue appearance effects for that sprite; the placed Sprite and its dialogue nodes remain.

### Adventure Editor → Dialogues & Choices → Edit a node

Every choice now has **NPC action 1** and **NPC action 2**, each comprising:

1. NPC target selector (by placed sprite ID, rendered as the sprite name).
2. Action: **Hide NPC**, **Show NPC** or **Toggle NPC**.

Both can run on one successful dialogue choice. They work alongside the existing Game Object **Event / resource** and **Game Object action**, inventory item rewards, and `Mark this NPC as helped`. Changes execute only on *successful* choices, not missing-item/wrong-item responses. No per-frame polling.

## Big Steve example

**Option A: BigSteveNiceSuit is a Game Object**, e.g., a non-conversational visual:

- Give the original `BigSteve` a goodbye dialogue and select its final choice in the dialog editor.
- For that choice: **NPC action 1 → BigSteve → Hide NPC**.
- Also select **Event / resource → Game Object: BigSteveNiceSuit**, **Game Object action → Activate**. Arrange the Game Object to start inactive via its ordinary Game Object settings. This gives you both changes from one choice without needing a second Adventure NPC.

**Option B: BigSteveNiceSuit is another conversational NPC**:

- Add the placed suit sprite to the Adventure **NPCs** table, choose its first dialogue and **untick Initially visible**.
- Set **NPC action 1 → BigSteve → Hide NPC** and **NPC action 2 → BigSteveNiceSuit → Show NPC** on the original Big Steve goodbye choice. Both happen together.
- You can animate or supply separate dialogue for the suit NPC.

NPC effects are *world-local*: a dialogue can change NPCs defined in its own Adventure world. An action in another world needs to run when that world's adventure is active or be routed by custom game logic.

## Runtime details

- Separate 256-byte visibility state array (maximum 256 NPCs, 1 byte each); only NPCs in the current world are checked. Its default values are configured by the generated `npc_initial_visibility[]` table, so the original six-field `game_adventure_npc_t` ABI remains unchanged.
- Invisible NPCs are excluded from `game_adventure_draw_npcs()`, proximity/FIRE2 conversation detection and the animation tick loop.
- Two NPC appearance changes are stored in a small table **only for choices which configure them** (one `choice_id` plus two NPC indices and action modes). The small table is searched on a successful dialogue choice only, not on each frame.
- `gameadventure_save_progress()` and `gameadventure_restore_progress()` now snapshot/restore visibility alongside the existing completed-dialogue, inventory exchange, wrong-item attempt and dropped-item progress. This persists over world transitions **within the current game session** but is **not yet included in an on-TFCard save-game file**.
- `game_adventure_npc_action(index, GAME_ADVENTURE_NPC_HIDE/SHOW/TOGGLE)`, `game_adventure_set_npc_visible()` and `game_adventure_npc_visible()` are also exposed for custom user code. Do not hardcode numeric NPC indices in gameplay if you routinely reorder the NPC table; the designer's sprite ID lookup is safer.
- Existing custom dialogue event IDs and Game Object event IDs are unchanged. No new event-ID ranges or signed 16-bit event pitfalls.

## Installation & acceptance

1. Back up your project, then apply the **Stage 5.71 drop-in over Stage 5.70.1** at the IDE source root.
2. Rebuild the Qt6 CoderGirl IDE.
3. Add the two placed sprites / NPC rows as needed and configure their starting visibility and goodbye choice actions.
4. Save the design, use **Update Game Project** to regenerate `gamehelpers/gameadventure.c/.h` and the shared `gameadventureruntime.c/.h`, then rebuild your SIDBOX game.
5. Test: forest BigSteve visible; suit version initially hidden; goodbye causes hide/show as configured; return to forest and confirm the original remains hidden; check the replacement can be spoken to if configured as an Adventure NPC.

This patch does not overwrite your handwritten `main.c`. If a custom game loop *also* draws the NPC's placed sprite through an independent `gfx_drawbob()` call, remove that duplicate drawing; the Adventure renderer can hide only sprites it owns.

## Verification

**Passed with GCC host stubs:** `development/tests/test_stage571_npc_visibility.py` and C companion, covering hidden draw/talk blocking, double-action switch, independent custom event, world save/restore and toggle. Existing Stage 5.69 wrong-item tests, Stage 5.70.1 high event-ID regression and Stage 5.70 dialogue folder-tree wiring tests also pass.

**Not tested:** a full Qt6 GUI build (Qt6 development headers absent in this environment) and physical SIDBOX hardware acceptance. The patched generated-runtime C compiles and runs under the test harness, but the GUI still needs the user's Fedora build.

Splash screen: **Build: 5.71.241026**.
