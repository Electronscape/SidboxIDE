/* Stage 3.87: preserving horizontal loop-coast momentum must not force a
 * player to follow a downhill slope or snap to a lower cliff-side floor.
 * Native test (no SIDBOX firmware required):
 * cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *   -Iidelibs/api -Iidelibs/codehelpers/game \
 *   development/tests/test_stage387_loop_coast_cliff.c \
 *   -Wl,--gc-sections -o /tmp/gg387_cliff && /tmp/gg387_cliff
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

#define MW 64
#define MH 32
static uint8_t tiles[MW * MH];
static gfxbob_t sprite;
static game_tilemap_t map;

static game_tile_player_t player_at(int x, int y, int vx100, int coast)
{
    game_tile_player_t p;
    memset(&p, 0, sizeof(p));
    p.map = &map;
    p.sprite = &sprite;
    p.x100 = x * 100;
    p.y100 = y * 100;
    p.walk_speed = 3;
    p.max_fall_speed = 9;
    p.jump_speed = 7;
    p.gravity = 35;
    p.force_drag_percent = 12;
    p.on_ground = 1;
    p.force_vx100 = vx100;
    p.loop_coast_active = coast;
    return p;
}

static void setup(void)
{
    memset(tiles, 0, sizeof(tiles));
    memset(&map, 0, sizeof(map));
    memset(&sprite, 0, sizeof(sprite));
    sprite.width = 4;
    sprite.height = 8;
    map.width = MW;
    map.height = MH;
    map.tile_size = 8;
    map.collision = tiles;
}

static void downhill_into_lower_ground(void)
{
    setup();
    for (int tx = 0; tx < 12; ++tx)
        tiles[10 * MW + tx] = GAME_TILE_SOLID;   /* x=0..95, floor y=80 */
    tiles[10 * MW + 12] = GAME_TILE_SLOPE_DOWN; /* x=96..103, drops 7px */
    for (int tx = 13; tx < 24; ++tx)
        tiles[11 * MW + tx] = GAME_TILE_SOLID;   /* x>=104, floor y=88 */
    game_tile_player_t boosted = player_at(86, 72, 2100, 1);
    game_tile_player_run(&boosted, 0, 1);
    fprintf(stderr, "coasting: x=%d y=%d feet=%d vy=%d grounded=%u\n",
           (int)(boosted.x100/100), (int)(boosted.y100/100),
           (int)(boosted.y100/100 + sprite.height),
           (int)boosted.vy100, boosted.on_ground);
    assert(boosted.x100 / 100 > 103);
    assert(boosted.y100 < 74 * 100); /* no 7px downhill snap */
    assert(!boosted.on_ground); /* gravity rather than surface snapping */
    assert(boosted.vy100 > 0);
    assert(boosted.force_vx100 == 2100); /* the friction exemption persists */

    /* Normal/unticked loops retain their known ground-following behaviour. */
    game_tile_player_t normal = player_at(86, 72, 2100, 0);
    game_tile_player_run(&normal, 0, 1);
    fprintf(stderr, "normal: x=%d y=%d feet=%d vy=%d grounded=%u\n",
           (int)(normal.x100/100), (int)(normal.y100/100 + sprite.height),
           (int)(normal.y100/100 + sprite.height),
           (int)normal.vy100, normal.on_ground);
    assert(normal.y100 > boosted.y100 + 300);
}


static void mirrored_downhill_into_lower_ground(void)
{
    setup();
    for (int tx = 13; tx < 30; ++tx)
        tiles[10 * MW + tx] = GAME_TILE_SOLID; /* higher approach, floor y=80 */
    tiles[10 * MW + 12] = GAME_TILE_SLOPE_UP; /* slopes DOWN when moving left */
    for (int tx = 0; tx < 12; ++tx)
        tiles[11 * MW + tx] = GAME_TILE_SOLID; /* lower ledge, floor y=88 */
    game_tile_player_t boosted = player_at(114, 72, -2100, 1);
    game_tile_player_run(&boosted, 0, 1);
    fprintf(stderr, "mirrored coast: x=%d y=%d vy=%d grounded=%u\n",
            (int)(boosted.x100 / 100), (int)(boosted.y100 / 100),
            (int)boosted.vy100, boosted.on_ground);
    assert(boosted.x100 / 100 < 97);
    assert(boosted.y100 < 74 * 100);
    assert(!boosted.on_ground);
    assert(boosted.vy100 > 0);
    assert(boosted.force_vx100 == -2100);

    game_tile_player_t normal = player_at(114, 72, -2100, 0);
    game_tile_player_run(&normal, 0, 1);
    fprintf(stderr, "mirrored normal: x=%d y=%d grounded=%u\n",
            (int)(normal.x100 / 100), (int)(normal.y100 / 100), normal.on_ground);
    assert(normal.y100 > boosted.y100 + 300);
}

static void flat_cliff(void)
{
    setup();
    for (int tx = 0; tx < 12; ++tx)
        tiles[10 * MW + tx] = GAME_TILE_SOLID;
    for (int tx = 12; tx < 30; ++tx)
        tiles[13 * MW + tx] = GAME_TILE_SOLID; /* lower terrain at y=104 */
    game_tile_player_t p = player_at(87, 72, 1800, 1);
    game_tile_player_run(&p, 0, 1);
    assert(p.x100 / 100 >= 100);
    assert(p.y100 < 74 * 100);
    assert(!p.on_ground);
    assert(p.vy100 > 0);
    assert(p.loop_coast_active);
    const int32_t firstY = p.y100;
    game_tile_player_run(&p, 0, 4);
    assert(p.y100 > firstY); /* gravity brings her down, not floor snap */
    assert(p.loop_coast_active);
}

static void uphill_still_supported(void)
{
    setup();
    for (int tx = 0; tx < 12; ++tx)
        tiles[10 * MW + tx] = GAME_TILE_SOLID;
    tiles[10 * MW + 12] = GAME_TILE_SLOPE_UP;
    game_tile_player_t p = player_at(90, 72, 1200, 1);
    game_tile_player_run(&p, 0, 1);
    fprintf(stderr, "uphill: x=%d y=%d grounded=%u\n",
           (int)(p.x100/100), (int)(p.y100/100), p.on_ground);
    assert(p.x100 > 10000);
    assert(p.y100 <= 72 * 100);
}

int main(void)
{
    downhill_into_lower_ground();
    mirrored_downhill_into_lower_ground();
    flat_cliff();
    uphill_still_supported();
    puts("PASS: loop-coast cliff takes flight under gravity, downhill launch, old physics, uphill ground");
}
