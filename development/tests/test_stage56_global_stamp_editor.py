#!/usr/bin/env python3
"""Stage 5.6 source contracts: shared slope removal, rename and global loop list.

Qt6 GUI build/hardware behaviour still require testing on a Qt6-equipped host.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
load = lambda filename: (root / filename).read_text()
ui = load('gametilemap.cpp')
model = load('gametilemap.h')
project = load('gamedesigner_project.cpp')
bank = load('gameglobalstamps.h')
designer = load('gamedesigner.cpp')
assert 'm_map.collisionOriginalIndices.removeAt(row);' in ui
assert 'm_map.collisionOriginalIndices.append(-1);' in ui
assert 'm_collisionList->currentRow()' in ui
assert 'removeCollision->setEnabled(false);' in ui # initially disabled, enabled on selection
assert 'connect(m_collisionList, &QListWidget::currentRowChanged, removeCollision,' in ui
assert 'removeCollision->setToolTip(tr("Remove this shared slope' in ui
assert 'const auto commitCollisionName = [this]()' in ui
assert 'QLineEdit::returnPressed, this, commitCollisionName' in ui
assert 'QLineEdit::editingFinished, this, commitCollisionName' in ui
assert 'm_collisionName->hasFocus()' in ui
assert 'GGGlobalLoopStampBank' in ui
assert 'Global Loop Stamp Bank (all worlds)' in ui
assert 'Placed Loops (this world only)' in ui
assert 'globalLoopList->setCurrentRow(l.stamp)' in ui
assert 'loopStampPicker->hide();' in ui
assert 'QVector<int> collisionOriginalIndices' in model
assert 'm_tilemap.collisionOriginalIndices.append(i < m_loadedGlobalCollisionBank.size() ? i : -1);' in project
assert 'QVector<int> oldToNew(bank.collisions.size(), -1);' in project
assert 'bank.remapOtherWorlds(m_filePath, m_loadedGlobalCollisionBank,' in project
assert 'void acknowledgeGlobalStampSave();' in model.replace('QVector<int> collisionOriginalIndices;', 'QVector<int> collisionOriginalIndices;') or 'void acknowledgeGlobalStampSave();' in model
assert 'editor.acknowledgeGlobalStampSave();' in designer
assert 'bool remapOtherWorlds(' in bank
assert 'oldToNew.at(old)' in bank
assert 'cells[yy * width + xx] = char(0);' in bank
assert 'map.remove(QStringLiteral("collisionStamps"))' in bank
assert 'QSaveFile output(rewrite.path)' in bank
print('PASS Stage 5.6: global slope deletion/remap, Return commit, visible global loop bank')
