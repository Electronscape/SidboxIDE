#include "tilemap.h"
#include <string.h>
#include <stdlib.h>

/* One-player V1 platformer: CONTACT does not mean DEATH.
   Contact notifications leave physics running; only game code can mark a
   player dead. Registration survives resets and SD map reloads. */
static game_death_callback_t cg_death_callback;
static void *cg_death_user;
static uint8_t cg_player_dead;
static game_zone_callback_t cg_zone_callback;
static void *cg_zone_user;
void game_tile_set_zone_callback(game_zone_callback_t callback, void *user)
{
    cg_zone_callback = callback;
    cg_zone_user = user;
}

void game_death_set_callback(game_death_callback_t callback, void *user)
{
    cg_death_callback = callback;
    cg_death_user = user;
}

/* Hazard events are NOT fatal unless the programmer explicitly decides so.
   Detectors report ENTERED once, INSIDE while overlapping, EXITED on leaving. */
uint8_t game_hazard_notify(uint8_t reason, int32_t world_x, int32_t world_y)
{
    if (cg_player_dead || !cg_death_callback) return 0;
    cg_death_callback(reason, world_x, world_y, cg_death_user);
    return 1;
}

/* Mark dead without dispatching another callback. A damage handler can call
   this after health reaches zero, avoiding a recursive second damage event. */
void game_death_mark_dead(void) { cg_player_dead = 1; }

/* Explicit scripted death still freezes physics; this is never called
   automatically for an ordinary tile or Game Object hazard contact. */
uint8_t game_death_trigger(uint8_t reason, int32_t world_x, int32_t world_y)
{
    if (cg_player_dead) return 0;
    cg_player_dead = 1;
    if (cg_death_callback)
        cg_death_callback(reason, world_x, world_y, cg_death_user);
    return 1;
}

uint8_t game_death_is_dead(void) { return cg_player_dead; }
void game_death_rearm(void) { cg_player_dead = 0; }

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

/* GamerGirl / SIDBOX binary map versions 1 and 2. Header 20 bytes, LE:
   "SBMP", version, tile size, width, height, atlas count, animation count,
   FNV-1a checksum, reserved. Payload: graphics (LE u16 per cell), collision
   bytes, (version 2 only) flips per cell, animations (6 bytes: LE ID, frames, ticks, flags, reserved).
   Store no raw pointers in files; all allocations are under our control. */
static uint16_t cg_map_u16(const uint8_t *b)
{
    return (uint16_t)((uint16_t)b[0] | ((uint16_t)b[1] << 8));
}
static uint32_t cg_map_u32(const uint8_t *b)
{
    return (uint32_t)b[0] | ((uint32_t)b[1] << 8) |
           ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}
static uint32_t cg_map_hash(uint32_t h, const uint8_t *b, uint32_t length)
{
    while (length--) { h ^= *b++; h *= 16777619u; }
    return h;
}
/* SD .map v4: compact shared shapes and whole placements, no dense profile
 * unless a pre-v4 design still contains legacy type-7 slope cells.
 * Header[18] = number of shapes; header[19] = legacy-profile-present flag.
 * Payload: graphics, collision, flips, [legacy heights], u16 cell references,
 * u16 instance count, 8-byte shape descriptors, 4-byte points, 6-byte
 * instances, 6-byte tile animations. Hash covers the entire payload. */
static uint8_t cg_map_load_v4(game_tilemap_t *map, const uint8_t hdr[20])
{
    uint8_t *prefix = NULL, *memory = NULL;
    uint32_t got = 0, hash = 2166136261u;
    uint8_t ok = 0;
    const uint16_t w = cg_map_u16(hdr + 6), h = cg_map_u16(hdr + 8);
    const uint16_t count = cg_map_u16(hdr + 12);
    const uint8_t shapes = hdr[18], legacy = hdr[19];
    if (!w || !h || w > 256 || h > 256 || !shapes || shapes > 128 ||
        legacy > 1 || cg_map_u16(hdr+10) != map->atlas_count || count > 128)
        return 0;
    const uint32_t cells = (uint32_t)w * h;
    const uint32_t gfxbytes = cells * 2u;
    const uint32_t legacybytes = legacy ? cells * map->tile_size : 0u;
    const uint32_t refs_at = gfxbytes + cells * 2u + legacybytes;
    const uint32_t inst_count_at = refs_at + cells * 2u;
    const uint32_t defs_at = inst_count_at + 2u;
    const uint32_t fixed = defs_at + shapes * 8u;
    prefix = (uint8_t *)malloc(fixed);
    if (!prefix) goto finish;
    if (sfread(0, prefix, fixed, &got) != F_OK || got != fixed) goto finish;
    hash = cg_map_hash(hash, prefix, fixed);
    const uint16_t instances = cg_map_u16(prefix + inst_count_at);
    uint32_t point_count = 0;
    for (uint8_t i = 0; i < shapes; ++i) {
        const uint8_t *d = prefix + defs_at + 8u * i;
        const uint16_t offset = cg_map_u16(d+2);
        if (!d[0] || !d[1] || d[0] > 16 || d[1] > 16 ||
            d[4] < 2 || d[4] > 128 || d[5] || cg_map_u16(d+6) ||
            offset != point_count) goto finish;
        point_count += d[4];
    }
    if (point_count > 16384u || instances > cells) goto finish;
    const uint32_t points_at = fixed;
    const uint32_t instances_at = points_at + point_count * 4u;
    const uint32_t end_data = instances_at + (uint32_t)instances * 6u;
    const uint32_t animations_at = (end_data + 1u) & ~1u;
    const uint32_t total = animations_at + (uint32_t)count * sizeof(game_tile_animation_t);
    memory = (uint8_t *)malloc(total);
    if (!memory) goto finish;
    memcpy(memory, prefix, fixed);
    free(prefix); prefix = NULL;
    if (sfread(0, memory + points_at, end_data - points_at, &got) != F_OK ||
        got != end_data - points_at) goto finish;
    hash = cg_map_hash(hash, memory + points_at, end_data - points_at);
    const game_tile_shape_t *defs = (const game_tile_shape_t *)(const void *)(memory + defs_at);
    const game_tile_shape_point_t *points =
        (const game_tile_shape_point_t *)(const void *)(memory + points_at);
    const game_tile_shape_instance_t *places =
        (const game_tile_shape_instance_t *)(const void *)(memory + instances_at);
    const uint16_t *refs = (const uint16_t *)(const void *)(memory + refs_at);
    for (uint8_t i = 0; i < shapes; ++i) {
        const game_tile_shape_t *d = &defs[i];
        const game_tile_shape_point_t *pt = points + d->point_offset;
        uint16_t prev = 0;
        for (uint8_t k = 0; k < d->point_count; ++k) {
            if ((k && pt[k].x <= prev) ||
                pt[k].y > (uint16_t)d->height * map->tile_size ||
                pt[k].x > (uint16_t)d->width * map->tile_size) goto finish;
            if ((!k && pt[k].x) ||
                (k == d->point_count-1 && pt[k].x != (uint16_t)d->width*map->tile_size))
                goto finish;
            prev = pt[k].x;
        }
    }
    for (uint16_t i = 0; i < instances; ++i) {
        const game_tile_shape_instance_t *p = places + i;
        if (p->shape >= shapes || (p->flags & ~1u) ||
            (uint32_t)p->x + defs[p->shape].width > w ||
            (uint32_t)p->y + defs[p->shape].height > h) goto finish;
        for (uint16_t y = p->y; y < p->y + defs[p->shape].height; ++y)
            for (uint16_t x = p->x; x < p->x + defs[p->shape].width; ++x) {
                const uint32_t index = (uint32_t)y * w + x;
                if (refs[index] != i+1 || memory[gfxbytes + index] != GAME_TILE_POINT_SLOPE)
                    goto finish;
            }
    }
    for (uint32_t i = 0; i < cells; ++i) {
        if (cg_map_u16(memory + i * 2u) > map->atlas_count ||
            memory[gfxbytes + i] > GAME_TILE_CUSTOM_ZONE_MAX ||
            (memory[gfxbytes + cells + i] & ~7u)) goto finish;
        if (memory[gfxbytes + i] == GAME_TILE_POINT_SLOPE) {
            if (!refs[i] || refs[i] > instances) goto finish;
            const game_tile_shape_instance_t *p = places + refs[i]-1;
            const game_tile_shape_t *d = &defs[p->shape];
            if (i % w < p->x || i % w >= p->x+d->width ||
                i / w < p->y || i / w >= p->y+d->height) goto finish;
        } else if (refs[i]) goto finish;
        if (memory[gfxbytes + i] == GAME_TILE_CUSTOM_SLOPE) {
            if (!legacy) goto finish;
            const uint8_t *heightvalues = memory + gfxbytes + cells*2u + i*map->tile_size;
            for (uint16_t x = 0; x < map->tile_size; ++x)
                if (heightvalues[x] > map->tile_size) goto finish;
        }
    }
    game_tile_animation_t *animations =
        (game_tile_animation_t *)(void *)(memory + animations_at);
    for (uint16_t i = 0; i < count; ++i) {
        uint8_t b[6];
        if (sfread(0, b, sizeof(b), &got) != F_OK || got != sizeof(b)) goto finish;
        hash = cg_map_hash(hash, b, sizeof(b));
        animations[i].graphic_id = cg_map_u16(b);
        animations[i].frames = b[2]; animations[i].frame_ticks = b[3];
        animations[i].flags = b[4];
        if (b[5] || !animations[i].graphic_id || !animations[i].frames ||
            animations[i].frames > 16 || !animations[i].frame_ticks ||
            animations[i].flags & ~(GAME_TILE_ANIM_LOOP | GAME_TILE_ANIM_BOUNCE) ||
            (uint32_t)animations[i].graphic_id + animations[i].frames - 1u > map->atlas_count)
            goto finish;
    }
    uint8_t extra = 0;
    if (sfread(0, &extra, 1, &got) != F_OK || got || hash != cg_map_u32(hdr+14))
        goto finish;
    game_tilemap_unload_map(map);
    map->map_storage = memory;
    map->graphics = (const uint16_t *)(const void *)memory;
    map->collision = memory + gfxbytes;
    map->flips = memory + gfxbytes + cells;
    map->slopes = legacy ? memory + gfxbytes + cells*2u : NULL;
    map->shape_refs = refs;
    map->shape_defs = defs;
    map->shape_points = points;
    map->shape_instances = places;
    map->shape_count = shapes;
    map->shape_instance_count = instances;
    map->animations = count ? animations : NULL;
    map->animation_count = count;
    map->width = w; map->height = h;
    memory = NULL;
    ok = 1;
finish:
    free(prefix);
    free(memory);
    return ok;
}

void game_tilemap_unload_map(game_tilemap_t *map)
{
    if (!map || !map->map_storage) return;
    free(map->map_storage);
    map->map_storage = NULL;
    map->graphics = NULL;
    map->collision = NULL;
    map->flips = NULL;
    map->slopes = NULL;
    map->shape_refs = NULL;
    map->shape_instances = NULL;
    map->shape_defs = NULL;
    map->shape_points = NULL;
    map->shape_instance_count = 0;
    map->shape_count = 0;
    map->animations = NULL;
    map->animation_count = 0;
    map->width = map->height = 0;
}
uint8_t game_tilemap_load_map(game_tilemap_t *map, const char *filename)
{
    uint8_t hdr[20], extra;
    uint8_t *memory = NULL;
    uint32_t read_bytes = 0, hash = 2166136261u;
    uint8_t ok = 0;
    if (!map || !filename || !filename[0] || !map->tile_size) return 0;
    if (sfopen(0, (char *)filename, SD_READ) != F_OK) return 0;
    do {
        if (sfread(0, hdr, sizeof(hdr), &read_bytes) != F_OK ||
            read_bytes != sizeof(hdr) || memcmp(hdr, "SBMP", 4) ||
            (hdr[4] != 1 && hdr[4] != 2 && hdr[4] != 3 && hdr[4] != 4) ||
            hdr[5] != map->tile_size ||
            (hdr[4] != 4 && (hdr[18] || hdr[19]))) break;
        if (hdr[4] == 4) { ok = cg_map_load_v4(map, hdr); break; }
        const uint16_t width = cg_map_u16(hdr + 6);
        const uint16_t height = cg_map_u16(hdr + 8);
        const uint16_t atlas_count = cg_map_u16(hdr + 10);
        const uint16_t animation_count = cg_map_u16(hdr + 12);
        const uint32_t checksum = cg_map_u32(hdr + 14);
        if (!width || !height || width > 256 || height > 256 ||
            atlas_count != map->atlas_count || animation_count > 128) break;
        const uint32_t cells = (uint32_t)width * height;
        const uint32_t graphics_bytes = cells * 2u;
        const uint32_t payload_bytes = graphics_bytes + cells + (hdr[4] >= 2 ? cells : 0u)
            + (hdr[4] == 3 ? cells * map->tile_size : 0u);
        const uint32_t animation_offset = (payload_bytes + 1u) & ~1u;
        const uint32_t allocation = animation_offset +
            (uint32_t)animation_count * sizeof(game_tile_animation_t);
        memory = (uint8_t *)malloc(allocation);
        if (!memory) break;
        if (sfread(0, memory, payload_bytes, &read_bytes) != F_OK ||
            read_bytes != payload_bytes) break;
        hash = cg_map_hash(hash, memory, payload_bytes);
        for (uint32_t i = 0; i < cells; ++i) {
            const uint16_t id = cg_map_u16(memory + i * 2u);
            if (id > atlas_count ||
                (hdr[4] == 1 && memory[graphics_bytes + i] > GAME_TILE_DOOR) ||
                (hdr[4] >= 2 && memory[graphics_bytes + i] > GAME_TILE_CUSTOM_ZONE_MAX) ||
                (hdr[4] == 2 && (memory[graphics_bytes + i] == GAME_TILE_CUSTOM_SLOPE ||
                                  memory[graphics_bytes + i] == GAME_TILE_POINT_SLOPE)) ||
                (hdr[4] == 3 && memory[graphics_bytes + i] == GAME_TILE_POINT_SLOPE))
                goto map_done;
            if (hdr[4] >= 2 && (memory[graphics_bytes + cells + i] & ~7u))
                goto map_done;
            if (hdr[4] == 3 && memory[graphics_bytes + i] == GAME_TILE_CUSTOM_SLOPE) {
                const uint8_t *heights = memory + graphics_bytes + 2u * cells +
                                         i * map->tile_size;
                for (uint16_t j = 0; j < map->tile_size; ++j)
                    if (heights[j] > map->tile_size) goto map_done;
            }
        }
        game_tile_animation_t *animations =
            (game_tile_animation_t *)(void *)(memory + animation_offset);
        for (uint16_t i = 0; i < animation_count; ++i) {
            uint8_t b[6];
            if (sfread(0, b, sizeof(b), &read_bytes) != F_OK ||
                read_bytes != sizeof(b)) goto map_done;
            hash = cg_map_hash(hash, b, sizeof(b));
            animations[i].graphic_id = cg_map_u16(b);
            animations[i].frames = b[2];
            animations[i].frame_ticks = b[3];
            animations[i].flags = b[4];
            if (b[5] || !animations[i].graphic_id || !animations[i].frames ||
                animations[i].frames > 16 || !animations[i].frame_ticks ||
                (animations[i].flags & ~(GAME_TILE_ANIM_LOOP | GAME_TILE_ANIM_BOUNCE)) ||
                (uint32_t)animations[i].graphic_id + animations[i].frames - 1u > atlas_count)
                goto map_done;
        }
        if (sfread(0, &extra, 1, &read_bytes) != F_OK || read_bytes != 0 || hash != checksum)
            break;
        /* Commit only after COMPLETE validation. Retain the loaded PPB atlas. */
        game_tilemap_unload_map(map);
        map->map_storage = memory;
        map->graphics = (const uint16_t *)(const void *)memory;
        map->collision = memory + graphics_bytes;
        map->flips = hdr[4] >= 2 ? memory + graphics_bytes + cells : NULL;
        map->slopes = hdr[4] == 3 ? memory + graphics_bytes + 2u * cells : NULL;
        map->animations = animation_count ? animations : NULL;
        map->animation_count = animation_count;
        map->width = width;
        map->height = height;
        memory = NULL;
        ok = 1;
    } while (0);
map_done:
    sfclose(0);
    free(memory);
    return ok;
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

static void game_tilemap_blit_view_impl(const game_tilemap_t *m,
                                        int32_t camera_x, int32_t camera_y,
                                        uint16_t view_width, uint16_t view_height,
                                        uint8_t buffer_already_cleared,
                                        uint8_t front_only)
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
            /* Legacy draws clear each cell themselves. If the caller has
               ALREADY cleared the whole target buffer to palette index 0,
               another 2400+ tiny gfx_blit calls are completely redundant. */
            if (!buffer_already_cleared && !front_only)
                gfx_blit((uint8_t *)empty_tile, drawx, drawy,
                         (uint16_t)size, (uint16_t)size);

            if (!id || !valid_atlas || id > m->atlas_count) continue;
            const uint32_t cell = (uint32_t)ty * m->width + (uint32_t)tx;
            const uint8_t flip = m->flips ? m->flips[cell] : 0;
            if (((flip & GAME_TILE_DRAW_FRONT) != 0) != (front_only != 0)) continue;
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
            /* Set flags on EVERY tile: gfxbob_t is reused across the loop. */
            bob.flags = (uint8_t)(((flip & GAME_TILE_FLIP_X) ? BLIT_FLAG_FLIP_X : 0) |
                                  ((flip & GAME_TILE_FLIP_Y) ? BLIT_FLAG_FLIP_Y : 0));
            gfx_drawbob(&bob);
        }
    }
}

/* Fully self-contained original renderer: clears every tile, even blank ones.
   Keep this default safe for callers that draw onto a non-cleared buffer. */
void game_tilemap_blit_view(const game_tilemap_t *m,
                            int32_t camera_x, int32_t camera_y,
                            uint16_t view_width, uint16_t view_height)
{
    game_tilemap_blit_view_impl(m, camera_x, camera_y,
                                view_width, view_height, 0, 0);
}

/* Fast path: use ONLY when the ENTIRE destination buffer has already been
   cleared to palette index 0, e.g. gfx_setcolour(0); gfx_rectf(0,0,w,h).
   Preserves the original rendering while skipping one blank gfx_blit per
   visible tile cell. All tile atlas BOB draws and flip flags are unchanged. */
void game_tilemap_blit_view_cleared(const game_tilemap_t *m,
                                    int32_t camera_x, int32_t camera_y,
                                    uint16_t view_width, uint16_t view_height)
{
    game_tilemap_blit_view_impl(m, camera_x, camera_y,
                                view_width, view_height, 1, 0);
}

/* Foreground tiles are rendered after the player and never clear the
   framebuffer. When no tiles are flagged, this submits no BOB commands. */
void game_tilemap_blit_view_front(const game_tilemap_t *m,
                                  int32_t camera_x, int32_t camera_y,
                                  uint16_t view_width, uint16_t view_height)
{
    game_tilemap_blit_view_impl(m, camera_x, camera_y,
                                view_width, view_height, 1, 1);
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
            if (game_tile_at(m, tx, ty) == GAME_TILE_SOLID ||
                GAME_TILE_ZONE_BLOCKS(game_tile_at(m, tx, ty))) return 1;
    return 0;
}

/* Slopes have a solid triangular interior, not just a landing edge.
 * Prevent sideways entry into that interior while falling or jumping.
 * Sample the highest slope point covered by the full player hitbox.
 * This is only used for HORIZONTAL motion; vertical landing is handled
 * separately by tile_floor(), allowing the player to land on a ramp.
 */
/* Custom walkable ground. A height of 0 fills the tile column; tile_size
 * means empty. One byte per horizontal pixel of a custom slope cell. */
static int32_t custom_surface(const game_tilemap_t *m, int32_t tx, int32_t ty,
                              int32_t left, int32_t right)
{
    if (tx < 0 || ty < 0 || tx >= m->width || ty >= m->height)
        return 0x7FFFFFFF;
    if (game_tile_at(m, tx, ty) == GAME_TILE_POINT_SLOPE) {
        if (!m->shape_refs || !m->shape_instances || !m->shape_defs || !m->shape_points)
            return 0x7FFFFFFF;
        const uint16_t ref = m->shape_refs[(uint32_t)ty*m->width + tx];
        if (!ref || ref > m->shape_instance_count) return 0x7FFFFFFF;
        const game_tile_shape_instance_t *place = m->shape_instances + ref - 1;
        if (place->shape >= m->shape_count) return 0x7FFFFFFF;
        const game_tile_shape_t *d = m->shape_defs + place->shape;
        const game_tile_shape_point_t *pts = m->shape_points + d->point_offset;
        const int32_t width = (int32_t)d->width * m->tile_size;
        const int32_t origin = (int32_t)place->x * m->tile_size;
        /* A straight line is monotonic between its two endpoints. Instead
           of interpolating EACH horizontal pixel covered by the actor,
           inspect only the lowest endpoint inside each overlapping segment.
           This returns precisely the same integer-rounded height as the
           original pixel-by-pixel scan, but work scales with control points
           instead of player width times control points. This is especially
           helpful when a moving lift repeatedly checks actor collisions. */
        int32_t local_left = left - origin;
        int32_t local_right = right - origin;
        if (place->flags & 1u) {
            const int32_t mirrored_left = width - 1 - local_right;
            local_right = width - 1 - local_left;
            local_left = mirrored_left;
        }
        if (local_left < 0) local_left = 0;
        if (local_right >= width) local_right = width - 1;
        if (local_left > local_right) return 0x7FFFFFFF;
        int32_t best = 0x7FFFFFFF;
        for (uint8_t k = 1; k < d->point_count; ++k) {
            const game_tile_shape_point_t *a = pts + k - 1;
            const game_tile_shape_point_t *b = pts + k;
            if (b->x < local_left) continue;
            if (a->x > local_right) break;
            const int32_t segment_left = local_left > a->x ? local_left : a->x;
            const int32_t segment_right = local_right < b->x ? local_right : b->x;
            /* A falling line reaches its minimum at the right endpoint,
               a rising or level line at the left endpoint. */
            const int32_t sample = b->y < a->y ? segment_right : segment_left;
            const int32_t y = a->y + (int32_t)(b->y - (int32_t)a->y) *
                                           (sample - a->x) / (b->x - a->x);
            if (y < best) best = y;
            if (b->x >= local_right) break;
        }
        return best == 0x7FFFFFFF ? best : (int32_t)place->y * m->tile_size + best;
    }
    if (!m->slopes) return 0x7FFFFFFF;
    const int32_t s = m->tile_size;
    const uint8_t *values = m->slopes + ((uint32_t)ty * m->width + tx) * s;
    int32_t best = s;
    for (int32_t x = left - tx * s; x <= right - tx * s; ++x)
        if (values[x] < best) best = values[x];
    return ty * s + best;
}

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
            if (type != GAME_TILE_SLOPE_UP && type != GAME_TILE_SLOPE_DOWN &&
                type != GAME_TILE_CUSTOM_SLOPE && type != GAME_TILE_POINT_SLOPE) continue;
            const int32_t tileLeft = tx * s;
            const int32_t left = x > tileLeft ? x : tileLeft;
            const int32_t right = x + width - 1 < tileLeft + s - 1
                ? x + width - 1 : tileLeft + s - 1;
            const int32_t surface = (type == GAME_TILE_CUSTOM_SLOPE || type == GAME_TILE_POINT_SLOPE)
                ? custom_surface(m, tx, ty, left, right)
                : ty * s + (type == GAME_TILE_SLOPE_UP ? s - 1 - (right - tileLeft)
                                                         : left - tileLeft);
            if (feet > surface) return 1;
        }
    }
    return 0;
}

/* Public collision query for externally carried players (moving lifts).
   Share precisely the wall/slope rules used by the advanced tilemap player.
   One-way surfaces aren't walls: carrying a player across them is allowed. */
uint8_t game_tilemap_actor_blocked(const game_tilemap_t *map,
                                   int32_t x, int32_t y,
                                   uint16_t width, uint16_t height)
{
    if (!map || !map->collision || !map->tile_size || !width || !height)
        return 0;
    return (uint8_t)(touches_solid(map, x, y, width, height) ||
                     touches_slope_body(map, x, y, width, height));
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
                type != GAME_TILE_SLOPE_UP && type != GAME_TILE_SLOPE_DOWN &&
                type != GAME_TILE_CUSTOM_SLOPE && type != GAME_TILE_POINT_SLOPE &&
                !GAME_TILE_ZONE_BLOCKS(type)) continue;
            int32_t top = ty * s;
            if (type == GAME_TILE_SLOPE_UP || type == GAME_TILE_SLOPE_DOWN ||
                (type == GAME_TILE_CUSTOM_SLOPE || type == GAME_TILE_POINT_SLOPE)) {
                /* Sample the highest slope point covered by the feet. */
                int32_t leftX = worldX > tx * s ? worldX : tx * s;
                int32_t rightX = worldX + width - 1 < (tx + 1) * s - 1
                    ? worldX + width - 1 : (tx + 1) * s - 1;
                top = (type == GAME_TILE_CUSTOM_SLOPE || type == GAME_TILE_POINT_SLOPE)
                    ? custom_surface(m, tx, ty, leftX, rightX)
                    : top + (type == GAME_TILE_SLOPE_UP
                    ? s - 1 - (rightX - tx * s) : leftX - tx * s);
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
                type != GAME_TILE_SOLID && type != GAME_TILE_ONEWAY &&
                type != GAME_TILE_CUSTOM_SLOPE && type != GAME_TILE_POINT_SLOPE &&
                !GAME_TILE_ZONE_BLOCKS(type)) continue;
            const int32_t tileLeft = tx * s;
            const int32_t left = worldX > tileLeft ? worldX : tileLeft;
            const int32_t right = worldX + width - 1 < tileLeft + s - 1
                ? worldX + width - 1 : tileLeft + s - 1;
            const int32_t surface = (type == GAME_TILE_CUSTOM_SLOPE || type == GAME_TILE_POINT_SLOPE)
                ? custom_surface(m, tx, ty, left, right)
                : ty * s + (type == GAME_TILE_SLOPE_UP ? s - 1 - (right - tileLeft) :
                            type == GAME_TILE_SLOPE_DOWN ? left - tileLeft : 0);
            /* A wider step-up search helps walkable polyline ramps.
               Ordinary solid blocks remain limited to tiny ledges. */
            const int32_t permittedUp = (type == GAME_TILE_SOLID ||
                type == GAME_TILE_ONEWAY || GAME_TILE_ZONE_BLOCKS(type)) ? 2 : above;
            if (surface >= feet - permittedUp && surface <= feet + below &&
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

/* Build a bitmask for all eight zone identities. Blocking zones are detected
   at the hitbox boundary too, so the player can touch a rock without passing
   through it. Non-blocking zones require true overlap. */
static uint8_t game_zone_at_player(const game_tilemap_t *m,
    int32_t x, int32_t y, int32_t width, int32_t height)
{
    const int32_t s = m->tile_size;
    uint8_t mask = 0;
    for (int32_t ty = floor_tile(y-1, s); ty <= floor_tile(y+height, s); ++ty)
        for (int32_t tx = floor_tile(x-1, s); tx <= floor_tile(x+width, s); ++tx) {
            const uint8_t type = game_tile_at(m, tx, ty);
            const uint8_t zone = GAME_TILE_ZONE_NUMBER(type);
            if (!zone) continue;
            const int32_t left = tx*s, top = ty*s;
            const int32_t margin = GAME_TILE_ZONE_BLOCKS(type) ? 1 : 0;
            if (x + width - 1 + margin < left || x - margin >= left+s ||
                y + height - 1 + margin < top || y - margin >= top+s) continue;
            mask |= (uint8_t)(1u << (zone - 1u));
        }
    return mask;
}

/* Convert only at the API boundary; no FPU arithmetic in the physics loop.
   Clamp before converting to fixed point to avoid invalid float-to-int casts. */
void apply_force(game_tile_player_t *p, float x, float y)
{
    if (!p || !p->sprite || !p->map) return;
    if (!(x >= -32.0f && x <= 32.0f)) {
        if (x != x) x = 0.0f; /* NaN */
        else x = x < 0.0f ? -32.0f : 32.0f;
    }
    if (!(y >= -32.0f && y <= 32.0f)) {
        if (y != y) y = 0.0f;
        else y = y < 0.0f ? -32.0f : 32.0f;
    }
    const int32_t dx = (int32_t)(x * 100.0f + (x < 0.0f ? -0.5f : 0.5f));
    const int32_t dy = (int32_t)(y * 100.0f + (y < 0.0f ? -0.5f : 0.5f));
    int32_t newX = p->force_vx100 + dx;
    int32_t newY = p->vy100 + dy;
    if (newX > 3200) newX = 3200;
    if (newX < -3200) newX = -3200;
    if (newY > 3200) newY = 3200;
    if (newY < -3200) newY = -3200;
    p->force_vx100 = newX;
    p->vy100 = newY;
    if (dy < 0) {
        p->on_ground = 0;
        p->coyote = 0;
        p->external_ascent = 1;
    }
}
void game_tile_player_set_force_drag(game_tile_player_t *p, uint8_t percent)
{ if (p) p->force_drag_percent = percent > 100u ? 100u : percent; }
void game_tile_player_step(game_tile_player_t *p, uint16_t frames)
{ game_tile_player_run(p, 0, frames); }

void game_tile_player_set_gravity(game_tile_player_t *p, int16_t gravity)
{ if (p) p->gravity = gravity < 0 ? 0 : gravity; }
void game_tile_player_set_walk_speed(game_tile_player_t *p, int16_t speed)
{ if (p) p->walk_speed = speed < 0 ? 0 : speed > 16 ? 16 : speed; }
void game_tile_player_set_physics(game_tile_player_t *p, uint8_t mode)
{
    if (!p || mode > GAME_PHYSICS_JETPACK) return;
    /* Presets change material properties, NOT velocity. ICE uses the
       previous joystick speed directly. Other mode switches carry the
       outgoing speed into the force channel on the next physics tick,
       when we know the NEW walk input (or zero for a space thruster step).
       Never double-count current joystick input or existing impulses. */
    if (p->physics_mode != mode)
        p->physics_handoff_pending = (mode != GAME_PHYSICS_ICE);
    p->physics_mode = mode;
    p->force_drag_percent = 12; /* Normal: slow external horizontal momentum. */
    p->walk_speed = 3; p->jump_speed = 7;
    p->gravity = 35; p->max_fall_speed = 9;
    switch (mode) {
        case GAME_PHYSICS_ICE: p->walk_speed = 4; p->force_drag_percent = 2; break;
        case GAME_PHYSICS_WATER:
            p->walk_speed = 2; p->jump_speed = 5;
            p->gravity = 12; p->max_fall_speed = 3; p->force_drag_percent = 18; break;
        case GAME_PHYSICS_SLOW: p->walk_speed = 1; p->force_drag_percent = 18; break;
        case GAME_PHYSICS_SPACE:
            p->gravity = 3; p->max_fall_speed = 3; p->force_drag_percent = 0; break;
        case GAME_PHYSICS_FLOATING:
            p->gravity = 7; p->max_fall_speed = 2; p->force_drag_percent = 4; break;
        case GAME_PHYSICS_JETPACK:
            p->gravity = 20; p->max_fall_speed = 6; p->force_drag_percent = 6; break;
        default: break;
    }
}
void game_tile_player_set_physics_normal(game_tile_player_t *p) { game_tile_player_set_physics(p, GAME_PHYSICS_NORMAL); }
void game_tile_player_set_physics_ice(game_tile_player_t *p) { game_tile_player_set_physics(p, GAME_PHYSICS_ICE); }
void game_tile_player_set_physics_water(game_tile_player_t *p) { game_tile_player_set_physics(p, GAME_PHYSICS_WATER); }
void game_tile_player_set_physics_slow(game_tile_player_t *p) { game_tile_player_set_physics(p, GAME_PHYSICS_SLOW); }
void game_tile_player_set_physics_space(game_tile_player_t *p) { game_tile_player_set_physics(p, GAME_PHYSICS_SPACE); }
void game_tile_player_set_physics_floating(game_tile_player_t *p) { game_tile_player_set_physics(p, GAME_PHYSICS_FLOATING); }
void game_tile_player_set_physics_jetpack(game_tile_player_t *p) { game_tile_player_set_physics(p, GAME_PHYSICS_JETPACK); }

uint8_t game_tile_player_start(game_tile_player_t *p,
                                const game_tilemap_t *m, gfxbob_t *sprite)
{
    if (!p || !m || !m->collision || !m->tile_size || !sprite ||
        sprite->handle != BLIT_HANDLE_TOP_LEFT || sprite->scale != 100 ||
        !sprite->width || !sprite->height) return 0;
    memset(p, 0, sizeof(*p));
    p->sprite = sprite; p->map = m;
    p->walk_speed = 3; p->jump_speed = 7;
    p->gravity = 35; p->max_fall_speed = 9; p->force_drag_percent = 12;
    game_tile_player_reset(p, sprite->drawx, sprite->drawy);
    return 1;
}
void game_tile_player_reset(game_tile_player_t *p, int16_t x, int16_t y)
{
    if (!p || !p->sprite) return;
    p->x100 = (int32_t)x * 100; p->y100 = (int32_t)y * 100;
    p->vy100 = 0; p->on_ground = 0; p->jump_held = 0;
    p->coyote = 0; p->touch_type = 0; p->hazard_contact = 0;
    game_death_rearm();
    p->slide_velocity100 = 0; p->slide_remainder100 = 0;
    p->physics_handoff_pending = 0; p->zone_contacts = 0;
    p->physics_vy100 = 0; p->external_ascent = 0;
    p->force_vx100 = 0; p->force_remainder100 = 0;
    const int32_t feet = y + p->sprite->height;
    p->on_ground = tile_floor(p->map, x, p->sprite->width, feet, feet) == feet;
}
void game_tile_player_run(game_tile_player_t *p, uint8_t buttons, uint16_t frames)
{
    if (!p || !p->sprite || !p->map || game_death_is_dead()) return;
    if (frames > 60) frames = 60;
    const game_tilemap_t *m = p->map;
    const int32_t w = p->sprite->width, h = p->sprite->height;
    for (uint16_t n = 0; n < frames; ++n) {
        /* World Objects applies spring launches AFTER game_tile_player_run().
           Detect an upward impulse made between physics calls rather than
           treating it as an ordinary variable-height jump. This also works
           for manually launched players without changing main.c or wiring
           World Objects into the tilemap helper. */
        if (p->vy100 < 0 && p->vy100 != p->physics_vy100)
            p->external_ascent = 1;
        if (p->vy100 >= 0)
            p->external_ascent = 0;

        const uint8_t jumping = !!(buttons & (BTN_UP | BTN_FIRE));
        if (jumping && !p->jump_held && (p->on_ground || p->coyote)) {
            p->vy100 = -(int32_t)p->jump_speed * 100;
            p->on_ground = 0; p->coyote = 0;
            p->external_ascent = 0; /* A regular jump retains short-hop control. */
        }
        p->jump_held = jumping;
        if (!p->on_ground && p->coyote) --p->coyote;

        const int32_t deltaX = ((buttons & BTN_RIGHT) != 0) -
                               ((buttons & BTN_LEFT) != 0);
        /* Conserve horizontal motion through a change of preset. Compare
           PREVIOUS walking/sliding + existing force against NEW walking
           input, and carry only the difference as decaying/free-floating
           external momentum. If previously stationary, don't cancel the
           player's very first step in the new mode. */
        if (p->physics_handoff_pending && p->physics_mode != GAME_PHYSICS_ICE) {
            int32_t previous = p->slide_velocity100
                + p->slide_remainder100 + p->force_vx100;
            if (previous) {
                const int32_t target = deltaX * (int32_t)p->walk_speed * 100;
                int32_t carry = previous - target;
                if (carry > 3200) carry = 3200;
                if (carry < -3200) carry = -3200;
                p->force_vx100 = carry;
            }
            p->physics_handoff_pending = 0;
            p->slide_remainder100 = 0;
        }
        int32_t x = p->x100 / 100, y = p->y100 / 100;
        int32_t horizontalSteps = p->walk_speed;
        if (p->physics_mode == GAME_PHYSICS_ICE) {
            /* Acceleration + friction only in ICE mode; normal movement is
               bit-for-bit compatible with the original platformer. */
            if (deltaX) {
                int32_t v = p->slide_velocity100 + deltaX * 35;
                const int32_t top = (int32_t)p->walk_speed * 100;
                if (v > top) v = top;
                if (v < -top) v = -top;
                p->slide_velocity100 = (int16_t)v;
            } else {
                p->slide_velocity100 = (int16_t)((int32_t)p->slide_velocity100 *
                    (p->on_ground ? 90 : 96) / 100);
            }
            const int32_t step100 = p->slide_remainder100 + p->slide_velocity100;
            horizontalSteps = step100 < 0 ? -(step100 / 100) : step100 / 100;
            p->slide_remainder100 = (int16_t)(step100 % 100);
        }
        int32_t horizontalDirection = p->physics_mode == GAME_PHYSICS_ICE
            ? ((p->slide_velocity100 > 0) - (p->slide_velocity100 < 0)) : deltaX;
        /* Add external velocity to the ordinary horizontal displacement.
           Keep a 1/100-pixel remainder so even gentle wind accelerates and
           moves the player. No force means the old movement is unchanged. */
        if (p->force_vx100 || p->force_remainder100) {
            const int32_t delta100 = horizontalSteps * horizontalDirection * 100
                + p->force_vx100 + p->force_remainder100;
            const int32_t steps = delta100 / 100;
            p->force_remainder100 = delta100 - steps * 100;
            horizontalSteps = steps < 0 ? -steps : steps;
            horizontalDirection = (steps > 0) - (steps < 0);
        }
        const uint8_t walkingOnGround = p->on_ground && p->vy100 >= 0;
        uint8_t followedFloor = 0;
        uint8_t horizontalBlocked = 0;
        uint8_t crossed_hazard = special_type(m, x, y, w, h) == GAME_TILE_HAZARD;

        /* Resolve each horizontal pixel independently. A 45-degree slope
         * rises/falls one pixel per horizontal pixel. Move the player's Y
         * with its feet BEFORE checking the adjacent solid tiles.
         */
        for (int32_t i = 0; i < horizontalSteps && horizontalDirection; ++i) {
            const int32_t nextX = x + horizontalDirection;
            int32_t nextPlayerY = y;
            int32_t surface = 0x7FFFFFFF;
            if (walkingOnGround) {
                surface = ground_near_feet(m, nextX, w, y + h, 4, 2);
                if (surface != 0x7FFFFFFF)
                    nextPlayerY = surface - h;
            }
            if (touches_solid(m, nextX, nextPlayerY, w, h) ||
                touches_slope_body(m, nextX, nextPlayerY, w, h)) {
                p->slide_velocity100 = 0; p->slide_remainder100 = 0;
                p->force_vx100 = 0; p->force_remainder100 = 0;
                horizontalBlocked = 1;
                break;
            }
            x = nextX;
            y = nextPlayerY;
            if (special_type(m, x, y, w, h) == GAME_TILE_HAZARD)
                crossed_hazard = 1;
            if (surface != 0x7FFFFFFF) followedFloor = 1;
        }
        p->x100 = x * 100;
        if (followedFloor) p->y100 = y * 100;
        /* Track the joystick's last horizontal speed even on normal ground.
           The zone callback at the END of this tick can now switch to ICE
           without first forcing the player to accelerate from a standstill.
           Do not include external forces in this value: they persist in
           force_vx100 already, so including them would double the impulse. */
        if (p->physics_mode != GAME_PHYSICS_ICE) {
            p->slide_velocity100 = horizontalBlocked ? 0 :
                (int16_t)(deltaX * (int32_t)p->walk_speed * 100);
            p->slide_remainder100 = 0;
        }
        if (p->force_vx100 && p->force_drag_percent) {
            p->force_vx100 = p->force_vx100 *
                (100 - p->force_drag_percent) / 100;
            if (p->force_vx100 > -2 && p->force_vx100 < 2)
                p->force_vx100 = 0;
        }

        if (p->physics_mode == GAME_PHYSICS_JETPACK &&
            (buttons & BTN_FIRE) && !p->on_ground) {
            p->vy100 -= 65; /* sustained thrust, capped below */
            if (p->vy100 < -700) p->vy100 = -700;
        }
        p->vy100 += p->gravity;
        if (p->vy100 > (int32_t)p->max_fall_speed * 100)
            p->vy100 = (int32_t)p->max_fall_speed * 100;
        /* Spring/external launches must be independent of the Jump button,
           but NOT given the long held-jump arc (Stage 3.17 regression).
           Apply the existing short-hop gravity to an external ascent on
           EVERY rising frame. A normal jump still gets that extra gravity
           only when the Jump button is released. */
        if (p->vy100 < 0 && (p->external_ascent || !jumping))
            p->vy100 += p->gravity;
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
                if (special_type(m, x, y, w, h) == GAME_TILE_HAZARD)
                    crossed_hazard = 1;
            }
        } else if (nextY < y) {
            for (int32_t testY = y - 1; testY >= nextY; --testY) {
                if (touches_solid(m, x, testY, w, h)) {
                    p->vy100 = 0; blocked = 1; break;
                }
                y = testY;
                if (special_type(m, x, y, w, h) == GAME_TILE_HAZARD)
                    crossed_hazard = 1;
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
        const uint8_t was_in_hazard = p->hazard_contact;
        const uint8_t ended_inside_hazard = p->touch_type == GAME_TILE_HAZARD;
        /* Swept detection creates ENTERED when moving fully across hazards,
           but must not prolong INSIDE after a player has physically left. */
        const uint8_t touching_hazard = ended_inside_hazard ||
            (!was_in_hazard && crossed_hazard);
        if (touching_hazard) p->touch_type = GAME_TILE_HAZARD;
        /* Update contact BEFORE dispatch: callbacks may reset, teleport or
           mark the player dead. A tile-to-tile move stays INSIDE because
           special_type() sees any overlapping hazard tile. Swept contacts
           still generate ENTERED even when a fast player crosses entirely
           through a hazard in one frame (followed by EXITED next frame). */
        p->hazard_contact = touching_hazard;
        if (p->vy100 >= 0 || p->on_ground)
            p->external_ascent = 0;
        p->physics_vy100 = p->vy100;
        if (touching_hazard && !was_in_hazard) {
            game_hazard_notify(GAME_HAZARD_TILE_ENTERED, x, y);
        } else if (touching_hazard) {
            game_hazard_notify(GAME_HAZARD_TILE_INSIDE, x, y);
        } else if (was_in_hazard) {
            game_hazard_notify(GAME_HAZARD_TILE_EXITED, x, y);
        }
        /* A handler can explicitly kill or teleport the player. Never
           process more batched frames after it changes that state. */
        if (game_death_is_dead() || p->x100 / 100 != x || p->y100 / 100 != y)
            return;
        const uint8_t currentZones = cg_zone_callback ?
            game_zone_at_player(m, x, y, w, h) : 0;
        const uint8_t previousZones = p->zone_contacts;
        p->zone_contacts = currentZones; /* Store before callback/teleport. */
        if (cg_zone_callback) {
            for (uint8_t z = 0; z < 8; ++z) {
                const uint8_t bit = (uint8_t)(1u << z);
                const uint8_t event = (currentZones & bit)
                    ? ((previousZones & bit) ? GAME_ZONE_INSIDE : GAME_ZONE_ENTERED)
                    : ((previousZones & bit) ? GAME_ZONE_EXITED : 0);
                if (!event) continue;
                cg_zone_callback((uint8_t)(z+1), event, x, y, cg_zone_user);
                if (game_death_is_dead() || p->x100 / 100 != x || p->y100 / 100 != y)
                    return;
            }
        }
    }
}
void game_tile_player_screen(game_tile_player_t *p, int32_t cameraX, int32_t cameraY)
{
    if (!p || !p->sprite) return;
    p->sprite->drawx = (int16_t)limit(p->x100 / 100 - cameraX, -32768, 32767);
    p->sprite->drawy = (int16_t)limit(p->y100 / 100 - cameraY, -32768, 32767);
}
