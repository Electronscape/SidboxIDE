/* Stage 4.37: patrol + facing + shared Murder Object hurt effects. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
void run_spline(game_spline_t *p, uint16_t frames) {(void)p;(void)frames;}
void set_spline_pos(game_spline_t *p, int16_t x, int16_t y) {(void)p;(void)x;(void)y;}
void run_animation(game_animation_t *p, uint16_t frames) {(void)p;(void)frames;}
void test_bob(gfxbob_t *s) {(void)s;}
/* Floor from y>=100, a 2-pixel rise from x=40, vertical wall from x=90.
   All tests are world-space using the exported actor-blocked semantics. */
static uint8_t tile_collision(int32_t x,int32_t y,uint16_t w,uint16_t h,void *ctx) {
    (void)ctx;
    if (x < 0 || x + w > 90) return 1;
    if (y + h > (x + w > 40 ? 98 : 100)) return 1;
    return 0;
}
int main(void) {
    game_world_object_t o; gfxbob_t b = {0};
    assert(game_world_object_start(&o,GAME_OBJECT_ENEMY,&b,12,90,8,10));
    o.enemy_roam=1; o.enemy_roam_speed=2; o.enemy_step_height=4;
    o.enemy_roam_direction=1; o.enemy_base_flip_x=0;
    game_world_objects_update(&o,1,1);
    game_world_objects_roam(&o,1,12,tile_collision,0);
    assert(o.x==36 && o.y==88);
    game_world_objects_update(&o,1,1);
    game_world_objects_roam(&o,1,1,tile_collision,0);
    assert(o.x==38 && o.y==88); /* two-pixel tile rise */
    game_world_objects_update(&o,1,1);
    game_world_objects_roam(&o,1,40,tile_collision,0);
    assert(o.x <= 82 && o.enemy_roam_direction == -1);
    assert((b.flags & BLIT_FLAG_FLIP_X) != 0);
    /* Existing flip is mirrored relative to enemy's movement. */
    o.enemy_base_flip_x=1; game_world_objects_roam(&o,1,1,tile_collision,0);
    assert((b.flags & BLIT_FLAG_FLIP_X) == 0);
    /* Enemy damage: positive knockback X pushes away on either side. */
    int32_t x=0,y=90*100,vy=0,force=0; uint8_t ground=0;
    game_world_player_t p = {0}; p.x100=&x; p.y100=&y; p.vy100=&vy;
    p.on_ground=&ground;p.width=8;p.height=10;p.spring_force_vx100=&force;
    o.x=40;o.y=90;o.width=8;o.height=10;o.enemy_roam=0;
    o.hazard_damage=3; o.hazard_kick=1;o.hazard_kick_x=7;o.hazard_kick_y=-6;
    o.hazard_hurt_animation=1;o.hazard_flash=1;o.hazard_flash_colour=12;
    o.hazard_flash_count=3; o.hazard_flash_frames=4;
    /* Arrive from left, without registering a stomp. */
    x=25*100; game_world_objects_before(&o,1,&p);
    x=35*100;game_world_objects_after(&o,1,&p);
    game_world_objects_hazards(&o,1,&p);
    assert(p.hurt_triggered && p.hurt_damage_this_frame==3);
    assert(force==-700 && vy==-600);
    assert(p.hurt_anim_active && p.hurt_flash_active && p.hurt_flash_colour==12);
    /* Second separate contact from right after invulnerability ends. */
    o.hazard_touching=0;p.hurt_ticks_remaining=0;p.hurt_triggered=0;
    x=55*100;force=0; game_world_objects_before(&o,1,&p);
    x=44*100;game_world_objects_after(&o,1,&p);
    game_world_objects_hazards(&o,1,&p);
    assert(p.hurt_triggered && force==700);
    puts("PASS: slope-following tile patrol, wall reversal, flip-X facing, two-way hit knockback, hurt and flash");
    return 0;
}
