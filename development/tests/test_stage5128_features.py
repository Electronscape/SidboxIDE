#!/usr/bin/env python3
from pathlib import Path
import subprocess, tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
rt=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
world=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
assert 'Build: 5.128.251026' in (root/'splashscreenwidget.cpp').read_text()
assert 'ga_step_drops(frames);' in rt
assert 'player_y + (int32_t)player_h/2 - 8' in rt
assert 'game_adventure_set_drop_floor(gameadventure_drop_floor)' in world
assert 'game_tilemap_actor_blocked(map,x,y,16u,16u)' in world
assert 'game_tile_at(map,tx,ty)==GAME_TILE_ONEWAY' in world
assert 'gameworlds_map()' in world
assert 'HAS_DROP_TILEMAP' in gen
assert 'player_physics.x100 / 100 + player_physics.hitbox_x' in main
assert 'player_physics.y100 / 100 + player_physics.hitbox_y' in main
with tempfile.TemporaryDirectory(prefix='cg5128-') as directory:
    out=render_adventure_runtime(root,Path(directory),items=1)
    test=root/'development/tests'
    callback=world.split('static int32_t gameadventure_drop_floor',1)[1].split('@IDE_END',1)[0]
    (out/'stage5128_generated_floor.inc').write_text('static int32_t gameadventure_drop_floor'+callback)
    stub=out/'tile_landing'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-I',str(out),str(test/'test_stage5128_tile_landing.c'),'-o',str(stub)],check=True)
    subprocess.run([str(stub)],check=True)
    for source in ('test_stage5128_drop_gravity.c','test_stage5126_directional_drop.c','test_stage5126_thought_colours.c'):
        exe=out/source.replace('.c','')
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
            '-I',str(test/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(test/source),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.128 source integration and native C runtime PASS')
