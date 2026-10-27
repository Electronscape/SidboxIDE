#!/usr/bin/env python3
"""Stage 5.165.3 automatic dialogue IDs: source contracts + native generated runtime."""
from pathlib import Path
import subprocess, tempfile, sys
ROOT=Path(__file__).resolve().parents[2]
read=lambda rel:(ROOT/rel).read_text()
editor=read('gamequesteditor.cpp')
adv=read('gameadventureeditor.cpp')
gen=read('gameadventuregen.cpp')
world=read('idelibs/codehelpers/game/gameworlds.rulec')
world_h=read('idelibs/codehelpers/game/gameworlds.ruleh')
adv_rt=read('idelibs/codehelpers/game/adventureruntime.rulec')
adv_rt_h=read('idelibs/codehelpers/game/adventureruntime.ruleh')
adv_world=read('idelibs/codehelpers/game/gameadventure.rulec')
flow=read('gamefloweditor.cpp')
assert 'Build: 5.166.12.271026' in read('splashscreenwidget.cpp')
assert 'QSaveFile upgraded(world.filePath)' in editor
assert 'current.readAll()!=world.original' in editor
assert 'game_adventure_set_choice_signal(on_quest_choice)' in adv_world
assert 'ga_choice_signal(node,choice);' in adv_rt
assert adv_rt.index('ga_choice_signal(node,choice);')>adv_rt.index('static void ga_success_choice(')
assert adv_rt.index('ga_choice_signal(node,choice);')<adv_rt.index('static void ga_offer_item(')
assert 'void game_adventure_set_choice_signal' in adv_rt_h
assert 'questChoiceId' in adv and 'questChoiceId' in gen
assert 'QUEST_CHOICE_TOKENS' in adv_world and 'QUEST_CHOICE_TOKENS' in gen
assert 'dialogue_choice' in read('gamequestgen.h') and 'dialogue_choice' in editor
assert 'kind==QStringLiteral("dialogue_choice")' in flow
assert 'gameworlds_quest_dialogue_choice(id);' in adv_world
assert 'gameworlds_quest_dialogue_choice(' in world_h
assert 'strcmp(o->kind,"dialogue_choice")' in world
# Older numeric custom events and Game Object action paths MUST remain untouched.
assert 'gameworlds_quest_event_number(event_id);' in adv_world
assert 'if (c->action >= 0 && ga_action) ga_action' in adv_rt
# Emitted dialogue tokens are tied to answer IDs, not floating numeric action IDs.
assert 'choice.value(QStringLiteral("questChoiceId"))' in gen
assert 'choice.value("targetObjectId")' in gen

sys.path.insert(0,str(ROOT/'development/tests'))
from test_stage5163_rules_flow_audit import render
folder=ROOT/'idelibs/codehelpers/game'
flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,
       'HAS_WORLD_PHYSICS':False,'HAS_PLAYER_VISIBILITY':False, 'HAS_TITLE':False}
quest_data='''#define GW_QUEST_COUNT 1u
#define GW_OBJECTIVE_COUNT 1u
typedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;
typedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;
static const gw_quest_def_t gw_quest_defs[]={ {"q","Quest","","","",0,1} };
static const gw_objective_def_t gw_objective_defs[]={ {"o","Talk","dialogue_choice","world1:dlg_abcdef",""} };
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
native='''#define main previous_save_suite
#include "test_stage5164_save_load_native.c"
#undef main
int main(void) {
    active_world=&worlds[0];gw_quest_reset();
    assert(gameworlds_quest_status(0)==1);
    assert(gameworlds_quest_dialogue_choice("not_a_choice")==0);
    assert(gameworlds_quest_status(0)==1);
    assert(gameworlds_quest_dialogue_choice("dlg_abcdef")==1);
    assert(gameworlds_quest_status(0)==2);
    assert(gameworlds_quest_dialogue_choice("dlg_abcdef")==0);
    puts("PASS native stable dialogue quest callbacks");return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage5165_3_') as tmp:
    path=Path(tmp)
    (path/'gameworlds.c').write_text(source)
    (path/'gameworlds.h').write_text(header)
    (path/'native.c').write_text(native)
    args=['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
        '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
        '-I',str(path),'-I',str(ROOT/'idelibs/api'),'-I',str(folder),
        '-I',str(ROOT/'development/tests'),f'-DTEST_FS_ROOT="{path}/fs"',
        str(path/'native.c'),'-o',str(path/'native')]
    subprocess.run(args,check=True)
    subprocess.run([str(path/'native')],check=True)
print('PASS Stage 5.165.3: stable ID editor/generator/flow, manual event compatibility, native quest advancement')
