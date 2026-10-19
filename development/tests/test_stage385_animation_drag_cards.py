from pathlib import Path

root = Path(__file__).resolve().parents[2]
source = (root / 'gameanimationeditor.cpp').read_text()
header = (root / 'gameanimationeditor.h').read_text()

# User-supplied screenshot layout: mode directly under state selector.
assert 'leftLayout->addWidget(m_stateList, 1);' in source
assert 'leftLayout->addWidget(modeBox);' in source
assert source.index('leftLayout->addWidget(m_stateList, 1);') < source.index('leftLayout->addWidget(modeBox);')
assert 'new QRadioButton(tr("%1-Direction").arg(n), modeBox)' in source
assert 'for (int n : {2, 4, 8})' in source
assert 'connect(m_directionModeButtons, &QButtonGroup::idClicked' in source
assert 'QButtonGroup *m_directionModeButtons' in header

# Screenshot layout: actual painted index/image/ms in three bordered sections.
assert 'class AnimationFrameCardDelegate final : public QStyledItemDelegate' in source
assert 'const int cell = index.data(Qt::UserRole).toInt();' in source
assert 'const QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));' in source
assert 'QStringLiteral("%1ms").arg(ticks * 20)' in source
assert 'p->drawLine(card.left() + 1, card.top() + 23' in source
assert 'm_timeline->setItemDelegate(new AnimationFrameCardDelegate(m_timeline));' in source

# Qt drop path: uses its own MIME format and explicitly accepts drops.
assert 'new QDrag(this)' in source
assert 'application/x-sidbox-animation-frame' in source
assert 'void dragEnterEvent(QDragEnterEvent *event) override' in source
assert 'void dragMoveEvent(QDragMoveEvent *event) override' in source
assert 'void dropEvent(QDropEvent *event) override' in source
assert 'event->setDropAction(Qt::MoveAction);' in source
assert 'event->accept();' in source
assert 'QTimer::singleShot(0, this, [this, source, destination]' in source
assert 'm_dropInsertion = next;' in source

# Actual model update is atomic for both atlas index and the per-position duration.
assert 'std::function<void(int, int)> reordered' in source
assert 'const int frame = it->frames.takeAt(from);' in source
assert 'const int ticks = it->frameTicks.takeAt(from);' in source
assert 'it->frames.insert(to, frame);' in source
assert 'it->frameTicks.insert(to, ticks);' in source
assert 'refreshTimeline();' in source

# Source preserves Stage3.84 format, generated duration and look.
assert 'c["frameTicks"] = frameDurations;' in source
assert 'duration = clip->frame_ticks[a->position]' in source
assert 'border-radius:0px' in source
print('Stage 3.85 frame cards / mode panel / reorder source checks: PASS')
