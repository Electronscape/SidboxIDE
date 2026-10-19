/* Stage 3.86: loop full-lap coast is optional and terminates on wall/input.
 * Native-only test using the real SIDBOX helper; compile with:
 * cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *   -Iidelibs/api -Iidelibs/codehelpers/game \
 *   development/tests/test_stage386_loop_friction_coast.c \
 *   -Wl,--gc-sections -o /tmp/gg386_loop_coast && /tmp/gg386_loop_coast
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

#define MW 64
#define MH 64
static uint8_t collisions[MW * MH];
static game_tile_loop_t loop = {100, 100, 40, 100, 0, 0, 0};
static game_tilemap_t level;
static gfxbob_t bob;

static game_tile_player_t just_finished(int direction, int enable)
{
    game_tile_player_t p;
    assert(game_tile_player_start(&p, &level, &bob));
    loop.coast_after_exit = enable != 0;
    p.loop_index = 1;
    p.loop_phase = direction * 65400;
    p.loop_speed100 = direction * 600;
    p.gravity = 0;
    p.force_drag_percent = 0; /* isolate post-exit friction from loop drag */
    assert(cg_loop_tick(&p, 0, 16, 16) == 1);
    assert(p.loop_index == 0);
    assert(p.force_vx100 == direction * 600);
    assert(p.loop_coast_active == (enable != 0));
    p.force_drag_percent = 12;
    return p;
}

int main(void)
{
    memset(&level, 0, sizeof(level));
    level.width = MW;
    level.height = MH;
    level.tile_size = 8;
    level.collision = collisions;
    level.loops = &loop;
    level.loop_count = 1;
    memset(&bob, 0, sizeof(bob));
    bob.width = bob.height = 16;
    bob.scale = 100;

    for (int sign = -1; sign <= 1; sign += 2) {
        /* Opt-in preserves horizontal speed while there's no steering/wall. */
        game_tile_player_t p = just_finished(sign, 1);
        game_tile_player_run(&p, 0, 3);
        assert(p.loop_coast_active == 1);
        assert(p.force_vx100 == sign * 600);
        /* Player-directed movement hands back normal drag immediately. */
        game_tile_player_run(&p, sign > 0 ? BTN_RIGHT : BTN_LEFT, 1);
        assert(p.loop_coast_active == 0);
        assert(p.force_vx100 == sign * 528);
        game_tile_player_run(&p, 0, 1);
        assert(p.force_vx100 * sign < 528);

        /* Old loops (checkbox off) damp momentum immediately. */
        p = just_finished(sign, 0);
        game_tile_player_run(&p, 0, 1);
        assert(p.loop_coast_active == 0);
        assert(p.force_vx100 == sign * 528);

        /* A jump without horizontal input isn't a request to steer. */
        p = just_finished(sign, 1);
        game_tile_player_run(&p, BTN_FIRE, 1);
        assert(p.loop_coast_active == 1);
        assert(p.force_vx100 == sign * 600);
    }

    /* Leaving the track early is NOT a successful lap and cannot turn on coast. */
    {
        game_tile_player_t p;
        assert(game_tile_player_start(&p, &level, &bob));
        loop.coast_after_exit = 1;
        p.loop_index = 1;
        p.loop_phase = 21000;
        p.loop_speed100 = 5; /* below the minimum track-holding speed */
        p.gravity = 0;
        assert(cg_loop_tick(&p, 0, 16, 16) == 1);
        assert(p.loop_index == 0);
        assert(p.loop_coast_active == 0);
    }

    /* Hit a solid tile while coasting: collision zeroes force and cancels mode. */
    {
        game_tile_player_t p = just_finished(1, 1);
        memset(collisions, 0, sizeof(collisions));
        collisions[15 * MW + 26] = GAME_TILE_SOLID; /* x=208, y=120 */
        collisions[16 * MW + 26] = GAME_TILE_SOLID;
        collisions[17 * MW + 26] = GAME_TILE_SOLID;
        p.x100 = 19100; /* right edge just before the wall */
        p.y100 = 12400;
        game_tile_player_run(&p, 0, 1);
        assert(p.loop_coast_active == 0);
        assert(p.force_vx100 == 0);
        assert(p.force_remainder100 == 0);
    }

    /* Reset and entering a new loop must never retain an old coast latch. */
    {
        game_tile_player_t p = just_finished(1, 1);
        game_tile_player_reset(&p, 5, 5);
        assert(p.loop_coast_active == 0);
        p.loop_coast_active = 1;
        p.x100 = (loop.center_x - 8) * 100;
        p.y100 = (loop.center_y + loop.radius - 16) * 100;
        p.slide_velocity100 = 800;
        p.on_ground = 1;
        assert(cg_loop_try_attach(&p, 16, 16));
        assert(p.loop_coast_active == 0);
    }

    puts("PASS: loop friction coasting after full lap, both directions, old behaviour, steering, walls, reset");
    return 0;
}
