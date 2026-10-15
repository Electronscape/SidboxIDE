/* CoderGirl V1 - Sprite Tween
 * Moves any gfxbob_t from its CURRENT position to a chosen destination.
 * All timing is in game frames, not seconds: at 50 FPS, 50 frames = 1 second.
 * Call run_tween() once per VBlank with frame_step=1. If frames were skipped,
 * pass the number elapsed. This code does NOT wait for VBlank itself.
 *
 * Example (after gameassets_init()):
 *   #include "gamehelpers/gametween.h"
 *   game_tween_t movement = {0}; // preferably global or static
 *   start_tween(&movement, &player, 300, 160, 50, 0);
 *
 * Inside the game loop, once per displayed frame:
 *   run_tween(&movement, 1);
 *   gfx_drawbob(&player);
 *
 * Use &enemies[0] for a sprite in an array.
 * Set loop=1 to repeat from the original position after each journey.
 */
#ifndef CODERGIRL_V1_GAMETWEEN_H
#define CODERGIRL_V1_GAMETWEEN_H

#include "apis.h"
#include <stdint.h>

typedef struct {
    gfxbob_t *sprite;       /* sprite that moves; not allocated or owned here */
    int16_t from_x, from_y; /* where the sprite was when started */
    int16_t to_x, to_y;     /* destination */
    uint16_t duration_frames;
    uint16_t elapsed_frames;
    uint8_t loop;
    uint8_t active;
} game_tween_t;

/* Use duration_frames=0 to move immediately. 50 frames = 1 sec at FPS_50. */
void start_tween(game_tween_t *tween, gfxbob_t *sprite,
                 int16_t x, int16_t y, uint16_t duration_frames, uint8_t loop);
/* Advance by frame_step game frames; usually 1 per VBlank. */
void run_tween(game_tween_t *tween, uint16_t frame_step);
/* Stop moving but leave sprite at its current position. */
void stop_tween(game_tween_t *tween);

#endif
