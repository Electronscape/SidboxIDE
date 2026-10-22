# CoderGirl Stage 5.5: Project-global slope and loop stamps

Source-only update, 22 October 2026. No IDE executable is rebuilt in this package.

## What changed

- The project's one `.proj` JSON file owns `gameCollisionStamps` and `gameLoopStamps`. Definitions are shared by every `.sbgm` world in the project.
- Each `.sbgm` saves just collision placements (with project-global `stamp` index), and loop placements (`stamp`, `centerX`, `centerY`). Ordinary multi-tile **graphic** stamps remain per-world (not part of this request).
- The tilemap editor shows the entire shared collision bank and a global reusable loop bank. `New Stamp + Place` defines one loop; `Place Stamp` reuses a loop definition at a new centre. Changing loop parameters changes its shared definition.
- The collision-stamp Remove Definition button is disabled to prevent accidental index shifts between levels. Removing a placed stamp from a map is still supported.
- Each embedded world's generated map C refers to shared `gamehelpers/gameglobalstamps.c` arrays; world C retains only placements. The common C is compiled once with the project. The runtime resolves loop physics from the shared definition and that world's centre. Existing `game_tile_loop_t` runtime callers continue working.
- Legacy `.sbgm` files with per-world collision and loop definitions open as before. On saving each world, definitions are merged into `.proj` and its placement indices are converted. The old file is NOT rewritten just by opening it.
- The existing binary TFCard `.map` v4 format retains its compact local point-slope data for compatibility with existing loader/firmware. Embedded-world C uses project-global shape data. Both compiled modes use the global loop stamp bank.
- At most 128 collision definitions and 128 loop definitions per project; at most 32 loop placements per world. Shared stamp indexes remain stable while definitions are edited.

## Source files changed

- `gameglobalstamps.h` (new): project bank, legacy migration, compact per-world references
- `gamedesigner_project.cpp`, `gamedesigner.h`: load/save and stale-tab conflict protection
- `gamedesigner.cpp`, `gamedesigner_update.cpp`: helper compatibility check, export and backup set
- `gametilemap.cpp`, `gametilemap.h`: editor, project-stamp IDs, generated C/headers
- `mainwindow.cpp`: preserve global bank fields when saving `.proj`
- `idelibs/codehelpers/game/tilemap.c`, `tilemap.h`: global loop definition lookup at runtime
- `idelibs/codehelpers/game/worldmap.rulec`, `worldmap.ruleh`: shared definitions + per-world references
- `development/tests/test_stage55_global_stamp_runtime.c` (new)

## Before trying with your existing platformer

1. **Back up the entire platformer project**, especially `platform3.proj`, `forest.sbgm`, `world1.sbgm`, `gamehelpers/`, and `gamelevels/`.
2. Rebuild the **IDE source**. The pre-existing `SidboxIDE` binary, if one is left in another directory, is NOT updated by copying source files.
3. Open one old world and save it. Its legacy definitions are moved into the project bank. Close that design tab, then open/save the next world; this lets legacy local stamp IDs be remapped correctly.
4. Run **Update Game Project** for the current world, approving the backed-up refresh of the `gametilemap.c/.h` SDK helpers. Published worlds will then be available to the existing build flow. A project-wide build/F5 should use the root `gamehelpers/gameglobalstamps.c` exactly once.
5. Do a compile and SIDBOX hardware test. Changing a definition affects every world using it, so edits to dimensions/radii need checking against placements in the other worlds.

**Important:** Do not keep two worlds with unsaved edits to the shared bank open at once. Saving an older tab after another world changed the bank is deliberately blocked; close and reopen it instead.

## Tests performed here

- Host GCC (`-std=c11 -Wall -Wextra -Werror`) original Stage 3.80 loop momentum regression: PASS.
- Host GCC new two-world, one-global-loop-stamp runtime test: PASS.
- Stage 5.1, 5.2d, 5.3/5.4, 5.4f and 5.4i source regressions: PASS.
- Stage 4.06 point slope / v4 export source regression: PASS.
- **Not tested:** compiling/running the Qt6 IDE, compiling the complete STM32 game, or actual SIDBOX hardware. Qt6 development libraries aren't installed in this environment.
