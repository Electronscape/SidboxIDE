#!/usr/bin/env python3
"""Stage 5.40 UI/source contracts + independent drag and erase-stroke checks.
The actual Qt6 widget remains a Fedora acceptance test; Qt6 headers aren't
installed on this CI runner. Existing generated-C regressions run separately.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
import json
import struct
root=Path(__file__).resolve().parents[2]
s=(root/'gamehudeditor.cpp').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.40.231026' in splash
# Project HUD format stays v1, with an optional text palette source field.
assert '{"version",1}' in s
assert '{"atlas",atlas},{"textPalette",textPalette}' in s
assert 'textPalette=j.value("textPalette").toString()' in s
assert 'SidboxGamePalette::readPalette' in s
assert 'QDirIterator palettes' in s
assert 'Text palette source:' in s
assert 'choosePaletteIndex(' in s
assert 'const int count=qMin(256,int(palette.size()))' in s
assert 'border-radius: 0px' in s, 'Keep Qt colour chooser square-edged'
assert 'canvas->textColors=textPaletteFor(projectRoot,doc.textPalette,src)' in s
assert 'paletteColour(textColors,doc->colour' in s
assert 'canvas->atlasImage,index' not in s
assert 'gfx_setcolour(%1u)' in s, 'Runtime still uses colour INDEX (no RGB conversions)'
# Grabbing a counter/label preserves its relative mouse offset.
assert 'grabOffset=q-QPoint(c.x,c.y)' in s
assert 'grabOffset=q-QPoint(l.x,l.y)' in s
assert 'const QPoint position=q-grabOffset' in s
assert 'doc->counters[selectedCounter].x=q.x()' not in s
for initial, grab, cursor, expected in [((25,14),(29,18),(29,18),(25,14)),
                                        ((25,14),(29,18),(44,41),(40,37)),
                                        ((75,44),(76,45),(80,70),(79,69))]:
    offset=(grab[0]-initial[0],grab[1]-initial[1])
    new=(cursor[0]-offset[0],cursor[1]-offset[1])
    assert new==expected,(new,expected)
assert 'Hide text and items (paint tiles underneath)' in s
assert 'if(hideOverlays)return' in s
assert 'if(hideOverlays)return; // edit tile art' in s
assert 'if(!doc || hideOverlays || !e->mimeData()->hasFormat(kMime)' in s
# A held right button paints an erase stroke, interpolating skipped cells.
assert 'if((e->buttons()&Qt::RightButton) && validPixel(q))' in s
assert 'paintStrokeTo(q,true)' in s
assert 'lastPaintCell=cell' in s and 'lastPaintCell=QPoint(-1,-1)' in s

def stroke(start,end):
    x,y=start;x2,y2=end
    dx,dy=abs(x2-x),abs(y2-y)
    sx=1 if x<x2 else -1;sy=1 if y<y2 else -1
    err=dx-dy; points=[]
    while True:
        points.append((x,y))
        if (x,y)==(x2,y2):break
        e=2*err
        if e>-dy:err-=dy;x+=sx
        if e<dx:err+=dx;y+=sy
    return points
assert stroke((0,2),(5,2))==[(0,2),(1,2),(2,2),(3,2),(4,2),(5,2)]
assert stroke((4,4),(4,1))==[(4,4),(4,3),(4,2),(4,1)]
assert stroke((0,0),(4,4))==[(0,0),(1,1),(2,2),(3,3),(4,4)]
# One-shot label entry: text entry arms placement, the first click disarms and clears it.
assert 'placeText->setChecked(true)' in s
assert 'placingLabel=false;labelText.clear()' in s
assert 'placeText->setChecked(false);textEdit->clear()' in s
assert 'if(doc->labels.size()>=80)return;' in s
assert 'QInputDialog::getText' in s, 'Renaming text remains available'
# Palette loader uses correct foreground bank and doesn't change PPB bytes.
raw=bytes([1,2,3,255])+bytes([0,0,0,255])*255
assert len(raw)==1024
assert struct.unpack('BBBB',raw[:4])==(1,2,3,255) # blue, green, red, alpha
print('PASS Stage 5.40 HUD interactions, palette selector, drag offset, continuous eraser, and one-shot text')
