#ifndef CODERGIRL_V1_GAMETILEMAP_H
#define CODERGIRL_V1_GAMETILEMAP_H

#include "apis.h"
#include <stdint.h>

/* Two bytes per graphics tile, one byte per collision tile. Graphics IDs: 0=blank,
 * 1=first atlas tile, 2=second, etc. Collision IDs describe behaviour.
 * Tile pixels come straight from the row-major SD PPB image.
 * SIDBOX's gfx_drawbob() handles atlas selection and foreground rendering.
 */
#define GAME_TILE_EMPTY       0u
#define GAME_TILE_SOLID       1u
#define GAME_TILE_ONEWAY      2u
#define GAME_TILE_SLOPE_UP    3u
#define GAME_TILE_SLOPE_DOWN  4u
#define GAME_TILE_HAZARD      5u
#define GAME_TILE_DOOR        6u
#define GAME_TILE_CUSTOM_SLOPE 7u /* Legacy v3 per-pixel surface */
#define GAME_TILE_POINT_SLOPE  8u /* Shared point-defined surface (v4) */

/* GamerGirl hazard contact phases and scripted death.
   Existing GAME_DEATH_TILE_HAZARD / GAME_DEATH_ZONE values are retained as
   ENTERED aliases so older on_player_death() callbacks remain compatible.
   ENTERED occurs on the first contact frame, INSIDE on each following
   overlapping physics update, EXITED on the first update after leaving.
   These are NOT fatal; only an explicit death call stops player physics. */
#define GAME_DEATH_TILE_HAZARD 1u
#define GAME_DEATH_ZONE        2u
#define GAME_DEATH_SCRIPT      3u
#define GAME_HAZARD_TILE_ENTERED GAME_DEATH_TILE_HAZARD
#define GAME_HAZARD_ZONE_ENTERED GAME_DEATH_ZONE
#define GAME_HAZARD_TILE_INSIDE 4u
#define GAME_HAZARD_ZONE_INSIDE 5u
#define GAME_HAZARD_TILE_EXITED 6u
#define GAME_HAZARD_ZONE_EXITED 7u
typedef void (*game_death_callback_t)(uint8_t reason, int32_t world_x,
                                      int32_t world_y, void *user);
void game_death_set_callback(game_death_callback_t callback, void *user);
/* Contact notification; does NOT stop movement. Used by generated helpers. */
uint8_t game_hazard_notify(uint8_t reason, int32_t world_x, int32_t world_y);
/* Explicit death: freezes physics and notifies registered callback once. */
uint8_t game_death_trigger(uint8_t reason, int32_t world_x, int32_t world_y);
/* Explicit death from INSIDE the contact callback (no second notification). */
void game_death_mark_dead(void);
uint8_t game_death_is_dead(void);
void game_death_rearm(void);

#define GAME_TILE_FLIP_X       1u
#define GAME_TILE_FLIP_Y       2u
#define GAME_TILE_DRAW_FRONT   4u /* foreground pass, after the player */

#define GAME_TILE_ANIM_LOOP    1u
#define GAME_TILE_ANIM_BOUNCE  2u

/* Graphic tile ID is 1-based. The following N atlas frames are played
 * together everywhere that graphic ID is painted. No per-cell state.
 * Counts 1..16, frame_ticks 1..255 VBlanks, flags are LOOP and BOUNCE.
 */
typedef struct {
    uint16_t graphic_id;
    uint8_t frames;
    uint8_t frame_ticks;
    uint8_t flags;
} game_tile_animation_t;

/* SD v4 point-defined slope database. Shapes and points are shared by all
 * placements. A per-cell uint16 reference makes collision queries O(1) to
 * find the placement; then a handful of line segments are interpolated. */
typedef struct {
    uint8_t width, height; /* stamp dimensions in tile cells */
    uint16_t point_offset; /* index into shape_points */
    uint8_t point_count;
    uint8_t reserved;
    uint16_t reserved2;
} game_tile_shape_t;
typedef struct {
    uint16_t x, y; /* local pixel position */
} game_tile_shape_point_t;
typedef struct {
    uint16_t x, y; /* tile coordinates of top-left corner */
    uint8_t shape; /* index into shape_defs */
    uint8_t flags; /* bit 0: horizontal mirror */
} game_tile_shape_instance_t;

typedef struct {
    const uint16_t *graphics;
    const uint8_t *collision;
    const uint8_t *atlas; /* Original PPB pixels, NULL until loaded. */
    uint16_t width;       /* Map width, in tiles. */
    uint16_t height;      /* Map height, in tiles. */
    uint16_t tile_size;   /* 8, 16 or 32 pixels per tile. */
    uint16_t atlas_count; /* Graphic IDs 1 through atlas_count. */
    const game_tile_animation_t *animations; /* NULL means no animation. */
    uint16_t animation_count;
    uint16_t atlas_width;   /* PPB width in pixels; set by atlas loader. */
    uint16_t atlas_height;  /* PPB height in pixels; set by atlas loader. */
    uint8_t atlas_borrowed; /* Nonzero: atlas owned by gameassets; never free here. */
    void *map_storage; /* SD .map allocation. NULL for embedded C maps. */
    const uint8_t *flips; /* Per-cell X/Y + front-layer flag; NULL for legacy maps. */
    const uint8_t *slopes; /* Legacy v3 height array, NULL for pure v4 shapes. */
    const uint16_t *shape_refs; /* [cell]: instance index + 1, 0 = none */
    const game_tile_shape_instance_t *shape_instances;
    const game_tile_shape_t *shape_defs;
    const game_tile_shape_point_t *shape_points;
    uint16_t shape_instance_count;
    uint8_t shape_count;
} game_tilemap_t;

/* Redraw visible tiles using the V1 BOB atlas renderer and whichever
 * foreground buffer gfx_usebuffer() selected. This is NOT a ring buffer.
 * The tile renderer clears each tile first, preserving transparency. */
/* Call once per VBlank in the main loop, BEFORE drawing either front buffer.
 * Both buffers then use the same animation frame. Call reset on level start.
 */
/* GAME_TILEMAP_BOB_SD_ATLAS_V1: retain normal PPB pixel layout.
   Load the complete pixel data once, validate its FNV-1a checksum and use
   gfx_drawbob() to pick tiles by their atlas positions. No repacking.
   Return 1 on success; 0 on bad/missing/stale file or allocation failure.
   map->atlas starts NULL. Call unload before reloading/leaving the level. */
uint8_t game_tilemap_load_ppb_atlas(game_tilemap_t *map, const char *file,
                                   uint16_t atlas_width, uint16_t atlas_height,
                                   uint32_t expected_hash);
/* Borrow an already-loaded, path-matched sprite PPB if its exact pixel
   checksum/dimensions match the level. Caller MUST unload tilemap before
   gameassets_shutdown(); gameassets owns the borrowed allocation. */
uint8_t game_tilemap_attach_shared_ppb_atlas(game_tilemap_t *map,
                                            const uint8_t *pixels,
                                            uint16_t atlas_width, uint16_t atlas_height,
                                            uint32_t expected_hash);
void game_tilemap_unload_ppb_atlas(game_tilemap_t *map);
/* SD .map v1/v2/v3/v4: tile graphics, collisions and tile animations (not sprites,
   object placements or atlas PPB pixels). All fields checked before swap.
   Call after initMalloc(); optionally replace an already loaded SD map.
   A failed load leaves the current map intact. Atlas must match tile size
   and tile count. Unload the map allocation when leaving the level. */
uint8_t game_tilemap_load_map(game_tilemap_t *map, const char *filename);
void game_tilemap_unload_map(game_tilemap_t *map);

void game_tilemap_animation_reset(void);
void game_tilemap_animation_tick(uint16_t frames);

void game_tilemap_blit_view(const game_tilemap_t *map,
                            int32_t camera_x, int32_t camera_y,
                            uint16_t view_width, uint16_t view_height);

/* Draw ONLY tiles marked GAME_TILE_DRAW_FRONT over the player.
   Does not clear any pixels: call after the normal tile pass and player draw. */
void game_tilemap_blit_view_front(const game_tilemap_t *map,
                                  int32_t camera_x, int32_t camera_y,
                                  uint16_t view_width, uint16_t view_height);

/* Optimised redraw for a target buffer that was ALREADY cleared in full.
   Skips redundant clear blits; all rear tiles render normally. */
void game_tilemap_blit_view_cleared(const game_tilemap_t *map,
                                    int32_t camera_x, int32_t camera_y,
                                    uint16_t view_width, uint16_t view_height);

/* Check whether a WORLD-space actor hitbox intersects solid walls or the
   interior of slopes. Used to prevent lifts carrying a player into a wall. */
uint8_t game_tilemap_actor_blocked(const game_tilemap_t *map,
                                   int32_t x, int32_t y,
                                   uint16_t width, uint16_t height);

/* Advanced tile-aware player movement (world coordinates). */
typedef struct {
    const game_tilemap_t *map;
    gfxbob_t *sprite;
    int32_t x100, y100, vy100;
    int16_t walk_speed, jump_speed, gravity, max_fall_speed;
    uint8_t on_ground, jump_held, coyote, touch_type;
    /* Internal: detect externally applied upward impulses (e.g. springs).
       Such launches always use the SHORT-HOP gravity, independent of the
       Jump button. Ordinary player jumps keep variable-height control.
       No additional main.c wiring is required. */
    int32_t physics_vy100; /* Velocity at the end of the previous physics step. */
    uint8_t external_ascent;
    uint8_t hazard_contact; /* Internal: overlapping tile hazard on previous update. */
} game_tile_player_t;

uint8_t game_tile_player_start(game_tile_player_t *p,
                                const game_tilemap_t *map, gfxbob_t *sprite);
void game_tile_player_reset(game_tile_player_t *p, int16_t x, int16_t y);
void game_tile_player_run(game_tile_player_t *p, uint8_t buttons, uint16_t frames);
/* Move the bob to the correct SCREEN position before gfx_drawbob(). */
void game_tile_player_screen(game_tile_player_t *p, int32_t camera_x, int32_t camera_y);

#endif
