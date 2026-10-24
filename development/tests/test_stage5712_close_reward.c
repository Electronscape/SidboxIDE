/* Terminal dialogue gifts fire on close, once per world, with NPC hiding. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static const game_adventure_item_t items[]={{"Feather",8,0,9,0},{"Dildo",9,0,9,0}};
static const game_adventure_node_t nodes[]={
    {"Future Kim","NOT THE FEATHER AGAIN!",{{0},{0},{0}}}
};
static const game_adventure_npc_t npcs[]={{100,100,16,16,30,0}};
static const game_adventure_close_gift_t gifts[]={{0u,1u}};
static const game_adventure_npc_choice_action_t npc_action[]={
    {3u,0u,UINT16_MAX,GAME_ADVENTURE_NPC_HIDE,0u}
};
static const uint16_t skin[9]={0};
static uint8_t memory[GAME_ADVENTURE_CLOSE_GIFT_BYTES];
void test_colour(uint8_t x){(void)x;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_text(int x,int y,const char *t){(void)x;(void)y;(void)t;}
void test_bob(gfxbob_t *b){(void)b;}
static void tick(uint8_t buttons,int frames){game_adventure_input(buttons,100,100,16,16,(uint16_t)frames);}
static void tap(uint8_t button){tick(0,1);tick(button,1);tick(0,1);}
static void fresh(void){
  game_adventure_start(items,2,nodes,1,npcs,1,0,0,0,8,skin,1,0,0);
  game_adventure_close_gifts(gifts,1);
  game_adventure_npc_choice_actions(npc_action,1);
}
static void talk(void){tap(BTN_FIRE2);tick(0,70);tap(BTN_FIRE2);}
int main(void){
  fresh();assert(game_adventure_quantity(1)==0);
  talk();
  assert(game_adventure_quantity(1)==1);
  assert(!game_adventure_npc_visible(0));
  game_adventure_save_close_gifts(memory);
  /* Can re-show the NPC but closing again must not give a second item. */
  game_adventure_npc_action(0,GAME_ADVENTURE_NPC_SHOW);
  talk();assert(game_adventure_quantity(1)==1);
  /* A world switch resets runtime tables but restores claimed gifts. */
  fresh();game_adventure_restore_close_gifts(memory);
  talk();assert(game_adventure_quantity(1)==0);
  /* A fresh session grants again. */
  fresh();talk();assert(game_adventure_quantity(1)==1);
  puts("Stage 5.71.2 terminal one-time gift, NPC hide and world restore PASS");
  return 0;
}
