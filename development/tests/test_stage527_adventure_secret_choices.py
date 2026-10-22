#!/usr/bin/env python3
"""Render shipping Adventure templates, compile -Werror, and test both paths."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root = Path(__file__).resolve().parents[2]
tests = root / 'development/tests'
with tempfile.TemporaryDirectory() as tmp:
    out = Path(tmp)
    render_adventure_runtime(root, out, items=1)
    exe = out / 'stage527_test'
    subprocess.run([
        'gcc', '-std=c11', '-O0', '-Wall', '-Wextra', '-Werror',
        '-I', str(tests / 'stage429_mock_api'), '-I', str(out),
        str(out / 'adventureruntime.c'),
        str(tests / 'test_stage527_adventure_secret_choices.c'),
        '-o', str(exe)
    ], check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.27: rendered C builds and dialogue secrecy regression passes')
