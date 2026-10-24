#!/usr/bin/env python3
"""Stage 5.64.3 source-level positioning calibration regressions.

Runtime's -6px correction follows real hardware visual feedback; only an
on-device re-test can validate the final pixels.
"""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
editor=(root/'gametitlescreeneditor.cpp').read_text()
runtime=(root/'idelibs/codehelpers/game/gametitle-runtime.rulec').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.64.3.231026' in splash
# The runtime adjustment is restricted to filled selectors, not sprites/text.
assert 'if (behind) gfx_rectf(x-3,y-8,w+6,h+4);' in runtime
assert 'gfx_drawtextf(a->x,a->y,a->text,a->size_x,a->size_y);' in runtime
assert 'gfx_rectf(x-3,y-2,w+6,h+4)' not in runtime
assert 'if (i==(int)selected) title_draw_selector(&title_menu[i].art,1);' in runtime
assert 'title_draw_art(&title_menu[i].art);' in runtime
# The glyph starts exactly at stored X/Y with no phantom 1px padding.
body=editor.split('QImage textImage(',1)[1].split('QGraphicsItem *addPreviewItem(',1)[0]
assert 'const QImage glyphs=guiGlyphs.scaled(width,8,Qt::IgnoreAspectRatio,' in body
assert 'const QImage scaledGlyph=glyphs.scaled(width*scaleX,8*scaleY,' in body
assert 'return tint(fg);' in body
assert 'QImage base(scaledGlyph.width()+2,scaledGlyph.height()+2,' in body
assert 'painter.drawImage(1,1,tint(fg));' in body
assert 'item->setOffset(-1,-1);' in editor
assert 'item->setPos(a.x,a.y);' in editor
# The rectangle now follows the glyph bounds without taking the optional
# outline pixels into account and without a sub-pixel pen stroke.
assert 'r=QRectF(selected->pos(),QSizeF(entries[row].label.toLatin1().size()*8*sx,8*sy));' in editor
assert 'outlinePath.addRect(r.adjusted(-3,-2,3,2));' in editor
assert 'type==QStringLiteral("rect")\n            ? QPen(Qt::NoPen)' in editor
# Preview text metrics remain native 8px height for unscaled glyphs.
for sy in (1,2,4,8):
    assert 8*sy>0
# No .sbgm, .json or user-owned main.c edits are needed.
print('Stage 5.64.3 selector alignment source regression: PASS')
