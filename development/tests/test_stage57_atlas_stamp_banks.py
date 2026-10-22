#!/usr/bin/env python3
"""Source contracts for atlas-keyed tile stamp banks, IDE-only Stage 5.7.
Requires Qt6 GUI testing for actual editor interactions.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
def source(name): return (root / name).read_text()
model = source('gametilemapmodel.cpp')
header = source('gametilemap.h')
editor = source('gametilemap.cpp')
bank = source('gameglobalstamps.h')
project = source('gamedesigner_project.cpp')
designer = source('gamedesigner.cpp')
assert 'QJsonObject tileStampBanks;' in header
assert 'stampsToJson(' in header and 'stampsFromJson(' in header
assert 'bool SidboxTilemap::stampsFromJson(' in model
assert 'QJsonArray SidboxTilemap::stampsToJson(' in model
assert 'gameTileStampBanks' in bank
assert 'tileStampBanks = root.value(QStringLiteral("gameTileStampBanks")).toObject()' in bank
assert 'root.insert(QStringLiteral("gameTileStampBanks"), tileStampBanks)' in bank
assert 'world.remove(QStringLiteral("stamps"))' in bank
assert 'QJsonObject m_loadedTileStampBanks;' in source('gamedesigner.h')
assert 'm_tilemap.tileStampBanks = bank.tileStampBanks;' in project
assert 'const QJsonValue savedAtlasBank = bank.tileStampBanks.value(atlasKey);' in project
assert 'SidboxTilemap::stampsFromJson(savedAtlasBank.toArray(), &m_tilemap.stamps)' in project
assert 'SidboxTilemap::stampsToJson(m_tilemap.stamps)' in project
assert 'bank.tileStampBanks.insert(it.key(), it.value())' in project
assert 'bank.tileStampBanks != m_loadedTileStampBanks' not in project
assert 'm_loadedTileStampBanks = bank.tileStampBanks;' in project
assert 'void SidboxTilemapEditor::setAtlas(const QString &absolutePath, bool switchBank)' in editor
assert 'm_map.tileStampBanks.insert(' in editor
assert 'SidboxTilemap::stampsFromJson(m_map.tileStampBanks.value(nextKey).toArray(), &bank)' in editor
assert 'setAtlas(full, false);' in editor # undo restores the snapshot, not stale bank
assert '|| a.tileStampBanks != b.tileStampBanks' in editor
assert 'tr("Remove Tile Stamp")' in editor
assert 'QMessageBox::Yes | QMessageBox::No, QMessageBox::No' in editor
assert 'QLineEdit::returnPressed, this, commitTileStampName' in editor
assert 'QLineEdit::editingFinished, this, commitTileStampName' in editor
assert 'm_stampName && m_stampName->hasFocus()' in editor
assert 'Tile Atlas Stamp Bank (shared)' in editor
assert 'editor.acknowledgeGlobalStampSave();' in designer
assert 'editor.syncCommittedTileStampBanks(m_tilemap.tileStampBanks);' in designer
print('PASS Stage 5.7: project atlas bank storage, world projection, switching/undo, delete confirmation, rename')
