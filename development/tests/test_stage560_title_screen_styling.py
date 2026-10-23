#!/usr/bin/env python3
"""Stage 5.60 source/regression checks (Qt6 GUI compile still needed)."""
from pathlib import Path
import json
import tarfile

root=Path(__file__).resolve().parents[2]
s=(root/'gametitlescreeneditor.cpp').read_text()
assert 'TitleBackground background' in s
assert 'backgroundAtlas' in s and 'backgroundMode' in s
for mode in ('sprite', 'direct_ready', 'direct_convert'):
    assert f'QStringLiteral("{mode}")' in s
assert 'upright.scanLine(x)[y]=input[x]' in s  # Direct-prepared display only.
assert 'SidboxGamePalette::readPalette' in s
assert 'chooseTitleColour' in s and 'Foreground colour' in s and 'Outline colour' in s
assert 'Enable outline' in s
assert 'gfx_drawtextf' in (root/'idelibs/api/graphics/graphics.h').read_text()
assert '1<<(qBound(1,a.fontSize,4)-1)' in s
for key in ('foreground','outline','outlineEnabled','fontSize','background','textPalette'):
    assert f'QStringLiteral("{key}")' in s
assert 'QJsonValue(QJsonValue::Null)' in s
assert 'const bool hasDestination=(e.action==QStringLiteral("start")||e.action==QStringLiteral("goto"))' in s
assert 'worldCombo->setEnabled(destination)' in s and 'startCombo->setEnabled(destination)' in s
assert '(Not used)' in s
assert 'obj.insert(QStringLiteral("version"),3)' in s
assert 'obj.insert(QStringLiteral("saveSlots"),10)' in s
assert 'Build: 5.60.1.231026' in (root/'splashscreenwidget.cpp').read_text()
# Stage 5.59 entries without new fields remain readable via artFromJson fallback.
assert 'if (obj.isEmpty()) return a;' in s
assert 'a.foreground = qBound(0,obj.value(' in s
# The actual two-world project retains named starts and original PPBs.
example=Path('/mnt/data/GameTest3 - 23-10-2026-1549.tar.gz')
if example.exists():
    with tarfile.open(example,'r:gz') as tf:
        names=tf.getnames()
        assert any(name.endswith('world1.sbgm') for name in names)
        assert any(name.endswith('forest.sbgm') for name in names)
        assert any(name.lower().endswith('.ppb') for name in names)
print('Stage 5.60 design-time title styling checks: PASS')
