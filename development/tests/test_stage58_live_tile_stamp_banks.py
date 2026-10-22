#!/usr/bin/env python3
"""Stage 5.8 contracts for live atlas stamp sync across open world tabs.
This is source inspection, NOT a Qt GUI/runtime test.
"""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
read=lambda fn:(root/fn).read_text()
project=read('gamedesigner_project.cpp')
designer=read('gamedesigner.cpp')
header=read('gamedesigner.h')
assert 'void syncProjectTileStampBanks(const QJsonObject &banks);' in header
assert 'void SidboxGameDesigner::syncProjectTileStampBanks(const QJsonObject &banks)' in project
assert 'm_loadedTileStampBanks = banks;' in project
assert 'm_tilemap.tileStampBanks = merged;' in project
assert 'm_tilemap.stamps = stamps;' in project
assert 'if (!merged.contains(it.key()) && !m_loadedTileStampBanks.contains(it.key()))' in project
assert 'if (it.value() == oldValue) continue;' in project
assert 'bank.tileStampBanks.insert(it.key(), it.value())' in project
assert 'QApplication::allWidgets()' in project
assert 'dynamic_cast<SidboxGameDesigner *>(widget)' in project
assert 'QFileInfo(other->m_filePath).absolutePath() == projectDir' in project
assert 'other->syncProjectTileStampBanks(m_loadedTileStampBanks)' in project
assert 'syncProjectTileStampBanks(liveBank.tileStampBanks);' in designer
assert 'if (!saveDesign()) return false;' in designer
assert 'const bool needsExport = !fromSaveButton && tilemapBuildFilesMissing();' in designer
assert 'Reopen this world before saving tile stamps.' not in project
assert 'editor.setSaveCallback([this, &applyChanges, &editor]' in designer
assert 'editor.acknowledgeGlobalStampSave();' in designer
assert 'editor.syncCommittedTileStampBanks(m_tilemap.tileStampBanks);' in designer
assert 'qobject_cast<SidboxGameDesigner' not in project  # class has no Q_OBJECT
print('PASS Stage 5.8: live same-project tab sync, conflict-safe atlas merge, Save/Apply .proj commit')
