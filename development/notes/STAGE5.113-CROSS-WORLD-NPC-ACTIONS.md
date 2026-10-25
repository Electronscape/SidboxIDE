# CoderGirl Stage 5.113 (25 October 2026): Cross-world NPC actions

## What's new

- **Trigger -> Ordered linked actions** now includes both local NPCs (`NPC: BigSteve [0]`) and those in other saved worlds (`Forest: NPC BigSteve [1]`). The same dropdown keeps Game Object and Player Spotlight targets.
- **Adventure Editor -> Dialogue Node** already supports two NPC appearance actions per choice and two actions when an answerless dialogue closes. Those pickers now also include NPCs in other saved worlds.
- **Hide / Show / Toggle** on NPCs affects both their sprite visibility and their ability to start their own conversation. Targets use **world + stable placed-sprite ID** rather than a fragile name or row index.
- Changes to an unloaded world are queued in tiny per-world static arrays and applied when its Adventure state is restored. No additional PPBs, worlds, or maps are loaded. The existing Game Object cross-world actions are unchanged.
- Cross-world NPC action connections are drawn to the appropriate NPC card in the Logic Flow Chart.

## How to dress Big Steve

1. In **Forest -> Adventure Editor -> NPCs**, set `BigSteve [0]` (original) to **Initially visible**, and `BigSteve [1]` (dressed) to **Initially hidden**. They may overlap spatially; each NPC retains a separate dialogue node.
2. **Save Forest** before setting references from another world.
3. In **World1 -> Game Object -> Trigger -> Ordered linked actions**, add:
   - `Forest: NPC BigSteve [0]` -> **Disable** (hide undressed NPC)
   - `Forest: NPC BigSteve [1]` -> **Enable** (show dressed NPC)
   These run when the Trigger succeeds (e.g., after the underwear exchange).
4. Alternatively, in **World1 -> Adventure Editor -> Dialogue Node**, choose these two targets under the player answer's **NPC action 1/2**, or the corresponding **When this dialogue closes** actions. **Message sequence remains text-only**, by design.
5. Save both worlds, click **Update Game Project**, rebuild, and test World1 -> Forest and Forest -> World1 -> Forest.

## Runtime / integration

The shared world manager adds `gameworlds_npc_action(world, npc_slot, action)` where action = 0 hide, 1 show, 2 toggle. Each generated world supplies `gameadventure_npc_action`, `gameadventure_npc_remote_action`, and `gameadventure_npc_remote_reset` callbacks. Cross-world NPC changes use the static world-specific story visibility snapshot without loading another world's assets. **No change to user-owned `main.c`.**

Target IDs in `.sbgm` use an editor-side, version-safe string `@npc:<world>:<sprite-uuid>`; the generator resolves and validates these on Update Project. Deleted NPCs or worlds produce a clear validation error rather than silently selecting the wrong character.

### Testing

- `development/tests/test_stage5113_npc_crossworld.py`: native GCC -Wall -Wextra -Werror test for remote hide/show/toggle, first visit, saved story, new-game reset; editor/generator/Flow Chart source checks.
- Stage 5.112 cross-world object, Stage 5.108 spotlight action and world toggle, Stage 5.111 cached feather animation, and Stage 5.97 dialogue sequence regressions passed.
- Qt6 IDE compilation and physical SIDBOX hardware validation remain to be done.

## Compatibility

Normal Game Object actions, player spotlight toggles, local NPC actions, prior stories, inventory, and hand-written `main.c` remain unchanged. The new features are opt-in. The per-world stage data uses static arrays; it does not create a TFCard save-game system.
