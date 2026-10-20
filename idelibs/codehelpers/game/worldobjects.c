#include "worldobjects.h"

static int16_t clamp16(int64_t x)
{
    return (int16_t)(x < -32768 ? -32768 : x > 32767 ? 32767 : x);
}

uint8_t game_world_object_start(game_world_object_t *object, uint8_t type,
                                gfxbob_t *sprite, int32_t x, int32_t y,
                                uint16_t width, uint16_t height)
{
    if (!object || type < GAME_OBJECT_LIFT || type > GAME_OBJECT_ENEMY ||
        !width || !height) return 0;
    object->sprite = sprite;
    object->animation = 0;
    object->spline = 0;
    object->spline_start_delay = 0;
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
    object->break_hits_required = 1;
    object->break_hits_done = 0;
    object->break_touch_mode = 0;
    object->break_bounce = 0;
    object->break_strength = 11;
    object->break_launch_x = 0;
    object->break_touching = 0;
    object->enemy_hurts_on_touch = 1;
    object->enemy_defeat_frame = -1;
    object->enemy_defeat_frames = 20;
    object->enemy_dying = 0;
    object->break_triggered = 0;
    object->break_hit_triggered = 0;
    object->break_bounce_triggered = 0;
    object->draw_behind_tiles = 0;
    object->hazard_damage = 1;
    object->hazard_kick_x = 0;
    object->hazard_kick_y = -11;
    object->hazard_kick = 1;
    object->hazard_hurt_animation = 1;
    object->hazard_flash = 1;
    object->hazard_flash_colour = 15;
    object->hazard_flash_count = 4;
    object->hazard_flash_frames = 3;
    object->hazard_touching = 0;
    object->hazard_hit_triggered = 0;
    object->hazard_bounce_triggered = 0;
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
        object->break_triggered = 0;
        object->break_hit_triggered = 0;
        object->break_bounce_triggered = 0;
        object->hazard_hit_triggered = 0;
        object->hazard_bounce_triggered = 0;
        if (!object->active) {
            if (object->type == GAME_OBJECT_ENEMY && object->enemy_dying) {
                object->enemy_dying = frames >= object->enemy_dying
                    ? 0 : (uint8_t)(object->enemy_dying - frames);
            }
            object->spring_touching = 0;
            object->break_touching = 0;
            object->hazard_touching = 0;
            continue;
        }
        object->previous_x = object->x;
        object->previous_y = object->y;
        if (object->spline && object->sprite) {
            /* Consume the delay without advancing this object's path.
               A multi-frame update may end the wait partway through, so
               advance ONLY the remaining frames after the countdown. */
            uint16_t move_frames = frames;
            if (object->spline_start_delay) {
                const uint16_t waiting = object->spline_start_delay < move_frames
                    ? object->spline_start_delay : move_frames;
                object->spline_start_delay -= waiting;
                move_frames -= waiting;
            }
            if (move_frames) run_spline(object->spline, move_frames);
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
    const int32_t x = *p->x100 / 100 + p->offset_x;
    const int32_t feet = *p->y100 / 100 + p->offset_y + p->height;
    p->before_x = x;
    p->before_feet = feet;
    p->before_vy100 = *p->vy100;
    p->before_jump_held = p->jump_held ? *p->jump_held : 0;
    p->hurt_triggered = 0;
    p->hurt_damage_this_frame = 0;
    if (p->hurt_ticks_remaining) {
        --p->hurt_ticks_remaining;
        ++p->hurt_elapsed;
    }
    if (!p->hurt_ticks_remaining) {
        p->hurt_anim_active = 0;
        p->hurt_flash_active = 0;
    }

    /* Legacy sideways spring movement for standalone platformers and for
       NON-SLIDY springs. Tilemap SLIDY springs with spring_force_vx100
       bound instead use the tilemap's normal external-force solver and
       current physics-mode drag (ICE, WATER, SPACE, etc.). This legacy
       path retains original airborne/grounded damping for old projects. */
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
                p->position_blocked(x + moved + step, *p->y100 / 100 + p->offset_y,
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
                o->type == GAME_OBJECT_HAZARD ||
                o->type == GAME_OBJECT_ENEMY ||
                (o->type == GAME_OBJECT_SPRING && o->touch_activation) ||
                (o->type == GAME_OBJECT_BREAKABLE && o->break_touch_mode) ||
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
            int32_t new_y = *p->y100 / 100 + p->offset_y + delta_y;
            if (!p->position_blocked ||
                !p->position_blocked(x, new_y, p->width, p->height,
                                     p->collision_context))
                *p->y100 += delta_y * 100;
            else
                new_y = *p->y100 / 100 + p->offset_y;
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
    /* The tile player sets jump_held on a new press and changes vy100 to
       negative ONLY when the jump is allowed. Remember that takeoff across
       subsequent frames: the FIRE button will often be released by landing.
       An ordinary fall, walking onto a platform, or a spring launch without
       a new jump press must not masquerade as an intentional stomp. */
    const uint8_t deliberate_takeoff = (uint8_t)(jumping_now && rising &&
                                                   p->before_vy100 >= 0 &&
                                                   !*p->on_ground);
    if (*p->on_ground) p->break_stomp_armed = 0;
    if (deliberate_takeoff) p->break_stomp_armed = 1;
    const int32_t x = *p->x100 / 100 + p->offset_x;
    const int32_t y = *p->y100 / 100 + p->offset_y;
    const int32_t feet = y + p->height;
    game_world_object_t *best = 0;
    uint8_t best_touch = 0;
    int64_t best_n = 0, best_d = 1;

    for (uint16_t i = 0; i < count; ++i) {
        game_world_object_t *o = &objects[i];
        if (!o->active || !o->width || !o->height) {
            o->spring_touching = 0;
            o->break_touching = 0;
            continue;
        }
        if ((o->type == GAME_OBJECT_BREAKABLE || o->type == GAME_OBJECT_ENEMY) && o->break_touching) {
            /* A hit only rearms once the player's bounds have separated. */
            const uint8_t still_touching = (uint8_t)(
                (int64_t)x <= (int64_t)o->x + o->width &&
                (int64_t)x + p->width >= o->x &&
                (int64_t)y <= (int64_t)o->y + o->height &&
                (int64_t)y + p->height >= o->y);
            if (!still_touching) o->break_touching = 0;
        }
        /* Head-butt blocks register a fresh upward crossing of their underside.
           The jump must be deliberate, not a spike/spring knockback or fall.
           Reset the armed jump here: a second hit requires a NEW jump. */
        if (o->type == GAME_OBJECT_BREAKABLE && o->break_from_below &&
            !o->break_touching && p->break_stomp_armed) {
            const int32_t old_top = p->before_feet - p->height;
            const int64_t old_bottom = (int64_t)o->previous_y + o->height;
            const int64_t new_bottom = (int64_t)o->y + o->height;
            if (old_top >= old_bottom && y <= new_bottom && y < old_top &&
                (int64_t)x < (int64_t)o->x + o->width &&
                (int64_t)x + p->width > o->x) {
                o->break_touching = 1;
                if (o->break_hits_done < 255) ++o->break_hits_done;
                o->break_hit_triggered = 1;
                if (o->break_hits_done >= (o->break_hits_required
                        ? o->break_hits_required : 1)) {
                    o->break_triggered = 1;
                    o->active = 0;
                }
                *p->y100 = ((int32_t)new_bottom - p->offset_y) * 100;
                if (*p->vy100 < 0) *p->vy100 = 0;
                *p->on_ground = 0;
                p->break_stomp_armed = 0;
                return;
            }
        }
        // Switches are intangible: they never behave like a platform.
        if (o->type == GAME_OBJECT_TRIGGER || o->type == GAME_OBJECT_DEATH_ZONE ||
            o->type == GAME_OBJECT_HAZARD) continue;
        // Door collision is resolved below, before the old one-way platform
        // rules. Only this new type uses blocking on all four sides.
        if (o->type == GAME_OBJECT_DOOR) {
            const int32_t old_x = p->before_x;
            const int32_t old_y = p->before_feet - p->height;
            const int64_t ox2 = (int64_t)o->x + o->width;
            const int64_t oy2 = (int64_t)o->y + o->height;
            if ((int64_t)x < ox2 && (int64_t)x + p->width > o->x &&
                (int64_t)y < oy2 && (int64_t)y + p->height > o->y) {
                if ((int64_t)old_x + p->width <= o->x) *p->x100 = (o->x - p->width - p->offset_x) * 100;
                else if (old_x >= ox2) *p->x100 = ((int32_t)ox2 - p->offset_x) * 100;
                else if ((int64_t)old_y + p->height <= o->y) {
                    *p->y100 = (o->y - p->height - p->offset_y) * 100;
                    *p->vy100 = 0; *p->on_ground = 1;
                } else if (old_y >= oy2) {
                    *p->y100 = ((int32_t)oy2 - p->offset_y) * 100;
                    if (*p->vy100 < 0) *p->vy100 = 0;
                }
                p->spring_x100 = 0; p->spring_remainder_x100 = 0;
                p->spring_sliding = 0;
            }
            continue;
        }

        if ((o->type == GAME_OBJECT_SPRING && o->touch_activation) ||
            (o->type == GAME_OBJECT_BREAKABLE && o->break_touch_mode)) {
            /* Inclusive edges count as touch. This also detects a spring
               moving into a stationary player. The per-axis swept test uses
               relative player/object movement from the same frame. */
            const uint8_t touching_now = (uint8_t)(
                (int64_t)x <= (int64_t)o->x + o->width &&
                (int64_t)x + p->width >= o->x &&
                (int64_t)y <= (int64_t)o->y + o->height &&
                (int64_t)y + p->height >= o->y);
            const uint8_t already_touching = o->type == GAME_OBJECT_BREAKABLE
                ? o->break_touching : o->spring_touching;
            if (o->type == GAME_OBJECT_SPRING) o->spring_touching = touching_now;
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
    if (!best_touch) *p->y100 = (best->y - p->height - p->offset_y) * 100;
    if (best->type == GAME_OBJECT_BREAKABLE || best->type == GAME_OBJECT_ENEMY) {
        /* Touch-mode counts a fresh contact from any direction. Stomp-mode
           counts ONLY a landing following an actual player jump; gravity
           alone is not an attack. A non-stomping landing is still solid. */
        const uint8_t valid_hit = (uint8_t)(best->type == GAME_OBJECT_ENEMY
            ? (!best_touch && !rising) : (!best->break_from_below &&
            (best_touch || p->break_stomp_armed)));
        if (valid_hit && !best->break_touching) {
            best->break_touching = 1;
            if (best->type == GAME_OBJECT_ENEMY) best->hazard_touching = 1;
            if (best->break_hits_done < 255) ++best->break_hits_done;
            best->break_hit_triggered = 1; /* A valid hit, including the final break. */
            if (best->break_hits_done >= (best->break_hits_required
                    ? best->break_hits_required : 1)) {
                best->break_triggered = 1;
                best->active = 0; /* Collision disappears immediately. */
                if (best->type == GAME_OBJECT_ENEMY && best->sprite &&
                    best->enemy_defeat_frame >= 0 && best->enemy_defeat_frames) {
                    best->sprite->index = (uint8_t)best->enemy_defeat_frame;
                    best->enemy_dying = best->enemy_defeat_frames;
                }
            }
        }
        if (!best_touch && valid_hit && best->break_bounce && !best->break_touch_mode) {
            best->break_bounce_triggered = 1; /* A real bounce, never mere contact. */
            *p->vy100 = -(int32_t)(best->break_strength > 0 ? best->break_strength : 11) * 100;
            *p->on_ground = 0;
            if (p->coyote) *p->coyote = 0;
            if (p->spring_force_vx100) {
                int64_t vx = (int64_t)*p->spring_force_vx100 +
                             (int64_t)best->break_launch_x * 100;
                if (vx > 3200) vx = 3200;
                if (vx < -3200) vx = -3200;
                *p->spring_force_vx100 = (int32_t)vx;
            } else {
                p->spring_x100 = (int32_t)best->break_launch_x * 100;
            }
        } else if (!best_touch) {
            /* Walking/falling onto a breakable is a normal landing. An
               unbounced successful stomp consumes the intentional jump. */
            *p->vy100 = 0;
            *p->on_ground = !best->break_triggered;
            p->break_stomp_armed = 0;
        }
    } else if (best->type == GAME_OBJECT_SPRING) {
        best->spring_triggered = 1; /* Exactly one sound event per launch. */
        int32_t launch = best->spring_strength > 0 ? best->spring_strength : 10;
        if (best->allow_jump_boost && p->jump_held && p->jump_speed &&
            !p->before_jump_held && *p->jump_held && *p->jump_speed > 0)
            launch += *p->jump_speed;
        *p->vy100 = -launch * 100;
        if (best->spring_slide && p->spring_force_vx100) {
            /* Share the tilemap player's external velocity with wind and
               apply_force(): all use the same wall collisions and the
               currently selected preset drag. A new spring adds its impulse
               rather than resetting momentum already in flight. Clamp to
               the same +/-32 px/frame range as apply_force(). */
            int64_t v = (int64_t)*p->spring_force_vx100 +
                        (int64_t)best->spring_launch_x * 100;
            if (v > 3200) v = 3200;
            if (v < -3200) v = -3200;
            *p->spring_force_vx100 = (int32_t)v;
            p->spring_x100 = 0;
            p->spring_remainder_x100 = 0;
            p->spring_sliding = 0;
        } else {
            /* Non-slidy launches and legacy adapters keep their original
               behaviour, so older games and platformers aren't changed. */
            p->spring_x100 = (int32_t)best->spring_launch_x * 100;
            p->spring_sliding = best->spring_slide;
            p->spring_remainder_x100 = 0;
        }
        *p->on_ground = 0;
        if (p->coyote) *p->coyote = 0;
    } else {
        /* Sliding momentum survives a lift/conveyor landing. */
        if (!p->spring_sliding) p->spring_x100 = 0;
        *p->vy100 = 0;
        *p->on_ground = 1;
        p->break_stomp_armed = 0;
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

/* Relative swept axis-aligned rectangle check. Both player AND hazard can
   move during the frame. Inclusive edges make thin spikes reliable at speed. */
static uint8_t hazard_swept_contact(const game_world_player_t *p,
                                    const game_world_object_t *o,
                                    int32_t x, int32_t y)
{
    const int64_t start[2] = {(int64_t)p->before_x - o->previous_x,
                              (int64_t)p->before_feet - p->height - o->previous_y};
    const int64_t end[2] = {(int64_t)x - o->x, (int64_t)y - o->y};
    const int64_t low[2] = {-(int64_t)p->width, -(int64_t)p->height};
    const int64_t high[2] = {o->width, o->height};
    const int64_t scale = 1000000;
    int64_t entry = 0, exit = scale;
    for (uint8_t axis = 0; axis < 2; ++axis) {
        const int64_t delta = end[axis] - start[axis];
        if (!delta) {
            if (start[axis] < low[axis] || start[axis] > high[axis]) return 0;
            continue;
        }
        const int64_t distance = delta < 0 ? -delta : delta;
        const int64_t enter_dist = delta > 0 ? low[axis] - start[axis]
                                                   : start[axis] - high[axis];
        const int64_t exit_dist = delta > 0 ? high[axis] - start[axis]
                                                  : start[axis] - low[axis];
        const int64_t a = enter_dist <= 0 ? 0 :
                          (enter_dist * scale + distance - 1) / distance;
        const int64_t b = exit_dist < 0 ? -1 : exit_dist * scale / distance;
        if (a > entry) entry = a;
        if (b < exit) exit = b;
        if (entry > exit) return 0;
    }
    return 1;
}

void game_world_objects_hazards(game_world_object_t *objects, uint16_t count,
                                game_world_player_t *p)
{
    if (!objects || !p || !p->x100 || !p->y100 || !p->vy100 ||
        !p->on_ground || !p->width || !p->height) return;
    const int32_t x = *p->x100 / 100 + p->offset_x;
    const int32_t y = *p->y100 / 100 + p->offset_y;
    for (uint16_t i = 0; i < count; ++i) {
        game_world_object_t *o = &objects[i];
        if (o->type != GAME_OBJECT_HAZARD &&
            o->type != GAME_OBJECT_ENEMY) continue;
        if (o->type == GAME_OBJECT_ENEMY && !o->enemy_hurts_on_touch) continue;
        if (!o->active || !o->width || !o->height) {
            o->hazard_touching = 0;
            continue;
        }
        const uint8_t touching = (uint8_t)(
            (int64_t)x <= (int64_t)o->x + o->width &&
            (int64_t)x + p->width >= o->x &&
            (int64_t)y <= (int64_t)o->y + o->height &&
            (int64_t)y + p->height >= o->y);
        if (!touching && o->hazard_touching) o->hazard_touching = 0;
        if (o->hazard_touching || p->hurt_ticks_remaining ||
            !hazard_swept_contact(p, o, x, y)) continue;
        o->hazard_touching = 1;
        o->hazard_hit_triggered = 1;
        p->hurt_triggered = 1;
        p->hurt_damage_this_frame = o->hazard_damage;
        p->hurt_anim_active = o->hazard_hurt_animation;
        p->hurt_flash_active = o->hazard_flash;
        p->hurt_flash_colour = o->hazard_flash_colour;
        p->hurt_flash_frames = o->hazard_flash_frames ? o->hazard_flash_frames : 1;
        p->hurt_elapsed = 0;
        /* Shared grace period: protects against a second overlapping spike
           damaging every game frame, even if flashing was disabled. */
        const uint32_t duration = o->hazard_flash && o->hazard_flash_count
            ? (uint32_t)o->hazard_flash_count * p->hurt_flash_frames * 2u : 20u;
        p->hurt_ticks_remaining = (uint16_t)(duration > 65535u ? 65535u : duration);
        if (o->hazard_kick) {
            o->hazard_bounce_triggered = 1;
            *p->vy100 = (int32_t)o->hazard_kick_y * 100;
            *p->on_ground = 0;
            if (p->coyote) *p->coyote = 0;
            if (p->spring_force_vx100) {
                int64_t vx = (int64_t)*p->spring_force_vx100 +
                             (int64_t)o->hazard_kick_x * 100;
                if (vx > 3200) vx = 3200;
                if (vx < -3200) vx = -3200;
                *p->spring_force_vx100 = (int32_t)vx;
            } else {
                p->spring_x100 = (int32_t)o->hazard_kick_x * 100;
            }
        }
        break; /* One damage event maximum per frame. */
    }
}

uint8_t game_world_player_hurt_flash(const game_world_player_t *p,
                                    uint8_t *palette_index)
{
    if (!p || !p->hurt_ticks_remaining || !p->hurt_flash_active ||
        !p->hurt_flash_frames) return 0;
    if (palette_index) *palette_index = p->hurt_flash_colour;
    return (uint8_t)((p->hurt_elapsed / p->hurt_flash_frames) % 2u == 0u);
}

void game_world_objects_draw_layer(const game_world_object_t *objects,
                                   uint16_t count, int32_t cx, int32_t cy,
                                   uint8_t behind)
{
    if (!objects) return;
    for (uint16_t i = 0; i < count; ++i) {
        const game_world_object_t *object = &objects[i];
        if ((!object->active && !object->enemy_dying) || !object->sprite ||
            !!object->draw_behind_tiles != !!behind) continue;
        gfxbob_t visible = *object->sprite;
        visible.drawx = clamp16((int64_t)object->x - cx);
        visible.drawy = clamp16((int64_t)object->y - cy);
        gfx_drawbob(&visible);
    }
}

/* Legacy API draws FRONT objects only; a newly generated game calls
   draw_layer(behind=1) before the tilemap for background objects. */
void game_world_objects_draw(const game_world_object_t *objects, uint16_t count,
                              int32_t cx, int32_t cy)
{
    game_world_objects_draw_layer(objects, count, cx, cy, 0);
}
