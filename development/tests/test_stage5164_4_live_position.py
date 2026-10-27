#!/usr/bin/env python3
"""Native compiled save test: exact live-player position, not world start."""
EMPTY_QUEST_DATA = "#define GW_QUEST_COUNT 0u\n#define GW_OBJECTIVE_COUNT 0u\ntypedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;} gw_quest_def_t;\ntypedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;\nstatic const gw_quest_def_t gw_quest_defs[]={{0,0,0,0,0,0,0}};\nstatic const gw_objective_def_t gw_objective_defs[]={{0,0,0,0,0}};\n"

from pathlib import Path
import subprocess, sys, tempfile
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from test_stage5163_rules_flow_audit import render
src=ROOT/'idelibs/codehelpers/game'
flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,
       'HAS_SHARED_PLAYER':True,'HAS_WORLD_PHYSICS':False,
       'HAS_PLAYER_VISIBILITY':False}
text=render((src/'gameworlds.rulec').read_text(),flags)
record='''{.name="world1",.start_x=10,.start_y=20,.start_facing=1,.map=(void*)0x1234,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''
text=text.replace('@IDE{WORLD_DECLARATIONS}', '''static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);
''').replace('@IDE{WORLD_RECORDS}',record).replace('@IDE{SAVE_KEY}','123').replace('@IDE{QUEST_DATA}',EMPTY_QUEST_DATA)
header=render((src/'gameworlds.ruleh').read_text(),flags)
with tempfile.TemporaryDirectory(prefix='cg5164_4_player_') as td:
    p=Path(td)
    (p/'gameworlds.c').write_text(text)
    (p/'gameworlds.h').write_text(header)
    (p/'gametilemap.h').write_text((src/'tilemap.h').read_text())
    (p/'gameplayer.h').write_text('''#ifndef CG_TEST_PLAYER\n#define CG_TEST_PLAYER\n#include "gametilemap.h"\nextern gfxbob_t gameplayer_sprite;\nuint8_t gameplayer_apply_physics(game_tile_player_t *p, uint8_t id);\nuint16_t gameplayer_custom_stat_count(void);\nconst char *gameplayer_custom_stat_name(uint16_t i);\nuint8_t gameplayer_stat_get(const char *n, int32_t *v);\nuint8_t gameplayer_stat_set(const char *n, int32_t v);\n#endif\n''')
    native=(ROOT/'development/tests/test_stage5164_save_load_native.c').read_text()
    native=native.replace('static int32_t fake_data=77;', '''static int32_t fake_data=77;
static game_tile_player_t fake_player;
static gfxbob_t fake_sprite;
static uint8_t player_available=1;
gfxbob_t gameplayer_sprite;
const game_tile_player_t *game_tile_player_current(void) {
    return player_available ? &fake_player : NULL;
}
uint8_t gameplayer_apply_physics(game_tile_player_t *p,uint8_t profile) {
    (void)p;(void)profile;return 1;
}
uint16_t gameplayer_custom_stat_count(void){return 0;}
const char *gameplayer_custom_stat_name(uint16_t i){(void)i;return NULL;}
uint8_t gameplayer_stat_get(const char *n,int32_t *v){(void)n;(void)v;return 0;}
uint8_t gameplayer_stat_set(const char *n,int32_t v){(void)n;(void)v;return 0;}''')
    native=native.replace('    active_world=&worlds[0];persistent.health=45;persistent.lives=3;', '''    active_world=&worlds[0];persistent.health=45;persistent.lives=3;
    fake_player.map=(const game_tilemap_t*)0x1234;
    fake_player.sprite=&fake_sprite;
    fake_player.x100=17300;
    fake_player.y100=24500;
    fake_sprite.flags=BLIT_FLAG_FLIP_X;''')
    native=native.replace('    assert(gameworlds_save_slot(0)); assert(gameworlds_slot_exists(0));', '''    assert(gameworlds_save_slot(0)); assert(gameworlds_slot_exists(0));
    player_available=0;
    assert(!gameworlds_save_slot(0)); /* Refuse false checkpoint at world start. */
    player_available=1;''')
    native=native.replace('    assert(gameworlds_player_start(&position) && position.x==10 && position.y==20);', '''    assert(gameworlds_player_start(&position) && position.x==173 && position.y==245 && position.facing==0);''')
    (p/'native.c').write_text(native)
    executable=p/'native'
    subprocess.run(['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
                    '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
                    '-I',str(p),'-I',str(ROOT/'idelibs/api'),'-I',str(src),
                    f'-DTEST_FS_ROOT="{p}/fs"',str(p/'native.c'),'-o',str(executable)],check=True)
    subprocess.run([str(executable)],check=True)
print('PASS Stage 5.164.4: live XY/facing restored; unregistered player refuses save')
