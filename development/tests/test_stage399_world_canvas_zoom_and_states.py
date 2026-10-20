#!/usr/bin/env python3
"""Stage 3.99: per-design world canvas pan, 400% zoom, theme-state cards.

Source integration guard. Real Qt6 save/reopen behaviour requires an IDE GUI test.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
read = lambda rel: (root / rel).read_text()
world = read('gamedesigner.cpp')
header = read('gamedesigner.h')
project = read('gamedesigner_project.cpp')
animation = read('gameanimationeditor.cpp')

# The World Editor's pan is persisted in the .sbgm, distinct from cameraX/Y
# (gameplay camera), and restored when its viewport is visible and laid out.
assert 'worldViewCenterX' in project and 'worldViewCenterY' in project
assert project.count('QStringLiteral("worldViewCenterX")') == 3
assert project.count('QStringLiteral("worldViewCenterY")') == 3
assert 'm_view->mapToScene(m_view->viewport()->rect().center())' in project
assert 'm_restoreWorldViewCenter = obj.value(' in project
assert 'void SidboxGameDesigner::showEvent(QShowEvent *event)' in world
assert 'QTimer::singleShot(0, this, [this]' in world
assert 'm_view->centerOn(m_savedWorldViewCenter)' in world
assert 'bool m_restoreWorldViewCenter = false;' in header
assert 'if (m_worldPanMoved) setDirty();' in world
assert 'QScrollBar::sliderMoved' in world
# zoom selection and loader must both accept 400% so it survives reopen.
assert 'QStringLiteral("400%")' in world
assert 'QStringLiteral("400")' in project
assert 'const int zoom = QStringList' in project
assert 'm_view->scale(zoom / 100.0, zoom / 100.0)' in project
assert 'setDirty(); // Zoom is persisted in the .sbgm' in world
# Style only animation state selector; do not replace state names/save logic.
assert 'm_stateList->setObjectName(QStringLiteral("GGAnimationStates"))' in animation
assert 'QListWidget#GGAnimationStates::item:selected' in animation
assert 'border-left:3px solid %6' in animation
assert 'm_theme.accent.darker(230)' in animation
assert 'item->setSizeHint(QSize(170, 43))' in animation
assert 'animationStateIcon(state, m_theme)' in animation
print('PASS Stage 3.99: World Canvas pan save/load, delayed restore, 400% zoom and theme state cards')
