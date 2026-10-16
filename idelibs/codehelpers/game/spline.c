#include "gamespline.h"

void start_spline(game_spline_t *path, gfxbob_t *sprite,
                  const game_spline_point_t *points, uint16_t point_count,
                  uint16_t duration_frames, uint8_t loop)
{
    if (!path) return;
    path->active = 0;
    path->sprite = sprite;
    path->points = points;
    path->point_count = point_count;
    path->duration_frames = duration_frames;
    path->elapsed_frames = 0;
    path->offset_x = 0;
    path->offset_y = 0;
    path->view_x = 0;
    path->view_y = 0;
    path->loop = loop ? 1 : 0;
    path->has_pauses = 0;
    path->finish_after_pause = 0;
    path->pause_remaining = 0;
    path->next_pause_index = 1;
    if (!sprite || !points || point_count < 2) return;
    for (uint16_t i = 0; i < point_count; ++i)
        if (points[i].pause_frames) path->has_pauses = 1;
    if (path->has_pauses) path->pause_remaining = points[0].pause_frames;
    sprite->drawx = points[0].x;
    sprite->drawy = points[0].y;
    if (!duration_frames) {
        if (!path->loop) {
            sprite->drawx = points[point_count - 1].x;
            sprite->drawy = points[point_count - 1].y;
        }
        return;
    }
    path->active = 1;
}

/* Draw a specific MOVEMENT frame. Pause time is counted separately, so
   holding at knots cannot slow the original Catmull-Rom travel speed. */
static void spline_draw_movement_frame(game_spline_t *path, uint32_t frame)
{
    const uint32_t duration = path->duration_frames;
    /* A completed closing segment of a loop wraps to the first point. */
    if (path->loop && frame >= duration) frame %= duration;
    if (!path->loop && frame == duration) {
        const int64_t final_x = (int64_t)path->points[path->point_count - 1].x + path->offset_x + path->view_x;
        const int64_t final_y = (int64_t)path->points[path->point_count - 1].y + path->offset_y + path->view_y;
        path->sprite->drawx = (int16_t)(final_x < -32768 ? -32768 : final_x > 32767 ? 32767 : final_x);
        path->sprite->drawy = (int16_t)(final_y < -32768 ? -32768 : final_y > 32767 ? 32767 : final_y);
        return;
    }

    /* Equal time for each segment, smooth Catmull-Rom interpolation.
     * All arithmetic is integer/fixed-point, no floating-point library.
     */
    const uint32_t segments = path->loop ? path->point_count : path->point_count - 1u;
    const uint32_t location = (uint32_t)((uint64_t)frame * segments * 4096u / duration);
    const uint32_t index = location / 4096u;
    const int64_t t = (int64_t)(location % 4096u);
    const int64_t t2 = (t * t) / 4096;
    const int64_t t3 = (t2 * t) / 4096;
    const uint32_t n = path->point_count;
    const uint32_t a = index > 0 ? index - 1u : (path->loop ? n - 1u : 0u);
    const uint32_t b = index;
    const uint32_t c = (index + 1u < n) ? index + 1u : (path->loop ? 0u : n - 1u);
    const uint32_t d = (index + 2u < n) ? index + 2u
                    : (path->loop ? (index + 2u) % n : n - 1u);

    for (uint32_t axis = 0; axis != 2; ++axis) {
        const int64_t p0 = axis ? path->points[a].y : path->points[a].x;
        const int64_t p1 = axis ? path->points[b].y : path->points[b].x;
        const int64_t p2 = axis ? path->points[c].y : path->points[c].x;
        const int64_t p3 = axis ? path->points[d].y : path->points[d].x;
        const int64_t value = (2 * p1 * 4096 + (-p0 + p2) * t
            + (2 * p0 - 5 * p1 + 4 * p2 - p3) * t2
            + (-p0 + 3 * p1 - 3 * p2 + p3) * t3) / (2 * 4096);
        const int64_t translated = value + (axis ? path->offset_y : path->offset_x)
                                         + (axis ? path->view_y : path->view_x);
        const int16_t pos = (int16_t)(translated < -32768 ? -32768
                                   : translated > 32767 ? 32767 : translated);
        if (axis) path->sprite->drawy = pos;
        else path->sprite->drawx = pos;
    }
}

void run_spline(game_spline_t *path, uint16_t frame_step)
{
    if (!path || !path->active || !path->sprite || !path->points
        || path->point_count < 2 || !path->duration_frames || !frame_step)
        return;


    const uint32_t duration = path->duration_frames;
    if (!path->has_pauses) {
        /* EXACTLY the original zero-pause timing and interpolation. */
        const uint32_t next = (uint32_t)path->elapsed_frames + frame_step;
        const uint32_t frame = path->loop ? (next % duration)
                                          : (next < duration ? next : duration);
        path->elapsed_frames = (uint16_t)frame;
        spline_draw_movement_frame(path, frame);
        if (!path->loop && frame == duration) path->active = 0;
        return;
    }

    /* Pause-aware path: traverse the SAME spline at its normal speed, but
       stop at each selected knot. Large frame_step values can cross several
       movements and pauses in one call (useful after skipped VBlanks). */
    const uint32_t segments = path->loop ? path->point_count : path->point_count - 1u;
    uint32_t remaining = frame_step;
    while (remaining && path->active) {
        if (path->pause_remaining) {
            const uint32_t held = remaining < path->pause_remaining
                                ? remaining : path->pause_remaining;
            path->pause_remaining -= (uint16_t)held;
            remaining -= held;
            if (!path->pause_remaining && path->finish_after_pause)
                path->active = 0;
            continue;
        }
        const uint32_t point = path->next_pause_index;
        /* ceil(point * duration / segments) prevents missing a knot when
           the journey length isn't divisible by the segment count. */
        const uint32_t boundary = (point * duration + segments - 1u) / segments;
        const uint32_t to_knot = boundary > path->elapsed_frames
                               ? boundary - path->elapsed_frames : 0u;
        if (to_knot) {
            const uint32_t advance = remaining < to_knot ? remaining : to_knot;
            path->elapsed_frames = (uint16_t)(path->elapsed_frames + advance);
            remaining -= advance;
            spline_draw_movement_frame(path, path->elapsed_frames);
            if (advance < to_knot) break;
        }
        /* We've arrived at a control point. Hold at its EXACT coordinates
           rather than a rounded interpolation fraction. */
        const uint32_t vertex = (path->loop && point == segments) ? 0u : point;
        const int64_t x = (int64_t)path->points[vertex].x + path->offset_x + path->view_x;
        const int64_t y = (int64_t)path->points[vertex].y + path->offset_y + path->view_y;
        path->sprite->drawx = (int16_t)(x < -32768 ? -32768 : x > 32767 ? 32767 : x);
        path->sprite->drawy = (int16_t)(y < -32768 ? -32768 : y > 32767 ? 32767 : y);
        path->pause_remaining = path->points[vertex].pause_frames;
        if (point == segments) {
            if (path->loop) {
                path->elapsed_frames = 0;
                path->next_pause_index = 1;
            } else {
                path->finish_after_pause = 1;
                if (!path->pause_remaining) path->active = 0;
            }
        } else {
            ++path->next_pause_index;
        }
    }
}

void stop_spline(game_spline_t *path)
{
    if (path) path->active = 0;
}

void set_spline_pos(game_spline_t *path, int16_t x, int16_t y)
{
    if (!path || !path->sprite || !path->points || path->point_count < 2) return;
    // Never modify the exported path points: other sprites may share them.
    const int32_t new_offset_x = (int32_t)x - path->points[0].x;
    const int32_t new_offset_y = (int32_t)y - path->points[0].y;
    const int64_t new_x = (int64_t)path->sprite->drawx
                        + (new_offset_x - path->offset_x);
    const int64_t new_y = (int64_t)path->sprite->drawy
                        + (new_offset_y - path->offset_y);
    path->offset_x = new_offset_x;
    path->offset_y = new_offset_y;
    path->sprite->drawx = (int16_t)(new_x < -32768 ? -32768
                                   : new_x > 32767 ? 32767 : new_x);
    path->sprite->drawy = (int16_t)(new_y < -32768 ? -32768
                                   : new_y > 32767 ? 32767 : new_y);
}

/* Give this spline an ABSOLUTE drawing offset relative to its world path.
   The previous drawing offset is REPLACED, not accumulated, making this safe
   to call every frame with (-camera_x, -camera_y). set_spline_pos() can still
   choose a different world start position independently of the camera.
   Exported control points and animation progress are never modified. */
void offset_spline(game_spline_t *path, int32_t x, int32_t y)
{
    if (!path || !path->sprite || !path->points || path->point_count < 2) return;

    const int64_t new_x = (int64_t)path->sprite->drawx + ((int64_t)x - path->view_x);
    const int64_t new_y = (int64_t)path->sprite->drawy + ((int64_t)y - path->view_y);
    path->view_x = x;
    path->view_y = y;
    path->sprite->drawx = (int16_t)(new_x < -32768 ? -32768
                                   : new_x > 32767 ? 32767 : new_x);
    path->sprite->drawy = (int16_t)(new_y < -32768 ? -32768
                                   : new_y > 32767 ? 32767 : new_y);
}
