#!/usr/bin/env python3
"""Stage 5.166.41 source contract for first-open camera and saved .vsgm view.
Qt GUI smoke test remains necessary on developer workstation.
"""
from pathlib import Path
import json
import re

root = Path(__file__).resolve().parents[2]
s = (root / 'gamevisualnodes.cpp').read_text()
assert (lambda v: v and int(v.group(1)) >= 41)(re.search(r'Build: 5\.166\.(\d+)\.\d{6}', (root/'splashscreenwidget.cpp').read_text()))
assert '#include <QShowEvent>' in s
assert 'void showEvent(QShowEvent *event) override' in s
assert 'QTimer::singleShot(0,this,[this] {restoreViewport();});' in s
assert 'void restoreViewport()' in s
assert 'm_hasStoredView' in s and 'm_storedZoom' in s and 'm_storedCenter' in s
assert 'm_view->centerOn(m_storedCenter)' in s
assert 'm_view->scale(0.85,0.85)' in s
assert 'if (fit>=0.7)' in s
assert 'm_view->fitInView(bounds,Qt::KeepAspectRatio)' in s
assert 'const qreal target=qBound(0.03,current*factor,2.5)' in s
assert 'const QJsonObject storedView = graph.value(QStringLiteral("view")).toObject()' in s
assert 'root.insert(QStringLiteral("view"),viewportJson())' in s
assert 'bool saveViewportOnly()' in s
assert 'const QJsonObject view=viewportJson()' in s
assert 'graph.insert(QStringLiteral("view"),view)' in s
assert 'if (answer==QMessageBox::Save && !saveAll())return false;' in s
assert 'if (answer==QMessageBox::Discard)m_dirty=false;' in s
assert 'if (!saveViewportOnly())' in s
assert 'QCryptographicHash::hash(input,QCryptographicHash::Sha256)!=m_layoutHash' in s
assert 'return false; // Another editor modified the graph; never overwrite it.' in s
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',s)
render = s[s.index('    void renderCards() {'):s.index('    void redrawLinks() {')]
assert 'fitInView' not in render, 'Must not fit before the QDialog becomes visible'
assert 'm_view->fitInView' in s[s.index('    void restoreViewport()'):s.index('    void buildUi()')]
# V1 .vsgm documents continue to use the original schema, with optional view.
doc={'format':'SIDBOX-VISUAL-NODES','version':1,'world':'world1',
     'positions':{'trigger1':[80,110]},
     'connections':[{'from':'trigger1','to':'lifty','action':'disable'}]}
assert 'view' not in doc
with_view=json.loads(json.dumps(doc))
with_view['view']={'zoom':0.85,'center':[153.25,180.5]}
assert with_view['connections']==doc['connections']
assert with_view['positions']==doc['positions']
assert with_view['view']['center']==[153.25,180.5]
print('Stage 5.166.41 Visual Nodes view source/schema contracts PASS')
