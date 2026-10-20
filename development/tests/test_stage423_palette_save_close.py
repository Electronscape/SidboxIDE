#!/usr/bin/env python3
"""Stage 4.23: Save closes only after a successful palette write."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[2]
src = (root / 'gamepaletteeditor.cpp').read_text()
designer = (root / 'gamedesigner.cpp').read_text()
header = (root / 'gamepaletteeditor.h').read_text()
save = src.split('void SidboxGamePaletteEditor::savePalette()', 1)[1].split('void SidboxGamePaletteEditor::selectIndex', 1)[0]
export = src.split('void SidboxGamePaletteEditor::exportPalette()', 1)[1].split('void SidboxGamePaletteEditor::savePalette', 1)[0]
assert re.search(r'if \(!ok\)\s*\{[^}]*return;', save, re.S), 'save failure must leave editor open'
assert 'm_savedPath = m_sourcePath;' in save
assert save.index('m_savedPath = m_sourcePath;') < save.index('QDialog::accept();')
assert save.count('QDialog::accept();') == 1, 'save should close once, on success'
assert 'QDialog::accept();' not in export, 'Save As behaviour should be unchanged'
assert 'connect(close, &QPushButton::clicked, this, &QDialog::reject);' in src
assert 'void SidboxGamePaletteEditor::reject()' in src
assert 'if (confirmDiscard()) QDialog::reject();' in src
assert 'const auto foreground = dialog.foregroundColourCycle();' in designer
assert 'const auto background = dialog.backgroundColourCycle();' in designer
assert 'const QString saved = dialog.savedPath();' in designer
assert 'bool loadFromFile(const QString &path);' in header
print('PASS Stage 4.23: Save closes only on success; Save As and Close unchanged; design cycles returned')
