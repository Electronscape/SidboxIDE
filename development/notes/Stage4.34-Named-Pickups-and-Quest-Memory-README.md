# GamerGirl Stage 4.34 — Named Pickup Types & NPC Quest Memory

## New features

### Named pickup types (5–255)
- **World Designer → placed sprite → Game Object Properties → Collectable.**
- Leave classics `1 Coin`, `2 Health`, `3 Key`, `4 Gem` unchanged, or press **+ New type...** for a project-wide custom ID 5–255 such as `5 Puzzle Piece`, `6 Flower`.
- **Rename / Remove...** manages names. IDs are stable: renaming does not change inventory mappings. Removal is refused while placed collectables or inventory items still refer to that ID. Changes are saved in `.sbgm` under `adventure.pickupTypes`.
- Pick the named ID on the placed collectible. In **Adventure Editor → Inventory Items**, add a row such as `Rare Flower`, set **Pick up from...** to that same named ID, choose capacity and optionally its atlas icon.
- **One-time collectable (never respawn)** is a clearer control for the old `Respawn frames = 0` behaviour. Uncheck to enable a delay (in 50Hz frames). The underlying collectables runtime and map file format are unchanged.
- Item inventory amounts are still limited to 64 different item definitions. Up to 255 is the **pickup kind number space**, not 255 allocated inventory slots.
- Hand-edited `main.c` still requires `game_adventure_collect(item->kind)` inside `on_pickup()`; the IDE does not overwrite it.

### Dialogue choices that remember success
- **Adventure Editor → Dialogues & Choices → Edit Node... → each Choice:**
  - Tick **Only show this answer until successfully used** to hide the choice after the player successfully selects it. An absent required item or failed take does **not** consume the flag.
  - Tick **Mark this NPC as helped** to set a per-NPC completed state on successful selection.
- **Adventure Editor → NPCs → After helped (optional):** choose the dialogue node to use on later conversations after that NPC is completed.
- State is stored in bounded static RAM and resets when `gameadventure_setup()` starts a new game/level. Persisting the quest state across resets or game saves is **not** implemented yet.
- One-time choice flags are per **dialogue node and choice slot** for the current session (shared if multiple NPCs use the same node). Completed status is tracked per NPC.

## Example: Guardian & flower

1. In Game Object Properties for a flower sprite, add `5 Rare Flower`. Set it as a Collectable and tick **One-time collectable**.
2. Adventure → Inventory Items: add `Rare Flower`, **Pick up from = 5 Rare Flower**, capacity 1, starting quantity 0.
3. Guardian's opening dialogue node: one choice `Give her the flower` with **Needs Rare Flower**, **Take Rare Flower**, and **Game Object: Door → Deactivate**.
4. Tick **Only show this answer until successfully used** and **Mark this NPC as helped** on that choice.
5. Create a second dialogue node, e.g. `Thank you! The way is open.`; in NPCs, choose this under **After helped** for Guardian.
6. Save and Update Game Project, rebuild the game and test on real hardware.

Now, first contact without a flower does not spend anything or unlock the door. After successfully handing it over, the flower leaves inventory, the door deactivates, and later conversations show the completed dialogue without asking for another flower.

## Installation

Update both IDE **and game runtime**. The IDE update includes the new template `idelibs/codehelpers/game/adventureruntime.c/.h`. Existing game helpers are protected, so separately extract the game helper ZIP into the game project before compiling. Game code from **Update Game Project** calls `game_adventure_story_flags()`; stale runtime helper versions cannot link that function.

The generated game uses arrays (`story_choice_flags[]`, `npc_completed_nodes[]`) rather than changing the ABI of the established `game_adventure_choice_t` / `game_adventure_npc_t` structures. This avoids disrupting user-authored table initializers.

## Verification

- Runtime compiled with GCC `-std=c11 -Wall -Wextra -Werror` and passed a Stage 4.34 test covering failure before possession, collecting kind 5, consuming the flower, firing the event only once and selecting the completed greeting on return.
- Existing 4.29, 4.30, 4.31 and 4.33 runtime checks and 4.27–4.33 focused source regressions passed.
- **Qt6 IDE compilation on Fedora and actual STM32 hardware remain to be tested by the user.** No firmware or music changes.
