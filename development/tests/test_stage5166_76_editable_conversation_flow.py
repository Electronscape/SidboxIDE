"""Stage 5.166.76 editable conversation nodes + Adventure deep-link source-contract tests.
This is not a Qt graphical/desktop build.
"""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
ui=(r/'gamevisualnodes.cpp').read_text()
header=(r/'gamevisualnodes.h').read_text()
world=(r/'gamedesigner.cpp').read_text()
world_h=(r/'gamedesigner.h').read_text()
adv=(r/'gameadventureeditor.cpp').read_text()
adv_h=(r/'gameadventureeditor.h').read_text()
version=(r/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in version
assert 'void setConversationField(' in ui
assert 'void setConversationAnswer(' in ui
assert 'void openConversationInAdventure(' in ui
assert 'void makeConversationCard(' in ui
assert 'QLineEdit(node.value(QStringLiteral("speaker"))' in ui
assert 'QPlainTextEdit(node.value(QStringLiteral("text"))' in ui
assert 'answer.value(QStringLiteral("text"))' in ui
assert 'answer.value(QStringLiteral("next")).toInt(-1)' in ui
assert 'while(choices.size()<3)choices.append(QJsonObject())' in ui
assert 'choices.replace(option,answer)' in ui
assert 'm_dialogues.replace(index,node)' in ui
assert 'm_dialoguesChanged=true' in ui
assert 'QTimer::singleShot(0,this' in ui
assert 'rebuildConversationFlow();' in ui
assert 'Open this dialogue in Adventure Editor...' in ui
assert 'if(m_dirty && !saveAll())return;' in ui
assert 'done(3);' in ui
assert 'int *openAdventureDialogue = nullptr' in header
assert 'dialog.requestedAdventureDialogue()' in ui
assert 'openAdventureEditor(QString(),openDialogue,true);' in world
assert 'int focusDialogueIndex = -1' in world_h
assert 'int focusDialogueIndex = -1' in adv_h
assert 'redrawNodes(focusDialogueIndex)' in adv
assert 'tabs->setCurrentWidget(dialoguePage);' in adv
assert 'QStringLiteral("conversation-output")' in ui
assert 'proxy->subWidgetRect(edit)' in ui  # ports align after Qt widget embedding
# Core Adventure format remains canonical, and editing does not replace choices or add new IDs.
fn=ui[ui.index('void setConversationAnswer('):ui.index('void openConversationInAdventure(')]
for key in ('choices','next','text'):
 assert key in ui
assert 'QJsonObject node=m_dialogues.at(index).toObject();' in fn
assert 'node.insert(QStringLiteral("choices"),choices);' in fn
assert 'm_dialogues.append' not in fn
assert 'm_dialogues.remove' not in fn
layout=ui[ui.index('QJsonObject graphJson() const'):ui.index('bool saveLayout()')]
assert 'root.insert(QStringLiteral("nodes")' not in layout
assert 'root.insert(QStringLiteral("choices")' not in layout
print('PASS editable conversation nodes, canonical .sbgm save, safe Adventure Editor handoff')
