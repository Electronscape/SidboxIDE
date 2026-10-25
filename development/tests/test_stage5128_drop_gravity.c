#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
#ifndef BTN_FIRE2
#define BTN_FIRE2 4u
#endif
#ifndef BTN_LEFT
#define BTN_LEFT 16u
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT 32u
#endif
void test_colour(uint8_t col) {(void)col;}
void test_text(int x,int y,const char *t){(void)x;(void)y;(void)t;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob){(void)bob;}
static int32_t surface=145;
static unsigned floor_calls=0;
static int32_t floor_at(int32_t x,int32_t old_y,int32_t next_y)
{
    (void)x;
    ++floor_calls;
    /* A simple platform at 145: the 16px item lands with y=129. */
    const int32_t item_y=surface-16;
    return item_y>=old_y && item_y<=next_y ? item_y : INT32_MAX;
}
static void push(uint8_t buttons, int32_t px,int32_t py,uint16_t pw,uint16_t ph)
{ (void)game_adventure_input(buttons,px,py,pw,ph,1); }
static void drop(int32_t px,int32_t py,uint16_t pw,uint16_t ph)
{
    push(BTN_FIRE2,px,py,pw,ph);push(0,px,py,pw,ph);
    push(BTN_FIRE,px,py,pw,ph);push(0,px,py,pw,ph);
    assert(!game_adventure_open());
}
int main(void)
{
    static uint8_t skin[32*32];
    static const uint16_t cells[9]={0,1,2,3,4,5,6,7,8};
    static const game_adventure_item_t items[]={{"Stone",0,0,10,3}};
    static const game_adventure_item_style_t style[]={{{0,0,0,0},0,0,1}};
    game_adventure_drop_t saved[GAME_ADVENTURE_MAX_DROPS];
    game_adventure_start(items,1,0,0,0,0,skin,32,32,8,cells,1,0,0);
    game_adventure_item_styles(style,1);
    game_adventure_set_drop_floor(floor_at);
    game_adventure_set_player_facing(1);
    /* The caller passes the EXACT hitbox (sprite+offset), not sprite origin. */
    drop(107,100,22,32);
    game_adventure_save_drops(saved);
    assert(saved[0].active && saved[0].x==137);  /* 107+22+8 */
    assert(saved[0].y==108);                    /* midpoint 100+16-8 */
    for (int i=0; i<45; ++i) push(0,107,100,22,32);
    game_adventure_save_drops(saved);
    assert(saved[0].y==129); /* settled on floor */
    assert(floor_calls>0);
    for (int i=0; i<25; ++i) push(0,107,100,22,32);
    game_adventure_save_drops(saved);
    assert(saved[0].y==129); /* stays landed */
    /* World-save preserves the current position, not temporary speed. */
    game_adventure_restore_drops(saved);
    game_adventure_save_drops(saved);
    assert(saved[0].y==129 && saved[0].active);
    /* Walking left, then opening inventory must not change facing. */
    push(BTN_LEFT,200,100,22,32);push(0,200,100,22,32);
    drop(200,100,22,32);
    game_adventure_save_drops(saved);
    assert(saved[1].active && saved[1].x==176); /* 200-16-8 */
    assert(saved[1].y==108);
    /* Older saves need no field changes: the structure is unchanged. */
    assert(sizeof(game_adventure_drop_t)==12u);
    puts("Stage 5.128 drop midpoint, facing, gravity, collision, world-save PASS");
    return 0;
}
