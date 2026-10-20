"""Stage 4.03 source regressions: animation atlas + world canvas + object editor."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
anim = (root / 'gameanimationeditor.cpp').read_text()
world = (root / 'gamedesigner.cpp').read_text()
assert 'class AnimationAtlasScrollArea final : public QScrollArea' in anim
assert 'mouse->button() == Qt::MiddleButton' in anim
assert 'Qt::ClosedHandCursor' in anim
assert 'horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x())' in anim
assert 'const double imageX' in anim and 'qRound(imageX * after) - at.x()' in anim
assert 'scroll->setAtlasWidget(atlas);' in anim
assert 'scroll->setZoom = [this](int zoom) { m_zoom->setValue(zoom); };' in anim
assert 'const QPointF scenePoint = m_view->mapToScene(at);' in world
assert 'm_zoom->setCurrentIndex(next);' in world
assert 'm_view->horizontalScrollBar()->value() + now.x() - at.x()' in world
assert 'gameResourceIcon(QStringLiteral("gr_icon_object.png")).pixmap(44, 44)' in world
assert 'previousObject->setIcon(arrowIcon(false));' in world
assert 'nextObject->setIcon(arrowIcon(true));' in world
assert 'button->setIconSize(QSize(16, 16));' in world
assert 'candidate.objectType == QStringLiteral("decoration")) continue;' in world
assert 'if (previousIndex >= 0 && commitObject()) showObject(previousIndex);' in world
assert 'if (nextIndex >= 0 && commitObject()) showObject(nextIndex);' in world
assert 'connect(stopButton, &QToolButton::clicked' in world
assert 'previewFrame = 0;' in world
assert 'if (animated->isChecked() && previewPlaying) previewTimer->start();' in world
assert 'painter.setBrush(m_theme.text);' in world
assert 'setDirty(); // Zoom is persisted in the .sbgm' in world
print('PASS Stage 4.03: atlas pan/anchored zoom, world zoom, object nav and playback')
