/* CoderGirl V1 - Sprite Animation
 *
 * Plays frames from an existing sprite atlas by changing gfxbob_t.index.
 * Works with sprites created by the Game Designer / gameassets_init().
 * It does NOT load pictures, wait for VBlank, or allocate any memory.
 * It can animate a sprite while Tween or Spline moves that same sprite.
 *
 * Each picture in the atlas is numbered from 0, left-to-right, top-to-bottom.
 * "first_frame" is the first picture to play, "frame_count" is how many
 * consecutive pictures to use (maximum atlas index: 255).
 * "frames_per_image" controls speed: at 50 FPS, 5 = 10 pictures/second.
 *
 * For copyable examples, open gamehelpers/gameanimation.txt.
 */
#ifndef CODERGIRL_V1_GAMEANIMATION_H
#define CODERGIRL_V1_GAMEANIMATION_H

#include "apis.h"
#include <stdint.h>

/* Choose how the animation behaves at the end. */
#define GAME_ANIM_ONCE      0u /* Play once; keep the final picture visible. */
#define GAME_ANIM_LOOP      1u /* Return to the first picture and repeat. */
#define GAME_ANIM_PINGPONG  2u /* Play forwards, then backwards, repeatedly. */

typedef struct {
    gfxbob_t *sprite;           /* Sprite supplied by your game; not owned here. */
    uint16_t first_frame;       /* First atlas picture, numbered from 0. */
    uint16_t frame_count;       /* Number of pictures in the animation (1..256). */
    uint16_t current_frame;     /* Current position within this animation. */
    uint16_t frames_per_image;  /* Game frames to show each picture. */
    uint16_t frame_counter;     /* Game frames since the last picture change. */
    uint16_t pingpong_phase;   /* Internal position along the forward/back path. */
    uint8_t mode;               /* GAME_ANIM_ONCE, LOOP, or PINGPONG. */
    uint8_t playing;            /* 1 while advancing; 0 when stopped/finished. */
    uint8_t finished;           /* 1 after GAME_ANIM_ONCE has reached its end. */
} game_animation_t;

/* Start from the first picture straight away (no need to wait one frame).
 * Call AFTER gameassets_init(), when the sprite's atlas is ready.
 * Returns 1 on success. Returns 0 for an invalid sprite, range or mode;
 * on failure the current animation and the sprite remain unchanged.
 * frames_per_image=0 is treated as 1 (fastest playback).
 */
uint8_t start_animation(game_animation_t *animation, gfxbob_t *sprite,
                        uint16_t first_frame, uint16_t frame_count,
                        uint16_t frames_per_image, uint8_t mode);

/* Run once per displayed game frame AFTER VBlank, usually with frame_step=1.
 * If the game skipped frames, supply how many elapsed instead.
 * Call BEFORE drawing the sprite. This never waits for VBlank itself.
 */
void run_animation(game_animation_t *animation, uint16_t frame_step);

/* Freeze the sprite on its current picture without changing its position.
 * To play again from the start, call start_animation() again.
 */
void stop_animation(game_animation_t *animation);

#endif
