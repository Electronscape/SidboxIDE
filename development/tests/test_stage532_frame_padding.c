#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int inventory_frame_y, inventory_frame_h, other_frame_x, other_frame_y;
static int header_x,header_y,footer_x,footer_y,speaker_x,speaker_y;
static int body_x,body_y,reply_x,reply_y;
static int frame_seen;
void test_colour(uint8_t c) { (void)c; }
void test_bob(gfxbob_t *b) { (void)b; }
void test_rect(int x,int y,int w,int h) {
    if (x == 8 && w == 464) {inventory_frame_y=y;inventory_frame_h=h;}
    else if (w > 120 && h >= 16) {other_frame_x=x;other_frame_y=y;frame_seen=1;}
}
void test_text(int x,int y,const char *s) {
    if (!strcmp(s,"Inventory:")) {header_x=x;header_y=y;}
    else if (!strcmp(s,"FIRE2: CLOSE")) {footer_x=x;footer_y=y;}
    else if (!strcmp(s,"Elder")) {speaker_x=x;speaker_y=y;}
    else if (!strcmp(s,"Hello traveler")) {body_x=x;body_y=y;}
    else if (!strcmp(s,"Sure")) {reply_x=x;reply_y=y;}
}
static void input(uint8_t b,int x,int y,unsigned frames) {
    (void)game_adventure_input(b,x,y,16u,16u,(uint16_t)frames);
}
static void release(int x,int y) {input(0,x,y,1);}
static void press(int x,int y) {release(x,y);input(BTN_FIRE2,x,y,1);release(x,y);}
static const uint16_t skin[9]={0,1,2,3,4,5,6,7,8};
static const game_adventure_item_t items[]={ {"Apple",0,0,3,1} };
static const game_adventure_node_t nodes[]={
    {"Elder","Hello traveler",{{"Yes","Sure",-1,-1,-1,-1,-1,-1},{0},{0}}}
};
static const game_adventure_npc_t npcs[]={ {100,100,16,16,30,0} };
static uint8_t atlas[128*128];
static void check(int tile,int optional,int has_skin) {
    const int border=has_skin?tile:0;
    const int i_pad=border+8, d_pad=border+optional;
    game_adventure_start(items,1,nodes,1,npcs,1,
        has_skin?atlas:0,has_skin?128:0,has_skin?128:0,(uint8_t)tile,skin,1,0,0);
    game_adventure_dialogue_box(20,40,440,96);
    game_adventure_text_padding((uint8_t)optional);
    inventory_frame_y=-1;header_x=footer_x=-1;
    press(2,2); /* Player outside NPC: open inventory */
    game_adventure_draw(0,0,2,2);
    assert(inventory_frame_y>=0);
    assert(header_x==8+i_pad);
    assert(header_y==inventory_frame_y+i_pad);
    assert(footer_x==8+464-i_pad-12*8);
    assert(footer_y==inventory_frame_y+inventory_frame_h-i_pad-8);
    assert(inventory_frame_h<=320);
    assert(header_y>=inventory_frame_y+border+8);
    press(2,2); /* close inventory */

    speaker_x=body_x=reply_x=-1;
    frame_seen=0;
    press(100,100); /* Talk to Elder */
    input(0,100,100,100);
    game_adventure_draw(0,0,100,100);
    assert(frame_seen && speaker_x==other_frame_x+d_pad);
    assert(speaker_y==other_frame_y+d_pad);
    assert(body_x==other_frame_x+d_pad);
    assert(body_y>=other_frame_y+d_pad);

    /* Select answer: the player's reply bubble obeys the same inset. */
    press(100,100);
    input(0,100,100,100);
    frame_seen=0;
    game_adventure_draw(0,0,100,100);
    if(!(frame_seen && reply_x==other_frame_x+d_pad)) fprintf(stderr,"tile=%d extra=%d skin=%d frame=%d x=%d dx=%d rep=%d ry=%d\n",tile,optional,has_skin,frame_seen,other_frame_x,d_pad,reply_x,reply_y);
    assert(frame_seen && reply_x==other_frame_x+d_pad);
    assert(reply_y==other_frame_y+d_pad);
    press(100,100); /* return to idle */
}
int main(void) {
    for(int tile=8;tile<=32;tile*=2)
        for(int extra=0;extra<=8;extra+=8) check(tile,extra,1);
    check(8,0,0);check(8,8,0);
    puts("Stage 5.32: real frame-border + 8px inventory padding; 0/8px dialogue and reply padding PASS");
    return 0;
}
