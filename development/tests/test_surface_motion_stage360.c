/* End-to-end SIDBOX V1 player solver test, from rest on an enabled slope. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"
int main(void) {
    uint8_t collision[20*8] = {0};
    uint16_t refs[20*8] = {0};
    game_tile_shape_t shape = {8,4,0,2,0,1}; /* 0% damping, enabled */
    game_tile_shape_point_t pts[] = {{0,8},{64,24}};
    game_tile_shape_instance_t inst = {0,0,0,0};
    game_tilemap_t m={0};
    m.width=20; m.height=8; m.tile_size=8; m.collision=collision;
    m.shape_refs=refs; m.shape_defs=&shape; m.shape_points=pts;
    m.shape_instances=&inst; m.shape_instance_count=1; m.shape_count=1;
    for (int y=0;y<4;y++) for (int x=0;x<8;x++) {
        collision[y*20+x]=GAME_TILE_POINT_SLOPE; refs[y*20+x]=1;
    }
    gfxbob_t sprite={0}; sprite.width=4; sprite.height=4;
    game_tile_player_t p={0};
    p.map=&m; p.sprite=&sprite; p.gravity=35; p.walk_speed=3;
    p.max_fall_speed=9; p.jump_speed=7; p.force_drag_percent=12;
    p.x100=0; p.y100=400; p.on_ground=1;
    for(int i=0;i<30;i++) game_tile_player_run(&p,0,1);
    printf("slide x=%ld y=%ld velocity=%ld grounded=%u\n",
       (long)(p.x100/100),(long)(p.y100/100),(long)p.force_vx100,p.on_ground);
    assert(p.x100 > 0);
    assert(p.on_ground);
    /* 100% sticky surface must stop even accumulated subpixel drift. */
    shape.damping_percent=100;
    p.x100=0; p.y100=400; p.vy100=0; p.force_vx100=0;
    p.force_remainder100=0; p.on_ground=1;
    for (int i=0;i<60;i++) game_tile_player_run(&p,0,1);
    assert(p.x100==0 && p.force_vx100==0);
    /* Legacy/default stamp: inertia remains off unless opted in. */
    shape.surface_flags=0;
    p.x100=0; p.y100=400; p.vy100=0; p.force_vx100=0;
    p.force_remainder100=0; p.on_ground=1;
    for (int i=0;i<60;i++) game_tile_player_run(&p,0,1);
    assert(p.x100==0);
    puts("Stage 3.60 player motion: slide, sticky and disabled passed");
    return 0;
}
