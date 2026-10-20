#!/usr/bin/env python3
"""Stage 4.18: consistent Qt widget base, compact numeric edits and popup colours."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
main = (root/'main.cpp').read_text()
style = (root/'ideglobaltheme.h').read_text()
assert 'QApplication::setStyle(QStringLiteral("Fusion"));' in main
assert main.index('QApplication::setStyle(QStringLiteral("Fusion"));') < main.index('MainWindow w;')
assert 'QSpinBox, QDoubleSpinBox { padding:1px 4px; min-height:16px; }' in style
assert 'QScrollBar:vertical {' in style and 'width:10px; min-width:10px; max-width:10px;' in style
assert 'QCheckBox::indicator:checked' in style
assert '_sidboxComboBaseStyle' in style
assert 'combo->setStyleSheet(newComboStyle);' in style
assert 'QComboBox QAbstractItemView::item:selected' in style
assert 'C(m_theme.menuBackground)' in style
assert 'view->setStyleSheet(combined);' in style
assert 'watched->inherits("QComboBoxPrivateContainer")' in style
assert 'popup->parentWidget()' in style
assert 'for (QWidget *widget : QApplication::allWidgets())' in style
print('PASS Stage 4.18: compact numeric widgets and KDE-independent themed combos')
