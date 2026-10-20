#!/usr/bin/env python3
"""Stage 3.94: portable source checks for the Qt6 Game Object Properties polish."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[2]
src = (root / 'gamedesigner.cpp').read_text()
assert src.count('void SidboxGameDesigner::configureGameObject(int index)') == 1
fn = src.split('void SidboxGameDesigner::configureGameObject(int index)',1)[1].split('void SidboxGameDesigner::refreshObjectHitbox()',1)[0]
assert 'QListWidget#GGObjectTypes::item:selected' in fn
assert 'border:1px solid %6; border-left:3px solid %6' in fn
assert 'QCheckBox::indicator:checked { background:%6; border-color:%6; }' in fn
assert 'QCheckBox::indicator { width:16px; height:16px;' in fn
# Section header remains clickable and has a left icon / right disclosure.
assert 'toggle->setIconSize(QSize(16, 16))' in fn
assert 'barLayout->addWidget(toggle, 1)' in fn
assert 'barLayout->addWidget(arrow)' in fn
assert 'connect(arrow, &QToolButton::clicked, toggle, &QToolButton::toggle)' in fn
assert 'toggle->setText(name)' in fn
# Paired settings must not introduce new object fields.
assert 'pairFields(tr("Pickup Type"), pickup, tr("Pickup Value"), value)' in fn
assert 'pairFields(tr("Pickup sound"), sfxPickup' in fn
assert 'tr("Respawn sound"), sfxRespawn)' in fn
assert 'pairFields(tr("Audible radius"), radius' in fn
assert 'tr("Loop fade frames"), fade)' in fn
for k in (1,2,3,4): assert f'pickup->addItem(pickupIcon({k})' in fn
assert 'SPRITE INFO' in fn and 'COLLISION PREVIEW' in fn
assert 'collisionDimensions->addRow(tr("Width"), quickValue(hitW))' in fn
assert 'collisionDimensions->addRow(tr("Height"), quickValue(hitH))' in fn
assert 'previewScroll->setWidget(previewPanel)' in fn
assert 'const auto updatePreview = [this, &previewFrame, &atlas, &old, animated,' in fn
assert 'const auto makeCanvas = [this, frame, hitW, hitH]' in fn
# Existing runtime fields are still assigned after user accepts the dialog.
for field in ('objectType', 'pickupKind', 'objectValue', 'hitWidth', 'hitHeight',
              'respawnFrames', 'audioRadius', 'audioFadeFrames',
              'sfxPickup', 'sfxRespawn', 'sfxBreakHit', 'sfxBreakBounce',
              'sfxBreakFinish', 'sfxHazardHit', 'sfxHazardAmbient',
              'drawBehindTiles', 'hazardFlashColour', 'animTicks'):
    assert re.search(r'\br\.' + field + r'\s*=',fn), field
assert 'r.hitWidth = hitW->value(); r.hitHeight = hitH->value();' in fn
assert 'hitW->value()*sx' in fn and 'hitH->value()*sy' in fn
assert 'dialog.exec();' in fn and 'if (commitObject()) dialog.accept();' in fn
print('PASS: Stage 3.94 polished controls and preserved object save fields')
