#!/usr/bin/env python3
from pathlib import Path
import subprocess,tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage5342-') as td:
    out=Path(td)
    render_adventure_runtime(root,out,items=1)
    exe=out/'handoff'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(tests/'test_stage5342_fire1_handoff.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
source=(root/'idelibs/codehelpers/game/tilemap.c').read_text()
assert 'GAME_ADVENTURE_FIRE1_INPUT_GUARD_V1' in source
assert 'buttons=game_adventure_gameplay_buttons(buttons);' in source
ide=(root/'gamedesigner.cpp').read_text()
assert 'existingC.contains("GAME_ADVENTURE_FIRE1_INPUT_GUARD_V1")' in ide
editor=(root/'gameadventureeditor.cpp').read_text()
assert 'Still missing items' not in editor
assert 'responseForm->addRow(QObject::tr("Wrong item → dialogue"),wrong);' in editor
runtime=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
assert 'FIRE1: CONFIRM  FIRE2: BACK' in runtime
assert '2*inset+24+' in runtime
assert 'Build: ' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.34.2: new source/generator checks PASS')
