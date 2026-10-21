# GamerGirl — Stages 5.2e + 5.3 + 5.4 (combined)

**Based on the Stage 5.2d World-Manager-Only source.** These edits touch V1 game IDE/exporter code only; the V2 GUI Designer is unchanged. Keep your working IDE and project backups.

## What is new

- **Stage 5.2e:** Game Designer's **Update Game Project** button updates **all** saved project `.sbgm` worlds, using the same batch world-generation implementation as F5. Update All Worlds asks for confirmation. F5 checks the published world builds and regenerates stale worlds, following existing prompt/auto-update settings. The user's hand-owned `main.c` is never regenerated.
- **Stage 5.3:** **Create / Edit Player...** replaces the old Player Animations button. New project-level `players/player.sbpi` (JSON v1) holds one shared player's PPB atlas reference, animation `.sbanim` reference, atlas cell size, optional hitbox override, starting physics preset, starting health/lives/score, and inventory definitions. We reuse the existing animation editor rather than discarding `.sbanim` files. Rules `gameplayer.rulec/.ruleh` render `gamehelpers/gameplayer.c/.h`. Its atlas pixels are owned by the GAME and survive world unloads.
- **Stage 5.4:** Each `.sbgm` saves **Player Start**: shared profile reference, entry label, world X/Y and facing. The map/design canvas has a draggable yellow Player Start marker; double-click Player Start in Game Resources to edit X/Y and facing. Runtime `gameworlds_player_start()` obtains the active world's default spawn; generated `maingame.c.txt` binds shared player graphics to that position and map.

## First use in the test project

1. Install replacement files **with their directory paths intact**. Rebuild the Qt6 IDE.
2. Open your project and `world1.sbgm`. Choose **Create / Edit Player...**. The editor attempts to migrate your existing named `player` sprite's PPB path, cell size and `.sbanim` reference. Confirm these fields and save `players/player.sbpi`. The PPB must exist **inside the project**. It is referenced, **not copied** by the editor.
3. Open each world's Game Designer. Drag its yellow **Player Start** marker or double-click **Player Start** in Game Resources; choose the world X/Y and initial facing. Save each `.sbgm`. For world1, if you want the old player position, use its existing sprite X/Y (automatic migration is attempted when creating the profile).
4. Click **Update Game Project** once: all project `.sbgm` designs should regenerate. Confirm the shared `gamehelpers/gameplayer.c/.h`, the multi-world registry and each `worlds/<name>/` set.
5. Check `maingame.c.txt` for the new shared player `gameplayer_init()`/`gameworlds_start()` sequence and its `gameworlds_player_start()` use.
6. F5: it should NOT ask which world to compile. Regeneration occurs as needed for all worlds. Check that your previously working V1 APP still compiles and runs.

## Your `main.c` is protected

GamerGirl **never overwrites user-owned main.c**. Your Stage 5.2b custom `main.c` will continue to run its world-specific player until YOU deliberately migrate it to use `gameplayer_sprite`, `gameplayer_init`, `gameworlds_player_start` and the shared cleanup. The generated `maingame.c.txt` provides a concrete example. Retain your physics, sprites and springs until that works on hardware. There is **no automatic rewriting** of `main.c` or user-owned animation `.sbanim` files.

## Animation, inventory and transitions

- The `.sbpi` **references** an existing `.sbanim`, and the player editor opens the existing animation editor through the original player Sprite. The `.sbanim` is not itself copied or reformatted. Generated startup includes the existing animation header if available and explicitly enabled in the starter.
- `.sbpi` inventory counts are **initial quantities only**. They are seeded into the project-owned world manager **before** the first world activates, so transitions do not reinitialise them. Health/lives/score initial defaults are provided to the game-owned state; hand-written gameplay must integrate updating them.
- `gameworlds_player_start()` currently gets the default spawn per world. **Named additional door destinations and automatic runtime physics rebinding during transitions are not part of this release.** They belong to the subsequent world-transition stage.
- A mapless world can have Player Start metadata but cannot initialise tilemap player physics until it has a playable map (or the game provides a separate non-tilemap mode).
- PPB assets and external `.map` files must also be present at the expected paths on the SIDBOX **TFCard**.

## Test status

Host GCC tests: `development/tests/test_stage536_shared_player.py`, `stage52_world_manager_test.py`, `stage52_world_features_test.py` and `test_stage52d_world_manager_only.py`. Source contract test: `test_stage536_integrated.py`. Passed locally. **Full Qt6 IDE build and real STM32/ARM compile are NOT verified here** (Qt6 development libraries are unavailable). User hardware acceptance is required before considering these changes stable.

**Excluded intentionally:** V2 GUI Designer modifications, automatic door-to-world actions, automatic conversion of user-owned main.c, deletion of legacy archived output files or per-world player resources.
