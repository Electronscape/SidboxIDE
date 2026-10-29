#!/usr/bin/env python3
"""Stage 5.166.51 Visual Nodes contract checks (no full Qt6 GUI build here)."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
import re
assert (m := re.search(r'Build: 5\.166\.(\d+)\.281026', (root/'splashscreenwidget.cpp').read_text())) and int(m.group(1)) >= 51
card=s[s.index('class NodeCard final'):s.index('// The drawn pen stays crisp')]
assert 'ItemPositionChange && m_gridSnap' in card
assert 'ItemPositionHasChanged && moved' in card
assert 'constexpr qreal cell=8.0' in card
assert 'std::round(p.x()/cell)*cell' in card and 'std::round(p.y()/cell)*cell' in card
assert 'bool m_gridSnap=false' in card
assert 'void enableGridSnap()' in card
# Position saved before enabling snapping, preserving existing .vsgm positions.
for key,place in [('id','position'),('key','pos')]:
    assert re.search(rf'card->setPos\({place}\);\s*card->enableGridSnap\(\);\s*m_positions.insert\({key},{place}\);',s)
assert s.count('card->enableGridSnap();')>=4  # includes newer independent graph/dialogue card types
newcard=s[s.index('void createDialogueCard('):s.index('void refreshDialogueCard(')]
assert 'rowItem->setData(Qt::UserRole,key)' in newcard
assert 'rowItem->setForeground(QBrush(QColor(199,149,248)))' in newcard
assert 'refreshDialogueCard(id);' in newcard
update=s[s.index('void refreshDialogueCard('):s.index('void editDialogueText(')]
assert 'item->data(Qt::UserRole).toString()!=key' in update
assert 'Show Dialogue: %1  (#%2)' in update
assert 'Show Dialogue: %1  (unlinked)' in update
# Double-click focus and Delete use exactly the same keys used by canvas cards.
assert 'm_view->centerOn(m_cards.value(id));showDetails(id);' in s
assert 'watched==m_list && event->type()==QEvent::KeyPress' in s
assert 'if (id.startsWith(QStringLiteral("@dialogue:")))' in s
assert 'if (m_list->item(i)->data(Qt::UserRole).toString()==id)' in s
# Grid is a presentation concern; .sbgm remains the source of gameplay links.
assert 'root.insert(QStringLiteral("connections")' not in s
assert 'const QPointF p=m_cards.value(key)->pos();' in s
# Verify nearest 8px mathematical contract including negatives.
from math import floor
def snap(v): return floor(v/8+0.5)*8 if v>=0 else -floor(-v/8+0.5)*8
for value,expected in [(0,0),(3,0),(4,8),(7,8),(9,8),(12,16),(-1,0),(-4,-8),(-9,-8),(81,80)]:
    assert snap(value)==expected,(value,snap(value),expected)
print('PASS Stage 5.166.51: 8px drag snapping and Visible Nodes dialogue cards')
