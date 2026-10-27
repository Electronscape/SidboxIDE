#!/usr/bin/env python3
"""Stage 5.166.12 native C journal-scroll glyph contract and runtime regression."""
from pathlib import Path
import tempfile
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime

source = (ROOT / 'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
preview = (ROOT / 'gamequestjournaleditor.cpp').read_text()
assert source.count('"\\x1e"') >= 4
assert source.count('"\\x1f"') >= 4
assert 'if((uint32_t)ga_quest_scroll+rows<count)' in source
assert 'if(ga_quest_scroll)' in source
assert 'const int title_width=split-(list_x+20)-22;' in source
assert 'QChar(0x1F)' in preview
assert 'Build: 5.166.12.271026' in (ROOT / 'splashscreenwidget.cpp').read_text()
assert 'ga_text(selector_x,box_y+box_h-inset-8,"v")' not in source

with tempfile.TemporaryDirectory(prefix='sidbox_stage5166_12_') as temp:
    folder = Path(temp)
    render_adventure_runtime(ROOT, folder)
    mock = (ROOT / 'development/tests/stage429_mock_api/apis.h').read_text()
    mock = mock.replace('#define BTN_FIRE2 0x01u', '#define BTN_FIRE2 0x02u')
    mock = mock.replace('#define BTN_UP 0x02u', '#define BTN_UP 0x04u')
    mock = mock.replace('#define BTN_DOWN 0x04u', '#define BTN_DOWN 0x08u')
    mock = mock[:-len('#endif\n')] + '''typedef struct {void (*init)(void);uint8_t (*ispressed)(void);uint8_t (*getxy)(int16_t*,int16_t*);} mock_touch_t;
typedef struct {const mock_touch_t *touch;} mock_root_t;
extern mock_root_t *mock_api;
#define API mock_api
#define apiTouchInit() (API->touch->init())
#define apiTouchDown() (API->touch->ispressed())
#define apiTouchGetXY(x,y) (API->touch->getxy((x),(y)))
#endif
'''
    (folder / 'apis.h').write_text(mock)
    (folder / 'check.c').write_text(r'''
#include "adventureruntime.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
static uint8_t finger;
static int up,down,up_list,down_list,legacy;
static int list_split;
static uint16_t quests=12;
static uint8_t ink_colour;
static void init(void){}
static uint8_t pressed(void){return finger;}
static uint8_t coords(int16_t*x,int16_t*y){*x=24;*y=160;return 1;}
static const mock_touch_t touch={init,pressed,coords};
static mock_root_t root={&touch};mock_root_t *mock_api=&root;
void test_colour(uint8_t c){ink_colour=c;}
void test_text(int x,int y,const char*s){
    (void)ink_colour;
    if(!strcmp(s,"^")){legacy++;return;}
    if(!strcmp(s,"v")){legacy++;return;}
    if((unsigned char)s[0]==0x1e && s[1]==0){up++;if(x==list_split-16)up_list++;}
    if((unsigned char)s[0]==0x1f && s[1]==0){down++;if(x==list_split-16)down_list++;}
    (void)y;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t*b){(void)b;}
static uint16_t count(void){return quests;}
static const char *id(uint16_t n){(void)n;return "q";}
static const char *title(uint16_t n){(void)n;return "Long Quest Title";}
static const char *description(uint16_t n){(void)n;return "Short description.";}
static const char *objective(uint16_t n){(void)n;return "Find flower";}
static uint8_t status(uint16_t n){(void)n;return 1u;}
static int16_t tracked(void){return -1;}
static uint8_t track(const char *x){(void)x;return 1u;}
static const game_adventure_quest_ui_t ui={count,id,title,description,objective,status,tracked,track,0};
static void clear(void){up=down=up_list=down_list=legacy=0;}
static void draw(void){clear();game_adventure_draw(0,0,0,0);assert(legacy==0);}
static void tap(uint8_t button){game_adventure_input(button,0,0,16,16,1);game_adventure_input(0,0,0,16,16,1);}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_quest_journal(&ui);
    const int margin=6,w=480-2*margin;
    list_split=margin+w*42/100;
    finger=0;game_adventure_input(0,0,0,16,16,1);
    finger=1;game_adventure_input(0,0,0,16,16,1);
    assert(game_adventure_open());
    draw();assert(up_list==0 && down_list==1);
    finger=0;tap(0);
    for(int i=0;i<8;i++)tap(BTN_DOWN);
    draw();assert(up_list==1 && down_list==1);
    for(int i=8;i<11;i++)tap(BTN_DOWN);
    draw();assert(up_list==1 && down_list==0);
    for(int i=0;i<11;i++)tap(BTN_UP);
    draw();assert(up_list==0 && down_list==1);
    quests=1;
    draw();assert(up_list==0 && down_list==0);
    puts("PASS Stage 5.166.12 native scroll glyphs, scroll bounds and ASCII-free arrows");
    return 0;
}
''')
    exe = folder / 'test'
    subprocess.run(['gcc', '-std=gnu11', '-O0', '-Wall', '-Wextra', '-Werror',
                    '-I', str(folder), str(folder/'adventureruntime.c'),
                    str(folder/'check.c'), '-o', str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.12 source/preview glyphs')
