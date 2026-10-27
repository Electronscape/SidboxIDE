#!/usr/bin/env python3
"""Stage 5.166.10: header status shares heading row, never quest title row."""
from pathlib import Path
import tempfile, subprocess, sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime

runtime=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
preview=(ROOT/'gamequestjournaleditor.cpp').read_text()
assert 'header_status' in runtime
assert 'ga_quest_header_status(ga_quest_ui->status(selected_for_header)' in runtime
assert 'const int status_y=y+(int)ga_quest_style.title_y+' in runtime
assert 'const int heading_right=status_w?status_x-8:right_limit;' in runtime
assert 'const int statusY=y+style.titleY+' in preview
assert 'const int headingChars=std::max(0,(statusX-8-headingX)/(8*style.titleScaleX));' in preview
assert 'ga_text(status_x>right?status_x:right,y+header+8,status_header)' not in runtime
assert 'Build: 5.166.13.271026' in (ROOT/'splashscreenwidget.cpp').read_text()

with tempfile.TemporaryDirectory(prefix='quest_header_') as folder_path:
    folder=Path(folder_path)
    render_adventure_runtime(ROOT,folder)
    mock=(ROOT/'development/tests/stage429_mock_api/apis.h').read_text()
    mock=mock.replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u')
    mock=mock.replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u')
    mock=mock.replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u')
    mock=mock.replace('#define gfx_drawtextf(x,y,s,sx,sy) test_text(x,y,s)',
                      '#define gfx_drawtextf(x,y,s,sx,sy) test_textf(x,y,s,sx,sy)')
    mock=mock.replace('void test_text(int x,int y,const char *text);',
                      'void test_text(int x,int y,const char *text);\nvoid test_textf(int x,int y,const char *text,int sx,int sy);')
    mock=mock[:-len('#endif\n')]+'''typedef struct {void (*init)(void);uint8_t (*ispressed)(void);uint8_t (*getxy)(int16_t*,int16_t*);} mock_touch_t;
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
static uint8_t finger;
static uint8_t colour;
static int hx,hy,hcount,hsx,hsy,status_x,status_y,status_count;
static int quest_title_y,title_count;
static char last_status[32];
static void init(void){}
static uint8_t pressed(void){return finger;}
static uint8_t coords(int16_t*x,int16_t*y){*x=40;*y=40;return 1;}
static const mock_touch_t touch={init,pressed,coords};
static mock_root_t root={&touch}; mock_root_t *mock_api=&root;
void test_colour(uint8_t c){colour=c;}
void test_text(int x,int y,const char*s){
    if(!strcmp(s,"ACTIVE / TRACKED") || !strcmp(s,"COMPLETED")){
        assert(colour==15);
        assert(status_count==0);
        status_x=x; status_y=y;status_count++;snprintf(last_status,sizeof(last_status),"%s",s);
    }
    if(!strcmp(s,"Forest Mystery") || !strcmp(s,"Lost Flower")){
        if(!title_count)quest_title_y=y;
        title_count++;
    }
}
void test_textf(int x,int y,const char*s,int sx,int sy){
    if(!strncmp(s,"QUEST",5)){
        hx=x;hy=y;hcount++;hsx=sx;hsy=sy;
    }
    test_text(x,y,s);
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t*b){(void)b;}
static uint16_t count(void){return 2u;}
static const char* id(uint16_t i){return i?"b":"a";}
static const char* title(uint16_t i){return i?"Lost Flower":"Forest Mystery";}
static const char* description(uint16_t i){(void)i;return "The quest goes here.";}
static const char* objective(uint16_t i){(void)i;return "Enter forest";}
static uint8_t status(uint16_t i){return i?2u:1u;}
static int16_t tracked(void){return 0;}
static uint8_t track(const char*s){(void)s;return 1u;}
static const game_adventure_quest_ui_t ui={count,id,title,description,objective,status,tracked,track,0};
static void clear(void){hx=hy=hcount=hsx=hsy=status_x=status_y=status_count=quest_title_y=title_count=0;last_status[0]=0;}
static void draw_and_check(int sx,int sy,int title_x,int title_y,int inset,const char*expected){
    clear();game_adventure_draw(0,0,0,0);
    assert(status_count==1 && !strcmp(last_status,expected));
    assert(status_x == 480-6-inset-(int)strlen(expected)*8);
    assert(status_y == 6+title_y+((8*sy>16)?(8*sy-16)/2:0));
    assert(quest_title_y==6+((title_y+8*sy+10)>34?(title_y+8*sy+10):34)+34);
    assert(title_count==2); /* Two quests in left list, no duplicated right title. */
    assert(status_y != quest_title_y);
    assert(hcount==1);
    assert(hx == 6+(title_x>inset?title_x:inset) && hy == 6+title_y);
    assert(hsx==sx && hsy==sy);
    const int status_left=status_x;
    assert(hx+8*sx*13<=status_left-8 || (status_left-8-hx)/(8*sx)<13);
}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_quest_journal(&ui);
    /* A scaled heading and solid frame. */
    game_adventure_quest_style_t style={6u,42u,2u,15u,15u,14u,10u,11u,8u,2u,2u,0u,0u};
    game_adventure_quest_style(&style);
    game_adventure_input(0,0,0,16,16,1);finger=1;
    game_adventure_input(0,0,0,16,16,1);
    assert(game_adventure_open());
    draw_and_check(2,2,11,8,8,"ACTIVE / TRACKED");
    /* Completed status is still in journal header when selecting another quest. */
    game_adventure_input(BTN_DOWN,0,0,16,16,1);
    draw_and_check(2,2,11,8,8,"COMPLETED");
    /* Atlas frame changes the safe inset, but not the header row. */
    static uint8_t atlas[24*24];
    static const uint16_t cells[9]={0,1,2,3,4,5,6,7,8};
    game_adventure_quest_skin_file(atlas,"frame.ppb",24,24,24,24,8,cells,0);
    draw_and_check(2,2,11,8,16,"COMPLETED");
    /* Larger heading font, status is centered vertically in header. */
    style.title_font_x=4u;style.title_font_y=4u;
    game_adventure_quest_style(&style);
    draw_and_check(4,4,11,8,16,"COMPLETED");
    puts("PASS Stage 5.166.10 journal status header, scaled title, selected quest and atlas");
    return 0;
}
''')
    exe=folder/'test'
    subprocess.run(['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror','-I',str(folder),str(folder/'adventureruntime.c'),str(folder/'check.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.10 source and preview contract')
