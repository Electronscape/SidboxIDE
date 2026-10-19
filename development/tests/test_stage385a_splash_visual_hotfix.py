#!/usr/bin/env python3
"""Static regression checks for Stage 3.85a splash cosmetics."""
from pathlib import Path
src=Path(__file__).resolve().parents[2] / "mainwindow.cpp"
s=src.read_text(encoding="utf-8")
head=s.index('class ProjectLoadProgressDialog final')
tail=s.index('bool isHistoryTextFile',head)
block=s[head:tail]
assert 'auto *spacer = new QWidget(panel);' not in block
assert 'panelLayout->addWidget(spacer);' not in block
assert 'panelLayout->addStretch(1);' in block
assert 'm_progressBar->setFormat(QStringLiteral("%p%"));' in block
assert '%p%%' not in block
assert 'm_progressBar->setValue(100);' in block
assert 'Project Loaded!' in block
print('PASS: project splash transparent layout spacing and single percent sign')
