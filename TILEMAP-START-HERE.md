# Advanced Tilemap — Stage 1.1: foreground ring

**Keep a backup of your working game and IDE.** This patch has passed standalone C tests, but Qt6 compilation and the SIDBOX display tests have **not** been run here.

## The three sizes are independent

- **Virtual world:** for example 100 x 100 cells of 16 pixels = **1600 x 1600** world pixels. Seeing 1600 in the designer's **World** field is correct, not a request for a 1600-wide graphics buffer.
- **Visible display:** **480 x 320** pixels.
- **Foreground ring:** **960 x 320** physical pixels, two mirrored 480-wide halves. The renderer scrolls the **front** layer with `gfx_scrollf()` and updates only the newly uncovered pixel columns.
- **Background:** a separate **480 x 320** static backdrop, shown with `gameassets_show_background()`. `gfx_scrollb(0,0)` keeps it still for this test.

This prototype scrolls the foreground **horizontally only**. Vertical camera scrolling and parallax can be added in a later stage. The foreground's palette index 0 must be transparent, while the background palette is opaque.

## Replace already-installed game helpers!

The IDE does NOT overwrite existing game helper code when exporting. If your game already has the old Stage 1 helper, replace:

- `<your-game>/gamehelpers/gametilemap.c`
- `<your-game>/gamehelpers/gametilemap.h`

with the game-ready files supplied in `gamehelpers/` in the drop-in archive. The IDE's reusable originals go in:

- `<IDE>/idelibs/codehelpers/game/tilemap.c`
- `<IDE>/idelibs/codehelpers/game/tilemap.h`

Also replace `gametilemap.cpp` (updated export instructions and faster editing) and `gamedesigner.cpp` (world-width tooltip); rebuild the Qt IDE. Re-export the map (`Export Tilemap to C`) to refresh the beginner example in `gamelevels/level1.c`. Your `.sbgm` map and existing assets remain untouched.

## In your V1 game's main.c

The exact sprite variable name depends on your asset generator. Below, `player` is an **example**. Use your actual `gfxbob_t`.

```c
#include "gamehelpers/gametilemap.h"
#include "gamelevels/level1.h"

static game_tilemap_ring_t ring = {0};
static game_tile_player_t player_physics = {0};
static int32_t camera_x = 0;

// Once, after initMalloc(), BEFORE gameassets_init():
gfx_mode(960, 320, 480, 320,
         DISPFLAG_DUALLAYER | DISPFLAG_SCROLLABLE);

// Once, AFTER gameassets_init():
gameassets_show_background();
gfx_scrollb(0, 0);
if (!game_tilemap_ring_init(&ring, &game_level1,
        gfx_getfbuffer1(), gfx_getfbuffer2())) {
    // STOP: check that the foreground buffer descriptors are 960 x 320
    // with stride >= 320 and enough memspacelen. Do not draw to them.
}
gfx_showfbuffer(gfx_getfbuffer1());
game_tile_player_start(&player_physics, &game_level1, &player);

// Once per game frame (after gfx_lcdwait()):
int32_t old_x = player_physics.x100 / 100;
int32_t old_y = player_physics.y100 / 100;
game_tile_player_run(&player_physics, getjoyport(), 1);
camera_x = player_physics.x100 / 100 - 240;
game_tilemap_ring_update(&ring, camera_x, 0);
gfx_scrollf(game_tilemap_scroll_x(&ring), 0);
game_tilemap_ring_restore_rect(&ring, old_x, old_y,
                                player.width, player.height);
game_tile_player_ring_screen(&player_physics, &ring);
gfx_usebuffer(gfx_getfbuffer1());
gfx_drawbob(&player);
gfx_displaynow();
```

**IMPORTANT:** Do **not** call `gfx_cls()` on the foreground in your loop; it erases the ring's persistent tiles. The restore call repaints the previous sprite area with its original map pixels. This example displays only `gfx_getfbuffer1()`; do not swap buffers without also accounting for dynamic sprites. If you add more moving sprites, restore each one's old footprint.

The background should be imported as a **Direct to Buffer** background resource in Game Designer. A normal background sprite drawn on the foreground isn't a static hardware background. Check the `gameassets_init()` return value and that `gameassets_show_background()` has been called.

## Map and collision editing

As before: right-click the Game Designer canvas -> **Tilemap Editor (Graphics + Collisions)**. Choose a PPB sprite atlas, paint graphic IDs, switch to Collision layer and paint solid/one-way tiles independently. The full virtual world can be panned freely in the editor. Press **Apply to Design**, then **Save Design**, and **Export Tilemap to C**.

### Hardware checkpoints

1. At camera X=0: backdrop visible through transparent foreground regions; bricks drawn over it.
2. Move gradually through camera X=479, 480, 481. No strip distortion should appear at the physical 480-column join.
3. Scroll right and back left: newly exposed columns should update and old bricks should return.
4. Player should not leave trails. If it does, check the `restore_rect()` call and remove any `gfx_cls()` calls.
5. Check VBlank timing. Desktop tests cover ring memory indexing but cannot prove the firmware's `gfx_scrollf()` implementation or DMA transfer throughput.

### Verified on desktop

The revised C helper compiles against the V1 API with strict warnings; tests cover both 960x320 mirrored foreground buffers, varied tile artwork, camera steps across both half-buffer seams, left/right movement, full ring refreshes, sprite-footprint repair, bounds checks and sprite coordinates.

### Still needs hardware/Qt confirmation

- SIDBOX foreground buffer descriptors and how `gfx_scrollf()` interprets them.
- Foreground alpha composition over the static background.
- Sprite drawing/restoring under the actual V1 display pipeline.
- Qt6 Game Designer build and tile paint performance.
