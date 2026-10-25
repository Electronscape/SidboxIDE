#include "adventureruntime.h"
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#ifndef BTN_FIRE
#define BTN_FIRE 8u
#endif
#ifndef BTN_FIRE2
#define BTN_FIRE2 4u
#endif
#ifndef BTN_LEFT
#define BTN_LEFT 16u
#endif
#ifndef BTN_RIGHT
#define BTN_RIGHT 32u
#endif
#define GAME_TILE_SOLID 1u
#define GAME_TILE_ONEWAY 2u
typedef struct { const uint8_t *collision; uint16_t width,height,tile_size; } game_tilemap_t;
static uint8_t cells[20*16];
static game_tilemap_t world={cells,20,16,16};
static game_tilemap_t *active=&world;
static void *gameworlds_map(void) { return active; }
static uint8_t game_tile_at(const game_tilemap_t *map,int32_t tx,int32_t ty)
{
    return (!map || tx<0 || ty<0 || tx>=map->width || ty>=map->height)
        ? 0u : map->collision[ty*map->width+tx];
}
static uint8_t game_tilemap_actor_blocked(const game_tilemap_t *map,
                                          int32_t x,int32_t y,uint16_t w,uint16_t h)
{
    for(int32_t yy=y;yy<y+(int32_t)h; ++yy)
        for(int32_t xx=x;xx<x+(int32_t)w; ++xx)
            if(xx>=0 && yy>=0 &&
                game_tile_at(map,xx/(int32_t)map->tile_size,yy/(int32_t)map->tile_size)==GAME_TILE_SOLID)
                return 1u;
    return 0u;
}
#include "stage5130_generated_sweep.inc"
void test_colour(uint8_t col){(void)col;}
void test_text(int x,int y,const char *t){(void)x;(void)y;(void)t;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob){(void)bob;}
static int32_t sx=60,sy=20;
static uint8_t valid=1u;
static uint8_t sprite_position(int32_t *x,int32_t *y)
{
    if(!valid) return 0u;
    *x=sx;*y=sy;return 1u;
}
static void tick(uint8_t buttons)
{ (void)game_adventure_input(buttons,1,1,25,62,1); }
static void drop(void)
{
    tick(BTN_FIRE2);tick(0u);  /* Inventory */
    tick(BTN_FIRE);tick(0u);
}
static void reset(uint8_t facing)
{
    static uint8_t atlas[32*32];
    static const uint16_t icons[9]={0,1,2,3,4,5,6,7,8};
    static const game_adventure_item_t items[]={{"Stone",0,0,10,4}};
    static const game_adventure_item_style_t styles[]={{{0,0,0,0},0,0,1}};
    memset(cells,0,sizeof(cells));
    active=&world;valid=1u;sx=60;sy=20;
    game_adventure_start(items,1,0,0,0,0,atlas,32,32,8,icons,1,0,0);
    game_adventure_item_styles(styles,1);
    game_adventure_set_drop_anchor(sprite_position,32,63,25,62);
    game_adventure_set_drop_sweep(gameadventure_drop_sweep);
    game_adventure_set_player_facing(facing);
}
int main(void)
{
    game_adventure_drop_t d[GAME_ADVENTURE_MAX_DROPS];
    /* Free trajectory: original Stage 5.129 placement is unchanged. */
    reset(1u);drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==125 && d[0].y==44);
    assert(game_adventure_quantity(0)==3u);
    /* Wall crossing target footprint: stop BEFORE crossing it. */
    reset(1u);cells[2*20+8]=GAME_TILE_SOLID;cells[3*20+8]=GAME_TILE_SOLID;
    drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==112 && d[0].y==44);
    assert(game_adventure_quantity(0)==3u);
    /* More important: destination is clear, but a THIN wall lies en route. */
    reset(1u);cells[2*20+6]=GAME_TILE_SOLID;cells[3*20+6]=GAME_TILE_SOLID;
    assert(!game_tilemap_actor_blocked(&world,125,44,16,16));
    drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==80); /* 80..95, wall begins x96 */
    /* The opposite side uses the SAME foot anchor; never go through left wall. */
    reset(0u);cells[2*20+3]=GAME_TILE_SOLID;cells[3*20+3]=GAME_TILE_SOLID;
    drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==64 && d[0].y==44);
    /* Left: wall lies BETWEEN foot and otherwise clear final target. */
    reset(0u);cells[2*20+4]=GAME_TILE_SOLID;cells[3*20+4]=GAME_TILE_SOLID;
    assert(!game_tilemap_actor_blocked(&world,43,44,16,16));
    drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==80); /* outside the wall at 64..79 */
    /* One-way platforms DO NOT block horizontal travel. */
    reset(1u);cells[2*20+8]=GAME_TILE_ONEWAY;
    drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==125);
    /* If the item starts embedded in a solid, don't lose it. */
    reset(1u);cells[2*20+5]=GAME_TILE_SOLID; /* start 76..91 intersects 80..95 */
    drop();game_adventure_save_drops(d);
    assert(!d[0].active && game_adventure_quantity(0)==4u);
    assert(game_adventure_open());
    /* Clamp to the far map edge, never disappear into the void. */
    reset(1u);sx=245;drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==304); /* map = 320, item width = 16 */
    /* No callback: backwards-compatible foot placement. */
    reset(1u);game_adventure_set_drop_sweep(0);
    cells[2*20+8]=GAME_TILE_SOLID;drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==125);
    /* Missing map shouldn't cause an item loss. */
    reset(1u);active=0;drop();game_adventure_save_drops(d);
    assert(d[0].active && d[0].x==125);
    puts("Stage 5.130 wall-sweep, foot anchor, map bounds, no inventory loss PASS");
    return 0;
}
