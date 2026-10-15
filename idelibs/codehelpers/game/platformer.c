#include "platformer.h"

uint8_t start_platformer(game_platformer_t *physics, gfxbob_t *sprite,
                         const game_platform_t *platforms,
                         uint16_t platform_count)
{
    if (!physics || !sprite || !sprite->imgdat || !sprite->width ||
        !sprite->height || sprite->scale != 100u ||
        sprite->handle != BLIT_HANDLE_TOP_LEFT ||
        (platform_count && !platforms)) return 0;

    physics->sprite = sprite;
    physics->platforms = platforms;
    physics->platform_count = platform_count;
    physics->walk_speed = 3;
    physics->jump_speed = 7;
    physics->gravity = 35;
    physics->max_fall_speed = 9;
    reset_platformer(physics, sprite->drawx, sprite->drawy);
    return 1;
}

void reset_platformer(game_platformer_t *physics, int16_t x, int16_t y)
{
    if (!physics || !physics->sprite) return;
    physics->x100 = (int32_t)x * 100;
    physics->y100 = (int32_t)y * 100;
    physics->vy100 = 0;
    physics->jump_held = 0;
    physics->on_ground = 0;
    physics->sprite->drawx = x;
    physics->sprite->drawy = y;

    /* Recognise a player already standing on a platform at the start. */
    for (uint16_t i = 0; i < physics->platform_count; ++i) {
        const game_platform_t *p = &physics->platforms[i];
        if (!p->width || !p->height) continue;
        if ((int32_t)y + physics->sprite->height == p->y &&
            (int32_t)x < (int32_t)p->x + p->width &&
            (int32_t)x + physics->sprite->width > p->x) {
            physics->on_ground = 1;
            break;
        }
    }
}

void run_platformer(game_platformer_t *physics, uint8_t joypad,
                    uint16_t frame_step)
{
    if (!physics || !physics->sprite || !frame_step) return;
    gfxbob_t *sprite = physics->sprite;
    const int32_t w = sprite->width;
    const int32_t h = sprite->height;
    const uint8_t jump = (joypad & (BTN_FIRE | BTN_UP)) != 0;

    /* Don't spend ages catching up after a long pause. */
    if (frame_step > 60u) frame_step = 60u;

    for (uint16_t frame = 0; frame < frame_step; ++frame) {
        if (jump && !physics->jump_held && physics->on_ground) {
            physics->vy100 = -(int32_t)physics->jump_speed * 100;
            physics->on_ground = 0;
        }
        physics->jump_held = jump;

        /* Walk horizontally. Left and right together cancel each other. */
        const int32_t left = (joypad & BTN_LEFT) != 0;
        const int32_t right = (joypad & BTN_RIGHT) != 0;
        const int32_t walk = physics->walk_speed > 0 ? physics->walk_speed : 0;
        const int32_t dx100 = (right - left) * walk * 100;
        const int32_t old_x = physics->x100 / 100;
        int32_t proposed_x100 = physics->x100 + dx100;
        int32_t new_x = proposed_x100 / 100;
        const int32_t old_y = physics->y100 / 100;

        /* Prevent moving through the sides of SOLID rectangles. */
        for (uint16_t i = 0; i < physics->platform_count; ++i) {
            const game_platform_t *p = &physics->platforms[i];
            if (!p->width || !p->height || p->type != GAME_PLATFORM_SOLID) continue;
            if (old_y + h <= p->y || old_y >= (int32_t)p->y + p->height) continue;

            if (dx100 > 0 && old_x + w <= p->x && new_x + w > p->x) {
                proposed_x100 = ((int32_t)p->x - w) * 100;
                new_x = proposed_x100 / 100;
            } else if (dx100 < 0 && old_x >= (int32_t)p->x + p->width &&
                       new_x < (int32_t)p->x + p->width) {
                proposed_x100 = ((int32_t)p->x + p->width) * 100;
                new_x = proposed_x100 / 100;
            }
        }
        physics->x100 = proposed_x100;

        /* Gravity adds a small amount of downward speed each frame. */
        const int32_t gravity = physics->gravity > 0 ? physics->gravity : 0;
        const int32_t max_fall = physics->max_fall_speed > 0
                               ? (int32_t)physics->max_fall_speed * 100 : 0;
        physics->vy100 += gravity;
        if (physics->vy100 > max_fall) physics->vy100 = max_fall;
        int32_t proposed_y100 = physics->y100 + physics->vy100;
        int32_t new_y = proposed_y100 / 100;
        physics->on_ground = 0;

        for (uint16_t i = 0; i < physics->platform_count; ++i) {
            const game_platform_t *p = &physics->platforms[i];
            if (!p->width || !p->height) continue;
            if (new_x + w <= p->x || new_x >= (int32_t)p->x + p->width) continue;

            /* Falling onto either kind of platform: stop at its top. */
            if (physics->vy100 >= 0 && old_y + h <= p->y &&
                new_y + h >= p->y) {
                proposed_y100 = ((int32_t)p->y - h) * 100;
                new_y = proposed_y100 / 100;
                physics->vy100 = 0;
                physics->on_ground = 1;
            }
            /* SOLID ceilings block upward movement; ONE-WAY ones don't. */
            else if (physics->vy100 < 0 && p->type == GAME_PLATFORM_SOLID &&
                     old_y >= (int32_t)p->y + p->height &&
                     new_y <= (int32_t)p->y + p->height) {
                proposed_y100 = ((int32_t)p->y + p->height) * 100;
                new_y = proposed_y100 / 100;
                physics->vy100 = 0;
            }
        }
        physics->y100 = proposed_y100;

        /* gfxbob_t uses signed 16-bit draw positions. Stay in that range. */
        if (physics->x100 < -3276800) physics->x100 = -3276800;
        if (physics->x100 > 3276700) physics->x100 = 3276700;
        if (physics->y100 < -3276800) { physics->y100 = -3276800; physics->vy100 = 0; }
        if (physics->y100 > 3276700) { physics->y100 = 3276700; physics->vy100 = 0; }
        sprite->drawx = (int16_t)(physics->x100 / 100);
        sprite->drawy = (int16_t)(physics->y100 / 100);
    }
}
