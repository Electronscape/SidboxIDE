#include "worldobjects.h"

static int16_t clamp16(int64_t x)
{
    return (int16_t)(x < -32768 ? -32768 : x > 32767 ? 32767 : x);
}

uint8_t game_world_object_start(game_world_object_t *object, uint8_t type,
                                gfxbob_t *sprite, int32_t x, int32_t y,
                                uint16_t width, uint16_t height)
{
    if (!object || type < GAME_OBJECT_LIFT || type > GAME_OBJECT_DEATH_ZONE ||
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
    object->spring_launch_x = 0; /* Default remains a straight-up bounce. */
    object->allow_jump_boost = 0; /* Explicit opt-in only: avoid surprise super-jumps. */
    object->touch_activation = 0; /* Existing springs always use landing behaviour. */
    object->spring_slide = 0; /* Existing springs keep constant-speed kickback. */
    object->spring_touching = 0;
    object->active = 1;
    object->spring_triggered = 0;
    object->trigger_press = 0;
    object->trigger_one_shot = 0;
    object->trigger_touching = 0;
    object->trigger_pressed = 0;
    object->trigger_fired = 0;
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
        object->spring_triggered = 0;
        if (!object->active) { object->spring_touching = 0; continue; }
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
    p->before_vy100 = *p->vy100;
    p->before_jump_held = p->jump_held ? *p->jump_held : 0;

    /* Spring sideways velocity is in addition to joystick movement.
       Default (OFF) deliberately retains Stage 3.20's exact behaviour:
       constant X speed while airborne, stopped immediately on landing.
       Inertia (ON) applies an independent impulse: air drag 6%/frame,
       ground drag 14%/frame. The last subpixel fraction is accumulated,
       since the tilemap player snaps X to whole pixels each frame.
       A solid wall cancels the push in either mode. */
    if (*p->on_ground && !p->spring_sliding) {
        p->spring_x100 = 0;
        p->spring_remainder_x100 = 0;
    } else if (p->spring_x100 != 0) {
        int32_t dx;
        if (p->spring_sliding) {
            const int32_t distance100 = p->spring_x100 + p->spring_remainder_x100;
            dx = distance100 / 100;
            p->spring_remainder_x100 = distance100 - dx * 100;
        } else {
            dx = p->spring_x100 / 100;
        }
        const int32_t step = (dx > 0) - (dx < 0);
        const int64_t pixels = dx < 0 ? -(int64_t)dx : (int64_t)dx;
        int32_t moved = 0;
        for (int64_t n = 0; n < pixels; ++n) {
            if (p->position_blocked &&
                p->position_blocked(x + moved + step, *p->y100 / 100,
                                    p->width, p->height, p->collision_context)) {
                p->spring_x100 = 0; /* Solid walls absorb momentum. */
                p->spring_remainder_x100 = 0;
                break;
            }
            moved += step;
        }
        *p->x100 += moved * 100;
        if (p->spring_sliding && p->spring_x100) {
            /* Integer drag keeps this STM32-friendly and frame-based.
               Ground friction is stronger than airborne drag. */
            p->spring_x100 = (p->spring_x100 *
                              (*p->on_ground ? 86 : 94)) / 100;
            if (p->spring_x100 > -12 && p->spring_x100 < 12) {
                p->spring_x100 = 0;
                p->spring_remainder_x100 = 0;
                p->spring_sliding = 0;
            }
        }
    }
    /* Carry on one supporting surface only; never add platform deltas twice.
       Capture the pre-carry coordinates above for swept collisions below. */
    if (objects && *p->on_ground && *p->vy100 >= 0) {
        for (uint16_t i = 0; i < count; ++i) {
            const game_world_object_t *o = &objects[i];
            if (!o->active || o->type == GAME_OBJECT_TRIGGER ||
                o->type == GAME_OBJECT_DEATH_ZONE ||
                (o->type == GAME_OBJECT_SPRING && o->touch_activation) ||
                feet != o->previous_y ||
                (int64_t)x + p->width <= o->previous_x ||
                x >= (int64_t)o->previous_x + o->width) continue;
            /* Move the rider vertically with its platform, then apply the
               horizontal carry in 1-pixel steps. The ordinary player run()
               only checks joystick movement, not externally added offsets.
               Without these checks a horizontal lift can carry the player
               straight THROUGH a solid wall before tile collision runs. */
            const int32_t delta_y = o->y - o->previous_y;
            const int32_t delta_x = o->x - o->previous_x;
            int32_t new_y = *p->y100 / 100 + delta_y;
            if (!p->position_blocked ||
                !p->position_blocked(x, new_y, p->width, p->height,
                                     p->collision_context))
                *p->y100 += delta_y * 100;
            else
                new_y = *p->y100 / 100;
            if (!p->position_blocked) {
                *p->x100 += delta_x * 100;
            } else {
                const int32_t step = (delta_x > 0) - (delta_x < 0);
                int32_t carried_x = x;
                const int64_t distance = delta_x < 0 ? -(int64_t)delta_x :
                                         (int64_t)delta_x;
                for (int64_t n = 0; n < distance; ++n) {
                    if (p->position_blocked(carried_x + step, new_y,
                                            p->width, p->height,
                                            p->collision_context)) break;
                    carried_x += step;
                }
                *p->x100 += (carried_x - x) * 100;
            }
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
/* Handle ordinary top landings and optional any-side spring contacts.
   Touch springs sweep the player hitbox against the spring's moving hitbox,
   so a fast crossing does not slip through between frames. A contact latch
   stops repeated launches until the player has actually left the spring. */
void game_world_objects_after(game_world_object_t *objects, uint16_t count,
                              game_world_player_t *p)
{
    if (!p || !p->ready || !p->x100 || !p->y100 || !p->vy100 ||
        !p->on_ground || !p->width || !p->height) return;
    p->ready = 0;
    if (!objects) return;

    const uint8_t jumping_now = (uint8_t)(p->jump_held && *p->jump_held &&
                                          !p->before_jump_held);
    const uint8_t rising = (uint8_t)(*p->vy100 < 0);
    const int32_t x = *p->x100 / 100;
    const int32_t y = *p->y100 / 100;
    const int32_t feet = y + p->height;
    game_world_object_t *best = 0;
    uint8_t best_touch = 0;
    int64_t best_n = 0, best_d = 1;

    for (uint16_t i = 0; i < count; ++i) {
        game_world_object_t *o = &objects[i];
        if (!o->active || !o->width || !o->height) {
            o->spring_touching = 0;
            continue;
        }
        // Switches are intangible: they never behave like a platform.
        if (o->type == GAME_OBJECT_TRIGGER || o->type == GAME_OBJECT_DEATH_ZONE) continue;
        // Door collision is resolved below, before the old one-way platform
        // rules. Only this new type uses blocking on all four sides.
        if (o->type == GAME_OBJECT_DOOR) {
            const int32_t old_x = p->before_x;
            const int32_t old_y = p->before_feet - p->height;
            const int64_t ox2 = (int64_t)o->x + o->width;
            const int64_t oy2 = (int64_t)o->y + o->height;
            if ((int64_t)x < ox2 && (int64_t)x + p->width > o->x &&
                (int64_t)y < oy2 && (int64_t)y + p->height > o->y) {
                if ((int64_t)old_x + p->width <= o->x) *p->x100 = (o->x - p->width) * 100;
                else if (old_x >= ox2) *p->x100 = (int32_t)ox2 * 100;
                else if ((int64_t)old_y + p->height <= o->y) {
                    *p->y100 = (o->y - p->height) * 100;
                    *p->vy100 = 0; *p->on_ground = 1;
                } else if (old_y >= oy2) {
                    *p->y100 = (int32_t)oy2 * 100;
                    if (*p->vy100 < 0) *p->vy100 = 0;
                }
                p->spring_x100 = 0; p->spring_remainder_x100 = 0;
                p->spring_sliding = 0;
            }
            continue;
        }

        if (o->type == GAME_OBJECT_SPRING && o->touch_activation) {
            /* Inclusive edges count as touch. This also detects a spring
               moving into a stationary player. The per-axis swept test uses
               relative player/object movement from the same frame. */
            const uint8_t touching_now = (uint8_t)(
                (int64_t)x <= (int64_t)o->x + o->width &&
                (int64_t)x + p->width >= o->x &&
                (int64_t)y <= (int64_t)o->y + o->height &&
                (int64_t)y + p->height >= o->y);
            const uint8_t already_touching = o->spring_touching;
            o->spring_touching = touching_now;
            if (already_touching) continue;

            /* Time of entry/exit in millionths of a game frame.
               Integer arithmetic avoids floating point on the STM32. */
            const int64_t scale = 1000000;
            int64_t entry = 0, exit = scale;
            const int64_t start[2] = {
                (int64_t)p->before_x - o->previous_x,
                (int64_t)p->before_feet - p->height - o->previous_y
            };
            const int64_t end[2] = {
                (int64_t)x - o->x, (int64_t)y - o->y
            };
            const int64_t lower[2] = { -(int64_t)p->width, -(int64_t)p->height };
            const int64_t upper[2] = { o->width, o->height };
            uint8_t hit = 1;
            for (uint8_t axis = 0; axis < 2; ++axis) {
                const int64_t delta = end[axis] - start[axis];
                if (!delta) {
                    if (start[axis] < lower[axis] || start[axis] > upper[axis]) {
                        hit = 0;
                        break;
                    }
                    continue;
                }
                const int64_t distance = delta > 0 ? delta : -delta;
                const int64_t enter_distance = delta > 0 ?
                    lower[axis] - start[axis] : start[axis] - upper[axis];
                const int64_t exit_distance = delta > 0 ?
                    upper[axis] - start[axis] : start[axis] - lower[axis];
                /* Round entry UP and exit DOWN to avoid false hits. */
                const int64_t axis_entry = enter_distance <= 0 ? 0 :
                    (enter_distance * scale + distance - 1) / distance;
                const int64_t axis_exit = exit_distance < 0 ? -1 :
                    (exit_distance * scale) / distance;
                if (axis_entry > entry) entry = axis_entry;
                if (axis_exit < exit) exit = axis_exit;
                if (entry > exit) { hit = 0; break; }
            }
            if (!hit) continue;
            if (!best || entry * best_d < best_n * scale ||
                (entry * best_d == best_n * scale && !best_touch)) {
                best = o;
                best_touch = 1;
                best_n = entry;
                best_d = scale;
            }
            continue; /* Touch springs never behave as standing platforms. */
        }

        /* The old one-way landing rules remain unchanged for normal
           springs, moving lifts and conveyors. */
        if (rising && !jumping_now) continue;
        const int64_t start = (int64_t)p->before_feet - o->previous_y;
        const int64_t end = (int64_t)feet - o->y;
        const uint8_t spring_jump_contact = (uint8_t)(
            rising && jumping_now && p->before_vy100 >= 0 &&
            o->type == GAME_OBJECT_SPRING && start == 0);
        if (!spring_jump_contact && (rising || start > 0 || end < 0)) continue;
        int64_t n = spring_jump_contact ? 0 : -start;
        int64_t d = spring_jump_contact ? 1 : end - start;
        if (d == 0) { n = 1; d = 1; }
        else if (n == 0 && !spring_jump_contact) { n = d; }
        const int64_t player_at_x = (int64_t)p->before_x * (d - n) + (int64_t)x * n;
        const int64_t object_at_x = (int64_t)o->previous_x * (d - n) + (int64_t)o->x * n;
        if (player_at_x + (int64_t)p->width * d <= object_at_x ||
            player_at_x >= object_at_x + (int64_t)o->width * d) continue;
        if (!best || n * best_d < best_n * d ||
            (n * best_d == best_n * d && !best_touch && o->y < best->y)) {
            best = o;
            best_touch = 0;
            best_n = n;
            best_d = d;
        }
    }
    if (!best) return;
    /* Side/underside contact must NOT teleport the player onto the top. */
    if (!best_touch) *p->y100 = (best->y - p->height) * 100;
    if (best->type == GAME_OBJECT_SPRING) {
        best->spring_triggered = 1; /* Exactly one sound event per launch. */
        int32_t launch = best->spring_strength > 0 ? best->spring_strength : 10;
        if (best->allow_jump_boost && p->jump_held && p->jump_speed &&
            !p->before_jump_held && *p->jump_held && *p->jump_speed > 0)
            launch += *p->jump_speed;
        *p->vy100 = -launch * 100;
        p->spring_x100 = (int32_t)best->spring_launch_x * 100;
        p->spring_sliding = best->spring_slide;
        p->spring_remainder_x100 = 0;
        *p->on_ground = 0;
        if (p->coyote) *p->coyote = 0;
    } else {
        /* Sliding momentum survives a lift/conveyor landing. */
        if (!p->spring_sliding) p->spring_x100 = 0;
        *p->vy100 = 0;
        *p->on_ground = 1;
        if (best->type == GAME_OBJECT_CONVEYOR)
            *p->x100 += (int32_t)best->conveyor_speed * 100;
    }
}

/* Death Zones are sensors, not solid objects or standing surfaces. */
uint8_t game_world_objects_death_zone(const game_world_object_t *objects,
                                      uint16_t count, int32_t x, int32_t y,
                                      uint16_t w, uint16_t h)
{
    if (!objects || !w || !h) return 0;
    for (uint16_t i = 0; i < count; ++i) {
        const game_world_object_t *o = &objects[i];
        if (!o->active || o->type != GAME_OBJECT_DEATH_ZONE ||
            !o->width || !o->height) continue;
        if ((int64_t)x < (int64_t)o->x + o->width &&
            (int64_t)x + w > o->x &&
            (int64_t)y < (int64_t)o->y + o->height &&
            (int64_t)y + h > o->y) return 1;
    }
    return 0;
}

uint16_t game_world_objects_trigger(game_world_object_t *objects, uint16_t count,
                                    int32_t x, int32_t y, uint16_t w, uint16_t h,
                                    uint8_t pressed)
{
    if (!objects || !w || !h) return 0;
    uint16_t fired = 0;
    for (uint16_t i = 0; i < count; ++i) {
        game_world_object_t *o = &objects[i];
        o->trigger_fired = 0;
        if (o->type != GAME_OBJECT_TRIGGER) continue;
        if (!o->active) {
            o->trigger_touching = 0;
            o->trigger_pressed = !!pressed;
            continue;
        }
        const uint8_t touching = (uint8_t)(
            (int64_t)x < (int64_t)o->x + o->width &&
            (int64_t)x + w > o->x &&
            (int64_t)y < (int64_t)o->y + o->height &&
            (int64_t)y + h > o->y);
        const uint8_t activate = o->trigger_press
            ? (uint8_t)(touching && pressed && !o->trigger_pressed)
            : (uint8_t)(touching && !o->trigger_touching);
        o->trigger_pressed = !!pressed;
        o->trigger_touching = touching;
        if (!activate) continue;
        o->trigger_fired = 1;
        ++fired;
        if (o->trigger_one_shot) o->active = 0;
    }
    return fired;
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
