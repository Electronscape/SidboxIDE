#!/usr/bin/env python3
"""Stage 4.09 source regression — player quick-place and hitbox map clearance."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
header = (root/'gametilemap.h').read_text()
ui = (root/'gametilemap.cpp').read_text()
designer = (root/'gamedesigner.cpp').read_text()
model = (root/'gametilemapmodel.cpp').read_text()
exporter = (root/'gamedesigner_export.cpp').read_text()
assert 'movePlayerReferenceToMouse()' in ui
assert 'QShortcut(QKeySequence(Qt::Key_Space), this)' in ui
assert 'viewport()->mapFromGlobal(QCursor::pos())' in ui
assert 'world.x() - size.width() / 2' in ui and 'world.y() - size.height() / 2' in ui
assert 'draggingPlayerReference || painting || selectingRegion || panning' in ui
assert 'if (strokeStarted) strokeStarted();' in ui and 'if (strokeFinished) strokeFinished();' in ui
assert 'm_canvas->movePlayerReferenceToMouse();' in ui
assert 'm_canvas->showPlayerReference = visible;' in ui
assert 'm_canvas->playerHitbox = hitbox;' in ui
assert 'playerHitboxWorldRect()' in ui
assert 'playerCellContact(int tx, int ty, const QRect &box)' in ui
assert 'const QRect overlap = box.intersected(cell);' in ui
assert 'type == 1 || (type >= 17 && type <= 24)' in ui
assert 'type == 5' in ui and 'type == 2' in ui and 'type == 6' in ui
assert 'type == 3' in ui and 'type == 4' in ui and 'type == 7' in ui and 'type == 8' in ui
assert 'collisionPlacementAt(*map, tx, ty)' in ui and 'shape->width * tile - 1 - localX' in ui
assert 'm_playerCollisionToggle = new TilemapFlagButton(' in ui
assert 'm_canvas->showPlayerCollision = enabled;' in ui
assert 'QStringLiteral("BLOCKED")' in ui and 'QStringLiteral("CLEAR")' in ui
assert 'const QRect proposed(root.value(QStringLiteral("hitboxX"))' in designer
assert 'root.value(QStringLiteral("hitboxW")).toInt(sprite.width())' in designer
assert 'root.value(QStringLiteral("format")).toString()' in designer
assert 'root.value(QStringLiteral("cellWidth")).toInt() == sprite.width()' in designer
assert 'editor.setPlayerReference(sprite, r.scale, QPoint(r.x, r.y), playerHitbox);' in designer
assert 'const QRect &hitbox = QRect()' in header
assert 'm_playerCollisionToggle = nullptr' in header
# persistent position is independent; clearance controls are NOT exported
assert 'result.insert(QStringLiteral("referencePlayerX"), referencePlayerX)' in model
assert 'result.insert(QStringLiteral("referencePlayerY"), referencePlayerY)' in model
assert 'playerHitbox' not in exporter and 'referencePlayerX' not in exporter
assert not any(part in designer for part in ('m_resources[index].x = m_map.referencePlayerX', 'm_resources[index].y = m_map.referencePlayerY'))
print('PASS Stage 4.09: space placement, undo/persist, animation hitbox, eight collision groups, editor-only')
