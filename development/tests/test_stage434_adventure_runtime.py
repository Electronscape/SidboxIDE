#!/usr/bin/env python3
import subprocess, tempfile
from pathlib import Path
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory() as d:
    exe=Path(d)/'adventure434'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(root/'idelibs/codehelpers/game'),
        str(root/'idelibs/codehelpers/game/adventureruntime.c'),
        str(tests/'test_stage434_adventure_runtime.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
