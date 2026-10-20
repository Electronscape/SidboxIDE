"""Stage 4.11 editor-only regression checks (no Qt runtime required)."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
tile = (root/'gametilemap.cpp').read_text()
world = (root/'gamedesigner.cpp').read_text()
header = (root/'gametilemap.h').read_text()
assert 'new WorldObjectTag(r.name, item)' in world
assert tile.count('QPainterPath letter;') == 2
assert 'TilemapPaintButton::KeepGraphic' in tile
assert 'TilemapPaintButton::EmptyGraphic' in tile
assert 'TilemapPaintButton::AtlasGraphic' in tile
assert 'TilemapPaintButton::KeepCollision' in tile
assert 'TilemapPaintButton::EmptyCollision' in tile
assert 'setFixedSize(small ? QSize(28, 28) : QSize(38, 36))' in tile
assert 'setIconSize(small ? QSize(16, 16) : QSize(24, 24))' in tile
assert 'sideLayout->addLayout(graphicModes);' in tile
assert 'flipRow->addWidget(brushC);' in tile
assert 'layout->addLayout(paintRow);' not in tile
assert 'brushG->hide();' in tile
assert 'm_graphicMode->setCurrentIndex(2);' in tile
assert 'brushG->findData(-1)' in tile and 'brushG->findData(0)' in tile and 'brushG->findData(1)' in tile
assert 'brushC->findData(-1)' in tile and 'brushC->findData(0)' in tile
assert 'syncGraphicModes();' in tile and 'syncCollisionModes();' in tile
assert 'renameZone->setVisible(isCustom);' in tile
assert 'customSolid->setVisible(isCustom);' in tile
for field in ['m_graphicKeep','m_graphicEmpty','m_graphicAtlas',
              'm_collisionKeep','m_collisionEmpty']:
    assert f'QToolButton *{field} = nullptr;' in header
assert 'findChildren<TilemapPaintButton' not in tile
print('PASS Stage 4.11: outlined text; toolbar icon, mode, atlas and theme wiring')
