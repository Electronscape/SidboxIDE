#!/usr/bin/env python3
"""Stage 4.05 portable source assertions; native Qt6 GUI tests remain local."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[2]
world = (root / 'gamedesigner.cpp').read_text()
header = (root / 'gamedesigner.h').read_text()
project = (root / 'gamedesigner_project.cpp').read_text()
tile = (root / 'gametilemap.cpp').read_text()
tileh = (root / 'gametilemap.h').read_text()

# The .sbgm owns the editor pan, not the game camera; postpone restoration
# until the inner viewport has finished tab show/resize layout.
assert 'worldViewCenterX' in project and 'worldViewCenterY' in project
assert 'm_view->mapToScene(m_view->viewport()->rect().center())' in project
assert 'void SidboxGameDesigner::restoreWorldViewPosition()' in world
assert 'void restoreWorldViewPosition();' in header
assert 'm_view->centerOn(m_savedWorldViewCenter)' in world
assert 'm_view->setResizeAnchor(QGraphicsView::AnchorViewCenter)' in world
assert 'event->type() == QEvent::Resize || event->type() == QEvent::Show' in world
assert '!m_view->viewport()->isVisible()' in world
assert 'm_restoreWorldViewCenter = false;' in world

# A focused slope canvas owns the Delete shortcut, avoiding text/spinboxes.
assert 'setFocus(Qt::MouseFocusReason);' in tile
assert 'new QShortcut(QKeySequence(Qt::Key_Delete), m_collisionCanvas)' in tile
assert 'deleteCollisionPoint->setContext(Qt::WidgetShortcut)' in tile
assert 'm_collisionDeletePoint->click();' in tile
assert 'deleteCollisionPoint->setContext(Qt::WindowShortcut)' not in tile
# Explicit confirm/cancel buttons and undo-safe rollback.
for needle in ('GGCollisionEditorAccept', 'GGCollisionEditorCancel',
               'button->setIconSize(QSize(24, 24))',
               'void SidboxTilemapEditor::finishCollisionStampEdit(bool accept)',
               'restoreMap(m_collisionEditBefore)',
               'm_undoStack = m_collisionEditUndoBefore',
               'm_redoStack = m_collisionEditRedoBefore',
               'finishCollisionStampEdit(false);',
               'finishCollisionStampEdit(true);'):
    assert needle in tile, needle
assert 'SidboxTilemap m_collisionEditBefore;' in tileh

# Navigation saves the active object and updates one persistent Qt dialog.
fn = world.split('void SidboxGameDesigner::configureGameObject(int index)', 1)[1].split('void SidboxGameDesigner::refreshObjectHitbox()', 1)[0]
assert 'const auto commitObject = [&]() -> bool {' in fn
assert 'const auto showObject = [&](int selectedIndex) {' in fn
assert 'if (previousIndex >= 0 && commitObject()) showObject(previousIndex);' in fn
assert 'if (nextIndex >= 0 && commitObject()) showObject(nextIndex);' in fn
assert 'if (commitObject()) dialog.accept();' in fn
assert 'QTimer::singleShot(0, this, [this, navigateTo]()' not in fn
assert 'dialog.accept(); // Save existing edits using the ordinary OK path.' not in fn
assert 'old = m_resources.at(index)' in fn
assert 'resourceName->setText(old.name)' in fn
assert 'targetObject->clear();' in fn and 'breakReward->clear();' in fn
assert 'previewFrame = 0;' in fn and 'atlas = cachedImage(resolvedPath(old.path));' in fn
assert 'enableFields();\n        refreshTimer();' in fn
assert 'previousObject->setEnabled(previousIndex >= 0);' in fn
assert 'nextObject->setEnabled(nextIndex >= 0);' in fn
saved = set(re.findall(r'\br\.(\w+)\s*=', fn[fn.index('const auto commitObject'):fn.index('const auto showObject')]))
loaded = set(re.findall(r'\bold\.(\w+)', fn[fn.index('const auto showObject'):fn.index('// Arrows commit')]))
assert saved <= loaded, f'Object fields are not reloaded: {sorted(saved-loaded)}'
print('PASS Stage 4.05: delayed world pan, slope edit transaction/keyboard, in-place object navigation')
