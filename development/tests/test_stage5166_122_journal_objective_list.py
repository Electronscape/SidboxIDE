#!/usr/bin/env python3
"""Native C renderer test: RIGHT objectives, LEFT description, UP/DOWN quest reset."""
from pathlib import Path
import subprocess, tempfile, sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
c=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
h=(ROOT/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
w=(ROOT/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
wh=(ROOT/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
a=(ROOT/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
for needle in ('ga_quest_has_objectives','ga_quest_obj_view','ga_quest_obj_page',
               'OBJECTIVES %u/%u DONE','U/D QUEST L BACK R NEXT'):
    assert needle in c,needle
for needle in ('game_adventure_quest_objectives_t','game_adventure_set_quest_objectives'):
    assert needle in h and needle in a,needle
for needle in ('gameworlds_quest_objective_count','gameworlds_quest_objective_title_at',
               'gameworlds_quest_objective_done_at','gameworlds_quest_is_unordered'):
    assert needle in w and needle in wh and needle in a,needle
with tempfile.TemporaryDirectory(prefix='sidbox_journal_122_') as temp:
    folder=Path(temp)
    render_adventure_runtime(ROOT,folder)
    mock=(ROOT/'development/tests/stage429_mock_api/apis.h').read_text()
    mock=(mock.replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u')
              .replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u')
              .replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u'))
    mock=mock[:-len('#endif\n')]+'''typedef struct {void(*init)(void);uint8_t(*ispressed)(void);uint8_t(*getxy)(int16_t*,int16_t*);} mock_touch_t;
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
#define BTN_RIGHT 0x20u
#define BTN_LEFT 0x10u
static uint8_t finger,done[17]={0};
static int list,desc,first_item,last_item,page2_item,second_quest,ordered,done_label;
static void init(void){}
static uint8_t pressed(void){return finger;}
static uint8_t coords(int16_t*x,int16_t*y){*x=24;*y=160;return 1;}
static const mock_touch_t touch={init,pressed,coords};
static mock_root_t root={&touch};mock_root_t *mock_api=&root;
void test_colour(uint8_t x){(void)x;}
void test_text(int x,int y,const char*s){
 (void)x;(void)y;
 if(strstr(s,"OBJECTIVES ") && strstr(s," DONE"))list++;
 if(strstr(s,"CURRENT OBJECTIVE"))desc++;
 if(strstr(s,"Alpha"))first_item++;
 if(strstr(s,"Beta"))last_item++;
 if(strstr(s,"Item_10"))page2_item++;
 if(strstr(s,"Ordered_"))ordered++;
 if(strstr(s,"1/11 DONE"))done_label++;
 if(strstr(s,"Second Quest"))second_quest++;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t*b){(void)b;}
static uint16_t count(void){return 2;}
static const char *id(uint16_t x){(void)x;return "q";}
static const char *title(uint16_t x){return x?"Second Quest":"Parts";}
static const char *description(uint16_t x){return x?"Two ordered tasks":"Find eleven pieces.";}
static const char *objective(uint16_t x){return x?"Ordered_0":"Alpha";}
static uint8_t status(uint16_t x){(void)x;return 1;}
static int16_t tracked(void){return -1;}
static uint8_t track(const char*x){(void)x;return 1;}
static uint8_t visible(uint16_t x){(void)x;return 1;}
static uint16_t nobj(uint16_t q){return q?2:11;}
static const char*obj_title(uint16_t q,uint16_t o){
 if(q){static const char *names[]={"Ordered_0","Ordered_1"};return names[o];}
 static const char *names[]={"Alpha","Gamma","Delta","Epsilon","Zeta","Eta","Theta","Iota","Kappa","Item_10","Beta"};
 return names[o];
}
static uint8_t obj_done(uint16_t q,uint16_t o){return q? (uint8_t)(o==0):done[o];}
static uint8_t unordered(uint16_t q){return q?0:1;}
static const game_adventure_quest_ui_t ui={count,id,title,description,objective,status,tracked,track,visible};
static const game_adventure_quest_objectives_t objectives={nobj,obj_title,obj_done,unordered};
static void tap(uint8_t button){game_adventure_input(button,0,0,16,16,1);game_adventure_input(0,0,0,16,16,1);}
static void clear_seen(void){list=desc=first_item=last_item=page2_item=second_quest=ordered=done_label=0;}
static void draw(void){game_adventure_draw(0,0,0,0);}
int main(void){
 game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
 game_adventure_set_quest_journal(&ui);
 game_adventure_set_quest_objectives(&objectives);
 finger=0;tap(0);finger=1;tap(0);finger=0;
 assert(game_adventure_open());
 draw();
 assert(desc && !list && !last_item); /* Opens on description, NOT checklist */
 clear_seen();tap(BTN_RIGHT);draw();
 assert(list && !desc && first_item && !last_item); /* opens first page */
 clear_seen();tap(BTN_RIGHT);draw();
 assert(list && !desc && !first_item && page2_item && last_item); /* next page */
 clear_seen();tap(BTN_LEFT);draw();
 assert(desc && !list && !last_item); /* returns to description */
 clear_seen();tap(BTN_RIGHT);draw();
 assert(first_item && !last_item); /* always reopens from first page */
 clear_seen();tap(BTN_DOWN);draw();
 assert(desc && !list && second_quest); /* changing quest resets view */
 clear_seen();tap(BTN_RIGHT);draw();
 assert(list && ordered); /* ordered quests also have checklists */
 clear_seen();tap(BTN_UP);draw();
 assert(desc && !list); /* returns to description on quest movement */
 done[0]=1;
 clear_seen();tap(BTN_RIGHT);draw();
 assert(done_label && first_item); /* live status reflects progress */
 clear_seen();tap(BTN_LEFT);tap(BTN_UP);draw();
 assert(desc && !list); /* UP even at start returns to description */
 /* Same UI must remain navigable with the HUD dock occupying 56 pixels. */
 game_adventure_quest_viewport(56,264);
 clear_seen();tap(BTN_RIGHT);draw();
 assert(list && first_item);
 clear_seen();tap(BTN_RIGHT);draw();
 assert(list && !first_item); /* reduced viewport still pages correctly */
 clear_seen();tap(BTN_LEFT);draw();
 assert(desc && !list);
 puts("PASS Stage 5.166.122 journal D-pad two-view / page / reset / docked HUD native C renderer");
 return 0;
}
''')
    exe=folder/'test'
    subprocess.run(['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(folder),str(folder/'adventureruntime.c'),str(folder/'check.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
