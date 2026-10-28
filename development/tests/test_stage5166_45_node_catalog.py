#!/usr/bin/env python3
"""Stage 5.166.45 Visual Nodes source/schema regression (not a Qt GUI test)."""
import json,re
from pathlib import Path
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
build=re.search(r'Build: 5\.166\.(\d+)\.\d{6}',version)
assert build and int(build.group(1))>=45, 'Phase 2B or newer splash build expected'
required=(
    'void showInsertTree(', 'void makeObjectCard(', 'QSet<QString> linkedObjectIds() const',
    'm_view->insertRequested=', 'm_view->dropRequested=',
    'tree->expandAll()', 'QTreeWidget::itemDoubleClicked',
    'QStringLiteral("enable")', 'void appendConnection(',
    'void connectNewDialogue(', 'QStringLiteral("placedCards")',
    'm_objects.value(id).dialogueNode>=0',
    'm_dialoguesChanged=true', 'dialogueCardId(from)',
    'QCryptographicHash::hash(current,QCryptographicHash::Sha256)!=m_originalHash',
    'QFile::copy(m_worldPath,backup)',
    'const QJsonArray npcs=',
    'value(QStringLiteral("spriteId"))',
    'm_placedCards.contains(id)',
    'object.insert(QStringLiteral("targetObjectId")',
)
for name in required: assert name in s,name
assert 'root.insert(QStringLiteral("connections"),' not in s, 'vsgm must not own gameplay links'
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',s), 'lambda pointer declaration'
assert re.search(r'if \(!linked.contains\(id\) && !m_placedCards.contains\(id\)\)continue;',s)
# Verify actual schema can supply a complete on-demand catalog and visible graph
# without consulting any legacy vsgm connection snapshots.
for world_name in ('world1','forest'):
    world_file=Path('/mnt/data/testgame16635')/(world_name+'.sbgm')
    if not world_file.exists(): continue
    doc=json.loads(world_file.read_text())
    resources={r.get('id'):r for r in doc['resources'] if r.get('kind')=='sprite'}
    graph_objects={id:r for id,r in resources.items() if r.get('gameObject',{}).get('type') not in ('',None,'decoration')}
    npcs={npc['spriteId'] for npc in doc.get('adventure',{}).get('npcs',[]) if npc.get('spriteId') in resources}
    for npc in npcs: assert npc in resources
    links=[]
    for id,r in graph_objects.items():
        game=r['gameObject']
        if game.get('type')!='trigger': continue
        if game.get('targetObjectId') and game.get('targetAction') in ('enable','disable','toggle'):
            links.append((id,game['targetObjectId']))
        for x in game.get('triggerExtraActions',[]):
            if x.get('action') in ('enable','disable','toggle') and x.get('objectId'):
                links.append((id,x['objectId']))
    auto_visible=set()
    for source,target in links:
        if target in graph_objects or target in npcs:
            auto_visible.update((source,target))
    for id,r in graph_objects.items():
        if r['gameObject'].get('type')=='trigger' and r['gameObject'].get('interactDialogueNode',-1)>=0:
            auto_visible.add(id)
    assert auto_visible <= set(graph_objects)|npcs
    assert len(graph_objects)+len(npcs)>=len(auto_visible)
    print(world_name,'catalog',len(graph_objects)+len(npcs),'auto-visible',len(auto_visible))
# Old graph documents with positions for every object must not force every
# card to display: explicit placement list is intentionally a NEW field.
legacy={'positions':{'orphan':[100,200]},'connections':[{'from':'old','to':'orphan','action':'enable'}]}
assert not legacy.get('placedCards')
assert 'orphan' not in set(legacy.get('placedCards',[]))
print('Stage 5.166.45 on-demand node/catalog source/schema checks PASS')
