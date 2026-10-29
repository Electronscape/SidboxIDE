"""Stage 5.166.84: GIVE output sockets follow final dropdown geometry.

A Qt desktop compile and visual test are still required. This source test
protects the post-proxy alignment and existing Adventure wiring contracts.
"""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
s=(r/'gamevisualnodes.cpp').read_text()
version=(r/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in version
fn=s[s.index('void makeGiveCard('):s.index('void rebuildConversationFlow()',s.index('void makeGiveCard('))]
# Align only after the widget is parented into a QGraphicsProxyWidget.
assert fn.index('proxy->setWidget(panel)') < fn.index('proxy->subWidgetRect(pair.second)')
assert 'pair.second->mapTo(panel' not in fn
assert 'layout->activate();' in fn
assert 'panel->ensurePolished();' in fn
assert 'const qreal y=proxy->pos().y()+row.center().y();' in fn
assert 'pair.first->setRect(QRectF(width-6.5,y-6.5,13,13));' in fn
assert 'const qreal neededHeight=proxy->pos().y()+panel->height()+12.0;' in fn
# The dynamic redraw pass is safe for collapsed cards and recomputes from the
# actual combobox rows before constructing the wires.
redraw=s[s.index('void redrawLinks() {'):s.index('void showDetails(',s.index('void redrawLinks() {'))]
assert redraw.index('proxy->subWidgetRect(combo)') < redraw.index('for (QGraphicsPathItem *item:m_lines)')
assert 'card->collapsed()' in redraw
assert 'panel->findChildren<QComboBox*>()' in redraw
assert 'for(QComboBox *combo:panel->findChildren<QComboBox*>())' in redraw
assert 'findChildren<ConversationTreeCombo*>()' not in redraw
assert 'combo->property("giveRouteBranch").toInt()' in redraw
assert 'destination->setProperty("giveRouteBranch",branch);' in fn
assert 'card->rect().right()-r.width()*.5' in redraw
assert 'const QJsonObject exchange=giveExchange(sourceIndex,option);' in redraw
assert 'setGiveDestination' not in redraw
assert 'restoreViewport();' in s
assert 'redrawLinks();' in s[s.index('void showEvent('):s.index('void reject()')]
assert 'wrongRepeatFirst' in s and 'wrongRepeatLater' in s
print('PASS Stage 5.166.84 GIVE sockets align to final dropdown centres, no exchange data changes')
