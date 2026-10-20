#!/usr/bin/env python3
"""Stage 4.10a: the custom button has no Q_OBJECT, so never use it in findChildren."""
from pathlib import Path
cpp = (Path(__file__).resolve().parents[2] / 'gametilemap.cpp').read_text()
assert 'class TilemapFlagButton final : public QToolButton' in cpp
assert 'findChildren<TilemapFlagButton' not in cpp
assert 'static_cast<TilemapFlagButton *>(tool)' in cpp
start = cpp.index('    for (QToolButton *tool : {m_flipX,')
end = cpp.index('        button->setGlyphColours(theme.text, selectedText);', start)
section = cpp[start:end]
for field in ('m_flipX', 'm_flipY', 'm_stampMirrorX', 'm_stampMirrorY',
              'm_drawFront', 'm_stampUseFront', 'm_playerReferenceToggle',
              'm_playerCollisionToggle'):
    assert field in section, field
print('PASS Stage 4.10a: custom glyph theme loop avoids Qt Q_OBJECT requirement')
