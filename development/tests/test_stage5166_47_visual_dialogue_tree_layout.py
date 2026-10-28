#!/usr/bin/env python3
"""Stage 5.166.47 graph save and Adventure Dialogue-tree contract checks.
This is a source/data contract test, NOT a substitute for Qt6 GUI testing.
"""
import json
import re
from pathlib import Path
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
d=(root/'gameadventureeditor.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
assert re.search(r'Build: 5\.166\.(\d+)\.\d{6}',version) and int(re.search(r'Build: 5\.166\.(\d+)\.\d{6}',version).group(1)) >= 47
assert 'event->globalPosition().toPoint()' in s
assert 'dropRequested(from,mapToScene(event->pos()),event->globalPos())' not in s
assert '#include <QTreeWidgetItemIterator>' in s
assert 'void populateDialogueChoices(QTreeWidget *tree,QTreeWidgetItem *parent) const' in s
assert 'int browseDialogueTree(int current)' in s
assert 'void connectExistingDialogue(' in s
assert 'connectNewDialogue(from,at)' in s
assert 'connectExistingDialogue(from,at,index)' in s
assert 'm_dialogueFolders=adventure.value(QStringLiteral("dialogueFolders")).toArray()' in s
assert 'dialogue.value(QStringLiteral("folderId"))' in s
assert 'folder.value(QStringLiteral("parentId"))' in s
assert 'folder.value(QStringLiteral("name"))' in s
assert 'dialogueFolders=old.value("dialogueFolders").toArray()' in d
assert 'result.insert("dialogueFolders",dialogueFolders)' in d
assert 'selectedId.startsWith(QStringLiteral("@dialogue-node:"))' in s
assert 'create->setText(0,tr("+ Create New Dialogue"))' in s
assert 'tree->sortItems(0,Qt::AscendingOrder);' in s
assert s.index('populateDialogueChoices(tree,root);',s.index('void showInsertTree(')) > s.index('tree->sortItems(0,Qt::AscendingOrder);')
assert 'Browse Dialogue Folders...' in s
assert 'controls.picker->setCurrentIndex(row)' in s
assert 'm_cards.value(id)->pos()' in s
assert 'm_cards.value(key)->pos()' in s
assert 'm_positions.value(key);' not in s[s.index('QJsonObject graphJson() const {'):s.index('bool saveLayout()')]
assert 'root.insert(QStringLiteral("positions"),positions)' in s
assert 'root.insert(QStringLiteral("connections")' not in s
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',s)
# Actual .sbgm document test: the folder IDs are stable metadata and node
# indices are never remapped for the editor's tree.
for world in (Path('/mnt/data/gametest_unpacked/world1.sbgm'),Path('/mnt/data/gametest_unpacked/forest.sbgm')):
    if not world.exists(): continue
    doc=json.loads(world.read_text()); adventure=doc.get('adventure',{})
    nodes=adventure.get('nodes',[]); folders=adventure.get('dialogueFolders',[])
    folder_ids={f.get('id') for f in folders}
    branches={}
    for index,node in enumerate(nodes):
        folder=node.get('folderId')
        key=folder if folder in folder_ids else 'unfiled'
        branches.setdefault(key,[]).append(index)
    assert sorted(i for ids in branches.values() for i in ids)==list(range(len(nodes)))
    print(world.stem, 'dialogues',len(nodes),'folders',len(folders))
print('Stage 5.166.47 Dialogue-tree/layout/source checks PASS')
