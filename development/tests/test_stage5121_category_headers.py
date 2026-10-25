#!/usr/bin/env python3
"""5.121 root cards shade category label; title-first mini cards unchanged."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
s=(root/'gamefloweditor.cpp').read_text()
assert 'Build: 5.121.251026' in (root/'splashscreenwidget.cpp').read_text()
# WORLD label at y=4 (with icon) is in the 22px header; forest is below.
assert 'kind->setParentItem(card);kind->setPos(36,4)' in s
assert 'symbol->setParentItem(card);symbol->setPos(15,4)' in s
assert 'name->setParentItem(card);name->setPos(14,24)' in s
assert ': QRectF(7,0,card->rect().width()-7,22),card' in s
assert ': QRectF(7,21,card->rect().width()-7,26)' not in s
# Big Steve and other title-first mini cards stay at y=5 with 25px banner.
assert s.count('expandableTrigger ? 58 : 25')==2
assert 'label->setPos(12,5)' in s
assert 'kind->setPos(12,29)' in s
# Expandables and choice drilldown retain geometry and rendering.
assert 'expandableTrigger ? QRectF(7,0,card->rect().width()-7,60)' in s
assert 'QRectF(0,0,width,27),card' in s
assert s.count('QRectF(0,0,card->rect().width(),70),card')==1
print('Stage 5.121 category-first banner position and unchanged mini cards: PASS')
