/* CoderGirl V1 - World Collectables
   Optional sprite animations and spline paths use the existing helpers.
   Read gamehelpers/gamecollectables.txt for a complete beginner example.
   Positions are WORLD coordinates; only draw() subtracts the camera.
*/
#ifndef CODERGIRL_V1_GAMECOLLECTABLES_H
#define CODERGIRL_V1_GAMECOLLECTABLES_H

#include "apis.h"
#include <stdint.h>
#include "gameanimation.h"
#include "gamespline.h"

/* Change/extend these IDs in your own game if desired. */
#define GAME_PICKUP_COIN    1u
#define GAME_PICKUP_HEALTH  2u
#define GAME_PICKUP_KEY     3u
#define GAME_PICKUP_GEM     4u

typedef struct {
    gfxbob_t *sprite;               /* Each item needs its own gfxbob_t instance. */
    game_animation_t *animation;    /* Optional: NULL for still images. */
    game_spline_t *spline;          /* Optional: NULL for stationary items. */
    int32_t x, y;                   /* Current WORLD top-left position. */
    uint16_t width, height;         /* Pickup hitbox (not rendered). */
    uint16_t kind, value;           /* Game-specific kind and amount. */
    uint8_t active;                 /* 0 = already collected / hidden. */
} game_collectable_t;

typedef void (*game_pickup_callback_t)(game_collectable_t *pickup, void *user);

/* Bind existing sprite; valid sprite dimensions and top-left/scale 100 required.
   One sprite per collectable: do not reuse the same mutable sprite instance. */
uint8_t game_collectable_start(game_collectable_t *item, gfxbob_t *sprite,
                                uint16_t kind, uint16_t value);
/* If a spline is attached, (x,y) specifies its NEW FIRST control point. */
void game_collectable_set_position(game_collectable_t *item, int32_t x, int32_t y);

/* After optional animation/spline has been started, assign their pointers to
   item->animation and item->spline. Spline coordinates must be WORLD coords:
   do not apply offset_spline() to an item whose draw() subtracts the camera. */
void game_collectables_update(game_collectable_t *items, uint16_t count, uint16_t frames);

/* Player position AND pickup positions must both be in world coordinates.
   Deactivates each intersecting item exactly once, then calls callback (if any).
   Returns how many objects were picked up; never waits/draws/allocates. */
uint16_t game_collectables_check(game_collectable_t *items, uint16_t count,
                                  int32_t player_x, int32_t player_y,
                                  uint16_t player_w, uint16_t player_h,
                                  game_pickup_callback_t callback, void *user);

/* Draw to the CURRENT foreground buffer, using temporary sprite copies.
   This NEVER alters the real sprite's world position or animation frame. */
void game_collectables_draw(const game_collectable_t *items, uint16_t count,
                             int32_t camera_x, int32_t camera_y);

#endif
