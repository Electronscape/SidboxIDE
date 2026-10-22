/* Stage 5.33: action completion closes bag, 10-frame bracket blink, and
   bottom trim without clipping dialogue or losing frame-aware insets. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
#ifndef BTN_LEFT
#define BTN_LEFT 16u
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT 32u
#endif

static int bracket_open, bracket_close, use_x, drop_x;
static int inv_y, inv_h, dlg_y, dlg_h, footer_y, body_x, answer_x, confirm_h;
static int stat_ok=1, stat_calls=0;
void test_colour(uint8_t c) {(void)c;}
void test_rect(int x,int y,int w,int h) {
    if(x==8 && w==464){inv_y=y;inv_h=h;}
    if(x==20 && w==440){dlg_y=y;dlg_h=h;}
    if(x==72 && w==336) confirm_h=h;
}
void test_bob(gfxbob_t *b) {(void)b;}
void test_text(int x,int y,const char *s) {
    if(!strcmp(s,"["))++bracket_open;
    if(!strcmp(s,"]"))++bracket_close;
    if(!strcmp(s,"USE"))use_x=x;
    if(!strcmp(s,"DROP"))drop_x=x;
    if(!strcmp(s,"FIRE2: CLOSE"))footer_y=y;
    if(!strcmp(s,"A dialogue body"))body_x=x;
    if(!strcmp(s,"Ask"))answer_x=x;
}
static uint8_t stat(const char *s,int32_t d,void *u) {
    (void)u; assert(!strcmp(s,"Health"));assert(d==5);++stat_calls;
    return (uint8_t)stat_ok;
}
static void tick(uint8_t keys,uint16_t frames) {
    (void)game_adventure_input(keys,0,0,16,16,frames);
}
static void tap(uint8_t keys) {tick(0,1);tick(keys,1);tick(0,1);}
static void draw_reset(void) {
    bracket_open=bracket_close=0;use_x=drop_x=0;footer_y=0;
    game_adventure_draw(0,0,0,0);
}
static const game_adventure_item_t items[]={
    {"Potion",0,65535,5,3}, {"Crystal",0,65535,5,3}
};
static const game_adventure_item_style_t styles[]={
    {{65535,65535,65535,65535},0,1},{{65535,65535,65535,65535},0,1}
};
static const game_adventure_item_use_t uses[]={ {"Health",5,1},{0,0,0} };
static const game_adventure_node_t nodes[]={
    {"Elder","A dialogue body",{{"Ask","Okay",-1,-1,-1,-1,-1,-1},{0},{0}}}
};
static const game_adventure_npc_t npcs[]={{100,100,16,16,32,0}};
static void setup(void) {
    uint16_t cells[9]={0};
    game_adventure_start(items,2,nodes,1,npcs,1,0,0,0,8,cells,1,0,0);
    game_adventure_item_styles(styles,2);
    game_adventure_use_effects(uses,2,stat,0);
}
int main(void) {
    setup();
    /* The inventory has 2 rows: 8px inset top/bottom, not one extra blank
       8px block after its actual rows and footer. */
    tap(BTN_FIRE2); assert(game_adventure_open());
    draw_reset();
    assert(inv_h==2*8+32+2*22);
    assert(footer_y==inv_y+inv_h-8-16);
    assert(bracket_open==1 && bracket_close==1);
    const int initial_use_x=use_x;
    tick(0,10);draw_reset();assert(bracket_open==0 && bracket_close==0);
    assert(use_x==initial_use_x);
    tick(0,10);draw_reset();assert(bracket_open==1 && bracket_close==1);
    assert(use_x==initial_use_x);
    /* Failed USE stays open and doesn't consume anything. */
    stat_ok=0;tap(BTN_FIRE);assert(game_adventure_open());
    assert(stat_calls==1 && game_adventure_quantity(0)==3);
    stat_ok=1;tap(BTN_FIRE);assert(!game_adventure_open());
    assert(stat_calls==2 && game_adventure_quantity(0)==2);

    /* DROP makes a recoverable world object and immediately closes. */
    tap(BTN_FIRE2);tap(BTN_RIGHT);draw_reset();
    assert(drop_x>use_x && bracket_open==1);
    tap(BTN_FIRE);assert(!game_adventure_open());
    assert(game_adventure_quantity(0)==1);

    /* DESTROY prompts first. NO returns to inventory, YES consumes one
       and closes. Confirm highlights blink; text remains fixed. */
    tap(BTN_FIRE2);tap(BTN_RIGHT);tap(BTN_RIGHT);tap(BTN_FIRE);
    assert(game_adventure_open());
    confirm_h=0;draw_reset();assert(bracket_open==1 && bracket_close==1); /* NO */
    assert(confirm_h==144);
    tick(0,10);draw_reset();assert(bracket_open==0 && bracket_close==0);
    tap(BTN_FIRE); assert(game_adventure_open()); /* NO */
    assert(game_adventure_quantity(0)==1);
    tap(BTN_FIRE); assert(game_adventure_open()); /* prompt again */
    tap(BTN_RIGHT);tap(BTN_FIRE); assert(!game_adventure_open());
    assert(game_adventure_quantity(0)==0);

    /* A single world dialogue uses the trimmed height and still renders
       both the NPC body and the player choice. */
    { uint16_t cells[9]={0};
      game_adventure_start(items,2,nodes,1,npcs,1,0,0,0,8,cells,1,0,0);
      game_adventure_dialogue_box(20,40,440,96);
      game_adventure_text_padding(8);
      tick(0,1);tick(BTN_FIRE2,1);tick(0,32); /* outside NPC: inventory */
      tap(BTN_FIRE2); /* close */
      (void)game_adventure_input(BTN_FIRE2,100,100,16,16,1);
      tick(0,32);
      dlg_h=body_x=answer_x=0;
      game_adventure_draw(0,0,100,100);
      assert(dlg_h>=88 && dlg_h<=96);
      assert(body_x==28 && answer_x==42);
    }
    puts("Stage 5.33: action closing, failed/cancelled action, 10-frame blinking, and box trim PASS");
    return 0;
}
