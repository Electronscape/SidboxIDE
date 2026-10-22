#!/usr/bin/env python3
from pathlib import Path
import subprocess, tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage532-') as td:
    out=Path(td)
    render_adventure_runtime(root,out,items=1,overrides={'GA_LINES':'6'})
    exe=out/'stage532'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=0x08u','-DBTN_LEFT=0x10u','-DBTN_RIGHT=0x20u',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(tests/'test_stage532_frame_padding.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
src=(root/'gameadventureeditor.cpp').read_text()
assert 'auto previewInset=[&]' in src
assert src.count('outline->isChecked(),previewInset()')>=2
assert 'const int pad=previewInset();' in src
assert 'Build: 5.33.221026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.32: generated templates + IDE preview alignment PASS')
