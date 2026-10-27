#!/usr/bin/env python3
"""5.166.13: actual authored quest preview, legacy slot-safe icon removal."""
from pathlib import Path
import sys
ROOT=Path(__file__).resolve().parents[2]
editor=(ROOT/'gamequestjournaleditor.cpp').read_text()
runtime=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
header=(ROOT/'gamequesteditor.h').read_text()
questeditor=(ROOT/'gamequesteditor.cpp').read_text()
generator=(ROOT/'gameadventuregen.cpp').read_text()
assert 'const int desc_y=panel_y+header+8;' in runtime
assert 'const int desc_y=y+header+8;' in runtime
assert 'ga_quest_draw_icon_slot(2u' not in runtime
assert 'ga_quest_label(title_text_x' not in runtime
assert 'ga_quest_label(list_x+20,line_y,ga_quest_ui->title(index),title_cols)' in runtime
assert 'const int descY=y+headerBottom+8;' in editor
assert 'drawIcon(2,' not in editor
assert 'No quests yet.' in editor
assert 'projectQuests(projectRoot,&error)' in editor
assert '.codergirl/quests.json' in editor
for key in ('"quests"','"title"','"description"','"objectives"','"initiallyHidden"'):
    assert key in editor, key
assert 'questPreviewChoice->addItem(quest.title+' in editor
assert 'preview->selectedQuest=index;' in editor
assert 'selectedDescription=quests.isEmpty()?QString():quests.at(selected).description;' in editor
assert 'selectedObjective=quests.isEmpty()?QString():quests.at(selected).objective;' in editor
assert 'previewScroll->setRange(0,63)' in editor
assert 'descriptionScroll' in editor
assert 'iconLabel->hide()' in editor and 'partsWidget->hide()' in editor
assert 'iconChosen[2]=65535;' in editor
assert 'const int index=i==2?65535:' in generator
assert 'const bool composite=i!=2 &&' in generator
assert 'iconTwoByTwo[2]->setChecked(false);' in editor
assert 'const QString &selectQuestId = QString()' in header
assert 'questList->setCurrentRow(first);' in questeditor
assert 'questPreviewChoice->currentData().toString()' in editor
assert 'Build: 5.166.13.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
print('PASS 5.166.13 genuine quest preview, objective, hidden selection, icon ABI and editor shortcut contracts')
