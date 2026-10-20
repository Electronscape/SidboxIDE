#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int action_calls, saw_completed;
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
void test_text(int x,int y,const char *str){(void)x;(void)y;if(str && strstr(str,"Thank you"))saw_completed=1;}
static void on_action(uint16_t action, void *user){(void)user; assert(action==9u);action_calls++;}
static void advance(uint8_t buttons,uint16_t frames){
    game_adventure_input(buttons,100,100,16,16,frames);
}
int main(void){
    const game_adventure_item_t items[]={ {"Rare Flower",5u,65535u,1u,0u} };
    const game_adventure_node_t nodes[]={
        {"Guardian","Please bring me a flower",{
            {"Give a flower","",-1,0,-1,0,9}, {"Leave","",-1,-1,-1,-1,-1}, {0}
        }},
        {"Guardian","Thank you for helping me!",{{"Goodbye","",-1,-1,-1,-1,-1},{0},{0}}}
    };
    const game_adventure_npc_t npcs[]={ {100,100,16,16,50u,0u} };
    const uint8_t choice_flags[]={ 3u,0u,0u, 0u,0u,0u };
    const uint16_t completed[]={ 1u };
    game_adventure_start(items,1,nodes,2,npcs,1,0,0,0,8,0,1,on_action,0);
    game_adventure_story_flags(choice_flags,completed);
    // No flower: trying the "give" choice does not mark completion or fire event.
    advance(BTN_FIRE2,1);advance(0,70);advance(BTN_FIRE2,1);
    assert(game_adventure_open() && action_calls==0);
    advance(0,1);advance(BTN_UP,1);advance(0,1);advance(BTN_FIRE2,1); // Leave
    advance(0,1);advance(BTN_FIRE2,1); // close player's reply
    assert(!game_adventure_open());
    // Custom kind 5 is mapped directly; 1..4 remain unchanged.
    assert(game_adventure_collect(5u)==1u);
    assert(game_adventure_quantity(0)==1u);
    advance(0,1);advance(BTN_FIRE2,1);advance(0,70);
    advance(BTN_FIRE2,1); // give flower
    assert(game_adventure_quantity(0)==0u && action_calls==1);
    advance(0,1);advance(BTN_FIRE2,1);
    assert(!game_adventure_open());
    // Returning to same NPC now uses its completed greeting, not original request.
    advance(0,1);advance(BTN_FIRE2,1);advance(0,70);
    game_adventure_draw(0,0,100,100);
    assert(saw_completed);
    assert(action_calls==1);
    puts("Stage4.34: custom pickup 5, one-time choice, failed attempt, NPC completed greeting PASS");
    return 0;
}
