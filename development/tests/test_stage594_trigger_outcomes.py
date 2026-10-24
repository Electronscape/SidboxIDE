#!/usr/bin/env python3
"""Compile the actual Adventure rule C with native GCC and exercise Stage 5.94."""
from pathlib import Path
import subprocess, tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory(prefix='sidbox594-') as td:
    out=render_adventure_runtime(root,Path(td))
    exe=out/'stage594'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-I',str(root/'development/tests/stage429_mock_api'),
        '-I',str(out),str(out/'adventureruntime.c'),
        str(root/'development/tests/test_stage594_trigger_outcomes.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
