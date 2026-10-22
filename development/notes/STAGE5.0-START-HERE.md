# Stage 5.0 — World-Owned Generated Bundles (Foundation)

Based on the user's working Stage 4.55. V1-only. The GUI/V2 generator is unchanged.

## Why Stage 5.0 is a foundation, not runtime switching

Every `.sbgm` already stores its own world design, dialogue, splines, tilemap,
objects, triggers, collections and resource configuration. Stage 4.53 made the
**tilemap** name world-specific, but other compiled V1 outputs still have shared
filenames and API symbols (`gameassets`, `gameworlditems`, `gameadventure`,
`splinepaths`). Putting multiple copies of those into the normal C source tree
would create duplicate definitions and break the game.

This stage safely snapshots EACH world's entire generated build input into
`.codergirl/worlds/<world>/`, while preserving the existing canonical C/H paths
for the ONE selected active world. These snapshots are **not compiled** and
cannot yet be switched at runtime. A later stage will convert shared generated
APIs to distinct world-specific symbols and introduce a runtime manager.

## Expected per-project layout

    world1.sbgm
    forest.sbgm
    main.c                          (handwritten, protected)
    gamelevels/world1.c/.h[/map]    (already world-named)
    gamelevels/forest.c/.h[/map]    (when forest is exported)
    gameassets/gameassets.c/.h      (only current active world)
    gamehelpers/gameworlditems.c/.h (only current active world)
    gamehelpers/gameadventure.c/.h  (only current active world)
    gamehelpers/splinepaths.c/.h    (only current active world)
    .codergirl/active-world.json    (the exact active .sbgm)
    .codergirl/worlds/world1/       (world1's saved generated bundle)
    .codergirl/worlds/forest/       (forest's saved generated bundle)

Each bundle stores `world.json` with its originating `.sbgm`, generated files,
configuration, and generation timestamp. Updating a world stages its new bundle
first, preserves any old bundle until the replacement is ready, and publishes
it with a directory rename. No `.sbgm` or user-owned `main.c` is moved.

## Main improvements

- F5 knows which `.sbgm` actually generated the canonical shared C files;
  mtime checks alone cannot confuse one world's output with another's.
- F5 won't silently compile a different selected world when `main.c` includes
  only a different world header; it warns you before generating/building.
- `Compile Without Updating` is blocked if an explicit active-world marker
  proves that the canonical sources belong to another world.
- Editing/saving an INACTIVE world no longer auto-regenerates the ACTIVE
  world's shared `splinepaths.c/.h`.
- Worlds with no World Objects generate harmless stubs from the existing
  `gameworlditems.rulec/.ruleh/.ruletxt` rather than retaining stale objects.
- Worlds with no Adventure generate harmless `gameadventure.c/.h` using the
  new `gameadventureempty.rulec/.ruleh`, rather than retaining stale dialogue.
- The .codergirl directory (and its world bundle C files) is excluded from
  project traversal and compilation, even if an old manifest explicitly
  lists those paths. This avoids duplicate global/linker symbols.
- Name collisions such as `Cave 2.sbgm` and `Cave-2.sbgm`, both sanitising to
  the same C symbol, are caught before generation.
- Update Game Project backs up the active-world marker as well as the
  existing generated C/H outputs and user-owned main.c.
- No gameplay physics, map format, or V2 GUI rule code changed.

## How to test safely

1. Keep your known-good Stage 4.55 game and its external backup.
2. Replace Stage 5.0 changed files and install its two new rule files.
3. Rebuild the Qt IDE.
4. Open `world1.sbgm`, run Update Game Project, and build your existing
   `world1` game on SIDBOX. The runtime behavior should be unchanged.
5. Check `.codergirl/active-world.json` and
   `.codergirl/worlds/world1/world.json`. The bundle should contain the
   world1 resources, objects, splines, dialogue and map that apply.
6. Create a second `.sbgm` named `forest.sbgm`, give it a different spline,
   collectable and dialogue, and use **Generate V1 Game Code** or
   **Update Game Project** on that design. Check
   `.codergirl/worlds/forest/` has a separate bundle while
   `.codergirl/worlds/world1/` is unchanged.
7. Do not expect an `forest` build to work with a hand-edited `main.c`
   that still hardcodes the `world1` map: F5 now warns instead of silently
   mixing worlds. Change main.c deliberately, or continue building world1.

## Still to implement (next stages)

1. Per-world C namespaces and linkable simultaneous worlds. Current
   `gameassets_*` and other APIs still have shared compiled names.
2. Runtime load/unload, entry points and world transitions from main.c.
3. Cross-world persistent inventory, score, dialogue progress and quest state.

This is an intentionally additive first stage for preserving *all* resources
per `.sbgm` safely; it is NOT yet a playable multi-world loader.

## Verification performed here

- Compiled no-story Adventure C stub with GCC using `-std=c11 -Wall -Wextra -Werror -pedantic`.
- Source-level integration invariants checked (snapshot publishing, no duplicate
  compiler traversal, named-world marker, user-owned main protection, rollback).
- Qt6 toolchain is not installed in this environment: IDE build and SIDBOX
  hardware execution must be verified by the user.
