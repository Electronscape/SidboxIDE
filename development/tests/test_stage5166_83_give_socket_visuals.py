"""5.166.83: Real GIVE anchors + opaque hollow sockets + centred edge positions."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (root/'splashscreenwidget.cpp').read_text()
# No runtime or independent data model is introduced: dragging teal merely
# moves the visual card belonging to its original Adventure dialogue choice.
assert 'socketKind==QStringLiteral("give-anchor")' in s
assert 'm_giveDrag=socketKind==QStringLiteral("give-anchor")' in s
assert 'giveAnchorDropped(from,choiceOption,dropPoint,to);' in s
assert 'm_view->giveAnchorDropped=[this]' in s
assert 'const QString targetId=giveCardId(dialogue,answer);' in s
assert 'makeGiveCard(dialogue,answer,point+QPointF(24,-52));' in s
assert 'card->setPos(next);' in s
assert 'recordHistoryNow();' in s
assert 'if(!onto.isEmpty() && onto!=targetId)' in s
# The original world exchange model must not be rewritten when pulling a card.
start=s.index('m_view->giveAnchorDropped=[this]')
end=s.index('m_view->insertRequested=[this]',start)
callback=s[start:end]
assert 'setGiveDestination' not in callback
assert 'setConversationAnswer' not in callback
assert 'exchange.insert' not in callback
# All expanded dialogue output centres are exactly on the right boundary;
# collapse uses one vertical column and grows tall enough to fit every socket.
assert 'circle->setRect(QRectF(card->rect().right()-r.width()*.5,' in s
assert '14.0+17.0*slot-original.center().y()' in s
assert '12.0+compactOutputs.size()*17.0' in s
assert 'answerText->setProperty("conversationAnswerIndex",option);' in s
assert 'missingPort->setData(2,option);' in s
assert 'kind==QStringLiteral("give-anchor")?-15.0:' in s
assert 'kind==QStringLiteral("conversation-missing-output")?0.0:15.0' in s
assert 'pair.first->setRect(QRectF(width-6.5,y-6.5,13,13));' in s
# Outlined ports must obscure lines and borders, not be alpha-transparent.
body=s[s.index('void updateSocketStates()'):s.index('// Session-only undo history.')]
assert 'const QBrush socketBrush(connected?fill:m_theme.panelBackground);' in body
assert 'setBrush(Qt::NoBrush)' not in body
assert 'child->setZValue' in body
print('PASS 5.166.83: pull-out GIVE anchor, socket grouping, opaque empty sockets, no gameplay changes')
