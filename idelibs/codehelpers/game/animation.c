#include "animation.h"

uint8_t start_animation(game_animation_t *animation, gfxbob_t *sprite,
                        uint16_t first_frame, uint16_t frame_count,
                        uint16_t frames_per_image, uint8_t mode)
{
    if (!animation || !sprite || !sprite->imgdat || !sprite->width ||
        !sprite->height || !sprite->atlas_stride || !sprite->atlas_height ||
        mode > GAME_ANIM_PINGPONG || !frame_count || first_frame > 255u ||
        (uint32_t)first_frame + frame_count > 256u) return 0;

    /* Never select an atlas picture that doesn't exist. A V1 gfxbob_t has
     * an 8-bit index, so only the first 256 pictures are addressable. */
    const uint32_t columns = sprite->atlas_stride / sprite->width;
    const uint32_t rows = sprite->atlas_height / sprite->height;
    const uint32_t available = columns * rows;
    if (!columns || !rows || (uint32_t)first_frame + frame_count > available)
        return 0;

    animation->sprite = sprite;
    animation->first_frame = first_frame;
    animation->frame_count = frame_count;
    animation->current_frame = 0;
    animation->frames_per_image = frames_per_image ? frames_per_image : 1u;
    animation->frame_counter = 0;
    animation->pingpong_phase = 0;
    animation->mode = mode;
    animation->finished = (mode == GAME_ANIM_ONCE && frame_count == 1u) ? 1u : 0u;
    animation->playing = animation->finished ? 0u : 1u;
    sprite->index = (uint8_t)first_frame;
    return 1;
}

void run_animation(game_animation_t *animation, uint16_t frame_step)
{
    if (!animation || !animation->playing || !animation->sprite || !frame_step)
        return;

    /* This division also handles missed frames without looping thousands of
     * times. Integer arithmetic only: fine for a small STM32 game loop. */
    const uint32_t elapsed = (uint32_t)animation->frame_counter + frame_step;
    const uint32_t steps = elapsed / animation->frames_per_image;
    animation->frame_counter = (uint16_t)(elapsed % animation->frames_per_image);
    if (!steps) return;

    if (animation->mode == GAME_ANIM_ONCE) {
        const uint32_t remaining = (uint32_t)animation->frame_count - 1u
                                   - animation->current_frame;
        if (steps >= remaining) {
            animation->current_frame = animation->frame_count - 1u;
            animation->playing = 0;
            animation->finished = 1;
            animation->frame_counter = 0;
        } else {
            animation->current_frame = (uint16_t)(animation->current_frame + steps);
        }
    } else if (animation->mode == GAME_ANIM_PINGPONG && animation->frame_count > 1u) {
        /* No duplicated endpoints: 0,1,2,1,0,1,2,1,... */
        const uint32_t cycle = (uint32_t)(animation->frame_count - 1u) * 2u;
        const uint32_t phase = ((uint32_t)animation->pingpong_phase + steps) % cycle;
        animation->pingpong_phase = (uint16_t)phase;
        animation->current_frame = (uint16_t)(phase < animation->frame_count
                                           ? phase : cycle - phase);
    } else if (animation->mode == GAME_ANIM_LOOP) {
        animation->current_frame = (uint16_t)(
            ((uint32_t)animation->current_frame + steps) % animation->frame_count);
    }
    animation->sprite->index = (uint8_t)(animation->first_frame + animation->current_frame);
}

void stop_animation(game_animation_t *animation)
{
    if (!animation) return;
    animation->playing = 0;
    animation->finished = 0;
}
