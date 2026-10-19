/* Stage 3.89: breakable hit count, touch re-arm and directional stomp bounce.
 * Native: cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *    -I/tmp/st390includes -Iidelibs/api -Iidelibs/codehelpers/game \
 *    development/tests/test_stage389_breakable_objects.c -Wl,--gc-sections -o /tmp/gg390 && /tmp/gg390
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
static int32_t x100,y100,vy100,force;
static uint8_t ground,coyote,jump_held;
static game_world_player_t player;

static void reset(void) {
    x100=y100=vy100=force=0; ground=coyote=jump_held=0;
    player=(game_world_player_t){0};
    player.x100=&x100;player.y100=&y100;player.vy100=&vy100;
    player.on_ground=&ground;player.coyote=&coyote;player.jump_held=&jump_held;
    player.spring_force_vx100=&force;player.width=16;player.height=16;
}
static game_world_object_t make_breakable(void) {
    game_world_object_t o={0};
    assert(game_world_object_start(&o,GAME_OBJECT_BREAKABLE,0,32,80,48,8));
    return o;
}
static void touchdown(game_world_object_t *o) {
    /* A real jump starts with a new button press AND upward takeoff. The
       player may release the button well before descending onto the object. */
    x100=40*100; y100=56*100; ground=1; vy100=0; jump_held=0;
    game_world_objects_before(o,1,&player);
    ground=0; vy100=-700; jump_held=1;
    game_world_objects_after(o,1,&player);
    assert(player.break_stomp_armed);
    jump_held=0; vy100=300;
    game_world_objects_before(o,1,&player);
    y100=70*100;
    game_world_objects_after(o,1,&player);
}
static void separate(game_world_object_t *o) {
    x100=0; y100=0;ground=0;vy100=-100;
    game_world_objects_before(o,1,&player);
    game_world_objects_after(o,1,&player);
}
static void side_touch(game_world_object_t *o) {
    x100=0;y100=78*100;ground=0;vy100=0;
    game_world_objects_before(o,1,&player);
    x100=30*100;
    game_world_objects_after(o,1,&player);
}
int main(void) {
    reset();
    game_world_object_t o=make_breakable();
    o.break_hits_required=4;
    touchdown(&o);
    assert(o.active && o.break_hits_done==1 && ground==1 && y100==64*100);
    /* Remaining on top must never count extra hits. */
    for (int i=0;i<10;i++) {
        game_world_objects_before(&o,1,&player);
        game_world_objects_after(&o,1,&player);
        assert(o.break_hits_done==1 && o.active);
    }
    separate(&o);
    touchdown(&o);assert(o.active && o.break_hits_done==2);
    separate(&o);
    touchdown(&o);assert(o.active && o.break_hits_done==3);
    separate(&o);
    touchdown(&o);assert(!o.active && o.break_hits_done==4 && o.break_triggered);
    /* Touch mode counts a contact from a side, but never its continuous overlap. */
    reset();o=make_breakable();o.break_hits_required=2;o.break_touch_mode=1;
    side_touch(&o);
    assert(o.break_hits_done==1 && o.active && x100==3000);
    game_world_objects_before(&o,1,&player);
    game_world_objects_after(&o,1,&player);
    assert(o.break_hits_done==1);
    separate(&o);
    side_touch(&o);
    assert(o.break_hits_done==2 && !o.active);
    /* Stomping can bounce up and left; final hit also gives a launch. */
    reset();o=make_breakable();o.break_hits_required=2;
    o.break_bounce=1;o.break_strength=15;o.break_launch_x=-6;
    touchdown(&o);
    assert(o.active && o.break_hits_done==1 && !ground);
    assert(vy100==-1500 && force==-600);
    separate(&o);touchdown(&o);
    assert(!o.active && o.break_hits_done==2 && vy100==-1500);
    /* Independent instances and old platforms have no shared hit counter. */
    reset();
    game_world_object_t others[2]={make_breakable(),make_breakable()};
    others[0].break_hits_required=2; others[1].break_hits_required=2;
    others[1].x=200;others[1].previous_x=200;
    touchdown(&others[0]);assert(others[0].break_hits_done==1);
    assert(others[1].break_hits_done==0 && others[1].active);
    puts("PASS: deliberate-jump breakable stomps, rearm, touch, bounce, independent counters");
    return 0;
}
