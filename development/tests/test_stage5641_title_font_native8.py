#!/usr/bin/env python3
"""Stage 5.64.1 SIDBOX font-height alignment contract.

Hardware validation from user: gfx_drawtextf(...,size_y=1) is 8px tall.
Static source tests; real GUI/H743 acceptance is still required.
"""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
title=(root/'gametitlescreeneditor.cpp').read_text()
guide=(root/'guidesigner_graphics.cpp').read_text()
runtime=(root/'idelibs/codehelpers/game/gametitle-runtime.rulec').read_text()
generator=(root/'gametitleruntime.cpp').read_text()
start=title.index('QImage textImage(')
end=title.index('QGraphicsItem *addPreviewItem(',start)
body=title[start:end]
assert 'GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,Qt::white);' in body
assert 'QImage guiGlyphs(width,16,' in body
assert 'const QImage glyphs=guiGlyphs.scaled(width,8,Qt::IgnoreAspectRatio,' in body
assert 'Qt::FastTransformation' in body
assert 'QImage base(width+2,10,' in body
assert 'base.scaled(base.width()*scaleX,base.height()*scaleY,' in body
assert 'qBound(1,a.fontSizeX,4)' in body and 'qBound(1,a.fontSizeY,4)' in body
assert 'a.outlineEnabled' in body and 'tint(outline)' in body
assert '8×8 native font' in title
assert 'kCoderGirlSystemFont[256][8]' in guide
assert 'y + row * 2' in guide  # GUI helper still uses 8x16; title collapses it to 8x8.
assert 'return 8*title_scale(a->size_y);' in runtime
assert 'gfx_drawtextf(a->x,a->y,a->text,a->size_x,a->size_y)' in runtime
assert 'fontSizeY' in generator and 'fontSizeX' in generator
assert 'Build: 5.64.1.231026' in (root/'splashscreenwidget.cpp').read_text()
# The eight vertical rows encoded per character really are the source data.
block=guide.split('kCoderGirlSystemFont[256][8] = {',1)[1].split('};',1)[0]
entries=re.findall(r'^\s*\{\s*(?:0x[0-9a-fA-F]{2}\s*,\s*){7}0x[0-9a-fA-F]{2}\s*\}',block,re.M)
assert len(entries)==256, len(entries)
print('Stage 5.64.1 native 8x8 title preview and runtime selector-height regression: PASS')
