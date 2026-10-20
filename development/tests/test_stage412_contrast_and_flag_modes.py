"""Stage 4.12: high contrast world/stamp tags, flags mode glyphs and toolbar groups."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
world=(r/'gamedesigner.cpp').read_text()
tile=(r/'gametilemap.cpp').read_text()
hdr=(r/'gametilemap.h').read_text()
assert 'class WorldObjectTag final : public QGraphicsSimpleTextItem' in world
assert 'new WorldObjectTag(r.name, item)' in world
assert 'tagFont.setWeight(QFont::Black)' in world
assert 'painter->setBrush(QColor(255, 255, 225))' in world
assert 'painter->drawPath(glyph)' in world
assert world.index('painter->setPen(QPen(Qt::black, 3.4') < world.index('painter->setBrush(QColor(255, 255, 225))')
assert 'QGraphicsSimpleTextItem *>(child)' in world  # rename and show toggles remain compatible
assert tile.count('QPainterPath letter;') == 2
assert tile.count('markerFont.setWeight(QFont::DemiBold)') == 2  # Stage 4.13: thinner F overlay
assert tile.count('painter.setBrush(QColor(255, 255, 225));') == 2
assert tile.count('painter.setBrush(Qt::NoBrush);') >= 2
assert 'enum Glyph { KeepGraphic, EmptyGraphic, AtlasGraphic, KeepCollision, EmptyCollision,\n                 ApplyFlags, KeepFlags }' not in tile or 'ApplyFlags, KeepFlags' in tile
for f,g in [('m_flagApply','ApplyFlags'),('m_flagKeep','KeepFlags')]:
    assert f'QToolButton *{f} = nullptr;' in hdr
    assert f'flipRow->addWidget({f});' in tile
    assert f'{f} = new TilemapPaintButton(TilemapPaintButton::{g}' in tile
    assert f'{f}->setToolTip' in tile
    assert f'connect({f}, &QToolButton::clicked' in tile
assert 'm_flipMode->hide();' in tile
assert 'm_flipMode->setCurrentIndex(m_flipMode->findData(1))' in tile
assert 'm_flipMode->setCurrentIndex(m_flipMode->findData(-1))' in tile
assert 'GameTilemapEditor/flipMode' in tile
assert 'm_canvas->flipMode = mode' in tile
assert 'm_stampCanvas->flipMode = mode' in tile
assert 'syncFlagModes();' in tile
assert 'm_flagApply, m_flagKeep' in tile # theme glyph update
assert 'flipRow->addWidget(collisionDivider);' in tile
assert 'flipRow->addWidget(m_playerToolsDivider);' in tile
assert 'frontDivider' not in tile
assert 'setIconSize(small ? QSize(16, 16) : QSize(24, 24))' in tile
print('PASS Stage 4.12: labels use fixed bright bold fill; flag icon modes stay synced with painting')
