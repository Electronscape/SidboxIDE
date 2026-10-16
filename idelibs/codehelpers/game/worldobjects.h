/* CoderGirl V1 - Dynamic World Objects: lifts, conveyors, springs.
   See gamehelpers/gameworldobjects.txt for the frame order and examples.
   Reuses existing spline/animation helpers; collision is world-relative.
*/
#ifndef CODERGIRL_V1_GAMEWORLDOBJECTS_H
#define CODERGIRL_V1_GAMEWORLDOBJECTS_H

#include "apis.h"
#include <stdint.h>
#include "gameanimation.h"
#include "gamespline.h"

#define GAME_OBJECT_LIFT      1u
#define GAME_OBJECT_CONVEYOR  2u
#define GAME_OBJECT_SPRING    3u

typedef struct {
    gfxbob_t *sprite;           /* Optional image; NULL = invisible collider. */
    game_animation_t *animation;/* Optional frame animation. */
    game_spline_t *spline;      /* Optional spline driving WORLD movement. */
    int32_t x, y;               /* Current WORLD top-left of collision box. */
    int32_t previous_x, previous_y; /* Previous position for carrying rider. */
    uint16_t width, height;
    int16_t conveyor_speed;     /* Pixels / frame, signed; for CONVEYOR. */
    int16_t spring_strength;    /* Positive upward speed in px/frame. */
    uint8_t allow_jump_boost;  /* 0 = launch only; 1 = add jump on NEW press. */
    uint8_t type, active;
    uint8_t spring_triggered;      /* Set on landing/launch; cleared in update. */
} game_world_object_t;

/* Point this at the live physics fields of game_tile_player_t OR
   game_platformer_t. Both store their coordinates/velocity in x100/y100/vy100.
   Initialise once; do not pass sprite->drawx after camera projection! */
typedef struct {
    int32_t *x100, *y100, *vy100;
    uint8_t *on_ground;
    uint16_t width, height;
    int32_t before_feet; /* Feet BEFORE platform movement and player physics. */
    int32_t before_vy100; /* Velocity before jump input/physics (spring priority). */
    int32_t before_x;    /* Player X before movement; used for swept landing. */
    uint8_t ready;      /* Internal. */
    /* OPTIONAL: point these at the LIVE player's jump state if springs should
       know whether Jump was newly pressed this frame. Without these, spring
       launch still works normally (no combined jump boost). */
    uint8_t *jump_held;
    uint8_t *coyote;           /* Tilemap only; NULL for basic platformer. */
    const int16_t *jump_speed;
    uint8_t before_jump_held; /* Internal: input state before physics. */
    /* Optional collision test for platform carrying. Returns 1 if the
       player's hitbox would collide at WORLD (x,y). Generated tilemap games
       connect this automatically; standalone projects can leave it NULL. */
    uint8_t (*position_blocked)(int32_t x, int32_t y, uint16_t width,
                                uint16_t height, void *context);
    void *collision_context;
} game_world_player_t;

/* Initialise AFTER gameassets_init() if sprite is supplied.
   width/height specify collision box independent of image dimensions. */
uint8_t game_world_object_start(game_world_object_t *object, uint8_t type,
                                gfxbob_t *sprite, int32_t x, int32_t y,
                                uint16_t width, uint16_t height);
/* If a spline is attached, (x,y) specifies its NEW FIRST control point. */
void game_world_object_set_position(game_world_object_t *object, int32_t x, int32_t y);
void game_world_objects_update(game_world_object_t *objects, uint16_t count,
                                uint16_t frames);

/* Called BEFORE the existing tile/platformer physics. Carry known riders and
   remember their original feet for collision testing. One game-frame at a time. */
void game_world_objects_before(const game_world_object_t *objects, uint16_t count,
                                game_world_player_t *player);
/* Called AFTER physics. Handle landing, conveyors and spring launch.
   No modification to the tilemap's own collision code. */
void game_world_objects_after(game_world_object_t *objects, uint16_t count,
                               game_world_player_t *player);
void game_world_objects_draw(const game_world_object_t *objects, uint16_t count,
                              int32_t camera_x, int32_t camera_y);

#endif
