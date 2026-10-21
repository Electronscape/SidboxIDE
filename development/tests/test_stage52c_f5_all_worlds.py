#!/usr/bin/env python3
"""Stage 5.2c: F5 selects no single design for a world-manager main.c.

Source contract checks. Run with python3 on IDE source; Qt/ARM integration
remains a hardware test.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
cpp = (root / "mainwindow.cpp").read_text()
h = (root / "mainwindow.h").read_text()
check = cpp.split("bool MainWindow::checkGameBuildGeneration()", 1)[1].split("void MainWindow::compileActiveFile()", 1)[0]
verify = cpp.split("bool MainWindow::gameBuildFilesOutdated(", 1)[1].split("bool MainWindow::checkGameBuildGeneration()", 1)[0]
build = cpp.split("QStringList MainWindow::projectFilesForCompile()", 1)[1].split("QStringList MainWindow::projectFunctionSignatures()", 1)[0]
assert 'GAMERGIRL_WORLD_MANAGER_MAIN' in build
assert 'entryPoint.readAll().contains("GAMERGIRL_WORLD_MANAGER_MAIN")' in check
assert 'if (!worldManagerMode && designs.size() > 1)' in check
assert 'QInputDialog::getItem(this, tr("Choose Game Design")' in check
assert 'if (gameBuildFilesOutdated(path, worldManagerMode))' in check
assert 'const QStringList targets = m_gameBuildFirstCheckPending ? designs : outdated;' in check
assert 'if (!worldManagerMode && !shouldRegenerate' in check
assert 'if (!game->updateGameProject(true)) return false;' in check
assert 'gameBuildFilesOutdated(const QString &designPath, bool worldManagerMode) const;' in h
assert 'if (worldManagerMode)' in verify and 'world-build.json' in verify
assert '.codergirl/worlds/' in verify and 'world_api.h' in verify
assert 'design.lastModified() > built' in verify
assert 'gameassets/gameassets.c' in verify and 'active-world.json' in verify
assert '2048LL * 1024LL' in cpp
print('PASS Stage 5.2c: world-manager F5 checks all bundles; old starter path preserved')
