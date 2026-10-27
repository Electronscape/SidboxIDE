/* Stage 5.69: escalating wrong-item reactions and world transition memory. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int reveal_hits, wrong_hits;
static int observed[5];
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
void test_text(int x,int y,const char *s){
 (void)x;(void)y;
 const char *lines[]={"Hehehe!","Stop that!","The key is behind the clock!",
                      "Not the feather again!","That's the wrong item."};
 for(int i=0;i<5;i++)if(strstr(s,lines[i]))observed[i]++;
}
static void action(uint16_t id,void *u){(void)u;if(id==61)reveal_hits++;if(id==20)wrong_hits++;}
static const game_adventure_item_t items[]={
  {"Key",0,65535,1,1},{"Feather",0,65535,1,1},{"Apple",0,65535,1,1}};
static const game_adventure_node_t nodes[]={
  {"Future Kim","Have you got the key?",{{"Offer",0,5,-1,-1,-1,-1,-1},{0},{0}}},
  {"Future Kim","Hehehe!",{{0},{0},{0}}},
  {"Future Kim","Stop that!",{{0},{0},{0}}},
  {"Future Kim","The key is behind the clock!",{{0},{0},{0}}},
  {"Future Kim","Not the feather again!",{{0},{0},{0}}},
  {"Future Kim","That's the wrong item.",{{0},{0},{0}}}
};
static const game_adventure_npc_t npcs[]={{100,100,16,16,48,0}};
static game_adventure_exchange_t rules[18];
static const game_adventure_wrong_repeat_t repeat[]={
 {0u,1,{1,2,3,4},61}
};
static void tick(uint8_t keys,uint16_t f){game_adventure_input(keys,100,100,16,16,f);}
static void tap(uint8_t k){tick(0,1);tick(k,1);tick(0,1);}
static void start(void){
 uint16_t cells[9]={0};memset(rules,0,sizeof(rules));
 rules[0].items[0]=0;rules[0].items[1]=-1;rules[0].items[2]=-1;rules[0].items[3]=-1;
 rules[0].count=1;rules[0].wrong_next=5;rules[0].wrong_action=20;
 game_adventure_start(items,3,nodes,6,npcs,1,0,0,0,8,cells,1,action,0);
 game_adventure_exchange_rules(rules,18);
 game_adventure_wrong_repeat_rules(repeat,1);
}
static void open_give(void){
 tap(BTN_FIRE2);tick(0,90);tap(BTN_FIRE2);assert(game_adventure_open());
}
static void offer_feather(int expected){
 open_give();tap(BTN_DOWN);tap(BTN_FIRE);
 /* A dialogue branch is displayed, but the item is not removed. */
 assert(game_adventure_quantity(1)==1);
 tick(0,90);
 game_adventure_draw(0,0,100,100);
 assert(observed[expected]>0);
 tap(BTN_FIRE2);
}
int main(void){
 uint8_t saved[GAME_ADVENTURE_EXCHANGE_SLOTS]={0};
 start();
 offer_feather(0);game_adventure_save_wrong_repeats(saved);
 assert(saved[0]==1 && reveal_hits==0 && wrong_hits==0);
 offer_feather(1);game_adventure_save_wrong_repeats(saved);
 assert(saved[0]==2 && reveal_hits==0 && wrong_hits==0);
 /* Same world entered again, restore only the old world's counts. */
 start();game_adventure_restore_wrong_repeats(saved);
 offer_feather(2);game_adventure_save_wrong_repeats(saved);
 assert(saved[0]==3 && reveal_hits==1 && wrong_hits==0);
 offer_feather(3);game_adventure_save_wrong_repeats(saved);
 assert(saved[0]==4 && reveal_hits==1 && wrong_hits==0);
 for(int i=0;i<5;i++)offer_feather(3);
 game_adventure_save_wrong_repeats(saved);
 assert(saved[0]==4 && reveal_hits==1);
 /* Other wrong items still take the original fallback. The backpack is
  * ordered by acquisition (newest first), NOT item-definition order:
  * Apple is row 0, Feather row 1, Key row 2. Choosing row 2 would
  * correctly hand over the Key, not exercise the wrong-item action. */
 open_give();tap(BTN_FIRE);
 assert(wrong_hits==1 && game_adventure_quantity(2)==1 && game_adventure_quantity(0)==1);
 /* No repeat rule: original exchange is unchanged. */
 start();game_adventure_wrong_repeat_rules(0,0);
 open_give();tap(BTN_DOWN);tap(BTN_FIRE);
 assert(wrong_hits==2 && reveal_hits==1);
 puts("Stage 5.69 repeated item: 1/2/3/4+, action once, fallback, save/restore PASS");
 return 0;
}
