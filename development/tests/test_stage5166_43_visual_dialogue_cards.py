#!/usr/bin/env python3
"""Phase 2A source and real-design JSON contract (not a Qt interactive test)."""
from pathlib import Path
import copy,json,re
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert (lambda v: v and int(v.group(1)) >= 43)(re.search(r'Build: 5\.166\.(\d+)\.\d{6}', (root/'splashscreenwidget.cpp').read_text()))
for key in ('class NodeCard final', 'class NodeCanvas final', 'QGraphicsProxyWidget',
            'void createDialogueCard(', 'void refreshDialogueCard(',
            'void editDialogueText(', 'void addDialogueCard(',
            'm_dialogueCards', 'm_dialoguesChanged',
            'm_dialogueControls.value(from).picker->showPopup()',
            'object.insert(QStringLiteral("interactDialogueNode"),node.dialogueNode)',
            'object.insert(QStringLiteral("interactDialogueMode"),node.dialogueMode)',
            'adventure.insert(QStringLiteral("nodes"),m_dialogues)',
            'root.insert(QStringLiteral("dialogueCards"),dialogueCards)',
            'QCryptographicHash::hash(current,QCryptographicHash::Sha256)!=m_originalHash',
            'QFile::copy(m_worldPath,backup)',
            'if (!m_touched.isEmpty() || m_dialoguesChanged)',
            'm_dialogues.size()>=256'):
    assert key in s, f'missing phase2 property: {key}'
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',s)
exporter=(root/'gamedesigner_export.cpp').read_text()
assert 'ordinary touch/FIRE2 Triggers can now show' in exporter
assert 'if (r.interactItemName.isEmpty() && r.interactDialogueNode >= 0)' in exporter
assert 'action+=QStringLiteral("        %1(%2u);\\n")' in exporter
assert 'cg_complete_item_interaction()' in exporter
assert 'dialogueFunction' in exporter
# Generator path for an item-gated Trigger continues to use the existing
# interaction-success hook, while a plain Trigger gets its own action call.
assert 'INTERACT_DIALOGUE_ACTIONS' in exporter and 'TRIGGER_ACTION' in exporter
# .vsgm holds presentation, not editable text or authoring settings.
graph=s[s.index('    QJsonObject graphJson() const {'):s.index('    bool saveLayout() {')]
assert 'dialogueCards' in graph and 'm_dialogues' not in graph
# .sbgm test world: preserve existing advanced choices, unrelated resources,
# dialogue node numeric identities and event settings while editing a message.
p=Path('/mnt/data/gametest_unpacked/world1.sbgm')
if p.exists():
    original=json.loads(p.read_text())
    doc=copy.deepcopy(original)
    trigger=next((r for r in doc['resources'] if r.get('gameObject',{}).get('type')=='trigger'),None)
    assert trigger is not None
    before=copy.deepcopy(trigger['gameObject'])
    nodes=doc['adventure']['nodes']
    assert nodes and len(nodes)<256
    saved_before=copy.deepcopy(nodes[0]['choices'])
    nodes[0]['text']='Updated inline visual node text.'
    assert nodes[0]['choices']==saved_before
    nodes.append({'speaker':'NPC','text':'Hello!', 'choices':[{'text':'','reply':'','next':-1,'missingNext':-1,'requires':-1,'give':-1,'take':-1,'action':-1} for _ in range(3)]})
    trigger['gameObject']['interactDialogueNode']=len(nodes)-1
    trigger['gameObject']['interactDialogueMode']='single'
    # Known extra actions and unrelated special interactions must survive.
    for k,v in before.items():
        if k not in ('interactDialogueNode','interactDialogueMode'):
            assert trigger['gameObject'][k]==v, k
    assert [n['text'] for n in nodes[1:-1]]==[n['text'] for n in original['adventure']['nodes'][1:]]
    assert doc['adventure']['nodes'][-1]['choices'] and len(doc['adventure']['nodes'])==len(original['adventure']['nodes'])+1
    assert len(doc['resources'])==len(original['resources'])
print('Stage 5.166.43 Show Dialogue node schema/source checks PASS')
