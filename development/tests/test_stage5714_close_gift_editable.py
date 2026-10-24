#!/usr/bin/env python3
"""Regression for Stage 5.71.4 editable NPC gives on answerless dialogue nodes.

Qt6 headers are unavailable on the host runner, so validate editor signal wiring,
serialization and the shared source/runtime contract. Native runtime tests are run
separately using the same project generator rules.
"""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
e=(root/'gameadventureeditor.cpp').read_text()
assert 'bool syncingCloseGift = false;' in e
assert 'const auto mirrorCloseGift = [&]()' in e
assert 'const auto chooseCloseGiftFromChoice = [&](int i)' in e
assert 'if (syncingCloseGift || hasAnyAnswer()) return;' in e
assert 'const QSignalBlocker blockGift(f.give);' in e
assert 'const QSignalBlocker blockGift(onCloseGift);' in e
assert 'onCloseGift->currentData().toInt()' in e
assert 'onCloseGift->setCurrentIndex(std::max(0,' in e
assert 'f.give->setEnabled(terminal || hasAnswer);' in e
assert 'f.give->setEnabled(hasAnswer);' not in e
assert 'mirrorCloseGift();' in e
assert 'chooseCloseGiftFromChoice(i);' in e
assert 'node.insert("closeGiveItem",onCloseGift->currentData().toInt());' in e
assert 'choice.insert("give",-1); /* empty answers cannot award items */' in e
assert 'detail->insertWidget(1,onCloseGroup);' in e
assert 'Build: 5.71.5.241026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.71.4 editable gift combo, two-way terminal mirroring, save + guard source checks PASS')
