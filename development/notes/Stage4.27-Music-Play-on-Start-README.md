# GamerGirl Stage 4.27 — Start Music When Game Starts

Based on the Stage 4.26 full IDE archive. No firmware changes.

## Installation

Extract the changed-files archive over your existing Stage 4.26 IDE source tree, preserving paths; rebuild GamerGirl. Or replace these six production files in the IDE source root:

- `gamedesigner.h`
- `gamedesigner.cpp`
- `gamedesigner_project.cpp`
- `gamedesigner_export.cpp`
- `gamecodegen.h`
- `gamecodegen.cpp`

## Using it

1. In **Game Resources → Music**, select a track (including `.spc`).
2. In **Resource Properties**, tick **Play on game start**.
3. Save the design; choose **Update Game Project** to regenerate `gameassets/gameassets.c` and the starter program.
4. Make sure the music file is at the expected TFCard path, and that the chosen SIDBOX firmware supports that file type through `music_play()`.
5. Start the game. The selected track will be played by `gameassets_init()` after the resource setup completes successfully.

Only one Music resource may be flagged at a time. Selecting another clears the previous startup flag. Older `.sbgm` designs default to **off**. The choice lives in `.sbgm` per Music resource as `musicPlayOnStart`, with no changes to `.pal`, `.map` or music files.

## Behaviour and scope

- Generated `gameassets_init()` emits the standard `music_play(path, subsong)` call; the file-type detection is still performed by your private/normal SIDBOX music system.
- Existing Music trigger actions, `playmusicNAME()` helper functions, and `music_update()` remain unchanged.
- A hand-edited, protected `main.c` is never overwritten. Its existing call to `gameassets_init()` will start the chosen music after you regenerate the managed `gameassets.c`.
- The checkbox means **initial game startup / each explicit `gameassets_init()` call**. It does not automatically re-run on arbitrary level transitions unless your game reinitialises the assets; on later levels you can call the appropriate `playmusicNAME()` function.
- When no track is selected, nothing is auto-played.

## Validation

The Stage 4.20–4.27 focused Python checks passed, including the new startup-music regression test. A Fedora Qt6 build and an actual SIDBOX/TFCard music test have **not** been run in this environment.
