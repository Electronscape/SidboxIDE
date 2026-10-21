/* Host GCC test: zero-count rows stay hidden and owning a secret reveals it.
 * The NPC dialogue item quantities are unchanged by display filtering.
 */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static char drawn[512];
void test_colour(uint8_t c) { (void)c; }
void test_rect(int x,int y,int w,int h) { (void)x;(void)y;(void)w;(void)h; }
void test_bob(gfxbob_t *b) { (void)b; }
void test_text(int x,int y,const char *str) {
    (void)x;(void)y;
    if (str && strlen(drawn)+strlen(str)+2 < sizeof(drawn)) {
        strcat(drawn,"|"); strcat(drawn,str);
    }
}
static uint8_t old_hidden_filter(const char *name) {
    return name && strcmp(name,"Secret") != 0 && strcmp(name,"Other Secret") != 0;
}
static void advance(uint8_t buttons) { game_adventure_input(buttons,100,100,16,16,1); }
static void draw(void) { drawn[0]=0; game_adventure_draw(0,0,100,100); }
static void has(const char *name) { if (!strstr(drawn,name)) { fprintf(stderr,"Missing [%s] in [%s]\n",name,drawn); assert(0); } }
static void lacks(const char *name) { assert(strstr(drawn,name)==0); }
int main(void) {
    const game_adventure_item_t items[]={
        {"Key",0,65535,9,1}, {"Secret",0,65535,9,0},
        {"Map",0,65535,9,3}, {"Other Secret",0,65535,9,2},
        {"Gem",0,65535,9,5}
    };
    game_adventure_start(items,5,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_inventory_filter(old_hidden_filter);
    assert(game_adventure_quantity(1)==0);
    advance(BTN_UP | BTN_FIRE2);
    assert(game_adventure_open());
    draw(); has("Key x1"); has("Map x3"); lacks("Secret"); lacks("Gem x5");
    advance(0); advance(BTN_DOWN);
    draw(); has("Map x3"); has("Other Secret x2"); lacks("Key x1");
    advance(0); advance(BTN_DOWN);
    draw(); has("Other Secret x2"); has("Gem x5"); lacks("Secret x0");

    /* Picking up a secret reveals it, even while the old filter rejects it. */
    assert(game_adventure_add(1,1)==1 && game_adventure_quantity(1)==1);
    advance(0); advance(BTN_UP); advance(0); advance(BTN_UP);
    draw(); has("Key x1"); has("Secret x1"); lacks("Map x3");
    advance(0); advance(BTN_DOWN);
    draw(); has("Secret x1"); has("Map x3"); lacks("Key x1");

    /* Removing items while scrolled clamps scroll to the remaining rows. */
    assert(game_adventure_remove(3,2));
    assert(game_adventure_remove(4,5));
    assert(game_adventure_quantity(3)==0 && game_adventure_quantity(4)==0);
    draw(); has("Secret x1"); has("Map x3"); lacks("Other Secret"); lacks("Gem");
    assert(game_adventure_remove(1,1));
    draw(); has("Key x1"); has("Map x3"); lacks("Secret");
    assert(game_adventure_remove(0,1));
    assert(game_adventure_remove(2,3));
    draw(); has("INVENTORY"); lacks("Key x"); lacks("Map x");

    /* With no filter registered, zero-quantity items remain hidden. */
    game_adventure_set_inventory_filter(0);
    assert(game_adventure_add(1,2)==2);
    draw(); has("Secret x2"); lacks("Key x0");
    assert(game_adventure_quantity(1)==2);
    puts("Stage 5.4g: owned secret appears; zero quantities, scrolling and NPC counts: PASS");
    return 0;
}
