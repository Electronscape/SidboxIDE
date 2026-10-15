#include "platformer.h"

uint8_t start_platformer(game_platformer_t *physics, gfxbob_t *sprite,
                         const game_platform_t *platforms,
                         uint16_t platform_count)
{
    if (!physics || !sprite || !sprite->imgdat || !sprite->width ||
        !sprite->height || sprite->scale != 100u ||
        sprite->handle != BLIT_HANDLE_TOP_LEFT ||
        (platform_count && !platforms)) return 0;

    physics->sprite = sprite;
    physics->platforms = platforms;
    physics->platform_count = platform_count;
    physics->walk_speed = 3;
    physics->jump_speed = 7;
    physics->gravity = 35;
    physics->max_fall_speed = 9;
    reset_platformer(physics, sprite->drawx, sprite->drawy);
    return 1;
}

void reset_platformer(game_platformer_t *physics, int16_t x, int16_t y)
{
    if (!physics || !physics->sprite) return;
    physics->x100 = (int32_t)x * 100;
    physics->y100 = (int32_t)y * 100;
    physics->vy100 = 0;
    physics->jump_held = 0;
    physics->on_ground = 0;
    physics->sprite->drawx = x;
    physics->sprite->drawy = y;

    /* Recognise a player already standing on a platform at the start. */
    for (uint16_t i = 0; i < physics->platform_count; ++i) {
        const game_platform_t *p = &physics->platforms[i];
        if (!p->width || !p->height) continue;
        if ((int32_t)y + physics->sprite->height == p->y &&
            (int32_t)x < (int32_t)p->x + p->width &&
            (int32_t)x + physics->sprite->width > p->x) {
            physics->on_ground = 1;
            break;
        }
    }
}

void run_platformer(game_platformer_t *physics, uint8_t joypad,
                    uint16_t frame_step)
{
    if (!physics || !physics->sprite || !frame_step) return;
    gfxbob_t *sprite = physics->sprite;
    const int32_t w = sprite->width;
    const int32_t h = sprite->height;
    const uint8_t jump = (joypad & (BTN_FIRE | BTN_UP)) != 0;

    /* Don't spend ages catching up after a long pause. */
    if (frame_step > 60u) frame_step = 60u;

    for (uint16_t frame = 0; frame < frame_step; ++frame) {
        if (jump && !physics->jump_held && physics->on_ground) {
            physics->vy100 = -(int32_t)physics->jump_speed * 100;
            physics->on_ground = 0;
        }
        physics->jump_held = jump;

        /* Walk horizontally. Left and right together cancel each other. */
        const int32_t left = (joypad & BTN_LEFT) != 0;
        const int32_t right = (joypad & BTN_RIGHT) != 0;
        const int32_t walk = physics->walk_speed > 0 ? physics->walk_speed : 0;
        const int32_t dx100 = (right - left) * walk * 100;
        const int32_t old_x = physics->x100 / 100;
        int32_t proposed_x100 = physics->x100 + dx100;
        int32_t new_x = proposed_x100 / 100;
        const int32_t old_y = physics->y100 / 100;

        /* Prevent moving through the sides of SOLID rectangles. */
        for (uint16_t i = 0; i < physics->platform_count; ++i) {
            const game_platform_t *p = &physics->platforms[i];
            if (!p->width || !p->height || p->type != GAME_PLATFORM_SOLID) continue;
            if (old_y + h <= p->y || old_y >= (int32_t)p->y + p->height) continue;

            if (dx100 > 0 && old_x + w <= p->x && new_x + w > p->x) {
                proposed_x100 = ((int32_t)p->x - w) * 100;
                new_x = proposed_x100 / 100;
            } else if (dx100 < 0 && old_x >= (int32_t)p->x + p->width &&
                       new_x < (int32_t)p->x + p->width) {
                proposed_x100 = ((int32_t)p->x + p->width) * 100;
                new_x = proposed_x100 / 100;
            }
        }
        physics->x100 = proposed_x100;

        /* Gravity adds a small amount of downward speed each frame. */
        const int32_t gravity = physics->gravity > 0 ? physics->gravity : 0;
        const int32_t max_fall = physics->max_fall_speed > 0
                               ? (int32_t)physics->max_fall_speed * 100 : 0;
        physics->vy100 += gravity;
        if (physics->vy100 > max_fall) physics->vy100 = max_fall;
        int32_t proposed_y100 = physics->y100 + physics->vy100;
        int32_t new_y = proposed_y100 / 100;
        physics->on_ground = 0;

        for (uint16_t i = 0; i < physics->platform_count; ++i) {
            const game_platform_t *p = &physics->platforms[i];
            if (!p->width || !p->height) continue;
            if (new_x + w <= p->x || new_x >= (int32_t)p->x + p->width) continue;

            /* Falling onto either kind of platform: stop at its top. */
            if (physics->vy100 >= 0 && old_y + h <= p->y &&
                new_y + h >= p->y) {
                proposed_y100 = ((int32_t)p->y - h) * 100;
                new_y = proposed_y100 / 100;
                physics->vy100 = 0;
                physics->on_ground = 1;
            }
            /* SOLID ceilings block upward movement; ONE-WAY ones don't. */
            else if (physics->vy100 < 0 && p->type == GAME_PLATFORM_SOLID &&
                     old_y >= (int32_t)p->y + p->height &&
                     new_y <= (int32_t)p->y + p->height) {
                proposed_y100 = ((int32_t)p->y + p->height) * 100;
                new_y = proposed_y100 / 100;
                physics->vy100 = 0;
            }
        }
        physics->y100 = proposed_y100;

        /* gfxbob_t uses signed 16-bit draw positions. Stay in that range. */
        if (physics->x100 < -3276800) physics->x100 = -3276800;
        if (physics->x100 > 3276700) physics->x100 = 3276700;
        if (physics->y100 < -3276800) { physics->y100 = -3276800; physics->vy100 = 0; }
        if (physics->y100 > 3276700) { physics->y100 = 3276700; physics->vy100 = 0; }
        sprite->drawx = (int16_t)(physics->x100 / 100);
        sprite->drawy = (int16_t)(physics->y100 / 100);
    }
}

/*
 * ==================== BEGINNER EXAMPLE ====================
 *
 * 1. Make a sprite in Game Designer called "player" and give it an image.
 *    Set its Handle to TOP LEFT and its Scale to 100% (the defaults).
 *    You may draw any background and scenery separately in your game.
 *
 * 2. Add this at the top of main.c (after your usual includes):
 *
 *      #include "gameassets.h"
 *      #include "gamehelpers/gameplatformer.h"
 *
 *    The level is just a list of invisible collision rectangles.
 *    Each entry is {x, y, width, height, type} in screen pixels.
 *    Draw matching platform graphics in your background if you wish.
 *
 *      static const game_platform_t level[] = {
 *          {  0, 280, 480, 40, GAME_PLATFORM_SOLID  }, // ground
 *          { 80, 220, 100, 12, GAME_PLATFORM_ONEWAY }, // jump-through ledge
 *          {250, 175, 100, 12, GAME_PLATFORM_ONEWAY }  // higher ledge
 *      };
 *      static game_platformer_t player_physics = {0};
 *
 * 3. AFTER gameassets_init() succeeds, BEFORE your main game loop:
 *
 *      player.drawx = 32;
 *      player.drawy = 280 - player.height;  // feet on the ground
 *      if (!start_platformer(&player_physics, &player,
 *                            level, sizeof(level) / sizeof(level[0]))) {
 *          // Check that the sprite is initialised, TOP LEFT, scale=100.
 *      }
 *
 *    OPTIONAL settings:
 *      player_physics.walk_speed = 4; // quicker walking
 *      player_physics.jump_speed = 8; // higher jump
 *      player_physics.gravity = 40;   // stronger gravity (0.40 pixels/frame)
 *
 * 4. Inside the game loop, ONCE PER VBlank and BEFORE drawing:
 *
 *      run_platformer(&player_physics, getjoyport(), 1);
 *      // Keep your EXISTING buffer-clearing and drawing code here.
 *      // Draw the player normally, e.g. gfx_drawbob(&player);
 *
 *    LEFT/RIGHT: walk.  UP or FIRE: jump. Release and press again to jump.
 *    50 frames = 1 second at FPS_50. The helper does NOT wait for VBlank.
 *
 * 5. To restart after falling off the level:
 *
 *      if (player.drawy > 340) reset_platformer(&player_physics, 32, 240);
 *
 * IMPORTANT:
 * - "player" is just an example name. Use your generated sprite variable.
 * - The helper only moves ONE player. It doesn't draw the level or camera.
 * - Your invisible collision rectangles should match your platform artwork.
 * - One-way platforms let the player jump UP through them and land on top.
 * - Tween/spline and platformer should NOT move the same sprite at once:
 *   they'd both write to drawx/drawy. Sprite Animation CAN be combined.
 * - To grow beyond a screen-sized level, a tilemap and camera helper can
 *   come later; no need to learn those before making your first platformer.
 * ==========================================================
 */
