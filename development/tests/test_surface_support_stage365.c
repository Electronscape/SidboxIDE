/* Stage 3.65: a wide player's landing height must match the passive
 * contact test even on a steep slope/Bezier segment.  A descending
 * slope's DOWNHILL end must not falsely disable low damping.
 *
 * gcc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
 *     -Iidelibs/api -Iidelibs/codehelpers/game \
 *     development/tests/test_surface_support_stage365.c \
 *     -Wl,--gc-sections -o /tmp/gg_surface_support && /tmp/gg_surface_support
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

static uint8_t tiles[16 * 8];
static uint16_t refs[16 * 8];
static game_tile_shape_t shape;
static game_tile_shape_point_t pts[3];
static game_tile_shape_instance_t place;
static game_tilemap_t m;

static void ramp(uint8_t flipped, uint8_t damping)
{
    memset(tiles, 0, sizeof tiles);
    memset(refs, 0, sizeof refs);
    memset(&m, 0, sizeof m);
    shape = (game_tile_shape_t){8, 6, 0, 2, damping, 1};
    pts[0] = (game_tile_shape_point_t){0, 8};
    pts[1] = (game_tile_shape_point_t){63, 40};
    place = (game_tile_shape_instance_t){2, 0, 0, flipped};
    m.tile_size = 8; m.width = 16; m.height = 8;
    m.collision = tiles; m.shape_refs = refs;
    m.shape_defs = &shape; m.shape_count = 1;
    m.shape_points = pts; m.shape_instances = &place;
    m.shape_instance_count = 1;
    for (int y = 0; y < 6; ++y) for (int x = 2; x < 10; ++x) {
        tiles[y * 16 + x] = GAME_TILE_POINT_SLOPE;
        refs[y * 16 + x] = 1;
    }
}

static void test_wide_player(uint8_t flipped)
{
    ramp(flipped, 0);
    int32_t vx = 0;
    uint8_t drag = 99;
    /* Start 1px into the uphill tip: contact occurs at x16 or x79.
     * The 20px feet cover a >9px height difference along this ramp. */
    const int32_t x = flipped ? 61 : 16;
    const int32_t feet = 8;
    assert(cg_passive_shape_surface(&m, x, feet, 20, 35, &vx, &drag, 0));
    assert(drag == 0);
    assert(flipped ? vx < 0 : vx > 0);
    gfxbob_t bob = {0}; bob.width = 20; bob.height = 4;
    game_tile_player_t p = {0};
    p.map = &m; p.sprite = &bob; p.x100 = x * 100;
    p.y100 = (feet - bob.height) * 100;
    p.gravity = 35; p.walk_speed = 3; p.jump_speed = 7;
    p.max_fall_speed = 9; p.force_drag_percent = 12; p.on_ground = 1;
    game_tile_player_run(&p, 0, 1);
    assert(flipped ? p.force_vx100 < 0 : p.force_vx100 > 0);
    /* Persist long enough to move without joystick input. */
    for (int n = 0; n < 28; ++n) game_tile_player_run(&p, 0, 1);
    printf("wide%s: x=%ld force=%ld grounded=%u\n", flipped ? " mirrored" : "",
           (long)(p.x100 / 100), (long)p.force_vx100, p.on_ground);
    assert(flipped ? p.x100 < x * 100 : p.x100 > x * 100);
}

static void test_bowl_segment(uint8_t flipped)
{
    ramp(flipped, 0);
    shape.width = 8; shape.height = 4; shape.point_count = 3;
    pts[0] = (game_tile_shape_point_t){0, 8};
    pts[1] = (game_tile_shape_point_t){32, 24};
    pts[2] = (game_tile_shape_point_t){63, 8};
    int32_t force = 0; uint8_t drag = 50;
    const int32_t x = flipped ? 60 : 16;
    assert(cg_passive_shape_surface(&m, x, 8, 20, 35, &force, &drag, 0));
    assert(drag == 0);
    assert(flipped ? force < 0 : force > 0);
    /* A sticky surface on the same geometry must report its own damping. */
    shape.damping_percent = 100;
    drag = 0;
    assert(cg_passive_shape_surface(&m, x, 8, 20, 35, &force, &drag, 0));
    assert(drag == 100);
    shape.surface_flags = 0;
    assert(!cg_passive_shape_surface(&m, x, 8, 20, 35, &force, &drag, 0));
}

/* The old per-tile 'nearest contact' could select the uphill slope on the
 * OTHER side of a Bezier bowl, despite the foot centre already being past
 * the bottom.  This pushed the actor the wrong way.  The runtime full-foot
 * landing check is still the reference for the contact Y. */
static void test_bowl_tangent_at_centre(void)
{
    static uint8_t collision[48 * 16];
    static uint16_t shape_refs[48 * 16];
    const game_tile_shape_point_t curve[] = {
        {0, 8}, {32, 48}, {64, 56}, {96, 48}, {127, 8}
    };
    const game_tile_shape_t def = {16, 8, 0, 5, 0, 1};
    const game_tile_shape_instance_t instance = {4, 0, 0, 0};
    game_tilemap_t b = {0};
    b.width = 48; b.height = 16; b.tile_size = 8;
    b.collision = collision; b.shape_refs = shape_refs;
    b.shape_defs = &def; b.shape_points = curve;
    b.shape_instances = &instance; b.shape_count = 1;
    b.shape_instance_count = 1;
    for (int y = 0; y < 8; ++y) for (int x = 4; x < 20; ++x) {
        collision[y * 48 + x] = GAME_TILE_POINT_SLOPE;
        shape_refs[y * 48 + x] = 1;
    }
    /* 20px-wide player, foot centre at x97: right of bowl bottom (x96).
     * Local slope therefore heads downhill to the LEFT (negative force).
     * The legacy algorithm returned +8 here and accelerated the wrong way. */
    const int32_t x = 88;
    const int32_t feet = tile_floor(&b, x, 20, 0, 100);
    assert(feet == 54);
    int32_t accel = 0;
    uint8_t damping = 99;
    assert(cg_passive_shape_surface(&b, x, feet, 20, 35, &accel, &damping, 0));
    assert(accel < 0 && damping == 0);
}

int main(void)
{
    test_wide_player(0);
    test_wide_player(1);
    test_bowl_segment(0);
    test_bowl_segment(1);
    test_bowl_tangent_at_centre();
    puts("Stage 3.65 slope support, wide foot, mirrored bowl, damping: PASS");
    return 0;
}
