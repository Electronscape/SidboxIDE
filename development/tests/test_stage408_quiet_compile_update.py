#!/usr/bin/env python3
"""Stage 4.08: F5 skips nested update dialogs; explicit update stays interactive."""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
main = (root / "mainwindow.cpp").read_text()
header = (root / "gamedesigner.h").read_text()
update = (root / "gamedesigner_update.cpp").read_text()
designer = (root / "gamedesigner.cpp").read_text()
check = main.split("bool MainWindow::checkGameBuildGeneration()", 1)[1].split("void MainWindow::compileActiveFile()", 1)[0]
func = update.split("bool SidboxGameDesigner::updateGameProject(bool fromCompile)", 1)[1]

# F5 still asks on the first compile unless the session choice was remembered.
assert "m_gameBuildAskBeforeBuild" in check
assert 'tr("Remember my choice for this project session")' in check
assert "rememberUpdateAfterSuccess" in check
assert "m_gameBuildAskBeforeBuild = false;" in check
assert "if (!game->updateGameProject(true)) return false;" in check
assert check.index("if (!game->updateGameProject(true)) return false;") < check.index("if (rememberUpdateAfterSuccess)")

# The normal Update Project button must call the *interactive default*.
assert "bool updateGameProject(bool fromCompile = false);" in header
assert 'connect(updateProject, &QPushButton::clicked, this, [this]() { updateGameProject(); });' in designer
assert "bool embedPixels = false;" in func
confirm = func.index("QMessageBox confirm(this);")
assert func.rfind("if (!fromCompile) {", 0, confirm) != -1
assert "embedPixels = embed->isChecked();" in func
assert 'if (!fromCompile) {\n        QMessageBox::information(this, tr("Game Project Updated")' in func

# The actual update and safeguards run for BOTH paths. Failures remain visible.
assert "gameBackupWriteZip(backupFolder, archivePath, &zipError)" in func
assert "gameBackupTrimArchives(backupRoot)" in func
assert "generateGameCodeCore(embedPixels, true)" in func
assert "!saveDesign()" in func
assert 'QMessageBox::critical(this, tr("Update Game Project — Incomplete")' in func
assert 'QMessageBox::warning(this, tr("Update Game Project")' in func
assert "main.c" in func and "maingame.c.txt" in func
assert "2048LL * 1024LL" in main
print("PASS Stage 4.08: silent F5 updates, interactive manual update, retained backups/errors")
