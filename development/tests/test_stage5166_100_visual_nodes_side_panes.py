"""Stage 5.166.100 sidebar source-contract checks (not a Qt GUI test)."""
from pathlib import Path

root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
sp=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.100.291026' in sp
# No verbose teaching banner or old width cap.
assert 'Use + Conversation Flow or right-click an NPC to edit Adventure dialogue branches.' not in s
assert 'left->setMaximumWidth(270)' not in s
# Registered cards are classified into a real tree, with filtering and navigation.
assert 'm_visibleTree=new QTreeWidget(left)' in s
assert 'm_treeSearch=new QLineEdit(left)' in s
assert 'm_list=new QListWidget(this)' in s  # Legacy registration model, hidden.
assert 'm_list->hide()' in s
assert 'void scheduleVisibleTreeRefresh()' in s
for category in ('Conversation Flows','Dialogue Actions','Game Objects','NPCs','PLAYER','Logic','Triggers'):
    assert 'tr("'+category+'")' in s
assert 'm_visibleTree,&QTreeWidget::itemDoubleClicked' in s
assert 'm_view->centerOn(m_cards.value(id))' in s
# Structured inspector, with verbose notes optional.
assert 'm_inspectorTree=new QTreeWidget(right)' in s
assert 'void refreshCardInspector(const QString &id)' in s
assert 'm_details->setVisible(false)' in s
for field in ('Requires FIRE2','Remove after use','Initially visible','Talk radius',
              'Required items','Tracked item','Missing','Linked actions','Operator'):
    assert field in s,field
# Resizable panes persisted as display-only .vsgm metadata.
assert 'split->setChildrenCollapsible(false)' in s
assert 'split->setSizes({255,1000,340})' in s
assert 'graph.value(QStringLiteral("paneWidths"))' in s
assert 'm_splitter->setSizes(m_savedPaneWidths)' in s
assert 'root.insert(QStringLiteral("paneWidths")' in s
assert 'graph.insert(QStringLiteral("paneWidths"),paneWidths)' in s
assert 'm_theme.inputBackground.name()' in s
print('PASS Stage 5.166.100 sidebar tree, inspector, pane widths and no banner')
