#!/usr/bin/env python3
"""Stage 4.19: bit labels and toggles follow MSB-first row order without clipping."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
s = (root / 'mainwindow.cpp').read_text()
start = s.index('    void rebuildBitRows(int bits)')
end = s.index('    void recalculate()', start)
fn = s[start:end]
assert 'const int low = (rowCount - 1 - row) * 16;' in fn
assert 'const int high = qMin(low + 15, bits - 1);' in fn
assert 'QStringLiteral("%1-%2").arg(high).arg(low)' in fn
assert 'for (int bit = high; bit >= low; --bit)' in fn
assert 'button->setObjectName(QStringLiteral("programmerCalculatorBit%1").arg(bit))' in fn
assert 'm_bitButtons[bit] = button;' in fn
assert 'const quint64 newValue = (m_currentValue ^ (quint64(1) << bit)) & mask;' in fn
assert 'button->setMinimumWidth(0);' in fn
assert 'button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);' in fn
assert 'line->addSpacing(2)' in fn

for width in (8, 16, 32, 64):
    rows = []
    for row in range((width + 15) // 16):
        low = (((width + 15) // 16) - 1 - row) * 16
        high = min(low + 15, width - 1)
        rows.append((f'{high}-{low}', list(range(high, low - 1, -1))))
    bits = [bit for _, contents in rows for bit in contents]
    assert bits == list(range(width - 1, -1, -1)), (width, rows)
    if width == 32:
        assert [caption for caption, _ in rows] == ['31-16', '15-0']
    if width == 64:
        assert [caption for caption, _ in rows] == ['63-48', '47-32', '31-16', '15-0']

print('PASS Stage 4.19: calculator rows MSB-first; correct 8/16/32/64 labels; narrow-bit layout')
