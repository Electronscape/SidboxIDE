#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 0x01u
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT 0x20u
#endif

static char words[1200];
static const uint8_t *pixels;
static unsigned hits;
static uint8_t verify_quad;
void test_colour(uint8_t c) {(void)c;}
void test_rect(int x, int y, int w, int h) {(void)x;(void)y;(void)w;(void)h;}
void test_text(int x, int y, const char *str) {
    (void)x;(void)y;
    if (str && strlen(words)+strlen(str)+2 < sizeof(words)) {
        strcat(words,"|"); strcat(words,str);
    }
}
void test_bob(gfxbob_t *bob) {
    static const int xy[4][2]={{40,142},{48,142},{40,150},{48,150}};
    static const unsigned offset[4]={8,16,24,256};
    for (int i=0;i<4;i++) {
        if (verify_quad && bob->drawx==xy[i][0] && bob->drawy==xy[i][1]) {
            assert(bob->imgdat == pixels+offset[i]);
            hits++;
        }
    }
}
static uint8_t input(uint8_t buttons)
{ return game_adventure_input(buttons,100,100,16,16,1); }
static void up(void) {(void)input(0);}
static void draw(void) {words[0]=0;hits=0;game_adventure_draw(0,0,100,100);}
int main(void)
{
    uint8_t atlas[32*32]={0}; pixels=atlas;
    const uint16_t frame[9]={0,1,2,3,4,5,6,7,8};
    const game_adventure_item_t items[]={{"Apple",0,0,99,2},{"Quest key",0,0,99,1}};
    const game_adventure_item_style_t styles[]={
        {{1,2,3,4},1,1},{{0,0,0,0},0,0}
    };
    game_adventure_start(items,2,NULL,0,NULL,0,atlas,32,32,8,frame,1,NULL,NULL);
    game_adventure_item_styles(styles,2);
    game_adventure_text_padding(0);
    assert(input(BTN_FIRE2)==1); up();
    verify_quad=1; draw();assert(hits==4); verify_quad=0;
    assert(strstr(words,"Apple x2"));
    assert(input(BTN_RIGHT)==1);up();
    assert(input(BTN_FIRE)==1);up();
    draw();assert(strstr(words,"Destroy ONE item?"));
    /* NO is preselected, accidental confirmation cannot consume an item. */
    assert(input(BTN_FIRE)==1);up();
    assert(game_adventure_quantity(0)==2);
    assert(input(BTN_FIRE)==1);up();
    assert(input(BTN_RIGHT)==1);up();
    assert(input(BTN_FIRE)==1);up();
    assert(game_adventure_quantity(0)==1);
    assert(!game_adventure_open());
    assert(input(BTN_FIRE2)==1);up(); /* Reopen after confirmed DESTROY. */
    assert(input(BTN_DOWN)==1);up();
    assert(input(BTN_FIRE)==1);up();
    draw();
    assert(game_adventure_quantity(1)==1);
    assert(!strstr(words,"Destroy ONE item?"));
    /* Old five-field struct initializer remains source-compatible. */
    game_adventure_start(items,2,NULL,0,NULL,0,atlas,32,32,8,frame,1,NULL,NULL);
    assert(input(BTN_FIRE2)==1); up();
    assert(input(BTN_FIRE)==1);up();
    draw();assert(!strstr(words,"Destroy ONE item?"));
    puts("Stage 5.31: 2x2 atlas icon, destroy YES/NO, protected item and default-safe PASS");
    return 0;
}
