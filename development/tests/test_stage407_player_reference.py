#!/usr/bin/env python3
"""Stage 4.07 IDE-only player sizing overlay, source-level regression checks."""
from pathlib import Path
base=Path(__file__).resolve().parents[2]
model=(base/'gametilemapmodel.cpp').read_text()
header=(base/'gametilemap.h').read_text()
editor=(base/'gametilemap.cpp').read_text()
designer=(base/'gamedesigner.cpp').read_text()
export=(base/'gametilemap_export.cpp').read_text() if (base/'gametilemap_export.cpp').exists() else ''
for part in ('referencePlayerPositionSet', 'referencePlayerX', 'referencePlayerY'):
    assert part in header and part in model and part in editor, part
assert 'if (referencePlayerPositionSet) {' in model
assert 'result.insert(QStringLiteral("referencePlayerX"), referencePlayerX)' in model
assert 'result.insert(QStringLiteral("referencePlayerY"), referencePlayerY)' in model
assert 'object.value(QStringLiteral("referencePlayerX")).isDouble()' in model
assert 'object.value(QStringLiteral("referencePlayerY")).isDouble()' in model
assert 'void SidboxTilemapEditor::setPlayerReference(' in editor
assert 'editor.setPlayerReference(sprite, r.scale, QPoint(r.x, r.y), playerHitbox);' in designer
assert 'r.name.trimmed().compare(QStringLiteral("player"), Qt::CaseInsensitive) == 0' in designer
assert 'r.objectType == QStringLiteral("decoration")' in designer
assert 'playerReferenceRect().contains' in editor
assert 'viewport()->setCursor(Qt::ClosedHandCursor)' in editor
assert 'if (strokeStarted) strokeStarted();' in editor
assert 'if (strokeFinished) strokeFinished();' in editor
assert 'm_canvas->showPlayerReference = visible;' in editor
assert 'Show player reference (drag to check gaps)' in editor
assert 'm_playerReferenceToggle->hide();' in editor
assert 'a.referencePlayerX != b.referencePlayerX || a.referencePlayerY != b.referencePlayerY' in editor
assert 'm_map.viewPanX =' in editor and 'm_saveCallback(m_map)' in editor
assert not any(n in designer for n in ('m_resources[index].x = m_map.referencePlayerX', 'm_resources[index].y = m_map.referencePlayerY'))
assert all(k not in export for k in ('referencePlayerX', 'referencePlayerY', 'referencePlayerPositionSet'))
print('PASS Stage 4.07: player sizing overlay, pan/zoom drag, saved design-only location, independent world player')
