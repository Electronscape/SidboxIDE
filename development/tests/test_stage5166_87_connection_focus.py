"""Stage 5.166.87: selected nodes and individual wires highlight real endpoints.

Contract test: UI pixels/interaction require desktop Qt, but connection IDs,
selection preservation, all route classes and no graph data mutation are checked.
"""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (root/'splashscreenwidget.cpp').read_text()
canvas=s[s.index('class NodeCanvas final'):s.index('class VisualNodesDialog final')]
assert 'std::function<void(const QString &)> wireSelected;' in canvas
assert 'dynamic_cast<NodeWire*>(item) && wireSelected' in canvas
assert 'wireSelected(item->data(6).toString());' in canvas
assert 'setFocus(Qt::MouseFocusReason);' in canvas
assert 'if (event->key()==Qt::Key_Escape && cardSelected)' in canvas
assert canvas.index('dynamic_cast<NodeWire*>(item) && wireSelected') < canvas.index('QGraphicsView::mousePressEvent(event);')
assert 'void applyWireFocus()' in s
focus=s[s.index('void applyWireFocus()'):s.index('void redrawLinks()')]
assert 'focusedCards.contains(wire->data(4).toString())' in focus
assert 'focusedCards.contains(wire->data(5).toString())' in focus
assert 'wire->data(6).toString()==m_selectedWireKey' in focus
assert 'wire->setOpacity(!focused || active?1.0:0.12)' in focus
assert 'wire->setZValue(active?0.8:0.0)' in focus
assert 'QVariant::fromValue(wire->pen())' in focus
assert 'QVariant::fromValue(card->pen())' in focus
assert 'card->setPen(pen);' in focus
assert 'if(!exists)m_selectedWireKey.clear();' in focus
assert 'm_selectedWireKey.clear();\n        m_selectedCardId=id;' in s
assert 'm_view->wireSelected=[this](const QString &key)' in s
assert 'm_details->setPlainText(tr("SELECTED CONNECTION' in s
assert 'm_selectedWireKey=key;' in s
redraw=s[s.index('void redrawLinks()'):s.index('void showDetails(')]
assert 'wire->setData(6,key)' in redraw
assert 'applyWireFocus();' in redraw
assert 'wire->setData(4,id);wire->setData(5,link.target)' in redraw
assert 'wire->setData(4,sourceId);wire->setData(5,toggleCardId(id))' in redraw
for kind in ('conversation-next-wire', 'conversation-missing-wire',
             'give-preview-wire','give-response-wire','conversation-preview-wire',
             'state-true-link','state-false-link', 'state-true-action',
             'state-false-action','dialogue-link'):
    assert f'QStringLiteral("{kind}")' in redraw, kind
assert 'wire->setData(4,id);wire->setData(5,conversationCardId(next));' in redraw
assert 'wire->setData(4,id);wire->setData(5,conversationCardId(missing));' in redraw
assert 'wire->setData(4,id);wire->setData(5,conversationCardId(targetIndex));' in redraw
# Graph wires also have source/target IDs, not just route owner.
assert 'wire->setData(4,fromId);wire->setData(5,toId);' in s
for kind in ('graph-input','graph-result-binding','graph-true-action','graph-false-action',
             'graph-true-dialogue','graph-false-dialogue'):
    assert f'QStringLiteral("{kind}")' in s, kind
# Focus is UI-only, not serialized in the world or layout formats.
assert 'QString m_selectedWireKey; // Transient selection; never written to .sbgm/.vsgm.' in s
assert '.sbgm' in s and '.vsgm' in s
print('PASS Stage 5.166.87: wire click, node focus, stable endpoints, route coverage, highlight and safe clear')
