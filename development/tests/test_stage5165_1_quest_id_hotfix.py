#!/usr/bin/env python3
"""Regression for Stage 5.165.1: ID format accepted by editor and publisher.

Qt6 headers are unavailable in this CI container. This test checks source
contracts and exercises the exact accepted ID expression with representative
quest/objective examples, including the ID from the hardware report.
"""
from pathlib import Path
import re

root=Path(__file__).resolve().parents[2]
gen=(root/'gamequestgen.h').read_text()
editor=(root/'gamequesteditor.cpp').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()

assert 'return validate(*quests,error);' in gen, 'publisher must use shared validator'
assert 'GameQuestGen::validate(quests,&why)' in editor, 'editor must share validator'
assert 'newId("quest_")' in editor and 'newId("obj_")' in editor
assert ".remove(QLatin1Char('-')).left(12)" in editor, 'new IDs must not include UUID separators'
assert 'Build: 5.166.12.271026' in splash

found=re.search(r'const QRegularExpression idRe\(QStringLiteral\("([^"\n]+)"\)\);',gen)
assert found, 'shared validation regex missing'
pattern=re.compile(found.group(1))
for id_value in ('quest_2005cee2-aae', 'obj_342fec0e-7a5', 'quest_2005cee2aae',
                 'obj_abcdefgh1234', 'forest'):
    assert pattern.fullmatch(id_value), ('valid stable ID rejected', id_value)
for id_value in ('bad space','bad/slash','bad:colon','-leading','', '3leading',
                 'x'*49):
    assert not pattern.fullmatch(id_value), ('bad stable ID accepted', id_value)

# Existing user data is read/validated, NEVER normalised in situ: changing
# stable IDs would invalidate quest-aware saves and prerequisite references.
assert 'q["id"]=' not in gen and 'o["id"]=' not in gen
print('PASS Stage 5.165.1: old generated IDs accepted, new IDs safe, single validator, identities preserved')
