"""Stage 5.166.92: direct GIVE exchange editing, no Adventure window handoff.
Source/data contracts only; Qt mouse interactions require the user's desktop.
"""
from pathlib import Path
import json, tarfile
r=Path(__file__).resolve().parents[2]
v=(r/'gamevisualnodes.cpp').read_text()
a=(r/'gameadventureeditor.cpp').read_text()
h=(r/'gameadventureeditor.h').read_text()
assert 'Build: 5.166.99.291026' in (r/'splashscreenwidget.cpp').read_text()
assert '#include "gameadventureeditor.h"' in v
assert 'bool editGameAdventureGiveExchange(QWidget *parent, QJsonObject *exchange,' in h
assert 'bool editGameAdventureGiveExchange(QWidget *parent, QJsonObject *exchange,' in a
assert 'const QJsonObject result = editExchange(parent, *exchange, items, nodes,' in a
assert 'if (accepted) *exchange = result;' in a
assert 'if (accepted) *accepted = false;' in a
assert 'if (accepted) *accepted = true;' in a
assert 'if(dlg.exec()!=QDialog::Accepted) return saved;' in a
body=v[v.index('void editGiveExchangeInPlace('):v.index('void openConversationInAdventure(',v.index('void editGiveExchangeInPlace('))]
assert 'editGameAdventureGiveExchange(this,&exchange,items,m_dialogues,' in body
assert 'm_dialogueFolders' in body
assert 'm_world.value(QStringLiteral("resources"))' in body
assert 'updatedChoice.insert(QStringLiteral("exchange"),exchange);' in body
assert 'm_dialogues.replace(dialogue,updatedNode);' in body
assert 'm_dialoguesChanged=true;' in body
assert 'QTimer::singleShot(0,this,' in body  # avoid deleting clicked QWidget synchronously
assert 'removeOrphanCard(id,true)' in body
assert 'rebuildConversationFlow();' in body
assert 'redrawLinks();' in body
assert 'if(!saveAll())return;' in body
assert 'done(3)' not in body  # dialogue handoff is separate, GIVE editor stays in graph
assert 'openConversationInAdventure(' not in body
assert 'connect(advanced,&QPushButton::clicked,this,[this,dialogue,option]' in v
assert 'editGiveExchangeInPlace(dialogue,option);' in v
assert 'if(chosen==advanced)editGiveExchangeInPlace(dialogue,answer);' in v
assert 'bool saveAll()' in v and 'adventure.insert(QStringLiteral("nodes"),m_dialogues);' in v
# The existing save writer must preserve all other .sbgm Adventure contents.
assert 'QJsonObject adventure=next.value(QStringLiteral("adventure")).toObject();' in v
# The game exporter / runtime generation are unchanged from the previous stage.
print('PASS 5.166.92: direct GIVE exchange editor, Cancel guard, in-place card and .sbgm update')
