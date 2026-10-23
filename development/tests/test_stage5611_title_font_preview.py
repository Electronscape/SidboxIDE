#!/usr/bin/env python3
"""Source regression: title preview uses same fixed glyphs as GUI Designer.

The Qt6 GUI build and interactive check are separate acceptance steps.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
title = (root / 'gametitlescreeneditor.cpp').read_text()
guide = (root / 'guidesigner_graphics.cpp').read_text()
header = (root / 'guidesigner_detail.h').read_text()
cmake = (root / 'CMakeLists.txt').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()

start = title.index('QImage textImage(')
end = title.index('QGraphicsItem *addPreviewItem(', start)
renderer = title[start:end]
assert '#include "guidesigner_detail.h"' in title
assert 'GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,Qt::white);' in renderer
assert 'QFontDatabase::systemFont' not in renderer
assert 'gp.drawText(' not in renderer
assert 'QImage glyphs(width,16,' in renderer
assert 'text.toLatin1().size())*8' in renderer
assert 'qBound(1,a.fontSizeX,4)' in renderer
assert 'qBound(1,a.fontSizeY,4)' in renderer
assert 'a.outlineEnabled' in renderer and 'tint(outline)' in renderer
assert 'kCoderGirlSystemFont[256][8]' in guide
assert 'glyph[column]' in guide and 'y + row * 2' in guide
assert 'void drawCoderGirlText(' in header
assert 'guidesigner_graphics.cpp' in cmake
assert 'fontSizeX' in title and 'fontSizeY' in title
assert 'Build: 5.61.1.231026' in splash

block = guide.split('kCoderGirlSystemFont[256][8] = {', 1)[1].split('};', 1)[0]
entries = re.findall(r'^\s*\{\s*(?:0x[0-9a-fA-F]{2}\s*,\s*){7}0x[0-9a-fA-F]{2}\s*\}', block, re.M)
assert len(entries) == 256, f'Expected all 256 real GUI glyphs, found {len(entries)}'
print('Stage 5.61.1 canonical SIDBOX glyph preview source regression: PASS')
