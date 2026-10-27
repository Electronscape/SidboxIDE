#!/usr/bin/env python3
"""Stage 5.166.21 editor source contracts and generator compatibility."""
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
ui=(ROOT/'gamerpguieditors.h').read_text()
gen=(ROOT/'gameadventuregen.cpp').read_text()
assert 'Build: 5.166.28.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
for required in (
  'e->button()==Qt::MiddleButton',
  'horizontalScrollBar()->setValue(initialH-diff.x())',
  'verticalScrollBar()->setValue(initialV-diff.y())',
  'void wheelEvent(QWheelEvent *e) override',
  'setTransformationAnchor(QGraphicsView::AnchorUnderMouse)',
  'mapBounds.intersected(area)',
  'p->drawRect(mapBounds)',
  'Fit canvas',
  'view->mapBounds=QRectF(0,0,pixelWidth,pixelHeight)',
  'paletteScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff)',
  'paletteScroll->setWidgetResizable(true)',
  'const int first=qMax(0,(event->rect().top()/thumb)*cols())',
  'const int n=row*cols()+col',
  'class CgRpgMapAtlas : public QWidget',
  'cgRpgGlyphText(paint,px,py,str',
  'GuiDesignerDetail::drawCoderGirlText(glyph,0,0,s,Qt::white)',
  'SidboxPalettePicker::chooseIndex(&dialog,actualPalette()',
  'cgRpgChooseCell(&dialog,image,tile,cells[i]->value())',
  'paletteChoice->currentData().toString()',
  'atlas->currentData().toString()',
  'out.insert(QStringLiteral("palette")',
  'out.insert(QStringLiteral("atlas")',
): assert required in ui,required
assert 'QFont(QStringLiteral("Monospace")' not in ui
assert 'val==4||val==8' in gen
runtime=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
assert 'ga_defeat_window(void)' in runtime
assert 'scale_x==4u||scale_x==8u' in runtime
assert 'scale_y==4u||scale_y==8u' in runtime
print('PASS Stage 5.166.21: map viewport, wrapped atlas, native defeat preview and shared pickers')
