#!/usr/bin/env python3
"""Stage 5.118: combo chevrons and subtle dependency outlines."""
from pathlib import Path
import hashlib
import re
import subprocess
import tempfile

root=Path(__file__).resolve().parents[2]
qss=(root/'ideglobaltheme.h').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
ed=(root/'gameadventureeditor.cpp').read_text()
assert 'Build: 5.118.251026' in splash
assert 'inline QString ideComboDownArrowImageUrl(' in qss
assert 'QPainter painter(&arrow);' in qss
assert 'QImage arrow(12, 9, QImage::Format_ARGB32_Premultiplied);' in qss
assert 'image:url("@comboArrow")' in qss
assert 'image:url("@comboArrowDisabled")' in qss
assert 'image:url("@localComboArrow")' in qss
assert 'image:url("@localComboArrowDisabled")' in qss
assert 'QComboBox[customChevron="true"]::down-arrow' in qss
assert 'QComboBox[adventureGuard="true"]:enabled' in qss
assert 'QComboBox[adventureGuard="true"]:disabled' in qss
# The per-combo popup stylesheet used to erase the global disabled state.
local=qss[qss.index('QString comboRules ='):qss.index('const QString newComboStyle =')]
for token in ('@localAdvRed','@localAdvGreen','@localAdvRedBg','@localAdvGreenBg',
              '@localComboArrow','@localComboArrowDisabled','@localDisabledText'):
    assert token in local
    assert f'comboRules.replace(QStringLiteral("{token}")' in local
assert local.index('QComboBox[adventureGuard="true"]:enabled') < local.index('QComboBox QAbstractItemView')
assert re.search(r'QComboBox\[adventureGuard="true"\]:disabled\s*\{\s*border:1px solid @localAdvRed;', local)
assert 'const QColor adventureGreenBorder=blend(theme.border,adventureGreen,48);' in qss
assert 'const QColor adventureRedBorder=blend(theme.border,adventureRed,58);' in qss
assert 'border:2px solid @advGreen' not in qss
assert 'border:2px solid @advRed' not in qss
assert 'const QColor adventureGreenBg=blend(theme.inputBackground,adventureGreen,5);' in qss
assert 'const QColor adventureRedBg=blend(theme.panelBackground,adventureRed,11);' in qss
assert ed.count('->setEnabled(')==45  # dependency logic unchanged
# Ensure the new stage did not alter the game runtime or saved-world format.
previous=Path('/mnt/data/ide_251026_stage5117')
for file in ('gameadventureeditor.cpp','gameadventureruntime.cpp','gameadventureeditor.h'):
    before=previous/file
    after=root/file
    if before.exists(): assert hashlib.sha256(before.read_bytes()).digest()==hashlib.sha256(after.read_bytes()).digest(),file
print('Stage 5.118 chevron + dependency styling contracts: PASS')
