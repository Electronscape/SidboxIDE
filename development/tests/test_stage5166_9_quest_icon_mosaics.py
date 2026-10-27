#!/usr/bin/env python3
"""Stage 5.166.9: native 2x2 8px mosaic icons, no bob scaling, compile regression."""
from pathlib import Path
import sys, tempfile, subprocess
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
runtime=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
header=(ROOT/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
gen=(ROOT/'gameadventuregen.cpp').read_text()
tpl=(ROOT/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
editor=(ROOT/'gamequestjournaleditor.cpp').read_text()
assert runtime.index('static uint8_t ga_answer_rows(const char *text, uint8_t columns, uint8_t max_rows);') < runtime.index('static uint8_t ga_quest_input(')
for name in ('icon2x2','iconParts','iconTwoByTwo','iconPartButtons','iconPartChosen'):
    assert name in editor, name
for token in ('QUEST_ICON_MODES','QUEST_ICON_PARTS'):
    assert token in gen and token in tpl, token
assert 'game_adventure_quest_icon_composites' in runtime and 'game_adventure_quest_icon_composites' in header
assert 'icon.scale=100u;' in runtime
with tempfile.TemporaryDirectory(prefix='stage51669_native_') as t:
    folder=Path(t)
    render_adventure_runtime(ROOT,folder)
    mock=(ROOT/'development/tests/stage429_mock_api/apis.h').read_text()
    mock=mock.replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u').replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u').replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u')
    mock=mock[:-len('#endif\n')]+'''typedef struct { void (*init)(void); uint8_t (*ispressed)(void); uint8_t (*getxy)(int16_t*,int16_t*); } mock_touch_t;
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
#include <string.h>
#include <stdio.h>
static uint8_t pressed=0;
static uint8_t atlas[64*64];
static int recorded, saw[8];
static int expected_index[]={30,31,38,39,41,40,49,48};
static int expected_x[8],expected_y[8];
static void init_touch(void){}
static uint8_t touch_down(void){return pressed;}
static uint8_t touch_xy(int16_t *x,int16_t*y){*x=12;*y=14;return 1;}
static const mock_touch_t touch={init_touch,touch_down,touch_xy};
static mock_root_t root={&touch}; mock_root_t *mock_api=&root;
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char *s){(void)x;(void)y;(void)s;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){
    if(b->imgdat<atlas || b->imgdat>=atlas+sizeof(atlas)) return;
    const int offset=(int)(b->imgdat-atlas);
    const int cell=(offset/(8*64))*8+(offset%64)/8;
    for(int k=0;k<8;++k)if(cell==expected_index[k]){
        assert(!saw[k]); saw[k]=1; ++recorded;
        assert(b->scale==100u && b->width==8u && b->height==8u);
        assert(b->drawx==expected_x[k] && b->drawy==expected_y[k]);
        return;
    }
}
static uint16_t count(void){return 2u;}
static const char *id(uint16_t n){return n?"b":"a";}
static const char *title(uint16_t n){return n?"Completed":"Active";}
static const char *description(uint16_t n){(void)n;return "This description has enough text to exercise rendering.";}
static const char *objective(uint16_t n){(void)n;return "Pick a flower";}
static uint8_t status(uint16_t n){return n?2u:1u;}
static int16_t tracked(void){return 0;}
static uint8_t track(const char *idstr){(void)idstr;return 1u;}
static const game_adventure_quest_ui_t ui={count,id,title,description,objective,status,tracked,track,0};
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_quest_journal(&ui);
    static const uint16_t frame[9]={0,1,2,3,4,5,6,7,8};
    game_adventure_quest_skin_file(atlas,"icons.ppb",64,64,64,64,8,frame,0);
    static const uint16_t singles[5]={0,1,65535,65535,65535};
    static const uint8_t flips[5]={0,4,0,0,0};
    static const uint8_t modes[5]={1,1,0,0,0};
    static const uint16_t cells[5][4]={
        {30,31,38,39},{40,41,48,49},{65535,65535,65535,65535},
        {65535,65535,65535,65535},{65535,65535,65535,65535}};
    game_adventure_quest_icons(singles,flips);
    game_adventure_quest_icon_composites(modes,cells);
    /* Margin 6, width 468, split=42%=202, inset=16, list left 16. */
    const int list_x=22;
    const int row0_y=6+34+34;
    expected_x[0]=list_x;expected_y[0]=row0_y;
    expected_x[1]=list_x+8;expected_y[1]=row0_y;
    expected_x[2]=list_x;expected_y[2]=row0_y+8;
    expected_x[3]=list_x+8;expected_y[3]=row0_y+8;
    for(int i=4;i<8;++i){expected_x[i]=list_x+((i-4)&1)*8;expected_y[i]=row0_y+24+((i-4)>>1)*8;}
    game_adventure_input(0,0,0,16,16,1);pressed=1;
    game_adventure_input(0,0,0,16,16,1);
    assert(game_adventure_open());
    game_adventure_draw(0,0,0,0);
    assert(recorded==8);
    for(int i=0;i<8;++i)assert(saw[i]);
    puts("PASS Stage 5.166.9 native 2x2 quest icons, 8x8 BOB, no scaling");
    return 0;
}
''')
    exe=folder/'icon_test'
    subprocess.run(['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror','-I',str(folder),str(folder/'adventureruntime.c'),str(folder/'check.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.9 generation/editor/ABI source contracts')
