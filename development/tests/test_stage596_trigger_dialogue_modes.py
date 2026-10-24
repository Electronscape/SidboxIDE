#!/usr/bin/env python3
from pathlib import Path
import subprocess,tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory(prefix='sidbox596-') as td:
    out=render_adventure_runtime(root,Path(td))
    exe=out/'stage596'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8',
        '-I',str(root/'development/tests/stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),
        str(root/'development/tests/test_stage596_trigger_dialogue_modes.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
