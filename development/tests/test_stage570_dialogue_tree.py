"""Stage 5.70 source-level checks for folder-tree drop-down wiring."""
from pathlib import Path
p=Path(__file__).resolve().parents[2]
s=(p/'gameadventureeditor.cpp').read_text()
assert 'class DialogueTreeCombo final : public QComboBox' in s
assert 'void showPopup() override' in s
assert 'new QTreeWidget(popup)' in s
assert 'setPlaceholderText(tr("Find dialogue, speaker or folder..."))' in s
assert 'folder.value(QStringLiteral("parentId"))' in s
assert 'value(QStringLiteral("folderId"))' in s
assert 'new QTreeWidgetItem(parent)' in s
assert 'const int row=entry->data(0,Qt::UserRole).toInt();' in s
assert 'setCurrentIndex(row);' in s
assert 'itemData(row).toInt()' in s
assert 'QComboBox *combo=new DialogueTreeCombo(owner ? owner : response,&nodes,&folders)' in s
assert 'fields[i].next=new DialogueTreeCombo(box,&nodes,&folders)' in s
assert 'fields[i].missingNext = new DialogueTreeCombo(box,&nodes,&folders)' in s
assert 'new DialogueTreeCombo(afterHelp,&nodes,&folders)' in s
assert 'new DialogueTreeCombo(npcs,&nodes,&dialogueFolders)' in s
assert 'new DialogueTreeCombo(positionPage,&nodes,&dialogueFolders)' in s
assert 'editExchange(&dialog,before,items,nodes,objects,folders)' in s
assert 'editNode(&dialog,nodes,row,tableItems(items),worldObjects,npcs,dialogueFolders)' in s
assert 'Build: 5.71.4.241026' in (p/'splashscreenwidget.cpp').read_text()
assert '2048' in (p/'mainwindow.cpp').read_text()
print('Stage 5.70 folder tree selectors / ID preservation wiring PASS')
