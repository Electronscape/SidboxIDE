#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
static int rx=-1,ry=-1,rw=0,rh=0;
static int answer_rows=0,first_y=-1,second_y=-1, max_y=-1;
static uint8_t colour;
void test_colour(uint8_t c){colour=c;}
void test_rect(int x,int y,int w,int h){rx=x;ry=y;rw=w;rh=h;}
void test_bob(gfxbob_t *s){(void)s;}
void test_text(int x,int y,const char *line){
    if(colour==15 && x==46 && y>=80 && line && strlen(line)>2){
        if(first_y==-1) first_y=y;
        else if(second_y==-1)second_y=y;
        answer_rows++;
        if(y>max_y)max_y=y;
    }
}
int main(void){
    const char *long_answer="Please explain exactly why this door has been locked and what kind of flower you need before I can go through it";
    const char *long_reply="I think there may be another way to solve this puzzle because I have explored the whole forest and found two different types of flowers and a mysterious copper key";
    game_adventure_node_t node={"Guardian","Would you like to enter?",{
      {long_answer,long_reply,-1,-1,-1,-1,-1},
      {"Leave", "",-1,-1,-1,-1,-1},
    }};
    game_adventure_npc_t npc={100,100,16,16,50,0};
    game_adventure_start(0,0,&node,1,&npc,1,0,0,0,8,0,2,0,0);
    game_adventure_dialogue_box(20,10,350,270);
    game_adventure_input(BTN_FIRE2,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,100);
    game_adventure_draw(0,0,100,100);
    assert(rx==20 && ry==10 && rw==350 && rh==270);
    assert(answer_rows>=2 && second_y>first_y);
    assert(max_y<280);
    /* Geometry clamps inside 480x320, even for invalid input. */
    game_adventure_dialogue_box(470,310,400,200);
    game_adventure_draw(0,0,100,100);
    assert(rx>=0 && ry>=0 && rx+rw<=480 && ry+rh<=320);
    /* Player speech uses its own window: a long reply needs more than 2 rows. */
    game_adventure_input(BTN_FIRE2,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,180);
    answer_rows=0;first_y=-1;second_y=-1;
    game_adventure_draw(0,0,100,100);
    assert(rw>=200 && rh>=70 && rx>=0 && rx+rw<=480 && ry>=0 && ry+rh<=320);
    puts("Stage4.32: dialogue placement, long choices, reply bubble, clamping PASS");
    return 0;
}
