# Stage 3.92b — Explain drawing order and player hurt flashing in `maingame.c.txt`

Starting point: **Stage 3.92a** (Murder Object header hotfix).

## Why

`maingame.c.txt` is intended to be a working, beginner-readable manual. When a
project uses placed Game Objects, the exporter now places an explanation
immediately above `gameworlditems_draw_behind(camera_x, camera_y)`:

- What "Draw behind tilemap" means for rendering layers;
- Why the call **must precede** drawing the tilemap (e.g. moving spikes behind a floor);
- What the camera offsets do, and that drawing order does not change collisions.

When a project uses Hazard / Murder Objects, the exporter now explains the
`player_visible` copy, `game_world_player_hurt_flash`, `flash_colour`,
`BLIT_FLAG_SOLIDCOLOUR`, `BLIT_FLAG_TYPE_TINT_VALUE`, and the final
`gfx_drawbob(&player_visible)` call:

- Flash is enabled only during the ON phases reported by the helper;
- The chosen colour is a **foreground palette index**, not a direct RGB colour;
- Changing a temporary BOB copy means the original player sprite never
  permanently inherits the solid-colour draw flag;
- The player is still drawn exactly once each frame, flashed or normal.

## Installation / refreshing the tutorial

1. Replace **`gamedesigner_export.cpp`** in the IDE source tree and rebuild it
   in Qt Creator. The game engine runtime and IDE interfaces are unchanged.
2. Open the game project and run **F5 → Update and Compile** to regenerate
   `maingame.c.txt` with the new explanations. Because the generator respects
   user-owned `main.c`, the tutorial is **not** silently inserted into an
   already-customised `main.c`. Copy comments into it manually if desired.
3. Look for both headings in the generated file if the project uses Game Objects
   and a Hazard / Murder Object. The hurt block is intentionally omitted from
   projects without hazards, and the behind-tiles block is omitted when no
   managed Game Objects exist.

## Changes and checks

- **Only one production file** changed: `gamedesigner_export.cpp`.
- Added a source regression test confirming the tutorial contents, conditional
  emission and unchanged ordering of the real draw calls.
- Existing hazard, breakable and physics behaviour has not been changed.
- No Qt6 SDK or hardware is available here; rebuild and hardware confirmation
  remain necessary on Fedora.
