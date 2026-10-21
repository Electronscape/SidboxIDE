#!/usr/bin/env python3
"""Stage 3.79b update: full Update Project for F5; Stage 4.08 silent F5 dialogs."""
from pathlib import Path
p = Path(__file__).resolve().parents[2]
m = (p/'mainwindow.cpp').read_text()
h = (p/'mainwindow.h').read_text()
d = (p/'projectsettingsdialog.cpp').read_text()
dh = (p/'projectsettingsdialog.h').read_text()
gh = (p/'gamedesigner.h').read_text()
ge = (p/'gamedesigner_export.cpp').read_text()
proj = (p/'gamedesigner_update.cpp').read_text()
compile_f5 = m.split('void MainWindow::compileActiveFile()', 1)[1].split('void MainWindow::handleCompilerFinished(', 1)[0]
check = m.split('bool MainWindow::checkGameBuildGeneration()',1)[1].split('void MainWindow::compileActiveFile()',1)[0]
generate = ge.split('bool SidboxGameDesigner::regenerateBuildFiles()',1)[1].split('void SidboxGameDesigner::generateGameCode()',1)[0]
full = proj.split('bool SidboxGameDesigner::updateGameProject(bool fromCompile)',1)[1]
assert 'if (!checkGameBuildGeneration()) return;' in compile_f5
assert compile_f5.index('if (!checkGameBuildGeneration()) return;') < compile_f5.index('projectFilesForCompile()')
assert 'm_gameBuildFirstCheckPending' in h and 'm_gameBuildAskBeforeBuild' in h
assert m.count('m_gameBuildFirstCheckPending = true;') == 2
assert m.count('m_gameBuildAskBeforeBuild = true;') == 2
assert 'QCheckBox(tr("Remember my choice for this project session")' in check
assert 'm_gameBuildAskBeforeBuild = false;' in check
assert 'gameBuildFilesOutdated(path, worldManagerMode)' in check
assert 'new SidboxGameDesigner' not in check
assert 'openGameDesigner(path)' in check
assert 'if (!game->updateGameProject(true)) return false;' in check
assert 'game->regenerateBuildFiles()' not in check
assert 'if (rememberUpdateAfterSuccess)' in check
assert check.index('if (!game->updateGameProject(true)) return false;') < check.index('if (rememberUpdateAfterSuccess)')
assert 'if (game->tilemapBuildFilesMissing())' not in compile_f5
assert 'void MainWindow::showProjectSettings()' in m
assert 'dialog.setAskBeforeGameBuild(m_gameBuildAskBeforeBuild);' in m
assert 'm_gameBuildAskBeforeBuild = dialog.askBeforeGameBuild();' in m
assert 'askBeforeGameBuild() const' in dh
assert 'm_askBeforeGameBuildCheck' in d
assert '"Ask before running Update Project on build (F5)"' in d
assert 'bool updateGameProject(bool fromCompile = false);' in gh.split('protected:',1)[0], 'method callable by MainWindow'
assert 'regenerateBuildFiles()' in gh
assert 'generateGameCodeCore(embedPixels, true)' in generate
assert 'tilemapBuildFilesMissing()' in generate
assert 'embedPixels = prefix.contains(' in generate
assert 'updateGameProject(' not in generate
assert 'regenerateBuildFiles()' not in full
assert 'gameBackupWriteZip(' in full
assert 'gameBackupTrimArchives(' in full
assert 'backupFolder' in full
assert 'maingame.c.txt' in full
assert 'generateGameCodeCore(embedPixels, true)' in full
assert 'saveDesign()' in full
assert 'return false;' in full and full.rstrip().endswith('return true;\n}')
assert '2048LL * 1024LL' in m
assert 'QMessageBox, QPushButton, QCheckBox { border-radius: 0px; }' in m
assert '.proj' not in check and 'QSettings' not in check
print('PASS: Stage 3.79b full backed-up Update Project on F5, remembered choice, cancellation handling')
