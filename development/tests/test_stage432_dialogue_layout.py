#!/usr/bin/env python3
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
tests=Path(__file__).parent
with tempfile.TemporaryDirectory() as d:
    exe=Path(d)/'stage432'
    from stage442_render_test_helpers import render_adventure_runtime
    runtime=render_adventure_runtime(root, Path(d) / 'runtime')
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(runtime),
        str(runtime/'adventureruntime.c'),
        str(tests/'test_stage432_dialogue_layout.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
