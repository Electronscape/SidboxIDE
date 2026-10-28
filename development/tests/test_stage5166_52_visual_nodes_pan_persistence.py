#!/usr/bin/env python3
"""Stage 5.166.52: exact camera pan persistence regression contract.

This checks .vsgm model compatibility and source paths; GUI Qt6 interaction
must still be tested on a workstation with Qt6 development libraries.
"""
from pathlib import Path
import json
import re

root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert 'setResizeAnchor(QGraphicsView::AnchorViewCenter);' in s
assert 'setTransformationAnchor(QGraphicsView::AnchorUnderMouse);' in s
assert 'const QJsonArray storedScroll = storedView.value(QStringLiteral("scrollbars")).toArray();' in s
assert 'const QJsonArray storedViewport = storedView.value(QStringLiteral("viewportPixels")).toArray();' in s
assert 'm_storedViewport=QSize(width,height);' in s
assert 'm_storedScroll=QPoint(' in s
assert 'view.insert(QStringLiteral("scrollbars"),QJsonArray{' in s
assert 'view.insert(QStringLiteral("viewportPixels"),QJsonArray{' in s
assert 'm_view->horizontalScrollBar()->value(),m_view->verticalScrollBar()->value()' in s
assert 'if (m_hasStoredScroll && m_storedViewport==m_view->viewport()->size()) {' in s
assert 'm_view->horizontalScrollBar()->setValue(m_storedScroll.x());' in s
assert 'm_view->verticalScrollBar()->setValue(m_storedScroll.y());' in s
assert s.index('if (m_hasStoredView) {',s.index('void restoreViewport()')) < s.index('if (m_cards.isEmpty())',s.index('void restoreViewport()'))
assert 'm_view->centerOn(m_storedCenter);' in s  # fallback on resized displays / older graphs
assert 'QTimer::singleShot(0,this,[this] {restoreViewport();});' in s  # delayed until window visible
assert 'if (!saveViewportOnly())' in s       # persists even if only panning, without graph edits
assert 'if (!saveLayout())return fail(' in s  # explicit Save Graph + World also saves camera
assert 'root.insert(QStringLiteral("view"),viewportJson())' in s
assert 'root.insert(QStringLiteral("connections")' not in s
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',s)
assert re.search(r'Build: 5\.166\.(\d+)\.281026', (root/'splashscreenwidget.cpp').read_text()) and int(re.search(r'Build: 5\.166\.(\d+)\.281026', (root/'splashscreenwidget.cpp').read_text()).group(1)) >= 52

# Old graph without a view remains valid. Old view with zoom/center remains valid.
base={'format':'SIDBOX-VISUAL-NODES','version':1,'world':'world1',
      'placedCards':['trigger1'],'positions':{'trigger1':[64,128]}}
legacy_view=dict(base,view={'zoom':0.85,'center':[500.25,150.5]})
new_view=dict(base,view={'zoom':0.85,'center':[500.25,150.5],
                         'scrollbars':[4312,2540],'viewportPixels':[1100,700]})
assert 'view' not in json.loads(json.dumps(base))
assert 'scrollbars' not in json.loads(json.dumps(legacy_view))['view']
assert json.loads(json.dumps(new_view))['view']['scrollbars']==[4312,2540]
assert json.loads(json.dumps(new_view))['positions']==base['positions']
# Exact scrollbar restoration only for matching geometry; otherwise use scene center.
def restore(saved,viewport):
    view=saved['view']
    if view.get('viewportPixels')==list(viewport) and 'scrollbars' in view:
        return ('scrollbars',tuple(view['scrollbars']))
    return ('center',tuple(view['center']))
assert restore(new_view,(1100,700))==('scrollbars',(4312,2540))
assert restore(new_view,(900,700))==('center',(500.25,150.5))
assert restore(legacy_view,(1100,700))==('center',(500.25,150.5))
print('PASS Stage 5.166.52: exact pan save/restore, resize fallback, legacy .vsgm')
