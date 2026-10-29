"""Stage 5.166.86: accidental self-links have safe, reversible editing paths.

Source-level tests only; interactive Qt verification belongs on the desktop.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
s = (root / 'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (root / 'splashscreenwidget.cpp').read_text()

# Both direct drag and destination tree changes go through one guarded setter.
assert 'conversationConnectionRequested(from,choiceOption,missingRoute,to)' in s
assert 'setConversationAnswer(source,option,missing?QStringLiteral("missingNext"):QStringLiteral("next"),target);' in s
assert 'setConversationAnswer(index,option,QStringLiteral("next"),QJsonValue(next->currentData().toInt()))' in s
assert 'value.isDouble() && value.toInt(-1)==index' in s
assert 'QMessageBox::Yes|QMessageBox::No,QMessageBox::No' in s
assert 'Create this loop intentionally?' in s

# Intentional self-links display a visible path outside the card.
assert 'QPainterPath conversationSelfLoopCurve(' in s
assert 'cardBounds.top()-clearance' in s
assert 'cardBounds.right()+clearance' in s
assert 'cardBounds.left()-clearance' in s
assert 'conversationSelfLoopCurve(a,b,source->sceneBoundingRect(),option,false)' in s
assert 'conversationSelfLoopCurve(a,b,source->sceneBoundingRect(),option,true)' in s

# Right-click works on both normal and item-missing dialogue wires, but
# cards take priority over wires hidden beneath their Qt controls.
canvas=s[s.index('class NodeCanvas final'):s.index('class VisualNodesDialog final')]
assert 'conversationWireMenuRequested' in canvas
assert 'giveWireMenuRequested' in canvas
assert canvas.index('if (cardMenuRequested)') < canvas.index('for(QGraphicsItem *wire:items(event->pos()))')
assert 'QStringLiteral("conversation-next-wire")' in canvas
assert 'QStringLiteral("conversation-missing-wire")' in canvas
assert 'QStringLiteral("give-response-wire")' in canvas
assert 'wire->setData(1,id);wire->setData(2,option);' in s

# Right-clicking the card can disconnect even a link obscured by a card.
menu=s[s.index('void showCardContextMenu('):s.index('void hideDisconnectedCards()')]
assert 'Disconnect answer route' in menu
assert 'QStringLiteral("next")' in menu
assert 'QStringLiteral("missingNext")' in menu
assert 'SELF-LOOP' in menu
assert 'setConversationAnswer(index,route.first,route.second,-1);' in menu

# Disconnect means -1 in the SAME Adventure choice field, not deletion
# of the dialogue or creation of new runtime data.
assert 'setConversationAnswer(dialogue,option,field,-1)' in s
assert 'setGiveDestination(dialogue,answer,branch,-1)' in s
assert 'answer.insert(field,value);' in s
assert 'm_dialogues.replace(index,node);' in s
assert '.sbgm' in s and '.vsgm' in s
print('PASS Stage 5.166.86: self-loop confirmation, external loop geometry, wire/card disconnect, preserved dialogue IDs')
