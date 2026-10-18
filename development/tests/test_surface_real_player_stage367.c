/* Stage 3.67: reproduction of adjacent 16px descending stamps supporting
 * a 32px player (same dimensions/geometry as the reported SIDBOX game).
 * Stage 3.66 went 4 pixels and stopped.  The stamp-to-stamp handoff must
 * preserve slope gravity, and a single 16px stamp must finish sliding.
 * Run with gcc -std=c11 -Wall -Wextra -Werror -ffunction-sections \
 *   -fdata-sections -Iidelibs/api -Iidelibs/codehelpers/game \
 *   development/tests/test_surface_real_player_stage367.c \
 *   -Wl,--gc-sections -o /tmp/gg367 && /tmp/gg367
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

#define MW 24
#define MH 24
static uint8_t collision[MW * MH];
static uint16_t refs[MW * MH];
static game_tile_shape_t shape = {2, 2, 0, 2, 2, 1};
static game_tile_shape_point_t points[] = {{0,0},{16,16}};
static game_tile_shape_instance_t instances[10];
static game_tilemap_t map;

static void setup(int count)
{
    memset(collision, 0, sizeof collision);
    memset(refs, 0, sizeof refs);
    memset(&map, 0, sizeof map);
    map.collision=collision; map.shape_refs=refs;
    map.tile_size=8; map.width=MW; map.height=MH;
    map.shape_defs=&shape; map.shape_count=1;
    map.shape_points=points;
    map.shape_instances=instances; map.shape_instance_count=count;
    for(int i=0;i<count;i++) {
        const int start_x=4+2*i;
        const int start_y=4+2*i;
        instances[i]=(game_tile_shape_instance_t){start_x,start_y,0,0};
        for(int dy=0;dy<2;dy++) for(int dx=0;dx<2;dx++) {
            int index=(start_y+dy)*MW+start_x+dx;
            collision[index]=GAME_TILE_POINT_SLOPE;
            refs[index]=(uint16_t)(i+1);
        }
    }
}

static void run(int count, int frames, int minimum_x)
{
    setup(count);
    gfxbob_t bob={0}; bob.width=32; bob.height=32;
    game_tile_player_t player={0};
    player.map=&map;player.sprite=&bob;
    player.walk_speed=3;player.jump_speed=7;
    player.gravity=35;player.max_fall_speed=9;
    player.force_drag_percent=12;
    player.x100=32*100;
    player.y100=0; /* feet at y32 */
    player.on_ground=1;
    for(int i=0;i<frames;i++) game_tile_player_run(&player, 0, 1);
    printf("%d x16 slopes, 32px player: %ld -> %ld in %d frames\n",
           count, 32L, (long)(player.x100/100), frames);
    assert(player.x100/100>=minimum_x);
}

int main(void)
{
    run(8, 40, 115); /* continuous downhill from real game: no joins stall */
    run(1, 20, 46); /* even one 16px slope must finish sliding */
    puts("Stage 3.67 wide player and adjacent slope handoff: PASS");
    return 0;
}
