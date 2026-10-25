#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 0x08u
#endif
#ifndef BTN_LEFT
#define BTN_LEFT 0x10u
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT 0x20u
#endif
static void noop(void) {}
void test_colour(uint8_t col) {(void)col;}
void test_text(int x,int y,const char *t) {(void)x;(void)y;(void)t;}
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob) {(void)bob;}
static void tick(uint8_t b,int x) {(void)game_adventure_input(b,x,100,16,16,1);}
static void drop(int x) {
    tick(BTN_FIRE2,x);tick(0,x);    /* open inventory */
    tick(BTN_FIRE,x);tick(0,x);      /* drop action */
    assert(!game_adventure_open());
}
int main(void) {
    static uint8_t atlas[32*32];
    static const uint16_t cells[9]={0,1,2,3,4,5,6,7,8};
    static const game_adventure_item_t items[]={ {"Stone",0,0,10,3} };
    static const game_adventure_item_style_t style[]={{{0,0,0,0},0,0,1}};
    game_adventure_drop_t saved[GAME_ADVENTURE_MAX_DROPS];
    (void)noop;
    game_adventure_start(items,1,0,0,0,0,atlas,32,32,8,cells,1,0,0);
    game_adventure_item_styles(style,1);
    game_adventure_set_player_facing(1);
    drop(100);
    game_adventure_save_drops(saved);
    assert(saved[0].active && saved[0].x == 124);
    assert(game_adventure_quantity(0)==2);
    /* Walking left sets direction; navigating inventory does not change it. */
    tick(BTN_LEFT,200);tick(0,200);
    drop(200);
    game_adventure_save_drops(saved);
    assert(saved[1].active && saved[1].x == 176);
    assert(game_adventure_quantity(0)==1);
    /* Walking right again changes drop side; left boundary clamps to zero. */
    tick(BTN_RIGHT,200);tick(0,200);
    drop(200);
    game_adventure_save_drops(saved);
    assert(saved[2].active && saved[2].x == 224);
    assert(game_adventure_quantity(0)==0);
    /* Restore & set exact initial facing, including a spawn at the left edge. */
    game_adventure_start(items,1,0,0,0,0,atlas,32,32,8,cells,1,0,0);
    game_adventure_item_styles(style,1);
    game_adventure_set_player_facing(0);
    drop(5);
    game_adventure_save_drops(saved);
    assert(saved[0].active && saved[0].x == 0);
    printf("Stage 5.126: right/left direction, idle facing, bounds and inventory PASS\n");
    return 0;
}
