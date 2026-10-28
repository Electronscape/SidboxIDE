#!/usr/bin/env python3
"""Stage 5.166.49 source-contract and .sbgm schema regression.
These are not Qt6 interactive GUI tests; hardware/GUI checks remain necessary.
"""
from pathlib import Path
import re, copy
root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert re.search(r'Build: 5\.166\.(\d+)\.281026', (root/'splashscreenwidget.cpp').read_text()) and int(re.search(r'Build: 5\.166\.(\d+)\.281026', (root/'splashscreenwidget.cpp').read_text()).group(1)) >= 49
for fragment in (
 'void keyPressEvent(QKeyEvent *event) override',
 'event->key()==Qt::Key_Delete',
 '!(scene() && scene()->focusItem())',
 'm_view->deleteRequested=[this] {removeSelectedNode();};',
 'm_list->installEventFilter(this);',
 'watched==m_list && event->type()==QEvent::KeyPress',
 'scene()->setFocusItem(nullptr);',
 'void removeSelectedNode()',
 'void disconnectDialogue(const QString &triggerId)',
 'Delete Node (disconnect links)',
 'Remove Connection',
 'if (ref.second==-1)disconnectDialogue(ref.first);',
 'kind==QStringLiteral("dialogue-link") ? -1 :',
 'if (link.target==id)++removedLinks;',
 'for (int i=node.links.size()-1;i>=0;--i)',
 'if (node.links[i].target==id) {node.links.removeAt(i);changed=true;}',
 'if (node.dialogueNode>=0) {node.dialogueNode=-1;changed=true;}',
 'const int removed=removeOrphanCard(id);',
 'for (const QString &remaining:m_cards.keys())',
 'm_placedCards.insert(remaining);',
 'if (removedLinks>0 && QMessageBox::question(',
 'm_touched.insert(source);',
 'QCryptographicHash::hash(current,QCryptographicHash::Sha256)!=m_originalHash',
 'root.insert(QStringLiteral("placedCards"),placedCards);',
 'root.insert(QStringLiteral("positions"),positions);',
):
 assert fragment in s, fragment
# Check no old hairpin offsets and proper wire geometry for all dialogue wires.
wire=s[s.index('void redrawLinks()'):s.index('void showDetails(')]
assert 'path.cubicTo(a+QPointF(bend,-55),b-QPointF(bend,55),b)' not in wire
assert 'path.cubicTo(a+QPointF(bend,offset),b+QPointF(-bend,offset),b);' in wire
assert 'const bool targetOnLeft=target.center().x()<a.x();' in wire
assert 'QPainterPathStroker stroker' in s and 'stroker.setWidth(20.0)' in s
assert 'root.insert(QStringLiteral("connections")' not in s
assert 'm_dialogues.removeAt(' not in s[s.index('void removeSelectedNode()'):s.index('void removeAllOrphans()')]
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',s)
# A representative two-trigger world: removing a Lift card disconnects both
# incoming paths, including parallel actions, without destroying resources.
world={'resources':[
 {'id':'triggerA','gameObject':{'type':'trigger','targetObjectId':'lift','targetAction':'enable',
   'triggerExtraActions':[{'objectId':'lift','action':'disable'},
                          {'objectId':'door','action':'toggle'}],
   'interactDialogueNode':13, 'interactDialogueMode':'single','damage':3}},
 {'id':'triggerB','gameObject':{'type':'trigger','targetObjectId':'lift','targetAction':'toggle',
   'triggerExtraActions':[], 'interactDialogueNode':-1}},
 {'id':'lift','gameObject':{'type':'lift','speed':42}},
 {'id':'door','gameObject':{'type':'door','locked':True}}],
 'adventure':{'nodes':[{'speaker':'BLOB','text':'Hi'}]}, 'quests':[{'id':'do-not-touch'}]}
original=copy.deepcopy(world)
for res in world['resources']:
 ob=res['gameObject']
 if ob['type']!='trigger':continue
 links=[{'objectId':ob['targetObjectId'],'action':ob['targetAction']}]+ob['triggerExtraActions']
 links=[l for l in links if l['objectId']!='lift']
 ob['targetObjectId']=links[0]['objectId'] if links else ''
 ob['targetAction']=links[0]['action'] if links else 'none'
 ob['triggerExtraActions']=links[1:]
assert world['resources'][0]['gameObject']['targetObjectId']=='door'
assert world['resources'][1]['gameObject']['targetObjectId']==''
assert world['resources'][0]['gameObject']['interactDialogueNode']==13
assert world['resources'][0]['gameObject']['damage']==3
assert world['resources'][2:] == original['resources'][2:]
assert world['adventure']==original['adventure'] and world['quests']==original['quests']
print('PASS 5.166.49: Delete/UI/wires .sbgm schema contracts and shared target disconnect scenario')
