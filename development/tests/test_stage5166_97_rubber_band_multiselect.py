"""Stage 5.166.97 visual-node rectangle selection contract.

Desktop Qt mouse behaviour requires a GUI smoke test. These assertions guard
Qt's native multi-item selection and the editor's existing wire-focus rules.
"""
from pathlib import Path
src=Path(__file__).resolve().parents[2]
s=(src/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.100.291026' in (src/'splashscreenwidget.cpp').read_text()
canvas=s[s.index('class NodeCanvas final'):s.index('class VisualNodesDialog final')]
assert 'setDragMode(QGraphicsView::RubberBandDrag)' in canvas
assert 'setRubberBandSelectionMode(Qt::IntersectsItemShape)' in canvas
assert 'event->button()==Qt::MiddleButton' in canvas
assert 'm_panning=true' in canvas
assert 'std::function<void(const QStringList &)> cardsSelectionChanged;' in canvas
assert 'scene()->selectedItems()' in canvas
assert 'selected.removeDuplicates();' in canvas
assert 'cardsSelectionChanged(selected);' in canvas
assert 'cardDragFinished();' in canvas
assert 'm_dragLine' in canvas
assert 'dynamic_cast<NodeWire*>(item)' in canvas
assert 'setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable' in s
focus=s[s.index('void applyWireFocus()'):s.index('void updateLiveWires(')]
assert 'QSet<QString> focusedCards=m_multiSelectedCards;' in focus
assert 'focusedCards.contains(wire->data(4).toString())' in focus
assert 'focusedCards.contains(wire->data(5).toString())' in focus
assert 'focusedCards.contains(it.key())' in focus
assert 'm_view->cardsSelectionChanged=[this](const QStringList &ids)' in s
assert 'm_multiSelectedCards=selected.size()>1?selected:QSet<QString>();' in s
assert 'm_removeSelectedButton->setEnabled(false);' in s
assert 'm_selectedCardId.clear();m_multiSelectedCards.clear();m_selectedWireKey.clear();' in s
# There are no authored event, world or dialogue-data format changes.
assert 'm_multiSelectedCards; // UI-only selection, never saved to .vsgm.' in s
print('PASS Stage 5.166.97 rubber-band select, Ctrl multi-select, move and focus contract')
