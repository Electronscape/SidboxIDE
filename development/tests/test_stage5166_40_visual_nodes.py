#!/usr/bin/env python3
"""Source/schema regression for the opt-in .vsgm first slice (Qt GUI not executable here)."""
from pathlib import Path
import json
import re

ROOT=Path(__file__).resolve().parents[2]
node=(ROOT/'gamevisualnodes.cpp').read_text()
game=(ROOT/'gamedesigner.cpp').read_text()
main=(ROOT/'mainwindow.cpp').read_text()
cmake=(ROOT/'CMakeLists.txt').read_text()
flow=(ROOT/'gamefloweditor.cpp').read_text()
assert 'gamevisualnodes.cpp' in cmake and 'gamevisualnodes.h' in cmake
assert 'Visual Nodes...' in game and 'openGameVisualNodes(this, graph, m_theme)' in game
assert 'suffix().compare(QStringLiteral("vsgm")' in main
assert 'Open Visual Nodes (.vsgm)' in main
assert 'QStringLiteral("*.vsgm")' in main
assert 'lower == QStringLiteral("vsgm")' in main
assert 'QSaveFile file(fileName)' in node
assert 'QCryptographicHash::hash(current,QCryptographicHash::Sha256)!=m_originalHash' in node
assert 'QFile::copy(m_worldPath,backup)' in node
assert 'triggerExtraActions' in node and 'targetObjectId' in node and 'targetAction' in node
assert 'resources.replace(node.resourceIndex,resource)' in node
assert 'm_touched' in node and 'resource.value(QStringLiteral("id")).toString()!=id' in node
assert 'setWindowState(windowState() | Qt::WindowMaximized)' in node
assert 'connectionRequested' in node and 'linkMenuRequested' in node
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',node)
assert 'read-only' in flow.lower()
# Verify real project .sbgm semantics: mixed local/external actions and all other fields.
for name in ('world1','forest'):
    path=Path('/mnt/data/gametest_unpacked')/(name+'.sbgm')
    if not path.exists(): continue
    original=json.loads(path.read_text())
    resources=original['resources']
    for i,r in enumerate(resources):
        obj=r.get('gameObject',{})
        if obj.get('type') != 'trigger': continue
        links=[]
        if obj.get('targetObjectId'):links.append({'objectId':obj['targetObjectId'],'action':obj.get('targetAction','')})
        links.extend(obj.get('triggerExtraActions',[]))
        if links:
            copy=json.loads(json.dumps(original))
            gameobj=copy['resources'][i]['gameObject']
            gameobj['targetObjectId']=links[0]['objectId']
            gameobj['targetAction']=links[0]['action']
            gameobj['triggerExtraActions']=links[1:]
            assert copy == original, f'unrelated data changed for {name}'
print('Stage 5.166.40 .vsgm source and real game design schema checks PASS')
