#!/usr/bin/env python3
"""Stage 5.60.1 regression: scene selection must never destroy clicked item.

This is a source-level regression, NOT a substitute for Qt GUI interaction tests.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
src = (root/'gametitlescreeneditor.cpp').read_text()

first = src.index('QObject::connect(scene,&QGraphicsScene::selectionChanged')
second = src.index('QObject::connect(target,qOverload<int>(&QComboBox::currentIndexChanged)', first)
third = src.index('QObject::connect(titleEdit,&QLineEdit::textChanged', second)
scene_handler = src[first:second]
target_handler = src[second:third]

assert 'target->setCurrentIndex(idx);' in scene_handler
assert 'handlingPreviewSelection=true;' in scene_handler
assert 'handlingPreviewSelection=false;' in scene_handler
assert 'render();' not in scene_handler, 'Click-to-select may destroy the QGraphicsItem before Qt finishes setSelected'
assert 'scene->clear()' not in scene_handler
assert 'render();' not in target_handler, 'Selecting an element must not rebuild the scene'
assert 'QSignalBlocker blocker(scene);' in target_handler
assert 'if(handlingPreviewSelection || rebuilding)return;' in target_handler
assert 'setSelected(shouldSelect)' in target_handler
assert 'if(it.key()->isSelected()!=shouldSelect)' in target_handler

# Full rebuild is still allowed when artwork or content actually changes.
assert 'scene->clear();' in src
assert 'QObject::connect(titleEdit,&QLineEdit::textChanged,&dialog,[&](const QString &){render();if(remember)remember();});' in src
assert 'if(changed) {' in src and 'updateProperties();' in src and 'if(remember)remember();' in src
assert 'Build: 5.63.231026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.60.1 title preview selection source regression: PASS')
