"""Stage 5.166.85: selected card raise; final Qt control row alignment.

Source-contract test. Pixel and mouse interaction still require real Qt GUI.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
s = (root/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (root/'splashscreenwidget.cpp').read_text()
view = s[s.index('class NodeCanvas final'):s.index('class NodeCanvas final')+16000]
assert 'for (QGraphicsItem *candidate=item;candidate;candidate=candidate->parentItem())' in view
assert 'candidate->setZValue(highest+1.0);' in view
assert 'top->data(0).toString()==QStringLiteral("card")' in view
assert view.index('candidate->setZValue(highest+1.0)') < view.index('QGraphicsView::mousePressEvent(event);')
redraw = s[s.index('void redrawLinks() {'):s.index('for (QGraphicsPathItem *item:m_lines)',s.index('void redrawLinks() {'))]
for required in ('proxy->subWidgetRect(edit)', 'proxy->subWidgetRect(combo)',
                 'conversationAnswerIndex','npcDialogueInputSlot','conversationSpeechInput',
                 'giveRouteBranch','card->collapsed()',
                 'card->rect().right()-r.width()*.5','card->rect().left()-r.width()*.5',
                 'conversation-missing-output','give-anchor','npc-input',
                 'exchange-output'):
    assert required in redraw, required
assert 'answerText->setProperty("conversationAnswerIndex",option)' in s
assert 'speech->setProperty("conversationSpeechInput",true)' in s
assert 'start->setProperty("npcDialogueInputSlot",QStringLiteral("start"))' in s
assert 'done->setProperty("npcDialogueInputSlot",QStringLiteral("helped"))' in s
conversation = s[s.index('void makeConversationCard('):s.index('void makeGiveCard(')]
assert 'control->mapTo(panel' not in conversation
assert 'panel->ensurePolished()' in s
assert 'return nearest->sceneBoundingRect().center()' in s
assert 'const QBrush socketBrush(connected?fill:QColor(26,31,41));' in s
print('PASS Stage 5.166.85: click-to-front and standardised post-layout ports')
