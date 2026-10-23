#!/usr/bin/env python3
from pathlib import Path
import subprocess,tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory(prefix="cg-stage545-") as td:
    out=Path(td)
    render_adventure_runtime(root,out)
    exe=out/"portable"
    subprocess.run(["cc","-std=c11","-Wall","-Wextra","-Werror",
        "-DTEST_PORTABLE_PPB","-I",str(root/"development/tests/stage429_mock_api"),
        "-I",str(out),str(out/"adventureruntime.c"),
        str(root/"development/tests/test_stage545_portable_icons.c"),"-o",str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
