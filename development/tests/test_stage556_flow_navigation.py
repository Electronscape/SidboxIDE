"""Stage 5.56 static regression: scene backplanes, F2, PPB art previews.
Run: python3 development/tests/test_stage556_flow_navigation.py
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
s = (root / 'gamefloweditor.cpp').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()

def check(value, what):
    assert value, what

# All four requested changes must be real graph functionality, not UI text.
check('QKeySequence(Qt::Key_F2)' in s, 'F2 rename shortcut is missing')
check('FlowGroupTitleItem *title=groupTitles.value(id,nullptr)' in s, 'F2 must edit in place')
check('title->beginEditing()' in s, 'F2 must start editing instead of opening a modal dialog')
check('mousePressEvent(QGraphicsSceneMouseEvent *event) override' in s and 'beginEditing();' in s,
      'first click needs to reach editable group title')
check('const auto resizeWorldBands=' in s, 'world backplanes must update dynamically')
check('resizeWorldBands(false)' in s and 'resizeWorldBands(true)' in s, 'move and drop must update world backplanes')
check('worldBands.insert(world,band)' in s, 'world background tracking is missing')
check('view->viewport()->update()' in s, 'world switch/move must schedule a repaint')
check('centerOn(QPointF(band.left()' in s, 'world selection must recenter on its new graph')
check('flowArtworkIcon' in s and 'SidboxPpb::read(filename,&picture)' in s,
      'artwork must decode the existing PPB, not a baked/new image')
check('qBound(0,node.artFrame,cols*rows-1)' in s, 'resource frame lookup is missing')
check('stamp.compose(sheet)' in s, 'source PPB stamps must honour arrangement and flips')
check('node.artCells.at(cell)' in s, 'inventory 2x2 cell indices must be respected')
check('KeepAspectRatio' in s and 'QPixmap result(16,16)' in s, 'thumbs must fit 16x16')
check('new QGraphicsPixmapItem(art,card)' in s and 'new QGraphicsPixmapItem(art,child)' in s,
      'normal and mini card art previews must be rendered')
check('QFile::WriteOnly' not in s and 'SidboxPpb::write(' not in s, 'flow editor must not output PPBs')
check('Build: 5.57.231026' in splash, 'splash build version not advanced')
print('Stage 5.56 Logic Flow source regression checks: PASS')
