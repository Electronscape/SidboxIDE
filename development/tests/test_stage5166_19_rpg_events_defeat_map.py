#!/usr/bin/env python3
"""Stage 5.166.19 native runtime tests: real day/night actions, defeat menu and world-map panning."""
from pathlib import Path
import sys,tempfile,subprocess
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
from test_stage5163_rules_flow_audit import render
src=ROOT/'idelibs/codehelpers/game'
with tempfile.TemporaryDirectory(prefix='cg_rpg_16619_') as folder:
 p=Path(folder)
 render_adventure_runtime(ROOT,p)
 (p/'apis.h').write_text((ROOT/'development/tests/stage429_mock_api/apis.h').read_text().replace(
     '#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u').replace(
     '#define BTN_UP 0x02u','#define BTN_UP 0x04u').replace(
     '#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u'))
 (p/'test_adventure.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BTN_FIRE 0x01u
#define BTN_FIRE2 0x02u
#define BTN_LEFT 0x10u
#define BTN_RIGHT 0x20u
static uint32_t hp=7;
static unsigned reloads;
static uint8_t chosen;
static unsigned drawn_defeat,drawn_map;
static uint8_t reload_slot(uint8_t s){reloads++;chosen=s;return 1;}
static uint8_t exists(uint8_t s){return s==2u || s==8u;}
static uint8_t last(void){return 8u;}
static const char *current(void){return "Forest";}
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char *s){(void)x;(void)y;
  if(strstr(s,"DEFEATED"))drawn_defeat++;
  if(strstr(s,"WORLD MAP") || !strcmp(s,"Forest"))drawn_map++;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
static void input(uint8_t keys){game_adventure_input(keys,0,0,16,16,1);}
int main(void){
 game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
 game_adventure_defeat_setup(&hp,reload_slot,exists,last,1,"DEFEATED","Retry?",2,15,15,14,35,44);
 input(0);assert(!ga_defeat_open && ga_defeat_armed);
 hp=0;input(0);assert(ga_defeat_open && ga_defeat_slot==8u);
 assert(game_adventure_open());assert(game_adventure_gameplay_buttons(BTN_FIRE)==0u);
 for(int i=0;i<50;++i)input(0); /* Current death screen fades in over 50 frames. */
 game_adventure_draw(0,0,0,0);assert(drawn_defeat);
 input(BTN_FIRE);assert(reloads==1u && chosen==8u);
 input(0);input(BTN_LEFT);assert(ga_defeat_slot==3u);
 input(0);input(BTN_UP);assert(ga_defeat_slot==2u);
 input(0);input(BTN_FIRE);assert(reloads==2u && chosen==2u);
 input(0);input(BTN_FIRE2);assert(reloads==3u && chosen==8u);
 /* A successful world reload reinitialises Adventure, removing the modal. */
 game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
 assert(!ga_defeat_open);
 static const game_adventure_map_point_t points[]={{600,400,"Forest",65535u,0u},{200,120,"World1",65535u,0u}};
 game_adventure_world_map(points,2,1024,768,current);
 ga_map_open=1u;
 game_adventure_draw(0,0,0,0);assert(drawn_map>0u);
 for(int i=0;i<20;++i)input(BTN_RIGHT|BTN_DOWN);
 assert(ga_map_pan_x==80 && ga_map_pan_y==80);
 input(0);input(BTN_FIRE2);assert(!ga_map_open);
 puts("PASS Stage 5.166.19 Adventure defeat + retry slots + map panning");
 return 0;
}
''')
 subprocess.run(['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror','-I',str(p),str(p/'test_adventure.c'),'-o',str(p/'adv')],check=True)
 subprocess.run([str(p/'adv')],check=True)
 # The Adventure harness uses a minimal SDK mock. The world tests need full SDK headers.
 (p/'apis.h').unlink()
 flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,'HAS_WORLD_PHYSICS':False,'HAS_PLAYER_VISIBILITY':False, 'HAS_TITLE':False,'HAS_MAP':False}
 extra=r'''
static unsigned object_calls,npc_calls;
static uint8_t last_object_action,last_npc_action;
static void object_action(uint16_t slot,uint8_t action){assert(slot==4u);object_calls++;last_object_action=action;}
static void npc_action(uint16_t slot,uint8_t action){assert(slot==2u);npc_calls++;last_npc_action=action;}
static const gw_time_action_t day_events[]={{4u,0u,1u},{2u,1u,0u}};
static const gw_time_action_t night_events[]={{4u,0u,0u},{2u,1u,1u}};
static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);
'''
 record='''{.name="world1",.start_x=10,.start_y=20,.start_facing=1,
.day_night_mode=2,.day_night_day_frames=50,.day_night_night_frames=50,.day_night_fade_frames=25,
.day_actions=day_events,.night_actions=night_events,.day_action_count=2,.night_action_count=2,
.object_set_active=object_action,.npc_set_active=npc_action,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''
 world=render((src/'gameworlds.rulec').read_text(),flags).replace('@IDE{WORLD_DECLARATIONS}',extra)
 world=world.replace('@IDE{WORLD_RECORDS}',record).replace('@IDE{SAVE_KEY}','123').replace('@IDE{SAVE_IDENTITY}', '0x0123456789abcdef').replace('@IDE{QUEST_DATA}',
     ' #define GW_QUEST_COUNT 0u\n#define GW_OBJECTIVE_COUNT 0u\ntypedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;\ntypedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;\nstatic const gw_quest_def_t gw_quest_defs[]={{0}};\nstatic const gw_objective_def_t gw_objective_defs[]={{0}};')
 assert '@IDE{' not in world
 (p/'gameworlds.c').write_text(world)
 (p/'gameworlds.h').write_text(render((src/'gameworlds.ruleh').read_text(),flags))
 # Existing tested TFCard mock provides required low-level SDK functions.
 existing=(ROOT/'development/tests/test_stage5164_save_load_native.c').read_text()
 existing=existing[:existing.index('int main(void)')]+r'''
int main(void){
 active_world=&worlds[0];
 weather_enter(&worlds[0]);
 gw_time_phase=255u;gw_time_refresh();
 assert(object_calls==1u && npc_calls==1u && last_object_action==1u && last_npc_action==0u);
 weather_update(74);assert(object_calls==1u);
 weather_update(1);assert(object_calls==2u && last_object_action==0u && last_npc_action==1u);
 weather_update(75);assert(object_calls==3u && last_object_action==1u && last_npc_action==0u);
 weather_update(10);assert(object_calls==3u);
 /* Defeat recovery is queued, not performed from the UI or render callback. */
 mock_api.system=&systems;
 (void)mkdir(TEST_FS_ROOT,0700);
 (void)mkdir(TEST_FS_ROOT "/game",0700);
 persistent.health=15u;
 assert(gameworlds_save_slot(8u));
 assert(gameworlds_last_saved_slot()==8u);
 assert(gameworlds_reload_request(8u));
 assert(pending_reload_slot==9u && active_world==&worlds[0]);
 assert(!gameworlds_reload_request(9u));
 puts("PASS Stage 5.166.19 Day/Night events and safely queued save reload");
 return 0;
}
'''
 (p/'test_world.c').write_text(existing)
 subprocess.run(['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
                 '-I',str(p),'-I',str(ROOT/'idelibs/api'),'-I',str(src),f'-DTEST_FS_ROOT="{p}/fs"',str(p/'test_world.c'),'-o',str(p/'world')],check=True)
 subprocess.run([str(p/'world')],check=True)
# Source integration assertions for all three authoring flows.
assert 'dayActions' in (ROOT/'gamedesigner_project.cpp').read_text()
assert 'nightActions' in (ROOT/'gameworldsnapshot.h').read_text()
assert 'gw_time_%1_%2' in (ROOT/'gameworldsnapshot.h').read_text()
assert 'editGameDefeatScreen(' in (ROOT/'gamequesteditor.cpp').read_text()
assert 'editGameWorldMap(' in (ROOT/'gamequesteditor.cpp').read_text()
assert 'gameworlds_reload_request' in (src/'gameadventure.rulec').read_text()
assert 'ga_map_open' in (src/'adventureruntime.rulec').read_text()
print('PASS Stage 5.166.19 IDE/export source contracts')
