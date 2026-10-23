#!/usr/bin/env python3
"""Stage 5.62 source regression: HUD uses the same firmware glyphs as GUI/Title.

This validates source contracts, not a complete Qt build or physical display.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
hud = (root / 'gamehudeditor.cpp').read_text()
guide = (root / 'guidesigner_graphics.cpp').read_text()
title = (root / 'gametitlescreeneditor.cpp').read_text()
header = (root / 'guidesigner_detail.h').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()

start = hud.index('static void previewText(')
end = hud.index('class HudCanvas :', start)
preview = hud[start:end]
assert '#include "guidesigner_detail.h"' in hud
assert 'GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,foreground);' in preview
assert 'QFontDatabase::systemFont' not in preview.replace('// Do not rasterise and stretch the desktop\'s QFontDatabase::FixedFont:', '')
assert 't.drawText(' not in preview
assert 'QImage glyphs(qMax(8,columns*8),lines*16,' in preview
assert 'const QRect target(x*zoom,y*zoom,glyphs.width()*zoom,glyphs.height()*zoom);' in preview
assert 'p.drawImage(target.translated(delta),edges);' in preview
assert 'p.drawImage(target,glyphs);' in preview
assert "if(ch=='\\n')" in preview
assert 'void drawCoderGirlText(' in header
assert 'kCoderGirlSystemFont[256][8]' in guide
assert 'y + row * 2' in guide
assert 'GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,Qt::white);' in title
# Labels, live numeric stats, and collectable counters all use the same preview.
assert len(re.findall(r'previewText\(p,', hud)) == 3
# Runtime must retain its original hardware-side text generation.
assert 'gfx_drawtext(x,y,text);' in hud
assert 'Build: 5.62.231026' in splash
print('Stage 5.62 HUD/Title/GUI canonical SIDBOX 8x16 font source checks: PASS')
