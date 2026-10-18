/* Host-side regression of the real compiled slope-contact calculation.
 * Build: gcc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections
 *        -Iidelibs/api -Iidelibs/codehelpers/game
 *        development/tests/test_surface_physics_stage360.c -Wl,--gc-sections -o /tmp/cg_surface_test
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"

_Static_assert(sizeof(game_tile_shape_t) == 8, "shape descriptor must remain 8 bytes");

static void test_shape(int ay, int by, int mirror, int useSurface, int expectedSign)
{
    uint8_t collision[16*8] = {0};
    uint16_t refs[16*8] = {0};
    game_tile_shape_t def = {4, 4, 0, 2, 2, 1};
    game_tile_shape_point_t points[] = {{0, (uint16_t)ay}, {32, (uint16_t)by}};
    game_tile_shape_instance_t inst = {0, 0, 0, (uint8_t)mirror};
    game_tilemap_t m = {0};
    m.width=16; m.height=8; m.tile_size=8;
    m.collision = collision; m.shape_refs=refs;
    m.shape_defs=&def; m.shape_points=points;
    m.shape_instances=&inst; m.shape_count=1; m.shape_instance_count=1;
    for (int y=0;y<4;y++) for (int x=0;x<4;x++) {
        collision[y*16+x] = GAME_TILE_POINT_SLOPE;
        refs[y*16+x] = 1;
    }
    if (!useSurface) def.surface_flags=0;
    int32_t feet = custom_surface(&m, 0, 0, 0, 7);
    uint8_t damp = 50;
    int32_t force=0;
    int found=cg_passive_shape_surface(&m,0,feet,8,35,&force,&damp, 0);
    assert(found == useSurface);
    if (!useSurface) { assert(force==0 && damp==50); return; }
    assert(damp == 2);
    assert((force>0)-(force<0) == expectedSign);
    damp=50; force=0;
    /* A player far above the ramp should not be affected by a nearby shape. */
    assert(!cg_passive_shape_surface(&m,0,feet-5,8,35,&force,&damp, 0));
    assert(force==0 && damp==50);
}

int main(void)
{
    test_shape(8,24,0,1, 1); /* downhill right */
    test_shape(8,24,1,1,-1); /* mirrored downhill left */
    test_shape(24,8,0,1,-1); /* downhill left */
    test_shape(24,8,1,1, 1); /* mirrored downhill right */
    test_shape(16,16,0,1,0); /* no acceleration on flats */
    test_shape(8,24,0,0,0); /* disabled is inert */
    puts("Stage 3.60 contact projection: all 6 cases passed");
    return 0;
}
