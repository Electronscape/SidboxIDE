#!/usr/bin/env python3
"""Stage 4.10: compact 24px tilemap flag toolbar, existing wiring preserved."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
cpp = (r/'gametilemap.cpp').read_text()
hdr = (r/'gametilemap.h').read_text()
common = (r/'ideglobaltheme.h').read_text()
assert 'class TilemapFlagButton final : public QToolButton' in cpp
assert 'setIconSize(QSize(24, 24));' in cpp
assert 'setCheckable(true);' in cpp
assert 'setFixedSize(38, 36);' in cpp
assert 'setFocusPolicy(Qt::TabFocus)' in cpp
assert 'button->setGlyphColours(theme.text, selectedText);' in cpp
assert 'p.setPen(QPen(ink, 1.8' in cpp
assert 'QToolButton:checked' in common and 'border-radius:0px' in common
fields = {
    'm_flipX':'CellX', 'm_flipY':'CellY',
    'm_stampMirrorX':'StampX', 'm_stampMirrorY':'StampY',
    'm_drawFront':'Front', 'm_stampUseFront':'StampFront',
    'm_playerReferenceToggle':'Player', 'm_playerCollisionToggle':'Hitbox',
}
for f,g in fields.items():
    assert f + ' = new TilemapFlagButton(TilemapFlagButton::' + g in cpp, f
    assert 'QToolButton *'+f+' = nullptr;' in hdr, f
    assert 'flipRow->addWidget('+f+');' in cpp, f
    assert f+'->setToolTip(' in cpp, f
    assert f+'->setChecked(' in cpp or f in ('m_stampMirrorX', 'm_stampMirrorY'), f
    assert 'connect('+f+', &QToolButton::toggled' in cpp or f in ('m_playerCollisionToggle',),f
assert 'm_playerToolsDivider->setVisible(available);' in cpp
assert 'm_playerReferenceToggle->setVisible(available);' in cpp
assert 'm_playerCollisionToggle->setVisible(available);' in cpp
assert 'm_playerReferenceToggle->hide();' in cpp
assert 'm_playerCollisionToggle->hide();' in cpp
assert 'm_canvas->showPlayerReference = visible;' in cpp
assert 'm_canvas->showPlayerCollision = enabled;' in cpp
assert 'm_canvas->stampUseFrontBrush = enabled;' in cpp
assert 'm_canvas->stampMirror = quint8(' in cpp
assert 'm_canvas->flipBrush = flags;' in cpp
assert 'GameTilemapEditor/stampUseFront' in cpp
assert 'GameTilemapEditor/flipMode' in cpp
assert 'GameTilemapEditor/brushFlags' in cpp
assert 'auto *stampFlagRow =' not in cpp
assert 'layout->addWidget(m_playerReferenceToggle);' not in cpp
assert 'layout->addWidget(m_playerCollisionToggle);' not in cpp
print('PASS Stage 4.10: 8 themed 24px icon toggles, single toolbar, tooltip/setting/paint signals retained')
