#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
static uint8_t skin[640*80];
static uint8_t sprite_pixels[128*16];
static uint32_t last_icon_offset=0xffffffffu;
static int npcDrawCount=0, npcFlip=0, firstTileFlip=0;
static int sawFirstTile=0;
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char *s){(void)x;(void)y;(void)s;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *s){
  if(s->imgdat==sprite_pixels){npcDrawCount++;npcFlip=s->flags;}
  if(s->imgdat>=skin && s->imgdat<skin+sizeof(skin)){
    if(!sawFirstTile){firstTileFlip=s->flags;sawFirstTile=1;}
    if(s->drawx==56 && s->drawy==68)last_icon_offset=(uint32_t)(s->imgdat-skin);
  }
}
int main(void){
  gfxbob_t sprite={.imgdat=sprite_pixels,.atlas_stride=128,.atlas_height=16,
    .width=16,.height=16};
  const game_adventure_npc_frame_t idle[]={ {3,1},{0,3},{7,2} };
  const game_adventure_npc_frame_t talk[]={ {6,2},{5,1} };
  const game_adventure_npc_animation_t sequences[]={ {&sprite,0,3,6,0,2,5,idle,talk,
    BLIT_FLAG_FLIP_X|BLIT_FLAG_FLIP_Y} };
  const game_adventure_item_t items[]={ {"Key",2,300,1,0} };
  const game_adventure_node_t nodes[]={ {"Guardian","Hello",{{"Bye","",-1,-1,-1,-1,-1}}} };
  const game_adventure_npc_t npcs[]={ {100,100,16,16,48,0} };
  const uint16_t cells[9]={300,301,302,303,304,305,306,307,308};
  uint8_t flips[9]={BLIT_FLAG_FLIP_X};
  game_adventure_start(items,1,nodes,1,npcs,1,skin,640,80,8,cells,1,0,0);
  game_adventure_npc_animations(sequences,1);
  game_adventure_skin_flips(flips);
  game_adventure_input(0,100,100,16,16,1);
  assert(sprite.index==3);
  game_adventure_input(0,100,100,16,16,1);
  assert(sprite.index==0);
  game_adventure_input(0,100,100,16,16,3);
  assert(sprite.index==7);
  game_adventure_draw_npcs(20,30);
  assert(npcDrawCount==1 && npcFlip==(BLIT_FLAG_FLIP_X|BLIT_FLAG_FLIP_Y));
  game_adventure_input(BTN_FIRE2,100,100,16,16,1);
  game_adventure_input(0,100,100,16,16,1);
  assert(sprite.index==6); /* Talking state starts on its own first cell */
  game_adventure_input(0,100,100,16,16,2);
  assert(sprite.index==5);
  game_adventure_draw(0,0,100,100);
  assert(firstTileFlip==BLIT_FLAG_FLIP_X);
  assert(game_adventure_collect(2)==1 && game_adventure_quantity(0)==1);
  game_adventure_start(items,1,nodes,1,npcs,1,skin,640,80,8,cells,1,0,0);
  game_adventure_skin_flips(flips);
  game_adventure_input(BTN_UP|BTN_FIRE2,400,200,16,16,1);
  assert(game_adventure_open());
  game_adventure_draw(0,0,400,200);
  assert(last_icon_offset==((300u/80u)*8u*640u+(300u%80u)*8u));
  puts("Stage4.31 runtime: ordered per-frame timing, flips and 16-bit icons PASS");
  return 0;
}
