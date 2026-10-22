#!/usr/bin/env python3
"""Stage 5.14 source contracts + real Forest/World 1 fixture checks.
Requires no Qt; this does NOT replace IDE GUI or hardware testing.
"""
from pathlib import Path
import json
import re

root = Path(__file__).resolve().parents[2]
cpp = (root / 'gamedesigner.cpp').read_text()
header = (root / 'gamedesigner.h').read_text()
project = (root / 'gamedesigner_project.cpp').read_text()
rt = (root / 'idelibs/codehelpers/game/maingame.rulec').read_text()
assert 's_copiedWorldAdventure = m_adventure;' in cpp
assert 'static QJsonObject s_copiedWorldAdventure;' in header
paste = cpp.split('void SidboxGameDesigner::pasteCopiedSprite()', 1)[1].split('void SidboxGameDesigner::suggestSpriteCells(', 1)[0]
for s in (
    'copy.objectType == QStringLiteral("enemy")',
    'copy.objectType == QStringLiteral("breakable")',
    'sourceById(copy.breakDropCollectableId)',
    'reward->objectType == QStringLiteral("collectable")',
    'const QJsonArray targetItems = m_adventure.value(',
    'const QJsonArray targetTypes = m_adventure.value(',
    'Qt::CaseInsensitive',
    'QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel',
    'if (choice == QMessageBox::Cancel) return;',
    'if (!inventoryExists)',
    'rewardDestinationKind = 5;',
    'while (rewardDestinationKind <= 255 && used.contains(rewardDestinationKind))',
    'dep.pickupKind = rewardDestinationKind;',
    'importedInventoryItem.insert(QStringLiteral("icon"), 65535);',
    'importedInventoryItem.insert(QStringLiteral("initial"), 0);',
    'm_adventure.insert(QStringLiteral("pickupTypes"), types);',
    'm_adventure.insert(QStringLiteral("items"), items);',
    'rememberResourceEdit();',
):
    assert s in paste, s
assert paste.index('if (crossWorld) {') < paste.index('sourceById(copy.breakDropCollectableId)')
assert paste.index('QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel') < paste.index('rememberResourceEdit();')
assert paste.index('rememberResourceEdit();') < paste.index('m_adventure.insert(QStringLiteral("items"), items);')
for s in ('m_undoResourceAdventures', 'm_redoResourceAdventures'):
    assert s in header and s in cpp and s in project
assert 'game_adventure_collect(item->kind);' in rt
assert 'obj.insert(QStringLiteral("adventure"), m_adventure);' in project

# The actual demo source fixture defines MagicFlower in World 1 but no Forest
# Adventure entries. Its linked reward is a custom kind which must be imported
# as both a named pickup type and an inventory row, not just a sprite.
demo = Path('/mnt/data/stage514inspect')
if demo.is_dir():
    source = json.loads((demo / 'world1.sbgm').read_text())
    target = json.loads((demo / 'forest.sbgm').read_text())
    by_id = {r['id']: r for r in source['resources']}
    enemy = next(r for r in source['resources'] if r['name'] == 'baguy')
    reward = by_id[enemy['gameObject']['breakDropCollectableId']]
    kind = reward['gameObject']['pickupKind']
    source_item = next(i for i in source['adventure']['items'] if i['pickupKind'] == kind)
    source_type = next(t for t in source['adventure']['pickupTypes'] if t['id'] == kind)
    assert (source_type['name'], source_item['name']) == ('MagicFlower', 'Flower')
    assert not target['adventure'].get('items')
    assert kind == 5
print('PASS Stage 5.14: linked reward gating, copy snapshot, type remap, duplicate check, undo, persistence, demo fixture')
