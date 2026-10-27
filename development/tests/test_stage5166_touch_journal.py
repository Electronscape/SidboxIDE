#!/usr/bin/env python3
"""Touch journal native integration using a simulated SIDBOX touch API."""
from pathlib import Path
import tempfile,subprocess,sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
src=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
header=(ROOT/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
world=(ROOT/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert 'game_adventure_set_quest_journal(&quest_journal)' in world
assert 'gameworlds_quest_count, gameworlds_quest_id' in world
assert 'apiTouchInit()' in src and 'apiTouchDown()' in src
assert '/* Touches on an open journal have NO function. */' in src
assert 'ga_quest_window();return;' in src
assert 'if (!ga_state && !ga_quest_open) return;' in src
assert 'ga_quest_button' not in src
assert 'GA_QUEST_BUTTON_X' not in src
assert 'ga_quest_input(press,fire,up,down,left,right)' in src
assert 'game_adventure_open(void) { return ga_state != 0 || ga_quest_open; }' in src
assert 'game_adventure_quest_ui_t' in header
with tempfile.TemporaryDirectory(prefix='sidbox_quest_touch_') as t:
    folder=Path(t)
    render_adventure_runtime(ROOT,folder)
    sdk=(ROOT/'development/tests/stage429_mock_api/apis.h').read_text()
    sdk=sdk.replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u')
    sdk=sdk.replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u')
    sdk=sdk.replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u')
    sdk=sdk.replace('#endif\n', '''typedef struct {
 void (*init)(void);
 uint8_t (*ispressed)(void);
 uint8_t (*getxy)(int16_t *,int16_t *);
} mock_touch_t;
typedef struct {const mock_touch_t *touch;} mock_root_t;
extern mock_root_t *mock_api;
#define API mock_api
#define apiTouchInit() (API->touch->init())
#define apiTouchDown() (API->touch->ispressed())
#define apiTouchGetXY(x,y) (API->touch->getxy((x),(y)))
#define gfx_drawline(x0,y0,x1,y1) test_line(x0,y0,x1,y1)
void test_line(int,int,int,int);
#endif
''',1) if False else sdk
    # Preserve the existing mock's internal #ifdef boundaries, replace final guard only.
    assert sdk.endswith('#endif\n')
    sdk=sdk[:-len('#endif\n')]+'''typedef struct {
 void (*init)(void);
 uint8_t (*ispressed)(void);
 uint8_t (*getxy)(int16_t *,int16_t *);
} mock_touch_t;
typedef struct {const mock_touch_t *touch;} mock_root_t;
extern mock_root_t *mock_api;
#define API mock_api
#define apiTouchInit() (API->touch->init())
#define apiTouchDown() (API->touch->ispressed())
#define apiTouchGetXY(x,y) (API->touch->getxy((x),(y)))
#define gfx_drawline(x0,y0,x1,y1) test_line(x0,y0,x1,y1)
void test_line(int,int,int,int);
#endif
'''
    (folder/'apis.h').write_text(sdk)
    (folder/'touch_test.c').write_text(r'''
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BTN_FIRE 0x01u
#define BTN_LEFT 0x10u
#define BTN_RIGHT 0x20u
static int16_t touch_x,touch_y;
static uint8_t finger;
static int inits, drawn, tracked_calls, journal_headers;
static const char *tracked="q1";
static void touch_init(void){++inits;}
static uint8_t touch_down(void){return finger;}
static uint8_t touch_pos(int16_t*x,int16_t*y){*x=touch_x;*y=touch_y;return 1;}
static const mock_touch_t touch={touch_init,touch_down,touch_pos};
static mock_root_t root={&touch};
mock_root_t *mock_api=&root;
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char*s){(void)x;(void)y;++drawn;if(!strcmp(s,"QUEST JOURNAL"))++journal_headers;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_line(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t*b){(void)b;}
static uint16_t count(void){return 2;}
static const char *id(uint16_t n){return n==0?"q1":"q2";}
static const char *title(uint16_t n){return n==0?"Forest Mystery":"Lost Map";}
static const char *description(uint16_t n){(void)n;return "Find clues and solve the mystery.";}
static const char *objective(uint16_t n){(void)n;return "Enter the forest";}
static uint8_t status(uint16_t n){(void)n;return 1;}
static int16_t get_tracked(void){return !strcmp(tracked,"q1")?0:1;}
static uint8_t track(const char *id){tracked=id;++tracked_calls;return 1;}
static const game_adventure_quest_ui_t ui={count,id,title,description,objective,status,get_tracked,track};
static void frame(uint8_t button){game_adventure_input(button,0,0,16,16,1);}
static void lift(void){finger=0;frame(0);}
static void tap(int16_t x,int16_t y){finger=1;touch_x=x;touch_y=y;frame(0);}
static int bright_calls;
static void untint(void){++bright_calls;}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_set_quest_journal(&ui);
    game_adventure_set_modal_fullbright(untint);
    game_adventure_quest_viewport(48u,272u); /* TOP dock leaves 272 pixels */
    assert(inits==1);
    finger=1;touch_x=33;touch_y=190;frame(0);assert(!game_adventure_open());
    lift();tap(33,190);assert(game_adventure_open());
    assert(game_adventure_gameplay_buttons(0xff)==0);
    drawn=0;game_adventure_draw(0,0,0,0);assert(drawn>5 && bright_calls==1);
    /* Touchscreen MUST NOT navigate/track/close after opening. */
    lift();tap(370,284);assert(game_adventure_open() && !strcmp(tracked,"q1"));
    lift();tap(428,26);assert(game_adventure_open() && tracked_calls==0);
    /* Joystick DOWN changes the highlighted quest, but not tracked state. */
    lift();frame(BTN_DOWN);assert(!strcmp(tracked,"q1"));frame(0);
    frame(BTN_FIRE);assert(!strcmp(tracked,"q2") && tracked_calls==1);
    frame(BTN_FIRE);assert(tracked_calls==1);frame(0);
    /* LEFT and RIGHT do nothing. FIRE2 closes; FIRE1 tracks. */
    frame(BTN_LEFT);assert(game_adventure_open());frame(0);
    frame(BTN_RIGHT);assert(game_adventure_open() && tracked_calls==1);frame(0);
    frame(BTN_FIRE2);assert(!game_adventure_open());frame(0);
    lift();tap(190,180);assert(game_adventure_open());
    frame(BTN_UP);frame(0);frame(BTN_FIRE);
    assert(!strcmp(tracked,"q1") && tracked_calls==2);
    frame(0);frame(BTN_FIRE2);assert(!game_adventure_open());
    /* World travel resets only view; the world manager retains tracked ID. */
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    assert(!game_adventure_open());
    game_adventure_set_quest_journal(&ui);
    assert(inits==2 && !strcmp(tracked,"q1"));
    lift();tap(123,200);assert(game_adventure_open());
    game_adventure_quest_viewport(0u,272u); /* BOTTOM dock */
    drawn=0;game_adventure_draw(0,0,0,0);assert(drawn>5);
    lift();tap(430,24);assert(game_adventure_open());
    frame(BTN_FIRE2);assert(!game_adventure_open());
    /* Inventory must not be overridden. */
    frame(0);frame(BTN_FIRE2);frame(0);
    journal_headers=0;
    lift();tap(25,185);game_adventure_draw(0,0,0,0);
    assert(journal_headers==0);
    puts("PASS Stage 5.166.5 joystick, touch-open-only, HUD dock and palette callback");
    return 0;
}
''')
    cmd=['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror',
         '-I',str(folder),str(folder/'adventureruntime.c'),
         str(folder/'touch_test.c'),'-o',str(folder/'test')]
    subprocess.run(cmd,check=True)
    subprocess.run([str(folder/'test')],check=True)
