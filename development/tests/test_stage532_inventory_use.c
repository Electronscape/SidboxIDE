#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "adventureruntime.h"
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
#ifndef BTN_LEFT
#define BTN_LEFT 16u
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT 32u
#endif
static int calls,last_delta,ok=1;
static int word_x,drop_x;
static uint32_t labels_seen;
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char*s){(void)y; if(strcmp(s,"USE")==0) {word_x=x;labels_seen|=1;}
  if(strcmp(s,"DROP")==0) {drop_x=x;labels_seen|=2;}
  if(strcmp(s,"[")==0)labels_seen|=4;
  if(strcmp(s,"]")==0)labels_seen|=8;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t*s){(void)s;}
static uint8_t on_stat(const char*s,int32_t d,void*u){(void)u;assert(strcmp(s,"Magic")==0);++calls;last_delta=d;return (uint8_t)ok;}
static void push(uint8_t b){game_adventure_input(b,0,0,16,16,1);}
int main(void){
 game_adventure_item_t items[2]={{"Potion",0,65535,5,2},{"Crystal",0,65535,5,1}};
 game_adventure_item_style_t style[2]={{{65535,65535,65535,65535},0,0},{{65535,65535,65535,65535},0,1}};
 game_adventure_item_use_t effects[2]={{"Magic",5,1},{0,0,0}};
 uint16_t cells[9]={0};
 game_adventure_start(items,2,0,0,0,0,0,0,0,8,cells,2,0,0);
 game_adventure_item_styles(style,2);
 game_adventure_use_effects(effects,2,on_stat,0);
 assert(game_adventure_quantity(0)==2);
 push(BTN_FIRE2);push(0);
 labels_seen=0; game_adventure_draw(0,0,0,0);assert((labels_seen&13)==13);assert(word_x>0);
 ok=0;push(BTN_FIRE);push(0);assert(calls==1 && game_adventure_quantity(0)==2);
 ok=1;push(BTN_FIRE);push(0);assert(calls==2 && last_delta==5 && game_adventure_quantity(0)==1);
 // Select the discardable crystal, and confirm DROP does not move horizontally when selected.
 push(BTN_DOWN);push(0);labels_seen=0;game_adventure_draw(0,0,0,0);int first=drop_x;assert(first>0);
 push(BTN_RIGHT);push(0);labels_seen=0;game_adventure_draw(0,0,0,0);assert(drop_x==first);
 puts("PASS: USE callbacks (success/failure), consume one, protected usable, stable action positions");
 return 0;
}
