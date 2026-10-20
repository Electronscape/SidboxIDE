/* Host check: BOB flip bits don't clear unrelated flags; generated preprocessor
 * support for the Hurt enum is an actual macro, unlike the enum itself. */
#include <assert.h>
#include <stdint.h>
#include "graphics.h"
enum { PLAYER_ANIM_STATE_IDLE = 0, PLAYER_ANIM_STATE_HURT = 8 };
#define PLAYER_ANIM_HAS_HURT_STATE 1
int main(void)
{
    gfxbob_t sprite = {0};
    sprite.flags = BLIT_FLAG_SOLIDCOLOUR;
    sprite.flags = (uint8_t)((sprite.flags & ~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y)) |
                             BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y);
    assert(sprite.flags & BLIT_FLAG_SOLIDCOLOUR);
    assert(sprite.flags & BLIT_FLAG_FLIP_X);
    assert(sprite.flags & BLIT_FLAG_FLIP_Y);
    uint8_t player_anim_state = PLAYER_ANIM_STATE_IDLE;
    uint8_t hurt_anim_active = 1, hurt_ticks_remaining = 9;
#if defined(PLAYER_ANIM_HAS_HURT_STATE) && PLAYER_ANIM_HAS_HURT_STATE
    if (hurt_anim_active && hurt_ticks_remaining)
        player_anim_state = PLAYER_ANIM_STATE_HURT;
#endif
    assert(player_anim_state == PLAYER_ANIM_STATE_HURT);
    return 0;
}
