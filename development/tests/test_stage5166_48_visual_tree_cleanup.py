#!/usr/bin/env python3
"""Stage 5.166.48 source/schema regression for visual-node trees and orphan removal.
Full Qt GUI compilation and interactive mouse validation are separate checks.
"""
from pathlib import Path
import re

root=Path(__file__).resolve().parents[2]
source=(root/'gamevisualnodes.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
assert re.search(r'Build: 5\.166\.(\d+)\.\d{6}',version) and int(re.search(r'Build: 5\.166\.(\d+)\.\d{6}',version).group(1)) >= 48
assert 'QTreeWidgetItem *gameObjectsRoot=nullptr;' in source
assert 'QHash<QString,QTreeWidgetItem*> objectTypes;' in source
assert 'new QTreeWidgetItem(gameObjectsRoot,QStringList{label})' in source
assert 'new QTreeWidgetItem(parent,QStringList{object.name})' in source
assert 'new QTreeWidgetItem(tree,QStringList{tr("NPCs")})' in source
assert 'tree->collapseAll();' in source
assert 'if (query.isEmpty())tree->collapseAll();' in source
assert 'else tree->expandAll();' in source
assert source.index('tree->sortItems(0,Qt::AscendingOrder);',source.index('void showInsertTree(')) < source.index('populateDialogueChoices(tree,root);',source.index('void showInsertTree('))
assert 'Delete Selected' in source and 'Remove Orphans' in source
assert 'Delete Node (disconnect links)' in source and 'Remove All Orphaned Nodes...' in source
assert 'connectedCardIds() const' in source
assert 'if (!m_cards.contains(id) || connectedCardIds().contains(id))return 0;' in source
assert 'm_dialogueCards.remove(trigger);' in source
assert 'm_dialogueControls.remove(trigger);' in source
assert 'm_placedCards.remove(id);' in source
assert 'm_positions.remove(id);' in source
assert 'm_scene->removeItem(card);' in source and 'delete card;' in source
assert 'm_dirty=true;' in source[source.index('int removeOrphanCard('):source.index('void hideDisconnectedCards()')]
cleanup=source[source.index('int removeOrphanCard('):source.index('void disconnectDialogue(')]
for forbidden in ('m_touched.insert(', 'm_dialoguesChanged=true', 'node.links.removeAt(', 'writeJson(m_worldPath'):
    assert forbidden not in cleanup, forbidden
assert 'if (connectedCardIds().contains(id)) {' not in cleanup
assert 'if (!connected.contains(id))removed+=removeOrphanCard(id);' in source[source.index('void removeAllOrphans()'):source.index('void showCardContextMenu(')]
assert 'cardMenuRequested' in source
assert 'root.insert(QStringLiteral("placedCards"),placedCards);' in source
assert 'root.insert(QStringLiteral("positions"),positions);' in source
assert 'root.insert(QStringLiteral("connections")' not in source
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',source)
print('PASS Stage 5.166.48 hierarchy, collapsed picker, .vsgm-only orphan cleanup contracts')
