#!/usr/bin/env python3
"""Stage 5.108: source and native runtime spotlight action tests."""
from pathlib import Path
import subprocess,tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
read=lambda f:(root/f).read_text()
assert 'gameworlds_spotlight_action' in read('idelibs/codehelpers/game/gameworlds.ruleh')
assert 'gameworlds_spotlight_action' in read('idelibs/codehelpers/game/gameworlditems.rulec') or 'gameworlds_spotlight_action' in read('gamedesigner_export.cpp')
assert 'SPOTLIGHT_ACTION_ROWS' in read('idelibs/codehelpers/game/gameadventure.rulec')
assert 'SPOTLIGHT_ACTION_ROWS' in read('gameadventuregen.cpp')
assert 'closeSpotlightAction' in read('gameadventureeditor.cpp')
assert 'spotlightAction' in read('gameadventureeditor.cpp')
assert '@player_spotlight' in read('gamedesigner.cpp')
assert '@player_spotlight' in read('gamedesigner_export.cpp')
assert 'foregroundSwatches' in read('gamedesigner.cpp')
assert 'GamePlayerProfile::idlePreview' in read('gamedesigner.cpp')
with tempfile.TemporaryDirectory(prefix='stage5108-') as td:
    out=render_adventure_runtime(root,Path(td))
    exe=out/'stage5108'
    result=subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-I',str(root/'development/tests/stage429_mock_api'),
        '-I',str(out),str(out/'adventureruntime.c'),
        str(root/'development/tests/test_stage5108_spotlight_dialogue.c'),
        '-o',str(exe)],capture_output=True,text=True)
    assert result.returncode == 0,result.stderr
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.108: UI/codegen contracts')
