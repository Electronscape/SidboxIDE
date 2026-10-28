#!/usr/bin/env python3
"""Static regression for Game Object Properties coloured checkbox geometry."""
from pathlib import Path
import re
ROOT = Path(__file__).resolve().parents[2]
src = (ROOT/'gamedesigner.cpp').read_text()
start = src.index('void SidboxGameDesigner::configureGameObject(int index)')
stop = src.index('    const auto commitObject = [&]() -> bool {', start)
body = src[start:stop]
checkboxes = set(re.findall(r'auto \*(\w+)\s*=\s*new QCheckBox\(',body))
assert len(checkboxes) >= 35, len(checkboxes)
# Form checkboxes must span both label and value columns. Longer enemy labels
# otherwise leave too little room for the indicator and coloured border.
rows = re.findall(r'([\w.]+)->addRow\(QString\(\),\s*(\w+)\s*\);',body)
remaining = [(form,name) for form,name in rows if name in checkboxes]
assert not remaining, remaining
for name in ('enemyRewardImpulse','enemyRoamLeft','enemyStompSideKick',
             'triggerPress','triggerDrop','triggerOneShot','interactConsume'):
    assert re.search(r'->addRow\(\s*'+re.escape(name)+r'\s*\);',body),name
qss=(ROOT/'ideglobaltheme.h').read_text()
assert 'QCheckBox[adventureGuard="true"],' in qss
part=qss[qss.index('QCheckBox[adventureGuard="true"],'):]
assert 'padding:5px 8px; margin:0px; spacing:8px;' in part
assert 'QCheckBox[adventureGuard="true"]:enabled' in part
assert 'QCheckBox[adventureGuard="true"]:disabled' in part
assert '5.166.39.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
print(f'PASS: {len(checkboxes)} Game Object checkboxes, all single-widget rows span columns; guard sizes match')
