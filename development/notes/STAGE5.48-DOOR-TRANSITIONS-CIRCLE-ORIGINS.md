# Stage 5.48.231026: Door-selected transitions and circle origins

## Corrected runtime behaviour

**The Goto World doorway's selected destination Player Start controls both transitions.**

- `Transition OUT` plays over the currently active world **before** the safe load.
- `Transition IN` plays in the destination world **after** loading, at the selected start.
- The original game's launch uses the initial world's **default** Player Start `Transition IN`.
- The outgoing effect no longer depends on the start used to enter the current world previously. This fixes inconsistent return trips and repeated crossings.
- Both effects still use the destination start's duration. All modes default to `None` in older project files.

## New circle-centre option

Double-click **Game Resources → Player Starts → Default start**, or a named Player Start.

`Circle centre` choices:

- **Screen centre** (default): original Stage 5.46 behaviour.
- **Door / Player Start**: Circle Close closes around the *departing Goto World object's centre* and Circle Open opens around the *destination Player Start's world position*. Both positions are projected through the current camera offset and clamped to the screen. The enclosing circle radius accounts for off-centre origin so corners remain covered.

The `Circle centre` setting is saved as `circleOrigin` in `.sbgm`; old projects load as `center`. No extra PPBs or palette remapping.

## Files changed

- `gamedesigner.h`, `gamedesigner.cpp`, `gamedesigner_project.cpp`: Player Start circle setting in both dialogs and JSON.
- `gameworldsnapshot.h`: exports the new per-start data and default settings.
- `gamedesigner_export.cpp`, `idelibs/codehelpers/game/gameworlditems.rulec`: Goto World trigger now passes its doorway centre.
- `idelibs/codehelpers/game/gameworlds.rulec`, `.ruleh`, `.ruletxt`: selected destination OUT/IN resolution, new optional origin and camera API, screen masking calculations.
- `idelibs/codehelpers/game/maingame.rulec`: provides camera position every rendered frame.
- `splashscreenwidget.cpp`: `Build: 5.48.231026`.
- `development/tests/test_stage548_transitions.py`: compiled native regression.

## Updating existing games

1. Apply Stage 5.48 drop-in over **Stage 5.47** and rebuild the IDE.
2. In each `.sbgm` world, open the Player Starts and save the desired IN, OUT, and Circle centre settings.
3. **Update Game Project on every world** so the registry and generated trigger functions agree.
4. Rebuild the game. Test entering from each door, returning, and entering again.

### If `main.c` is user-owned

The IDE does not overwrite user-owned `main.c`. The regenerated `maingame.c.txt` shows one new call **just before** `gameworlds_transition_frame(VIEW_W, VIEW_H);`:

```c
gameworlds_transition_camera(camera_x, camera_y);
gameworlds_transition_frame(VIEW_W, VIEW_H);
```

Your previous Stage 5.46 integration still works without the new call, but location-centred circles remain screen-centred until camera coordinates are supplied.

### If hand-writing transition requests

`gameworlds_request_at(name, start_id)` still works. When location circles are chosen, Circle Close falls back to the last active Player Start's position. To give it an actual exit position in world pixels:

```c
gameworlds_request_at_from(name, start_id, exit_world_x, exit_world_y);
```

## Testing status

Compiled native C tests pass for target-selected transitions, 2× crossings, fade versus mask mode, named start positions, circle-centred exit door, camera-offset circle entry, memory-free safe world switches. Stage 5.42 stamps, Stage 5.45 portable inventory, Stage 5.46 compatibility, and Stage 5.47 HUD artwork checks pass. Full Qt6 GUI compilation and real SIDBOX hardware transitions are **not verified** in this environment.
