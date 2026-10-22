#!/usr/bin/env python3
"""Host-GCC regression for inventory USE actions and fixed action text origins."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage532-use-') as td:
    out=Path(td)
    render_adventure_runtime(root,out,items=2)
    exe=out/'use_actions'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(tests/'test_stage532_inventory_use.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.32: item USE, failed handler, consumption, stable labels PASS')
