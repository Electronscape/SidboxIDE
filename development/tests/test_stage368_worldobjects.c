/* Stage 3.68: moving platforms and springs must honour the offset hitbox
   while x100/y100 still represent the sprite's top-left. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../idelibs/codehelpers/game/worldobjects.c"

int main(void) {
    int32_t x100=0,y100=0,vy100=0,force=0;
    uint8_t grounded=1,jump=0,coyote=0;
    int16_t jumpSpeed=7;
    game_world_player_t p={0};
    p.x100=&x100; p.y100=&y100; p.vy100=&vy100;
    p.on_ground=&grounded; p.jump_held=&jump; p.coyote=&coyote;
    p.jump_speed=&jumpSpeed; p.spring_force_vx100=&force;
    p.width=32;p.height=52;p.offset_x=16;p.offset_y=12;
    game_world_object_t platform={0};
    platform.type=GAME_OBJECT_LIFT;platform.active=1;
    platform.width=64;platform.height=8;
    platform.previous_x=10;platform.previous_y=64;
    platform.x=14;platform.y=64;
    game_world_objects_before(&platform,1,&p);
    assert(p.before_x==16 && p.before_feet==64);
    assert(x100==400 && y100==0); /* Follow a platform by 4px. */
    game_world_objects_after(&platform,1,&p);
    assert(y100==0 && grounded);

    x100=0;y100=0;vy100=0;force=0;grounded=1;
    p.ready=0;
    game_world_object_t spring={0};
    spring.type=GAME_OBJECT_SPRING;spring.active=1;
    spring.x=16;spring.previous_x=16;spring.y=64;spring.previous_y=64;
    spring.width=32;spring.height=8;spring.spring_strength=10;
    game_world_objects_before(&spring,1,&p);
    game_world_objects_after(&spring,1,&p);
    assert(spring.spring_triggered && vy100 == -1000);
    assert(y100 == 0 && !grounded); /* World sprite anchor unchanged. */

    x100=0;y100=0;vy100=0;force=0;grounded=0;
    p.ready=0;
    spring=(game_world_object_t){0};
    spring.type=GAME_OBJECT_SPRING; spring.active=1;
    spring.x=48;spring.previous_x=48;
    spring.y=30;spring.previous_y=30;
    spring.width=8;spring.height=10;spring.spring_strength=12;
    spring.touch_activation=1;
    game_world_objects_before(&spring,1,&p);
    game_world_objects_after(&spring,1,&p);
    assert(spring.spring_triggered && vy100 == -1200);
    assert(x100 == 0 && y100 == 0);
    puts("PASS: offset hitbox moving platform, top spring and side-touch spring");
    return 0;
}
