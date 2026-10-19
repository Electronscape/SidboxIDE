/* Stage 3.90: accidental walk/fall landings must not break or bounce;
 * a real jump arms a stomp, which persists through release and an optional
 * breakable's automatic bounce. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"

static int32_t x100, y100, vy100;
static uint8_t grounded, jump_held;
static game_world_player_t player;
static game_world_object_t breakable;

static void reset_world(void)
{
    x100 = 40 * 100; y100 = 56 * 100; vy100 = 0;
    grounded = 0; jump_held = 0;
    player = (game_world_player_t){0};
    player.x100 = &x100;
    player.y100 = &y100;
    player.vy100 = &vy100;
    player.on_ground = &grounded;
    player.jump_held = &jump_held;
    player.width = 16;
    player.height = 16;
    breakable = (game_world_object_t){0};
    assert(game_world_object_start(&breakable, GAME_OBJECT_BREAKABLE,
                                   0, 32, 80, 48, 8));
    breakable.break_hits_required = 2;
    breakable.break_bounce = 1;
}

static void land_on_breakable(void)
{
    y100 = 56 * 100;
    grounded = 0;
    vy100 = 300;
    game_world_objects_before(&breakable, 1, &player);
    y100 = 70 * 100;
    game_world_objects_after(&breakable, 1, &player);
}

static void deliberate_jump(void)
{
    /* The world helper sees the jump state across a physics step. */
    grounded = 1;
    vy100 = 0;
    jump_held = 0;
    y100 = 56 * 100;
    game_world_objects_before(&breakable, 1, &player);
    grounded = 0;
    vy100 = -700;
    jump_held = 1;
    game_world_objects_after(&breakable, 1, &player);
    assert(player.break_stomp_armed == 1);
    jump_held = 0; /* Release midair. A stomp must remain armed. */
}

int main(void)
{
    /* Walking from a ledge onto a breakable is a normal landing, even if
       the breakable is configured to bounce *valid* stomps. */
    reset_world();
    grounded = 1;
    land_on_breakable();
    assert(grounded == 1 && vy100 == 0);
    assert(breakable.active && breakable.break_hits_done == 0);
    assert(y100 == 64 * 100);

    /* A fall without pressing Jump is not a stomp either. */
    reset_world();
    land_on_breakable();
    assert(grounded == 1 && vy100 == 0 && breakable.break_hits_done == 0);

    /* Actual player jump, button released midair, descending collision:
       damage once and launch; automatic bounce keeps the attack armed. */
    reset_world();
    deliberate_jump();
    assert(breakable.break_hits_done == 0);
    land_on_breakable();
    assert(breakable.active && breakable.break_hits_done == 1);
    assert(grounded == 0 && vy100 == -1100 && player.break_stomp_armed);

    /* Being held against its top does NOT add extra hits. */
    game_world_objects_before(&breakable, 1, &player);
    game_world_objects_after(&breakable, 1, &player);
    assert(breakable.break_hits_done == 1);

    /* Leave the hitbox during the bounce, then fall onto it again. */
    y100 = 20 * 100;
    vy100 = -500;
    game_world_objects_before(&breakable, 1, &player);
    game_world_objects_after(&breakable, 1, &player);
    assert(!breakable.break_touching && player.break_stomp_armed);
    land_on_breakable();
    assert(breakable.break_hits_done == 2 && !breakable.active);

    /* A failed jump (button press but no upward takeoff) cannot arm a stomp. */
    reset_world();
    game_world_objects_before(&breakable, 1, &player);
    jump_held = 1;
    vy100 = 0; /* No physics takeoff occurred. */
    game_world_objects_after(&breakable, 1, &player);
    assert(!player.break_stomp_armed);
    jump_held = 0;
    land_on_breakable();
    assert(breakable.break_hits_done == 0);

    /* Touch-to-break bypasses jump intent, as requested. */
    reset_world();
    breakable.break_touch_mode = 1;
    land_on_breakable();
    assert(breakable.break_hits_done == 1);

    puts("PASS: deliberate-jump-only stomps, accidental walking/falling, bounce rearm, touch mode");
    return 0;
}
