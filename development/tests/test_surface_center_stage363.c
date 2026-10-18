/* Stage 3.63 regression: the centre of the player's feet controls passive
 * surface entry, even if the 8px-wide shape is narrower than the player.
 * Build: gcc -std=c11 -Wall -Wextra -Werror -ffunction-sections \
 *   -fdata-sections -Iidelibs/api -Iidelibs/codehelpers/game \
 *   development/tests/test_surface_center_stage363.c \
 *   -Wl,--gc-sections -o /tmp/test_surface_center_stage363
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

static uint8_t collision[16 * 8];
static uint16_t refs[16 * 8];
static game_tile_shape_t shape;
static game_tile_shape_point_t points[2];
static game_tile_shape_instance_t instance;
static game_tilemap_t map;

static void setup(uint8_t mirror)
{
    memset(collision, 0, sizeof(collision));
    memset(refs, 0, sizeof(refs));
    memset(&map, 0, sizeof(map));
    shape = (game_tile_shape_t){1, 2, 0, 2, 0, 1}; /* 8px, frictionless */
    points[0] = (game_tile_shape_point_t){0, 0};
    points[1] = (game_tile_shape_point_t){7, 4};
    instance = (game_tile_shape_instance_t){4, 1, 0, mirror};
    map.width = 16; map.height = 8; map.tile_size = 8;
    map.collision = collision; map.shape_refs = refs;
    map.shape_defs = &shape; map.shape_points = points;
    map.shape_instances = &instance;
    map.shape_instance_count = 1; map.shape_count = 1;
    collision[1 * 16 + 4] = GAME_TILE_POINT_SLOPE;
    collision[2 * 16 + 4] = GAME_TILE_POINT_SLOPE;
    refs[1 * 16 + 4] = 1;
    refs[2 * 16 + 4] = 1;
}

static void assert_contact(int32_t x, int32_t feet, int32_t width,
                           uint8_t expected, int sign)
{
    int32_t force = 999;
    uint8_t damping = 77;
    const uint8_t found = cg_passive_shape_surface(&map, x, feet, width,
                                                   35, &force, &damping, 0);
    if (found != expected)
        fprintf(stderr, "x=%ld feet=%ld width=%ld mirror=%u actual=%u expected=%u\n",
                (long)x, (long)feet, (long)width, instance.flags, found, expected);
    assert(found == expected);
    if (found) {
        assert(damping == 0);
        assert((force > 0) - (force < 0) == sign);
    } else {
        assert(force == 999 && damping == 77);
    }
}

static void test_narrow_stamp_vs_wide_player(void)
{
    setup(0);
    /* Player width 20: a single 8px stamp CANNOT overlap half the feet.
       But the centre pixels 35/36 stand on the actual ramp. */
    assert_contact(26, 8, 20, 1, +1);
    assert_contact(19, 8, 20, 0, 0); /* only toes over slope, centre off */
    assert_contact(39, 12, 20, 0, 0); /* only heels over slope, centre off */
    /* Still obey left/right cliff-edge rules for 8px collision boxes. */
    assert_contact(25, 8, 8, 0, 0); /* 1px overlap */
    assert_contact(27, 8, 8, 0, 0); /* 3px overlap */
    assert_contact(28, 8, 8, 1, +1); /* 4px overlap */
    assert_contact(36, 12, 8, 1, +1); /* 4px at right edge */
    assert_contact(37, 12, 8, 0, 0); /* 3px at right edge */

    setup(1);
    assert_contact(26, 8, 20, 1, -1);
    assert_contact(28, 12, 8, 1, -1);
    assert_contact(36, 8, 8, 1, -1);
}

static void test_real_player_motion(void)
{
    setup(0);
    gfxbob_t sprite = {0};
    sprite.width = 20; sprite.height = 4;
    game_tile_player_t p = {0};
    p.map = &map; p.sprite = &sprite;
    p.gravity = 35; p.walk_speed = 3; p.max_fall_speed = 9;
    p.jump_speed = 7; p.force_drag_percent = 12;
    p.x100 = 26 * 100; p.y100 = 4 * 100; p.on_ground = 1;
    game_tile_player_run(&p, 0, 1);
    assert(p.force_vx100 > 0); /* Sliding starts without joystick */
}

int main(void)
{
    test_narrow_stamp_vs_wide_player();
    test_real_player_motion();
    puts("Stage 3.63 centre-foot contact and narrow-stamp sliding: PASS");
    return 0;
}
