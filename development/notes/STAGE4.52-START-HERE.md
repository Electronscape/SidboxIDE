# Stage 4.52 — Generic World Map Rule Templates

## What changed

This stage **genericises the tilemap rule-template filenames**:

- `idelibs/codehelpers/game/level1.rulec` → `idelibs/codehelpers/game/worldmap.rulec`
- `idelibs/codehelpers/game/level1.ruleh` → `idelibs/codehelpers/game/worldmap.ruleh`

The tilemap exporter in `gametilemap.cpp` has been updated to load the new generic template names.

## Important

This stage **does not yet implement multi-world naming**.
The generated output remains:

- `gamelevels/level1.c`
- `gamelevels/level1.h`
- `gamelevels/level1.map`
- `game_level1`
- `game_level1_load_map()`
- `game_level1_load_atlas()`

So this is a **template-name cleanup only**, making the SDK internals more future-friendly.

## Why do this now?

Because `level1.rulec/.ruleh` are reusable SDK templates, not a specific user level. The generic name better reflects their real purpose and prepares the codebase for later multi-world support.

## Files changed

- `gamedesigner/gametilemap.cpp` (actual file in project root: `gametilemap.cpp`)
- `idelibs/codehelpers/game/worldmap.rulec`
- `idelibs/codehelpers/game/worldmap.ruleh`

## Files to remove from older installs

Delete these old template files if they still exist:

- `idelibs/codehelpers/game/level1.rulec`
- `idelibs/codehelpers/game/level1.ruleh`

## Test plan

1. Rebuild the IDE.
2. Open an existing `.sbgm`.
3. Export Tilemap or run **Update Game Project**.
4. Confirm the generated files are still named:
   - `gamelevels/level1.c`
   - `gamelevels/level1.h`
   - `gamelevels/level1.map` (if using TFCard/external maps)
5. Compile the generated game and verify it still runs on SIDBOX.

## Next planned step

A later stage can add a **user-selected world name** so the generator can output `forest.c`, `cave.c`, etc., while preserving compatibility for existing projects.
