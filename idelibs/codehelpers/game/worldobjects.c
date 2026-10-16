#include "worldobjects.h"

static int16_t clamp16(int64_t x)
{
    return (int16_t)(x < -32768 ? -32768 : x > 32767 ? 32767 : x);
}

uint8_t game_world_object_start(game_world_object_t *object, uint8_t type,
                                gfxbob_t *sprite, int32_t x, int32_t y,
                                uint16_t width, uint16_t height)
{
    if (!object || type < GAME_OBJECT_LIFT || type > GAME_OBJECT_SPRING ||
        !width || !height) return 0;
    object->sprite = sprite;
    object->animation = 0;
    object->spline = 0;
    object->x = x;
    object->y = y;
    object->previous_x = x;
    object->previous_y = y;
    object->width = width;
    object->height = height;
    object->type = type;
    object->conveyor_speed = 0;
    object->spring_strength = 10;
    object->active = 1;
    if (sprite) {
        sprite->drawx = clamp16(x);
        sprite->drawy = clamp16(y);
    }
    return 1;
}

void game_world_object_set_position(game_world_object_t *object, int32_t x, int32_t y)
{
    if (!object) return;
    if (object->spline && object->sprite) {
        set_spline_pos(object->spline, clamp16(x), clamp16(y));
        object->x = object->sprite->drawx;
        object->y = object->sprite->drawy;
    } else {
        object->x = x;
        object->y = y;
        if (object->sprite) {
            object->sprite->drawx = clamp16(x);
            object->sprite->drawy = clamp16(y);
        }
    }
}

void game_world_objects_update(game_world_object_t *objects, uint16_t count,
                                uint16_t frames)
{
    if (!objects || !frames) return;
    for (uint16_t i = 0; i < count; ++i) {
        game_world_object_t *object = &objects[i];
        if (!object->active) continue;
        object->previous_x = object->x;
        object->previous_y = object->y;
        if (object->spline && object->sprite) {
            run_spline(object->spline, frames);
            object->x = object->sprite->drawx;
            object->y = object->sprite->drawy;
        }
        if (object->animation) run_animation(object->animation, frames);
    }
}

/* All positions are in WORLD coordinates.  Physics and platform splines
   advance once per frame. Capture the *original* player position before
   carrying them, because landing tests need both endpoints of the motion. */
void game_world_objects_before(const game_world_object_t *objects, uint16_t count,
                               game_world_player_t *p)
{
    if (!p || !p->x100 || !p->y100 || !p->vy100 || !p->on_ground ||
        !p->width || !p->height) return;
    p->ready = 1;
    const int32_t x = *p->x100 / 100;
    const int32_t feet = *p->y100 / 100 + p->height;
    p->before_x = x;
    p->before_feet = feet;
    /* Carry on one supporting surface only; never add platform deltas twice.
       Capture the pre-carry coordinates above for swept collisions below. */
    if (objects && *p->on_ground && *p->vy100 >= 0) {
        for (uint16_t i = 0; i < count; ++i) {
            const game_world_object_t *o = &objects[i];
            if (!o->active || feet != o->previous_y ||
                (int64_t)x + p->width <= o->previous_x ||
                x >= (int64_t)o->previous_x + o->width) continue;
            *p->x100 += (o->x - o->previous_x) * 100;
            *p->y100 += (o->y - o->previous_y) * 100;
            break;
        }
    }
}

/* Swept one-way platform collision: evaluate the player's feet and the
   platform TOP at the start AND end of the frame. Their relative motion must
   cross zero from above; a rising platform can meet a falling player between
   frames, even when neither endpoint happens to overlap.

   X overlap is tested at the same crossing time, not just at frame end. This
   avoids landing on a lift that passed sideways underneath the player. */
void game_world_objects_after(const game_world_object_t *objects, uint16_t count,
                              game_world_player_t *p)
{
    if (!p || !p->ready || !p->x100 || !p->y100 || !p->vy100 ||
        !p->on_ground || !p->width || !p->height) return;
    p->ready = 0;
    if (!objects || *p->vy100 < 0) return; /* Rising: one-way top only. */
    const int32_t x = *p->x100 / 100;
    const int32_t feet = *p->y100 / 100 + p->height;
    const game_world_object_t *best = 0;
    int64_t best_n = 0, best_d = 1;
    for (uint16_t i = 0; i < count; ++i) {
        const game_world_object_t *o = &objects[i];
        if (!o->active || !o->width || !o->height) continue;
        const int64_t start = (int64_t)p->before_feet - o->previous_y;
        const int64_t end = (int64_t)feet - o->y;
        if (start > 0 || end < 0) continue;
        /* Collision time t = n/d, 0 <= t <= 1.
           For a player already resting on the old top, use t=1 so X is
           checked at the NEW position after being carried. */
        int64_t n = -start;
        int64_t d = end - start;
        if (d == 0) { n = 1; d = 1; }
        else if (n == 0) { n = d; }
        const int64_t player_at_x = (int64_t)p->before_x * (d - n) + (int64_t)x * n;
        const int64_t object_at_x = (int64_t)o->previous_x * (d - n) + (int64_t)o->x * n;
        if (player_at_x + (int64_t)p->width * d <= object_at_x ||
            player_at_x >= object_at_x + (int64_t)o->width * d) continue;
        if (!best || n * best_d < best_n * d ||
            (n * best_d == best_n * d && o->y < best->y)) {
            best = o;
            best_n = n;
            best_d = d;
        }
    }
    if (!best) return;
    *p->y100 = (best->y - p->height) * 100;
    if (best->type == GAME_OBJECT_SPRING) {
        const int32_t strength = best->spring_strength > 0 ? best->spring_strength : 10;
        *p->vy100 = -strength * 100;
        *p->on_ground = 0;
    } else {
        *p->vy100 = 0;
        *p->on_ground = 1;
        if (best->type == GAME_OBJECT_CONVEYOR)
            *p->x100 += (int32_t)best->conveyor_speed * 100;
    }
}

void game_world_objects_draw(const game_world_object_t *objects, uint16_t count,
                              int32_t cx, int32_t cy)
{
    if (!objects) return;
    for (uint16_t i = 0; i < count; ++i) {
        const game_world_object_t *object = &objects[i];
        if (!object->active || !object->sprite) continue;
        gfxbob_t visible = *object->sprite;
        visible.drawx = clamp16((int64_t)object->x - cx);
        visible.drawy = clamp16((int64_t)object->y - cy);
        gfx_drawbob(&visible);
    }
}
