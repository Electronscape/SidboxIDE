# GamerGirl Stage 5.2 — Multi-World Runtime Foundations

Based on Stage 5.1. Install the changed files into your CoderGirl IDE source tree, retaining the folder layout; rebuild the Qt IDE and back up your test game before export.

## What is implemented

- One rule-generated `gamehelpers/gameworlds.c/.h` controller for all currently published `worlds/<name>/` modules, even when there is only one world.
- `gameworlds_start(name)` selects a world, initializes that world's assets/map/atlas, adventure and objects, and unloads the previous world.
- `gameworlds_request(name)` queues a transition for a safe frame boundary; `gameworlds_apply_pending()` executes it.
- Wrappers for the active world's update, draw, draw-behind, before/after physics, pickups and background helpers. Missing optional features are null-dispatched.
- Optional player save/restore callbacks with a persistent game-owned state (`gameworlds_player_state_t`); the FIRST start does not restore an uninitialized player. Hooks must rebind the player sprite, tilemap and intended spawn in the new world.
- Adventure inventory quantities carried between worlds by item name (up to 64 distinct entries, not saved to TFCard). World-local dialogue progress and collectables do not automatically persist across reloads.
- Visible public world API headers and SDK templates `gameworlds.rulec`, `gameworlds.ruleh`, `gameworlds.ruletxt`.
- No V2 GUI Designer changes and NO modification to hand-owned `main.c`.

## VERY IMPORTANT — Migration is deliberate

Your EXISTING main.c retains the legacy single-world path and should continue to run untouched. To ACTUALLY switch worlds at runtime, follow the generated `gamehelpers/gameworlds-guide.txt`. You MUST migrate your game-owned player loop to call the controller; merely compiling Stage 5.2 will not teleport the player or change the current world.

Once your main.c uses the world-manager API exclusively (no remaining root gameassets/gameworlditems/gameadventure/splinepaths symbol dependencies), add the exact opt-in marker in a comment:

    /* GAMERGIRL_WORLD_MANAGER_MAIN */

Then the build excludes those four legacy generated `.c` files so the new controller and its per-world modules own the runtime. DO NOT put this marker into a still-legacy main.c or it may fail to link. This stage does not add a "Change World" control to the GUI trigger properties, nor a spawn-point editor; call `gameworlds_request("forest")` from game code for now. Do not request an immediate transition inside collision/draw callbacks.

For the first test regenerate BOTH `world1.sbgm` and `forest.sbgm` in the new IDE so both public APIs have their Stage 5.2 inventory and optional callback declarations. Mapless scenery-only worlds are supported.

## Test order

1. Rebuild IDE with changed files. Open `world1.sbgm`, Update Game Project; repeat with `forest.sbgm`. Confirm `gamehelpers/gameworlds.c/.h` and the guide exist.
2. WITHOUT editing main.c, compile the existing app once as a regression test.
3. Read the guide. In the test project's user-owned main.c, migrate startup and update/drawing/collision dispatch to `gameworlds_*` and rebind your player to the active world's sprite and map in the restore hook. Compile again; fix any missing player sprite in forest before trying a gameplay switch.
4. Queue `gameworlds_request("forest")`, then call `gameworlds_apply_pending()` at a safe frame boundary; try returning to `world1`. Check player health/inventory and no stale sprite pointers.
5. If a map is external, the .map must be at the TFCard path specified by the generated world. For this stage world-map paths remain compatible with `gamelevels/<name>.map` (the generated copy is also in `worlds/<name>/gamelevels/`).

### RAM / V1 applet warning

Only runtime-allocated assets and loaded maps are unloaded; STATIC C data and code from all worlds remain linked into a single V1 applet. This can approach the project's fixed 200 KB applet RAM ceiling even when only one world is active. Your previous log reported 186 KB / 200 KB. Monitor linker RAM figures and embedded pixel arrays closely; do not assume the 8 MB SDRAM makes the V1 code/data allowance unlimited.

## Validation performed here

- Host GCC C11 simulator: world1 with map, mapless forest, inventory handoff, deferred switches, missing-world rejection and failed world activation — PASS.
- Host GCC C11 simulator: world1 with physics/pickups and forest without; optional wrappers dispatch correctly; initial startup does not restore zeroed player state — PASS.
- Full Qt build / arm-none-eabi toolchain / SIDBOX hardware NOT available in this environment. These require your real build test.

## Changed files

- `gameworldsnapshot.h`
- `gamedesigner_export.cpp`
- `gamedesigner_update.cpp`
- `mainwindow.cpp`
- `idelibs/codehelpers/game/gameadventure.rulec`
- `idelibs/codehelpers/game/gameadventure.ruleh`
- `idelibs/codehelpers/game/gameadventureempty.rulec`
- `idelibs/codehelpers/game/gameadventureempty.ruleh`
- `idelibs/codehelpers/game/gameworlds.rulec` (new)
- `idelibs/codehelpers/game/gameworlds.ruleh` (new)
- `idelibs/codehelpers/game/gameworlds.ruletxt` (new)
- `development/tests/stage52_world_manager_test.py` (new)
- `development/tests/stage52_world_features_test.py` (new)

Keep the 2048 KB editor highlighter threshold unchanged. This stage preserves the V1 rules-driven generator and uses TFCard terminology.
