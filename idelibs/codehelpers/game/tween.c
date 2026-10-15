#include "gametween.h"

void start_tween(game_tween_t *tween, gfxbob_t *sprite,
                 int16_t x, int16_t y, uint16_t duration_frames, uint8_t loop)
{
    if (!tween) return;
    tween->sprite = sprite;
    tween->active = 0;
    if (!sprite) return;
    tween->from_x = sprite->drawx;
    tween->from_y = sprite->drawy;
    tween->to_x = x;
    tween->to_y = y;
    tween->duration_frames = duration_frames;
    tween->elapsed_frames = 0;
    tween->loop = loop ? 1 : 0;
    if (!duration_frames) {
        sprite->drawx = x;
        sprite->drawy = y;
        return;
    }
    tween->active = 1;
}

void run_tween(game_tween_t *tween, uint16_t frame_step)
{
    if (!tween || !tween->active || !tween->sprite || !frame_step) return;
    const uint32_t next = (uint32_t)tween->elapsed_frames + frame_step;
    const uint32_t duration = tween->duration_frames;
    uint32_t frame;
    if (tween->loop) {
        // Frames 1..duration, so the destination is shown for a full frame.
        frame = ((next - 1u) % duration) + 1u;
    } else {
        frame = next < duration ? next : duration;
    }
    tween->elapsed_frames = (uint16_t)frame;
    // 64-bit intermediates avoid overflow when interpolating 16-bit positions.
    tween->sprite->drawx = (int16_t)(tween->from_x +
        ((int64_t)tween->to_x - tween->from_x) * frame / duration);
    tween->sprite->drawy = (int16_t)(tween->from_y +
        ((int64_t)tween->to_y - tween->from_y) * frame / duration);
    if (!tween->loop && frame == duration) tween->active = 0;
}

void stop_tween(game_tween_t *tween)
{
    if (tween) tween->active = 0;
}
