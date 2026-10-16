#include "gametilemap.h"
#include <string.h>
#include <stdlib.h>

/* GAME_TILEMAP_BOB_SD_ATLAS_V1
   Load an indexed PPB into RAM in its ORIGINAL row-major pixel layout.
   gfx_drawbob() already understands an atlas stride and selected cell.
   Keeping the atlas unchanged avoids a second graphics representation.
   The content hash catches stale SD files, even when dimensions match.
   Load once at level startup, never once per frame. */
uint8_t game_tilemap_load_ppb_atlas(game_tilemap_t *map, const char *file,
                                   uint16_t atlas_width, uint16_t atlas_height,
                                   uint32_t expected_hash)
{
    uint8_t hdr[16];
    uint8_t *pixels = NULL;
    uint32_t got = 0;
    uint8_t ok = 0;
    uint32_t hash = 2166136261u; /* FNV-1a, as exported by CoderGirl. */
    if (!map || !file || !file[0] || map->atlas || !map->tile_size ||
        !atlas_width || !atlas_height || !map->atlas_count ||
        (map->tile_size != 8u && map->tile_size != 16u && map->tile_size != 32u) ||
        atlas_width % map->tile_size || atlas_height % map->tile_size) return 0;

    const uint32_t width = atlas_width, height = atlas_height;
    const uint32_t count = width * height;
    const uint32_t columns = width / map->tile_size;
    const uint32_t rows = height / map->tile_size;
    if (columns * rows != map->atlas_count || count > 4u * 1024u * 1024u)
        return 0;

    if (sfopen(0, (char *)file, SD_READ) != F_OK) return 0;
    do {
        if (sfread(0, hdr, sizeof(hdr), &got) != F_OK || got != sizeof(hdr)) break;
        const uint32_t file_width = ((uint32_t)hdr[1] << 8) | hdr[2];
        const uint32_t file_height = ((uint32_t)hdr[3] << 8) | hdr[4];
        const uint32_t file_length = ((uint32_t)hdr[5] << 24) |
            ((uint32_t)hdr[6] << 16) | ((uint32_t)hdr[7] << 8) | hdr[8];
        if (file_width != width || file_height != height || file_length != count)
            break;

        pixels = (uint8_t *)malloc(count);
        if (!pixels || sflseek(0, 1040u) != F_OK) break;
        got = 0;
        if (sfread(0, pixels, count, &got) != F_OK || got != count) break;

        for (uint32_t i = 0; i < count; ++i) {
            hash ^= pixels[i];
            hash *= 16777619u;
        }
        if (hash != expected_hash) break;

        map->atlas = pixels;
        map->atlas_width = atlas_width;
        map->atlas_height = atlas_height;
        map->atlas_borrowed = 0;
        pixels = NULL; /* Ownership moves to the level only on success. */
        ok = 1;
    } while (0);
    sfclose(0);
    free(pixels);
    return ok;
}

uint8_t game_tilemap_attach_shared_ppb_atlas(game_tilemap_t *map,
                                            const uint8_t *pixels,
                                            uint16_t atlas_width, uint16_t atlas_height,
                                            uint32_t expected_hash)
{
    if (!map || !pixels || map->atlas || !map->tile_size ||
        !atlas_width || !atlas_height ||
        atlas_width % map->tile_size || atlas_height % map->tile_size ||
        (uint32_t)(atlas_width / map->tile_size) *
            (atlas_height / map->tile_size) != map->atlas_count ||
        (uint32_t)atlas_width * atlas_height > 4u * 1024u * 1024u)
        return 0;

    uint32_t hash = 2166136261u;
    const uint32_t count = (uint32_t)atlas_width * atlas_height;
    for (uint32_t i = 0; i < count; ++i) {
        hash ^= pixels[i];
        hash *= 16777619u;
    }
    if (hash != expected_hash) return 0;
    map->atlas = pixels;
    map->atlas_width = atlas_width;
    map->atlas_height = atlas_height;
    map->atlas_borrowed = 1;
    return 1;
}

void game_tilemap_unload_ppb_atlas(game_tilemap_t *map)
{
    if (!map || !map->atlas) return;
    /* Borrowed pixels belong to gameassets, so never free them here. */
    if (!map->atlas_borrowed) free((void *)map->atlas);
    map->atlas = NULL;
    map->atlas_width = 0;
    map->atlas_height = 0;
    map->atlas_borrowed = 0;
}

static int32_t limit(int32_t value, int32_t low, int32_t high)
{
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

uint8_t game_tile_at(const game_tilemap_t *map, int32_t x, int32_t y)
{
    if (!map || !map->collision || x < 0 || y < 0 ||
        x >= map->width || y >= map->height) return GAME_TILE_EMPTY;
    return map->collision[(uint32_t)y * map->width + (uint32_t)x];
}

static int32_t floor_tile(int32_t n, int32_t divisor)
{
    /* C truncates negative division toward zero; tile coordinates floor. */
    return n >= 0 ? n / divisor : -1 - (-1 - n) / divisor;
}

/* Draw the visible map using standard BOBs, directly from the PPB atlas.
   Before each tile, clear its foreground rectangle to transparent index 0.
   This preserves the old gfx_blit() behaviour even if the BOB has transparent
   pixels and even when double-buffered pages contain an older camera view.
   gfx_usebuffer(front_buffer) must be called by the game first. */
static const uint8_t empty_tile[32u * 32u] __attribute__((aligned(32))) = {0};

/* Single frame clock shared by all tile instances and both front pages.
 * Every level uses its own small animation table, not per-tile timers.
 */
static uint32_t tile_animation_clock = 0;

void game_tilemap_animation_reset(void)
{
    tile_animation_clock = 0;
}

void game_tilemap_animation_tick(uint16_t frames)
{
    tile_animation_clock += frames;
}

/* Frame index at a given time, including play-once and ping-pong. */
static uint8_t animation_frame(const game_tile_animation_t *a, uint32_t ticks)
{
    const uint32_t n = a->frames;
    const uint32_t step = ticks / a->frame_ticks;
    if (n < 2u) return 0;
    if (a->flags & GAME_TILE_ANIM_BOUNCE) {
        const uint32_t last = n - 1u;
        const uint32_t cycle = 2u * last;
        const uint32_t pos = (a->flags & GAME_TILE_ANIM_LOOP)
            ? step % cycle : (step < cycle ? step : cycle);
        return (uint8_t)(pos <= last ? pos : cycle - pos);
    }
    return (uint8_t)((a->flags & GAME_TILE_ANIM_LOOP)
        ? step % n : (step < n ? step : n - 1u));
}

/* Animation lookup is only over the defined animated tiles, not all 65536
 * possible IDs. That avoids allocating a huge mostly-empty lookup table.
 * All instances of one graphic ID share the same animation clock.
 */
static uint16_t animation_graphic_for_map(const game_tilemap_t *m, uint16_t id)
{
    if (!m->animations) return id;
    for (uint16_t i = 0; i < m->animation_count; ++i) {
        const game_tile_animation_t *a = m->animations + i;
        if (a->graphic_id != id) continue;
        const uint32_t end = (uint32_t)id + (uint32_t)a->frames - 1u;
        if (!id || !a->frame_ticks || !a->frames || a->frames > 16u ||
            end > m->atlas_count) return id;
        return (uint16_t)(id + animation_frame(a, tile_animation_clock));
    }
    return id;
}

void game_tilemap_blit_view(const game_tilemap_t *m,
                            int32_t camera_x, int32_t camera_y,
                            uint16_t view_width, uint16_t view_height)
{
    if (!m || !m->graphics || !m->tile_size || !m->width || !m->height ||
        (m->tile_size != 8u && m->tile_size != 16u && m->tile_size != 32u) ||
        !view_width || !view_height) return;

    const int32_t size = m->tile_size;
    int32_t max_x = (int32_t)m->width * size - view_width;
    int32_t max_y = (int32_t)m->height * size - view_height;
    if (max_x < 0) max_x = 0;
    if (max_y < 0) max_y = 0;
    camera_x = limit(camera_x, 0, max_x);
    camera_y = limit(camera_y, 0, max_y);

    const int32_t first_x = camera_x / size;
    const int32_t first_y = camera_y / size;
    const int32_t last_x = (camera_x + view_width - 1) / size;
    const int32_t last_y = (camera_y + view_height - 1) / size;
    const uint32_t atlas_columns = m->atlas_width / (uint32_t)size;
    const uint32_t atlas_rows = m->atlas_height / (uint32_t)size;
    const uint8_t valid_atlas = (uint8_t)(m->atlas && atlas_columns &&
         atlas_rows && atlas_columns * atlas_rows == m->atlas_count);

    /* BOB is a lightweight descriptor: the pixels stay in the SD-loaded PPB.
       Reposition its image pointer to the correct atlas ROW and set index to
       the COLUMN. Since gfxbob_t.index is uint8_t, shift the pointer again
       for columns beyond 255. No tile extraction/copying is required. */
    gfxbob_t bob = {0};
    bob.atlas_stride = m->atlas_width;
    bob.atlas_height = (uint16_t)size;
    bob.width = (uint16_t)size;
    bob.height = (uint16_t)size;
    bob.scale = 100;
    bob.handle = BLIT_HANDLE_TOP_LEFT;

    for (int32_t ty = first_y; ty <= last_y; ++ty) {
        for (int32_t tx = first_x; tx <= last_x; ++tx) {
            uint16_t id = 0;
            if (tx >= 0 && ty >= 0 && tx < m->width && ty < m->height)
                id = m->graphics[(uint32_t)ty * m->width + (uint32_t)tx];

            const int16_t drawx = (int16_t)(tx * size - camera_x);
            const int16_t drawy = (int16_t)(ty * size - camera_y);
            /* All cells clear first, including empty graphic ID 0. This is
               essential when tiles contain transparent palette index 0. */
            gfx_blit((uint8_t *)empty_tile, drawx, drawy,
                     (uint16_t)size, (uint16_t)size);

            if (!id || !valid_atlas || id > m->atlas_count) continue;
            const uint16_t frame_id = animation_graphic_for_map(m, id);
            if (!frame_id || frame_id > m->atlas_count) continue;
            const uint32_t index0 = (uint32_t)frame_id - 1u;
            const uint32_t row = index0 / atlas_columns;
            const uint32_t col = index0 % atlas_columns;
            const uint32_t page_col = col & ~255u;
            bob.imgdat = m->atlas + row * (uint32_t)size * m->atlas_width
                                      + page_col * (uint32_t)size;
            bob.index = (uint8_t)(col - page_col);
            bob.drawx = drawx;
            bob.drawy = drawy;
            gfx_drawbob(&bob);
        }
    }
}

/* Collision checks only the few map cells touched by the player hitbox. */
static uint8_t touches_solid(const game_tilemap_t *m, int32_t x, int32_t y,
                              int32_t width, int32_t height)
{
    const int32_t s = m->tile_size;
    const int32_t firstX = floor_tile(x, s), lastX = floor_tile(x + width - 1, s);
    const int32_t firstY = floor_tile(y, s), lastY = floor_tile(y + height - 1, s);
    for (int32_t ty = firstY; ty <= lastY; ++ty)
        for (int32_t tx = firstX; tx <= lastX; ++tx)
            if (game_tile_at(m, tx, ty) == GAME_TILE_SOLID) return 1;
    return 0;
}

/* Slopes have a solid triangular interior, not just a landing edge.
 * Prevent sideways entry into that interior while falling or jumping.
 * Sample the highest slope point covered by the full player hitbox.
 * This is only used for HORIZONTAL motion; vertical landing is handled
 * separately by tile_floor(), allowing the player to land on a ramp.
 */
static uint8_t touches_slope_body(const game_tilemap_t *m, int32_t x, int32_t y,
                                  int32_t width, int32_t height)
{
    const int32_t s = m->tile_size;
    const int32_t firstX = floor_tile(x, s);
    const int32_t lastX = floor_tile(x + width - 1, s);
    const int32_t firstY = floor_tile(y, s);
    const int32_t lastY = floor_tile(y + height - 1, s);
    const int32_t feet = y + height;
    for (int32_t ty = firstY; ty <= lastY; ++ty) {
        for (int32_t tx = firstX; tx <= lastX; ++tx) {
            const uint8_t type = game_tile_at(m, tx, ty);
            if (type != GAME_TILE_SLOPE_UP && type != GAME_TILE_SLOPE_DOWN)
                continue;
            const int32_t tileLeft = tx * s;
            const int32_t left = x > tileLeft ? x : tileLeft;
            const int32_t right = x + width - 1 < tileLeft + s - 1
                ? x + width - 1 : tileLeft + s - 1;
            const int32_t surface = ty * s +
                (type == GAME_TILE_SLOPE_UP ? s - 1 - (right - tileLeft)
                                            : left - tileLeft);
            if (feet > surface) return 1;
        }
    }
    return 0;
}

/* Find the first landing surface beneath the ENTIRE width of the player.
 * A 32px player can overlap three 16px tiles: checking only its two
 * outside corners misses the solid tile in the middle and traps the player.
 */
static int32_t tile_floor(const game_tilemap_t *m, int32_t worldX,
                          int32_t width, int32_t oldBottom, int32_t newBottom)
{
    const int32_t s = m->tile_size;
    const int32_t firstX = floor_tile(worldX, s);
    const int32_t lastX = floor_tile(worldX + width - 1, s);
    const int32_t beginY = floor_tile(oldBottom, s);
    const int32_t endY = floor_tile(newBottom, s);
    int32_t best = 0x7FFFFFFF;
    for (int32_t ty = beginY; ty <= endY; ++ty) {
        for (int32_t tx = firstX; tx <= lastX; ++tx) {
            const uint8_t type = game_tile_at(m, tx, ty);
            if (type != GAME_TILE_SOLID && type != GAME_TILE_ONEWAY &&
                type != GAME_TILE_SLOPE_UP && type != GAME_TILE_SLOPE_DOWN) continue;
            int32_t top = ty * s;
            if (type == GAME_TILE_SLOPE_UP || type == GAME_TILE_SLOPE_DOWN) {
                /* Sample the highest slope point covered by the feet. */
                int32_t leftX = worldX > tx * s ? worldX : tx * s;
                int32_t rightX = worldX + width - 1 < (tx + 1) * s - 1
                    ? worldX + width - 1 : (tx + 1) * s - 1;
                top += type == GAME_TILE_SLOPE_UP
                    ? s - 1 - (rightX - tx * s) : leftX - tx * s;
            }
            if (oldBottom <= top && newBottom >= top && top < best) best = top;
        }
    }
    return best;
}

/* Find a nearby solid, one-way or slope surface under the full footprint.
 * Use the same left/right sampling as tile_floor(): a rectangular player
 * stands on the highest point that touches its feet. This also prevents
 * walking partway inside a slope or across a solid ledge at its summit.
 * The caller supplies a small vertical search range (typically 1px).
 */
static int32_t ground_near_feet(const game_tilemap_t *m, int32_t worldX,
                                int32_t width, int32_t feet,
                                int32_t above, int32_t below)
{
    const int32_t s = m->tile_size;
    const int32_t firstX = floor_tile(worldX, s);
    const int32_t lastX = floor_tile(worldX + width - 1, s);
    int32_t best = 0x7FFFFFFF;
    for (int32_t ty = floor_tile(feet - above, s);
         ty <= floor_tile(feet + below, s); ++ty) {
        for (int32_t tx = firstX; tx <= lastX; ++tx) {
            const uint8_t type = game_tile_at(m, tx, ty);
            if (type != GAME_TILE_SLOPE_UP && type != GAME_TILE_SLOPE_DOWN &&
                type != GAME_TILE_SOLID && type != GAME_TILE_ONEWAY) continue;
            const int32_t tileLeft = tx * s;
            const int32_t left = worldX > tileLeft ? worldX : tileLeft;
            const int32_t right = worldX + width - 1 < tileLeft + s - 1
                ? worldX + width - 1 : tileLeft + s - 1;
            const int32_t surface = ty * s +
                (type == GAME_TILE_SLOPE_UP ? s - 1 - (right - tileLeft) :
                 type == GAME_TILE_SLOPE_DOWN ? left - tileLeft : 0);
            if (surface >= feet - above && surface <= feet + below &&
                surface < best)
                best = surface;
        }
    }
    return best;
}

static uint8_t special_type(const game_tilemap_t *m, int32_t x, int32_t y,
                             int32_t width, int32_t height)
{
    const int32_t s = m->tile_size;
    uint8_t found = GAME_TILE_EMPTY;
    for (int32_t ty = floor_tile(y,s); ty <= floor_tile(y+height-1,s); ++ty)
        for (int32_t tx = floor_tile(x,s); tx <= floor_tile(x+width-1,s); ++tx) {
            const uint8_t t = game_tile_at(m,tx,ty);
            if (t == GAME_TILE_HAZARD) return t;
            if (t == GAME_TILE_DOOR) found = t;
        }
    return found;
}

uint8_t game_tile_player_start(game_tile_player_t *p,
                                const game_tilemap_t *m, gfxbob_t *sprite)
{
    if (!p || !m || !m->collision || !m->tile_size || !sprite ||
        sprite->handle != BLIT_HANDLE_TOP_LEFT || sprite->scale != 100 ||
        !sprite->width || !sprite->height) return 0;
    memset(p, 0, sizeof(*p));
    p->sprite = sprite; p->map = m;
    p->walk_speed = 3; p->jump_speed = 7;
    p->gravity = 35; p->max_fall_speed = 9;
    game_tile_player_reset(p, sprite->drawx, sprite->drawy);
    return 1;
}
void game_tile_player_reset(game_tile_player_t *p, int16_t x, int16_t y)
{
    if (!p || !p->sprite) return;
    p->x100 = (int32_t)x * 100; p->y100 = (int32_t)y * 100;
    p->vy100 = 0; p->on_ground = 0; p->jump_held = 0;
    p->coyote = 0; p->touch_type = 0;
    const int32_t feet = y + p->sprite->height;
    p->on_ground = tile_floor(p->map, x, p->sprite->width, feet, feet) == feet;
}
void game_tile_player_run(game_tile_player_t *p, uint8_t buttons, uint16_t frames)
{
    if (!p || !p->sprite || !p->map) return;
    if (frames > 60) frames = 60;
    const game_tilemap_t *m = p->map;
    const int32_t w = p->sprite->width, h = p->sprite->height;
    for (uint16_t n = 0; n < frames; ++n) {
        const uint8_t jumping = !!(buttons & (BTN_UP | BTN_FIRE));
        if (jumping && !p->jump_held && (p->on_ground || p->coyote)) {
            p->vy100 = -(int32_t)p->jump_speed * 100;
            p->on_ground = 0; p->coyote = 0;
        }
        p->jump_held = jumping;
        if (!p->on_ground && p->coyote) --p->coyote;

        const int32_t deltaX = ((buttons & BTN_RIGHT) != 0) -
                               ((buttons & BTN_LEFT) != 0);
        int32_t x = p->x100 / 100, y = p->y100 / 100;
        const uint8_t walkingOnGround = p->on_ground && p->vy100 >= 0;
        uint8_t followedFloor = 0;

        /* Resolve each horizontal pixel independently. A 45-degree slope
         * rises/falls one pixel per horizontal pixel. Move the player's Y
         * with its feet BEFORE checking the adjacent solid tiles.
         */
        for (int32_t i = 0; i < p->walk_speed && deltaX; ++i) {
            const int32_t nextX = x + deltaX;
            int32_t nextPlayerY = y;
            int32_t surface = 0x7FFFFFFF;
            if (walkingOnGround) {
                surface = ground_near_feet(m, nextX, w, y + h, 1, 1);
                if (surface != 0x7FFFFFFF)
                    nextPlayerY = surface - h;
            }
            if (touches_solid(m, nextX, nextPlayerY, w, h) ||
                touches_slope_body(m, nextX, nextPlayerY, w, h)) break;
            x = nextX;
            y = nextPlayerY;
            if (surface != 0x7FFFFFFF) followedFloor = 1;
        }
        p->x100 = x * 100;
        if (followedFloor) p->y100 = y * 100;

        p->vy100 += p->gravity;
        if (p->vy100 > (int32_t)p->max_fall_speed * 100)
            p->vy100 = (int32_t)p->max_fall_speed * 100;
        if (!jumping && p->vy100 < 0) p->vy100 += p->gravity; // short hop
        const int32_t nextY100 = p->y100 + p->vy100;
        const int32_t nextY = nextY100 / 100;
        const uint8_t wasGrounded = p->on_ground;
        uint8_t blocked = 0;
        p->on_ground = 0;

        if (nextY > y) {
            for (int32_t testY = y + 1; testY <= nextY; ++testY) {
                const int32_t floor = tile_floor(m, x, w, testY+h-1, testY+h);
                if (floor != 0x7FFFFFFF) {
                    y = floor - h; p->on_ground = 1;
                    p->vy100 = 0; blocked = 1; break;
                }
                y = testY;
            }
        } else if (nextY < y) {
            for (int32_t testY = y - 1; testY >= nextY; --testY) {
                if (touches_solid(m, x, testY, w, h)) {
                    p->vy100 = 0; blocked = 1; break;
                }
                y = testY;
            }
        }

        /* Contact is checked against the SAME full-width surface as
         * landing. No centre-only snap: that was giving wrong Y positions
         * and sometimes leaving the player partly inside the slope.
         */
        if (!p->on_ground && p->vy100 >= 0) {
            const int32_t feet = y + h;
            if (tile_floor(m, x, w, feet, feet) == feet) {
                p->on_ground = 1; p->vy100 = 0; blocked = 1;
            }
        }
        if (blocked) p->y100 = y * 100;
        else p->y100 = nextY100;
        if (wasGrounded && !p->on_ground) p->coyote = 5;
        p->touch_type = special_type(m, x, y, w, h);
    }
}
void game_tile_player_screen(game_tile_player_t *p, int32_t cameraX, int32_t cameraY)
{
    if (!p || !p->sprite) return;
    p->sprite->drawx = (int16_t)limit(p->x100 / 100 - cameraX, -32768, 32767);
    p->sprite->drawy = (int16_t)limit(p->y100 / 100 - cameraY, -32768, 32767);
}
