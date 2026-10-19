/* Stage 3.91: audio event flags are pulses from actual physics events.
 * Compile with the same lightweight native API stubs as Stage 3.90.
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
/* update() can animate/move configured objects, not exercised in this test. */
void run_spline(game_spline_t *path, uint16_t frames) { (void)path; (void)frames; }
void run_animation(game_animation_t *anim, uint16_t frames) { (void)anim; (void)frames; }


static int32_t x100, y100, vy100;
static uint8_t grounded, jump_held;
static game_world_player_t p;
static game_world_object_t o;

static void reset(uint8_t touch, uint8_t bounce, uint8_t hits)
{
    x100=40*100; y100=56*100; vy100=0; grounded=0; jump_held=0;
    p=(game_world_player_t){0};
    p.x100=&x100; p.y100=&y100; p.vy100=&vy100;
    p.on_ground=&grounded; p.jump_held=&jump_held;
    p.width=16; p.height=16;
    o=(game_world_object_t){0};
    assert(game_world_object_start(&o,GAME_OBJECT_BREAKABLE,0,32,80,48,8));
    o.break_touch_mode=touch; o.break_bounce=bounce; o.break_hits_required=hits;
    assert(!o.break_hit_triggered && !o.break_bounce_triggered && !o.break_triggered);
}
static void step(void)
{
    game_world_objects_update(&o,1,1);
    game_world_objects_before(&o,1,&p);
}
static void finish(void) { game_world_objects_after(&o,1,&p); }
static void jump(void)
{
    y100=56*100; grounded=1; vy100=0; jump_held=0;
    step(); grounded=0; vy100=-700; jump_held=1; finish();
    assert(p.break_stomp_armed);
    jump_held=0;
}
static void land(void)
{
    vy100=300;
    step(); y100=70*100; finish();
}
static void leave(void)
{
    y100=20*100; vy100=-300;
    step(); finish();
}
int main(void)
{
    /* Unintentional landing isn't a hit and can't play a bounce sound. */
    reset(0,1,2); land();
    assert(!o.break_hit_triggered && !o.break_bounce_triggered && !o.break_triggered);
    /* Actual jump/stomp: hit and bounce, but no shatter yet. */
    reset(0,1,2); jump(); land();
    assert(o.active && o.break_hits_done==1);
    assert(o.break_hit_triggered && o.break_bounce_triggered && !o.break_triggered);
    /* Clear automatically on next update, no retriggers from remaining contact. */
    step(); finish();
    assert(!o.break_hit_triggered && !o.break_bounce_triggered && !o.break_triggered);
    leave(); land();
    assert(!o.active && o.break_hits_done==2);
    assert(o.break_hit_triggered && o.break_bounce_triggered && o.break_triggered);
    step(); finish();
    assert(!o.break_hit_triggered && !o.break_bounce_triggered && !o.break_triggered);
    /* Touch: a real hit, no bounce; after separating, final shatter pulse. */
    reset(1,0,2);
    x100=0; y100=78*100; step(); x100=30*100; finish();
    assert(o.break_hit_triggered && !o.break_bounce_triggered && !o.break_triggered);
    step(); finish();
    assert(!o.break_hit_triggered && !o.break_bounce_triggered && !o.break_triggered);
    x100=0; y100=0; step(); finish();
    x100=0; y100=78*100; step(); x100=30*100; finish();
    assert(o.break_hit_triggered && !o.break_bounce_triggered && o.break_triggered);
    /* Bounce disabled: hitting must not raise a bounce sound. */
    reset(0,0,1); jump(); land();
    assert(o.break_hit_triggered && !o.break_bounce_triggered && o.break_triggered);
    puts("PASS: breakable hit, bounce and shatter sounds are single-frame event pulses");
    return 0;
}
