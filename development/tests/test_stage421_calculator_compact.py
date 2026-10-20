#!/usr/bin/env python3
"""Stage 4.21: compact programmer calculator respects central theme, no clipped keys."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
source=(root/'mainwindow.cpp').read_text()
css=(root/'ideglobaltheme.h').read_text()
start=source.index('class SidboxProgrammerCalculator : public QWidget')
end=source.index('} // namespace',start)
calc=source[start:end]
assert 'setObjectName(QStringLiteral("sidboxProgrammerCalculator"));' in calc
assert 'setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed)' in calc
assert 'layout->setSpacing(2)' in calc
assert 'readouts->setVerticalSpacing(1)' in calc
assert 'keypad->setVerticalSpacing(1)' in calc
assert 'button->setFixedHeight(22);' in calc
assert 'button->setMinimumWidth(0);' in calc
assert 'button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);' in calc
assert 'm_copyBinary->setFixedHeight(21)' in calc
assert 'for (int row = 0; row < 7; ++row)' in calc
assert 'for (int col = 0; col < 5; ++col)' in calc
assert 'const QString rows[][5]' in calc
assert 'connect(button, &QPushButton::clicked' in calc
assert 'm_bitButtons[bit] = button;' in calc
assert 'const quint64 newValue =' in calc
assert 'QWidget#sidboxProgrammerCalculator QPushButton,' in css
assert 'QWidget#sidboxProgrammerCalculator QToolButton' in css
assert 'QWidget#sidboxProgrammerCalculator QLineEdit,' in css
assert 'QWidget#sidboxProgrammerCalculator QComboBox' in css
assert css.count('min-height:0px; padding:0px 2px;')==1
assert css.count('min-height:0px; padding:1px 4px;')==1
# Make sure compact sizing never becomes a global QPushButton rule.
assert css.index('QWidget#sidboxProgrammerCalculator QPushButton') > css.index('QPushButton, QToolButton {')
assert 'min-height:22px;' in css
# Layout still keeps the project tree above calculator, with its size fixed.
assert 'projectLayout->addWidget(m_projectFiles, 1);' in source
assert 'projectLayout->addWidget(new SidboxProgrammerCalculator(m_theme, projectPane));' in source
print('PASS Stage 4.21: compact calculator, complete five-column keypad, scoped QSS, preserved bit maths')
