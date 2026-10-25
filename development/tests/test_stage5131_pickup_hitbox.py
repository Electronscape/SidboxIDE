#!/usr/bin/env python3
from pathlib import Path
import subprocess,tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
helpers=root/'idelibs/codehelpers/game'
adventure=(helpers/'gameadventure.rulec').read_text()
world=(helpers/'gameworlds.rulec').read_text()
world_h=(helpers/'gameworlds.ruleh').read_text()
runtime=(helpers/'adventureruntime.rulec').read_text()
runtime_h=(helpers/'adventureruntime.ruleh').read_text()
assert 'Build: 5.131.251026' in (root/'splashscreenwidget.cpp').read_text()
assert 'game_adventure_set_pickup_rect(gameadventure_live_pickup_rect);' in adventure
assert 'return gameworlds_player_pickup_rect(x,y,w,h);' in adventure
assert 'gameworlds_player_pickup_rect(int32_t *x, int32_t *y,' in world_h
assert 'bound_player_physics->hitbox_x' in world and 'bound_player_physics->hitbox_y' in world
assert 'game_adventure_set_pickup_rect(0);' in runtime
assert 'ga_collect_drops(player_x, player_y, player_w, player_h)' in runtime
assert 'game_adventure_set_pickup_rect(game_adventure_pickup_rect_t source)' in runtime
assert 'game_adventure_pickup_rect_t' in runtime_h
# Extract actual bridge implementation and compile it against a stand-in
# player object, proving signed offsets and pixel fixed-point conversion.
bridge=world.split('uint8_t gameworlds_player_pickup_rect(',1)[1].split('@IDE_END',1)[0]
bridge='uint8_t gameworlds_player_pickup_rect('+bridge
with tempfile.TemporaryDirectory(prefix='cg5131-') as d:
    d=Path(d)
    (d/'bridge.c').write_text('''#include <stdint.h>
#include <assert.h>
typedef struct {int32_t x100,y100;int16_t hitbox_x,hitbox_y;uint16_t hitbox_w,hitbox_h;} game_tile_player_t;
static game_tile_player_t player={6000,2000,19,2,25,62};
static game_tile_player_t *bound_player_physics=&player;
static int active_world_marker=1;
static void *active_world=&active_world_marker;
'''+bridge+'''
int main(void) {int32_t x=0,y=0;uint16_t w=0,h=0;
assert(gameworlds_player_pickup_rect(&x,&y,&w,&h));
assert(x==79 && y==22 && w==25 && h==62);
player.hitbox_x=-8;player.hitbox_y=-4;
assert(gameworlds_player_pickup_rect(&x,&y,&w,&h));
assert(x==52 && y==16);
player.hitbox_w=0;
assert(!gameworlds_player_pickup_rect(&x,&y,&w,&h));
return 0;}
''')
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(d/'bridge.c'),'-o',str(d/'bridge')],check=True)
    subprocess.run([str(d/'bridge')],check=True)
    sweep=adventure.split('static int32_t gameadventure_drop_sweep(',1)[1].split('/* Query the SAME map',1)[0]
    (d/'stage5131_generated_sweep.inc').write_text('static int32_t gameadventure_drop_sweep('+sweep)
    render_adventure_runtime(root,d,items=1)
    tests=root/'development/tests'
    for name in ('test_stage5131_pickup_hitbox.c','test_stage5130_wall_sweep.c',
                 'test_stage5129_drop_foot.c','test_stage5128_drop_gravity.c',
                 'test_stage5126_directional_drop.c','test_stage5126_thought_colours.c'):
        # Stage5.130 test needs its expected generated sweep include.
        if name=='test_stage5130_wall_sweep.c':
            (d/'stage5130_generated_sweep.inc').write_text('static int32_t gameadventure_drop_sweep('+sweep)
        exe=d/name.removesuffix('.c')
        subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror','-DBTN_FIRE=8',
             '-I',str(tests/'stage429_mock_api'),'-I',str(d),str(d/'adventureruntime.c'),
             str(tests/name),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage5.131 pickup hitbox, wall drop, previous runtime regressions PASS')
