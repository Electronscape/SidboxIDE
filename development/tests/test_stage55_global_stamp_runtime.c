/* Stage 5.5: project-global loop templates and per-world placements.
 * cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *    -Iidelibs/api -Iidelibs/codehelpers/game \
 *    development/tests/test_stage55_global_stamp_runtime.c \
 *    -Wl,--gc-sections -o /tmp/gg55 && /tmp/gg55
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

static uint8_t cells[64 * 64];
static const game_tile_loop_stamp_t shared[] = { {40, 100, 50, 1, 20} };
static const game_tile_loop_placement_t a[] = { {100, 100, 0} };
static const game_tile_loop_placement_t b[] = { {300, 200, 0} };
static game_tilemap_t world_a;
static game_tilemap_t world_b;
static gfxbob_t bob;

int main(void)
{
    memset(&world_a, 0, sizeof(world_a));
    world_a.width = 64; world_a.height = 64; world_a.tile_size = 8;
    world_a.collision = cells;
    world_a.loop_placements = a;
    world_a.loop_stamps = shared;
    world_a.loop_stamp_count = 1;
    world_a.loop_count = 1;
    world_b = world_a;
    world_b.loop_placements = b;
    assert(world_a.loop_stamps == world_b.loop_stamps);
    assert(world_a.loops == NULL && world_b.loops == NULL);
    memset(&bob, 0, sizeof(bob));
    bob.width = 16; bob.height = 16; bob.scale = 100;
    for (int i = 0; i < 2; ++i) {
        game_tilemap_t *world = i == 0 ? &world_a : &world_b;
        const int32_t x = i == 0 ? 100 : 300;
        const int32_t y = i == 0 ? 100 : 200;
        game_tile_player_t p = {0};
        assert(game_tile_player_start(&p, world, &bob));
        p.x100 = (x - 8) * 100;
        p.y100 = (y + 40 - 16) * 100;
        p.slide_velocity100 = 900;
        p.on_ground = 1;
        assert(cg_loop_try_attach(&p, 16, 16));
        assert(p.loop_index == 1);
        p.loop_phase = 40000;
        p.loop_speed100 = 500;
        p.gravity = 0;
        assert(cg_loop_tick(&p, 0, 16, 16) == 1);
        assert(p.loop_speed100 == 550);
    }
    puts("PASS Stage 5.5: two worlds use one project loop stamp with distinct centres");
    return 0;
}
