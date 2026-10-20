#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static uint8_t skin[640*80];
static uint8_t spritePixels[64*16];
static uint32_t tileOffset = 0xffffffffu;
static int npcX = -1, npcY = -1, lineLength = -1, secondLine = 0;
static uint8_t colour;
void test_colour(uint8_t c){colour=c;}
void test_text(int x,int y,const char *text){
    if(colour==15 && x==32 && y==180) lineLength=(int)strlen(text);
    if(colour==15 && x==32 && y==196 && text[0]) secondLine=1;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *s){
    if(s->imgdat>=skin && s->imgdat<skin+sizeof(skin) && tileOffset==0xffffffffu) {
        tileOffset=(uint32_t)(s->imgdat-skin);
        assert(s->index==0); /* Rebased image pointer, never 8bit-truncate index 300 */
    }
    if(s->imgdat==spritePixels){npcX=s->drawx;npcY=s->drawy;}
}
int main(void){
    static char message[90];memset(message,'A',75);message[75]=0;
    gfxbob_t guardian={.imgdat=spritePixels,.atlas_stride=64,.atlas_height=16,.width=16,.height=16};
    game_adventure_item_t items[]={ {"Key",1,0,1,0} };
    game_adventure_node_t nodes[]={ {"Guardian",message,{{"Bye","",-1,-1,-1,-1,-1}}} };
    game_adventure_npc_t npcs[]={ {100,100,16,16,48,0} };
    game_adventure_npc_animation_t animations[]={ {&guardian,0,0,1,0,0,1,0,0,0} };
    uint16_t cells[9]={300,301,302,303,304,305,306,307,308};
    game_adventure_start(items,1,nodes,1,npcs,1,skin,640,80,8,cells,1,0,0);
    game_adventure_text_style(15,0,1);
    game_adventure_npc_animations(animations,1);
    game_adventure_draw_npcs(20,30);
    assert(npcX==80 && npcY==70);
    assert(game_adventure_collect(1)==1 && game_adventure_quantity(0)==1);
    game_adventure_input(BTN_FIRE2,100,100,16,16,1);
    game_adventure_input(0,100,100,16,16,100);
    game_adventure_draw(0,0,100,100);
    const uint32_t expected=(300u/80u)*8u*640u+(300u%80u)*8u;
    assert(tileOffset==expected);
    assert(lineLength==50 && secondLine);
    puts("Stage 4.30 runtime: 8px wrap, 16-bit tile selection, NPC autodraw and item collection PASS");
    return 0;
}
