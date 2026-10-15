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
    path->loop = loop ? 1 : 0;
    if (!sprite || !points || point_count < 2) return;
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

void run_spline(game_spline_t *path, uint16_t frame_step)
{
    if (!path || !path->active || !path->sprite || !path->points
        || path->point_count < 2 || !path->duration_frames || !frame_step)
        return;

    const uint32_t duration = path->duration_frames;
    const uint32_t next = (uint32_t)path->elapsed_frames + frame_step;
    const uint32_t frame = path->loop ? (next % duration)
                                      : (next < duration ? next : duration);
    path->elapsed_frames = (uint16_t)frame;
    if (!path->loop && frame == duration) {
        path->sprite->drawx = path->points[path->point_count - 1].x;
        path->sprite->drawy = path->points[path->point_count - 1].y;
        path->active = 0;
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
        const int16_t pos = (int16_t)(value < -32768 ? -32768
                                   : value > 32767 ? 32767 : value);
        if (axis) path->sprite->drawy = pos;
        else path->sprite->drawx = pos;
    }
}

void stop_spline(game_spline_t *path)
{
    if (path) path->active = 0;
}
