/* CoderGirl V1 - Beginner Platformer
 *
 * Adds walking, gravity, jumping and collision against rectangular platforms
 * to an existing gfxbob_t sprite. No new graphics, malloc or firmware needed.
 *
 * HOW TO START:
 * Open gamehelpers/gameplatformer.txt in the IDE Project Tree.
 * At 50 FPS, call run_platformer(..., getjoyport(), 1) once per game frame.
 * Your existing game loop still draws the sprites and waits for VBlank.
 *
 * IMPORTANT: This first version assumes your player uses the default
 * TOP-LEFT sprite handle and scale=100. Platform coordinates are in the
 * same pixel coordinates as sprite drawx/drawy. Platforms are invisible
 * collision areas: draw your platforms separately using your game assets.
 */
#ifndef CODERGIRL_V1_GAMEPLATFORMER_H
#define CODERGIRL_V1_GAMEPLATFORMER_H

#include "apis.h"
#include <stdint.h>

#define GAME_PLATFORM_SOLID   0u /* Blocks left, right, top and bottom. */
#define GAME_PLATFORM_ONEWAY  1u /* Jump through from below; land on top. */

typedef struct {
    int16_t x;             /* Top-left of the platform, in pixels. */
    int16_t y;
    uint16_t width;        /* Size of the platform in pixels. */
    uint16_t height;
    uint8_t type;          /* GAME_PLATFORM_SOLID or GAME_PLATFORM_ONEWAY */
} game_platform_t;

typedef struct {
    gfxbob_t *sprite;                /* Your game's existing player sprite. */
    const game_platform_t *platforms;/* Your game's rectangular collision areas. */
    uint16_t platform_count;
    uint8_t on_ground;               /* Read this to tell if the player landed. */
    uint8_t jump_held;               /* Internal: stops holding Jump from auto-repeating. */

    /* Beginner settings: feel free to change these AFTER start_platformer(). */
    int16_t walk_speed;              /* Pixels moved left/right per frame; default 3. */
    int16_t jump_speed;              /* Initial upward speed; default 7. */
    int16_t gravity;                 /* Default 35 = +0.35 pixel/frame of fall speed. */
    int16_t max_fall_speed;          /* Maximum falling speed; default 9 pixels/frame. */

    /* Internal movement values. Ignore these when starting out. */
    int32_t x100;
    int32_t y100;
    int32_t vy100;
} game_platformer_t;

/* Call AFTER gameassets_init() once your player sprite exists.
 * sprite must have a valid image, scale=100 and TOP-LEFT handle (the
 * Game Designer's normal defaults). Returns 1 if ready, 0 otherwise.
 * You can set platform_count=0 and platforms=NULL to test gravity alone.
 */
uint8_t start_platformer(game_platformer_t *physics, gfxbob_t *sprite,
                         const game_platform_t *platforms,
                         uint16_t platform_count);

/* Call once per VBlank BEFORE drawing, normally with frame_step=1.
 * Uses SIDBOX joypad flags: LEFT/RIGHT walk; UP or FIRE jumps.
 * One jump per press; release the button before the next jump.
 * For missed frames, frame_step may be >1; at most 60 steps per call.
 */
void run_platformer(game_platformer_t *physics, uint8_t joypad,
                    uint16_t frame_step);

/* Put the player back somewhere (e.g., after falling off the level).
 * Clears falling speed and checks whether the new position is on a platform.
 */
void reset_platformer(game_platformer_t *physics, int16_t x, int16_t y);

#endif
