#include "adventureruntime.h"
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
static uint8_t ppb[1040+16*16];
static uint32_t position;
static int opened,drawn,skin_draws;
static uint8_t skin[16*16];
int sfopen(int slot,char *path,int mode){
    (void)slot;(void)mode;
    if(strcmp(path,"graphics/pickups.ppb")) return 1;
    ++opened;position=0;return FR_OK;
}
int sfread(int slot,void *buf,uint32_t count,uint32_t *got){
    (void)slot;
    if(position+count>sizeof(ppb)) {*got=0;return FR_OK;}
    memcpy(buf,ppb+position,count);position+=count;*got=count;return FR_OK;
}
int sflseek(int slot,uint32_t at){(void)slot;if(at>sizeof(ppb))return 1;position=at;return FR_OK;}
int sfclose(int slot){(void)slot;return FR_OK;}
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char *str){(void)x;(void)y;(void)str;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *s){
    if(s->imgdat>=skin && s->imgdat<skin+sizeof(skin)) {++skin_draws;return;}
    assert(s->atlas_stride==16);
    ++drawn;
}
static void press(uint8_t buttons){
    game_adventure_input(buttons,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,1);
}
int main(void){
    ppb[1]=0;ppb[2]=16;ppb[3]=0;ppb[4]=16;ppb[7]=1;ppb[8]=0;
    for(int i=0;i<256;++i)ppb[1040+i]=(uint8_t)i;
    static const game_adventure_item_t items[]={
        {"Flower",5,1,5,0},{"Kim Health",2,2,5,0}
    };
    static const game_adventure_item_style_t styles[]={
        {{1,1,1,1},0,1},{{2,2,2,2},0,1}
    };
    game_adventure_start(items,2,0,0,0,0,skin,16,16,8,0,1,0,0);
    game_adventure_item_styles(styles,2);
    game_adventure_item_atlas_file(0,"graphics/pickups.ppb",16,16,8);
    game_adventure_item_atlas_file(1,"graphics/pickups.ppb",16,16,8);
    game_adventure_prepare_owned_icons();
    assert(opened==0); /* empty backpack does not consume TFCard or RAM */
    assert(game_adventure_add(0,1)==1);
    assert(opened==1);
    assert(game_adventure_add(1,1)==1);
    assert(opened==1); /* shared PPB not reloaded for second icon */
    press(BTN_FIRE2);
    game_adventure_draw(0,0,100,100);
    assert(drawn>=2);
    assert(skin_draws==0);
    game_adventure_prepare_owned_icons();
    assert(opened==1);
    /* Reloading another world releases the privately owned file buffers. */
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    puts("Stage 5.45: portable PPB lazy load, atlas reuse, and inventory artwork PASS");
    return 0;
}
