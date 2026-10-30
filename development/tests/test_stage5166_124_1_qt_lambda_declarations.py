"""Regression: Qt callable lambda declarations are objects, not pointers."""
from pathlib import Path
import re
r = Path(__file__).resolve().parents[2]
s = (r / 'gamedesigner.cpp').read_text()
assert 'auto updateCombatControls = [=] {' in s
assert 'auto *updateCombatControls' not in s
for p in [*r.glob('*.cpp'), *r.glob('*.h')]:
    assert not re.search(r'\bauto\s*\*\s*\w+\s*=\s*\[', p.read_text(errors='replace')), p
assert 'Build: 5.166.' in (r/'splashscreenwidget.cpp').read_text()
print('Stage124.1 Qt lambda declaration regression: PASS')
