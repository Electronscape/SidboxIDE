#!/usr/bin/env python3
"""Stage 3.83 source checks for the nonblocking two-second completion splash."""
from pathlib import Path
src = Path(__file__).resolve().parents[2] / "mainwindow.cpp"
text = src.read_text(encoding="utf-8")
start = text.index("bool MainWindow::loadProjectFile(const QString &filePath)")
end = text.index("bool MainWindow::saveProjectFile", start)
load = text[start:end]
assert '"Project Loaded!"' in text
assert '"Finished loading — all project assets are ready."' in text
assert 'm_progressBar->setValue(100);' in text
assert 'progress->showCompleted();' in load
assert 'QTimer::singleShot(2000, progress, [progress]()' in load
assert 'progress->hide();' in load
assert 'progress->deleteLater();' in load
assert 'QThread::sleep' not in load and 'QEventLoop loop' not in load
assert 'dismissProgress();' in load
assert 'ProjectLoadArtworkPanel' in text
assert 'border-radius:0px' in text
print('PASS: 100% project-loaded splash lasts two seconds with nonblocking QTimer')
