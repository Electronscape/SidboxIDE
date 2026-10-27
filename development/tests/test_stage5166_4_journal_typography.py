#!/usr/bin/env python3
"""Stage 5.166.4: scaled heading, padding, list offset, outlines and input contract."""
from pathlib import Path
import tempfile, subprocess, sys
root=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(root/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime

editor=(root/'gamequestjournaleditor.cpp').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
template=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
source=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
header=(root/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
for name in ('titleX','titleY','titleFontX','titleFontY','listLeft','outlineEnabled','outlineColour'):
    assert f'"{name}"' in editor, name
for token in ('QUEST_TITLE_X','QUEST_TITLE_Y','QUEST_TITLE_FONT_X','QUEST_TITLE_FONT_Y',
              'QUEST_LIST_LEFT','QUEST_OUTLINE_ENABLED','QUEST_OUTLINE_COLOUR'):
    assert token in gen and token in template, token
assert 'SidboxPalettePicker::chooseIndex' in editor
assert 'if(!ga_quest_skin_pixels)' in source
assert 'if(fire2_edge)' in source and 'if(fire2_edge || left_edge)' not in source
assert 'if(fire1_edge &&' in source and 'fire1_edge || right_edge' not in source
assert 'ga_outline_colour=saved_outline_colour' in source
assert 'list_left,title_x,title_y,title_font_x,title_font_y' in header
assert 'Build: 5.166.5.271026' in (root/'splashscreenwidget.cpp').read_text()
with tempfile.TemporaryDirectory(prefix='quest1664_') as work:
    d=Path(work)
    render_adventure_runtime(root,d)
    mock=(root/'development/tests/stage429_mock_api/apis.h').read_text()
    # No provider needed for these draw regressions; touch is deliberately absent.
    mock=mock.replace('#define gfx_drawtextf(x,y,s,sx,sy) test_text(x,y,s)',
                      '#define gfx_drawtextf(x,y,s,sx,sy) test_textf(x,y,s,sx,sy)')
    mock=mock.replace('void test_text(int x,int y,const char *text);',
                      'void test_text(int x,int y,const char *text);\nvoid test_textf(int x,int y,const char *text,int sx,int sy);')
    mock=mock[:-len('#endif\n')]+'''typedef struct {
  void (*init)(void); uint8_t (*ispressed)(void);
  uint8_t (*getxy)(int16_t *,int16_t *);
} mock_touch_t;
typedef struct {const mock_touch_t *touch;} mock_root_t;
extern mock_root_t *mock_api;
#define API mock_api
#define apiTouchInit() (API->touch->init())
#define apiTouchDown() (API->touch->ispressed())
#define apiTouchGetXY(x,y) (API->touch->getxy((x),(y)))
#endif
'''
    (d/'apis.h').write_text(mock)
    (d/'check.c').write_text(r'''
#include "adventureruntime.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
static int title_x,title_y,title_sx,title_sy,title_calls;
static int outer_0,draw_calls,last_title_colour,stroke_ink=0;
static uint8_t colour;
static int list_x,has_list;
static uint8_t finger=0;
static void init(void){}
static uint8_t down(void){return finger;}
static uint8_t coords(int16_t*x,int16_t*y){*x=20;*y=20;return 1;}
static const mock_touch_t touch={init,down,coords};
static mock_root_t root={&touch};
mock_root_t *mock_api=&root;
static void frame(void){game_adventure_input(0u,0,0,16,16,1);}
void test_colour(uint8_t c){colour=c;}
void test_text(int x,int y,const char*s){
    if(!strcmp(s,"QUESTS")){list_x=x;has_list=1;}
    if(!strcmp(s,"UP/DOWN SELECT"))assert(x>=8);
    (void)y;draw_calls++;
}
void test_textf(int x,int y,const char*s,int sx,int sy){
    if(!strcmp(s,"QUEST JOURNAL")){
        title_x=x;title_y=y;title_sx=sx;title_sy=sy;
        last_title_colour=colour;++title_calls;
        if(colour==5u)stroke_ink++;
    }
    draw_calls++;
}
void test_rect(int x,int y,int w,int h){
    if(x==6 && y==6 && w==468 && h==1)outer_0++;
    (void)x;(void)y;(void)w;(void)h;
}
void test_bob(gfxbob_t*b){(void)b;}
static uint16_t count(void){return 1u;}
static const char* id(uint16_t n){(void)n;return "q1";}
static const char* txt(uint16_t n){(void)n;return "Quest Title";}
static uint8_t status(uint16_t n){(void)n;return 1u;}
static int16_t tracked(void){return 0;}
static uint8_t track(const char*s){(void)s;return 1;}
static const game_adventure_quest_ui_t ui={count,id,txt,txt,txt,status,tracked,track};
int main(void){
    /* Normal non-atlas style. Heading uses Title Editor's native 1/2/4/8 scales. */
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_quest_journal(&ui);
    game_adventure_quest_viewport(0,320);
    game_adventure_quest_style_t style={6u,42u,2u,15u,15u,14u,
                                       54u,32u,16u,2u,4u,1u,5u};
    game_adventure_quest_style(&style);
    finger=0;frame();finger=1;frame();
    assert(game_adventure_open());
    game_adventure_draw(0,0,0,0);
    assert(title_calls==5 && stroke_ink==4);
    assert(title_x==38 && title_y==22 && title_sx==2 && title_sy==4);
    assert(last_title_colour==15 && has_list && list_x==60);
    assert(outer_0>=1); /* Solid frame requires separate outer border. */
    /* Atlas skin supplies its own edge: do not draw another border. */
    static uint8_t pixels[24*24]={0};
    static const uint16_t cells[9]={0,1,2,3,4,5,6,7,8};
    game_adventure_quest_skin_file(pixels,"skin.ppb",24,24,24,24,8,cells,0);
    outer_0=0;
    game_adventure_draw(0,0,0,0);
    assert(outer_0==0);
    assert(list_x==60 && title_x==38);
    puts("PASS 5.166.4 native layout, outline and atlas-border test");
    return 0;
}
''')
    # Build/run rendered runtime with a simulated SIDBOX touch provider.
    out=d/'test'
    subprocess.run(['gcc','-std=gnu11','-Wall','-Wextra','-Werror','-I',str(d),
                   str(d/'adventureruntime.c'),str(d/'check.c'),'-o',str(out)],check=True)
    subprocess.run([str(out)],check=True)
print('PASS Stage 5.166.4 typography, per-panel positioning, joystick and ABI compile')
