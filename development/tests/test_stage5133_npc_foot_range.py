#!/usr/bin/env python3
"""Stage 5.133 native NPC interaction range regression."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
source=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
assert 'pcx = sprite_x + ga_drop_foot_x;' in source
assert 'const int32_t pcy = player_y + (int32_t)player_h / 2;' in source
assert 'Build: 5.133.251026' in (root/'splashscreenwidget.cpp').read_text()
with tempfile.TemporaryDirectory(prefix='cg5133-') as directory:
    out=render_adventure_runtime(root,Path(directory),items=1)
    testroot=root/'development/tests'
    exe=out/'test_stage5133_npc_foot_range'
    cmd=['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
         '-I',str(testroot/'stage429_mock_api'),'-I',str(out),
         str(out/'adventureruntime.c'),str(testroot/'test_stage5133_npc_foot_range.c'),
         '-o',str(exe)]
    subprocess.run(cmd,check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.133 generated runtime NPC proximity regression PASS')
