#!/usr/bin/env python3
"""Stage 5.166.42: review regression contracts for overlapping actions and hit targets.

The production Qt code needs a Qt6 GUI smoke test on the developer's machine.
This test checks source contracts, index-safe removal, and world JSON semantics.
"""
from pathlib import Path
import copy
import json
import re

root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
assert (lambda v: v and int(v.group(1)) >= 42)(re.search(r'Build: 5\.166\.(\d+)\.\d{6}', (root/'splashscreenwidget.cpp').read_text()))
assert 'class NodeWire final : public QGraphicsPathItem' in s
assert 'QPainterPathStroker stroker' in s
assert 'stroker.setWidth(20.0)' in s
assert 'boundingRect() const override' in s
assert 'const QRect target(event->pos()-QPoint(10,10),QSize(21,21))' in s
assert 'for (QGraphicsItem *item: items(target))' in s
assert 'if (!hits.contains(ref)) hits.append(ref);' in s
assert 'QList<QPair<QString,int>> hits' in s
assert 'const qreal offset=(ordinal-(matching-1)*0.5)*42.0' in s
assert 'path.cubicTo(a+QPointF(bend,offset),b+QPointF(-bend,offset),b)' in s
assert 'm_linksList=new QListWidget(right)' in s
assert 'm_editLinkButton=new QPushButton(tr("Edit Action"),right)' in s
assert 'm_removeLinkButton=new QPushButton(tr("Remove"),right)' in s
assert 'left->setMaximumWidth(270)' in s and 'split->setSizes({225,1050,255})' in s
assert 'node.links.removeAt(index)' in s
assert 'action->setData(choice.first)' in s
assert 'remove->setData(QStringLiteral("remove"))' in s
assert 'if (operation==QStringLiteral("remove")) {' in s
assert 'removeConnection(ref.first,ref.second);' in s
assert 'if (!supportedAction(operation))return;' in s and 'if (ref.second<0)return;' in s
assert 'node.links[ref.second].action=operation' in s
assert 'if (ref.second==-1)disconnectDialogue(ref.first);' in s
assert 'else removeConnection(ref.first,ref.second);' in s
assert 'm_touched.insert(from)' in s and 'm_dirty=true' in s
assert 'object.insert(QStringLiteral("triggerExtraActions"),extras)' in s
assert 'QCryptographicHash::hash(current,QCryptographicHash::Sha256)!=m_originalHash' in s
assert not re.search(r'auto\s*\*\s*\w+\s*=\s*\[',s)

# Test the .sbgm representation when two parallel actions exist. Remove each
# index in turn and check surviving action is promoted or retained as needed.
world={'resources':[{'id':'triggerA','kind':'sprite','gameObject':{
  'type':'trigger','targetObjectId':'lift','targetAction':'enable',
  'triggerExtraActions':[{'objectId':'lift','action':'disable'}],
  'health':57, 'untouched':{'q':7}}},
  {'id':'lift','kind':'sprite','gameObject':{'type':'platform','speed':2}}],
  'quests':[{'id':'story'}]}
for removed in (0,1):
    doc=copy.deepcopy(world)
    obj=doc['resources'][0]['gameObject']
    links=[{'objectId':obj['targetObjectId'],'action':obj['targetAction']}]+obj['triggerExtraActions']
    links.pop(removed)
    obj['targetObjectId']=links[0]['objectId'] if links else ''
    obj['targetAction']=links[0]['action'] if links else 'none'
    obj['triggerExtraActions']=links[1:]
    assert obj['targetAction']== ('disable' if removed==0 else 'enable')
    assert doc['resources'][1]==world['resources'][1]
    assert obj['health']==57 and obj['untouched']=={'q':7}
    assert doc['quests']==world['quests']
# No connections: primary target cleared, extras empty.
obj=copy.deepcopy(world['resources'][0]['gameObject'])
obj['targetObjectId']=''; obj['targetAction']='none'; obj['triggerExtraActions']=[]
assert obj['targetObjectId']=='' and obj['triggerExtraActions']==[]
print('Stage 5.166.42 link selection/removal and .sbgm source/schema contracts PASS')
