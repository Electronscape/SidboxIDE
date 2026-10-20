#!/usr/bin/env python3
"""Stage 4.15: checkbox, slider, tree and popup theme consistency."""
from pathlib import Path
p = Path(__file__).resolve().parents[2]
css = (p / 'ideglobaltheme.h').read_text()
main = (p / 'mainwindow.cpp').read_text()
world = (p / 'gamedesigner.cpp').read_text()
tile = (p / 'gametilemap.cpp').read_text()
assert 'inline QPalette ideGlobalControlPalette(const IDETheme &theme)' in css
assert 'qApp->setPalette(ideGlobalControlPalette(m_theme));' in main
assert main.index('qApp->setPalette(ideGlobalControlPalette(m_theme))') < main.index('qApp->setStyleSheet(ideGlobalControlStyle(m_theme))')
assert 'QPalette::AlternateBase, theme.alternateBackground' in css
assert '{"@alternate", theme.alternateBackground}' in css
assert 'QTreeView, QTreeWidget, QListView, QListWidget, QTableView, QTableWidget' in css
assert 'alternate-background-color:@alternate;' in css
assert 'image:url("@tick")' in css
assert 'border-image:url("@tick")' not in css
assert 'QDir::fromNativeSeparators(file)' in css
assert 'return QUrl::fromLocalFile(file).toString()' not in css
assert 'QCheckBox::indicator:checked:disabled' in css
assert 'QSlider::groove:horizontal { height:4px;' in css
assert 'QSlider::groove:vertical { width:4px;' in css
assert 'width:10px; margin:-4px 0;' in css
assert 'height:10px; margin:0 -4px;' in css
assert 'QComboBoxPrivateContainer' in css
assert 'QComboBox QAbstractItemView::item:selected' in css
assert 'for (QComboBox *combo : findChildren<QComboBox *>())' not in world[world.index('void SidboxGameDesigner::setTheme('):world.index('    refreshColours();', world.index('void SidboxGameDesigner::setTheme('))]
assert 'QAbstractItemView::item:selected { background:%4' not in tile[tile.index('void SidboxTilemapEditor::setTheme('):tile.index('SidboxTilemapEditor::SidboxTilemapEditor', tile.index('void SidboxTilemapEditor::setTheme('))]
assert 'm_previewBackgroundChoice' in (p/'gameanimationeditor.cpp').read_text()
assert '2048' in main
print('PASS Stage 4.15: checkbox, sliders, alternate rows, popup theme, runtime unchanged')
