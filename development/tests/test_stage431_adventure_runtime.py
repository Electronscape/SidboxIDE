#!/usr/bin/env python3
from pathlib import Path
from stage442_render_test_helpers import render_adventure_runtime
import subprocess,tempfile
root=Path(__file__).resolve().parents[2]
tests=Path(__file__).parent
with tempfile.TemporaryDirectory() as d:
    binary=Path(d)/'adventure431'
    runtime = render_adventure_runtime(root, Path(d), items=64)
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(runtime),
        str(runtime/'adventureruntime.c'),
        str(tests/'test_stage431_adventure_runtime.c'),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
