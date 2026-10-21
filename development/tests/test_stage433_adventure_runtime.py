#!/usr/bin/env python3
from pathlib import Path
from stage442_render_test_helpers import render_adventure_runtime
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
tests=Path(__file__).parent
with tempfile.TemporaryDirectory() as tmp:
    exe=Path(tmp)/'adventure433'
    runtime = render_adventure_runtime(root, Path(tmp), items=64)
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(runtime),
        str(runtime/'adventureruntime.c'),
        str(tests/'test_stage433_adventure_runtime.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
