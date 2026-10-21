/* Stage 4.38 — separate vulnerable zone, body hazard and one-shot death atlas. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
void run_spline(game_spline_t *p, uint16_t frames) {(void)p;(void)frames;}
void set_spline_pos(game_spline_t *p, int16_t x, int16_t y) {(void)p;(void)x;(void)y;}
void run_animation(game_animation_t *p, uint16_t frames) {(void)p;(void)frames;}
void test_bob(gfxbob_t *s) {(void)s;}
static game_world_object_t enemy;
static game_world_player_t player;
static gfxbob_t bob;
static int32_t x, y, vy;
static uint8_t on_ground;
static void reset(void) {
    memset(&enemy,0,sizeof(enemy)); memset(&player,0,sizeof(player));
    memset(&bob,0,sizeof(bob));
    assert(game_world_object_start(&enemy,GAME_OBJECT_ENEMY,&bob,60,80,16,16));
    enemy.break_hits_required=2;enemy.break_bounce=1;enemy.break_strength=8;
    enemy.enemy_stomp_offset_x=-6;
    enemy.enemy_stomp_offset_y=-8;
    enemy.enemy_stomp_width=28;
    enemy.enemy_stomp_height=8;
    enemy.enemy_defeat_frame=20;
    enemy.enemy_defeat_count=4;
    enemy.enemy_defeat_delay=3;
    x=44*100; y=45*100; vy=0; on_ground=0;
    player.x100=&x;player.y100=&y;player.vy100=&vy;player.on_ground=&on_ground;
    player.width=16;player.height=16;
}
static void stomp(void){
    y=45*100;vy=450;on_ground=0;
    game_world_objects_update(&enemy,1,1);
    game_world_objects_before(&enemy,1,&player);
    y=60*100;
    game_world_objects_after(&enemy,1,&player);
    game_world_objects_hazards(&enemy,1,&player);
}
int main(void){
    reset();
    /* X=44: player right edge=60, EXACTLY at body left edge. Old body-only
       landing rejects it, new vulnerable top (-6px X) accepts it. */
    stomp();
    assert(enemy.break_hits_done==1 && !player.hurt_triggered);
    assert(vy==-800 && y==(72-16)*100 && enemy.active);
    /* One landing only counts once, even when still near the vulnerable area. */
    game_world_objects_before(&enemy,1,&player);
    game_world_objects_after(&enemy,1,&player);
    assert(enemy.break_hits_done==1);
    /* Move the player away, rearm and stomp again. */
    y=0;vy=-200;game_world_objects_before(&enemy,1,&player);
    game_world_objects_after(&enemy,1,&player);
    assert(!enemy.break_touching);
    stomp();
    assert(enemy.break_hits_done==2 && !enemy.active && enemy.break_triggered);
    assert(bob.index==20 && enemy.enemy_dying==12);
    game_world_objects_update(&enemy,1,2);assert(bob.index==20 && enemy.enemy_dying==10);
    game_world_objects_update(&enemy,1,1);assert(bob.index==21 && enemy.enemy_dying==9);
    game_world_objects_update(&enemy,1,3);assert(bob.index==22 && enemy.enemy_dying==6);
    game_world_objects_update(&enemy,1,3);assert(bob.index==23 && enemy.enemy_dying==3);
    game_world_objects_update(&enemy,1,2);assert(bob.index==23 && enemy.enemy_dying==1);
    game_world_objects_update(&enemy,1,1);assert(enemy.enemy_dying==0);
    /* Side hit: body still hurts, even though vulnerable box was widened. */
    reset();x=36*100;y=82*100;
    game_world_objects_before(&enemy,1,&player);
    x=62*100;game_world_objects_after(&enemy,1,&player);
    game_world_objects_hazards(&enemy,1,&player);
    assert(enemy.break_hits_done==0 && player.hurt_triggered);
    /* Merely being inside the grace zone while stationary must NOT stomp. */
    reset();x=62*100;y=59*100;vy=0;
    game_world_objects_before(&enemy,1,&player);
    game_world_objects_after(&enemy,1,&player);
    assert(enemy.break_hits_done==0);
    /* Legacy unmodified single-frame behavior is preserved by fallback. */
    reset();enemy.enemy_defeat_count=1;enemy.enemy_defeat_delay=0;
    enemy.enemy_defeat_frames=11;enemy.break_hits_required=1;
    stomp();assert(enemy.enemy_dying==11 && bob.index==20);
    game_world_objects_update(&enemy,1,10);assert(enemy.enemy_dying==1);
    game_world_objects_update(&enemy,1,1);assert(enemy.enemy_dying==0);
    puts("PASS: expanded vulnerable landing, separate body hazard, rearm, 4-frame one-shot death animation, legacy pose timer");
}
