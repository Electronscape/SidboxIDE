/* Stage 3.68: exact physics hitbox, sprite-origin preservation and legacy fallback.
   cc -std=c11 -Wall -Wextra -Werror -ffunction-sections -fdata-sections \
      -Iidelibs/api -Iidelibs/codehelpers/game \
      development/tests/test_stage368_player_hitbox.c \
      -Wl,--gc-sections -o /tmp/gg368_hitbox && /tmp/gg368_hitbox */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/tilemap.c"
#define MW 24
#define MH 24
static uint8_t collision[MW * MH];
static uint16_t refs[MW * MH];
static game_tile_shape_t shape = {2, 2, 0, 2, 2, 1};
static const game_tile_shape_point_t points[] = {{0,0},{16,16}};
static game_tile_shape_instance_t inst[8];
static game_tilemap_t m;
static void setup(void) {
    memset(&m, 0, sizeof(m)); memset(collision,0,sizeof(collision));
    memset(refs,0,sizeof(refs));
    m.collision=collision; m.shape_refs=refs; m.tile_size=8;
    m.width=MW; m.height=MH; m.shape_defs=&shape; m.shape_count=1;
    m.shape_points=points; m.shape_instances=inst; m.shape_instance_count=8;
    for (int i=0;i<8;i++) {
        int sx=4+2*i, sy=4+2*i;
        inst[i]=(game_tile_shape_instance_t){sx,sy,0,0};
        for(int dy=0;dy<2;dy++) for(int dx=0;dx<2;dx++) {
            int off=(sy+dy)*MW+sx+dx;
            collision[off]=GAME_TILE_POINT_SLOPE; refs[off]=(uint16_t)(i+1);
        }
    }
}
static void motion(int spriteSize, int bx, int by, int boxW, int boxH,
                   int expectedX, int expectedY) {
    gfxbob_t bob = {0}; bob.width=(uint16_t)spriteSize; bob.height=(uint16_t)spriteSize;
    bob.handle=BLIT_HANDLE_TOP_LEFT; bob.scale=100;
    game_tile_player_t p={0};
    assert(game_tile_player_start(&p,&m,&bob));
    // The collision box begins at world (32,0) with its feet at world y32.
    // For all sprite sizes, run the same physical box on the same slope.
    p.x100=(32-bx)*100; p.y100=(0-by)*100;
    if (spriteSize != 32 || bx || by || boxW !=32 || boxH !=32)
        assert(game_tile_player_set_hitbox(&p,bx,by,boxW,boxH));
    assert((p.x100/100+p.hitbox_x)==32);
    assert((p.y100/100+p.hitbox_y)==0);
    p.on_ground=1;
    p.walk_speed=3; p.gravity=35; p.max_fall_speed=9; p.jump_speed=7;
    p.force_drag_percent=12;
    for (int i=0;i<40;i++) game_tile_player_run(&p,0,1);
    fprintf(stderr,"Sprite %d hit (%d,%d,%d,%d): x=%ld y=%ld expect=%d %d, vx=%ld\n",spriteSize,bx,by,boxW,boxH,(long)(p.x100/100+p.hitbox_x),(long)(p.y100/100+p.hitbox_y),expectedX,expectedY,(long)p.force_vx100);
    assert(p.x100/100+p.hitbox_x==expectedX);
    assert(p.y100/100+p.hitbox_y==expectedY);
    // Rendering retains the visible sprite origin, independent of the box.
    game_tile_player_screen(&p, 11, 13);
    assert(bob.drawx==(p.x100/100-11));
    assert(bob.drawy==(p.y100/100-13));
    // Invalid rectangle must not corrupt previously working physics.
    uint16_t oldW=p.hitbox_w,oldX=p.hitbox_x;
    assert(!game_tile_player_set_hitbox(&p, (uint16_t)spriteSize-1, 0, 32, 32));
    assert(p.hitbox_w==oldW && p.hitbox_x==oldX);
    // Explicitly clearing the box restores full-sprite dimensions.
    assert(game_tile_player_set_hitbox(&p,0,0,0,0));
    assert(p.hitbox_w==0 && p.hitbox_h==0 && p.hitbox_x==0 && p.hitbox_y==0);
}
int main(void) {
    setup();
    gfxbob_t bob={0};bob.width=64;bob.height=64;bob.handle=BLIT_HANDLE_TOP_LEFT;bob.scale=100;
    game_tile_player_t p={0};
    assert(game_tile_player_start(&p,&m,&bob));
    assert(!p.hitbox_w && !p.hitbox_h && !p.hitbox_x && !p.hitbox_y);
    // legacy: even without animation, a 64px BOB gets 64px collision.
    assert(game_tile_player_set_hitbox(&p,16,12,32,52));
    assert(p.hitbox_w==32 && p.hitbox_h==52);
    assert(!game_tile_player_set_hitbox(&p,34,12,32,52));
    // identical 32px collider path regardless of the graphical cell size.
    game_tile_player_t reference={0};
    gfxbob_t r={0};r.width=32;r.height=32;r.handle=BLIT_HANDLE_TOP_LEFT;r.scale=100;
    assert(game_tile_player_start(&reference,&m,&r));
    reference.x100=3200;reference.y100=0;reference.on_ground=1;
    reference.walk_speed=3;reference.gravity=35;reference.max_fall_speed=9;
    reference.jump_speed=7;reference.force_drag_percent=12;
    for(int i=0;i<40;i++)game_tile_player_run(&reference,0,1);
    const int rx=reference.x100/100, ry=reference.y100/100;
    assert(rx>100); // regression for Stage 3.67 slippery slope handoff.
    fprintf(stderr,"ref x=%d y=%d vx=%ld\n",rx,ry,(long)reference.force_vx100);
    motion(32,0,0,32,32,rx,ry);
    motion(48,8,16,32,32,rx,ry);
    motion(64,16,32,32,32,rx,ry);
    /* An actual 64px sprite with a 32x52 physical box slides over the
       same connected small slope stamps without the old handoff stall. */
    gfxbob_t big={0}; big.width=64; big.height=64;
    game_tile_player_t custom={0}; custom.map=&m; custom.sprite=&big;
    custom.walk_speed=3; custom.jump_speed=7; custom.gravity=35;
    custom.max_fall_speed=9; custom.force_drag_percent=12;
    custom.x100=1600; custom.y100=-3200; // hitbox starts (32,-20), feet 32.
    assert(game_tile_player_set_hitbox(&custom,16,12,32,52));
    custom.on_ground=1;
    for(int i=0;i<40;i++) game_tile_player_run(&custom,0,1);
    assert(custom.x100/100 + custom.hitbox_x > 100);

    /* The loop track uses the box centre/feet, not the decorative sprite. */
    game_tile_loop_t loop={100,100,40,100};
    m.loops=&loop; m.loop_count=1;
    gfxbob_t aBob={0}, bBob={0};
    aBob.width=32;aBob.height=32;bBob.width=64;bBob.height=64;
    game_tile_player_t a={0},b={0};
    a.map=b.map=&m;a.sprite=&aBob;b.sprite=&bBob;
    a.gravity=b.gravity=35;
    a.x100=8400;a.y100=10800; // physical centre=100, feet=140
    b.x100=6800;b.y100=7600; // sprite origin shifted by (16,32)
    assert(game_tile_player_set_hitbox(&b,16,32,32,32));
    a.force_vx100=b.force_vx100=500;
    a.on_ground=b.on_ground=1;
    assert(cg_loop_try_attach(&a,32,32));
    assert(cg_loop_try_attach(&b,32,32));
    assert(cg_loop_tick(&a,0,32,32) == cg_loop_tick(&b,0,32,32));
    assert(a.x100 == b.x100 + b.hitbox_x*100);
    assert(a.y100 == b.y100 + b.hitbox_y*100);
    m.loops=0; m.loop_count=0;

    printf("PASS: 32 / 48 / 64px sprites follow the same 32px physics path; full-size fallback, offsets, render position and validation.\n");
    return 0;
}
