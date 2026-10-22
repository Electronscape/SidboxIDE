# Stage 5.28: FIRE2 opens inventory when there is no NPC or button-operated trigger

Based on **Stage 5.27**, dated 22 October 2026.

## Runtime behaviour

- **FIRE2 near NPC**: starts/advances NPC dialogue (unchanged).
- **FIRE2 near an active FIRE2 Trigger / Switch or Goto World door**: leaves the input to the normal world-object callback; no inventory popup. Only overlapping, enabled, button-operated triggers reserve FIRE2. Pure touch triggers do not.
- **FIRE2 anywhere else**: opens the inventory, with no UP modifier.
- **FIRE2 while inventory is open**: closes the inventory.
- **UP/DOWN**: scroll inventory/select dialogue choice as before.
- A held FIRE2 does **not** repeat the action or reopen inventory on arrival in another world.

## Integration

`gameadventure_setup()` now registers the optional world-specific, **read-only** FIRE2 trigger query. `game_adventure_start()` clears the query before the new world registers its own, but retains FIRE2 edge history so that a held door press cannot be mistaken for a fresh inventory-open press.

**Your hand-owned `main.c` requires no changes.** The existing `game_adventure_input()` integration remains valid.

## Installation

Apply the changed-files bundle to the **Stage 5.27 IDE source**, keeping folder structure. Rebuild the IDE, open the project, run **Update Game Project**, and rebuild the SIDBOX application. The generated game files must be refreshed because the shared Adventure, World Objects, and world-local wrappers changed.

## Testing

1. Away from all NPCs and doors, press FIRE2: inventory opens; press again: inventory closes.
2. Hold FIRE2: it should not repeatedly open/close.
3. Near an NPC, FIRE2 starts a conversation rather than inventory.
4. Near a configured FIRE2 Goto World door or switch, FIRE2 activates the door/switch and must **not** open inventory.
5. Keep FIRE2 held during a world transition: inventory should not open upon arrival.
6. Touch-only doors still activate on touch, independent of FIRE2.

Host GCC tests pass with `-Wall -Wextra -Werror`, including runtime inventory/NPC priority, no-action door overlap, held key across world changes, and Stage 5.25/5.27 dialogue behaviours. Qt6 IDE compilation and actual SIDBOX testing remain to be verified.

## Updated files

- `idelibs/codehelpers/game/adventureruntime.rulec` and `.ruleh`
- `idelibs/codehelpers/game/worldobjects.rulec` and `.ruleh`
- `idelibs/codehelpers/game/gameworlditems.rulec` and `.ruleh`
- `idelibs/codehelpers/game/gameadventure.rulec`
- `idelibs/codehelpers/game/adventureruntime.txt`
- `idelibs/codehelpers/game/maingame.rulec`
- `splashscreenwidget.cpp` (Build: 5.28.221026)
- `development/tests/test_stage528_fire2_fallback.c` and `.py`
