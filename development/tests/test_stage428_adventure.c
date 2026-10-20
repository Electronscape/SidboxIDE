#include "adventureruntime.h"
#include "apis.h"
#include <assert.h>
#include <stdio.h>
void gfx_setcolour(int x){(void)x;}
void gfx_rectf(int a,int b,int c,int d){(void)a;(void)b;(void)c;(void)d;}
void gfx_drawbob(gfxbob_t *s){(void)s;}
void gfx_drawtext(int a,int b,const char*s){(void)a;(void)b;(void)s;}
static int events=0;
void callback(uint16_t id,void *user){(void)user; events+=id;}
int main(void){
 static const game_adventure_item_t items[]={{"Key",3,0,2,0},{"Coin",1,0,99,0}};
 static const game_adventure_node_t nodes[]={
  {"Guard","Got a key?",{{"Unlock","I found it",-1,0,-1,0,3},{"No", "Bye",-1,-1,-1,-1,-1},{0}}}
 };
 static const game_adventure_npc_t npcs[]={{10,10,16,16,40,0}};
 game_adventure_start(items,2,nodes,1,npcs,1,0,0,0,8,0,2,callback,0);
 assert(game_adventure_quantity(0)==0);
 assert(game_adventure_collect(3)==1);
 assert(game_adventure_quantity(0)==1);
 assert(game_adventure_collect(3)==1);
 assert(game_adventure_quantity(0)==2);
 assert(game_adventure_collect(3)==1);
 assert(game_adventure_quantity(0)==2);
 assert(game_adventure_input(BTN_FIRE2,15,15,16,16,1)==1);
 assert(game_adventure_open());
 game_adventure_input(0,15,15,16,16,100);
 game_adventure_input(BTN_FIRE2,15,15,16,16,1);
 assert(game_adventure_quantity(0)==1);assert(events==3);
 game_adventure_input(0,15,15,16,16,3);
 game_adventure_input(BTN_FIRE2,15,15,16,16,1);
 assert(!game_adventure_open());
 game_adventure_input(0,300,200,16,16,1);
 game_adventure_input(BTN_UP | BTN_FIRE2,300,200,16,16,1);
 assert(game_adventure_open());
 game_adventure_input(0,300,200,16,16,1);
 game_adventure_input(BTN_FIRE2,300,200,16,16,1);
 assert(!game_adventure_open());
 puts("ADV runtime host checks passed");return 0;
}
