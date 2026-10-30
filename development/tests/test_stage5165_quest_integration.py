#!/usr/bin/env python3
"""Stage 5.165 build/editor/rule contracts; native C in separate test."""
from pathlib import Path
import subprocess
R=Path(__file__).resolve().parents[2]
read=lambda p:(R/p).read_text()
editor=read('gamequesteditor.cpp')
generator=read('gamequestgen.h')
snapshot=read('gameworldsnapshot.h')
world=read('idelibs/codehelpers/game/gameworlds.rulec')
header=read('idelibs/codehelpers/game/gameworlds.ruleh')
flow=read('gamefloweditor.cpp')
assert 'editGameQuests(this,QFileInfo(m_filePath).absolutePath()' in read('gamedesigner.cpp')
assert 'gamequesteditor.cpp' in read('CMakeLists.txt')
assert '.codergirl/quests.json' in editor and '.codergirl/quests.json' in generator
assert 'QSaveFile file(path)' in editor
assert 'Quest prerequisites contain a cycle' in editor
assert 'GameQuestGen::read(project,&projectQuests,error)' in snapshot
assert 'generated.replace("@IDE{QUEST_DATA}",GameQuestGen::generateData(projectQuests))' in snapshot
assert '@IDE{QUEST_DATA}' in world
for token in ['gameworlds_quest_track(', 'gameworlds_quest_event(',
              'gameworlds_quest_event_number(', 'gw_quest_reset()',
              'gw_quest_refresh()', 'GW_SAVE_VERSION 3u',
              'temp.version!=GW_SAVE_VERSION', 'questData.schema!=gw_quest_schema()',
              'gw_save_take(&questData', 'GW_WRITE(questData)']:
    assert token in world,token
for token in ['gameworlds_quest_current_step(', 'gameworlds_quest_tracked(',
              'gameworlds_quest_hint(']:assert token in header,token
assert 'gameworlds_quest_event_number(event_id);' in read('idelibs/codehelpers/game/gameadventure.rulec')
for token in ['Quest Objective','Quest Event','Enter world','Shared backpack',
              'Adventure event received','Unlock on completion','Exclude on completion']:
    assert token in flow,token
assert 'questConfig.lastModified()>worldManager.lastModified()' in read('mainwindow.cpp')
assert 'Build: 5.166.111.1.291026' in read('splashscreenwidget.cpp')
subprocess.run(['python3',str(R/'development/tests/test_stage5165_quest_runtime.py')],check=True)
subprocess.run(['python3',str(R/'development/tests/test_stage5164_3_multiworld_public_save_api.py')],check=True)
print('PASS Stage 5.165: quest editor, generator, flow, save compatibility, stale-build hooks')
