#!/usr/bin/env python3
import subprocess, tempfile
from pathlib import Path
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory() as d:
    exe=Path(d)/'adventure434'
    runtime = render_adventure_runtime(root, Path(d), items=64)
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(runtime),
        str(runtime/'adventureruntime.c'),
        str(tests/'test_stage434_adventure_runtime.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
