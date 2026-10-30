#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "gameworldobjects.c"
void run_spline(game_spline_t *p, uint16_t frames) {(void)p;(void)frames;}
void set_spline_pos(game_spline_t *p, int16_t x, int16_t y) {(void)p;(void)x;(void)y;}
void run_animation(game_animation_t *p, uint16_t frames) {(void)p;(void)frames;}
void test_bob(gfxbob_t *s) {(void)s;}
int main(void) {
    game_world_object_t a[2]; gfxbob_t b[2]; memset(a,0,sizeof a);memset(b,0,sizeof b);
    assert(game_world_object_start(&a[0], GAME_OBJECT_ENEMY, &b[0],50,50,20,20));
    assert(game_world_object_start(&a[1], GAME_OBJECT_ENEMY, &b[1],120,50,20,20));
    a[0].break_hits_required=3; a[0].enemy_defeat_frame=7;
    a[0].enemy_defeat_frames=2; a[0].enemy_defeat_count=2;
    assert(game_world_objects_attack(a,2,70,50,10,20,1)==0); /* touching edge isn't hit */
    assert(game_world_objects_attack(a,2,65,50,10,20,1)==1);
    assert(a[0].break_hits_done==1 && a[0].break_hit_triggered && a[0].active);
    game_world_objects_update(a,2,1);
    assert(game_world_objects_attack(a,2,65,50,10,20,1)==1);
    assert(a[0].break_hits_done==2 && a[0].active);
    game_world_objects_update(a,2,1);
    assert(game_world_objects_attack(a,2,65,50,10,20,1)==1);
    assert(!a[0].active && a[0].break_triggered && a[0].break_hit_triggered && a[0].enemy_dying==4);
    assert(game_world_objects_attack(a,2,65,50,10,20,1)==0); /* dead enemies immune */
    assert(!a[1].break_hits_done);
    assert(game_world_objects_attack(a,2,118,50,15,20,3)==1);
    assert(!a[1].active); /* 3 damage completes required-hit count */
    puts("Stage124 native melee/enemy damage: PASS");return 0;
}
