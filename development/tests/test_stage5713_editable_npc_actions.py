#!/usr/bin/env python3
"""Regression for 5.71.2 disabled NPC selectors on answerless dialogue nodes.

No Qt packages in this test environment. Check editor's signal wiring and
save/migration contract alongside the independent native runtime tests.
"""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
source=(root/'gameadventureeditor.cpp').read_text()
assert '#include <QSignalBlocker>' in source
assert 'f.npcTargets[effect]->setEnabled(true);' in source
assert 'f.npcModes[effect]->setEnabled(true);' in source
assert 'fields[i].npcTargets[effect]->setEnabled(hasAnswer)' not in source
assert 'fields[i].npcModes[effect]->setEnabled(hasAnswer)' not in source
# Changes to a choice row must update the persisted on-close selector, and vice versa.
assert 'chooseCloseNpcFromChoice(i,effect);' in source
assert 'onCloseNpcTarget[effect]->setCurrentIndex' in source
assert 'onCloseNpcMode[effect]->setCurrentIndex' in source
assert 'mirrorCloseNpc(effect);' in source
assert 'const QSignalBlocker blockTarget' in source
assert 'const QSignalBlocker blockMode' in source
# Only mirror actions for answerless final dialogue nodes.
assert 'if (syncingCloseNpc || hasAnyAnswer()) return;' in source
assert 'if (noAnswersAfterEdit) for' in source
assert 'choice.insert(prefix+QStringLiteral("SpriteId"),QString());' in source
# On-close NPC actions and gift should be visible near the top instead of below unused answers.
assert 'detail->insertWidget(1,onCloseGroup);' in source
assert 'Give item when dialogue closes' in source
assert 'Build: 5.71.5.241026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.71.3 editable NPC actions, mirrored on-close state, and save checks PASS')
