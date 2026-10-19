from pathlib import Path
root = Path(__file__).resolve().parents[2]
source = (root / 'pngpaletteimport.cpp').read_text()
old_source = Path('/mnt/data/gg_stage377/pngpaletteimport.cpp').read_text() if Path('/mnt/data/gg_stage377/pngpaletteimport.cpp').is_file() else None
assert 'void enableSourcePickCursor()' in source
assert 'qApp->installEventFilter(this)' in source
assert 'Qt::CrossCursor' in source
assert 'Qt::OpenHandCursor' in source
assert 'QEvent::KeyPress || event->type() == QEvent::KeyRelease' in source
assert 'm_before->enableSourcePickCursor();' in source
assert 'm_before->setObjectName(QStringLiteral("pngOriginalPreview"));' in source
assert 'm_after->enableSourcePickCursor();' not in source
assert 'sourcePixelSelected(at, bool(event->modifiers() & Qt::ShiftModifier))' in source
assert 'automaticCapacity = paletteSlotCount - protectedColours.size()' in source
if old_source is not None:
    marker = '} // namespace SidboxPngImport'
    assert source.split('namespace SidboxPngImport {', 1)[1].split(marker)[0] == old_source.split('namespace SidboxPngImport {', 1)[1].split(marker)[0], 'Palette conversion unexpectedly changed'
print('Stage 3.77a picker cursor source checks passed')
