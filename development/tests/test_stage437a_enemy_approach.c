/* Stage 4.37a: collision approach, including moving enemies and crossed centres. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
void run_spline(game_spline_t *p, uint16_t f) {(void)p;(void)f;}
void set_spline_pos(game_spline_t *p, int16_t x, int16_t y) {(void)p;(void)x;(void)y;}
void run_animation(game_animation_t *p, uint16_t f) {(void)p;(void)f;}
void test_bob(gfxbob_t *s) {(void)s;}

static void impact(uint8_t kind, int32_t player_before, int32_t player_now,
                   int32_t enemy_before, int32_t enemy_now,
                   int32_t old_force, int32_t expected_force) {
    game_world_object_t o = {0};
    game_world_player_t p = {0};
    gfxbob_t bob = {0};
    int32_t x=player_before*100, y=50*100, vy=0, force=old_force;
    uint8_t ground=1;
    assert(game_world_object_start(&o,kind,&bob,enemy_before,50,12,12));
    p.x100=&x; p.y100=&y; p.vy100=&vy; p.on_ground=&ground;
    p.width=12; p.height=12; p.spring_force_vx100=&force;
    o.hazard_kick=1; o.hazard_kick_x=7; o.hazard_kick_y=-6;
    o.hazard_damage=2;
    game_world_objects_before(&o,1,&p);
    /* Simulate enemy movement AFTER its previous position was recorded,
       and player movement AFTER before() as in the generated platformer. */
    x=player_now*100;
    o.x=enemy_now;
    game_world_objects_hazards(&o,1,&p);
    assert(p.hurt_triggered && p.hurt_damage_this_frame==2);
    if (force != expected_force) {
        fprintf(stderr,"kind=%u player=%ld->%ld enemy=%ld->%ld force=%ld expected=%ld\n",
                kind,(long)player_before,(long)player_now,(long)enemy_before,
                (long)enemy_now,(long)force,(long)expected_force);
    }
    assert(force==expected_force);
    assert(vy==-600);
}
int main(void) {
    /* Player approaches a stationary enemy from both directions. */
    impact(GAME_OBJECT_ENEMY, 0, 23, 20, 20, 800, -700);
    impact(GAME_OBJECT_ENEMY, 45, 27, 20, 20, -800, 700);
    /* Crossing the enemy's CENTRE during a fast hit must not reverse kick. */
    impact(GAME_OBJECT_ENEMY, 0, 35, 20, 20, 0, -700);
    impact(GAME_OBJECT_ENEMY, 55, 9, 20, 20, 0, 700);
    /* Enemy approaches a stationary player from either side. */
    impact(GAME_OBJECT_ENEMY, 35, 35, 10, 28, 0, 700);
    impact(GAME_OBJECT_ENEMY, 5, 5, 30, 10, 0, -700);
    /* Started overlapped: relative approach direction decides the push. */
    impact(GAME_OBJECT_ENEMY, 23, 27, 20, 20, 0, -700);
    impact(GAME_OBJECT_ENEMY, 23, 19, 20, 20, 0, 700);
    /* Existing Murder Objects must still apply their configured signed X. */
    impact(GAME_OBJECT_HAZARD, 35, 35, 10, 28, 100, 800);
    puts("PASS: enemy approach direction, fast centre crossings, moving enemies, existing force override, Murder Object signed kick");
    return 0;
}
