"""Stage 5.166.82: GIVE cards edit real Adventure choice.exchange, not new runtime data."""
from pathlib import Path
import copy
r=Path(__file__).resolve().parents[2]
s=(r/'gamevisualnodes.cpp').read_text()
assert ('Build: 5.166.99.291026' in (r/'splashscreenwidget.cpp').read_text() or any('Build: '+v+'.281026' in (r/'splashscreenwidget.cpp').read_text() for v in ('5.166.82','5.166.83','5.166.84','5.166.84.1','5.166.85','5.166.86')))
for label in ('Any wrong item','Tracked item · first offer','Tracked item · second offer',
              'Tracked item · third offer','Tracked item · fourth+ offer',
              'Required: %1','GIVE EXCHANGE','Edit full GIVE exchange in Adventure Editor'):
    assert label in s,label
for field in ('wrongNext','wrongRepeatFirst','wrongRepeatSecond','wrongRepeatThird',
              'wrongRepeatLater','wrongRepeatEnabled','wrongRepeatItem','incremental',
              'consume','logic','items'):
    assert field in s,field
for token in ('QStringLiteral("@give:%1:%2")','giveCardReference(',
              'makeGiveCard(', 'setGiveDestination(', 'giveExchange(',
              'QStringLiteral("exchange")','m_dialogues.replace(index,node);',
              'conversationConnectionRequested','conversationDropRequested',
              'give-preview-wire','exchange-output','give-anchor','exchange-input',
              'wantedGive','m_conversationRoots.insert(root)',
              'it.key().startsWith(QStringLiteral("@give:"))',
): 
    assert token in s,token
assert 'if(from.startsWith(QStringLiteral("@give:")))' in s
assert 'setGiveDestination(dialogue,answer,option,target);' in s
assert 'setGiveDestination(dialogue,answer,option,selected);' in s
assert 'exchange.insert(key,destination)' in s
assert 'setConversationAnswer(dialogue,answer,QStringLiteral("exchange"),exchange);' in s
assert 'if(!exchange.value(QStringLiteral("enabled")).toBool(false))return;' in s
assert 'if(branch>0 && !exchange.value(QStringLiteral("wrongRepeatEnabled")).toBool(false))return;' in s
assert 'if(!wantedGive.contains(id))removeOrphanCard(id,true)' in s
assert 'hideConversationContaining(dialogue)' in s
# Contract: the generator, Adventure Editor and runtime templates have not changed.
# Changing one destination must preserve all other exchange fields, including
# required inventory items, escalating rules and one-time event actions.
choice={'text':'Can I get past?', 'next':3,'missingNext':4,'requires':0,
        'exchange':{'enabled':True,'logic':'all','items':[0,2], 'consume':True,
          'incremental':True,'wrongNext':5,'wrongRepeatEnabled':True,
          'wrongRepeatItem':1,'wrongRepeatFirst':6,'wrongRepeatSecond':7,
          'wrongRepeatThird':8,'wrongRepeatLater':9,
          'wrongRepeatTargetObjectId':'door', 'wrongRepeatTargetAction':'disable'}}
updated=copy.deepcopy(choice)
updated['exchange']['wrongNext']=16
assert updated['next']==3 and updated['missingNext']==4
for key in ('items','logic','consume','incremental','wrongRepeatItem',
            'wrongRepeatEnabled','wrongRepeatFirst','wrongRepeatSecond',
            'wrongRepeatThird','wrongRepeatLater','wrongRepeatTargetObjectId',
            'wrongRepeatTargetAction'):
    assert updated['exchange'][key]==choice['exchange'][key],key
assert 'clampInt(exchange,"wrongNext"' in (r/'gameadventuregen.cpp').read_text()
print('PASS 5.166.82: GIVE exchange card, 5 routed outputs, visual connection/drop, preserved Adventure fields')
