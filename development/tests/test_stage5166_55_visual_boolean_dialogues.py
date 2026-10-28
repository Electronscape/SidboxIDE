#!/usr/bin/env python3
"""Stage 5.166.55 UI/schema contract: Boolean nodes and consistent dialogue cards.

This cannot replace a Qt6 GUI build, but prevents the incorrect Phase 2 flow
(returning an instruction popup or separate dialogue summary card).
"""
from pathlib import Path
source=Path(__file__).resolve().parents[2]
graph=(source/'gamevisualnodes.cpp').read_text()
version=(source/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.' in version
# Node discovery is a tree, not a toolbar-only state card.
assert 'QStringList{tr("Logic")}' in graph
assert 'QStringList{tr("Boolean (TRUE / FALSE)")}' in graph
assert 'QStringLiteral("@logic:boolean")' in graph
assert 'addBooleanFromObject(from,at);' in graph
# Stage 5.166.56: state source comes from a Game Object's output,
# not an editable dropdown inside the Boolean card.
start=graph.index('void createToggleCard(')
end=graph.index('void createBranchCard(',start)
boolean=graph[start:end]
assert 'No state dropdown' in boolean
assert 'm_booleanSourceLabels.insert(id,sourceLabel)' in boolean
assert 'Choose state to read...' not in boolean
assert 'm_booleanSourcePickers' not in graph
assert 'QStringLiteral("@stateout:true:")' in boolean
assert 'QStringLiteral("@stateout:false:")' in boolean
assert 'void addBooleanFromObject(' in graph
assert 'n.toggleStateTargetId=source;' in graph
assert 'const NodeCard *source' not in graph  # source is the existing movable NodeCard
assert 'NodeCard *source=m_cards.value(node.toggleStateTargetId);' in graph
# Branch outputs support same object action choices as Trigger outputs.
assert 'appendBranchConnection(from.mid(prefix.size()),yes,selectedId,QStringLiteral("enable"));' in graph
assert 'supportedAction(action)' in graph
assert 'QPair<QString,QString> &choice' in graph
# Branch dialogue editor has the same key interactive controls as normal dialogue.
normal=graph[graph.index('void createDialogueCard('):graph.index('void refreshDialogueCard(')]
branch=graph[graph.index('void createBranchCard('):graph.index('void refreshBranchCard(')]
for snippet in ('QComboBox(panel)','Browse Dialogue Folders...', 'QLineEdit(panel)',
                'QPlainTextEdit(panel)', 'Disconnect Dialogue', 'm_dialogueControls.insert('):
    assert snippet in normal and snippet in branch, snippet
assert 'QSignalBlocker pblock(c.picker);' in graph[graph.index('void refreshBranchCard('):graph.index('void setBranchDialogue(')]
assert 'm_dialogues.replace(index,dialogue)' in branch
assert 'm_dialoguesChanged=true' in branch
# Conditional branches explicitly remain single-message until runtime supports more.
assert 'mode->setEnabled(false);' in branch
assert 'Single message (no actions)' in branch
# Unlinked purple cards may still exist in .vsgm; real links only in .sbgm.
assert 'm_placedCards.contains(branchCardId(id,true))' in graph
assert 'm_placedCards.contains(branchCardId(id,false))' in graph
world_json=graph[graph.index('bool saveAll()'):]
for key in ('toggleStateTargetId','toggleTrueDialogueNode','toggleFalseDialogueNode',
            'toggleTrueActions','toggleFalseActions'):
    assert f'QStringLiteral("{key}")' in world_json
layout_json=graph[graph.index('QJsonObject graphJson('):graph.index('bool saveLayout(')]
assert 'toggleTrueDialogueNode' not in layout_json
assert 'toggleFalseDialogueNode' not in layout_json
print('Stage 5.166.55: Boolean / dialogue UI schema contracts passed')
