/* Stage 3.88: optional per-loop falloff following completed loop exit.
 * cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *   -Iidelibs/api -Iidelibs/codehelpers/game \
 *   development/tests/test_stage388_loop_coast_falloff.c \
 *   -Wl,--gc-sections -o /tmp/gg388_falloff && /tmp/gg388_falloff
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

#define W 64
#define H 64
static uint8_t collision[W*H];
static game_tile_loop_t loops[] = {
    {100, 100, 40, 100, 0, 1, 0},
    {180, 100, 40, 100, 0, 1, 50}
};
static game_tilemap_t map;
static gfxbob_t bob;

static game_tile_player_t leave_loop(int sign, int index, int falloff)
{
    game_tile_player_t p;
    assert(game_tile_player_start(&p, &map, &bob));
    loops[index].coast_after_exit = 1;
    loops[index].coast_falloff_permille = (uint16_t)falloff;
    p.loop_index = (uint8_t)(index+1);
    p.loop_phase = sign * 65400;
    p.loop_speed100 = sign * 1000;
    p.gravity = 0;
    p.force_drag_percent = 0; /* preserve full loop speed during exit tick */
    assert(cg_loop_tick(&p, 0, 16, 16) == 1);
    assert(p.loop_index == 0);
    assert(p.loop_coast_active);
    assert(p.force_vx100 == sign * 1000);
    assert(p.loop_coast_falloff_permille == falloff);
    p.force_drag_percent = 30;
    p.loop_cooldown = 100; /* isolate exit coast from entering another loop */
    return p;
}

int main(void)
{
    memset(&map, 0, sizeof(map));
    memset(&bob, 0, sizeof(bob));
    map.width=W; map.height=H; map.tile_size=8;
    map.collision=collision; map.loops=loops; map.loop_count=2;
    bob.width=bob.height=16; bob.scale=100;

    for (int sign=-1; sign<=1; sign+=2) {
        game_tile_player_t p=leave_loop(sign, 0, 0);
        game_tile_player_run(&p, 0, 10);
        assert(p.force_vx100 == sign*1000);
        assert(p.loop_coast_active);
        /* 5.0% loss per tick, not 5 px or 50% per tick. */
        p=leave_loop(sign, 1, 50);
        game_tile_player_run(&p, 0, 1);
        assert(p.force_vx100 == sign*950);
        game_tile_player_run(&p, 0, 1);
        assert(p.force_vx100 == sign*902); // 950*0.95 -> 902
        game_tile_player_run(&p, 0, 1);
        assert(p.force_vx100 == sign*856);
        /* Gravity / airborne movement must not cancel falloff. */
        p=leave_loop(sign, 1, 50);
        p.on_ground=0; p.gravity=35;
        game_tile_player_run(&p, 0, 2);
        assert(p.force_vx100 == sign*902);
        /* Steering cancels special coast; normal preset friction returns. */
        p=leave_loop(sign, 1, 50);
        game_tile_player_run(&p, sign>0? BTN_RIGHT:BTN_LEFT, 1);
        assert(p.loop_coast_active == 0);
        assert(p.loop_coast_falloff_permille == 0);
        assert(p.force_vx100 == sign*700); // 30% ordinary drag
        /* Jump doesn't count as steering. */
        p=leave_loop(sign, 1, 50);
        game_tile_player_run(&p, BTN_FIRE, 1);
        assert(p.loop_coast_active == 1);
        assert(p.force_vx100 == sign*950);
        /* A loop configured with coast disabled ignores configured falloff. */
        loops[1].coast_after_exit=0;
        {
            game_tile_player_t q;
            assert(game_tile_player_start(&q,&map,&bob));
            q.loop_index=2; q.loop_phase=sign*65400; q.loop_speed100=sign*1000;
            q.gravity=0; q.force_drag_percent=0;
            assert(cg_loop_tick(&q, 0, 16, 16) == 1);
            assert(!q.loop_coast_active && !q.loop_coast_falloff_permille);
        }
        loops[1].coast_after_exit=1;
    }
    /* Wall impact clears both momentum and falloff latch. */
    {
        game_tile_player_t p=leave_loop(1,1,50);
        memset(collision,0,sizeof(collision));
        collision[15*W + 26] = GAME_TILE_SOLID;
        collision[16*W + 26] = GAME_TILE_SOLID;
        collision[17*W + 26] = GAME_TILE_SOLID;
        p.x100=19100; p.y100=12400;
        game_tile_player_run(&p,0,1);
        assert(!p.loop_coast_active && !p.loop_coast_falloff_permille);
        assert(!p.force_vx100);
        memset(collision,0,sizeof(collision));
    }
    /* Reset or attach to another loop clears the previous falloff. */
    {
        game_tile_player_t p=leave_loop(1,1,50);
        game_tile_player_reset(&p,5,5);
        assert(!p.loop_coast_active && !p.loop_coast_falloff_permille);
        p.loop_coast_active=1; p.loop_coast_falloff_permille=70;
        p.x100=(loops[0].center_x-8)*100;
        p.y100=(loops[0].center_y+loops[0].radius-16)*100;
        p.slide_velocity100=800; p.on_ground=1;
        assert(cg_loop_try_attach(&p,16,16));
        assert(!p.loop_coast_active && !p.loop_coast_falloff_permille);
    }
    puts("PASS: loop coast per-frame falloff, old zero behaviour, directions, airborne, steer/wall/reset");
    return 0;
}
