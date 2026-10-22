#!/usr/bin/env python3
"""Strict host-GCC regression for Stage 5.33 behavior changes."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage533-') as td:
    out=Path(td)
    render_adventure_runtime(root,out,items=2)
    exe=out/'stage533'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(tests/'test_stage533_inventory_polish.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
assert 'Build: 5.33.221026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.33: generated C and splash checks PASS')

preview=(root/'gameadventureeditor.cpp').read_text()
assert 'm.height=std::min(320,std::max(minimumHeight-8,m.needed));' in preview
assert 'const int choiceSpace=metrics.answerHeight?metrics.answerHeight+1:0;' in preview
