/* Stage 5.98: a flagged Player speech is visible WITH its next dialogue. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE2
#define BTN_FIRE2 16u
#endif
void test_colour(uint8_t value){(void)value;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob){(void)bob;}
static int got_next,got_thought,got_skipped;
void test_text(int x,int y,const char *text)
{
    (void)x;(void)y;
    if(!text)return;
    if(strstr(text,"Next dialogue")) ++got_next;
    if(strstr(text,"my own secret thought")) ++got_thought;
    if(strstr(text,"unflagged comment")) ++got_skipped;
}
static const game_adventure_node_t nodes[]={
    {.speaker="Steve",.text="First dialogue",.choices={{
        .label="Continue",.reply="my own secret thought",.next=1},{0},{0}}},
    {.speaker="Steve",.text="Next dialogue",.choices={{
        .label="End",.reply="unflagged comment",.next=2},{0},{0}}},
    {.speaker="Steve",.text="Final dialogue",.choices={{0},{0},{0}}}
};
static void tick(uint8_t b){(void)game_adventure_input(b,0,0,16,16,100);}
int main(void)
{
    const uint16_t skins[9]={0}; const uint8_t flags[9]={1,0,0,0,0,0,0,0,0};
    game_adventure_start(0,0,nodes,3,0,0,0,0,0,8,skins,1,0,0);
    game_adventure_thought_choices(flags,9);
    game_adventure_thought_box(30,10,240,64,skins,0);
    assert(game_adventure_trigger_sequence(0));
    tick(0);tick(BTN_FIRE2);tick(0);
    game_adventure_draw(0,0,0,0);
    assert(got_next>0 && got_thought>0);
    got_thought=got_skipped=0;
    tick(BTN_FIRE2);tick(0);
    game_adventure_draw(0,0,0,0);
    assert(got_thought==0 && got_skipped==0);
    /* Reopening another conversation must never reuse a previous thought. */
    game_adventure_start(0,0,nodes,3,0,0,0,0,0,8,skins,1,0,0);
    assert(game_adventure_trigger_sequence(1));
    got_thought=0;tick(0);game_adventure_draw(0,0,0,0);
    assert(got_thought==0);
    puts("Stage 5.98: simultaneous thought / reset PASS");
    return 0;
}
