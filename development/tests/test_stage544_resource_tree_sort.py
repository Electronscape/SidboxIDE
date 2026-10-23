#!/usr/bin/env python3
"""Stage 5.44: fixed Game Resources root order and child-only A-Z sorting."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
s = (root / 'gamedesigner.cpp').read_text()
refresh = s.split('void SidboxGameDesigner::refreshResources()', 1)[1].split('\nQImage SidboxGameDesigner::cachedImage', 1)[0]
rename = s.split('connect(m_propName, &QLineEdit::textEdited', 1)[1].split('    for (QSpinBox *spin', 1)[0]

# Whole-tree sorting would reorder the top-level categories.
assert 'm_resourceTree->setSortingEnabled(false);' in s
assert 'm_resourceTree->sortItems(' not in refresh
assert 'm_resourceTree->setSortingEnabled(true)' not in s
assert 'm_resourceTree->sortChildren(' not in refresh

# The existing top-level creation order is part of the contract.
starts = refresh.index('auto *startsRoot = new QTreeWidgetItem(m_resourceTree')
regular = refresh.index('for (const QString &kind : {')
objects = refresh.index('auto *objectsRoot = new QTreeWidgetItem(m_resourceTree')
splines = refresh.index('auto *splinesRoot = new QTreeWidgetItem(m_resourceTree')
assert starts < regular < objects < splines
categories = refresh[regular:refresh.index('auto *root = new QTreeWidgetItem(m_resourceTree', regular)]
for term in ('"sprite"', '"tileatlas"', '"background"', '"palette"', '"sound"', '"music"'):
    assert term in categories
assert [categories.index(x) for x in ('"sprite"','"tileatlas"','"background"','"palette"','"sound"','"music"')] == sorted(
    categories.index(x) for x in ('"sprite"','"tileatlas"','"background"','"palette"','"sound"','"music"'))

# Child groups are sorted after they have been populated.
for group in ('startsRoot', 'objectsRoot', 'splinesRoot', 'frontRoot', 'backRoot', 'root'):
    assert f'{group}->sortChildren(0, Qt::AscendingOrder);' in refresh, group
assert refresh.index('startsRoot->sortChildren') < regular
assert refresh.index('objectsRoot->sortChildren') < splines
assert refresh.index('splinesRoot->sortChildren') < refresh.index('refreshPaletteSelectors();')

# A rename can affect both the Sprites row and Game Objects alias; resort
# only when tree iteration is over to avoid corrupting that iterator.
assert 'QSet<QTreeWidgetItem *> renamedParents;' in rename
assert rename.index('renamedParents.insert(item->parent());') < rename.index('parent->sortChildren(0, Qt::AscendingOrder);')
assert 'group == QStringLiteral("sprite") || group == QStringLiteral("gameobject")' in rename

# Indices/IDs and selection restore stay intact (sorting is presentation only).
for term in ('child->setData(0, Qt::UserRole, index);',
             'item->setData(0, Qt::UserRole, i);',
             'item->setData(0, Qt::UserRole + 3, path.id);',
             'selectedGroup == QStringLiteral("gameobject")',
             'selectResource(preserve);',
             'expandedGroups.value'):
    assert term in refresh, term

assert re.search(r'Build: 5\.44(?:\.\d+)?\.231026', (root / 'splashscreenwidget.cpp').read_text())
print('Stage 5.44 resource categories, child sorting, live rename, selection and version: PASS')
