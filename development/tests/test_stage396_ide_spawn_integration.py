"""Stage 3.96: source/export integration checks (not a substitute for Qt6 build)."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
read=lambda name:(r/name).read_text()
main=read('mainwindow.cpp')
find=read('mainwindow_findreplace.cpp')
header=read('mainwindow.h')
editor=read('gamedesigner.cpp')
model=read('gamedesigner.h')
project=read('gamedesigner_project.cpp')
export=read('gamedesigner_export.cpp')
worldh=read('idelibs/codehelpers/game/worldobjects.h')
worldc=read('idelibs/codehelpers/game/worldobjects.c')
pickh=read('idelibs/codehelpers/game/collectables.h')
pickc=read('idelibs/codehelpers/game/collectables.c')
# Ctrl+F confined to current editor, F3 wraps, Ctrl+Shift+F preserved.
assert 'findDocumentAction->setShortcut(QKeySequence(QStringLiteral("Ctrl+F")))' in main
assert 'findNextAction->setShortcut(QKeySequence(QStringLiteral("F3")))' in main
assert 'findReplaceAction->setShortcut(QKeySequence(QStringLiteral("Ctrl+Shift+F")))' in main
assert 'QInputDialog::getText' in find and 'document->find(m_documentFindText, 0)' in find
assert 'm_documentFindText' in header
# Standalone PPB viewer reads embedded CLUT, with drag and wheel zoom.
assert '#include "ppbcodec.h"' in main
assert 'SidboxPpb::read(filePath, &picture, &error)' in main
assert 'ScrollHandDrag' in main and 'wheelEvent(QWheelEvent *event)' in main
assert 'QGraphicsPixmapItem *pix = scene->addPixmap' in main
assert 'QStringLiteral("ppb")' not in main.split('// Do not accidentally interpret binary SIDBOX game assets',1)[1].split('for (int i =',1)[0]
# Calculator checked bits use selected IDE theme; not system palette.
assert 'void updateTheme(const IDETheme &theme)' in main
assert 'm_bitAccent = theme.accent' in main and 'm_bitSelectedText' in main
assert 'palette(highlighted-text)' not in main
# Game Object UX: stable IDs remain in underlying model, not end-user UI.
assert 'generalCard.form->addRow(tr("Object ID")' not in editor
assert 'QListWidget#GGObjectTypes::item:selected { background:%8; color:%11' in editor
assert 'objectSelectionFg' in editor
# Breakable from below + collectable linked by stable ID.
assert 'breakFromBelow' in model and 'breakDropCollectableId' in model
for key in ['breakFromBelow','breakDropCollectableId']:
    assert 'QStringLiteral("'+key+'")' in project
assert 'Break by jumping into underside' in editor
assert 'Drop collectable on break' in editor
assert 'r.breakDropCollectableId = breakReward->currentData().toString()' in editor
assert 'break_from_below' in worldh and 'old_top >= old_bottom' in worldc
assert 'cg_reward_falling' in export and 'cg_reward_vy100' in export
assert 'game_tilemap_actor_blocked(&game_level1' in export
assert 'breakRewardOwner.contains(id)' in export
assert 'breakDropCollectableId' in export
assert 'can_collect' in pickh and 'if (!item->active || !item->can_collect' in pickc
# F5 visual settings and unchanged large-file highlighter threshold.
assert 'const qint64 largeSourceThreshold = 2048LL * 1024LL;' in main
print('PASS: local find, PPB viewer, themed bits, selection, hide ID, breakable reward export')
