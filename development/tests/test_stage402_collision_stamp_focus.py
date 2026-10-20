"""Stage 4.02: bank/editor mode and enlarged collision coordinate regression.

Source-only because this environment has no Qt6 development SDK; the final
mouse/double-click interaction still needs a real Qt Creator GUI check.
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
cpp = (root / 'gametilemap.cpp').read_text()
h = (root / 'gametilemap.h').read_text()
assert '#include <QStackedWidget>' in cpp
assert 'QStackedWidget *m_collisionViews = nullptr;' in h
assert 'void openCollisionStampEditor(int row);' in h
assert 'auto *collisionSidebar = new QStackedWidget(m_stampTabs);' in cpp
assert 'collisionSidebar->addWidget(collisionBankPane);' in cpp
assert 'collisionSidebar->addWidget(collisionEditPane);' in cpp
assert 'collisionSidebar->setCurrentIndex(0);' in cpp
assert 'collisionSidebar->setStretchFactor' not in cpp
assert 'itemDoubleClicked' in cpp and 'openCollisionStampEditor(m_collisionList->row(item))' in cpp
assert 'm_canvas->editPlacedCollision = [this](int shapeIndex)' in cpp
assert 'openCollisionStampEditor(shapeIndex);' in cpp
assert 'GGCollisionEditorAccept' in cpp and 'GGCollisionEditorCancel' in cpp
assert 'm_collisionViews->setCurrentIndex(0);' in cpp
assert 'm_collisionViews->setCurrentIndex(1);' in cpp
assert 'if (!valid && m_collisionViews && m_collisionViews->currentIndex() != 0)' in cpp
assert 'static constexpr int gridUnit = 96;' in cpp
assert 'qRound(double(p.x()) * s.tileSize / gridUnit)' in cpp
assert 'qRound(double(p.y()) * s.tileSize / gridUnit)' in cpp
assert 'const int unit = gridUnit, size = s.tileSize;' in cpp
assert 'gridUnit * gridUnit /' in cpp
assert 'collisionScroll->setAlignment(Qt::AlignCenter);' in cpp
assert 'finishCollisionStampEdit(true)' in cpp and 'finishCollisionStampEdit(false)' in cpp
assert 'QDialog::keyPressEvent(event);' in cpp
# Existing editing/undo/paint work must stay wired.
for needle in ('m_collisionCanvas->strokeStarted', 'm_collisionCanvas->modified',
               'm_collisionCanvas->pointSelected', 'resizeSelectedCollisionStamp',
               'm_collisionInsertPoint', 'm_collisionDeletePoint',
               'recordChange(before)', 'selectCollisionStamp(int row)'):
    assert needle in cpp, needle
print('PASS: Collision bank/editor navigation, enlarged canvas, point conversion and undo hooks')
