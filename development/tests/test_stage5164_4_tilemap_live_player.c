/* Native collision-module registration test: no world-manager hooks. */
#include <assert.h>
#include <stdio.h>
#include "tilemap.h"
int main(void)
{
    static uint8_t collisions[64];
    game_tilemap_t map={0};
    map.collision=collisions;
    map.width=8; map.height=8; map.tile_size=16;
    gfxbob_t sprite={0};
    sprite.handle=BLIT_HANDLE_TOP_LEFT;
    sprite.scale=100;
    sprite.width=16; sprite.height=16;
    sprite.drawx=23; sprite.drawy=45;
    game_tile_player_t player={0};
    assert(game_tile_player_current()==NULL);
    assert(game_tile_player_start(&player,&map,&sprite));
    assert(game_tile_player_current()==&player);
    player.x100=12300; player.y100=23400;
    assert(game_tile_player_current()->x100/100==123);
    assert(game_tile_player_current()->y100/100==234);
    puts("PASS Stage 5.164.4: tilemap automatically exposes the live player");
    return 0;
}
