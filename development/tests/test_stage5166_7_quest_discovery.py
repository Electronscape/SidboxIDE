#!/usr/bin/env python3
"""Native quest discovery, persistent pending offer, and source wiring checks."""
from pathlib import Path
import subprocess,tempfile,sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from test_stage5163_rules_flow_audit import render
flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,
       'HAS_WORLD_PHYSICS':False,'HAS_PLAYER_VISIBILITY':False}
folder=ROOT/'idelibs/codehelpers/game'
data='''#define GW_QUEST_COUNT 2u
#define GW_OBJECTIVE_COUNT 2u
typedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;
typedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;
static const gw_quest_def_t gw_quest_defs[]={
  {"main","Starter","","","",0,1,0u},
  {"future","Future Kim's Flower","","main","",1,1,1u}
};
static const gw_objective_def_t gw_objective_defs[]={
  {"step1","Speak","event","starter_done",""},
  {"step2","Bring flower","event","flower_found",""}
};
'''
record='''{.name="world1",.start_x=10,.start_y=20,.start_facing=1,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''
source=render((folder/'gameworlds.rulec').read_text(),flags)
source=(source.replace('@IDE{WORLD_DECLARATIONS}',
       'static void fake_save(void (*)(const void*,uint32_t,void*),void*);\n'
       'static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);\n')
    .replace('@IDE{WORLD_RECORDS}',record)
    .replace('@IDE{SAVE_KEY}','123')
    .replace('@IDE{QUEST_DATA}',data))
header=render((folder/'gameworlds.ruleh').read_text(),flags)
assert '@IDE' not in source and '@IDE' not in header
assert 'questNodeEnableIds' in (ROOT/'gameadventuregen.cpp').read_text()
assert 'game_adventure_set_node_signal(on_quest_node)' in (folder/'gameadventure.rulec').read_text()
assert 'dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);' in (ROOT/'gameadventureeditor.cpp').read_text()
assert 'class QuestDialogueTreeCombo' in (ROOT/'gamequesteditor.cpp').read_text()
assert 'dialogueKey(entry.name,ni)' in (ROOT/'gamefloweditor.cpp').read_text()
assert 'Build: 5.166.12.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
with tempfile.TemporaryDirectory(prefix='quest_discovery_') as tmp:
    path=Path(tmp)
    (path/'gameworlds.c').write_text(source)
    (path/'gameworlds.h').write_text(header)
    (path/'test.c').write_text('''
#define main legacy_main
#include "test_stage5164_save_load_native.c"
#undef main
int main(void) {
    mock_api.system=&systems;
    (void)mkdir(TEST_FS_ROOT,0700);(void)mkdir(TEST_FS_ROOT "/game",0700);
    active_world=&worlds[0];gw_quest_reset();
    assert(gameworlds_quest_status(0)==1u);
    assert(gameworlds_quest_status(1)==0u);
    assert(!gameworlds_quest_visible(1));
    assert(!gameworlds_quest_event("flower_found"));
    assert(gameworlds_quest_enable("future")==1u);
    assert(gameworlds_quest_status(1)==4u);
    assert(gameworlds_quest_visible(1));
    assert(gameworlds_quest_enable("future")==0u);
    assert(gameworlds_save_slot(5));
    active_world=0;gw_quest_reset();
    assert(gameworlds_load_slot(5));
    assert(gameworlds_quest_status(1)==4u);
    active_world=&worlds[0];
    assert(gameworlds_quest_event("starter_done")==1u);
    assert(gameworlds_quest_status(0)==2u);
    assert(gameworlds_quest_status(1)==1u);
    assert(gameworlds_quest_event("flower_found")==1u);
    assert(gameworlds_quest_status(1)==2u);
    assert(gameworlds_quest_enable("future")==0u);
    assert(gw_quest_step[1]==1u);
    puts("PASS Stage 5.166.7 hidden quest offer, prerequisite, TFCard save and completion");
    return 0;
}
''')
    exe=path/'test'
    cmd=['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
         '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
         '-I',str(path),'-I',str(ROOT/'idelibs/api'),'-I',str(folder),
         '-I',str(ROOT/'development/tests'),f'-DTEST_FS_ROOT="{path}/fs"',
         str(path/'test.c'),'-o',str(exe)]
    subprocess.run(cmd,check=True)
    subprocess.run([str(exe)],check=True)
