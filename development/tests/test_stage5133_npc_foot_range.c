/* Stage 5.133: NPC talk distance uses the saved Player Animation Foot X.
   The user's hand-maintained main.c may pass sprite top-left + hitbox size.
   No physics/movement collision values may be changed as a side effect. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int32_t sprite_x, sprite_y = 96;
static uint8_t sprite_available, seen_npc, seen_inventory;
static int sprite_reads;
static uint8_t sprite_origin(int32_t *x,int32_t *y)
{
    ++sprite_reads;
    if (!sprite_available) return 0u;
    *x=sprite_x; *y=sprite_y;
    return 1u;
}
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
void test_text(int x,int y,const char *s)
{
    (void)x;(void)y;
    if (s && strstr(s,"FOREST")) seen_npc=1u;
    if (s && strstr(s,"Inventory:")) seen_inventory=1u;
}
static const game_adventure_node_t nodes[] = {
    {"Big Steve", "FOREST", {{0},{0},{0}}}
};
static const game_adventure_npc_t npcs[] = {
    {200,100,32,32,30,0} /* centre X=216, NPC range [186,246] */
};
static const uint16_t frame_cells[9] = {0,1,2,3,4,5,6,7,8};
static uint8_t frame_pixels[32*32];
/* Input width 25 is a collision-box measurement, NOT sprite width 64.
   The actual interaction X is sprite_x+32 (saved Foot X). */
static uint8_t probe(int32_t player_sprite_x, uint8_t use_anchor,
                     uint8_t origin_available, int32_t input_x, uint16_t height)
{
    seen_npc=seen_inventory=0u;
    sprite_reads=0;
    sprite_x=player_sprite_x;
    sprite_available=origin_available;
    game_adventure_start(0,0,nodes,1,npcs,1,
                         frame_pixels,32,32,8,frame_cells,1,0,0);
    if (use_anchor) game_adventure_set_drop_anchor(sprite_origin,32,63,25,62);
    (void)game_adventure_input(BTN_FIRE2,input_x,96,25,height,1);
    (void)game_adventure_input(0,input_x,96,25,height,80);
    game_adventure_draw(0,0,input_x,96);
    assert((seen_npc ^ seen_inventory) && "Either NPC speech or inventory must open");
    return seen_npc;
}
int main(void)
{
    /* Foot X = sprite X + 32. Range boundaries MUST be symmetric. */
    assert(probe(154,1,1,154,40)==1); /* left edge: foot 186 */
    assert(sprite_reads==1);
    assert(probe(214,1,1,214,40)==1); /* right edge: foot 246 */
    assert(probe(153,1,1,153,40)==0); /* one pixel too far LEFT */
    assert(probe(215,1,1,215,40)==0); /* one pixel too far RIGHT */
    assert(probe(230,1,1,230,40)==0); /* old sprite X+12 would talk */
    /* Prefer LIVE sprite position over possibly stale callback argument. */
    assert(probe(154,1,1,230,40)==1);
    /* Existing old projects and temporarily unbound physics retain behaviour. */
    assert(probe(230,0,1,230,40)==1);
    assert(probe(230,1,0,230,40)==1);
    /* Vertical talk range remains based on legacy input box midpoint. */
    assert(probe(154,1,1,154,200)==0);
    puts("Stage 5.133 NPC Foot X range, symmetry, fallback and Y compatibility PASS");
    return 0;
}
