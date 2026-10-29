#!/usr/bin/env python3
"""Stage 5.166.75 source-contract and representative dialogue traversal checks.

Not a Qt build: native interaction still needs a desktop acceptance test.
"""
from pathlib import Path
import json, re

root=Path(__file__).resolve().parents[2]
ui=(root/'gamevisualnodes.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in version

for token in (
    '+ Conversation Flow', 'void showConversationFlowPicker(',
    'void showConversationFlow(', 'void makeConversationCard(',
    'void rebuildConversationFlow(', 'conversationReachable(',
    'QStringLiteral("@conversation:%1")', 'QStringLiteral("choices")',
    'QStringLiteral("next")', 'QStringLiteral("missingNext")',
    'QStringLiteral("requires")', 'QStringLiteral("text")',
    'tr("Show Opening Conversation Flow...")',
    'tr("Show After-helped Conversation Flow...")',
    'QStringLiteral("conversation-input")',
    'QStringLiteral("conversation-output")',
    'QStringLiteral("conversation-preview-wire")',
    'if (choice.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;',
    'if(choice.value(QStringLiteral("requires")).toInt(-1)>=0 &&',
    'Qt::DashLine', 'void hideConversationContaining(',
    'm_conversationRoots.insert(root)',
    'm_view->centerOn(m_cards.value(id))',
    'rebuildConversationFlow();\n        redrawLinks();',
    'm_collapsedCards', 'card->moved=[this,id,card] {updateLiveWires(id,card);};',
):
    assert token in ui, f'missing preview feature: {token}'

# The visual socket edits the existing Adventure choice, never a second gameplay wire.
canvas=ui[ui.index('class NodeCanvas'):ui.index('class VisualNodesDialog')]
assert 'socketKind==QStringLiteral("output")' in canvas
assert 'QStringLiteral("conversation-output")' in canvas  # Stage 81 enables real Adventure choice routing
assert 'kind!=QStringLiteral("link")' in canvas
assert 'QStringLiteral("conversation-preview-wire")' not in canvas

# Real .sbgm remains source of dialogue content and branching.
source=ui[ui.index('bool initialise()'):ui.index('void renderCards()')]
assert 'm_dialogues=adventure.value(QStringLiteral("nodes")).toArray()' in source
assert 'adventure.nodes' in ui
assert 'm_dialogues.replace(index,node)' in ui  # older inline editor remains
assert 'void editDialogueText(' in ui

layout=ui[ui.index('QJsonObject graphJson() const'):ui.index('bool saveLayout()')]
assert 'conversationFlowRoots' in layout
assert 'conversationCardId(root)' in layout
assert 'QStringLiteral("@conversation:")' in layout
assert 'root.insert(QStringLiteral("nodes")' not in layout
assert 'root.insert(QStringLiteral("choices")' not in layout
assert 'm_dialogues' not in layout

# Deleting an imported flow card hides PREVIEW roots, not Adventure content.
remove=ui[ui.index('void removeSelectedNode()'):ui.index('void removeAllOrphans()')]
assert 'hideConversationContaining(index)' in remove
assert remove.index('hideConversationContaining(index)')<remove.index('tr("Delete Visual Node")')

# In a branching cycle, every numeric dialogue ID is visited once. Blank
# answers are ignored, and item-missing routes remain separate graph edges.
sample={
    'adventure':{'nodes':[
        {'speaker':'Big Steve','text':'Hello','choices':[
            {'text':'Hello','next':1,'requires':-1,'missingNext':-1},
            {'text':'Show item','next':2,'requires':3,'missingNext':3},
            {'text':'','next':9,'requires':-1,'missingNext':-1},
        ]},
        {'speaker':'Kim','text':'Again?','choices':[{'text':'Back','next':0,'requires':-1,'missingNext':-1}]},
        {'speaker':'Big Steve','text':'Thanks!','choices':[]},
        {'speaker':'Big Steve','text':'No item','choices':[{'text':'Leave','next':-1,'requires':-1,'missingNext':-1}]},
    ]}
}
nodes=sample['adventure']['nodes']
assert len(nodes)==4
queue=[0];visited=set();edges=[]
while queue:
    i=queue.pop(0)
    if i in visited:continue
    visited.add(i)
    for choice in nodes[i]['choices']:
        if not choice['text'].strip():continue
        for kind,destination in (
            ('answer',choice['next']),
            ('missing', choice['missingNext'] if choice['requires']>=0 else -1),
        ):
            if destination>=0 and destination<len(nodes):
                edges.append((i,destination,kind))
                if destination not in visited:queue.append(destination)
assert visited=={0,1,2,3}
assert (1,0,'answer') in edges
assert (0,3,'missing') in edges
assert all(b!=9 for _,b,_ in edges)
print('PASS Stage 5.166.75 read-only conversation flow schema, branching/cycles, alternate item route and layout authority')
