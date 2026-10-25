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
#define GAME_TILE_SOLID 1u
#define GAME_TILE_ONEWAY 2u
typedef struct { const uint8_t *collision; uint16_t width,height,tile_size; } game_tilemap_t;
static uint8_t cells[20*16];
static game_tilemap_t world={cells,20,16,16};
static void *gameworlds_map(void) { return &world; }
static uint8_t game_tile_at(const game_tilemap_t *map,int32_t tx,int32_t ty)
{
    return (!map || tx<0 || ty<0 || tx>=map->width || ty>=map->height)
        ? 0u : map->collision[ty*map->width+tx];
}
static uint8_t game_tilemap_actor_blocked(const game_tilemap_t *map,
                                          int32_t x,int32_t y,uint16_t w,uint16_t h)
{
    for(int32_t yy=y;yy<y+(int32_t)h;++yy)
        for(int32_t xx=x;xx<x+(int32_t)w;++xx)
            if(xx>=0 && yy>=0 &&
                game_tile_at(map,xx/(int32_t)map->tile_size,yy/(int32_t)map->tile_size)==GAME_TILE_SOLID)
                return 1u;
    return 0u;
}
#include "stage5131_generated_sweep.inc"
void test_colour(uint8_t col){(void)col;}
void test_text(int x,int y,const char *t){(void)x;(void)y;(void)t;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *bob){(void)bob;}
static int32_t sprite_x=60,sprite_y=20;
static uint8_t provide_physics=1;
static uint8_t sprite_origin(int32_t *x,int32_t *y)
{ *x=sprite_x; *y=sprite_y; return 1u; }
static uint8_t live_hitbox(int32_t *x,int32_t *y,uint16_t *w,uint16_t *h)
{
    if(!provide_physics) return 0u;
    *x=sprite_x+19; *y=sprite_y+2; *w=25; *h=62;
    return 1u;
}
/* Mimic old user main.c: Adventure still receives sprite top-left. */
static void tick(uint8_t buttons)
{ (void)game_adventure_input(buttons,sprite_x,sprite_y,25u,62u,1u); }
static void drop_item(void)
{ tick(BTN_FIRE2);tick(0u);tick(BTN_FIRE);tick(0u); }
static void reset(uint8_t facing)
{
    static uint8_t atlas[32*32];
    static const uint16_t icons[9]={0,1,2,3,4,5,6,7,8};
    static const game_adventure_item_t items[]={{"Stone",0,0,10,4}};
    static const game_adventure_item_style_t styles[]={{{0,0,0,0},0,0,1}};
    memset(cells,0,sizeof(cells));
    sprite_x=60;sprite_y=20;provide_physics=1;
    game_adventure_start(items,1,0,0,0,0,atlas,32,32,8,icons,1,0,0);
    game_adventure_item_styles(styles,1);
    game_adventure_set_drop_anchor(sprite_origin,32,63,25,62);
    game_adventure_set_drop_sweep(gameadventure_drop_sweep);
    game_adventure_set_pickup_rect(live_hitbox);
    game_adventure_set_player_facing(facing);
}
int main(void)
{
    game_adventure_drop_t drops[GAME_ADVENTURE_MAX_DROPS];
    /* Wall on RIGHT: collision hitbox can reach item, sprite-left box cannot. */
    reset(1u);cells[2*20+8]=GAME_TILE_SOLID;cells[3*20+8]=GAME_TILE_SOLID;
    drop_item();game_adventure_save_drops(drops);
    assert(drops[0].active && drops[0].x==112 && game_adventure_quantity(0)==3u);
    sprite_x=84; /* sprite-left 84..108 never reaches item at 112! */
    tick(0u);
    assert(game_adventure_quantity(0)==4u);
    game_adventure_save_drops(drops);assert(!drops[0].active);
    /* Wall on LEFT: also use collision hitbox, never an asymmetrical box. */
    reset(0u);cells[2*20+3]=GAME_TILE_SOLID;cells[3*20+3]=GAME_TILE_SOLID;
    drop_item();game_adventure_save_drops(drops);
    assert(drops[0].active && drops[0].x==64 && game_adventure_quantity(0)==3u);
    sprite_x=90;tick(0u); /* Leave the one-pixel initial overlap. */
    sprite_x=47;tick(0u);
    assert(game_adventure_quantity(0)==4u);
    /* Close RIGHT wall: an overlapping new drop must not insta-collect.
       Moving away arms it; moving back collects it. */
    reset(1u);cells[2*20+6]=GAME_TILE_SOLID;cells[3*20+6]=GAME_TILE_SOLID;
    drop_item();game_adventure_save_drops(drops);
    assert(drops[0].active && drops[0].x==80 && game_adventure_quantity(0)==3u);
    tick(0u);assert(game_adventure_quantity(0)==3u);
    sprite_x=30;tick(0u);assert(game_adventure_quantity(0)==3u);
    sprite_x=60;tick(0u);assert(game_adventure_quantity(0)==4u);
    /* If live physics isn't available, the old input rectangle still works. */
    reset(1u);provide_physics=0u;
    cells[2*20+8]=GAME_TILE_SOLID;cells[3*20+8]=GAME_TILE_SOLID;
    drop_item();sprite_x=100;tick(0u);
    assert(game_adventure_quantity(0)==4u);
    puts("Stage 5.131 left/right pickup, wall-limited item, arming, fallback PASS");
    return 0;
}
