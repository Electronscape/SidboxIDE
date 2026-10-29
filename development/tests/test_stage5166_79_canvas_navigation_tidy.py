#!/usr/bin/env python3
"""Static regression guard for 5.166.79 canvas-only navigation/layout changes.

These checks do not replace the actual Qt UI build and mouse tests.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
cpp = (root/'gamevisualnodes.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in version
canvas=cpp[cpp.index('class NodeCanvas final'):cpp.index('class VisualNodesDialog final')]
assert 'event->button()==Qt::MiddleButton' in canvas
assert 'm_panning=true' in canvas and 'm_panning=false' in canvas
assert 'm_panPosition=event->pos()' in canvas
assert 'horizontalScrollBar()->setValue' in canvas
assert 'verticalScrollBar()->setValue' in canvas
assert 'event->accept()' in canvas
assert 'setDragMode(QGraphicsView::RubberBandDrag)' in canvas
assert 'm_dragLine' in canvas and 'Qt::LeftButton' in canvas
assert 'contextMenuEvent(QContextMenuEvent *event)' in canvas
assert 'void updateSocketStates()' in cpp
sockets=cpp[cpp.index('void updateSocketStates()'):cpp.index('void tidyCards()')]
for text in ('conversation-input','npc-input','conversation-output','connected',
             'square->setBrush(socketBrush)','circle->setBrush(socketBrush)',
             'wire->path().pointAtPercent(0)','wire->path().pointAtPercent(1)'):
    assert text in sockets, text
assert 'void tidyCards()' in cpp
rearrange=cpp[cpp.index('void tidyCards()'):cpp.index('void fitAllCards()')]
for text in ('QMessageBox::Cancel','m_lines','adjacent','outgoing','columns',
             'card->setPos','m_positions[id]=card->pos()','redrawLinks();','m_dirty=true'):
    assert text in rearrange, text
assert 'm_objects.insert' not in rearrange
assert 'm_dialogues.replace' not in rearrange
assert 'm_touched.insert' not in rearrange
assert 'auto *tidy=new QPushButton(tr("Tidy"),this)' in cpp
assert 'connect(tidy,&QPushButton::clicked,this,[this] {tidyCards();});' in cpp
assert 'void updateCanvasBounds()' in cpp
assert 'void viewportInsertionPoint(' not in cpp
assert 'QPointF viewportInsertionPoint(' in cpp
spawn=cpp[cpp.index('QPointF viewportInsertionPoint('):cpp.index('void addFoldButton(')]
assert 'mapToScene(m_view->viewport()->rect().center())' in spawn
assert 'target.adjusted(-18,-18,18,18).intersects' in spawn
assert 'QPointF(1180+level*420' not in cpp
assert 'anchor+QPointF(level*435.0,ordinal*520.0)' in cpp
assert 'smoothNodeCurve(a,b,16.0)' not in cpp  # 5.166.80 removes the artificial bow
assert 'QPen(QColor(233,177,98),2,Qt::DashLine)' in cpp
assert cpp.count('smoothNodeCurve(a,b)')>=3
assert 'm_flowAnchor=m_positions.contains(rootId)?m_positions.value(rootId)' in cpp
assert 'Build: 5.166.99.291026' in version
print('PASS 5.166.79: MMB navigation, hollow ports, viewport spawn, tidy layout, shared dashed dialogue curves')
