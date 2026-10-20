#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int rx,ry,rw,rh;
static int saw_first,saw_second,saw_third,saw_up,saw_down;
void test_colour(uint8_t c) {(void)c;}
void test_rect(int x,int y,int w,int h) {rx=x;ry=y;rw=w;rh=h;}
void test_bob(gfxbob_t *sprite) {(void)sprite;}
void test_text(int x,int y,const char *s) {
    (void)y;
    /* Only answer labels, not NPC body, are drawn at +26. */
    if(x==56) {
        if(strstr(s,"FIRST"))saw_first++;
        if(strstr(s,"SECOND"))saw_second++;
        if(strstr(s,"THIRD"))saw_third++;
    }
    if(x==30+280-12-8) {
        if(strcmp(s,"^")==0)saw_up++;
        if(strcmp(s,"v")==0)saw_down++;
    }
}
static void clear_marks(void) {
    saw_first=saw_second=saw_third=saw_up=saw_down=0;
}
int main(void) {
    const char *body="The guardian wants to know if you have collected the flower. "
        "Please choose the answer which best explains what happened here and "
        "whether the magical wooden door should finally be opened.";
    game_adventure_node_t nodes[]={ {"Future Kim",body,{
        {"FIRST OPTION This choice has an intentionally longer explanation that wraps a few times", "",-1,-1,-1,-1,-1},
        {"SECOND OPTION The flower", "",-1,-1,-1,-1,-1},
        {"THIRD OPTION This answer is longer than the others and should wrap across several lines with a description of the puzzle adventure", "",-1,-1,-1,-1,-1}
    }} };
    game_adventure_npc_t npc={100,100,16,16,50,0};
    game_adventure_start(0,0,nodes,1,&npc,1,0,0,0,8,0,1,0,0);
    game_adventure_dialogue_box(30,250,280,96);
    game_adventure_input(BTN_FIRE2,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,1000);
    clear_marks();game_adventure_draw(0,0,100,100);
    assert(rx==30 && rw==280 && rh>96 && ry<250 && ry+rh<=320);
    assert(saw_first && saw_second && !saw_third);
    assert(!saw_up && saw_down);
    const int fixed_height=rh;
    /* Scroll Down twice; view becomes SECOND + THIRD, never three answers. */
    game_adventure_input(BTN_DOWN,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,1);
    game_adventure_input(BTN_DOWN,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,1);
    clear_marks();game_adventure_draw(0,0,100,100);
    assert(rh==fixed_height);
    assert(!saw_first && saw_second && saw_third);
    assert(saw_up && !saw_down);
    /* Oversized dialogue never escapes the 480x320 canvas. */
    static char massive[513];memset(massive,'X',512);massive[512]=0;
    nodes[0].text=massive;
    clear_marks();game_adventure_draw(0,0,100,100);
    assert(ry==0 && rh==320 && rx+rw<=480 && ry+rh<=320);
    puts("Stage4.33: auto-height, two-choice scroll arrows, stable height, full-screen clamp PASS");
    return 0;
}
