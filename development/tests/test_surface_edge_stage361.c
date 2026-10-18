/* Stage 3.61 centre-foot entry gate, extended in Stage 3.66: even with
 * centre-foot contact, a flat ledge supporting the rear of the player's
 * collision box must prevent premature passive sliding. Normal landing
 * collisions remain unchanged.
 * Build from the project root:
 *   gcc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *       -Iidelibs/api -Iidelibs/codehelpers/game \
 *       development/tests/test_surface_edge_stage361.c \
 *       -Wl,--gc-sections -o /tmp/test_surface_edge_stage361
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

static uint8_t collision[16*8];
static uint16_t refs[16*8];
static game_tile_shape_t shape;
static game_tile_shape_point_t pts[2];
static game_tile_shape_instance_t inst;
static game_tilemap_t map;

static void setup(uint8_t mirror)
{
    memset(collision, 0, sizeof(collision));
    memset(refs, 0, sizeof(refs));
    memset(&map, 0, sizeof(map));
    shape=(game_tile_shape_t){4,3,0,2,0,1}; /* 0% damping, enabled */
    pts[0]=(game_tile_shape_point_t){0,0};
    pts[1]=(game_tile_shape_point_t){31,16};
    inst=(game_tile_shape_instance_t){4,1,0,mirror};
    map.width=16; map.height=8; map.tile_size=8;
    map.collision=collision; map.shape_refs=refs;
    map.shape_defs=&shape; map.shape_points=pts;
    map.shape_instances=&inst; map.shape_instance_count=1; map.shape_count=1;
    for(int row=1;row<=3;row++) for(int col=4;col<8;col++) {
        collision[row*16+col]=GAME_TILE_POINT_SLOPE;
        refs[row*16+col]=1;
    }
}

static void check_overlap(int32_t x, int32_t feet, uint8_t expected,
                          int expectedSign)
{
    int32_t accel=999;
    uint8_t damp=73;
    const uint8_t on=cg_passive_shape_surface(&map,x,feet,8,35,&accel,&damp, 0);
    if (on != expected) fprintf(stderr,"FAILED x=%ld feet=%ld mirror=%u actual=%u expected=%u accel=%ld\n",(long)x,(long)feet,inst.flags,on,expected,(long)accel);
    assert(on==expected);
    if(!on) { assert(accel==999 && damp==73); }
    else { assert(damp==0); assert((accel>0)-(accel<0)==expectedSign); }
}

static void test_edges(void)
{
    setup(0);
    /* Shape spans [32,63]. Only 1..3 foot pixels over the slope: no pull. */
    check_overlap(25,8,0,0);  /* 1 px over */
    check_overlap(27,8,0,0);  /* 3 px over */
    check_overlap(28,8,1,+1); /* 4 px over: centre crosses */
    check_overlap(29,8,1,+1); /* 5 px over */
    check_overlap(63,24,0,0); /* 1 px over at far end */
    check_overlap(61,24,0,0); /* 3 px over */
    check_overlap(60,24,1,+1); /* 4 px over */

    setup(1);
    /* Mirror swaps downhill direction and the high/low end. */
    check_overlap(25,24,0,0);
    check_overlap(27,24,0,0);
    check_overlap(28,24,1,-1);
    check_overlap(29,21,1,-1);
    check_overlap(63,8,0,0);
    check_overlap(61,8,0,0);
    check_overlap(60,8,1,-1);
}

static void test_real_player_at_cliff(void)
{
    setup(0);
    /* Solid flat ledge at x=0..31, same height as the slope entrance. */
    for(int col=0;col<4;col++) collision[16+col]=GAME_TILE_SOLID;
    gfxbob_t sprite={0}; sprite.width=8; sprite.height=4;
    game_tile_player_t p={0};
    p.map=&map; p.sprite=&sprite; p.gravity=35; p.walk_speed=3;
    p.jump_speed=7; p.max_fall_speed=9; p.force_drag_percent=12;
    p.x100=25*100; p.y100=4*100; p.on_ground=1;
    for(int f=0;f<30;f++) game_tile_player_run(&p,0,1);
    assert(p.on_ground && p.x100==2500 && p.force_vx100==0);
    /* Stage 3.66 refinement: centre contact is necessary but not enough
     * while the player's heels are still supported on the flat ledge. */
    p.x100=28*100; p.y100=4*100; p.force_remainder100=0;
    p.force_vx100=0; p.vy100=0; p.on_ground=1;
    for (int f=0; f<30; ++f) game_tile_player_run(&p,0,1);
    assert(p.force_vx100 == 0 && p.x100 == 2800);
    assert(p.on_ground);
    /* Once the whole footprint has left flat collision the downhill
     * slide can start under gravity. */
    p.x100=32*100; p.y100=4*100; p.force_remainder100=0;
    p.force_vx100=0; p.vy100=0; p.on_ground=1;
    game_tile_player_run(&p,0,1);
    assert(p.force_vx100>0);
}

int main(void)
{
    test_edges();
    test_real_player_at_cliff();
    puts("Stage 3.61 cliff-edge gating: all overlap, mirror and player tests passed");
    return 0;
}
