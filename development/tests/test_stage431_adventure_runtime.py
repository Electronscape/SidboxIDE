#!/usr/bin/env python3
from pathlib import Path
import subprocess,tempfile
root=Path(__file__).resolve().parents[2]
tests=Path(__file__).parent
with tempfile.TemporaryDirectory() as d:
    binary=Path(d)/'adventure431'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(root/'idelibs/codehelpers/game'),
        str(root/'idelibs/codehelpers/game/adventureruntime.c'),
        str(tests/'test_stage431_adventure_runtime.c'),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
