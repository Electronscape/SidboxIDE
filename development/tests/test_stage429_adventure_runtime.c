#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
static int drawn, colour_count, colour;
static int outline_colours, foreground_colours;
void test_colour(uint8_t c){colour=c;colour_count++;}
void test_text(int x,int y,const char *text){(void)x;(void)y;(void)text;drawn++;
  if(colour == 3) outline_colours++;
  if(colour == 15)foreground_colours++;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *s){(void)s;}
int main(void){
 static uint8_t pixels[128];
 gfxbob_t sprite={.imgdat=pixels,.atlas_stride=64,.atlas_height=16,.width=16,.height=16};
 game_adventure_npc_t npc[]={ {100,100,16,16,48,0} };
 game_adventure_node_t node[]={ {"Guardian","Hello there!",{{"Bye","Bye!",-1,-1,-1,-1,-1}}} };
 game_adventure_npc_animation_t anim[]={ {&sprite,0,2,2,2,2,1,0,0,0} };
 game_adventure_start(0,0,node,1,npc,1,0,0,0,8,0,2,0,0);
 game_adventure_text_style(15,1,3);
 game_adventure_npc_animations(anim,1);
 game_adventure_input(0,100,100,16,16,1);
 assert(sprite.index==0);
 game_adventure_input(0,100,100,16,16,2);
 assert(sprite.index==1);
 game_adventure_input(BTN_FIRE2,100,100,16,16,1);
 assert(game_adventure_open());
 game_adventure_input(0,100,100,16,16,1);
 assert(sprite.index==2);
 game_adventure_input(0,100,100,16,16,1);
 assert(sprite.index==3);
 game_adventure_draw(0,0,100,100);
 assert(outline_colours>=4 && foreground_colours>=1);
 assert(drawn == outline_colours + foreground_colours);
 puts("Stage4.29 runtime colour/outline/NPC idle-talk test PASS");
 return 0;
}
