/* Stage 3.66: real player solver, gentle slopes, 2% surface damping,
 * ledge entry, mirrored direction, and 100%-sticky compatibility.
 * Compiles the same tilemap.c shipped with the game, not a fake solver.
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

static uint8_t collision[24 * 12];
static uint16_t refs[24 * 12];
static game_tile_shape_t slope;
static game_tile_shape_point_t pts[2];
static game_tile_shape_instance_t place;
static game_tilemap_t m;

static void setup(uint16_t delta_y, uint8_t damping, uint8_t mirrored, uint8_t ledge)
{
    memset(collision, 0, sizeof collision);
    memset(refs, 0, sizeof refs);
    memset(&m, 0, sizeof m);
    slope = (game_tile_shape_t){8, 8, 0, 2, damping, 1};
    pts[0] = (game_tile_shape_point_t){0, 16};
    pts[1] = (game_tile_shape_point_t){63, (uint16_t)(16 + delta_y)};
    place = (game_tile_shape_instance_t){4, 0, 0, mirrored};
    m.width = 24; m.height = 12; m.tile_size = 8;
    m.collision = collision; m.shape_refs = refs;
    m.shape_defs = &slope; m.shape_count = 1;
    m.shape_points = pts; m.shape_instances = &place;
    m.shape_instance_count = 1;
    for (int ty = 0; ty < 8; ++ty)
        for (int tx = 4; tx < 12; ++tx) {
            collision[ty * 24 + tx] = GAME_TILE_POINT_SLOPE;
            refs[ty * 24 + tx] = 1;
        }
    if (ledge)
        for (int tx = mirrored ? 12 : 0; tx < (mirrored ? 16 : 4); ++tx)
            collision[2 * 24 + tx] = GAME_TILE_SOLID;
}

static void init_player(game_tile_player_t *p, gfxbob_t *bob, int x, int width)
{
    memset(p, 0, sizeof *p);
    memset(bob, 0, sizeof *bob);
    bob->width = (uint16_t)width;
    bob->height = 8;
    p->map = &m; p->sprite = bob;
    p->gravity = 35; p->walk_speed = 2;
    p->max_fall_speed = 9; p->jump_speed = 7;
    p->force_drag_percent = 12;
    p->x100 = x * 100;
    p->y100 = 8 * 100;
    p->on_ground = 1;
}

static void run(game_tile_player_t *p, int count, uint8_t buttons)
{
    for (int f = 0; f < count; ++f)
        game_tile_player_run(p, buttons, 1);
}

static void test_nearly_horizontal_slides(void)
{
    gfxbob_t bob;
    game_tile_player_t p;
    setup(1, 2, 0, 0); /* 1px descent across 64px, 2% drag */
    init_player(&p, &bob, 40, 8);
    run(&p, 120, 0);
    printf("gentle 2%% slide: start x=40, end x=%ld, speed=%ld/100\n",
           (long)(p.x100 / 100), (long)p.force_vx100);
    assert(p.x100 >= 55 * 100);
    assert(p.on_ground);

    setup(1, 100, 0, 0);
    init_player(&p, &bob, 40, 8);
    run(&p, 120, 0);
    assert(p.x100 == 4000 && p.force_vx100 == 0);

    setup(1, 2, 0, 0);
    slope.surface_flags = 0; /* opt-in remains opt-in */
    init_player(&p, &bob, 40, 8);
    run(&p, 120, 0);
    assert(p.x100 == 4000);
}

static void test_flat_ledge_does_not_tug(void)
{
    gfxbob_t bob;
    game_tile_player_t p;
    setup(32, 2, 0, 1);
    init_player(&p, &bob, 28, 8); /* 4 of 8 feet over slope */
    run(&p, 80, 0);
    assert(p.x100 == 2800 && p.force_vx100 == 0 && p.on_ground);
    p.x100 = 31 * 100; /* only 1px still supported by flat collision */
    run(&p, 80, 0);
    assert(p.x100 == 3100 && p.force_vx100 == 0 && p.on_ground);

    init_player(&p, &bob, 24, 8);
    run(&p, 5, BTN_RIGHT); /* walk completely onto slope */
    assert(p.x100 >= 32 * 100);
    const int32_t release_x = p.x100;
    run(&p, 35, 0);
    printf("ledge entry: release=%ld end=%ld\n", (long)(release_x/100),
           (long)(p.x100/100));
    assert(p.x100 > release_x + 10 * 100);
}

static void test_mirrored_ledge(void)
{
    gfxbob_t bob;
    game_tile_player_t p;
    setup(16, 2, 1, 1);
    init_player(&p, &bob, 92, 8); /* feet over right ledge */
    run(&p, 50, 0);
    assert(p.x100 == 9200 && p.force_vx100 == 0);
    init_player(&p, &bob, 88, 8); /* wholly on slope */
    run(&p, 90, 0);
    assert(p.x100 < 88 * 100);
}

static void test_wide_foot(void)
{
    gfxbob_t bob;
    game_tile_player_t p;
    setup(16, 2, 0, 0);
    init_player(&p, &bob, 40, 20);
    run(&p, 60, 0);
    assert(p.x100 > 40 * 100);
}

int main(void)
{
    test_nearly_horizontal_slides();
    test_flat_ledge_does_not_tug();
    test_mirrored_ledge();
    test_wide_foot();
    puts("Stage 3.66 downhill / ledge contact / damping: PASS");
    return 0;
}
