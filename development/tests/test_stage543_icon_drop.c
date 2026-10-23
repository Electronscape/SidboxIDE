#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 0x08u
#endif
static uint8_t skin[32*32], icon_sheet[64*64];
static int icon_draws, skin_draws, unexpected_draws;
void test_colour(uint8_t c) {(void)c;}
void test_text(int x,int y,const char *str){(void)x;(void)y;(void)str;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob){
    const uintptr_t address=(uintptr_t)bob->imgdat;
    if(address>=(uintptr_t)icon_sheet && address<(uintptr_t)(icon_sheet+sizeof(icon_sheet))) {
        assert(bob->atlas_stride==64);
        assert(bob->imgdat==icon_sheet+(2/8)*8*64+(2%8)*8);
        ++icon_draws;
    } else if(address>=(uintptr_t)skin && address<(uintptr_t)(skin+sizeof(skin))) {
        ++skin_draws;
    } else ++unexpected_draws;
}
static void press(uint8_t buttons){
    (void)game_adventure_input(buttons,100,100,16,16,1);
    (void)game_adventure_input(0,100,100,16,16,1);
}
int main(void){
    static const game_adventure_item_t items[]={ {"Kim Health",2,2,5,1} };
    static const game_adventure_item_style_t styles[]={ {{2,2,2,2},0,1} };
    static const uint16_t frame[9]={0,1,2,3,4,5,6,7,8};
    game_adventure_start(items,1,0,0,0,0,skin,32,32,8,frame,1,0,0);
    game_adventure_item_styles(styles,1);
    game_adventure_item_atlas(0,icon_sheet,64,64,8);
    press(BTN_FIRE2); /* Open inventory */
    game_adventure_draw(0,0,100,100);
    assert(icon_draws>=1); /* Inventory icon comes from selected PPB */
    icon_draws=skin_draws=unexpected_draws=0;
    press(BTN_FIRE); /* DROP */
    assert(game_adventure_quantity(0)==0);
    game_adventure_draw_npcs(0,0);
    assert(icon_draws==1 && skin_draws==0 && unexpected_draws==0);
    /* Explicit custom PPB missing at runtime: never silently draw skin tiles. */
    game_adventure_item_atlas(0,0,0,0,8);
    icon_draws=skin_draws=unexpected_draws=0;
    game_adventure_draw_npcs(0,0);
    assert(icon_draws==0 && skin_draws==0 && unexpected_draws==0);
    puts("Stage 5.43: selected PPB used for inventory and DROP, missing PPB does not fall back: PASS");
    return 0;
}
