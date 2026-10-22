#!/usr/bin/env python3
"""Stage 5.9 source-flow regression: per-world map outputs, not root copies.
Qt6 IDE compilation / actual C export must still be verified by a user build.
"""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
read = lambda n: (r/n).read_text()
header = read('gametilemap.h')
exporter = read('gametilemap.cpp')
designer = read('gamedesigner.cpp')
project = read('gamedesigner_project.cpp')
codegen = read('gamedesigner_export.cpp')
update = read('gamedesigner_update.cpp')
snapshot = read('gameworldsnapshot.h')
main = read('mainwindow.cpp')
assert 'const QString &outputDirectory = QString()' in header
assert 'const QString &rulesDirectory, const QString &outputDirectory)' in exporter
assert 'QDir(outputDirectory.isEmpty() ? designDirectory : outputDirectory)' in exporter
assert 'const QDir globalDir(designDirectory);' in exporter, 'project-global physics must remain project-root'
assert 'QStringLiteral(".codergirl/tilemap-staging/") + worldBase' in designer
assert '                             staging)) {' in designer
assert 'const QString levelPath = QStringLiteral("worlds/") + worldBase' in designer
assert 'QStringLiteral("worlds/") + worldBase + QStringLiteral("/gamelevels/")' in project
assert 'if (m_tilemapEnabled && !exportTilemap(false, true))' in codegen
assert 'relative.startsWith(QStringLiteral("gamelevels/"))' in snapshot
assert 'mapStaging.filePath(relative) : project.filePath(relative)' in snapshot
assert 'QDir(mapStaging).removeRecursively();' in snapshot
assert 'const bool generated = ext == QStringLiteral(".c")' in snapshot
assert 'project.rmdir(QStringLiteral("gamelevels"));' in snapshot
assert 'if (QFileInfo::exists(project.filePath(legacy))) outputs.insert(legacy);' in update
assert 'if (gameProject && relativePath.startsWith(QStringLiteral("gamelevels/"))' in main
assert 'if (QFileInfo::exists(copy)) continue;' not in main
assert '&& !QFileInfo::exists(*it))' in main
assert '&& !regenerateBuildFiles()) return false;' in designer
assert '#include "gameglobalstamps.h"' in designer, 'preserve Stage 5.8 compile fix'
print('PASS Stage 5.9: staged world tilemaps, shared helper, publish, cleanup, build exclusions')
