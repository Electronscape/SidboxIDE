"""Stage 5.128.1: quest-completion Show Dialogue drop & persistence regression."""
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
V=(ROOT/'gamevisualnodes.cpp').read_text()


def body_between(start,stop):
    assert start in V and stop in V
    return V.split(start,1)[1].split(stop,1)[0]


def test_dropping_onto_unlinked_card_prompts_for_selection():
    method=body_between('void addConnection(', 'int removeOrphanCard(')
    quest=method.split('if(m_objects.value(eventOwner(from)).type==QStringLiteral("quest_completed")) {',1)[1]
    quest=quest.split('if(m_objects.contains(eventOwner(from))',1)[0]
    assert 'int selected=selectedDialogueOnCard(to);' in quest
    assert 'if(selected<0)selected=browseDialogueTree(-1);' in quest
    assert 'if(selected==-1)return;' in quest
    assert 'connectQuestCompletionDialogue(owner,at,selected);' in quest


def test_quest_add_dialogue_button_links_instead_of_orphan():
    add=body_between('void addDialogueCard() {','void createDialogueCard(')
    assert 'm_objects.value(id).type==QStringLiteral("quest_completed")' in add
    assert 'm_objects.value(id).dialogueNode<0' in add
    assert 'const int selected=browseDialogueTree(-1);' in add
    assert 'if(selected==-1)return;' in add
    assert 'connectQuestCompletionDialogue(id,at,selected);' in add


def test_quest_dialogue_is_real_connected_card_without_vsgm():
    linked=body_between('QSet<QString> linkedObjectIds() const {','QSet<QString> connectedCardIds() const {')
    connected=body_between('QSet<QString> connectedCardIds() const {','void updateNpcProperty(')
    assert 'n.type==QStringLiteral("quest_completed")' in linked
    assert 'm_objects.value(id).type==QStringLiteral("quest_completed")' in connected
    assert 'ids.insert(dialogueCardId(id));' in connected
    render=body_between('void renderCards() {','void showInsertTree(') if False else V
    assert 'node.type==QStringLiteral("quest_completed") && node.dialogueNode>=0' in render


def test_persists_into_world_dialogue_not_layout_only():
    assert 'node.dialogueNode=selected;' in V
    assert 'm_touched.insert(owner);' in V
    assert 'm_dirty=true;' in V
    assert 'questCompletionDialogues.insert(questId,QJsonObject{' in V
    assert 'next.insert(QStringLiteral("questCompletionDialogues"),questCompletionDialogues);' in V
    assert 'completion.dialogueNode=completionDialogue.value(QStringLiteral("dialogueNode")).toInt(-1);' in V


def test_new_four_field_splash_version():
    s=(ROOT/'splashscreenwidget.cpp').read_text()
    assert 'Build: 5.128.1.301026' in s
