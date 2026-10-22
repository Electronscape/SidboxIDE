#!/usr/bin/env python3
"""Stage 5.15: inventory icon previews must be reconstructed from saved indices.
Source regression only: Qt6 GUI compilation and interactive tests remain pending.
"""
from pathlib import Path
import json

root = Path(__file__).resolve().parents[2]
source = (root / 'gameadventureeditor.cpp').read_text()
start = source.index('bool editGameAdventure(')
editor = source[start:]
assert 'iconCell->setData(Qt::UserRole,iconIndex);' in editor
assert 'item.insert("icon",table->item(r,4)' in source

refresh_start = editor.index('const auto refreshInventoryIcons = [&] {')
refresh_end = editor.index('    auto appendItem =', refresh_start)
refresh = editor[refresh_start:refresh_end]
for contract in [
    'skinAtlas->currentData().toString()',
    'old.value("skinAtlasId").toString()',
    'tileSize->value()',
    'indexedPreview(atlas->path, foregroundPalette)',
    'entry->data(Qt::UserRole).toInt()',
    'entry->setIcon(QIcon());',
    'index == 65535',
    'index >= columns * rows',
    'index % columns',
    'index / columns',
    'QPixmap::fromImage',
]:
    assert contract in refresh, contract
assert editor.count('refreshInventoryIcons();') == 4, 'pick, atlas change, size change, initial load'
assert editor.index('updatePreview();\n    refreshInventoryIcons();') > editor.index('skinAtlas=new QComboBox')
# Confirm an existing inventory icon can exceed a single 256-cell page.
fixture = Path('/mnt/data/stage514inspect/world1.sbgm')
if fixture.exists():
    game = json.loads(fixture.read_text())
    assert any(item.get('icon', 65535) > 255 and item.get('icon') != 65535
               for item in game['adventure']['items'])
# No changes to map/engine runtime or Adventure schema are needed.
print('PASS Stage 5.15: saved index, atlas-dependent reconstruction, invalid/missing asset protection, initial + live refresh')
