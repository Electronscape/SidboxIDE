from pathlib import Path
import re

root=Path(__file__).resolve().parents[2]
source=(root/'gameanimationeditor.cpp').read_text()
header=(root/'gameanimationeditor.h').read_text()

assert 'void mouseDoubleClickEvent(QMouseEvent *event) override' in source
assert 'if (doubleClicked) doubleClicked(frame' in source
assert 'if (clicked) clicked(frame' not in source
assert 'const QString number = QString::number(n)' in source
assert 'class AnimationTimelineList final : public QListWidget' in source
assert (('takeItem(m_draggedRow)' in source and 'insertItem(destination, item)' in source)
        or ('it->frames.takeAt(from)' in source and 'it->frames.insert(to, frame)' in source))
assert (('reorderedTicks.append(item->data(Qt::UserRole + 1).toInt());' in source
         and 'it->frameTicks = reorderedTicks;' in source)
        or ('it->frameTicks.takeAt(from)' in source
            and 'it->frameTicks.insert(to, ticks)' in source))
assert 'clip.frameTicks.append(m_ticks->value());' in source
assert 'clip.frameTicks.removeAt(position);' in source
assert 'std::swap(clip.frameTicks[pos], clip.frameTicks[to]);' in source
assert 'c["frameTicks"] = frameDurations;' in source
assert 'c.value("frameTicks").toArray()' in source
assert 'root["version"] = 2;' in source
assert 'const uint8_t *frame_ticks;' in source
assert 'duration = clip->frame_ticks[a->position]' in source
assert 'if (!clip->frame_ticks)' in source
assert 'QSpinBox *m_frameTicks = nullptr;' in header
assert 'QDialog { background:#10161e; color:#e5eaf2; }' in source
assert 'border-radius:0px' in source

print('Stage 3.84 UI structure, frame timing, serialization and export: PASS')
