#include "adventureruntime.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
#ifndef BTN_FIRE2
#define BTN_FIRE2 4u
#endif
#ifndef BTN_LEFT
#define BTN_LEFT 16u
#endif
void test_colour(uint8_t col) {(void)col;}
void test_text(int x,int y,const char *t){(void)x;(void)y;(void)t;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob){(void)bob;}
static int32_t sprite_x=100, sprite_y=200;
static uint8_t valid=1;
static uint8_t sprite_position(int32_t *x,int32_t *y)
{
    if (!valid) return 0;
    *x=sprite_x; *y=sprite_y;
    return 1;
}
static void tick(uint8_t b)
{ (void)game_adventure_input(b,777,888,25,62,1); }
static void drop(void)
{
    tick(BTN_FIRE2); tick(0);
    tick(BTN_FIRE); tick(0);
    assert(!game_adventure_open());
}
int main(void)
{
    static uint8_t skin[32*32];
    static const uint16_t cells[9]={0,1,2,3,4,5,6,7,8};
    static const game_adventure_item_t items[]={{"Stone",0,0,10,4}};
    static const game_adventure_item_style_t styles[]={{{0,0,0,0},0,0,1}};
    game_adventure_drop_t drops[GAME_ADVENTURE_MAX_DROPS];
    game_adventure_start(items,1,0,0,0,0,skin,32,32,8,cells,1,0,0);
    game_adventure_item_styles(styles,1);
    /* The input rectangle is deliberately bogus: dropped item must use the
       sprite's live X/Y plus foot anchor, not input hitbox or sprite corner. */
    game_adventure_set_drop_anchor(sprite_position,32,63,25,62);
    game_adventure_set_player_facing(1);
    drop();
    game_adventure_save_drops(drops);
    assert(drops[0].active && drops[0].x==165 && drops[0].y==224);
    /* Facing left retains the last real movement direction. */
    tick(BTN_LEFT); tick(0);
    drop();
    game_adventure_save_drops(drops);
    assert(drops[1].active && drops[1].x==83 && drops[1].y==224);
    /* The position source is sampled LIVE, not cached on world setup. */
    sprite_x=300; sprite_y=150;
    drop();
    game_adventure_save_drops(drops);
    assert(drops[2].active && drops[2].x==283 && drops[2].y==174);
    /* Missing bound sprite: backwards-compatible original placement. */
    valid=0;
    drop();
    game_adventure_save_drops(drops);
    assert(drops[3].active && drops[3].x==753 && drops[3].y==911);
    puts("Stage 5.129 foot anchor drop + live position + fallback PASS");
    return 0;
}
