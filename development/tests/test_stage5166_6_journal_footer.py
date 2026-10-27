#!/usr/bin/env python3
"""Regression for footer cut in half by the Quest Journal frame/clip region."""
from pathlib import Path
import tempfile, subprocess, sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
source=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
preview=(ROOT/'gamequestjournaleditor.cpp').read_text()
assert 'const int footer_y=y+h-inset-18;' in source
assert 'const int footerY=y+h-inset-18;' in preview
assert 'const int footer_separator_y=footer_y-8;' in source
assert 'const int footerSeparatorY=footerY-8;' in preview
assert 'const int objective_y=footer_separator_y-55;' in source
assert 'const int objectiveY=footerSeparatorY-55;' in preview
assert 'y+h-22,"UP/DOWN SELECT"' not in source
assert 'y+h-22,QStringLiteral("UP/DOWN SELECT")' not in preview
with tempfile.TemporaryDirectory(prefix='sidbox_quest_footer_') as temp:
    folder=Path(temp)
    render_adventure_runtime(ROOT,folder)
    mock=(ROOT/'development/tests/stage429_mock_api/apis.h').read_text()
    # These tests deliberately supply touch through the same mock used by
    # Stage 5.166's actual game-input native test.
    mock=mock[:-len('#endif\n')]+'''typedef struct {void (*init)(void); uint8_t (*ispressed)(void); uint8_t (*getxy)(int16_t *,int16_t *);} mock_touch_t;
typedef struct {const mock_touch_t *touch;} mock_root_t;
extern mock_root_t *mock_api;
#define API mock_api
#define apiTouchInit() (API->touch->init())
#define apiTouchDown() (API->touch->ispressed())
#define apiTouchGetXY(x,y) (API->touch->getxy((x),(y)))
#endif
'''
    (folder/'apis.h').write_text(mock)
    (folder/'check.c').write_text(r'''
#include "adventureruntime.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
static int footer_y,footer_calls,divider_y,objective_y,footer_text_seen;
static uint8_t finger=0;
static void init(void){}
static uint8_t pressed(void){return finger;}
static uint8_t coords(int16_t*x,int16_t*y){*x=120;*y=140;return 1;}
static const mock_touch_t touch={init,pressed,coords};
static mock_root_t root={&touch};
mock_root_t *mock_api=&root;
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char*s){
    if(!strcmp(s,"UP/DOWN SELECT")) {
        footer_y=y;
        ++footer_calls;
        footer_text_seen=1;
        assert(x>=8);
    }
    if(!strcmp(s,"CURRENT OBJECTIVE"))objective_y=y;
}
void test_rect(int x,int y,int w,int h){
    (void)x;
    if(w>200 && h==1 && y>140)divider_y=y;
}
void test_bob(gfxbob_t*b){(void)b;}
static uint16_t count(void){return 1u;}
static const char* name(uint16_t index){(void)index;return "The Forest Mystery";}
static uint8_t status(uint16_t index){(void)index;return 1u;}
static int16_t tracked(void){return 0;}
static uint8_t track(const char*id){(void)id;return 1u;}
static const game_adventure_quest_ui_t ui={count,name,name,name,name,status,tracked,track};
static uint8_t atlas[96*96]={0};
static const uint16_t cells[9]={0,1,2,3,4,5,6,7,8};
static void check(uint16_t top,uint16_t height,uint8_t tile){
    const game_adventure_quest_style_t style={6u,42u,2u,15u,15u,14u,10u,11u,8u,1u,2u,1u,3u};
    game_adventure_quest_style(&style);
    game_adventure_quest_viewport(top,height);
    if(tile)game_adventure_quest_skin_file(atlas,"journal.ppb",3*tile,3*tile,3*tile,3*tile,tile,cells,0);
    else game_adventure_quest_skin_file(0,0,0,0,0,0,0,0,0);
    footer_y=footer_calls=divider_y=footer_text_seen=0;
    objective_y=0;
    game_adventure_draw(0,0,0,0);
    const int inset=tile?(tile+8):8;
    const int bottom=top+height-6;
    assert(footer_text_seen && footer_calls==5); /* 4 outline strokes plus ink */
    assert(footer_y == bottom-inset-18);
    assert(footer_y+16+1 <= bottom-inset); /* full glyph and outline clear of frame */
    assert(divider_y==footer_y-8);
    assert(objective_y+18+2*16+1 <= divider_y-4); /* two objectives fit */
}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_quest_journal(&ui);
    finger=0;game_adventure_input(0,0,0,16,16,1);
    finger=1;game_adventure_input(0,0,0,16,16,1);
    assert(game_adventure_open());
    check(0,320,0);  /* solid-colour frame */
    check(0,320,8);  /* regular atlas tile */
    check(0,320,16); /* bigger atlas tile */
    check(0,320,32); /* maximum atlas tile */
    check(40,280,8); /* top HUD dock */
    check(0,272,16); /* bottom HUD dock */
    puts("PASS full-size journal footer glyph and atlas-safe padding");
    return 0;
}
''')
    exe=folder/'journal_footer_test'
    subprocess.run(['gcc','-std=gnu11','-Wall','-Wextra','-Werror','-I',str(folder),str(folder/'adventureruntime.c'),str(folder/'check.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.6 journal footer and preview parity')
