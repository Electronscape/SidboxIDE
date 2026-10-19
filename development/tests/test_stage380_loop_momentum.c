/* Stage 3.80 loop momentum: native test, no STM32 needed.
 * From the IDE source root:
 * cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *   -Iidelibs/api -Iidelibs/codehelpers/game \
 *   development/tests/test_stage380_loop_momentum.c \
 *   -Wl,--gc-sections -o /tmp/gg380_loops && /tmp/gg380_loops
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

#define MW 64
#define MH 64
static uint8_t cells[MW * MH];
static game_tile_loop_t track = {100, 100, 40, 100, 0};
static game_tilemap_t map;
static gfxbob_t bob;

static game_tile_player_t player(int32_t phase, int32_t speed, uint16_t boost)
{
    game_tile_player_t p = {0};
    track.downhill_boost100 = boost;
    assert(game_tile_player_start(&p, &map, &bob));
    p.loop_index = 1;
    p.loop_phase = phase;
    p.loop_speed100 = speed;
    p.gravity = 0;  /* deterministic: isolate the new boost */
    p.force_drag_percent = 0;
    return p;
}
static void check_half(int32_t phase, int32_t speed, uint16_t boost,
                       int32_t expected)
{
    game_tile_player_t p = player(phase, speed, boost);
    assert(cg_loop_tick(&p, 0, 16, 16) == 1);
    assert(p.loop_index == 1);
    assert(p.loop_speed100 == expected);
}
int main(void)
{
    memset(&map, 0, sizeof(map));
    map.width = MW; map.height = MH; map.tile_size = 8;
    map.collision = cells; map.loops = &track; map.loop_count = 1;
    memset(&bob, 0, sizeof(bob));
    bob.width = 16; bob.height = 16; bob.scale = 100;
    /* Uphill must be unchanged, even with high friction and gravity. */
    for (int sign = -1; sign <= 1; sign += 2) {
        check_half(sign * 15000, sign * 500, 0, sign * 500);
        check_half(sign * 15000, sign * 500, 25, sign * 500);
        check_half(sign * 40000, sign * 500, 25, sign * 525);
        check_half(sign * 40000, sign * 500, 100, sign * 600);
        check_half(sign * 40000, sign * 3190, 100, sign * 3200);
    }
    /* Legacy mode with gravity and drag remains the original calculation. */
    {
        game_tile_player_t p = player(15000, 500, 0);
        p.gravity = 35;
        p.force_drag_percent = 3;
        const int32_t legacy = (500 - 35 * cg_loop_sin(15000) / 16384) * 97 / 100;
        assert(cg_loop_tick(&p, 0, 16, 16) == 1);
        assert(p.loop_speed100 == legacy);
    }
    /* Boosted uphill speed is held even if gravity and drag are nonzero. */
    {
        game_tile_player_t p = player(-15000, -800, 50);
        p.gravity = 35; p.force_drag_percent = 12;
        assert(cg_loop_tick(&p, 0, 16, 16) == 1);
        assert(p.loop_speed100 == -800);
    }
    /* The last downhill step keeps its extra speed when returned to tiles. */
    for (int sign = -1; sign <= 1; sign += 2) {
        game_tile_player_t p = player(sign * 65400, sign * 600, 50);
        assert(cg_loop_tick(&p, 0, 16, 16) == 1);
        assert(p.loop_index == 0);
        assert(p.force_vx100 == sign * 650);
    }
    /* Full attached traversal: from normal bottom entry to bottom exit. */
    for (int sign = -1; sign <= 1; sign += 2) {
        game_tile_player_t p = player(0, 0, 25);
        p.loop_index = 0; p.gravity = 35; p.force_drag_percent = 12;
        p.x100 = (track.center_x - 8) * 100;
        p.y100 = (track.center_y + track.radius - 16) * 100;
        p.slide_velocity100 = sign * 900;
        p.on_ground = 1;
        assert(cg_loop_try_attach(&p, 16, 16));
        assert(p.loop_speed100 == sign * 900);
        int frames = 0;
        while (p.loop_index && frames++ < 200)
            assert(cg_loop_tick(&p, 0, 16, 16) == 1);
        assert(frames < 200);
        assert(p.loop_index == 0);
        assert(p.force_vx100 * sign > 900);
    }
    puts("PASS: loop momentum uphill, downhill, both directions, cap, old physics, exit");
    return 0;
}
