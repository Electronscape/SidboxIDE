/* Stage 4.36 - stompable enemies use existing player collision and damage callbacks. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
void run_spline(game_spline_t *p, uint16_t frames) {(void)p;(void)frames;}
void set_spline_pos(game_spline_t *p, int16_t x, int16_t y) {(void)p;(void)x;(void)y;}
void run_animation(game_animation_t *p, uint16_t frames) {(void)p;(void)frames;}
static int drawings;
void test_bob(gfxbob_t *s) {(void)s; ++drawings;}
static game_world_object_t enemy;
static game_world_player_t player;
static gfxbob_t bob;
static int32_t x,y,vy;
static uint8_t ground;
static void reset(void) {
    memset(&enemy,0,sizeof enemy);memset(&player,0,sizeof player);memset(&bob,0,sizeof bob);
    x=40*100;y=56*100;vy=0;ground=0;drawings=0;
    player.x100=&x;player.y100=&y;player.vy100=&vy;player.on_ground=&ground;
    player.width=16;player.height=16;
    assert(game_world_object_start(&enemy,GAME_OBJECT_ENEMY,&bob,32,80,48,8));
    enemy.break_hits_required=3;enemy.break_bounce=1;enemy.break_strength=8;
    enemy.enemy_defeat_frame=7;enemy.enemy_defeat_frames=10;
}
static void stomp(void){
    y=56*100;vy=300;game_world_objects_update(&enemy,1,1);
    game_world_objects_before(&enemy,1,&player);
    y=70*100;game_world_objects_after(&enemy,1,&player);
    game_world_objects_hazards(&enemy,1,&player);
}
static void leave(void){
    y=20*100;vy=-400;game_world_objects_update(&enemy,1,1);
    game_world_objects_before(&enemy,1,&player);
    game_world_objects_after(&enemy,1,&player);
    game_world_objects_hazards(&enemy,1,&player);
}
int main(void){
    reset();stomp();
    assert(enemy.break_hits_done==1 && enemy.active && enemy.break_hit_triggered);
    assert(vy==-800 && !player.hurt_triggered);
    /* Continuously overlapping may not count another hit. */
    game_world_objects_before(&enemy,1,&player);
    game_world_objects_after(&enemy,1,&player);
    game_world_objects_hazards(&enemy,1,&player);
    assert(enemy.break_hits_done==1 && !player.hurt_triggered);
    leave();stomp();assert(enemy.break_hits_done==2 && enemy.active);
    leave();stomp();
    assert(enemy.break_hits_done==3 && !enemy.active && enemy.break_triggered);
    assert(bob.index==7 && enemy.enemy_dying==10);
    game_world_objects_draw_layer(&enemy,1,0,0,0);assert(drawings==1);
    game_world_objects_update(&enemy,1,9);assert(enemy.enemy_dying==1);
    game_world_objects_update(&enemy,1,1);assert(enemy.enemy_dying==0);
    game_world_objects_draw_layer(&enemy,1,0,0,0);assert(drawings==1);
    /* Side touch produces a single hurt event and uses existing grace period. */
    reset();x=20*100;y=78*100;
    game_world_objects_before(&enemy,1,&player);
    x=36*100;game_world_objects_after(&enemy,1,&player);
    game_world_objects_hazards(&enemy,1,&player);
    assert(player.hurt_triggered && player.hurt_damage_this_frame==1);
    assert(enemy.break_hits_done==0);
    game_world_objects_before(&enemy,1,&player);
    game_world_objects_after(&enemy,1,&player);
    game_world_objects_hazards(&enemy,1,&player);
    assert(!player.hurt_triggered);
    /* Turning side damage off must not disable valid stomps. */
    reset();enemy.enemy_hurts_on_touch=0;x=20*100;y=78*100;
    game_world_objects_before(&enemy,1,&player);x=36*100;
    game_world_objects_after(&enemy,1,&player);game_world_objects_hazards(&enemy,1,&player);
    assert(!player.hurt_triggered);leave();stomp();assert(enemy.break_hits_done==1);
    puts("PASS: multi-hit stomp, fixed bounce, one hurt per side contact, timed defeat frame");
}
