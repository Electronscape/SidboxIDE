#!/usr/bin/env python3
"""Stage 3.95a source regression check: both preview paths use QImage::flipped."""
from pathlib import Path
p = Path(__file__).resolve().parents[2] / 'gamedesigner.cpp'
s = p.read_text()
assert '.mirrored(' not in s, 'Deprecated QImage::mirrored remains in gamedesigner.cpp'
assert s.count('frameImage = frameImage.flipped(flipDirections);') == 1
assert s.count('frame = frame.flipped(flipDirections);') == 1
assert s.count('Qt::Orientations flipDirections;') == 2
assert s.count('flipDirections |= Qt::Horizontal;') == 2
assert s.count('flipDirections |= Qt::Vertical;') == 2
assert 'frameImage = frameImage.flipped(flipDirections);' in s
assert 'frame = frame.flipped(flipDirections);' in s
print('PASS: canvas and live preview both use explicit Qt6 horizontal/vertical flip directions')
