#ifndef CODERGIRL_V1_GAMETILEMAP_H
#define CODERGIRL_V1_GAMETILEMAP_H

#include "apis.h"
#include <stdint.h>

/* One byte per tile in EACH independent map. Graphics IDs: 0=blank,
 * 1=first atlas tile, 2=second, etc. Collision IDs describe behaviour.
 * Tile pixels are indexed 8-bit, stored in normal row-major tile order.
 * SIDBOX's gfx_blit() handles the framebuffer layout.
 */
#define GAME_TILE_EMPTY       0u
#define GAME_TILE_SOLID       1u
#define GAME_TILE_ONEWAY      2u
#define GAME_TILE_SLOPE_UP    3u
#define GAME_TILE_SLOPE_DOWN  4u
#define GAME_TILE_HAZARD      5u
#define GAME_TILE_DOOR        6u

#define GAME_TILE_ANIM_LOOP    1u
#define GAME_TILE_ANIM_BOUNCE  2u

/* Graphic tile ID is 1-based. The following N atlas frames are played
 * together everywhere that graphic ID is painted. No per-cell state.
 * Counts 1..16, frame_ticks 1..255 VBlanks, flags are LOOP and BOUNCE.
 */
typedef struct {
    uint8_t graphic_id;
    uint8_t frames;
    uint8_t frame_ticks;
    uint8_t flags;
} game_tile_animation_t;

typedef struct {
    const uint8_t *graphics;
    const uint8_t *collision;
    const uint8_t *atlas;
    uint16_t width;       /* Map width, in tiles. */
    uint16_t height;      /* Map height, in tiles. */
    uint16_t tile_size;   /* 8, 16 or 32 pixels per tile. */
    uint16_t atlas_count; /* Graphic IDs 1 through atlas_count. */
    const game_tile_animation_t *animations; /* NULL means no animation. */
    uint16_t animation_count;
} game_tilemap_t;

/* Stage 1.3 hardware diagnostic: redraw just the visible viewport with
 * gfx_blit(), using whichever foreground buffer gfx_usebuffer() selected.
 * This is NOT the optimised 960x320 ring yet. */
/* Call once per VBlank in the main loop, BEFORE drawing either front buffer.
 * Both buffers then use the same animation frame. Call reset on level start.
 */
void game_tilemap_animation_reset(void);
void game_tilemap_animation_tick(uint16_t frames);

void game_tilemap_blit_view(const game_tilemap_t *map,
                            int32_t camera_x, int32_t camera_y,
                            uint16_t view_width, uint16_t view_height);

/* Advanced tile-aware player movement (world coordinates). */
typedef struct {
    const game_tilemap_t *map;
    gfxbob_t *sprite;
    int32_t x100, y100, vy100;
    int16_t walk_speed, jump_speed, gravity, max_fall_speed;
    uint8_t on_ground, jump_held, coyote, touch_type;
} game_tile_player_t;

uint8_t game_tile_player_start(game_tile_player_t *p,
                                const game_tilemap_t *map, gfxbob_t *sprite);
void game_tile_player_reset(game_tile_player_t *p, int16_t x, int16_t y);
void game_tile_player_run(game_tile_player_t *p, uint8_t buttons, uint16_t frames);
/* Move the bob to the correct SCREEN position before gfx_drawbob(). */
void game_tile_player_screen(game_tile_player_t *p, int32_t camera_x, int32_t camera_y);

#endif
