/* Stage 3.96: a spawned reward can draw and fall without collecting in flight. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "../../idelibs/codehelpers/game/collectables.c"
static uint16_t calls;
static void on_pickup(game_collectable_t *o, void *arg) {
    (void)o;(void)arg; ++calls;
}
int main(void) {
    gfxbob_t sprite={0};
    game_collectable_t item={0};
    item.sprite=&sprite; item.x=40; item.y=80;
    item.width=16; item.height=16; item.active=1;
    item.can_collect=0;
    assert(game_collectables_check(&item,1,40,80,16,16,on_pickup,0)==0);
    assert(item.active && !calls);
    item.can_collect=1;
    assert(game_collectables_check(&item,1,40,80,16,16,on_pickup,0)==1);
    assert(!item.active && calls==1);
    assert(game_collectables_check(&item,1,40,80,16,16,on_pickup,0)==0);
    puts("PASS: reward cannot collect while falling, collected only on landing");
    return 0;
}
