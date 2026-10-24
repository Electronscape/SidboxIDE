#!/usr/bin/env python3
"""Host-compile generated Adventure runtime, simulate real controller exchanges."""
from pathlib import Path
import tempfile,subprocess
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage569-') as td:
    out=Path(td);render_adventure_runtime(root,out,items=3)
    exe=out/'repeat'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(tests/'test_stage569_repeated_wrong_item.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.69 runtime repeat tests PASS')
