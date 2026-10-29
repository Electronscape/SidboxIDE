#!/usr/bin/env python3
"""Stage 5.166.72: NPC graph edits the real Adventure NPC association.

Source contract checks, not a substitute for compiling Qt and interacting with
NPC cards on a desktop. Actual graph action generation is regression-tested by
existing independent-logic/Show Dialogue tests.
"""
from pathlib import Path
import re
R=Path(__file__).resolve().parents[2]
visual=(R/'gamevisualnodes.cpp').read_text()
adventure_ui=(R/'gameadventureeditor.cpp').read_text()
adventure_gen=(R/'gameadventuregen.cpp').read_text()
assert 'Build: 5.166.99.291026' in (R/'splashscreenwidget.cpp').read_text()

# Direct mapping, no new data model: reuse all four Adventure NPC properties.
for field,name in (('node','npcStartNode'),('doneNode','npcDoneNode'),
                   ('radius','npcRadius'),('initiallyVisible','npcInitiallyVisible')):
    assert f'node.{name}=npcValue.toObject().value(QStringLiteral("{field}"))' in visual
    assert f'field==QStringLiteral("{field}")' in visual
    assert f'"{field}"' in adventure_ui
    assert f'"{field}"' in adventure_gen
assert 'node.id=id;' in visual
assert 'npcValue.toObject().value(QStringLiteral("spriteId"))' in visual
assert 'm_npcEntries=adventure.value(QStringLiteral("npcs")).toArray()' in visual
assert 'updateNpcProperty(id,QStringLiteral("node")' in visual
assert 'updateNpcProperty(id,QStringLiteral("doneNode")' in visual
assert 'updateNpcProperty(id,QStringLiteral("initiallyVisible")' in visual
assert 'updateNpcProperty(id,QStringLiteral("radius")' in visual
assert 'new QSpinBox(panel)' in visual
assert 'startBrowse,&QPushButton::clicked' in visual
assert 'doneBrowse,&QPushButton::clicked' in visual
assert 'browseDialogueTree(m_objects.value(id).npcStartNode)' in visual
assert 'browseDialogueTree(m_objects.value(id).npcDoneNode)' in visual

# The picker exposes NPC conversations but resolves them back to the existing
# Adventure dialogue ID, through the pre-existing TRUE/FALSE dialogue handlers.
picker=visual[visual.index('void showInsertTree('):visual.index('void appendConnection(')]
assert 'tr("NPC Conversations")' in picker
assert 'tr("Opening: %1")' in picker
assert 'tr("After helped: %1")' in picker
assert '@npc-dialogue:start:' in picker
assert '@npc-dialogue:helped:' in picker
resolve=picker.index('selectedId=QStringLiteral("@dialogue-node:%1").arg(dialogue)')
existing=picker.index('if (selectedId.startsWith(QStringLiteral("@dialogue-node:")))')
assert resolve<existing
assert 'setGraphDialogue(key,yes,index,at)' in picker
assert 'setBranchDialogue(from.mid(prefix.size()),yes,index,at)' in picker
assert 'connectExistingDialogue(from,at,index)' in picker

# Two-way sync: a change goes ONLY into adventure.npcs, not gameObject or .vsgm.
update=visual[visual.index('void updateNpcProperty('):visual.index('QString npcDialogueTitle(')]
assert 'entry.insert(field,value)' in update
assert 'm_npcEntries.replace(index,entry)' in update
assert 'm_npcsChanged=true' in update
assert 'm_touched.insert(id)' not in update
save=visual[visual.index('bool saveAll()'):visual.index('bool fail(')]
assert 'm_dialoguesChanged || m_npcsChanged' in save
assert 'adventure.insert(QStringLiteral("npcs"),m_npcEntries)' in save
assert 'adventure.insert(QStringLiteral("nodes"),m_dialogues)' in save
assert 'QCryptographicHash::hash(current,QCryptographicHash::Sha256)!=m_originalHash' in save
assert 'QFile::copy(m_worldPath,backup)' in save
layout=visual[visual.index('QJsonObject graphJson() const'):visual.index('bool saveLayout()')]
for gameplay_key in ('npcStartNode','npcDoneNode','initiallyVisible','radius','m_npcEntries'):
    assert gameplay_key not in layout
assert 'hiddenNpcCards' in layout
assert 'm_hiddenNpcCards.contains(id)' in visual
assert 'm_hiddenNpcCards.remove(selectedId)' in visual
assert 'm_hiddenNpcCards.insert(id)' in visual

# Modifying an NPC dialogue never changes the Dialogue Editor's entry order.
assert 'm_dialogues.removeAt(' not in update
assert 'm_dialogues.replace(' not in update
assert 'node.npcStartNode' in visual and 'node.npcDoneNode' in visual
print('PASS Stage 5.166.72: NPC editor fields, existing dialogue mapping, safe save/refresh, hide/show layout')
