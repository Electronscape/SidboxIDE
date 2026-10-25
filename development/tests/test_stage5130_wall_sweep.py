#!/usr/bin/env python3
from pathlib import Path
import subprocess, tempfile, re
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
src=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert 'Build: 5.130.251026' in (root/'splashscreenwidget.cpp').read_text()
assert 'game_adventure_set_drop_sweep(gameadventure_drop_sweep);' in src
assert 'game_tilemap_actor_blocked(map,next_x,y,16u,16u)' in src
assert 'game_adventure_set_drop_sweep(game_adventure_drop_sweep_t query)' in (root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
assert 'const int32_t start_x=has_foot' in (root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
code=src.split('static int32_t gameadventure_drop_sweep(',1)[1].split('/* Query the SAME map',1)[0]
with tempfile.TemporaryDirectory(prefix='cg5130-') as d:
    d=Path(d)
    (d/'stage5130_generated_sweep.inc').write_text('static int32_t gameadventure_drop_sweep('+code)
    render_adventure_runtime(root,d,items=1)
    test=root/'development/tests'
    for name in ('test_stage5130_wall_sweep.c','test_stage5129_drop_foot.c',
                 'test_stage5128_drop_gravity.c','test_stage5126_directional_drop.c',
                 'test_stage5126_thought_colours.c'):
        exe=d/name.replace('.c','')
        subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
                        '-DBTN_FIRE=8','-I',str(test/'stage429_mock_api'),'-I',str(d),
                        str(d/'adventureruntime.c'),str(test/name),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.130 generated C and previous runtime tests PASS')
