# CoderGirl Stage 2.0 — Extended Tile IDs

## Why this change?

A tile atlas can now contain more than 255 tiles. The tilemap uses a `uint16_t` graphic ID (0 = empty, 1 = first atlas tile, etc.) and retains a `uint8_t` collision type. Animated tiles use the same graphical ID scheme. The SIDBOX V1 renderer continues to use `gfx_blit()` and the existing foreground double buffering; the independent `gfxbob_t.index` sprite API still has its original 8-bit frame field and was **not** changed.

## Replace the IDE files

In your IDE source root, replace:

- `gametilemap.cpp`
- `gametilemap.h`
- `idelibs/codehelpers/game/tilemap.c`
- `idelibs/codehelpers/game/tilemap.h`
- `idelibs/codehelpers/game/tilemap.ini` (menu description)
- `idelibs/codehelpers/README.md` (documentation)

Rebuild CoderGirl. No other Qt files were changed.

## Replace existing game helper files

Existing games already contain their own helper copies and **do not** automatically receive updated templates. Replace BOTH:

- `<your game>/gamehelpers/gametilemap.c`
- `<your game>/gamehelpers/gametilemap.h`

These files are included in a separate drop-in archive.

**Re-export your tilemap:** Open the `.sbgm` in the updated IDE, open Tilemap Editor, Apply to Design, choose Yes to export, and regenerate `gamelevels/level1.c` and `level1.h`. Rebuild your game. The exported graphics array changes type from `uint8_t[]` to `uint16_t[]`. Using an old generated level with the new helper is not safe. If you hand-edited a generated level, back it up before exporting.

## Animations — a simple example

Your generated `gamelevels/level1.c` and the template `gametilemap.c` now end with an ordinary `/* ... */` comment containing code lines **without leading `*` characters** for easy copy/paste.

```c
#include "gamelevels/level1.h"

// Once after graphics and player initialisation

game_tilemap_animation_reset();
game_tile_player_start(&physics, &game_level1, &player);

// Once per VBlank in the main loop

game_tilemap_animation_tick(1);
game_tile_player_run(&physics, getjoyport(), 1);

// After choosing the drawing foreground buffer

gfx_usebuffer(front[draw_index]);
game_tilemap_blit_view(&game_level1, camera_x, camera_y, 480, 320);
game_tile_player_screen(&physics, camera_x, camera_y);
gfx_drawbob(&player);
```

The shown variables are placeholders for those already defined in your working `main.c`. Use your existing double-buffer flip sequence, and tick animations just once per VBlank, **not once per foreground page**.

## Compatibility and limits

Old byte-graphics `.sbgm` documents load with their graphics IDs expanded to 16-bit automatically. The updated IDE writes the new key `graphics16Z` when saving. Save a backup first: an older IDE version won't understand newly saved 16-bit graphics. `gamelevels` data is generated in C form with `uint16_t` graphics and `uint8_t` collisions.

The graphic ID supports values 0–65535, but an atlas's total pixel data is limited to 4 MiB by the exporter in this first version because SIDBOX SDRAM is finite. At 16x16 pixels per tile, that's 16,384 tiles; actual application memory use can impose tighter limits. Tilemaps themselves may be up to 256x256 tiles, as before. V1 `gfxbob_t.index` is still 8-bit; the extended ID applies to `gfx_blit()`-based tilemaps, **not** bob sprite-frame selection.

## Validation

Desktop C tests passed for high graphic IDs, animations past 255, slopes and normal landing/collision. Full Qt6 compilation and testing on SIDBOX hardware have not been performed here.
