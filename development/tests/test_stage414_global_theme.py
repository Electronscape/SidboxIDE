#!/usr/bin/env python3
"""Stage 4.14: one application-wide control style and visible checked ticks."""
from pathlib import Path
p=Path(__file__).resolve().parents[2]
main=(p/'mainwindow.cpp').read_text()
css=(p/'ideglobaltheme.h').read_text()
world=(p/'gamedesigner.cpp').read_text()
tile=(p/'gametilemap.cpp').read_text()
anim=(p/'gameanimationeditor.cpp').read_text()
guide=(p/'guidesigner.cpp').read_text()
palette=(p/'gamepaletteeditor.cpp').read_text()
assert 'qApp->setStyleSheet(ideGlobalControlStyle(m_theme))' in main
# Existing startup hard-coded dark stylesheet must not override the global one.
startup=main.split('void MainWindow::setupInterface()',1)[1].split('auto *toolBar =',1)[0]
assert 'setStyleSheet(R"(' not in startup
assert 'QMainWindow, QDialog' in css and 'QWidget { color:@text; }' in css
for widget in ['QCheckBox::indicator:checked', 'QRadioButton::indicator:checked',
 'QPushButton', 'QToolButton', 'QComboBox', 'QSpinBox', 'QSlider::handle',
 'QTabBar::tab', 'QTreeWidget', 'QScrollBar', 'QToolTip', 'QMenu', 'QHeaderView']:
 assert widget in css,widget
assert 'image:url("@tick")' in css
assert 'ideCheckedBoxImageUrl(theme)' in css
assert 'QCryptographicHash::hash(colourSpec + bytes' in css
assert 'indicator.save(file, "PNG")' in css
assert 'gameEditorIconOverride(QStringLiteral("checkbox_tick.png"))' in css
assert 'QPainter painter(&indicator)' in css
# The global QSS must not remove arrows from regular QComboBoxes.
assert 'QComboBox[customChevron="true"]::down-arrow' in css
assert 'QComboBox::down-arrow { image:none' not in css
assert 'setProperty("customChevron", true)' in world
assert 'setProperty("customChevron", true)' in tile
# Old child-specific control styles no longer override the global stylesheet.
assert 'setStyleSheet(QString());' in world
assert 'setStyleSheet(QString());' in tile
assert 'image:url(@tick)' not in anim
assert 'QCheckBox::indicator' not in world
assert 'QCheckBox::indicator' not in guide
assert 'QCheckBox::indicator' not in main
assert 'QComboBox::drop-down' not in palette
# The fixed gadget artwork background is an intentional named-widget exception.
assert 'QListWidget#coderGirlGadgetPalette' in guide
assert (p/'icons/checkbox_tick.png').is_file()
print('PASS Stage 4.14: global controls, checkbox icons and scoped custom art')
