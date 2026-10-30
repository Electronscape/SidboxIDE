#!/usr/bin/env python3
"""Native tests for Stage 5.166.22 death fade/session and world reload."""
from pathlib import Path
import sys, subprocess, tempfile
root=Path(__file__).resolve().parents[2];sys.path.insert(0,str(root/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
from test_stage5163_rules_flow_audit import render
src=root/'idelibs/codehelpers/game'
with tempfile.TemporaryDirectory(prefix='cg16622_') as folder:
 p=Path(folder);render_adventure_runtime(root,p)
 (p/'apis.h').write_text((root/'development/tests/stage429_mock_api/apis.h').read_text().replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u').replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u').replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u'))
 (p/'test_ui.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BTN_FIRE 0x01u
#define BTN_FIRE2 0x02u
static uint32_t health=5u;
static uint8_t allowed=0u,reruns=0u,reloads=0u,last_brightness=255u;
static int footer_y=-1,first_y=900;
static uint8_t saved_exists(uint8_t s){return s==4u;}
static uint8_t reload_slot(uint8_t s){assert(s==4u);++reloads;return 1u;}
static uint8_t last_saved(void){return 4u;}
static uint8_t can_load(void){return allowed;}
static uint8_t restart(void){++reruns;return 1u;}
static void fade(uint8_t brightness){last_brightness=brightness;}
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char *s){(void)x;
    assert(strcmp(s,"CHOOSE SAVE TO RELOAD")!=0);
    if(y<first_y)first_y=y;
    if(strstr(s,"FIRE1")||strstr(s,"NO CHECKPOINT"))footer_y=y;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
static void keys(uint8_t button){game_adventure_input(button,0,0,16,16,1);}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_defeat_setup(&health,reload_slot,saved_exists,last_saved,1u,"YOU ARE DEAD","Retry",2,15,15,14,50,40);
    game_adventure_defeat_session(can_load,restart,fade);
    game_adventure_quest_viewport(48u,272u);
    keys(0);health=0;keys(0);
    assert(ga_defeat_open && !ga_defeat_occupied[4]);
    ga_defeat_window();assert(last_brightness>220u);
    for(int n=0;n<24;++n)keys(0);
    ga_defeat_window();assert(last_brightness==0u);
    for(int n=0;n<25;++n)keys(0);
    ga_defeat_window();assert(last_brightness==255u);
    assert(footer_y>=48 && footer_y+16<=320 && first_y>=48);
    keys(BTN_FIRE);assert(reruns==1u && reloads==0u);
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_defeat_setup(&health,reload_slot,saved_exists,last_saved,1u,"YOU ARE DEAD","Retry",2,15,15,14,50,40);
    game_adventure_defeat_session(can_load,restart,fade);
    allowed=1u;health=5u;keys(0);health=0;keys(0);
    assert(ga_defeat_occupied[4] && ga_defeat_slot==4u);
    for(int n=0;n<50;++n)keys(0);
    keys(BTN_FIRE);assert(reloads==1u && reruns==1u);
    puts("PASS Stage 5.166.22 native fade, HUD clearance, fresh-session policy");
}
''')
 subprocess.run(['gcc','-std=gnu11','-Wall','-Wextra','-Werror','-I',str(p),str(p/'test_ui.c'),'-o',str(p/'ui')],check=True)
 subprocess.run([str(p/'ui')],check=True)
 (p/'apis.h').unlink()
 flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,'HAS_WORLD_PHYSICS':False,'HAS_PLAYER_VISIBILITY':False, 'HAS_TITLE':False,'HAS_MAP':False}
 extra='''static int init(void){return 1;}static void shutdown(void){}static uint8_t objects_init(void){return 1;}
static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);'''
 record='''{.name="world1",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objects_init,
.start_x=10,.start_y=20,.start_facing=1,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''
 world=render((src/'gameworlds.rulec').read_text(),flags).replace('@IDE{WORLD_DECLARATIONS}',extra)
 world=world.replace('@IDE{WORLD_RECORDS}',record).replace('@IDE{SAVE_KEY}','123').replace('@IDE{SAVE_IDENTITY}', '0x0123456789abcdef').replace('@IDE{QUEST_DATA}',
     ' #define GW_QUEST_COUNT 0u\n#define GW_OBJECTIVE_COUNT 0u\ntypedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;\ntypedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;\nstatic const gw_quest_def_t gw_quest_defs[]={{0}};\nstatic const gw_objective_def_t gw_objective_defs[]={{0}};')
 assert '@IDE{' not in world
 (p/'gameworlds.c').write_text(world)
 (p/'gameworlds.h').write_text(render((src/'gameworlds.ruleh').read_text(),flags))
 fixture=(root/'development/tests/test_stage5164_save_load_native.c').read_text()
 fixture=fixture[:fixture.index('int main(void)')].replace('#include "gameworlds.c"', '#undef music_stop\n#define music_stop() ((void)0)\n#include "gameworlds.c"')+r'''
int main(void){
 mock_api.system=&systems;
 (void)mkdir(TEST_FS_ROOT,0700);(void)mkdir(TEST_FS_ROOT "/game",0700);
 active_world=&worlds[0];gameworlds_fresh_start_enable(1u);
 persistent.health=5u;fake_data=15;
 assert(!gameworlds_session_can_reload());
 gameworlds_update_gameplay(1u);
 assert(gw_fresh_bytes && gw_fresh_length>0);
 fake_data=99;persistent.health=0u;
 assert(gameworlds_restart_request());
 assert(gameworlds_apply_pending());
 assert(fake_data==15 && persistent.health==5u && gw_reload_revision==1u);
 assert(gameworlds_player_start(&saved_position) && saved_position.x==10);
 assert(!gameworlds_session_can_reload());
 assert(gameworlds_save_slot(4u));
 assert(gameworlds_session_can_reload() && !gw_fresh_bytes);
 fake_data=777;persistent.health=0;
 assert(gameworlds_reload_request(4u));
 assert(gameworlds_apply_pending());
 assert(fake_data==15 && persistent.health==5u && gw_reload_revision==2u);
 assert(!gameworlds_restart_request());
 gameworlds_shutdown();
 puts("PASS Stage 5.166.22 native fresh snapshot + checkpoint world recovery");
}
'''
 (p/'test_world.c').write_text(fixture)
 cmd=['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
       '-I',str(p),'-I',str(root/'idelibs/api'),'-I',str(src),f'-DTEST_FS_ROOT="{p}/fs"',str(p/'test_world.c'),'-o',str(p/'world')]
 subprocess.run(cmd,check=True)
 subprocess.run([str(p/'world')],check=True)
ui=(root/'gamerpguieditors.h').read_text()
for item in ('Fill empty cells with selected tile','Flood fill bucket (click to arm)','cgRpgChooseCell(&dialog,sheet','flagChoose','pending.takeLast()'):
 assert item in ui,item
worldsrc=(src/'gameworlds.rulec').read_text()
assert 'live->sprite->drawx=(int16_t)saved_position.x;' in worldsrc
assert 'game_tile_player_reset(live,' in worldsrc
assert 'gameworlds_reload_revision' in (src/'maingame.rulec').read_text()
assert 'threshold[16]' not in (src/'adventureruntime.rulec').read_text()[(src/'adventureruntime.rulec').read_text().index('static void ga_defeat_window(void)'):]
print('PASS Stage 5.166.22 static map-fill and same-world physics hooks')
