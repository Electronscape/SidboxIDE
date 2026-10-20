/* Stage 3.96: real upward jump hits a head-butt breakable, not a fall/stomp.
   cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
   -I/tmp/st390includes -Iidelibs/api -Iidelibs/codehelpers/game \
   development/tests/test_stage396_headbutt_reward.c -Wl,--gc-sections -o /tmp/gg396 && /tmp/gg396 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"
static int32_t x, y, vy;
static uint8_t ground, jump;
static game_world_player_t p;
static game_world_object_t b;
static void reset(void) {
    x=40*100; y=104*100; vy=0; ground=1; jump=0;
    p=(game_world_player_t){0};
    p.x100=&x; p.y100=&y; p.vy100=&vy; p.on_ground=&ground;
    p.jump_held=&jump; p.width=16; p.height=16;
    b=(game_world_object_t){0};
    assert(game_world_object_start(&b,GAME_OBJECT_BREAKABLE,0,32,80,48,8));
    b.break_from_below=1; b.break_hits_required=2;
}
static void hit_underside(void) {
    /* New intentional jump while standing below the object. */
    x=40*100; y=104*100; vy=0; ground=1; jump=0;
    game_world_objects_before(&b,1,&p);
    ground=0; vy=-700; jump=1;
    game_world_objects_after(&b,1,&p);
    assert(p.break_stomp_armed);
    jump=0;
    game_world_objects_before(&b,1,&p);
    y=84*100;
    game_world_objects_after(&b,1,&p);
}
int main(void) {
    reset();
    /* Ordinary fall onto the top cannot break a head-butt block. */
    y=56*100; ground=0; vy=300;
    game_world_objects_before(&b,1,&p); y=70*100;
    game_world_objects_after(&b,1,&p);
    assert(b.active && b.break_hits_done==0);
    /* First deliberate jump from below damages it and stops upward travel. */
    hit_underside();
    assert(b.active && b.break_hits_done==1 && b.break_hit_triggered);
    assert(vy==0 && y==88*100 && !p.break_stomp_armed);
    /* Contact without separating must never damage again. */
    game_world_objects_before(&b,1,&p);
    game_world_objects_after(&b,1,&p);
    assert(b.break_hits_done==1);
    y=104*100;vy=0;ground=1;
    game_world_objects_before(&b,1,&p);
    game_world_objects_after(&b,1,&p);
    assert(!b.break_touching);
    hit_underside();
    assert(!b.active && b.break_hits_done==2 && b.break_triggered);
    /* Any ordinary stomp remains original unless head-butt flag is ON. */
    reset(); b.break_from_below=0;
    y=56*100; ground=0;vy=300;
    game_world_objects_before(&b,1,&p);y=70*100;
    game_world_objects_after(&b,1,&p);
    assert(b.break_hits_done==0);
    puts("PASS: rising jump head-butt, rearm, no top break, final break event");
    return 0;
}
