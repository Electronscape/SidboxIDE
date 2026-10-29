"""Stage 5.166.88: live, indexed wire tracking during a node drag.

Qt's scene event/render integration must be tested on a desktop. These checks
exercise the source contract and the per-segment endpoint deformation design.
"""
from pathlib import Path
s=(Path(__file__).resolve().parents[2] / 'gamevisualnodes.cpp').read_text()
splash=(Path(__file__).resolve().parents[2] / 'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in splash
# The old restarted 20ms timer was the cause of orphan-looking lines.
assert 'm_linesTimer' not in s
assert 'void updateLiveWires(const QString &id,NodeCard *card)' in s
segment=s[s.index('void updateLiveWires('):s.index('void redrawLinks()')]
assert 'm_liveWiresByCard.value(id)' in segment
assert 'const QPointF delta=now-previous' in segment
assert 'const bool source=wire->data(4).toString()==id;' in segment
assert 'const bool destination=wire->data(5).toString()==id;' in segment
assert 'path.translate(delta)' in segment
assert 'path.setElementPositionAt(0,' in segment
assert 'path.setElementPositionAt(1,' in segment
assert 'path.setElementPositionAt(end,' in segment
assert 'path.setElementPositionAt(end-1,' in segment
assert 'wire->setPath(path)' in segment
assert 'redrawLinks();' not in segment  # No full scene rebuild during movement.
assert 'if (m_scene && !m_scene->sceneRect().contains(card->sceneBoundingRect()))' in segment
# Every kind of card must use the single live-update route.
assert s.count('card->moved=') == 8
assert s.count('card->moved=')==s.count('card->moved=[this,')
assert s.count('updateLiveWires(') == 9  # 8 callbacks + definition
# Post-draw indexing uses stable source/target identities, not geometry or
# the transient QGraphicsPathItem pointer from a previous full draw.
redraw=s[s.index('void redrawLinks()'):s.index('void showDetails(')]
assert 'm_liveWiresByCard.clear();' in redraw
assert 'm_liveWiresByCard[from].append(wire)' in redraw
assert 'm_liveWiresByCard[to].append(wire)' in redraw
assert 'to!=from' in redraw
assert 'm_liveWirePositions.clear();' in redraw
# Once mouse release has finished dispatching the card's final move,
# reconstruct accurate tangent handles a single time.
canvas=s[s.index('class NodeCanvas final'):s.index('class VisualNodesDialog final')]
assert 'std::function<void()> cardDragFinished;' in canvas
assert 'QGraphicsView::mouseReleaseEvent(event);' in canvas
assert 'if (event->button()==Qt::LeftButton && cardDragFinished)' in canvas
assert 'm_view->cardDragFinished=[this]' in s
# Wire selection and self-loops still work.
assert 'applyWireFocus();' in redraw
assert 'conversationSelfLoopCurve(a,b,' in redraw
assert 'm_selectedWireKey' in s
print('PASS Stage 5.166.88: no debounce, per-edge live paths, 8 card types, self-loops, final refresh')
