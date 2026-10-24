/* Stage 5.71 NPC visibility: invisible never renders/talks;
 * successful dialogue can atomically hide Big Steve and reveal his suit;
 * world reload restores visibility without disk access. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int bob_hits[2], story_events;
static uint8_t dummy_pixels[64] = {1};
static gfxbob_t bobs[2];
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_text(int x,int y,const char*s){(void)x;(void)y;(void)s;}
void test_bob(gfxbob_t *b){for(int i=0;i<2;i++)if(b==&bobs[i])bob_hits[i]++;}
static void on_event(uint16_t action,void *u){(void)u;if(action==77u)story_events++;}
static const game_adventure_node_t nodes[]={
  {"Big Steve","Here are my clothes!",{{"Goodbye",0,-1,-1,-1,-1,-1,77},{0},{0}}},
  {"Big Steve","Nice suit!",{{0},{0},{0}}}
};
static const game_adventure_npc_t npcs[]={
  {100,100,16,16,30,0}, {180,100,16,16,30,1}
};
static const game_adventure_npc_choice_action_t actions[]={
  {0u,0u,1u,GAME_ADVENTURE_NPC_HIDE,GAME_ADVENTURE_NPC_SHOW}
};
static const uint8_t initial[]={1u,0u};
static uint8_t saved[GAME_ADVENTURE_NPC_VISIBILITY_BYTES];
static int px=100;
static void tick(uint8_t keys,int frames){game_adventure_input(keys,px,100,16,16,(uint16_t)frames);}
static void tap(uint8_t k){tick(0,1);tick(k,1);tick(0,1);}
static void fresh(void){
    static const uint16_t cells[9]={0};
    memset(bob_hits,0,sizeof(bob_hits));
    for(int i=0;i<2;i++){
        bobs[i].imgdat=dummy_pixels;
        bobs[i].width=bobs[i].height=16;
        bobs[i].atlas_stride=bobs[i].atlas_height=16;
    }
    game_adventure_start(0,0,nodes,2,npcs,2,0,0,0,8,cells,1,on_event,0);
    game_adventure_npc_initial_visibility(initial,2);
    static const game_adventure_npc_animation_t anim[]={
        {&bobs[0],0,0,0,0,0,0,0,0,0},
        {&bobs[1],0,0,0,0,0,0,0,0,0}
    };
    game_adventure_npc_animations(anim,2);
    game_adventure_npc_choice_actions(actions,1);
}
int main(void){
    fresh();
    assert(game_adventure_npc_visible(0)==1);
    assert(game_adventure_npc_visible(1)==0);
    game_adventure_draw_npcs(0,0);
    assert(bob_hits[0]==1 && bob_hits[1]==0);
    /* Hidden NPC: FIRE2 at suit location opens inventory, not conversation. */
    px=180; tap(BTN_FIRE2);assert(game_adventure_open());tap(BTN_FIRE2);
    px=100; tap(BTN_FIRE2);assert(game_adventure_open());
    tick(0,90);tap(BTN_FIRE2);
    assert(game_adventure_npc_visible(0)==0);
    assert(game_adventure_npc_visible(1)==1);
    assert(story_events==1); /* independent custom event remains enabled */
    game_adventure_draw_npcs(0,0);
    assert(bob_hits[0]==1 && bob_hits[1]==1);
    /* Changing worlds retains visibility through existing generated snapshots. */
    game_adventure_save_npc_visibility(saved);
    fresh();assert(game_adventure_npc_visible(0)==1 && !game_adventure_npc_visible(1));
    game_adventure_restore_npc_visibility(saved);
    assert(!game_adventure_npc_visible(0) && game_adventure_npc_visible(1));
    /* Hidden Big Steve cannot be talked to on return to his location. */
    px=100;tap(BTN_FIRE2);assert(game_adventure_open());tap(BTN_FIRE2);
    px=180;tap(BTN_FIRE2);assert(game_adventure_open());
    game_adventure_npc_action(1,GAME_ADVENTURE_NPC_TOGGLE);
    assert(!game_adventure_npc_visible(1));
    game_adventure_npc_action(1,GAME_ADVENTURE_NPC_SHOW);
    assert(game_adventure_npc_visible(1));
    game_adventure_set_npc_visible(999u,0u);
    assert(!game_adventure_npc_visible(999u));
    puts("Stage 5.71 visibility, two choice actions, draw, talk, world restore, toggle PASS");
    return 0;
}
