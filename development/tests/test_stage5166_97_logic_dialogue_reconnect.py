"""Stage 5.166.97: source contract for reconnecting an independent logic
TRUE/FALSE output to existing Show Dialogue cards, including shared dialogue
IDs and robust hit-testing. Qt integration still needs an interactive test.
"""
from pathlib import Path
src=Path(__file__).resolve().parents[2]
s=(src/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.100.291026' in (src/'splashscreenwidget.cpp').read_text()
release=s[s.index('void mouseReleaseEvent(QMouseEvent *event) override {', s.index('class NodeCanvas final')):s.index('class VisualNodesDialog final',s.index('class NodeCanvas final'))]
assert 'scene()->items(' in release
assert 'if(dynamic_cast<NodeWire*>(hit))continue;' in release
assert 'connectionRequested(from,to,inputPort);' in release

method=s[s.index('int selectedDialogueOnCard('):s.index('int removeOrphanCard(',s.index('int selectedDialogueOnCard('))]
assert 'cardId.startsWith(QStringLiteral("@graph-dialogue:"))' in method
assert 'cardId.startsWith(QStringLiteral("@toggle-dialogue:"))' in method
assert 'cardId.startsWith(QStringLiteral("@dialogue:"))' in method
assert 'cardId.startsWith(QStringLiteral("@conversation:"))' in method
assert 'm_dialogueControls.value(cardId).picker' in method
assert 'selectedDialogueOnCard(to)' in method
assert 'setGraphDialogue(key,yes,selected,where);' in method
assert 'setBranchDialogue(owner,yes,selected' in method
assert 'if(to!=graphDialogueKey(key,yes))' not in method
assert 'if(m_objects.contains(to))addGraphAction' in method
print('PASS 5.166.97: direct TRUE/FALSE reconnect and shared dialogue card selection')
