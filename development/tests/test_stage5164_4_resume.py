#!/usr/bin/env python3
"""Stage 5.164.4: real-save origin, legacy title-startup and title CLUT styling."""
EMPTY_QUEST_DATA = "#define GW_QUEST_COUNT 0u\n#define GW_OBJECTIVE_COUNT 0u\ntypedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;} gw_quest_def_t;\ntypedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;\nstatic const gw_quest_def_t gw_quest_defs[]={{0,0,0,0,0,0,0}};\nstatic const gw_objective_def_t gw_objective_defs[]={{0,0,0,0,0}};\n"

from pathlib import Path
import subprocess, sys, tempfile
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT/'development/tests'))
from test_stage5163_rules_flow_audit import render
folder=ROOT/'idelibs/codehelpers/game'
world=(folder/'gameworlds.rulec').read_text()
title=(folder/'gametitle-runtime.rulec').read_text()
assert 'gfx_setcolour(15)' not in title.split('static void title_load_frame(',1)[1].split('static void title_options_frame(',1)[0]
for token in ('style=title_menu[i].art','title_draw_art(&art)','title_draw_selector(&art,1)','title_draw_selector(&art,0)',
              'gameworlds_request_at(title_load_marker,"default")'):
    assert token in title,token
assert 'name=gameworlds_saved_world();' in world
assert 'if (!saved_position_valid && !gameworlds_load_slot(slot)) return 0;' in world
assert 'game_tile_player_current()' in world
assert 'stream->failed=1;' in world.split('const game_tile_player_t *live=',1)[1].split('@IDE_END',1)[0]
tile=(folder/'tilemap.c').read_text()
assert 'cg_live_player=p;' in tile
assert 'const game_tile_player_t *game_tile_player_current(void)' in tile
ui=(ROOT/'gamedesigner.cpp').read_text()
assert 'existingC.contains("game_tile_player_current(void)")' in ui
assert 'existingH.contains("game_tile_player_current(void)")' in ui
# Actual compiled two-world title marker -> saved-world restoration, even if
# hand-maintained main.c ignores the marker and starts a default world.
flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,
       'HAS_SHARED_PLAYER':False,'HAS_WORLD_PHYSICS':False,
       'HAS_PLAYER_VISIBILITY':False}
source=render(world,flags)
functions='''static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);
static int fake_assets_init(void);
static void fake_assets_shutdown(void);
static uint8_t fake_objects_init(void);
'''
record=lambda name: '''{.name="%s",.start_x=10,.start_y=20,.start_facing=1,
.assets_init=fake_assets_init,.assets_shutdown=fake_assets_shutdown,
.objects_init=fake_objects_init,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''%name
source=source.replace('@IDE{WORLD_DECLARATIONS}',functions).replace('@IDE{WORLD_RECORDS}',record('world1')+','+record('forest')).replace('@IDE{SAVE_KEY}','123').replace('@IDE{QUEST_DATA}',EMPTY_QUEST_DATA)
header=render((folder/'gameworlds.ruleh').read_text(),flags)
assert '@IDE' not in source
with tempfile.TemporaryDirectory(prefix='cg5164_4_') as directory:
    temp=Path(directory)
    (temp/'gameworlds.c').write_text(source)
    (temp/'gameworlds.h').write_text(header)
    fixture=(ROOT/'development/tests/test_stage5164_save_load_native.c').read_text()
    fixture=fixture.replace('static int32_t fake_data=77;', '''static int32_t fake_data=77;
static int fake_assets_init(void){return 1;}
static void fake_assets_shutdown(void){}
static uint8_t fake_objects_init(void){return 1;}''')
    marker='''    /* Recompute the checksum after malicious structural corruption'''
    assertion='''    /* Legacy main.c calls start(DEFAULT) and discards the title marker.
       The saved world must still win, with the saved position intact. */
    active_world=NULL;
    saved_position_valid=0;
    inventory_count=0;
    assert(gameworlds_request_at("__CGSAVE0__","default"));
    assert(gameworlds_start("forest"));
    assert(strcmp(gameworlds_active(),"world1")==0);
    gameworlds_spawn_t restored={0};
    assert(gameworlds_player_start(&restored) && restored.x==10 && restored.y==20);
    '''
    assert marker in fixture
    fixture=fixture.replace(marker,assertion+marker)
    (temp/'native.c').write_text(fixture)
    executable=temp/'native'
    subprocess.run(['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
                    '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
                    '-I',str(temp),'-I',str(ROOT/'idelibs/api'),'-I',str(folder),
                    f'-DTEST_FS_ROOT="{temp}/fs"',str(temp/'native.c'),'-o',str(executable)],check=True)
    subprocess.run([str(executable)],check=True)
print('PASS Stage 5.164.4: load screen styling and legacy save-selection restoration')
