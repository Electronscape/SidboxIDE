/* Validate dialogue/thought draw order, scaled wrapping and world resets. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static char order[512];
static int order_len;
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob){(void)bob;}
void test_text(int x,int y,const char *text)
{
    (void)x;(void)y;
    if(!text)return;
    if(strstr(text,"SECOND"))order[order_len++]='D';
    if(strstr(text,"THOUGHT"))order[order_len++]='T';
    order[order_len]=0;
}
static const game_adventure_node_t nodes[]={
    {.speaker="Steve",.text="FIRST",.choices={{.label="Continue",.reply="THOUGHT",.next=1},{0},{0}}},
    {.speaker="Steve",.text="SECOND",.choices={{0},{0},{0}}}
};
static void tick(uint8_t buttons)
{ (void)game_adventure_input(buttons,0,0,16,16,100); }
int main(void)
{
    const uint16_t skin[9]={0};const uint8_t flags[3]={1,0,0};
    game_adventure_start(0,0,nodes,2,0,0,0,0,0,8,skin,1,0,0);
    game_adventure_thought_choices(flags,3);
    game_adventure_thought_box(30,12,240,64,skin,0);
    game_adventure_dialogue_typography(1,2,1,2,1);
    assert(game_adventure_trigger_sequence(0));
    tick(0);tick(BTN_FIRE2);tick(0);
    order_len=0;order[0]=0;game_adventure_draw(0,0,0,0);
    assert(strchr(order,'D') && strchr(order,'T'));
    assert(strchr(order,'D')<strchr(order,'T')); /* thought on top */
    game_adventure_dialogue_typography(2,4,2,4,0);
    order_len=0;order[0]=0;game_adventure_draw(0,0,0,0);
    assert(strchr(order,'D') && strchr(order,'T'));
    assert(strchr(order,'T')<strchr(order,'D')); /* dialogue on top */
    /* Very wide glyphs never cause an unsigned column underflow. */
    game_adventure_dialogue_typography(8,8,8,8,1);
    game_adventure_dialogue_box(0,0,128,96);
    game_adventure_thought_box(0,0,96,40,skin,0);
    game_adventure_draw(0,0,0,0);
    game_adventure_start(0,0,nodes,2,0,0,0,0,0,8,skin,1,0,0);
    game_adventure_thought_choices(flags,3);
    assert(game_adventure_trigger_sequence(1));
    order_len=0;order[0]=0;tick(0);game_adventure_draw(0,0,0,0);
    assert(strchr(order,'T')==0); /* no stale thoughts across worlds */
    puts("Stage 5.99: typography/stacking/default reset PASS");
    return 0;
}
