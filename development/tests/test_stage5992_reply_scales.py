#!/usr/bin/env python3
"""Compile the generated runtime with a spy that records actual font scales."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory(prefix='sidbox5992-') as tmp:
    tmp=Path(tmp)
    out=render_adventure_runtime(root,tmp/'runtime')
    mock=tmp/'mock'
    mock.mkdir()
    original=(root/'development/tests/stage429_mock_api/apis.h').read_text()
    original=original.replace('void test_text(int x,int y,const char *text);',
        'void test_text(int x,int y,const char *text);\n'
        'void test_text_scaled(int x,int y,const char *text,uint8_t sx,uint8_t sy);')
    original=original.replace('#define gfx_drawtextf(x,y,s,sx,sy) test_text(x,y,s)',
        '#define gfx_drawtextf(x,y,s,sx,sy) test_text_scaled(x,y,s,sx,sy)')
    (mock/'apis.h').write_text(original)
    exe=tmp/'stage5992'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-I',str(mock),'-I',str(out),
        str(out/'adventureruntime.c'),str(root/'development/tests/test_stage5992_reply_scales.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
