#include "adventureruntime.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
static uint8_t ink;
static int dialogue_colours, thought_colours, unexpected;
void test_colour(uint8_t c) { ink=c; }
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b) {(void)b;}
void test_text(int x,int y,const char *s) {
    (void)x;(void)y;
    if (!s) return;
    if (strstr(s,"DIALOGUE TEXT")) { if (ink==11) ++dialogue_colours; else ++unexpected; }
    if (strstr(s,"THOUGHT TEXT")) { if (ink==22) ++thought_colours; else ++unexpected; }
}
static const game_adventure_node_t nodes[]={
  {.speaker="Steve",.text="DIALOGUE TEXT",.choices={
    {.label="Response",.reply="THOUGHT TEXT",.next=-1,.requires=-1,.give=-1,.take=-1,.action=-1}, {0},{0}}}
};
static const uint8_t flags[]={2,0,0};
int main(void) {
    static const uint16_t cells[9]={0};
    game_adventure_start(0,0,nodes,1,0,0,0,0,0,8,cells,1,0,0);
    game_adventure_thought_choices(flags,3);
    game_adventure_thought_box(20,10,240,65,cells,0);
    game_adventure_text_style(11,0,1);
    game_adventure_thought_text_colour(22);
    assert(game_adventure_trigger_dialogue(0));
    (void)game_adventure_input(0,0,0,16,16,800);
    game_adventure_draw(0,0,0,0);
    assert(dialogue_colours>0 && thought_colours>0 && !unexpected);
    puts("Stage 5.126: dialogue and thought CLUT text colours independent PASS");
    return 0;
}
