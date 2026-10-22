#!/usr/bin/env python3
"""Stage 5.16: The Qt tab close glyph survives theme changes and app relocation."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
icons = (root / "gameeditoricons.h").read_text()
main = (root / "mainwindow.cpp").read_text()
cmake = (root / "CMakeLists.txt").read_text()
assert (root / "icons/close_tab.png").is_file()
assert "icons/close_tab.png" in cmake
assert 'PREFIX "/icons"' in cmake
assert 'image: url(:/icons/close_tab.png);' in main
assert 'image:url(\\"%8\\")' in main
assert 'gameEditorIconUrl(QStringLiteral("close_tab.png"))' in main
assert 'QDir::fromNativeSeparators(file);' in icons
assert 'QUrl::fromLocalFile(file).toString()' not in icons
assert 'return file.isEmpty() ? QStringLiteral(":/icons/") + fileName' in icons
assert 'QTabBar::close-button:hover' in main
assert 'border-radius:0px;' in main
assert '2048' in main
print("PASS Stage 5.16 tab close button resource, theme and external override")
