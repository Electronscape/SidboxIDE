#!/usr/bin/env python3
"""Stage 5.11 static regression: redundant world modules are not retained."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
snapshot = (root / 'gameworldsnapshot.h').read_text()
main = (root / 'mainwindow.cpp').read_text()
update = (root / 'gamedesigner_update.cpp').read_text()

world = ['gameworlditems.c','gameworlditems.h','gameworlditems.txt',
         'gameadventure.c','gameadventure.h','splinepaths.c','splinepaths.h']
for name in world:
    assert f'QStringLiteral("{name}")' in snapshot, name
    assert f'QStringLiteral("gamehelpers/{name}")' in main, name

assert 'const QByteArray namespaceInclude = "#include \\"../world_symbols.h\\"\\n";' in snapshot
assert 'worldBytes.remove(0, namespaceInclude.size());' in snapshot
assert 'if (rootBytes == worldBytes)' in snapshot
assert 'QFile::remove(rootFile)' in snapshot
assert snapshot.index('publishWorldRegistry(project, QDir(rulesDirectory), error)') < snapshot.index('// Stage 5.11:')
assert 'publishedWorlds.entryList(' in snapshot
assert 'world.filePath(QStringLiteral("world-build.json"))' in snapshot
assert 'generatedWorldHelpers.contains(relative)' in main
assert '&& !QFileInfo::exists(*it))' in main
assert 'gameTileStampBanks' in main
assert 'worlds/<name>/gamehelpers/' in update
# These root C files were already excluded from the V1 link inputs.
for name in ['gameworlditems.c', 'gameadventure.c', 'splinepaths.c']:
    assert f'relativePath == QStringLiteral("gamehelpers/{name}")' in main
print('PASS Stage 5.11: duplicate cleanup, project manifest, shared helper exclusions')
