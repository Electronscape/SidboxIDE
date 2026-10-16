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
    tween->offset_x = 0;
    tween->offset_y = 0;
    tween->to_x = x;
    tween->to_y = y;
    tween->duration_frames = duration_frames;
    tween->elapsed_frames = 0;
    tween->loop = loop ? 1 : 0;
    tween->start_pause_frames = 0;
    tween->end_pause_frames = 0;
    tween->pause_remaining = 0;
    tween->phase = 1;
    if (!duration_frames) {
        sprite->drawx = x;
        sprite->drawy = y;
        return;
    }
    tween->active = 1;
}

void set_tween_pauses(game_tween_t *tween, uint16_t start_frames,
                      uint16_t end_frames)
{
    if (!tween) return;
    tween->start_pause_frames = start_frames;
    tween->end_pause_frames = end_frames;
    /* A newly started tween has not travelled yet. Do not rewind a moving
       tween when its pause settings are adjusted mid-journey. */
    if (tween->active && tween->elapsed_frames == 0 && tween->phase == 1) {
        tween->phase = 0;
        tween->pause_remaining = start_frames;
    }
}

void run_tween(game_tween_t *tween, uint16_t frame_step)
{
    if (!tween || !tween->active || !tween->sprite || !frame_step) return;
    if (!tween->start_pause_frames && !tween->end_pause_frames) {
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
    const int64_t x = (int64_t)tween->from_x + tween->offset_x
        + ((int64_t)tween->to_x - tween->from_x) * frame / duration;
    const int64_t y = (int64_t)tween->from_y + tween->offset_y
        + ((int64_t)tween->to_y - tween->from_y) * frame / duration;
    tween->sprite->drawx = (int16_t)(x < -32768 ? -32768 : x > 32767 ? 32767 : x);
    tween->sprite->drawy = (int16_t)(y < -32768 ? -32768 : y > 32767 ? 32767 : y);
    if (!tween->loop && frame == duration) tween->active = 0;
        return;
    }
    uint32_t remaining = frame_step;
    const uint32_t duration = tween->duration_frames;
    while (remaining && tween->active) {
        if (tween->phase == 0 || tween->phase == 2) {
            if (tween->pause_remaining) {
                const uint32_t held = remaining < tween->pause_remaining
                                      ? remaining : tween->pause_remaining;
                tween->pause_remaining -= (uint16_t)held;
                remaining -= held;
                /* The final held frame still displays the endpoint. Do not
                   jump to the other end until the NEXT game frame. */
                if (!tween->pause_remaining && tween->phase == 2 && !tween->loop)
                    tween->active = 0;
                continue;
            }
            if (tween->phase == 2) {
                if (!tween->loop) { tween->active = 0; break; }
                tween->elapsed_frames = 0;
                tween->sprite->drawx = (int16_t)((int64_t)tween->from_x + tween->offset_x);
                tween->sprite->drawy = (int16_t)((int64_t)tween->from_y + tween->offset_y);
                tween->phase = 0;
                tween->pause_remaining = tween->start_pause_frames;
            } else {
                tween->phase = 1;
            }
            continue;
        }
        const uint32_t until_end = duration - tween->elapsed_frames;
        const uint32_t advance = remaining < until_end ? remaining : until_end;
        tween->elapsed_frames = (uint16_t)(tween->elapsed_frames + advance);
        remaining -= advance;
        const uint32_t frame = tween->elapsed_frames;
        const int64_t x = (int64_t)tween->from_x + tween->offset_x
            + ((int64_t)tween->to_x - tween->from_x) * frame / duration;
        const int64_t y = (int64_t)tween->from_y + tween->offset_y
            + ((int64_t)tween->to_y - tween->from_y) * frame / duration;
        tween->sprite->drawx = (int16_t)(x < -32768 ? -32768 : x > 32767 ? 32767 : x);
        tween->sprite->drawy = (int16_t)(y < -32768 ? -32768 : y > 32767 ? 32767 : y);
        if (frame == duration) {
            tween->phase = 2;
            tween->pause_remaining = tween->end_pause_frames;
            if (!tween->loop && !tween->pause_remaining) tween->active = 0;
        }
    }
}

void stop_tween(game_tween_t *tween)
{
    if (tween) tween->active = 0;
}

void set_tween_pos(game_tween_t *tween, int16_t x, int16_t y)
{
    if (!tween || !tween->sprite) return;
    // The start point is the anchor; repositioning never restarts the timer.
    const int32_t new_offset_x = (int32_t)x - tween->from_x;
    const int32_t new_offset_y = (int32_t)y - tween->from_y;
    const int64_t new_x = (int64_t)tween->sprite->drawx
                        + (new_offset_x - tween->offset_x);
    const int64_t new_y = (int64_t)tween->sprite->drawy
                        + (new_offset_y - tween->offset_y);
    tween->offset_x = new_offset_x;
    tween->offset_y = new_offset_y;
    tween->sprite->drawx = (int16_t)(new_x < -32768 ? -32768
                                    : new_x > 32767 ? 32767 : new_x);
    tween->sprite->drawy = (int16_t)(new_y < -32768 ? -32768
                                    : new_y > 32767 ? 32767 : new_y);
}
