#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static unsigned actions;
static char seen[200];
void test_colour(uint8_t c) {(void)c;}
void test_text(int x,int y,const char *text) {
    (void)x;(void)y;
    if(text && strstr(text,"missing")) strcpy(seen,"missing");
    if(text && strstr(text,"success")) strcpy(seen,"success");
}
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *sprite) {(void)sprite;}
static void action(uint16_t id, void *user) {(void)user; assert(id==11u); ++actions;}
static void input(uint8_t buttons, uint16_t frames) {
    (void)game_adventure_input(buttons,100,100,16,16,frames);
}
static void begin_dialogue(uint8_t has_item) {
    input(BTN_FIRE2,1);   /* NPC interaction */
    input(0,2000);        /* finish rendering node text */
    input(BTN_FIRE2,1);   /* select first answer */
    if (has_item) {       /* success still speaks the player's selected reply */
        input(0,2000);
        input(BTN_FIRE2,1);
    }                    /* missing item jumps straight to alternate NPC node */
    input(0,2000);
}
int main(void) {
    game_adventure_item_t items[] = { {"Key",0,65535,5,0} };
    game_adventure_node_t nodes[] = {
        {"NPC","Do you have the key?",{
            {"I can help", "I can help", 2, 1, 0, -1, -1, 11},
            {"", "", -1, -1, -1, -1, -1, -1},
            {"", "", -1, -1, -1, -1, -1, -1}
        }},
        {"NPC","Your key is missing",{
            {"Close", "", -1, -1, -1, -1, -1, -1}
        }},
        {"NPC","It is a success",{
            {"Close", "", -1, -1, -1, -1, -1, -1}
        }}
    };
    game_adventure_npc_t npc = {100,100,16,16,50,0};
    const uint8_t flags[] = {1,0,0,0,0,0,0,0,0};
    uint8_t used[96]={0}, completed[256]={0};
    game_adventure_start(items,1,nodes,3,&npc,1,0,0,0,8,0,1,action,0);
    game_adventure_story_flags(flags,0);
    begin_dialogue(0);
    assert(game_adventure_open());
    seen[0]=0;
    game_adventure_draw(0,0,100,100);
    assert(strcmp(seen,"missing")==0);
    assert(actions==0);
    game_adventure_save_progress(used,completed);
    assert(!(used[0]&1u));

    /* Re-enter with key and confirm the success path and its side-effects. */
    game_adventure_start(items,1,nodes,3,&npc,1,0,0,0,8,0,1,action,0);
    game_adventure_story_flags(flags,0);
    assert(game_adventure_add(0,1)==1);
    begin_dialogue(1);
    seen[0]=0;
    game_adventure_draw(0,0,100,100);
    assert(strcmp(seen,"success")==0);
    assert(actions==1);
    game_adventure_save_progress(used,completed);
    assert((used[0]&1u)!=0);

    /* Default missing_next=-1: the missing item cannot close the dialogue. */
    nodes[0].choices[0].missing_next=-1;
    game_adventure_start(items,1,nodes,3,&npc,1,0,0,0,8,0,1,action,0);
    input(BTN_FIRE2,1); input(0,2000); input(BTN_FIRE2,1);
    assert(game_adventure_open());
    assert(actions==1);
    puts("Stage5.25: missing/success/default fallback paths PASS");
    return 0;
}
