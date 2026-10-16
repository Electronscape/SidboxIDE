# CoderGirl Stage 3.3 — Shared PPB memory + swept moving-platform landings

This is based on the hardware-verified Stage 3.2 IDE. Both changes are V1 game-side code; no firmware changes.

## What changed

1. **No duplicated tile/sprite atlas pixels when they use the same PPB.**
   The Game Designer now generates a read-only `gameassets_find_ppb()` lookup.
   `game_level1_load_atlas()` first asks whether **that exact SD resource path**
   has already been loaded by `gameassets_init()`.

   - If found, it checks the PPB dimensions and pixel checksum and BORROWS the
     existing pixel buffer. No new allocation, no second SD read.
   - If there is no matching asset, the tilemap continues loading its own PPB
     from the SD card, as in Stage 3.2.
   - If a match exists but the contents are stale or incorrect, the load fails
     rather than hiding an asset-version error.
   - The tilemap uses an explicit `atlas_borrowed` flag so unloading a borrowed
     atlas NEVER frees the sprite buffer.
   - Old projects lacking the new lookup function still use the independent
     tilemap SD load. Standalone level export remains possible.

2. **Swept landings on moving platforms.** `game_world_objects_before()` captures
   the player's pre-physics WORLD position, while `game_world_objects_after()`
   looks at the previous and current feet and platform-top positions. A rising
   lift can now catch a falling player even if they pass through the same Y
   position between frames. Horizontal overlap is checked at that instant.
   Landing from underneath is still disallowed (one-way platform top).
   The normal lift carry, conveyor, spring, spline and tile physics remain intact.

## Installing to the IDE

Back up/commit your Stage 3.2 project. Extract the **IDE drop-ins** at the
CODERGIRL IDE source root, keeping their directory structure. Recompile Qt.
Alternatively use the complete Stage 3.3 IDE archive.

## Updating existing V1 games such as Platform2

1. Back up your game. Replace the following files from the **V1 game drop-ins**:

   - `gamehelpers/gametilemap.c`
   - `gamehelpers/gametilemap.h`
   - `gamehelpers/gametilemap.txt`
   - `gamehelpers/gameworldobjects.c`
   - `gamehelpers/gameworldobjects.h`
   - `gamehelpers/gameworldobjects.txt`

   These are SDK helper changes. If you customised either helper, merge changes
   rather than overwriting your edits.

2. In the newly rebuilt CoderGirl, re-export the attached tilemap, and run
   **Generate V1 Game Code**. This regenerates BOTH `gamelevels/level1.c/.h`
   and `gameassets/gameassets.c/.h`, linking the shared-atlas lookup.
   Your handwritten `main.c` will NOT be overwritten.

3. Keep the startup ordering:

   ```c
   initMalloc();
   /* Your working display and graphics initialisation ... */
   if (!gameassets_init()) return 1;
   if (!game_level1_load_atlas()) return 5;
   if (!gameworlditems_init()) return 2;
   ```

   If you use the generated world objects, continue calling:

   ```c
   gameworlditems_update(1);
   gameworlditems_before(&world_player);
   game_tile_player_run(&player_physics, getjoyport(), 1);
   gameworlditems_after(&world_player);
   ```

4. When exiting/unloading the scene, use the **reverse** ownership order:

   ```c
   game_level1_unload_atlas(); /* release borrowed pointer or dedicated RAM */
   gameassets_shutdown();     /* owns and frees sprite PPB pixels */
   ```

   Never call `gameassets_shutdown()` or reinitialise gameassets while a
   tilemap is still borrowing its pixel buffer. Do not unload each frame.

5. Rebuild the V1 game and test on SIDBOX. Try jumping down onto a rising lift
   multiple times, standing on a descending lift, springs/conveyors, scrolling,
   and the atlas-sharing scenario using the same `graphics/wall.ppb`.

## Test status

- GCC strict C compilation against the actual V1 API passed.
- Host tests passed: static/moving surfaces, springs, existing ten-frame real
  tilemap physics carry, falling player vs rising lift, and false collisions
  from below, while rising, and from sideways.
- Host memory tests passed: same pointer when shared, rejected wrong hash and
  dimensions, borrowed memory never freed by tilemap, and independent SD load.
- AddressSanitizer/UndefinedBehaviorSanitizer test cases passed.
- Qt6 is unavailable in the test environment, so desktop compilation is not
  verified here. Real SIDBOX hardware testing is still pending for Stage 3.3.

**Square corners remain untouched.** No game object editor UI was changed.
