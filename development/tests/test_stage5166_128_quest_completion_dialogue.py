"""Stage128 editor/export contract: quest completion can run Adventure dialogue."""
from pathlib import Path
import re
ROOT=Path(__file__).resolve().parents[2]
V=(ROOT/'gamevisualnodes.cpp').read_text()
E=(ROOT/'gamedesigner_export.cpp').read_text()
RULE=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()

def test_picker_offers_existing_and_new_dialogue_directly():
    assert '(!eventOutputPort || eventLogicSource || questCompletionSource)' in V
    assert 'if(questCompletionSource) {\n                connectQuestCompletionDialogue(eventOwner(from),at,-2);' in V
    assert 'connectQuestCompletionDialogue(eventOwner(from),at,index)' in V
    assert 'void connectQuestCompletionDialogue(' in V
    assert 'if(to.startsWith(QStringLiteral("@graph:")))return;' in V

def test_quest_dialogue_uses_existing_editable_card():
    assert 'node.type==QStringLiteral("quest_completed") && node.dialogueNode>=0' in V
    assert 'm_dialogueCards.contains(id)' in V
    assert 'm_cards.value(dialogueCardId(id)' in V
    assert 'QStringLiteral("dialogue-link")' in V
    assert 'Quest ON COMPLETED → Show Dialogue' in V
    assert 'node.type!=QStringLiteral("quest_completed"' in V  # dialogue disconnect supported

def test_roundtrip_preserves_actual_sbgm_actions_and_dialogue():
    assert 'completionDialogue=m_world.value(QStringLiteral("questCompletionDialogues"))' in V
    assert 'completion.dialogueNode=completionDialogue.value(QStringLiteral("dialogueNode"))' in V
    assert 'next.insert(QStringLiteral("questCompletionActions"),questCompletionActions);' in V
    assert 'next.insert(QStringLiteral("questCompletionDialogues"),questCompletionDialogues);' in V
    assert 'if(node.dialogueNode>=m_dialogues.size())' in V
    # The quest dialogue is a reference, never an extra Adventure dialogue copy.
    assert '{QStringLiteral("dialogueNode"),node.dialogueNode}' in V

def test_export_validates_and_fifo_queues_dialogues():
    assert 'questCompleteKeys.insert(it.key())' in E
    assert 'if(!questCompletedIds.contains(questId))' in E
    assert 'number<0 || number>=questDialogueCount' in E
    assert 'game_adventure_trigger_%1(%2u);' in E
    assert re.search(r'&interactionDialogueActions,\s*&questCompleteActions\}',E)
    assert 'game_adventure_trigger_(message|dialogue|sequence)' in E
    assert 'cg_action_enqueue(%1u)' in E
    assert '@IDE{QUEST_COMPLETE_ACTIONS}' in RULE

def test_no_ghost_dialogue_on_empty_world_or_load():
    assert 'Quest completion dialogue in an empty world requires at least one managed Game Object' in E
    assert 'quest_completed(const char *quest_id)' in RULE
    assert 'gw_quest_notice_ready=0u' in (ROOT/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
    assert 'if(!applying && active_world && active_world->quest_completed)' in (ROOT/'idelibs/codehelpers/game/gameworlds.rulec').read_text()

def test_old_main_and_runtime_unmodified():
    assert 'player_anim_step(&player_anim' in (ROOT/'idelibs/codehelpers/game/maingame.rulec').read_text()
    assert 'Build: 5.128.1.301026' in (ROOT/'splashscreenwidget.cpp').read_text()
