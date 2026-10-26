#!/usr/bin/env python3
"""Stage 5.140: Qt 6.11 deprecation-free shortcut construction.

The legacy int key-code conversion was deprecated in Qt 6.11. Ensure all
shortcut definitions use QKeyCombination and preserve existing bindings.
"""
from pathlib import Path
import hashlib

root = Path(__file__).resolve().parents[2]
previous = Path('/mnt/data/ide_251026_stage5139')
flow = (root / 'gamefloweditor.cpp').read_text()
viewer = (root / 'mainwindow.cpp').read_text()
tilemap = (root / 'gametilemap.cpp').read_text()
title = (root / 'gametitlescreeneditor.cpp').read_text()
assert 'Build: 5.140.251026' in (root / 'splashscreenwidget.cpp').read_text()

for src, callback, bindings in (
    (flow, 'flowCanvasShortcut', ('Plus', 'Equal', 'Minus', '1', 'F')),
    (viewer, 'bindViewerKey', ('Plus', 'Equal', 'Minus', '1', 'F')),
):
    assert f'const auto {callback}' in src
    assert '(Qt::Key key, QPushButton *button)' in src
    assert 'QKeySequence(QKeyCombination(Qt::ControlModifier, key))' in src
    for key in bindings:
        assert f'{callback}(Qt::Key_{key},' in src
        assert f'{callback}(Qt::CTRL | Qt::Key_{key},' not in src
    assert 'QKeySequence(key), view' not in src

assert 'QKeySequence(QKeyCombination(Qt::ControlModifier, Qt::Key_G))' in flow
assert 'QKeySequence(QKeyCombination(Qt::ControlModifier | Qt::ShiftModifier, Qt::Key_G))' in flow
for src, keys in ((title, ('Y',)), (tilemap, ('Y', 'Z'))):
    for key in keys:
        assert f'QKeySequence(QKeyCombination(Qt::ControlModifier, Qt::Key_{key}))' in src
    assert 'QKeySequence(QKeyCombination(Qt::ControlModifier | Qt::ShiftModifier, Qt::Key_Z))' in src
for src in (flow, viewer, tilemap, title):
    assert 'QKeySequence(Qt::CTRL' not in src

# IDE hotfix only: no runtime, save data or palette editing changes.
for relative in (
    'gameadventureeditor.cpp', 'gamedesigner.cpp', 'gameadventuregen.cpp',
    'gamepaletteeditor.cpp', 'gamepaletteeditor.h',
    'ppbcodec.cpp', 'ppbcodec.h',
    'idelibs/codehelpers/game/adventureruntime.rulec',
    'idelibs/codehelpers/game/adventureruntime.ruleh',
):
    new = (root / relative).read_bytes()
    old = (previous / relative).read_bytes()
    assert hashlib.sha256(new).digest() == hashlib.sha256(old).digest(), relative
print('Stage 5.140 shortcut and unchanged runtime checks PASS')
