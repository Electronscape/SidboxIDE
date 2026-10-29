#!/usr/bin/env python3
"""Source guard for Stage 5.166.78 modal destination tree and graph isolation.

This is a static UI contract check. Desktop Qt interaction must be tested in IDE.
"""
from pathlib import Path
p=Path(__file__).resolve().parents[2]
s=(p/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (p/'splashscreenwidget.cpp').read_text()
combo=s[s.index('class ConversationTreeCombo final'):s.index('class NodeFoldButton final')]
assert 'void showPopup() override' in combo
assert 'chooseDestination(selected,&selected)' in combo
assert 'if (!chooseDestination(selected,&selected))return;' in combo
assert 'findData(selected)' in combo and 'setCurrentIndex(row)' in combo
card=s[s.index('void makeConversationCard('):s.index('void rebuildConversationFlow()')]
assert 'new ConversationTreeCombo(panel)' in card
assert 'browseConversationDestination(current,chosen)' in card
assert 'next->view()->setMinimumWidth' not in card
assert 'next->addItem(label,target)' in card
assert 'next->addItem(tr("Close conversation"),-1)' in card
assert 'MISSING dialogue #%1' in card
assert 'next->currentData().toInt()' in card
selector=s[s.index('bool browseConversationDestination('):s.index('int browseDialogueTree(')]
for term in ('QDialog browser(this);','browser.setWindowModality(Qt::ApplicationModal)',
             'QTreeWidget(&browser)','populateDialogueChoices(tree,root,false)',
             'Search folder, speaker or dialogue text...','QDialogButtonBox::Ok | QDialogButtonBox::Cancel',
             'browser.exec()','@close-conversation','@dialogue-node:',
             'MISSING dialogue #%1','browser.accept()','browser.exec()!=QDialog::Accepted',
             'if(!valid || value<0 || value>=m_dialogues.size())return false;'):
    assert term in selector,term
folders=s[s.index('void populateDialogueChoices('):s.index('bool browseConversationDestination(')]
assert 'parentId' in folders and 'folderId' in folders
assert 'if (allowCreate)' in folders and '+ Create New Dialogue' in folders
assert 'Dialogue #%1\\nSpeaker: %2\\nText: %3' in folders
assert '.simplified()' in folders
# This must remain a graphics/editor-only update.
assert 'm_dialogues.replace(index,node)' in s
assert 'm_dialogues.append' not in selector
assert 'gameworlditems_sync_logic()' not in selector
print('PASS modal tree picker, z-order fix, folder/search/close/missing/cancel, numeric links')
