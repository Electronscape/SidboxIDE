/* Stage 5.99.2: player-spoken replies inherit dialogue scales; inventory does not. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int scaled_reply, unscaled_reply, scaled_inventory, unscaled_inventory;
static uint8_t expect_sx, expect_sy;
static int reply_y, second_y;
static int rect_outside;
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h)
{ if(x<0 || y<0 || x+w>480 || y+h>320) ++rect_outside; }
void test_bob(gfxbob_t *b){(void)b;}
void test_text(int x,int y,const char *s)
{
    (void)x;(void)y;
    if(s && strstr(s,"REPLY")) { ++unscaled_reply; reply_y=y; }
    if(s && strstr(s,"SECOND")) second_y=y;
    if(s && strstr(s,"Potion")) ++unscaled_inventory;
}
void test_text_scaled(int x,int y,const char *s,uint8_t sx,uint8_t sy)
{
    (void)x;(void)y;
    if(s && strstr(s,"REPLY")) { assert(sx==expect_sx && sy==expect_sy); ++scaled_reply; reply_y=y; }
    if(s && strstr(s,"SECOND")) { assert(sx==expect_sx && sy==expect_sy); second_y=y; }
    if(s && strstr(s,"Potion")) ++scaled_inventory;
}
static const game_adventure_node_t nodes[]={
    {.speaker="Steve",.text="Hi",.choices={
        {.label="Answer",.reply="REPLY\nSECOND",.next=-1,.requires=-1,.give=-1,.take=-1}, {0},{0}
    }}
};
static const game_adventure_item_t items[]={
    {.name="Potion",.pickup_kind=0,.icon=65535u,.capacity=4u,.initial=1u}
};
static void tick(uint8_t b)
{ (void)game_adventure_input(b,200,160,16,16,100); }
static void reset(uint8_t sx,uint8_t sy)
{
    const uint16_t indices[9]={0};
    game_adventure_start(items,1,nodes,1,0,0,0,0,0,8,indices,1,0,0);
    game_adventure_dialogue_typography(sx,sy,1u,2u,1u);
    expect_sx=sx; expect_sy=sy;
    scaled_reply=unscaled_reply=scaled_inventory=unscaled_inventory=rect_outside=0;
    reply_y=second_y=-1000;
}
static void reply_test(uint8_t sx,uint8_t sy)
{
    reset(sx,sy);
    assert(game_adventure_trigger_dialogue(0));
    tick(0);tick(BTN_FIRE2);tick(0);
    game_adventure_draw(0,0,200,160);
    if(sx==1u && sy==2u) { assert(unscaled_reply>0); assert(scaled_reply==0); }
    else { assert(scaled_reply>0); assert(unscaled_reply==0); }
    assert(second_y-reply_y==8*(int)sy); /* row advances match glyph height */
    assert(rect_outside==0);
}
int main(void)
{
    reply_test(1u,2u); /* old projects: exactly the same text path */
    reply_test(1u,1u); /* requested 8x8 reply text */
    reply_test(2u,4u); /* independent X/Y scaling */
    reply_test(8u,8u); /* large glyphs: frame stays on the LCD */
    reset(2u,4u);
    tick(0);tick(BTN_FIRE2);tick(0); /* inventory instead of NPC dialogue */
    game_adventure_draw(0,0,200,160);
    assert(unscaled_inventory>0 && scaled_inventory==0);
    puts("Stage 5.99.2: scaled player replies / legacy inventory PASS");
    return 0;
}
