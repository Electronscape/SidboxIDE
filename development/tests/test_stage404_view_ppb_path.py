"""Stage 4.04: PPB viewer remembers the most recently chosen folder."""
from pathlib import Path

source = (Path(__file__).resolve().parents[2] / 'mainwindow.cpp').read_text()
start = source.index('connect(viewPpbAction, &QAction::triggered')
end = source.index('connect(projectSettingsAction,', start)
viewer = source[start:end]

assert 'QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"))' in viewer
assert 'QStringLiteral("files/viewPpbLastDirectory")' in viewer
assert 'QDir::homePath()' in viewer
assert 'QDir(lastDirectory).exists()' in viewer
assert 'lastDirectory, tr("SIDBOX PPB Images (*.ppb);;All Files (*)")' in viewer
assert 'if (file.isEmpty())' in viewer
assert 'QFileInfo(file).absolutePath()' in viewer
assert viewer.index('if (file.isEmpty())') < viewer.index('settings.setValue(')
assert viewer.index('settings.setValue(') < viewer.index('openFile(file)')
print('PASS Stage 4.04: View PPB remembers directory; cancel does not update it')
