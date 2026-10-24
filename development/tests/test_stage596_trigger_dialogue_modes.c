/* Stage 5.96: a Trigger's one-message outcome MUST NOT execute dialogue choices. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE2
#define BTN_FIRE2 16u
#endif
void test_colour(uint8_t value) {(void)value;}
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob) {(void)bob;}
static int saw_second;
void test_text(int x,int y,const char *text)
{ (void)x;(void)y; if(text && strstr(text,"Second"))++saw_second; }
static const game_adventure_node_t nodes[]={
    {.speaker="Door", .text="Your key was accepted.", .choices={
        {.label="Like what?",.reply="",.next=1,.requires=-1,.give=-1,.take=-1,.action=-1},
        {0},{0}}},
    {.speaker="Door",.text="Second node reached", .choices={{0},{0},{0}}}
};
static void tick(uint8_t buttons)
{ (void)game_adventure_input(buttons,0,0,16,16,100); }
int main(void)
{
    uint16_t skin[9]={0};
    game_adventure_start(0,0,nodes,2,0,0,0,0,0,8,skin,1,0,0);
    assert(!game_adventure_trigger_message(99));
    assert(game_adventure_trigger_message(0));
    assert(game_adventure_open());
    tick(0);
    game_adventure_draw(0,0,0,0);
    assert(!saw_second);
    tick(BTN_FIRE2);
    assert(!game_adventure_open()); /* Does not enter choice node 1. */
    tick(0);
    assert(game_adventure_trigger_dialogue(0));
    tick(0);
    tick(BTN_FIRE2);
    assert(game_adventure_open()); /* Full conversation offers a reply. */
    tick(0); tick(BTN_FIRE2); tick(0); /* Advance the answer bubble to node 1. */
    assert(game_adventure_open());
    game_adventure_draw(0,0,0,0);
    assert(saw_second);
    tick(0);
    tick(BTN_FIRE2);
    assert(!game_adventure_open());
    puts("Stage 5.96: single message vs full conversation PASS");
    return 0;
}
