#!/usr/bin/env python3
"""Legacy journal contracts, updated to Stage 5.166.3 independent skin."""
from pathlib import Path
import subprocess
R=Path(__file__).resolve().parents[2]
source=lambda p:(R/p).read_text()
editor=source('gamequestjournaleditor.cpp')
quest=source('gamequesteditor.cpp')
gen=source('gameadventuregen.cpp')
template=source('idelibs/codehelpers/game/gameadventure.rulec')
world=source('idelibs/codehelpers/game/gameworlds.rulec')
header=source('idelibs/codehelpers/game/gameworlds.ruleh')
adventure=source('idelibs/codehelpers/game/adventureruntime.rulec')
assert 'gamequestjournaleditor.cpp' in source('CMakeLists.txt')
assert 'Journal Appearance...' in quest and 'editGameQuestJournal' in quest
assert 'QSaveFile out(path)' in editor
assert '.codergirl/quest-journal.json' in editor and '.codergirl/quest-journal.json' in gen
assert 'journalConfig.lastModified()>generatedAdventure.lastModified()' in source('mainwindow.cpp')
assert 'gameworlds_ui_full_brightness' in header and world and template
assert 'if(ga_modal_fullbright)ga_modal_fullbright();' in adventure
assert 'if (!ga_state && !ga_quest_open) return;' in adventure
assert '/* Touches on an open journal have NO function. */' in adventure
assert 'GA_QUEST_GETXY(&x,&y)' not in adventure
for token in ['QUEST_MARGIN','QUEST_SPLIT','QUEST_BG','QUEST_BORDER','QUEST_TEXT','QUEST_HIGHLIGHT','QUEST_ATLAS_PATH','QUEST_CELLS','QUEST_FLIPS']:
    assert '@IDE{'+token+'}' in template,token
    assert '"'+token+'"' in gen,token
assert '@IDE_IF{HAS_PROJECT_HUD}' in template
assert '"HAS_PROJECT_HUD"' in gen
assert 'game_adventure_quest_viewport(0u,' in template
assert 'Build: 5.166.5.271026' in source('splashscreenwidget.cpp')
subprocess.run(['python3',str(R/'development/tests/test_stage5166_touch_journal.py')],check=True)
print('PASS Stage 5.166.2 editor, generated style, HUD-safe rendering, modal palette')
