#!/usr/bin/env python3
"""Stage 4.25: foreground alpha slider, optional World preview, unchanged .pal."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
pe = (r/'gamepaletteeditor.cpp').read_text()
ph = (r/'gamepaletteeditor.h').read_text()
world = (r/'gamedesigner.cpp').read_text()
wh = (r/'gamedesigner.h').read_text()
project = (r/'gamedesigner_project.cpp').read_text()
pal = (r/'gamepalette.cpp').read_text()
assert '#include <QSlider>' in pe
assert 'm_alphaSlider = new QSlider(Qt::Horizontal, this)' in pe
assert 'm_alphaSlider->setRange(0, 255)' in pe
assert 'QSignalBlocker block(m_alphaSlider)' in pe # selection/hex/picker cannot recurse
assert 'currentBankIsBackground() || m_index == 0' in pe # index0 remains reserved
assert 'const bool editableAlpha = !currentBankIsBackground() && m_index != 0' in pe
assert 'colour = qRgba(qRed(colour), qGreen(colour), qBlue(colour), alpha)' in pe
assert 'm_modified = true' in pe
assert 'm_alphaValue->setText(' in pe
assert 'm_alphaSwatch->setPixmap(preview)' in pe
assert 'QSlider *m_alphaSlider' in ph
# The native .pal writer continues emitting 4 bytes per colour, BG forced opaque.
assert 'bytes.append(char(qAlpha(colour)))' in pal
assert 'const QRgb opaque = colour | 0xFF000000u;' in pe
assert 'SidboxGamePalette::writePal(m_sourcePath, m_front, m_back' in pe
# Independent cycles still shuffle whole 32-bit palette entries, retaining alpha.
assert 'out[first + (i + shift) % length] = palette.at(first + i);' in pal
# Default RGB-only forced previews preserved, new alpha option only on request.
assert 'foreground && previewAlpha ? qAlpha(colour) : 255' in world
assert 'm_previewPaletteAlpha->setChecked(false)' in world
assert 'Preview palette alpha' in world
assert 'QCheckBox *m_previewPaletteAlpha' in wh
assert world.count('m_previewPaletteAlpha && m_previewPaletteAlpha->isChecked()') >= 4
assert 'm_previewPaletteAlpha->setEnabled(checked)' in world
assert 'previewPaletteAlpha' in project
assert 'm_previewPaletteAlpha->setChecked(obj.value(QStringLiteral("previewPaletteAlpha")).toBool(false))' in project
assert 'obj.insert(QStringLiteral("previewPaletteAlpha"), m_previewPaletteAlpha->isChecked())' in project
# No changes to runtime API or palette serializer necessary.
print('PASS Stage4.25: ARGB alpha slider and nonintrusive World preview')
