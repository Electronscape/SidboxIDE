#!/usr/bin/env python3
"""Generate actual gameworlds.rulec then run native state + save regression."""
from pathlib import Path
import subprocess, tempfile, sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from test_stage5163_rules_flow_audit import render
flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,
       'HAS_WORLD_PHYSICS':False,'HAS_PLAYER_VISIBILITY':False}
folder=ROOT/'idelibs/codehelpers/game'
quest_data='''#define GW_QUEST_COUNT 3u
#define GW_OBJECTIVE_COUNT 4u
typedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;} gw_quest_def_t;
typedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;
static const gw_quest_def_t gw_quest_defs[]={
{"demo","Door", "Door quest", "", "",0,2},
{"after","Later","Later quest","demo","",2,1},
{"side","Side","Blocked branch","","demo",3,1}};
static const gw_objective_def_t gw_objective_defs[]={
{"a","Open","event","opened_door","Try the door"},
{"b","Hold key","item","Ruby Key","Find a key"},
{"c","Talk","adventure_event","world1:42","NPC"},
{"d","Forest","world","forest","Travel"}};
'''
records='''{.name="world1",.start_x=10,.start_y=20,.start_facing=1,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''
source=render((folder/'gameworlds.rulec').read_text(),flags)
source=(source.replace('@IDE{WORLD_DECLARATIONS}',
       'static void fake_save(void (*)(const void*,uint32_t,void*),void*);\n'
       'static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);\n')
    .replace('@IDE{WORLD_RECORDS}',records)
    .replace('@IDE{SAVE_KEY}','123')
    .replace('@IDE{QUEST_DATA}',quest_data))
header=render((folder/'gameworlds.ruleh').read_text(),flags)
assert '@IDE' not in source and '@IDE' not in header
with tempfile.TemporaryDirectory(prefix='stage5165_') as tmp:
    path=Path(tmp)
    (path/'gameworlds.c').write_text(source)
    (path/'gameworlds.h').write_text(header)
    args=['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
        '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
        '-I',str(path),'-I',str(ROOT/'idelibs/api'),'-I',str(folder),
        '-I',str(ROOT/'development/tests'),f'-DTEST_FS_ROOT="{path}/fs"',
        str(ROOT/'development/tests/test_stage5165_quest_runtime.c'),'-o',str(path/'native')]
    subprocess.run(args,check=True)
    subprocess.run([str(path/'native')],check=True)
