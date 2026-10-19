/* Stage 3.84 native regression for generated animation timing semantics.
   No STM32 hardware required: gcc -std=c99 -Wall -Wextra -Werror ... */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    const uint8_t *frames;
    const uint8_t *frame_ticks;
    uint16_t count, ticks;
    uint8_t loop, flip_x;
} Clip;
typedef struct { uint16_t elapsed, position; uint8_t state, direction, started; } Player;
static void step(Player *a, const Clip *clip, uint16_t frame_step)
{
    if (!a->started) {
        a->started = 1; a->position = 0; a->elapsed = 0;
    } else if (frame_step && (clip->loop || a->position + 1u < clip->count)) {
        uint32_t remaining = (uint32_t)a->elapsed + frame_step;
        if (!clip->frame_ticks) {
            uint32_t steps = remaining / clip->ticks;
            a->elapsed = (uint16_t)(remaining % clip->ticks);
            if (steps) {
                uint32_t next = (uint32_t)a->position + steps;
                a->position = clip->loop ? (uint16_t)(next % clip->count)
                        : (uint16_t)(next >= clip->count ? clip->count - 1u : next);
            }
        } else {
            uint16_t duration = clip->frame_ticks[a->position];
            while (remaining >= duration) {
                remaining -= duration;
                if (a->position + 1u < clip->count) ++a->position;
                else if (clip->loop) a->position = 0;
                else { remaining = 0; break; }
                duration = clip->frame_ticks[a->position];
            }
            a->elapsed = (uint16_t)remaining;
        }
    }
}
int main(void)
{
    const uint8_t frames[] = {10, 5, 10};
    const uint8_t timing[] = {2, 5, 1};
    Clip varied = {frames, timing, 3, 5, 1, 0};
    Player player = {0};
    step(&player, &varied, 1); assert(player.position == 0);
    step(&player, &varied, 1); assert(player.position == 0);
    step(&player, &varied, 1); assert(player.position == 1);
    step(&player, &varied, 4); assert(player.position == 1);
    step(&player, &varied, 1); assert(player.position == 2);
    step(&player, &varied, 1); assert(player.position == 0);
    /* A position's duration is independent of repeated atlas indexes. */
    step(&player, &varied, 8); assert(player.position == 0);
    /* Large frame_step crosses multiple differently sized frames. */
    step(&player, &varied, 3); assert(player.position == 1);

    Clip uniform = {frames, 0, 3, 5, 1, 0};
    Player legacy = {0};
    step(&legacy, &uniform, 1);
    step(&legacy, &uniform, 15);
    assert(legacy.position == 0 && legacy.elapsed == 0);

    Clip stop = {frames, timing, 3, 5, 0, 0};
    Player ending = {0};
    step(&ending, &stop, 1);
    step(&ending, &stop, 20);
    assert(ending.position == 2 && ending.elapsed == 0);
    step(&ending, &stop, 20);
    assert(ending.position == 2);
    puts("Stage 3.84 per-frame C timing semantics: PASS");
    return 0;
}
