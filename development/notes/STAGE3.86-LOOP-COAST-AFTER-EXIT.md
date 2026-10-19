# GamerGirl Stage 3.86 — Loop Track: Ignore Friction After Exit

## Baseline

IDE archive supplied 19 October 2026 at 10:25: `IDE 19-10-2026-1025.tar.gz`.
This stage starts from that exact source tree, not an older previous-stage archive.

## Feature

Tilemap Editor > Loop Tracks > select a loop:

- New checkbox: **Ignore friction after exit (until wall or movement)**.
- Off by default (all previous loop physics is preserved).
- After a player **completes one revolution**, the exiting horizontal force keeps its value rather than being decayed by the current physics preset's damping each tick.
- Works left or right; the original 32 px/frame loop speed cap remains.
- First Left/Right input cancels the override, immediately restoring normal friction; the existing carried momentum then decays normally. Jump alone doesn't cancel it.
- A solid tile collision cancels the override and stops the carried horizontal force as it already did.
- Losing contact with a loop before completing a lap **does not enable** indefinite coasting.
- Starting/entering another loop or resetting a player clears previous coast state.
- Does not modify the gravity, spring, slope or animation paths.

## Files changed

Production files:

- `gametilemap.h`: per-loop `coastAfterExit` setting.
- `gametilemap.cpp`: checkbox, change tracking, generated C loop initializer.
- `gametilemapmodel.cpp`: save/load `coastAfterExit` in `.sbgm` (backward-compatible default false).
- `idelibs/codehelpers/game/tilemap.h`: generated runtime loop setting and player's transient coast flag.
- `idelibs/codehelpers/game/tilemap.c`: apply friction immunity to the exiting impulse, stop on wall/input, clear on reset/re-entry.

Tests (native C tests updated for extra loop struct member and a new regression test):

- `development/tests/test_stage368_player_hitbox.c`
- `development/tests/test_stage372_loop_entry.c`
- `development/tests/test_stage380_loop_momentum.c`
- `development/tests/test_stage386_loop_friction_coast.c` (new)
- `development/tests/test_stage386_loop_coast_export.py` (new)

No old stage notes were moved. **All newly created notes are under `development/notes/`**.

## Installation / test on Fedora

1. Replace the changed source files in your Qt6 IDE checkout, preserving subdirectories (or use the full source archive).
2. Rebuild SIDBOX IDE in Qt Creator.
3. Open a `.sbgm`, select **Loop Tracks**, select a loop, tick **Ignore friction after exit** and save the map.
4. Press **F5 > Update and Compile** and confirm the backup/Update Project prompts. **This is essential** because the runtime helper `gamehelpers/gametilemap.c/.h` must be refreshed along with generated `level1.c`.
5. Run the game on SIDBOX. Build speed, complete a loop, coast without steering, then hit Left/Right or a wall to test that friction returns.
6. For comparison, untick the option and re-export: momentum should damp immediately like before.

## Verification performed here

- Native C test for continued momentum, Left/Right cancellation, wall cancellation, both travel directions, legacy loop behaviour, reset and re-entry: PASS.
- Stage 3.80 boost test: PASS.
- Stage 3.72 entry/exit test: PASS.
- Stage 3.68 hitbox test: PASS.
- Stage 3.86 static UI/JSON/codegen integration: PASS.
- Previous stage tests for build reminder, platform animation order, project splash, PNG importer: PASS.
- **Qt6 build unavailable in this environment:** test actual UI on Fedora before considering it hardware-confirmed.

Note: the override currently responds to tilemap solid collisions. Object-specific collisions resolved by other game helpers are not integrated into this toggle.
