/* Stage 5.94: targeted trigger dialogue and inventory reward preflight. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
static int saw_door_text;
void test_colour(uint8_t v) {(void)v;}
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b) {(void)b;}
void test_text(int x,int y,const char *s) {(void)x;(void)y; if (strstr(s,"Door unlocked")) ++saw_door_text;}
static const game_adventure_item_t items[]={
    {"Key",0,65535,4,1}, {"Gem",0,65535,4,0}, {"Feather",0,65535,4,0}
};
static const game_adventure_node_t nodes[]={
    {"Door", "Door unlocked!", {{0},{0},{0}}}
};
static int activations;
static uint8_t probe(int32_t x,int32_t y,uint16_t w,uint16_t h)
{(void)x;(void)y;(void)w;(void)h;return 1u;}
static uint8_t use_key(const char *name)
{
    if(strcmp(name,"Key"))return 0u;
    if(!game_adventure_can_reward_name("Gem",1u,"Key"))return 3u;
    assert(game_adventure_take_name("Key",1u));
    assert(game_adventure_reward_name("Gem",1u));
    ++activations;
    assert(game_adventure_trigger_dialogue(0));
    return 1u; /* Callback consumed the key itself. */
}
static void tick(uint8_t b)
{(void)game_adventure_input(b,0,0,16,16,1);}
int main(void)
{
    uint16_t skin[9]={0};
    game_adventure_start(items,3,nodes,1,0,0,0,0,0,8,skin,1,0,0);
    game_adventure_inventory_max_slots(1);
    assert(!game_adventure_can_reward_name("Gem",1,0));
    assert(game_adventure_can_reward_name("Gem",1,"Key"));
    assert(!game_adventure_can_reward_name("Gem",5,"Key"));
    assert(!game_adventure_can_reward_name("Ghost",1,"Key"));
    game_adventure_set_interaction(probe,use_key);
    tick(0);tick(BTN_FIRE2);tick(0);
    assert(game_adventure_open());
    tick(BTN_FIRE);tick(0);
    assert(activations==1);
    assert(game_adventure_quantity(0)==0 && game_adventure_quantity(1)==1);
    assert(game_adventure_open()); /* Dialogue must not be closed by inventory. */
    (void)game_adventure_input(0,0,0,16,16,80);
    game_adventure_draw(0,0,0,0);
    assert(saw_door_text);
    tick(BTN_FIRE2); tick(0);
    assert(!game_adventure_open());
    assert(!game_adventure_trigger_dialogue(999u));
    puts("Stage 5.94: inventory preflight, key hand-in, reward, dialogue modal PASS");
    return 0;
}
