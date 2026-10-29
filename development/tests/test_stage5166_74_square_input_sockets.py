#!/usr/bin/env python3
"""Stage 5.166.74: small inbound square sockets, round outbound sockets.

Static contract only: actual mouse-drop and visual positioning need Qt testing.
"""
from pathlib import Path
R=Path(__file__).resolve().parents[2]
s=(R/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (R/'splashscreenwidget.cpp').read_text()
# Game Objects, NPCs, independent and legacy Logic, and all dialogue cards.
regions=[('void makeObjectCard(', 'void npcDialogueTitle('),
         ('void makeGraphCard(', 'void refreshGraphDialogueCard('),
         ('void makeGraphDialogueCard(', 'void setGraphDialogue('),
         ('void createToggleCard(', 'void refreshToggleCard('),
         ('void createBranchCard(', 'void refreshBranchCard('),
         ('void createDialogueCard(', 'void refreshDialogueCard(')]
# These anchors are allowed to appear in different ordering; take each full method's region.
for marker in ['void makeObjectCard(', 'void makeGraphCard(', 'void makeGraphDialogueCard(',
               'void createToggleCard(', 'void createBranchCard(', 'void createDialogueCard(']:
    start=s.index('    '+marker)
    end=s.index('\n    void ',start+10)
    section=s[start:end]
    assert 'new QGraphicsRectItem(QRectF(-7,' in section, marker
    assert 'input->setData(0,QStringLiteral("input"))' in section, marker
assert 'new QGraphicsRectItem(QRectF(-7,y-7,14,14),card)' in s
# The large ports remain round; drag remains OUTPUT only.
assert 'new QGraphicsEllipseItem(QRectF(265,69,18,18),card)' in s
assert 'socketKind==QStringLiteral("output")' in s
# Both collapsed and expanded inbound wires arrive at the socket's center.
node=s[s.index('class NodeCard'):s.index('class NodeWire')]
assert 'kind!=QStringLiteral("npc-input")' in node and 'kind!=QStringLiteral("conversation-input")' in node
assert 'return nearest->sceneBoundingRect().center();' in node
assert 'child->setVisible(true)' in node
assert 'helped?39.0:24.0' in node
assert 'setCompactHeight(49)' in s
assert 'stateInput->setData(2,QStringLiteral("state"))' in s
assert 'port!=QStringLiteral("state")' in s
assert 'const QPointF b=target->wirePoint(QPointF(0,58));' in s
assert 'const QPointF b=to->wirePoint(QPointF(0,58));' in s
assert 'const QPointF b=routed?npcPoint:to->wirePoint(QPointF(0,57));' in s
# Nothing changes to the gameplay generator or adds a second link repository.
assert 'connectionRequested(from,to,inputPort)' in s
assert 'adventure.insert(QStringLiteral("npcs"),m_npcEntries)' in s
print('PASS Stage 5.166.74 square input ports and existing output port semantics')
