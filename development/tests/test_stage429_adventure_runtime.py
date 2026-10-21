#!/usr/bin/env python3
"""Build and execute an independent host-based text/animation regression test.
The mock apis.h records glyph draw colour without changing SIDBOX headers."""
from pathlib import Path
from stage442_render_test_helpers import render_adventure_runtime
import subprocess
import tempfile
root = Path(__file__).resolve().parents[2]
tests = Path(__file__).resolve().parent
with tempfile.TemporaryDirectory() as folder:
    binary=Path(folder)/'stage429_test'
    runtime = render_adventure_runtime(root, Path(folder), items=64)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),
        '-I',str(runtime),
        str(runtime/'adventureruntime.c'),
        str(tests/'test_stage429_adventure_runtime.c'),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
