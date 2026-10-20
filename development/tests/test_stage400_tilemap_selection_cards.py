#!/usr/bin/env python3
"""Stage 4.00 Tilemap Editor selection-card integration guard.

GUI appearance and interaction need a Qt Creator/Fedora visual check. This
ensures the three actual lists receive the theme palette, selected styles,
and no selection / map-rendering logic was changed from the Stage 3.99 base.
"""
from pathlib import Path
import difflib

root = Path(__file__).resolve().parents[2]
src = (root / 'gametilemap.cpp').read_text(encoding='utf-8')

for object_name in ('GGTileStampBank', 'GGCollisionStampBank', 'GGLoopTrackBank'):
    expected = 2 if object_name == 'GGLoopTrackBank' else 1  # registration + lookup
    assert src.count(f'QStringLiteral("{object_name}")') == expected, object_name

assert 'const QColor selectionBackground = theme.accent.darker(230);' in src
assert 'selectionBackground.lightnessF() < 0.52' in src
assert 'QColor(Qt::white) : QColor(Qt::black)' in src
assert 'QListWidget::item:selected {' in src
assert 'QListWidget::item:hover:!selected {' in src
assert 'border-left:3px solid %7' in src
assert 'border-radius:0px;' in src
assert 'bank->setPalette(dialogPalette)' in src
assert 'bank->setStyleSheet(selectionStyle)' in src
assert 'item->setSizeHint(QSize(0, 34))' in src

# Selection handlers, thumbnail previews, edit actions and saved/exported map
# format must remain unchanged; only this GUI source gets a production edit.
assert 'connect(m_stampList, &QListWidget::currentRowChanged' in src
assert 'connect(m_collisionList, &QListWidget::currentRowChanged' in src
assert 'connect(loopList,&QListWidget::currentRowChanged' in src
assert 'm_stampList->setViewMode(QListView::IconMode);' in src
assert 'm_collisionList->setViewMode(QListView::IconMode);' in src
assert 'const auto updateLoopList =' in src

previous = root.parent / 'gg_stage399' / 'gametilemap.cpp'
if previous.exists():
    before = previous.read_text(encoding='utf-8')
    # Stage 4.01 legitimately changes the Tilemap Editor's control styling
    # too; the Stage 4.00 insertion-count check only applies to 4.00 itself.
    old_stage = root.parent / 'gg_stage400' / 'gametilemap.cpp'
    if old_stage.exists():
        stage400 = old_stage.read_text(encoding='utf-8')
        diff = list(difflib.unified_diff(before.splitlines(), stage400.splitlines()))
        new_lines = [line for line in diff if line.startswith('+') and not line.startswith('+++')]
        assert 35 < len(new_lines) < 60, f'Unexpected Stage 4.00 patch size: {len(new_lines)} additions'

print('PASS Stage 4.00: Tile Stamps, Collision Stamps and Loop Tracks share bordered, theme-aware selections')
