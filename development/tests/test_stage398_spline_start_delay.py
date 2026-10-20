#!/usr/bin/env python3
"""Exercise real SIDBOX C spline runtime with delayed moving objects & collectables."""
from pathlib import Path
import subprocess,tempfile,shutil
root=Path(__file__).resolve().parents[2]
helpers=root/'idelibs/codehelpers/game'
api=root/'idelibs/api'
src=r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "worldobjects.h"
#include "collectables.h"

static game_spline_point_t points[] = {{0,0,0},{100,0,0}};
static void make_path(game_spline_t *path, gfxbob_t *sprite) {
    start_spline(path, sprite, points, 2, 100, 0);
}
int main(void) {
    gfxbob_t a = {0}, b = {0}, c = {0};
    game_spline_t sa = {0}, sb = {0}, sc = {0};
    game_world_object_t obj[2] = {{0},{0}};
    game_collectable_t pickup = {0};
    a.drawx = b.drawx = c.drawx = 0;
    make_path(&sa,&a); make_path(&sb,&b); make_path(&sc,&c);
    obj[0].active = obj[1].active = 1;
    obj[0].sprite=&a; obj[0].spline=&sa; obj[0].spline_start_delay=50;
    obj[1].sprite=&b; obj[1].spline=&sb; obj[1].spline_start_delay=0;
    for(int i=0;i<50;++i) game_world_objects_update(obj,2,1);
    assert(sa.elapsed_frames==0 && a.drawx==0 && obj[0].x==0);
    assert(sb.elapsed_frames==50 && b.drawx==50 && obj[1].x==50);
    game_world_objects_update(obj,2,1);
    assert(sa.elapsed_frames==1 && a.drawx>=0);
    assert(sb.elapsed_frames==51 && b.drawx>50);
    obj[0].spline_start_delay=5;
    game_world_objects_update(obj,1,8); // consume five, advance only three
    assert(!obj[0].spline_start_delay && sa.elapsed_frames==4);
    pickup.active=1; pickup.sprite=&c; pickup.spline=&sc;
    pickup.spline_start_delay=25;
    game_collectables_update(&pickup,1,10);
    assert(sc.elapsed_frames==0 && pickup.spline_start_delay==15);
    game_collectables_update(&pickup,1,17);
    assert(sc.elapsed_frames==2 && pickup.x==c.drawx);
    pickup.active=0;
    game_collectables_update(&pickup,1,8); // hidden pickups do not move
    assert(sc.elapsed_frames==2 && pickup.x==c.drawx);
    puts("PASS: actual spline runtime, independent start waits, fractional update, collectables");
    return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
    t=Path(d)
    for fn,name in [('spline.h','gamespline.h'),('animation.h','gameanimation.h')]:
        shutil.copyfile(helpers/fn,t/name)
    (t/'test.c').write_text(src)
    cmd=['cc','-std=c99','-O1','-Wall','-Wextra','-Werror','-ffunction-sections','-fdata-sections',
         '-I',str(t),'-I',str(api),'-I',str(helpers),str(t/'test.c'),
         str(helpers/'worldobjects.c'),str(helpers/'collectables.c'),str(helpers/'spline.c'),
         str(helpers/'animation.c'),'-Wl,--gc-sections','-o',str(t/'test')]
    subprocess.run(cmd,check=True)
    subprocess.run([str(t/'test')],check=True)
