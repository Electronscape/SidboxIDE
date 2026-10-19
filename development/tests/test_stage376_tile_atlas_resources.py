"""Stage 3.76+ Tile Atlas bank resource ownership invariants.

Self-contained regression checks, so this file also runs in the distributed IDE
without an earlier Stage 3.75 folder under /mnt/data.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
designer = (root / 'gamedesigner.cpp').read_text()
tiles = (root / 'gametilemap.cpp').read_text()

section = designer.split('void SidboxGameDesigner::openTilemapEditor()', 1)[1].split(
    'bool SidboxGameDesigner::tilemapBuildFilesMissing()', 1)[0]
assert 'r.kind != QStringLiteral("tileatlas") || r.path.isEmpty()' in section
assert 'r.kind == QStringLiteral("sprite")' not in section
assert 'atlases.append({r.name, QDir::cleanPath(path)});' in section
assert 'if (!exists)' not in section  # no Sprite-preempting same-file de-dup
assert 'SidboxTilemapEditor editor(m_tilemap, atlases, directory, this);' in section

picker = tiles.split('auto *atlasChoice = new TilemapComboBox(sidebar);', 1)[1].split(
    'sideLayout->addWidget(atlasChoice);', 1)[0]
assert 'for (const auto &a : atlases) atlasChoice->addItem(a.first, a.second);' in picker
assert 'Current map PPB (not in Tile Atlases)' in picker
assert 'm_map.atlasPath.isEmpty() ? QString()' in picker
assert 'atlasChoice->setCurrentIndex(atlasChoice->count() - 1)' in picker
assert 'No artwork (IDs only)' in picker
assert 'setAtlas(' not in picker  # initialisation below retains existing file

# Preserve the existing tilemap's current atlas until the user explicitly
# selects another resource from the picker.
assert 'void SidboxTilemapEditor::setAtlas(' in tiles
assert 'm_map.atlasPath' in tiles
assert 'm_map' in picker
print('PASS: Tile Atlas bank entries authoritative; legacy map art preserved')
