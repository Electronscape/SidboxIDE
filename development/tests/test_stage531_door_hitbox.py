#!/usr/bin/env python3
"""Compile the exact generated FIRE2 query body with an offset hitbox."""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess
root=Path(__file__).resolve().parents[2]
source=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
a=source.index('uint8_t gameworlditems_fire2_action(')
b=source.index('void gameworlditems_before(',a)
query=source[a:b].replace("@IDE{WORLD_OBJECT_COUNT}", "1")
preamble=r'''#include <stdint.h>
#include <assert.h>
#include <stdio.h>
typedef struct { int32_t *x100,*y100; int16_t offset_x,offset_y; uint16_t width,height; } game_world_player_t;
typedef struct { int32_t x,y;uint16_t w,h; } game_world_object_t;
#define GAME_OBJECT_TRIGGER 4
static game_world_object_t platforms[1]={{109,100,8,8}};
static const game_world_player_t *cg_fire2_player;
static uint8_t game_world_objects_fire2_action(const game_world_object_t *a,uint16_t n,
    int32_t x,int32_t y,uint16_t w,uint16_t h) {
    (void)n;
    return (uint8_t)(x<a[0].x+a[0].w && x+w>a[0].x &&
         y<a[0].y+a[0].h && y+h>a[0].y);
}
'''
main=r'''
int main(void) {
    int32_t x=10000,y=10000;
    game_world_player_t p={&x,&y,12,0,8,8};
    cg_fire2_player=0;
    assert(!gameworlditems_fire2_action(100,100,8,8));
    cg_fire2_player=&p;
    assert(gameworlditems_fire2_action(100,100,8,8));
    p.offset_x=0;
    assert(!gameworlditems_fire2_action(100,100,8,8));
    p.offset_x=12;x=17000;
    assert(!gameworlditems_fire2_action(100,100,8,8));
    puts("Stage 5.31: FIRE2 query uses the identical player hitbox and live coordinates PASS");
    return 0;
}
'''
with TemporaryDirectory() as temp:
    c=Path(temp)/'test.c';exe=Path(temp)/'test'
    c.write_text(preamble+query+main)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
