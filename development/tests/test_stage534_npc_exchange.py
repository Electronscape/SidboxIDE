#!/usr/bin/env python3
"""Render SDK code and exercise a real stateful NPC exchange with strict GCC."""
from pathlib import Path
import tempfile,subprocess
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage534-') as td:
    out=Path(td)
    render_adventure_runtime(root,out,items=3)
    exe=out/'exchange'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
       '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
       '-I',str(tests/'stage429_mock_api'),'-I',str(out),
       str(out/'adventureruntime.c'),str(tests/'test_stage534_npc_exchange.c'),
       '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
assert 'Build: ' in (root/'splashscreenwidget.cpp').read_text()
assert 'game_adventure_save_exchanges' in (root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert '"EXCHANGE_ROWS"' in (root/'gameadventuregen.cpp').read_text() or 'QStringLiteral("EXCHANGE_ROWS")' in (root/'gameadventuregen.cpp').read_text()
print('Stage 5.34: generator/runtime/splash checks PASS')
