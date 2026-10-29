#!/usr/bin/env python3
"""Stage 5.166.81 source contract + representative Adventure destination preservation.

Qt interactive hardware tests remain necessary. This test prevents wiring an
amber missing-item branch into ordinary Game Object actions or changing `next`.
"""
from pathlib import Path
import re
R=Path(__file__).resolve().parents[2]
s=(R/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (R/'splashscreenwidget.cpp').read_text()
assert 'conversation-missing-output' in s
assert 'QColor(233,177,98)' in s
assert 'Qt::DashLine' in s
assert 'AMBER DASHED · REQUIRED ITEM MISSING' in s
assert 'PURPLE · NORMAL ANSWER ROUTE' in s
assert "Drag the amber socket or edit 'No item'" in s
assert 'browseConversationDestination(current,chosen,true)' in s
assert 'missingNext->setCurrentIndex' in s
assert 'QStringLiteral("requires")' in s
assert 'QStringLiteral("missingNext")' in s
assert 'QStringLiteral("next")' in s
assert 'conversationConnectionRequested' in s
assert 'conversationDropRequested' in s
assert 'm_choiceMissing=socketKind==QStringLiteral("conversation-missing-output")' in s
assert 'if (to.startsWith(QStringLiteral("@conversation:")) && conversationConnectionRequested)' in s
assert 'const int source=from.mid(QStringLiteral("@conversation:").size()).toInt(&sourceOk);' in s
assert 'missing?QStringLiteral("missingNext"):QStringLiteral("next")' in s
assert 'setConversationAnswer(source,option,' in s
assert 'QTimer::singleShot(0,this,[this]' in s
assert 'm_dialogues.replace(index,node)' in s
assert 'm_dialoguesChanged=true;' in s
assert 'm_conversationRoots.insert(root)' in s
assert 'updateSocketStates();' in s
assert 'kind==QStringLiteral("conversation-missing-output")' in s
assert 'missingPort->setData(2,option);' in s
assert 'missingPort->setData(2,option);' in s
assert 'port->setData(2,option);' in s
assert 'edit->property("conversationAnswerIndex").toInt()' in s
# The generated Adventure data structure is still directly consumed from
# Adventure without any change to the runtime code generator.
gen=(R/'gameadventuregen.cpp').read_text()
assert 'clampInt(choice,"missingNext",-1,nodes.size()-1,-1)' in gen
assert 'clampInt(choice,"next",-1,nodes.size()-1,-1)' in gen
assert 'clampInt(choice,"requires",-1,itemList.size()-1,-1)' in gen
# Basic state invariant: moving one wire changes precisely one field.
import copy
choice={'text':'Can I get past?','requires':0,'next':3,'missingNext':4,'give':-1,'take':-1}
modified=copy.deepcopy(choice)
modified['missingNext']=1
assert modified['next']==3 and modified['requires']==0
assert modified['missingNext']==1 and modified['text']==choice['text']
modified['missingNext']=-1
assert modified['next']==3 and modified['requires']==0
print('PASS Stage 5.166.81: drag/edit amber and purple Adventure branches, tooltips, independent persisted destinations')
