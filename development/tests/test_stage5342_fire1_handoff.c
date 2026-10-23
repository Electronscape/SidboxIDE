/* A real modal FIRE1 must never reach gameplay jump, even after closing. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
void test_text(int x,int y,const char *s){(void)x;(void)y;(void)s;}
static uint8_t input(uint8_t keys) {
    game_adventure_input(keys,200,100,16,16,1);
    return game_adventure_gameplay_buttons(keys);
}
static const game_adventure_item_t items[]={ {"Crystal",0,65535,5,2} };
static const game_adventure_item_use_t uses[]={ {"Health",25,1} };
static const game_adventure_item_style_t styles[]={ {{65535,65535,65535,65535},0,1} };
static uint8_t apply(const char *key,int32_t d,void *u) {(void)key;(void)d;(void)u;return 1u;}
int main(void) {
    static const uint16_t cells[9]={0};
    game_adventure_start(items,1,0,0,0,0,0,0,0,8,cells,1,0,0);
    game_adventure_item_styles(styles,1);
    game_adventure_use_effects(uses,1,apply,0);
    input(0);
    assert(input(BTN_FIRE)==BTN_FIRE); /* Gameplay jump when idle. */
    input(0);
    input(BTN_FIRE2); input(0); /* Inventory open. */
    assert(game_adventure_open());
    assert(input(BTN_FIRE)==0); /* USE succeeds, closes inventory. */
    assert(!game_adventure_open());
    assert(input(BTN_FIRE)==0); /* Still held cannot jump. */
    assert(input(0)==0); /* Release clears suppression. */
    assert(input(BTN_FIRE)==BTN_FIRE); /* Next fresh press jumps. */
    input(0);
    input(BTN_FIRE2);input(0);
    input(BTN_RIGHT);input(0); /* DROP selection. */
    assert(input(BTN_FIRE)==0 && !game_adventure_open());
    assert(input(BTN_FIRE)==0);input(0);
    puts("Stage 5.34.2: FIRE1 modal handoff and held-release PASS");
    return 0;
}
