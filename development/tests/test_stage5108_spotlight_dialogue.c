/* Stage 5.108: dialogue choice and answerless-close spotlight actions. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#ifndef BTN_FIRE2
#define BTN_FIRE2 16u
#endif
void test_colour(uint8_t value){(void)value;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_text(int x,int y,const char *s){(void)x;(void)y;(void)s;}
void test_bob(gfxbob_t *b){(void)b;}
static int calls[4],last=-1;
static void spotlight(uint8_t action){assert(action<3);calls[action]++;last=action;}
static const game_adventure_node_t nodes[]={
    {.speaker="NPC",.text="Choose",.choices={
        {.label="Turn the light on",.next=-1,.missing_next=-1,.requires=-1,.give=-1,.take=-1,.action=-1}, {0},{0}}},
    {.speaker="NPC",.text="Goodbye",.choices={{0},{0},{0}}}
};
static const game_adventure_spotlight_rule_t actions[]={
    {0u,1u}, /* choice zero of node zero -> ON */
    {7u,0u}  /* three choices * two nodes + node one -> OFF at close */
};
static void tap(uint8_t button){(void)game_adventure_input(0u,0,0,16,16,0);(void)game_adventure_input(button,0,0,16,16,0);(void)game_adventure_input(0u,0,0,16,16,0);}
int main(void){
    const uint16_t skin[9]={0};
    game_adventure_start(0,0,nodes,2,0,0,0,0,0,8,skin,1,0,0);
    game_adventure_spotlight_actions(actions,2u,spotlight);
    assert(game_adventure_trigger_dialogue(0u));
    tap(BTN_FIRE2);tap(BTN_FIRE2);
    assert(calls[1]==1&&last==1);
    assert(game_adventure_trigger_dialogue(1u));
    tap(BTN_FIRE2);tap(BTN_FIRE2);
    assert(calls[0]==1&&last==0);
    /* Starting another world clears callback / sparse rows. */
    game_adventure_start(0,0,nodes,2,0,0,0,0,0,8,skin,1,0,0);
    assert(game_adventure_trigger_dialogue(1u));
    tap(BTN_FIRE2);tap(BTN_FIRE2);
    assert(calls[0]==1&&calls[1]==1);
    puts("PASS Stage 5.108: NPC choice and on-close spotlight events, reset");
    return 0;
}
