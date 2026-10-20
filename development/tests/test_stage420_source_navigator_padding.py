#!/usr/bin/env python3
"""Stage 4.20: Source navigator keeps top position and adds two pixels below."""
from pathlib import Path

src = (Path(__file__).resolve().parents[2] / "mainwindow.cpp").read_text()
create = src[src.index("CodeEditor *MainWindow::createEditor("):]
create = create[:create.index("connect(editor, &QPlainTextEdit::cursorPositionChanged")]
assert "barLayout->setContentsMargins(6, 2, 6, 4);" in create
assert "editor->setNavigationBar(bar, 32);" in create
assert "barLayout->setSpacing(7);" in create
assert "objects->setFixedWidth(185);" in create
assert "events->setFixedWidth(195);" in create
assert 'bar->setObjectName(QStringLiteral("sidboxEventNavigatorBar"));' in create
assert "min-height: 19px" in create
print("Stage 4.20 source navigator spacing: PASS")
