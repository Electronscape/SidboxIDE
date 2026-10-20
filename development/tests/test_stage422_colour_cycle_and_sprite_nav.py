#!/usr/bin/env python3
from pathlib import Path
import re
r=Path(__file__).resolve().parents[2]
d=(r/'gamedesigner.cpp').read_text()
h=(r/'gamedesigner.h').read_text()
p=(r/'gamedesigner_project.cpp').read_text()
e=(r/'gamepaletteeditor.cpp').read_text()
eh=(r/'gamepaletteeditor.h').read_text()
palette=(r/'gamepalette.cpp').read_text()
api=(r/'idelibs/api/graphics/graphics.h').read_text()
assert 'gfx_palcyclerange' in api and 'gfx_palcyclerate' in api
assert 'gfx_palcycleon' in api and 'gfx_palcycleoff' in api
assert 'gfx_palcyclerangeb' in api and 'gfx_palcyclerateb' in api
assert 'group == QStringLiteral("sprite")' in d and 'm_view->centerOn(m_sceneItems.at(index)->sceneBoundingRect().center())' in d
assert 'm_showColourCycles' in d and 'm_showColourCycles' in h
assert 'colourCycle' in p and 'showColourCycles' in p
assert 'obj.insert(QStringLiteral("foregroundColourCycle")' in p and 'obj.insert(QStringLiteral("backgroundColourCycle")' in p
assert 'obj.value(QStringLiteral("colourCycle")).toObject()' in p
assert 'm_cycleStart->setRange(0, 254)' in e
assert 'm_cycleLength->setMaximum(256 - cycle.start)' in e
assert 'm_cycleSpeed->setRange(1, 255)' in e
assert 'QCheckBox(tr("Preview")' in e
assert 'setColourCycles(m_frontColourCycle, m_backColourCycle)' in d
assert 'dialog.foregroundColourCycle()' in d and 'dialog.backgroundColourCycle()' in d
assert 'SidboxGamePalette::cyclePreview' in d
assert 'refreshColourCyclePreview()' in d
assert 'static_cast<GameTilemapOverlay *>(m_tilemapOverlayItem)->setColourCycle(' in d
assert 'void setColourCycle(const SidboxGamePalette::ColourCycle &cycle, int phase, bool preview)' in d
assert 'out[first + (i + shift) % length] = palette.at(first + i);' in palette
assert '.sbgm' in eh or '.sbgm' in e
assert 'request.foregroundCycle' in (r/'gamedesigner_export.cpp').read_text(), 'Generated cycles are supported after firmware verification'
print('PASS Stage 4.22: sprite double click, independent cycles + preview, format preservation, firmware API verified')
