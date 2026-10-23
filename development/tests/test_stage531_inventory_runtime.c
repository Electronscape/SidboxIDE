#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 0x08u
#endif
static char words[8000];
static int row_y[50], row_count, frame_h;
static int bob_draws;
void test_colour(uint8_t c) {(void)c;}
void test_rect(int x,int y,int w,int h) {
    if (x==8 && w==464) frame_h=h;
    (void)y;
}
void test_text(int x,int y,const char *s) {
    if (s && strlen(words)+strlen(s)+2 < sizeof(words)) {
        strcat(words,"|");strcat(words,s);
    }
    if (s && strstr(s,"thing")!=NULL && row_count<50) row_y[row_count++]=y;
    (void)x;
}
void test_bob(gfxbob_t *b){ (void)b; ++bob_draws; }
static void draw(void) {words[0]=0;frame_h=0;row_count=0;bob_draws=0;game_adventure_draw(0,0,100,100);}
static uint8_t input_at(uint8_t buttons,int x,int y) {
    return game_adventure_input(buttons,x,y,16,16,1);
}
static uint8_t input(uint8_t buttons) {return input_at(buttons,100,100);}
static void release(void) {(void)input(0);}
static void key(uint8_t k) {(void)input(k);release();}
int main(void) {
    static uint8_t atlas[32*32];
    static const uint16_t skin[9]={0,1,2,3,4,5,6,7,8};
    static const game_adventure_item_t items[]={{"Red thing",0,0,12,2},{"Quest thing",0,0,12,1}};
    static const game_adventure_item_style_t styles[]={{{0,0,0,0},0,1},{{0,0,0,0},0,0}};
    game_adventure_start(items,2,0,0,0,0,atlas,32,32,8,skin,1,0,0);
    game_adventure_item_styles(styles,2);
    assert(input(BTN_FIRE2));release();
    draw(); assert(frame_h==100);
    assert(strstr(words,"Inventory:"));
    assert(strstr(words,"FIRE2: CLOSE"));
    assert(strstr(words,"|DROP|") && strstr(words,"|[|"));
    assert(strstr(words,"DESTROY"));
    assert(!strstr(words,"UP/DOWN") && !strstr(words,"PROTECTED"));
    /* DROP is selected by default, drops 1 copy into the world. */
    key(BTN_FIRE);
    assert(game_adventure_quantity(0)==1);
    assert(!game_adventure_open());
    key(BTN_FIRE2); /* successful DROP now closes: reopen for inspection */
    draw();assert(frame_h==100);
    assert(strstr(words,"Red thing x1"));
    /* A dropped item should still render on the world after inventory closes. */
    key(BTN_FIRE2);
    bob_draws=0;game_adventure_draw_npcs(0,0); assert(bob_draws==1);
    /* Standing on it must not auto-collect; leave then return. */
    input(0);assert(game_adventure_quantity(0)==1);
    input_at(0,190,190);assert(game_adventure_quantity(0)==1);
    input(0);assert(game_adventure_quantity(0)==2);
    bob_draws=0;game_adventure_draw_npcs(0,0); assert(bob_draws==0);
    /* Protected item has no drop/destroy options and cannot be acted on. */
    key(BTN_FIRE2);key(BTN_DOWN);draw();
    assert(strstr(words,"Quest thing x1"));
    key(BTN_FIRE);draw();assert(!strstr(words,"Destroy ONE item?"));
    assert(game_adventure_quantity(1)==1);
    /* DESTROY is separate, default confirmation is NO. */
    key(BTN_UP);key(BTN_RIGHT); draw();assert(strstr(words,"|DESTROY|") && strstr(words,"|[|"));
    key(BTN_FIRE); draw();assert(strstr(words,"Destroy ONE item?"));
    key(BTN_FIRE);assert(game_adventure_quantity(0)==2);
    key(BTN_FIRE);key(BTN_RIGHT);key(BTN_FIRE);
    assert(game_adventure_quantity(0)==1);
    assert(!game_adventure_open());
    /* Dropped progress roundtrip: world snapshot keeps an item between visits. */
    key(BTN_FIRE2); /* Reopen after successful DESTROY; DROP is default. */
    key(BTN_FIRE);assert(game_adventure_quantity(0)==0);
    assert(!game_adventure_open());
    game_adventure_drop_t saved[GAME_ADVENTURE_MAX_DROPS];
    game_adventure_save_drops(saved);
    assert(saved[0].active);
    game_adventure_start(items,2,0,0,0,0,atlas,32,32,8,skin,1,0,0);
    game_adventure_item_styles(styles,2);
    /* Simulate the world manager restoring zero remaining copies by name. */
    assert(game_adventure_remove(0,2));
    assert(!game_adventure_quantity(0));
    game_adventure_restore_drops(saved);
    bob_draws=0;game_adventure_draw_npcs(0,0); assert(bob_draws==1);
    input_at(0,190,190);input_at(0,100,100);
    assert(game_adventure_quantity(0)==1);
    /* Ten items fill the box; an eleventh enables scrolling. */
    game_adventure_item_t many[11];
    char names[11][16];
    for (unsigned i=0;i<11;++i) {
        snprintf(names[i],sizeof(names[i]),"Thing %02u",i);
        many[i].name=names[i];many[i].pickup_kind=0;
        many[i].icon=0;many[i].capacity=10;many[i].initial=1;
    }
    game_adventure_start(many,11,0,0,0,0,atlas,32,32,8,skin,1,0,0);
    key(BTN_FIRE2);
    draw(); assert(frame_h==276);
    assert(strstr(words,"Thing 00 x1"));
    assert(!strstr(words,"Thing 10 x1"));
    for (unsigned i=0;i<10;++i) key(BTN_DOWN);
    draw(); assert(frame_h==276);
    assert(strstr(words,"Thing 10 x1"));
    assert(!strstr(words,"Thing 00 x1"));
    puts("Stage 5.31: inventory autoheight/scroll, actions, drop/pickup, protection, destroy, save/restore PASS");
    return 0;
}
