/* Stage 5.97: text-only linked dialogue, including wrong-item modal hand-off. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE2
#define BTN_FIRE2 16u
#endif
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
void test_colour(uint8_t value) {(void)value;}
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob) {(void)bob;}
static int saw_first, saw_second, saw_wrong, actions, attempted, sound_wrong;
void test_text(int x,int y,const char *text)
{
    (void)x; (void)y;
    if (!text) return;
    if (strstr(text,"first notice")) ++saw_first;
    if (strstr(text,"second notice")) ++saw_second;
    if (strstr(text,"wrong item")) ++saw_wrong;
}
static void trigger_action(uint16_t id,void *ctx) {(void)id; (void)ctx; ++actions;}
static const game_adventure_node_t nodes[]={
    {.speaker="Door",.text="first notice",.choices={
        {.label="Continue...",.reply="SHOULD NOT SPEAK",.next=1,.requires=0,.give=0,.take=0,.action=98},
        {0},{0}}},
    {.speaker="Door",.text="second notice",.choices={
        {.label="Thank god!",.next=-1,.requires=0,.give=0,.take=0,.action=98},
        {0},{0}}},
    {.speaker="Door",.text="wrong item",.choices={
        {.label="Go on...",.next=3,.requires=0,.give=0,.take=0,.action=98},
        {0},{0}}},
    {.speaker="Door",.text="try another item",.choices={{0},{0},{0}}}
};
static const game_adventure_item_t items[]={
    {.name="Wrong key",.pickup_kind=0,.icon=65535u,.capacity=10u,.initial=1u},
    {.name="Right key",.pickup_kind=0,.icon=65535u,.capacity=10u,.initial=0u}
};
static uint8_t probe(int32_t x,int32_t y,uint16_t w,uint16_t h)
{(void)x;(void)y;(void)w;(void)h;return 1u;}
static uint8_t use(const char *name)
{
    ++attempted;
    if (strcmp(name,"Wrong key")==0) {
        ++sound_wrong;
        assert(game_adventure_trigger_sequence(2));
        return 0u; /* Wrong item: must NOT consume or activate. */
    }
    return 1u;
}
static void tick(uint8_t buttons)
{(void)game_adventure_input(buttons,0,0,16,16,100);}
static void paint(void){game_adventure_draw(0,0,0,0);}
int main(void)
{
    uint16_t skin[9]={0};
    game_adventure_start(items,2,nodes,4,0,0,0,0,0,8,skin,1,trigger_action,0);
    assert(game_adventure_quantity(0)==1);
    /* The success-side single message still only shows one node. */
    assert(game_adventure_trigger_message(0));
    tick(0); paint(); assert(saw_first>0);
    tick(BTN_FIRE2); assert(!game_adventure_open());
    /* Linked success messages: choose Continue... then Thank god!, no actions. */
    tick(0); assert(game_adventure_trigger_sequence(0));
    tick(0); tick(BTN_FIRE2);
    assert(game_adventure_open());tick(0);paint();assert(saw_second>0);
    tick(0); tick(BTN_FIRE2);assert(!game_adventure_open());
    assert(game_adventure_quantity(0)==1 && actions==0);
    /* Wrong-item flow starts from the real FIRE2 inventory-USE state. */
    game_adventure_set_interaction(probe,use);
    tick(0);tick(BTN_FIRE2);assert(game_adventure_open());
    tick(0);tick(BTN_FIRE); assert(attempted==1);
    assert(game_adventure_open());
    tick(0);paint(); assert(saw_wrong>0); /* Picker didn't overwrite dialogue. */
    tick(0);tick(BTN_FIRE2);assert(game_adventure_open());
    tick(0);tick(BTN_FIRE2);assert(!game_adventure_open());
    assert(game_adventure_quantity(0)==1 && actions==0 && sound_wrong==1);
    /* Existing full dialogue still follows choices (Stage 5.96 regression). */
    game_adventure_set_interaction(0,0);
    tick(0);assert(game_adventure_trigger_dialogue(0));
    tick(0);tick(BTN_FIRE2);assert(game_adventure_open());
    tick(0);tick(BTN_FIRE2);tick(0);assert(game_adventure_open());
    paint();assert(saw_second>1);
    puts("Stage 5.97: trigger messages, sequence and wrong-item modal PASS");
    return 0;
}
