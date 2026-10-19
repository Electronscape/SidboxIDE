/* Stage 3.72 loop contact: 32/48/64 sprite atlases, rectangular hitboxes.
 * From IDE root:
 * cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *    -Iidelibs/api -Iidelibs/codehelpers/game \
 *    development/tests/test_stage372_loop_entry.c \
 *    -Wl,--gc-sections -o /tmp/gg372_loop && /tmp/gg372_loop
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

#define MW 64
#define MH 64
static uint8_t tiles[MW * MH];
static game_tile_loop_t loop = {100,100,40,100,0,0, 0};
static game_tilemap_t m;

static void check(int sprite_w, int sprite_h, int bx, int by, int w, int h)
{
    gfxbob_t bob = {0};
    game_tile_player_t p = {0};
    bob.width = (uint16_t)sprite_w;
    bob.height = (uint16_t)sprite_h;
    bob.handle = BLIT_HANDLE_TOP_LEFT;
    bob.scale = 100;
    assert(game_tile_player_start(&p, &m, &bob));
    if (bx || by || w != sprite_w || h != sprite_h)
        assert(game_tile_player_set_hitbox(&p, (uint16_t)bx,
                (uint16_t)by, (uint16_t)w, (uint16_t)h));
    p.x100 = (loop.center_x - w/2 - bx) * 100;
    p.y100 = (loop.center_y + loop.radius - h - by) * 100;
    p.slide_velocity100 = 500;
    p.force_drag_percent = 0;
    p.gravity = 0;
    p.on_ground = 1;
    const int32_t expected_feet100 = (loop.center_y + loop.radius)*100;
    assert(p.y100 + (p.hitbox_y + h)*100 == expected_feet100);
    assert(cg_loop_try_attach(&p,w,h));
    assert(p.loop_index == 1);
    const int32_t initial_worldY100 = p.y100;
    assert(cg_loop_tick(&p,0,w,h) == 1);
    /* First loop tick must not teleport rectangular hitbox feet downwards
       by 3/8/10px simply because the collider is narrower than tall. */
    const int32_t new_feet100 = p.y100 + (p.hitbox_y + h)*100;
    assert(new_feet100 <= expected_feet100 + 100);
    assert(new_feet100 >= expected_feet100 - 100);
    const int32_t ns = cg_loop_sin(p.loop_phase);
    const int32_t nc = cg_loop_sin(p.loop_phase + 16384);
    const int32_t footX100 = loop.center_x*100 +
        (int32_t)((int64_t)loop.radius*100*ns / 16384);
    const int32_t footY100 = loop.center_y*100 +
        (int32_t)((int64_t)loop.radius*100*nc / 16384);
    assert(p.x100 + bx*100 == footX100 - w*50 -
        (int32_t)((int64_t)w*50*ns/16384));
    assert(p.y100 + by*100 == footY100 - h*50 -
        (int32_t)((int64_t)h*50*nc/16384));
    printf("%dx%d sprite, hitbox=(%d,%d,%dx%d) entry jump %.2f px, loop feet=%.2f\n",
        sprite_w,sprite_h,bx,by,w,h,
        (p.y100-initial_worldY100)/100.0,(new_feet100)/100.0);

    /* After one full revolution, the exit snap agrees with entry height. */
    p.loop_phase = 65500;
    p.loop_speed100 = 500;
    assert(cg_loop_tick(&p,0,w,h) == 1);
    assert(p.loop_index == 0);
    assert(p.y100 + (by+h)*100 == expected_feet100);
}

int main(void)
{
    memset(&m,0,sizeof(m));
    m.width=MW; m.height=MH; m.tile_size=8;
    m.collision=tiles; m.loops=&loop; m.loop_count=1;
    check(32,32,0,0,32,32);      /* Original square legacy behaviour */
    check(64,64,3,0,26,32);      /* User's saved animation hitbox */
    check(64,64,8,8,16,32);      /* Old code sank 8 pixels */
    check(64,64,16,12,32,52);    /* Tall torso hitbox */
    check(64,64,0,0,64,64);      /* New full-size sprite fallback */
    puts("PASS: loop entry/exit consistent for square and rectangular hitboxes");
    return 0;
}
