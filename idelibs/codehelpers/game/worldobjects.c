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

void game_world_objects_before(const game_world_object_t *objects, uint16_t count,
                                game_world_player_t *p)
{
    if (!p || !p->x100 || !p->y100 || !p->vy100 || !p->on_ground ||
        !p->width || !p->height) return;
    p->ready = 1;
    int32_t x = *p->x100 / 100;
    int32_t feet = *p->y100 / 100 + p->height;
    /* Carry on one supporting surface only (never add deltas twice). */
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
    p->before_feet = *p->y100 / 100 + p->height;
}

void game_world_objects_after(const game_world_object_t *objects, uint16_t count,
                               game_world_player_t *p)
{
    if (!p || !p->ready || !p->x100 || !p->y100 || !p->vy100 ||
        !p->on_ground || !p->width || !p->height) return;
    p->ready = 0;
    if (!objects || *p->vy100 < 0) return;
    const int32_t x = *p->x100 / 100;
    const int32_t feet = *p->y100 / 100 + p->height;
    const game_world_object_t *best = 0;
    /* Choose the uppermost surface intersected this frame. A surface
       entered from below cannot support the player. */
    for (uint16_t i = 0; i < count; ++i) {
        const game_world_object_t *o = &objects[i];
        if (!o->active || o->width == 0 || o->height == 0 ||
            (int64_t)x + p->width <= o->x || x >= (int64_t)o->x + o->width ||
            p->before_feet > o->y || feet < o->y) continue;
        if (!best || o->y < best->y) best = o;
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
