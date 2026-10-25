/* Stub interfaces match the public tilemap API used by generated Adventure. */
#include <stdint.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#define GAME_TILE_ONEWAY 2u
#define GAME_TILE_SOLID 1u
typedef struct { const uint8_t *collision; uint16_t width,height,tile_size; } game_tilemap_t;
static uint8_t cells[16*16];
static game_tilemap_t world={cells,16,16,16};
static game_tilemap_t *active=&world;
static void *gameworlds_map(void) {return active;}
static uint8_t game_tile_at(const game_tilemap_t *map,int32_t tx,int32_t ty)
{
    if (!map || tx<0 || ty<0 || tx>=map->width || ty>=map->height) return 0;
    return map->collision[ty*map->width+tx];
}
static uint8_t game_tilemap_actor_blocked(const game_tilemap_t *map,
                                         int32_t x,int32_t y,uint16_t w,uint16_t h)
{
    if (!map || !map->collision) return 0;
    for (int32_t yy=y;yy<y+h;++yy)
        for (int32_t xx=x;xx<x+w;++xx)
            if (xx>=0 && yy>=0 &&
                game_tile_at(map,xx/(int32_t)map->tile_size,yy/(int32_t)map->tile_size)==GAME_TILE_SOLID)
                return 1;
    return 0;
}
/* Paste the actual callback from generated rulec below, rather than duplicating it. */
#include "stage5128_generated_floor.inc"
int main(void)
{
    /* Item x=30 spans tiles 1 and 2. Tile 2 at row 3 catches its right edge. */
    cells[3*16+2]=GAME_TILE_SOLID;
    assert(gameadventure_drop_floor(30,5,90)==32);
    cells[3*16+2]=0;
    cells[3*16+2]=GAME_TILE_ONEWAY;
    assert(gameadventure_drop_floor(30,5,90)==32);
    cells[3*16+2]=0;
    assert(gameadventure_drop_floor(30,5,45)==INT32_MAX);
    active=0;
    assert(gameadventure_drop_floor(30,5,45)==5);
    active=&world;
    /* Falling off a world with no solid floor stops at its bottom edge. */
    assert(gameadventure_drop_floor(30,232,260)==240);
    puts("Stage 5.128 generated collision callback: solids, one-way, map edge PASS");
    return 0;
}
