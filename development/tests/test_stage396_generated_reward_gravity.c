#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#define GAMEWORLDITEMS_PICKUP_COUNT 1
struct P {int32_t x,y;uint16_t width,height;uint8_t active,can_collect;};
static struct P pickups[1]={{0,0,16,16,1,0}};
static uint8_t cg_reward_falling[1]={1};
static int32_t cg_reward_y100[1]={0},cg_reward_vy100[1]={0};
static const int game_level1=0;
static int game_tilemap_actor_blocked(const int *map, int x, int y, int w, int h) {
   (void)map;(void)x;(void)w;return y+h>120;
}
static void game_collectable_set_position(struct P* item,int x,int y) {
  item->x=x; item->y=y;
}
static void step(uint16_t frames){
    /* Dropped rewards use simple gravity and per-pixel tilemap collision.
       They become collectible only AFTER touching solid ground. */
    for (uint16_t i = 0; i < GAMEWORLDITEMS_PICKUP_COUNT; ++i) {
        if (!cg_reward_falling[i]) continue;
        for (uint16_t tick = 0; tick < frames; ++tick) {
            int32_t v = cg_reward_vy100[i] + 65; /* 0.65 px/frame^2 */
            if (v > 900) v = 900; /* cap at 9px/frame for reliable collisions */
            cg_reward_vy100[i] = v;
            int32_t desired_y100 = cg_reward_y100[i] + v;
            int32_t desired_y = desired_y100 / 100;
            int32_t y = pickups[i].y;
            uint8_t landed = 0;
            while (y < desired_y) {
                if (game_tilemap_actor_blocked(&game_level1,
                        pickups[i].x, y + 1, pickups[i].width, pickups[i].height)) {
                    landed = 1;
                    break;
                }
                ++y;
            }
            game_collectable_set_position(&pickups[i], pickups[i].x, y);
            if (landed) {
                cg_reward_y100[i] = y * 100;
                cg_reward_vy100[i] = 0;
                cg_reward_falling[i] = 0;
                pickups[i].can_collect = 1;
                break;
            }
            cg_reward_y100[i] = desired_y100;
            /* Also unlock if already flush with a solid floor. */
            if (game_tilemap_actor_blocked(&game_level1,
                    pickups[i].x, y + 1, pickups[i].width, pickups[i].height)) {
                cg_reward_falling[i] = 0;
                pickups[i].can_collect = 1;
                break;
            }
        }
    }

}
int main(void) {
    for(int n=0;n<100;n++) {
        step(1);
        if(cg_reward_falling[0]) assert(!pickups[0].can_collect);
        else break;
    }
    assert(!cg_reward_falling[0]);
    assert(pickups[0].can_collect);
    assert(pickups[0].y==104);
    printf("PASS: generated reward drop gravity, ground blocking, pickup arming at y=%ld\n",(long)pickups[0].y);
    return 0;
}
