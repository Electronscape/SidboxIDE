#!/usr/bin/env python3
"""Stage 5.63.1: source-level protection for middle-button preview panning."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
source = (root / 'gametitlescreeneditor.cpp').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()
start = source.index('class TitlePreviewView final')
end = source.index('QString fileName(', start)
view = source[start:end]
assert 'Build: 5.63.1.231026' in splash
assert '#include <QScrollBar>' in source
assert 'Qt::MiddleButton' in view
assert 'void mousePressEvent(QMouseEvent *event) override' in view
assert 'void mouseMoveEvent(QMouseEvent *event) override' in view
assert 'm_middlePanning = true' in view
assert 'horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());' in view
assert 'verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());' in view
assert 'viewport()->unsetCursor();' in view
assert 'if (dragFinished && event->button()==Qt::LeftButton)' in view
assert 'void wheelEvent(QWheelEvent *event) override' in view
assert 'scene->clear()' not in view
assert 'MiddleButton' not in view.split('void mousePressEvent')[0]
print('Stage 5.63.1 middle-button preview pan source checks: PASS')
