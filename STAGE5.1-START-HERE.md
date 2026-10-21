# Stage 5.1 — Buildable World Folders (V1/Game only)

Based on Stage 5.0, retaining the rules-driven generators. V2 GUI untouched.

## What you get

Exporting `world1.sbgm` creates both its private `.codergirl/worlds/world1/`
archive and a visible, compilable `worlds/world1/` tree:

```
worlds/world1/
    world_symbols.h            <- preprocessor aliases for this world's exports
    world_api.h                <- short, stable entry-point declarations
    gameassets/gameassets.c/.h
    gamehelpers/gameworlditems.c/.h
    gamehelpers/gameadventure.c/.h
    gamehelpers/splinepaths.c/.h    (when paths exist)
    gamelevels/world1.c/.h/.map     (when map exists)
```

`world1_gameassets_init`, `world1_gameworlditems_init`, `world1_gameadventure_setup`,
resource symbols such as `world1_man`, `world1_drawman`, and exported spline
symbols are renamed by `world_symbols.h` when each C module is compiled.
`forest` gets separate `forest_...` identifiers. The tilemap symbols already
have their unique `game_world1` / `game_forest` names from Stage 4.53.

Build file discovery includes all world folders automatically. The original
`gamelevels/world1.c` is **not** compiled twice when its world-folder copy
exists; the legacy root `gameassets/` and `gamehelpers/` files remain available
for existing hand-edited `main.c`. Shared engine helpers compile once.

## Important scope

This is a linkable *multiworld foundation*, **not** runtime switching.
Do not call two worlds' init functions at once: palettes/audio/resource global
state are not yet managed across transitions. A world manager and persistent
player/inventory are Stage 5.2+.

Your user-owned `main.c` is never overwritten. F5 still chooses an active
world to regenerate canonical starter resources; all published worlds are linked.
World-specific .map paths remain `gamelevels/<name>.map` on the TFCard.

## Test sequence

1. Back up your working Stage 5.0 project.
2. Install changed files, rebuild the IDE.
3. Open world1.sbgm -> Update Game Project; confirm worlds/world1/ appears.
4. Open forest.sbgm -> Update Game Project; confirm worlds/forest/ appears.
5. Compile the project: check both world trees in compiler's Project sources;
   verify no duplicate definition errors. Existing hand-written main.c should
   keep its canonical gameassets/gameworlditems calls unchanged.
6. Test your active test game on hardware. Do **not** test switching yet.

Qt6/ARM toolchains are unavailable in this sandbox; IDE and hardware tests
must be run in your environment. A host-GCC namespace collision test is included
under development/tests/.
