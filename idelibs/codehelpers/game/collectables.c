#include "collectables.h"

static int16_t clamp16(int64_t n)
{
    return (int16_t)(n < -32768 ? -32768 : n > 32767 ? 32767 : n);
}

uint8_t game_collectable_start(game_collectable_t *item, gfxbob_t *sprite,
                                uint16_t kind, uint16_t value)
{
    if (!item || !sprite || !sprite->imgdat || !sprite->width || !sprite->height ||
        sprite->handle != BLIT_HANDLE_TOP_LEFT || sprite->scale != 100u)
        return 0;
    item->sprite = sprite;
    item->animation = 0;
    item->spline = 0;
    item->x = sprite->drawx;
    item->y = sprite->drawy;
    item->width = sprite->width;
    item->height = sprite->height;
    item->kind = kind;
    item->value = value;
    item->active = 1;
    return 1;
}

void game_collectable_set_position(game_collectable_t *item, int32_t x, int32_t y)
{
    if (!item || !item->sprite) return;
    if (item->spline) {
        /* Here x/y relocate the FIRST spline point, not today's animated position. */
        set_spline_pos(item->spline, clamp16(x), clamp16(y));
        item->x = item->sprite->drawx;
        item->y = item->sprite->drawy;
    } else {
        item->x = x;
        item->y = y;
        item->sprite->drawx = clamp16(x);
        item->sprite->drawy = clamp16(y);
    }
}

void game_collectables_update(game_collectable_t *items, uint16_t count, uint16_t frames)
{
    if (!items || !frames) return;
    for (uint16_t i = 0; i < count; ++i) {
        game_collectable_t *item = &items[i];
        if (!item->active || !item->sprite) continue;
        if (item->spline) {
            run_spline(item->spline, frames);
            item->x = item->sprite->drawx;
            item->y = item->sprite->drawy;
        }
        if (item->animation) run_animation(item->animation, frames);
    }
}

uint16_t game_collectables_check(game_collectable_t *items, uint16_t count,
                                  int32_t px, int32_t py, uint16_t pw, uint16_t ph,
                                  game_pickup_callback_t callback, void *user)
{
    if (!items || !pw || !ph) return 0;
    uint16_t taken = 0;
    for (uint16_t i = 0; i < count; ++i) {
        game_collectable_t *item = &items[i];
        if (!item->active || !item->sprite || !item->width || !item->height) continue;
        if (px < (int64_t)item->x + item->width &&
            (int64_t)px + pw > item->x &&
            py < (int64_t)item->y + item->height &&
            (int64_t)py + ph > item->y) {
            item->active = 0;
            ++taken;
            if (callback) callback(item, user);
        }
    }
    return taken;
}

void game_collectables_draw(const game_collectable_t *items, uint16_t count,
                             int32_t cx, int32_t cy)
{
    if (!items) return;
    for (uint16_t i = 0; i < count; ++i) {
        const game_collectable_t *item = &items[i];
        if (!item->active || !item->sprite) continue;
        gfxbob_t visible = *item->sprite;
        visible.drawx = clamp16((int64_t)item->x - cx);
        visible.drawy = clamp16((int64_t)item->y - cy);
        gfx_drawbob(&visible);
    }
}
