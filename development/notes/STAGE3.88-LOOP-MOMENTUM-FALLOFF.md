# Stage 3.88 — Loop Momentum Falloff

Baseline: **Stage 3.87** from the uploaded, most recent IDE. Preserves Stage 3.86 friction-free exits and Stage 3.87 cliff/ballistic launch.

## User-visible feature

Tilemap Editor -> Loop Tracks -> select loop -> **Momentum Falloff**.

- Slider: 0..200 units, 0.1 percentage point per unit, displayed as 0.0%..20.0% **per 50Hz physics frame**.
- Only active when **Ignore friction after exit (until wall or movement)** is checked.
- 0.0% is exact legacy free-coasting behaviour.
- Nonzero falloff loses a percentage of the *remaining* horizontal loop-exit momentum every frame; no minimum input and no effect on uphill/downhill loop boosts themselves.
- Falloff continues while jumping or airborne following a cliff; gravity remains active.
- Left or right input returns to ordinary physics drag; wall collision stops the horizontal speed and clears the special coast. New loop attachment and player reset also clear it.
- 50Hz suggested starting values: 0.1% (space-like drift), 1.0% (gentle drag), 5.0% (strong water-like resistance).

## Persistence and generation

- `.sbgm` key: `coastFalloffPermille` (0..200), per loop.
- Maps made with older IDE versions default the value to zero on load.
- `level1.c` exports a new 7th field in each `game_tile_loop_t` initializer.
- `game_tile_loop_t` in `idelibs/codehelpers/game/tilemap.h` adds `uint16_t coast_falloff_permille` at the end.
- `game_tile_player_t` latches its value as `loop_coast_falloff_permille` on completing the revolution.
- `game_tile_player_run()` applies fixed-point `(force_vx100 * (1000-falloff))/1000` AFTER that physics frame's horizontal movement, independently of normal drag.

**Important:** regenerate the level and update the installed C/H game helpers together. In the IDE use **F5 -> Update and Compile** and approve the existing backup/update confirmation. Do not merely compile an old generated level against the newly updated helper layout.

## Tests

- `development/tests/test_stage388_loop_coast_falloff.c`: native fixed-point behaviour in both directions, zero/5% falloff, airborne, reset/re-attachment, controls, wall collisions, disabled checkbox.
- `development/tests/test_stage388_loop_coast_falloff_export.py`: editor/JSON/codegen/runtime source-wiring checks.
- Earlier native Stage 3.68 player hitbox, 3.72 loop entry, 3.80 momentum, 3.86 coasting, 3.87 cliff gravity pass with new struct initialisers.
- No Qt6 SDK here to compile or visually verify the editor; Fedora/Qt Creator and real SIDBOX hardware remain the acceptance tests.

## Files changed

- `gametilemap.cpp`
- `gametilemap.h`
- `gametilemapmodel.cpp`
- `idelibs/codehelpers/game/tilemap.c`
- `idelibs/codehelpers/game/tilemap.h`

All new stage notes belong in `development/notes/`.
