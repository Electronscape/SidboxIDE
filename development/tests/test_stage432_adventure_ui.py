#!/usr/bin/env python3
"""Stage 4.32 UI/codegen contract checks; full Qt6 build done by user."""
from pathlib import Path
base=Path(__file__).resolve().parents[2]
ui=(base/'gameadventureeditor.cpp').read_text()
gen=(base/'gameadventuregen.cpp').read_text()
run=(base/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
header=(base/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
for name in ('dialogX','dialogY','dialogWidth','dialogHeight','Dialogue Position',
             'AdventureDialoguePositionPreview','Drag the yellow','screenPreview->moved',
             "Remove '%1' from Adventure NPCs?", 'QMessageBox::No',
             'QListView::IconMode','LIVE PREVIEW', 'Foreground colours',
             'fields[i].label->toPlainText().left(180)',
             'fields[i].reply->toPlainText().left(150)'):
    assert name in ui, f'UI missing {name}'
for name in (
             'quoted(choice.value("text").toString().left(180))',
             'quoted(choice.value("reply").toString().left(150))'):
    assert name in gen, f'generator missing {name}'
assert 'game_adventure_dialogue_box(' in header
assert '@IDE{DIALOG_X}' in run and '@IDE{DIALOG_WIDTH}' in run
assert ('ga_wrapped(node->choices[i].label,' in run or 'ga_wrapped(c->label,' in run)
assert 'const int bubble_h=18+' in run
assert 'const int y = 249 + i * 20' not in run
print('Stage4.32 UI & generator source checks PASS')
