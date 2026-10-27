#!/usr/bin/env python3
"""Regression for 5.166.17: nestedCellWidth undeclared in draw scope.
This source/sizing test isn't a substitute for Qt6 compilation.
"""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
s=(root/'gamefloweditor.cpp').read_text()
assert 'Build: 5.166.17.1.271026' in (root/'splashscreenwidget.cpp').read_text()
# Local declaration must precede its use inside the nested array renderer.
part=s[s.index('const QSizeF nestedSize=flowArrayGroupSize(inner,graph,layout);'):]
part=part[:part.index('sub->onToggle=')]
assert re.search(r'const qreal nestedW=nestedSize\.width\(\),nestedH=nestedSize\.height\(\);\s*'
                 r'//[^\n]*\n\s*//[^\n]*\n\s*//[^\n]*\n\s*'
                 r'const qreal nestedCellWidth=\(nestedW-54\.0\)/2\.0;',part)
assert 'mini->setPos(16+(i%2)*(nestedCellWidth+22),rowY);' in part
assert part.index('const qreal nestedCellWidth') < part.index('mini->setPos(16+(i%2)*(nestedCellWidth+22),rowY);')
assert 'return QSizeF(2*cellWidth+54,height);' in s
# If measured child cells expand, the same-sized enclosing group expands too.
for cell in (250,350,460,710):
    width=2*cell+54
    restored=(width-54)/2
    left=16
    right=left+restored+22
    assert right >= left+cell+22
    assert right+cell <= width-16
print('Stage 5.166.17.1 nested array scope / width regression: PASS')
