# CoderGirl V1 — Stage 3.0A: World Objects foundation

A working game-code foundation for animated collectables, moving lifts,
conveyors and bouncing springs. No firmware, pixel format, tilemap physics,
GUI Designer or CoderGirl editor source was altered.

## What is implemented NOW

**New dynamic code helpers** (discovered automatically by Game Designer's
existing *Add Helper Code* menu):

| SDK template | Installed in project | Purpose |
| --- | --- | --- |
| `collectables.c/.h/.ini/.txt` | `gamehelpers/gamecollectables.c/.h/.txt` | Pickups, one-time callbacks, animation, world-coordinate spline movement, world-based collision and camera-relative drawing |
| `worldobjects.c/.h/.ini/.txt` | `gamehelpers/gameworldobjects.c/.h/.txt` | Moving lifts, conveyors and springs; optional animation and spline; carrying and top-surface player interaction |

Both use the *existing* `gameanimation` and `gamespline` helpers. They have no
heap allocation or hidden VBlank/draw calls. No new graphics renderer.

### Coordinate rules

- **Game Designer**: sprite `x/y` are WORLD positions.
- **Spline**: stores WORLD positions. Attach a spline to the same sprite as its
  optional animation. Call `set_spline_pos()` ONCE at setup for new start.
- **Objects**: use WORLD positions for collision and physics. `draw()` makes
  a temporary sprite copy and subtracts camera `x/y` precisely once.
- **Do not call `offset_spline()`** on splines attached to these helpers.
  That function is appropriate when your game draws sprites directly.
  Here, the helper draws world positions using its own camera translation.

### Movement and collision

Use `game_world_objects_update()`, `game_world_objects_before()`, normal player
physics, then `game_world_objects_after()` in that order every frame.

The `game_world_player_t` adapter binds to `x100/y100/vy100/on_ground` fields of
`game_tile_player_t` or `game_platformer_t` without modifying either helper.
Top-surface interactions are intentionally conservative; existing tilemap
collision stays authoritative for terrain. In this stage, platforms have no
solid sides/undersides; high-speed lifts/conveyors can intersect terrain.

### Working visual placement available today

The *existing* Game Designer can already place sprite resources over the
visible tilemap. When you Generate V1 Game Code, the sprite's initial `drawx`/
`drawy` is the position from the canvas. The `.txt` guides use that position
when setting up objects in `main.c`. You manually choose each object's role
and optional spline using the helper setup calls for now.

## NEXT: Stage 3.0B — Full visual World Objects editing

Design proposal, NOT implemented in Stage 3.0A:

1. Add a **Behaviour** selector in the EXISTING sprite properties panel:
   `Decoration`, `Collectable`, `Lift`, `Conveyor`, `Spring`.
   No extra toolbar rows or reduction of the world canvas.
2. For Collectable: type, value, respawn flag, collision width/height.
3. For Lift/Conveyor/Spring: collision width/height, conveyor speed,
   bounce strength; optional moving-surface collision preview.
4. Optional **Spline** selection from Game Designer's already-exported
   paths, plus `Start`, `End`, `Frames per image`, `Loop/Pingpong` animation.
   Spline motion and sprite frame changes are independent of each other.
5. Add visual decorations/outlines to preview object hitboxes and attachments
   at the same world zoom as the tilemap, with sprites remaining foreground.
6. Save these fields as optional keys in `.sbgm` version 1 to preserve older
   project compatibility.
7. Export **separate** `gamehelpers/gameworlditems.h/.c` setup data, not
   modifications to `main.c` or hardware-proven platformer code. The generated
   startup function binds exported sprites to the chosen spline and animation
   and exposes the collectable and platform arrays to `main.c`.
8. Place instructions into `gamehelpers/gameworlditems.txt` and keep all UI
   controls theme-aware with rectangular/square corners.

## Tested here

- `gcc -std=c11 -Wall -Wextra -Werror -fsyntax-only` against the *actual*
  SIDBOX V1 SDK API headers (both new helpers and existing dependencies).
- Host AddressSanitizer + UndefinedBehaviourSanitizer tests: pickup once,
  score callback, animation frame advance, shared-world-to-screen rendering,
  spline relocation, carrying rider, conveyor movement and spring launch.
- Moving lift carry tested for ten game frames while running the ACTUAL
  `game_tile_player_run()` implementation from the existing tilemap helper.

Not compiled with Qt6; no IDE C++ source was changed. Not tested on STM32
hardware yet. Test in a backed-up V1 game project before depending on it.
