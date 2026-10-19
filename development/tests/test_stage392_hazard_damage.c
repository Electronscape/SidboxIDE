/* Stage 3.92: moving hazard swept contact, single damage event, knockback,
   flashing cadence, optional effects, and existing non-solid semantics.
   Host API stubs from the earlier C world-object regression harness. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
void run_spline(game_spline_t *path, uint16_t frames) { (void)path; (void)frames; }
void run_animation(game_animation_t *anim, uint16_t frames) { (void)anim; (void)frames; }
static int32_t x100, y100, vy100, force100;
static uint8_t on_ground, coyote;
static game_world_player_t p;
static game_world_object_t hazard;
static void setup(void) {
    x100=40*100; y100=55*100; vy100=0; force100=0;
    on_ground=1; coyote=1; p=(game_world_player_t){0};
    p.x100=&x100; p.y100=&y100; p.vy100=&vy100;
    p.on_ground=&on_ground; p.coyote=&coyote;
    p.spring_force_vx100=&force100; p.width=16; p.height=16;
    hazard=(game_world_object_t){0};
    assert(game_world_object_start(&hazard,GAME_OBJECT_HAZARD,0,32,80,40,12));
    hazard.hazard_damage=2; hazard.hazard_kick_x=-5;
    hazard.hazard_kick_y=-9; hazard.hazard_flash_colour=17;
    hazard.hazard_flash_count=2; hazard.hazard_flash_frames=2;
}
static void update(void){
    game_world_objects_update(&hazard,1,1);
    game_world_objects_before(&hazard,1,&p);
}
static void finish(void) {
    game_world_objects_after(&hazard,1,&p);
    game_world_objects_hazards(&hazard,1,&p);
}
int main(void) {
    setup(); update(); y100=72*100; finish();
    assert(p.hurt_triggered && p.hurt_damage_this_frame==2);
    assert(hazard.hazard_hit_triggered && hazard.hazard_bounce_triggered);
    assert(vy100==-900 && force100==-500 && !on_ground && !coyote);
    assert(p.hurt_ticks_remaining==8 && p.hurt_anim_active);
    uint8_t colour=0;
    assert(game_world_player_hurt_flash(&p,&colour) && colour==17);
    update(); finish();
    assert(!p.hurt_triggered && !hazard.hazard_hit_triggered);
    assert(game_world_player_hurt_flash(&p,0));
    update(); finish(); assert(!game_world_player_hurt_flash(&p,0));
    update(); finish(); assert(!game_world_player_hurt_flash(&p,0));
    update(); finish(); assert(game_world_player_hurt_flash(&p,0));
    for(int i=0;i<5;i++){update();finish();}
    assert(p.hurt_ticks_remaining==0 && !p.hurt_anim_active);
    /* Keeping the same overlap never triggers another damage event. */
    assert(!p.hurt_triggered);
    y100=0; update(); finish(); /* leave, rearm contact */
    update(); y100=72*100; finish(); assert(p.hurt_triggered);
    /* No knockback/flash/hurt animation: still one hit and grace period. */
    setup(); hazard.hazard_kick=0; hazard.hazard_flash=0;
    hazard.hazard_hurt_animation=0; update();y100=72*100;finish();
    assert(!hazard.hazard_bounce_triggered && vy100==0);
    assert(p.hurt_triggered && p.hurt_ticks_remaining==20);
    assert(!game_world_player_hurt_flash(&p,0) && !p.hurt_anim_active);
    /* The spike's spline moves horizontally THROUGH a stationary player,
       entirely between the start/end frame positions. This must be caught. */
    setup(); hazard.x=0; hazard.previous_x=0; hazard.y=55;hazard.previous_y=55;
    x100=40*100; y100=55*100;
    game_world_objects_before(&hazard,1,&p);
    hazard.x=85; game_world_objects_hazards(&hazard,1,&p);
    assert(p.hurt_triggered);
    /* Old platform collision must never land on a non-solid Hazard. */
    setup();update();y100=70*100;game_world_objects_after(&hazard,1,&p);
    assert(y100==70*100 && !hazard.break_triggered);
    puts("PASS: hazard swept contact, damage, knockback, grace window, flashes");
    return 0;
}
