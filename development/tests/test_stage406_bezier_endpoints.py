#!/usr/bin/env python3
"""Stage 4.06: Bezier endpoints are editable; exported point stamp remains v4.

Portable source assertions. Native Qt GUI dragging must be tested in the IDE.
"""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[2]
s = (root / 'gametilemap.cpp').read_text()
base = (root / 'gametilemapinternal.h').read_text()
start = s.index('    connect(generateCurve, &QPushButton::clicked, this, [this]() {')
end = s.index('    auto *collisionPointButtons', start)
dlg = s[start:end]

assert 'auto *startY = make(tr("Left endpoint Y"), 0, h, shape.points.first().y()).first;' in dlg
assert 'auto *endY = make(tr("Right endpoint Y"), 0, h, shape.points.last().y()).first;' in dlg
assert 'QSpinBox *m_startY, *m_endY;' in dlg
assert 'const QPointF start = toScreen(QPoint(0, m_startY->value()));' in dlg
assert 'const QPointF finish = toScreen(QPoint(m_w, m_endY->value()));' in dlg
assert 'sampledCubicSlope(m_w, m_h, m_startY->value(), m_endY->value(),' in dlg
assert 'sampledCubicSlope(w, h, startY->value(), endY->value(),' in dlg
assert 'for (QSpinBox *spin : {startY, x1, y1, x2, y2, endY})' in dlg
assert 'm_startY->setValue(y)' in dlg and 'm_endY->setValue(y)' in dlg
assert 'x = qMin(x, m_bx->value());' in dlg and 'x = qMax(x, m_ax->value());' in dlg
assert 'm_dragging = hitHandle(event->position());' in dlg
assert 'setCursor(hitHandle(event->position()) ? Qt::OpenHandCursor : Qt::ArrowCursor);' in dlg
assert 'QStringLiteral("L")' in dlg and 'QStringLiteral("R")' in dlg
assert 'The blue endpoints stay fixed' not in dlg
assert 'm_startY(startY), m_endY(endY)' in dlg
assert 'dialog.exec() != QDialog::Accepted' in dlg  # Cancel leaves points alone.
assert 'recordChange(before);' in dlg  # OK remains undoable.
assert 'stamp.points.first().x() != 0' in base
assert 'stamp.points.last().x() != stamp.width * stamp.tileSize' in base
# The generated points still cover 0..width with original point-based export.
assert 'out.first() = QPoint(0, startY);' in s
assert 'out.last() = QPoint(width, endY);' in s
assert re.search(r'for \(int i = 0; i <= intervals; \+\+i\)', s)
print('PASS Stage 4.06: editable endpoints, bounded dragging, undo and unchanged v4 export')
