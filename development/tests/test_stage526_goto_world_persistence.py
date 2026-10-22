#!/usr/bin/env python3
"""Stage 5.26 regression: Goto World survives .sbgm save/reopen.

This is a source-level persistence contract test: the Qt editor cannot be run
on machines without Qt6, but we check the exact generated writer and loader.
"""
import re
from pathlib import Path

root = Path(__file__).resolve().parents[2]
source = (root / 'gamedesigner_project.cpp').read_text()
header = (root / 'gamedesigner.h').read_text()
editor = (root / 'gamedesigner.cpp').read_text()

# Check the actual object-type allowlist used by loadDesign(), not just any
# occurrence of the keyword in the file.
match = re.search(
    r'const QString type\s*=\s*object\.value\(QStringLiteral\("type"\)\).*?'
    r'if\s*\(\s*QStringList\s*\{(?P<types>.*?)\}\.contains\(type\)'
    r'\s*&&\s*r\.kind\s*==\s*QStringLiteral\("sprite"\)\)\s*r\.objectType\s*=\s*type;',
    source, re.S,
)
assert match, 'Could not locate loadDesign() Game Object type restoration'
allowed = re.findall(r'QStringLiteral\("([^"\n]+)"\)', match['types'])
assert 'goto_world' in allowed, ('Goto World silently becomes decoration on load', allowed)
for existing in ('collectable','lift','conveyor','spring','trigger','door',
                 'deathzone','breakable','hazard','enemy'):
    assert existing in allowed, f'Existing Game Object type lost: {existing}'

# Ensure the world design .sbgm writer and reader both retain these values.
for key, member in (('type','r.objectType'),
                    ('gotoWorldName','r.gotoWorldName'),
                    ('gotoPress','r.gotoPress'),
                    ('gotoStartId','r.gotoStartId')):
    assert f'object.insert(QStringLiteral("{key}"), {member})' in source, f'Writer missing {key}'
    if key == 'type':
        assert 'r.objectType = type;' in match.group(0)
    else:
        assert re.search(r'r\.' + re.escape(member.split('.')[1]) +
                         r'\s*=\s*object\.value\(QStringLiteral\("' + key + r'"\)', source), f'Reader missing {key}'

assert 'r.objectType != QStringLiteral("decoration")' in source
assert 'QStringLiteral("goto_world")' in editor
assert 'QString gotoWorldName' in header
print('PASS Stage 5.26: Goto World type, destination, entrance and activation all survive .sbgm serialization contract')
