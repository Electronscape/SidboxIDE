#!/usr/bin/env python3
"""Stage 5.41.1: compiled Adventure-runtime inventory quantity for HUD."""
from pathlib import Path
import subprocess
import re
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root = Path(__file__).resolve().parents[2]
tests = root / 'development/tests'
with tempfile.TemporaryDirectory(prefix='stage5411-hud-') as tmp:
    out = Path(tmp)
    render_adventure_runtime(root, out, items=4)
    (out/'test.c').write_text(r'''#include "adventureruntime.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
void test_colour(uint8_t x){(void)x;}
void test_text(int x,int y,const char *t){(void)x;(void)y;(void)t;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
static const game_adventure_item_t items[]={
  {"Coin",1,65535,500,1},{"Special Coin",1,65535,500,2},
  {"Ruby",2,65535,500,6},{"Manual",0,65535,500,3}
};
int main(void){
    uint32_t n=999;
    game_adventure_start(items,4,0,0,0,0,0,0,0,8,0,2,0,0);
    assert(game_adventure_pickup_quantity(1,&n)==1 && n==3);
    assert(game_adventure_pickup_quantity(2,&n)==1 && n==6);
    assert(game_adventure_pickup_quantity(3,&n)==0 && n==0);
    assert(game_adventure_pickup_quantity(0,&n)==0 && n==0);
    assert(game_adventure_remove(0,1));
    assert(game_adventure_pickup_quantity(1,&n)==1 && n==2);
    assert(game_adventure_remove(1,2));
    assert(game_adventure_pickup_quantity(1,&n)==1 && n==0);
    assert(game_adventure_add(0,5)==5);
    assert(game_adventure_pickup_quantity(1,&n)==1 && n==5);
    assert(game_adventure_pickup_quantity(1,0)==1);
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,2,0,0);
    assert(game_adventure_pickup_quantity(1,&n)==0 && n==0);
    puts("PASS compiled HUD pickup-kind quantity responds to USE/DROP/GIVE/DESTROY");
    return 0;
}
''')
    exe = out/'test'
    cmd=['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(out/'test.c'),'-o',str(exe)]
    run=subprocess.run(cmd,capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    run=subprocess.run([str(exe)],capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    print(run.stdout.strip())

editor=(root/'gameadventureeditor.cpp').read_text()
# QVariant::toInt takes a bool*; Stage 5.41 incorrectly passed 8 as a fallback.
assert 'data(Qt::UserRole+4).toInt(8)' not in editor
assert editor.count('data(Qt::UserRole+4).isValid()') == 4
assert re.search(r'Build: 5\.\d+(?:\.\d+)?\.\d{6}', (root/'splashscreenwidget.cpp').read_text())
print('PASS Qt QVariant default handling at all four inventory icon call sites')
