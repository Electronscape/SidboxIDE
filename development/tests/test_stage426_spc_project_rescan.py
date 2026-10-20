#!/usr/bin/env python3
"""Stage 4.26: SNES SPC music can be discovered without implying playback support."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
main = (root / 'mainwindow.cpp').read_text()
designer = (root / 'gamedesigner.cpp').read_text()

suffix = main.split('bool isProjectExplorerSuffix(', 1)[1].split('// Stage 3.70:', 1)[0]
scan = main.split('QStringList MainWindow::projectFolderSourceFiles()', 1)[1].split('bool MainWindow::isProjectExplorerFile(', 1)[0]
rescan = main.split('void MainWindow::rescanProjectFiles()', 1)[1].split('void MainWindow::refreshProjectFiles()', 1)[0]
file_icon = main.split('const QString suffix = fileInfo.suffix().toLower();', 1)[1].split('const QString absoluteFilePath', 1)[0]
open_file = main.split('// Do not accidentally interpret binary SIDBOX game assets as UTF-8 C source.', 1)[1].split('for (int i = 0; i < m_editorTabs->count(); ++i)', 1)[0]
picker = designer.split('void SidboxGameDesigner::addResource(', 1)[1].split('if (path.isEmpty()) return;', 1)[0]

assert 'lower == QStringLiteral("spc")' in suffix, 'extension missing from explorer whitelist'
assert 'QStringLiteral("*.spc")' in scan, 'extension missing from recursive rescan filter'
assert 'QDir::Name | QDir::IgnoreCase' in scan, 'scan must remain case insensitive'
assert 'projectFolderSourceFiles()' in rescan, 'rescan should use the same filter'
assert 'suffix == QStringLiteral("spc")' in file_icon, 'music icon type missing'
assert 'QStringLiteral("spc")' in open_file, 'binary file could be opened as text'
assert 'Music (*.mod *.s3m *.xm *.med *.tfmx *.sid *.sba *.spc)' in picker, 'music resource picker missing SPC'
assert 'suffix == QStringLiteral("spc")' not in main.split('bool canContainFunctionSignatures(', 1)[1].split('bool canSearchProjectText(', 1)[0]
assert 'suffix == QStringLiteral("spc")' not in main.split('bool canSearchProjectText(', 1)[1].split('bool isExcludedProjectDirectoryName(', 1)[0]
print('PASS Stage 4.26: SPC discovery, icon, binary handling, picker; no decoder changes')
