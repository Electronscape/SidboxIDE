#!/usr/bin/env python3
"""Stage 5.166.11: adaptive Quest Journal description rows and scroll limits."""
from pathlib import Path
import subprocess
import tempfile
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime

runtime = (ROOT / 'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
preview = (ROOT / 'gamequestjournaleditor.cpp').read_text()
assert 'static uint8_t ga_quest_description_visible_rows(void)' in runtime
assert 'const uint8_t visible=ga_quest_description_visible_rows();' in runtime
assert 'const uint8_t visible_desc=ga_quest_description_visible_rows();' in runtime
assert 'const int descFree=objectiveTitleY-8-descY-(16+(style.outline?2:0));' in preview
assert 'const int descLines=descFree<0?0:1+descFree/rowH;' in preview
assert 'Build: 5.166.13.271026' in (ROOT / 'splashscreenwidget.cpp').read_text()

with tempfile.TemporaryDirectory(prefix='quest_dynamic_desc_') as folder_str:
    folder = Path(folder_str)
    render_adventure_runtime(ROOT, folder)
    mock = (ROOT / 'development/tests/stage429_mock_api/apis.h').read_text()
    mock = mock.replace('#define BTN_FIRE2 0x01u', '#define BTN_FIRE2 0x02u')
    mock = mock.replace('#define BTN_UP 0x02u', '#define BTN_UP 0x04u')
    mock = mock.replace('#define BTN_DOWN 0x04u', '#define BTN_DOWN 0x08u')
    mock = mock.replace('#define BTN_LEFT 0x08u', '#define BTN_LEFT 0x10u')
    mock = mock.replace('#define BTN_RIGHT 0x10u', '#define BTN_RIGHT 0x20u')
    mock = mock[:-len('#endif\n')] + '''typedef struct {void (*init)(void); uint8_t (*ispressed)(void); uint8_t (*getxy)(int16_t*,int16_t*);} mock_touch_t;
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
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BTN_RIGHT 0x20u
static uint8_t finger, ink;
static int text_rows, first_y, last_y, objective_y, arrows_down, arrows_up;
static char first_text[16];
static void init_touch(void){}
static uint8_t pressed(void){return finger;}
static uint8_t coords(int16_t*x,int16_t*y){*x=30;*y=30;return 1;}
static const mock_touch_t touch={init_touch,pressed,coords};
static mock_root_t root={&touch}; mock_root_t *mock_api=&root;
void test_colour(uint8_t c){ink=c;}
void test_text(int x,int y,const char*s){
    (void)x;
    if(ink!=15)return; /* Ignore the four outline copies. */
    if(!strncmp(s,"Line",4)){
        if(!text_rows){ first_y=y;snprintf(first_text,sizeof(first_text),"%s",s); }
        ++text_rows;last_y=y;
    }
    if(!strcmp(s,"CURRENT OBJECTIVE"))objective_y=y;
    if(!strcmp(s,"\x1f"))++arrows_down;
    if(!strcmp(s,"\x1e"))++arrows_up;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t*b){(void)b;}
static uint16_t count(void){return 1u;}
static const char* id(uint16_t i){(void)i;return "quest";}
static const char* title(uint16_t i){(void)i;return "Forest Mystery";}
static const char* desc(uint16_t i){(void)i;return
 "Line01\nLine02\nLine03\nLine04\nLine05\nLine06\nLine07\nLine08\nLine09\nLine10\n"
 "Line11\nLine12\nLine13\nLine14\nLine15\nLine16\nLine17\nLine18\nLine19\nLine20";}
static const char* obj(uint16_t i){(void)i;return "Enter Forest";}
static uint8_t status(uint16_t i){(void)i;return 1u;}
static int16_t tracked(void){return 0;}
static uint8_t track(const char *id){(void)id;return 1u;}
static const game_adventure_quest_ui_t ui={count,id,title,desc,obj,status,tracked,track,0};
static void clear(void){text_rows=first_y=last_y=objective_y=arrows_down=arrows_up=0;first_text[0]=0;}
static int draw_check(const char *expected,int step){
    clear();game_adventure_draw(0,0,0,0);
    assert(text_rows==step);
    assert(!strcmp(first_text,expected));
    assert(last_y+16<=objective_y-8);
    assert(arrows_down==1);
    return text_rows;
}
static void tap_button(uint8_t button){
    game_adventure_input(button,0,0,16,16,1);
    game_adventure_input(0,0,0,16,16,1);
}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_quest_journal(&ui);
    game_adventure_quest_style_t style={6u,42u,2u,15u,15u,14u,10u,11u,8u,1u,2u,0u,0u};
    game_adventure_quest_style(&style);
    game_adventure_input(0,0,0,16,16,1);finger=1;
    game_adventure_input(0,0,0,16,16,1);
    assert(game_adventure_open());
    /* Full screen, no atlas, 10 rows fit without touching objective. */
    game_adventure_quest_viewport(0,320);
    draw_check("Line01",11);
    tap_button(BTN_RIGHT);
    draw_check("Line02",11);
    /* Top HUD leaves 272 pixels, so only 7 rows fit; existing scroll remains. */
    game_adventure_quest_viewport(48,272);
    draw_check("Line02",8);
    /* Outline adds pixel-safe spacing, further reducing line count. */
    style.outline_enabled=1;
    game_adventure_quest_style(&style);
    clear();game_adventure_draw(0,0,0,0);
    assert(text_rows>=1 && text_rows<8);
    assert(last_y+18<=objective_y-8);
    /* A 32px nine-slice inset further reduces height, never overlaps objective. */
    static uint8_t atlas[96*96];
    static const uint16_t frame[9]={0,1,2,3,4,5,6,7,8};
    game_adventure_quest_skin_file(atlas,"frame.ppb",96,96,96,96,32,frame,0);
    clear();game_adventure_draw(0,0,0,0);
    assert(text_rows>=1 && text_rows<=6);
    assert(last_y+18<=objective_y-8);
    puts("PASS Stage 5.166.11 dynamic description: full 11, dock 8, outline and 32px atlas safe");
    return 0;
}
''')
    executable = folder / 'dynamic_desc'
    subprocess.run(['gcc', '-std=gnu11', '-O0', '-Wall', '-Wextra', '-Werror',
                    '-I', str(folder), str(folder / 'adventureruntime.c'),
                    str(folder / 'check.c'), '-o', str(executable)], check=True)
    subprocess.run([str(executable)], check=True)
print('PASS Stage 5.166.11 preview/runtime shared layout contract')
