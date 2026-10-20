"""Compile/run the exact generated reward-flight loop from gamedesigner_export.cpp.
This checks release output logic rather than a separately hand-copied approximation.
"""
from pathlib import Path
import re, subprocess, tempfile
root = Path(__file__).resolve().parents[2]
s = (root/'gamedesigner_export.cpp').read_text()
m = re.search(r'C << R"REWARD\(\n(.*?)\n\)REWARD";', s, re.S)
assert m, 'missing generated reward-flight code'
flight = m.group(1)
assert 'cg_reward_vx100' in flight and 'cg_reward_vy100' in flight
assert 'game_tilemap_actor_blocked' in flight and 'can_collect = 1' in flight
source = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#define GAMEWORLDITEMS_PICKUP_COUNT 1
struct P {int32_t x,y; uint16_t width,height; uint8_t active,can_collect;};
static struct P pickups[1];
static uint8_t cg_reward_falling[1];
static int32_t cg_reward_x100[1], cg_reward_y100[1], cg_reward_vx100[1], cg_reward_vy100[1];
static const int game_level1=0;
static int game_tilemap_actor_blocked(const int *map, int x, int y, int w, int h) {
    (void)map;
    return x < 0 || x + w > 200 || y < 0 || y + h > 100;
}
static void game_collectable_set_position(struct P *p, int x, int y) {p->x=x; p->y=y;}
static void step(uint16_t frames) {
''' + flight + r'''
}
static void reset(int vx, int vy, int x, int y) {
    pickups[0]=(struct P){x,y,16,16,1,0};
    cg_reward_falling[0]=1;
    cg_reward_x100[0]=x*100; cg_reward_y100[0]=y*100;
    cg_reward_vx100[0]=vx*100; cg_reward_vy100[0]=vy*100;
}
int main(void) {
    reset(0,0,70,20); step(1); assert(pickups[0].y>=20);
    for(int i=0;i<200&&cg_reward_falling[0];i++) step(1);
    assert(!cg_reward_falling[0] && pickups[0].can_collect && pickups[0].y==84);
    reset(0,-9,70,40); step(3);
    assert(pickups[0].y<40 && !pickups[0].can_collect);
    for(int i=0;i<200&&cg_reward_falling[0];i++) step(1);
    assert(!cg_reward_falling[0] && pickups[0].y==84);
    reset(6,-9,70,40); step(3);
    assert(pickups[0].x>70 && pickups[0].y<40 && !pickups[0].can_collect);
    for(int i=0;i<200&&cg_reward_falling[0];i++) step(1);
    assert(!cg_reward_falling[0] && pickups[0].can_collect);
    reset(-6,-9,70,40); step(2); assert(pickups[0].x<70);
    reset(0,12,70,40); step(1); assert(pickups[0].y>40);
    reset(20,-9,178,40); step(2);
    assert(pickups[0].x==184 && cg_reward_vx100[0]==0);
    reset(0,-20,70,1); step(1);
    assert(pickups[0].y>=0 && cg_reward_vy100[0]==0 && cg_reward_falling[0]);
    puts("PASS: source-generated reward flight: old drop/up/left/right/down/floor/wall/ceiling");
}
'''
with tempfile.TemporaryDirectory() as d:
    p=Path(d)
    (p/'flight.c').write_text(source)
    cmd=['cc','-std=c99','-Wall','-Wextra','-Werror',str(p/'flight.c'),'-o',str(p/'flight')]
    subprocess.run(cmd,check=True)
    subprocess.run([str(p/'flight')],check=True)
