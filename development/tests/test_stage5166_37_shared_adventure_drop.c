/* Stage 5.166.37: byte-for-byte collision behaviour for extracted world drop queries.
 * Compile with the ACTUAL tilemap.c SDK helper; never a reimplementation of it.
 */
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tilemap.h"
/* game_tile_at is intentionally internal to the tilemap runtime. */
extern uint8_t game_tile_at(const game_tilemap_t *, int32_t, int32_t);

/* Baseline: the exact routines shipped in gameadventure.rulec in Stage 5.166.36. */
static int32_t old_sweep(const game_tilemap_t *map,int32_t start_x,int32_t target_x,int32_t y)
{
    if (!map || !map->collision || !map->tile_size) return target_x;
    const int32_t max_x=(int32_t)map->width*map->tile_size-16;
    if (max_x<0) return INT32_MIN;
    if (start_x<0) start_x=0;
    if (start_x>max_x) start_x=max_x;
    if (target_x<0) target_x=0;
    if (target_x>max_x) target_x=max_x;
    if (game_tilemap_actor_blocked(map,start_x,y,16u,16u)) return INT32_MIN;
    const int32_t step=target_x>=start_x ? 1 : -1;
    int32_t clear_x=start_x;
    while (clear_x!=target_x) {
        const int32_t next_x=clear_x+step;
        if (game_tilemap_actor_blocked(map,next_x,y,16u,16u)) break;
        clear_x=next_x;
    }
    return clear_x;
}
static int32_t old_floor(const game_tilemap_t *map,int32_t x,int32_t old_y,int32_t next_y)
{
    if (!map || !map->collision || !map->tile_size) return old_y;
    const int32_t tile=map->tile_size;
    const int32_t map_bottom=(int32_t)map->height*tile;
    for (int32_t y=old_y; y<=next_y; ++y) {
        if (game_tilemap_actor_blocked(map,x,y,16u,16u))
            return y==old_y ? y : y-1;
        const int32_t feet=y+16;
        if (feet>=0 && feet%tile==0) {
            const int32_t ty=feet/tile;
            const int32_t left=x<0 ? 0 : x/tile;
            const int32_t right=(x+15)<0 ? -1 : (x+15)/tile;
            for (int32_t tx=left; tx<=right; ++tx)
                if (game_tile_at(map,tx,ty)==GAME_TILE_ONEWAY) return y;
        }
        if (feet>=map_bottom) return y;
    }
    return INT32_MAX;
}
static uint32_t seed=0xA8E5B173u;
static uint32_t rnd(void)
{
    seed ^=seed<<13; seed^=seed>>17; seed^=seed<<5;
    return seed;
}
int main(void)
{
    unsigned comparisons=0;
    if (game_tilemap_drop_floor(0,2,3,4)!=3 ||
        game_tilemap_drop_sweep(0,4,9,2)!=9) return 1;
    for (uint16_t t=8u;t<=32u;t*=2u) {
        for (uint16_t map_w=1;map_w<=8;++map_w) {
            for (uint16_t map_h=1;map_h<=8;++map_h) {
                uint8_t cells[64]={0};
                for (unsigned pattern=0;pattern<7;++pattern) {
                    for (uint16_t i=0;i<map_w*map_h;++i)
                        cells[i] = (uint8_t)(pattern==0 ? 0 :
                            pattern==1 ? 1 : pattern==2 ? 2 : (rnd()%7u));
                    game_tilemap_t map={0};
                    map.width=map_w;map.height=map_h;
                    map.tile_size=t;map.collision=cells;
                    for(unsigned n=0;n<16;++n) {
                        const int32_t sx=(int32_t)(rnd()%((uint32_t)map_w*t+16u))-8;
                        const int32_t tx=(int32_t)(rnd()%((uint32_t)map_w*t+16u))-8;
                        const int32_t x=(int32_t)(rnd()%((uint32_t)map_w*t+16u))-8;
                        const int32_t y=(int32_t)(rnd()%((uint32_t)map_h*t+16u))-8;
                        const int32_t next_y=y+(int32_t)(rnd()%22u);
                        const int32_t a=old_sweep(&map,sx,tx,y);
                        const int32_t b=game_tilemap_drop_sweep(&map,sx,tx,y);
                        const int32_t c=old_floor(&map,x,y,next_y);
                        const int32_t d=game_tilemap_drop_floor(&map,x,y,next_y);
                        if(a!=b || c!=d) {
                            fprintf(stderr,"mismatch map=%ux%u tile=%u s=(%ld,%ld,%ld) f=(%ld,%ld,%ld): sweep %ld/%ld floor %ld/%ld\n",
                                map_w,map_h,t,(long)sx,(long)tx,(long)y,(long)x,(long)y,(long)next_y,
                                (long)a,(long)b,(long)c,(long)d);
                            return 2;
                        }
                        comparisons+=2;
                    }
                }
            }
        }
    }
    printf("Stage 5.166.37 shared item-drop: %u identical collision results across 8/16/32px maps.\n", comparisons);
    return 0;
}
