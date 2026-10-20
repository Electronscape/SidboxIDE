#!/usr/bin/env python3
"""Stage 4.16: stable checkbox geometry and narrow global scrollbars."""
from pathlib import Path
s = (Path(__file__).resolve().parents[2] / 'ideglobaltheme.h').read_text()
assert 'ideCheckedBoxImageUrl(const IDETheme &theme, bool isChecked = true)' in s
assert 'isChecked ? theme.accent : theme.inputBackground' in s
assert 'checkbox-on-' in s and 'checkbox-off-' in s
assert 'image:url("@untick");' in s and 'image:url("@tick");' in s
assert 'css.replace(QStringLiteral("@untick"), ideCheckedBoxImageUrl(theme, false));' in s
assert 'css.replace(QStringLiteral("@tick"), ideCheckedBoxImageUrl(theme));' in s
start = s.index('        QCheckBox::indicator {')
end = s.index('        QRadioButton::indicator {', start)
checkbox = s[start:end]
assert 'width:16px; height:16px; border:0px;' in checkbox
assert 'border:1px' not in checkbox
assert 'background:@input' not in checkbox
assert 'QCheckBox::indicator:checked:disabled' in checkbox
assert 'QScrollBar:vertical {' in s and 'width:10px; min-width:10px; max-width:10px;' in s
assert 'QScrollBar:horizontal {' in s and 'height:10px; min-height:10px; max-height:10px;' in s
assert 'QComboBoxPrivateContainer QScrollBar:vertical' in s
assert 'QScrollBar::handle:vertical { min-height:18px; }' in s
assert 'QPalette::AlternateBase, theme.alternateBackground' in s
print('PASS Stage 4.16: 16x16 checked/unchecked indicators and 10px scrollbars')
