/* Stage 5.34: GIVE, wrong-item, ALL/ANY, hand-ins, cross-world progress. */
#include "adventureruntime.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
static int last_action, wrong_hits, partial_hits, success_hits, draw_give, give_prompt;
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
void test_text(int x,int y,const char *s){(void)x;(void)y;if(!strcmp(s,"GIVE"))++draw_give; if(strstr(s,"FIRE1: CONFIRM"))++give_prompt;}
static void action(uint16_t id,void *user){(void)user;last_action=id;
    if(id==20)++wrong_hits;
    if(id==21)++partial_hits;
    if(id==22)++success_hits;}
static const game_adventure_item_t items[]={
    {"Ruby",0,65535,9,1},{"Sapphire",0,65535,9,1},{"Banana",0,65535,9,1}};
static const game_adventure_node_t nodes[]={
    {"Wizard","Bring the gems",{{"Offer an item",0,3,-1,-1,-1,-1,22},{0},{0}}},
    {"Wizard","That is wrong!",{{0},{0},{0}}},
    {"Wizard","I still need another",{{0},{0},{0}}},
    {"Wizard","Thank you!",{{0},{0},{0}}}
};
static const game_adventure_npc_t npcs[]={{100,100,16,16,48,0}};
static game_adventure_exchange_t rules[12];
static void tick(uint8_t keys,uint16_t frames){game_adventure_input(keys,100,100,16,16,frames);}
static void tap(uint8_t k){tick(0,1);tick(k,1);tick(0,1);}
static void setup(int any,int incremental){
    uint16_t cells[9]={0};
    memset(rules,0,sizeof(rules));
    rules[0].items[0]=0;rules[0].items[1]=1;
    rules[0].items[2]=-1;rules[0].items[3]=-1;
    rules[0].count=2;rules[0].any=(uint8_t)any;
    rules[0].incremental=(uint8_t)incremental;rules[0].consume=1;
    rules[0].wrong_next=1;rules[0].partial_next=2;
    rules[0].wrong_action=20;rules[0].partial_action=21;
    game_adventure_start(items,3,nodes,4,npcs,1,0,0,0,8,cells,1,action,0);
    game_adventure_exchange_rules(rules,12);
}
static void open_give(void){
    tap(BTN_FIRE2); tick(0,90); tap(BTN_FIRE2); assert(game_adventure_open());
    draw_give=give_prompt=0;game_adventure_draw(0,0,100,100);assert(draw_give>0 && give_prompt>0);
}
static void close_dialogue(void){tick(0,90);tap(BTN_FIRE2);}
int main(void){
    /* Wrong offering retains inventory and runs ONLY wrong callback. */
    setup(0,0);open_give();tap(BTN_DOWN);tap(BTN_DOWN);tap(BTN_FIRE);
    assert(last_action==20 && wrong_hits==1);
    assert(game_adventure_quantity(0)==1 && game_adventure_quantity(1)==1 && game_adventure_quantity(2)==1);
    close_dialogue();
    /* ANY = OR: Sapphire alone succeeds and consumes only that item. */
    setup(1,0);open_give();tap(BTN_DOWN);tap(BTN_FIRE);
    assert(last_action==22 && success_hits==1);
    assert(game_adventure_quantity(0)==1 && game_adventure_quantity(1)==0);
    /* ALL-at-once = AND, atomically consumes both requested items. */
    setup(0,0);open_give();tap(BTN_FIRE);
    assert(success_hits==2);
    assert(game_adventure_quantity(0)==0 && game_adventure_quantity(1)==0);
    /* ALL-at-once cannot partially consume an offer when a second part is absent. */
    setup(0,0);
    game_adventure_remove(1,1);
    open_give();tap(BTN_FIRE);
    assert(last_action==22 && partial_hits==0); /* no hint/event on an incomplete exchange */
    assert(game_adventure_quantity(0)==1 && game_adventure_quantity(1)==0);
    /* Incremental AND: Ruby delivered now, Sapphire after world re-entry. */
    setup(0,1);open_give();tap(BTN_FIRE);
    assert(last_action==22 && partial_hits==0); /* hand-in remembered silently */
    assert(game_adventure_quantity(0)==0 && game_adventure_quantity(1)==1);
    uint8_t saved[GAME_ADVENTURE_EXCHANGE_SLOTS];
    game_adventure_save_exchanges(saved);
    assert(saved[0]==1u);
    setup(0,1);
    game_adventure_restore_exchanges(saved);
    game_adventure_remove(0,1); /* shared inventory restored separately */
    open_give();tap(BTN_FIRE);
    assert(last_action==22 && success_hits==3);
    assert(game_adventure_quantity(1)==0);
    /* Re-offering the already delivered Ruby is rejected without consuming. */
    setup(0,1);game_adventure_restore_exchanges(saved);open_give();tap(BTN_FIRE);
    assert(last_action==20 && game_adventure_quantity(0)==1);
    puts("Stage 5.34.2: GIVE/AND/OR/wrong/silent hand-ins/world-restore PASS");
    return 0;
}
