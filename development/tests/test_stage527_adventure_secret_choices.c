/* Runtime regression: secret required-item options must not leak availability
 * and the missing branch must jump straight to the selected NPC node. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static unsigned actions;
static unsigned x_marks;
static unsigned seen_missing;
static unsigned seen_success;
static unsigned seen_player_reply;

void test_colour(uint8_t c) { (void)c; }
void test_text(int x, int y, const char *t)
{
    (void)x; (void)y;
    if (!t) return;
    if (!strcmp(t,"X")) ++x_marks;
    if (strstr(t,"missing")) ++seen_missing;
    if (strstr(t,"success")) ++seen_success;
    if (strstr(t,"I have the key")) ++seen_player_reply;
}
void test_rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *sprite) {(void)sprite;}
static void action(uint16_t id, void *user)
{
    (void)user;
    assert(id==11u);
    ++actions;
}
static void input(uint8_t buttons, uint16_t frames)
{
    (void)game_adventure_input(buttons,100,100,16,16,frames);
}

int main(void)
{
    const game_adventure_item_t items[]={{"Key",0,65535,5,0}};
    const game_adventure_node_t nodes[]={
        {"NPC","Do you have the key?",{
            {"Sure, I'll help", "I have the key", 2, 1, 0, -1, -1, 11},
            {"", "", -1, -1, -1, -1, -1, -1},
            {"", "", -1, -1, -1, -1, -1, -1}
        }},
        {"NPC","The key is missing",{
            {"Close", "", -1, -1, -1, -1, -1, -1}
        }},
        {"NPC","It is a success",{
            {"Close", "", -1, -1, -1, -1, -1, -1}
        }}
    };
    const game_adventure_npc_t npc={100,100,16,16,50,0};
    const uint8_t flags[]={3,0,0,0,0,0,0,0,0};
    uint8_t used[96]={0};
    uint8_t completed[256]={0};

    game_adventure_start(items,1,nodes,3,&npc,1,0,0,0,8,0,1,action,0);
    game_adventure_story_flags(flags,0);
    input(BTN_FIRE2,1);  /* NPC intro */
    input(0,2000);       /* show full text/choices */
    game_adventure_draw(0,0,100,100);
    assert(x_marks==0);  /* never annotate missing item with an X */
    assert(game_adventure_quantity(0)==0);
    input(BTN_FIRE2,1); /* choose the answer without key */
    input(0,2000);
    game_adventure_draw(0,0,100,100);
    assert(seen_missing>0);        /* fallback node appears without extra FIRE2 */
    assert(seen_player_reply==0);  /* no successful-player-speech bubble */
    assert(x_marks==0);
    assert(actions==0);
    assert(game_adventure_quantity(0)==0);
    game_adventure_save_progress(used,completed);
    assert(!(used[0]&1u));
    assert(!completed[0]);

    /* With the key, retain the normal player-speech step and successful actions. */
    x_marks=seen_missing=seen_success=seen_player_reply=0;
    game_adventure_start(items,1,nodes,3,&npc,1,0,0,0,8,0,1,action,0);
    game_adventure_story_flags(flags,0);
    assert(game_adventure_add(0,1)==1);
    input(BTN_FIRE2,1);
    input(0,2000);
    game_adventure_draw(0,0,100,100);
    assert(x_marks==0);
    input(BTN_FIRE2,1);
    input(0,2000);
    game_adventure_draw(0,0,100,100);
    assert(seen_player_reply>0);
    assert(actions==1);
    input(BTN_FIRE2,1);
    input(0,2000);
    game_adventure_draw(0,0,100,100);
    assert(seen_success>0);
    game_adventure_save_progress(used,completed);
    assert(used[0]&1u);
    assert(completed[0]);
    puts("Stage 5.27: hidden choices + immediate fallback + successful branch PASS");
    return 0;
}
