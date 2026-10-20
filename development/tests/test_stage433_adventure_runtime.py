#!/usr/bin/env python3
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
tests=Path(__file__).parent
with tempfile.TemporaryDirectory() as tmp:
    exe=Path(tmp)/'adventure433'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(root/'idelibs/codehelpers/game'),
        str(root/'idelibs/codehelpers/game/adventureruntime.c'),
        str(tests/'test_stage433_adventure_runtime.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
