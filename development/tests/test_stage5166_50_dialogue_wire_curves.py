#!/usr/bin/env python3
"""Stage 5.166.50: dialogue wires use smooth Beziers, no top-box detours.

This verifies source contract and cubic geometry, not a Qt6 desktop render.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
code = (root / 'gamevisualnodes.cpp').read_text()
method = code.split('    void redrawLinks() {', 1)[1].split('    void showDetails(', 1)[0]
purple = method.split('if (node.dialogueNode>=0 && m_dialogueCards.contains(id)) {', 1)[1]
assert 'const QRectF target=to->sceneBoundingRect();' in purple
assert 'const bool targetOnLeft=target.center().x()<a.x();' in purple
assert 'targetOnLeft?target.right():target.left()' in purple
assert 'targetOnLeft?bend:-bend' in purple
assert 'path.cubicTo(' in purple
assert 'path.lineTo(' not in purple
assert 'const qreal top=qMin(' not in purple
assert 'QStringLiteral("dialogue-link")' in purple
assert 'new NodeWire(path,QPen(QColor(199,149,248),3))' in purple
assert 'stroker.setWidth(20.0);' in code # context hit target unchanged
assert 'm_linesTimer->start();' in code # moved cards update geometry

# Simulate cubic parameters from the real screenshot: WellDrop's socket is
# around (370, 498), its Show Dialogue card runs x=73..366, y=54..406.
def curve(source, card):
    x, y = source
    left, top, right, bottom = card
    target_left = (left + right) * 0.5 < x
    end = (right if target_left else left, top + 57.0)
    bend = max(55.0, min(150.0, abs(end[0]-x)*0.5))
    c1 = (x+bend, y)
    c2 = (end[0]+(bend if target_left else -bend), end[1])
    def point(t):
        omt = 1-t
        return tuple(omt**3*source[i] + 3*omt*omt*t*c1[i]
                     + 3*omt*t*t*c2[i] + t**3*end[i] for i in (0, 1))
    return target_left, end, [point(i/100) for i in range(101)]

# Left-hand dialogue: card right-side is used, no route over top frame.
reverse, end, points = curve((370, 498), (73, 54, 366, 406))
assert reverse and end == (366,111.0)
assert all(x >= 366-1e-9 for x, y in points)
assert all(y >= 111-1e-9 for x, y in points)
# Right-hand dialogue: normal action-style left-edge entry.
reverse, end, points = curve((636, 598), (736, 69, 1030, 421))
assert not reverse and end == (736,126.0)
assert all(636-1e-9 <= x <= 736+1e-9 for x, y in points)
# No gameplay or graph format changes.
assert 'root.insert(QStringLiteral("connections")' not in code
assert (m := re.search(r'Build: 5\.166\.(\d+)\.281026', (root / 'splashscreenwidget.cpp').read_text())) and int(m.group(1)) >= 50
print('PASS Stage 5.166.50: curved dialogue wires and backwards card attachment')
