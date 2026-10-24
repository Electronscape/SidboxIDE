#!/usr/bin/env python3
"""Host runtime test plus source/IDE/generator API compatibility checks."""
from pathlib import Path
import tempfile,subprocess
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage571-') as td:
    out=Path(td);render_adventure_runtime(root,out,items=3)
    exe=out/'npc_visibility'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(tests/'test_stage571_npc_visibility.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
e=(root/'gameadventureeditor.cpp').read_text()
g=(root/'gameadventuregen.cpp').read_text()
r=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
h=(root/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
assert 'new QTableWidget(0,5,npcPage)' in e
assert 'initiallyVisible' in e and 'npcAction%1' in e
assert 'NPC_CHOICE_ACTION_ROWS' in g and 'NPC_VISIBILITY_ROWS' in g
assert 'npcList[n].toObject().value("spriteId")' in g
assert 'game_adventure_save_npc_visibility' in r and 'game_adventure_restore_npc_visibility' in r
assert 'game_adventure_npc_choice_actions' in r
assert 'uint16_t first_node;\n} game_adventure_npc_t;' in h # legacy ABI preserved
assert 'Build: 5.71.5.241026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.71 editor, generator, splash and legacy API wiring PASS')
