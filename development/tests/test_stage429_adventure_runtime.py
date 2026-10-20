#!/usr/bin/env python3
"""Build and execute an independent host-based text/animation regression test.
The mock apis.h records glyph draw colour without changing SIDBOX headers."""
from pathlib import Path
import subprocess
import tempfile
root = Path(__file__).resolve().parents[2]
tests = Path(__file__).resolve().parent
with tempfile.TemporaryDirectory() as folder:
    binary=Path(folder)/'stage429_test'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),
        '-I',str(root/'idelibs/codehelpers/game'),
        str(root/'idelibs/codehelpers/game/adventureruntime.c'),
        str(tests/'test_stage429_adventure_runtime.c'),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
