/* FIRE2 dispatch: NPC dialogue first, world-trigger priority, bag otherwise. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int reserved;
static unsigned query_calls;
static uint8_t query_fire2(int32_t x, int32_t y, uint16_t w, uint16_t h)
{
    assert(x==100 && y==100 && w==16 && h==16);
    ++query_calls;
    return (uint8_t)reserved;
}
void test_colour(uint8_t c) { (void)c; }
void test_text(int x,int y,const char *t) {(void)x;(void)y;(void)t;}
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *sprite) {(void)sprite;}
static uint8_t press(uint8_t buttons)
{ return game_adventure_input(buttons,100,100,16,16,1); }
static void release(void) { (void)press(0); }
int main(void)
{
    const game_adventure_node_t nodes[] = {
        {"NPC", "Hi!", {{"Bye", "", -1,-1,-1,-1,-1,-1}}}
    };
    const game_adventure_npc_t npc = {100,100,16,16,40,0};
    /* A plain world: press opens bag, hold cannot toggle, release+press closes. */
    game_adventure_start(NULL,0,nodes,1,NULL,0,NULL,0,0,8,NULL,1,NULL,NULL);
    game_adventure_set_fire2_action(query_fire2);
    reserved=0; query_calls=0;
    assert(!game_adventure_open());
    assert(press(BTN_FIRE2)==1);
    assert(game_adventure_open());
    assert(query_calls==1);
    assert(press(BTN_FIRE2)==1);
    assert(game_adventure_open()); /* cannot immediately close on a held key */
    release();
    assert(press(BTN_FIRE2)==0);
    assert(!game_adventure_open());
    /* A world with a nearby FIRE2 trigger: inventory must not steal button. */
    release(); reserved=1;
    assert(press(BTN_FIRE2)==0);
    assert(!game_adventure_open());
    assert(query_calls==2);
    release(); reserved=0;
    assert(press(BTN_FIRE2)==1);
    assert(game_adventure_open());
    release(); assert(press(BTN_FIRE2)==0);
    release(); /* New dialogue starts after the previous FIRE2 is released. */
    /* A conversation takes precedence even when overlapping a button door. */
    game_adventure_start(NULL,0,nodes,1,&npc,1,NULL,0,0,8,NULL,1,NULL,NULL);
    game_adventure_set_fire2_action(query_fire2);
    query_calls=0; reserved=1;
    assert(press(BTN_FIRE2)==1);
    assert(game_adventure_open());
    assert(query_calls==0); /* No trigger probe needed: NPC already handled it. */
    release();
    /* Another world with no registration does not reuse previous-world probe. */
    game_adventure_start(NULL,0,nodes,1,NULL,0,NULL,0,0,8,NULL,1,NULL,NULL);
    reserved=1; query_calls=0;
    assert(press(BTN_FIRE2)==1);
    assert(game_adventure_open());
    assert(query_calls==0);
    /* FIRE2 held on an exit door must not reopen inventory on arrival. */
    release();
    game_adventure_start(NULL,0,nodes,1,NULL,0,NULL,0,0,8,NULL,1,NULL,NULL);
    game_adventure_set_fire2_action(query_fire2);
    reserved=1;
    assert(press(BTN_FIRE2)==0);  /* Simulates the button activating a door. */
    reserved=0;
    game_adventure_start(NULL,0,nodes,1,NULL,0,NULL,0,0,8,NULL,1,NULL,NULL);
    game_adventure_set_fire2_action(query_fire2);
    assert(press(BTN_FIRE2)==0);  /* Same held press after world reload. */
    assert(!game_adventure_open());
    release();
    assert(press(BTN_FIRE2)==1);  /* New press, away from door: inventory. */
    puts("Stage 5.28 FIRE2 priority + inventory toggle PASS");
    return 0;
}
