#!/usr/bin/env python3
"""Stage 5.166.73: NPC dialogue input wiring source-contract checks.

These checks verify the new UI connection uses the same dialogue fields
as the old runtime. Qt mouse/paint behaviour still requires desktop testing.
"""
from pathlib import Path
R=Path(__file__).resolve().parents[2]
s=(R/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (R/'splashscreenwidget.cpp').read_text()
# Two left-side input sockets, stable semantics on folded cards.
assert 'QStringLiteral("npc-input")' in s
assert 'QStringLiteral("helped"):QStringLiteral("start")' in s
assert 'const qreal y=helped?163.0:101.0;' in s
assert 'slot==QStringLiteral("start")?101:163' in s
assert 'child->setVisible(true)' in s
assert 'kind!=QStringLiteral("input") && kind!=QStringLiteral("npc-input")' in s
# Dragging to the port is not a plain NPC enable/disable action.
canvas=s[s.index('class NodeCanvas'):s.index('class VisualNodesDialog')]
assert 'connectionRequested(from,to,inputPort)' in canvas
assert 'port=p->data(2).toString()' in canvas and 'inputPort=port;' in canvas
node=s[s.index('void connectNpcDialogue('):s.index('void addConnection(')]
assert 'npc.npcStartNode' in node and 'npc.npcDoneNode' in node
assert 'setGraphDialogue(key,yes,dialogue)' in node
assert 'setBranchDialogue(owner,yes,dialogue' in node
assert 'connectExistingDialogue(from,' in node
assert 'm_npcDialogueRoutes.insert(from,QJsonObject' in node
assert 'if(!graph && !state && !trigger)return;' in node
assert 'tr("Which conversation on %1?")' in node
# All three established wire families can terminate at NPC inputs.
assert 'npcRoutePoint(id,node.dialogueNode,&npcPoint)' in s
assert 'npcRoutePoint(source,dialogue,&npcPoint)' in s
assert 'npcRoutePoint(source,index,&b)' in s
assert 'QStringLiteral("graph-true-dialogue")' in s
assert 'QStringLiteral("state-true-link")' in s
# A layout hint cannot become a second source of truth for game rules.
layout=s[s.index('QJsonObject graphJson() const'):s.index('bool saveLayout()')]
assert 'npcDialogueRoutes' in layout
assert 'targetObjectId' not in layout
assert 'logicNodes' not in layout
source=s[s.index('bool saveAll()'):s.index('bool fail(')]
assert 'object.insert(QStringLiteral("logicNodes"),node.logicNodes)' in source
assert 'adventure.insert(QStringLiteral("npcs"),m_npcEntries)' in source
# On-deletion/disconnection handling should not leave fake wires behind.
assert 'm_npcDialogueRoutes.remove(triggerId)' in s
assert 'm_npcDialogueRoutes.remove(QStringLiteral("@graphbranch:true:")+id)' in s
assert 'm_npcDialogueRoutes.remove(QStringLiteral("@stateout:true:")+id)' in s
print('PASS Stage 5.166.73 NPC input ports, direct dialogue wiring and .sbgm authority')
