"""Stage 5.166.120: Quest event actions are real queued, validated targets.

Static/contract checks complement the existing native queue and quest tests.
Requires no Qt SDK, so this file also works in the release build environment.
"""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[2]
GRAPH = (ROOT/'gamevisualnodes.cpp').read_text()
EXPORT = (ROOT/'gamedesigner_export.cpp').read_text()
QUEST = (ROOT/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
SPLASH = (ROOT/'splashscreenwidget.cpp').read_text()

class QuestEventNodes(unittest.TestCase):
    def test_project_quest_objectives_are_authoritative(self):
        self.assertIn('filePath(QStringLiteral(".codergirl/quests.json"))', GRAPH)
        self.assertIn('filePath(QStringLiteral(".codergirl/quests.json"))', EXPORT)
        self.assertIn('step.value(QStringLiteral("kind")).toString()!=QStringLiteral("event")', GRAPH)
        self.assertIn('questEventSignals.contains(id.mid(QStringLiteral("@quest_event:").size()))', EXPORT)
        self.assertIn('missing_reference', GRAPH)

    def test_action_card_and_target_selection(self):
        self.assertIn('node.type=QStringLiteral("quest_event")', GRAPH)
        self.assertIn('tr("QUEST EVENT / SIGNAL")', GRAPH)
        self.assertIn('tr("Quest Events")', GRAPH)
        self.assertIn('isQuestEvent(id)', GRAPH)
        self.assertIn('m_objects.value(target).type==QStringLiteral("quest_event")', GRAPH)
        self.assertIn('if(isPlayerCommand(target) && action!=QStringLiteral("enable"))return;', GRAPH)

    def test_codegen_uses_queued_existing_quest_api(self):
        self.assertIn('gameworlds_quest_event(%1)', EXPORT)
        self.assertIn('GameQuestGen::quoteC(eventId)', EXPORT)
        self.assertIn('if(r.targetAction!=QStringLiteral("enable") || !questEventSignals.contains(eventId))return false;', EXPORT)
        self.assertIn('if(!queueTargetAction(target,&graphDispatchBody))return false;', EXPORT)
        self.assertIn('if(!queueTargetAction(target,&action))return false;', EXPORT)
        self.assertIn('uint8_t gameworlds_quest_event(const char *event_id)', QUEST)
        self.assertIn('gw_quest_step[i]', QUEST)

    def test_initial_load_never_signals(self):
        block = EXPORT.split('graphInitialSyncBody+=QStringLiteral("    /* Independent logic graph',1)[1].split('    if (!usedSfx.isEmpty())',1)[0]
        self.assertIn('targetId.startsWith(QStringLiteral("@quest_event:")))continue;', block)
        self.assertNotIn('gameworlds_quest_event', block)

    def test_all_action_validation_guards_are_enable_only(self):
        for anchor in ['r->targetObjectId', 'link.objectId', 'id']:
            self.assertIn(anchor+'.startsWith(QStringLiteral("@quest_event:"))', EXPORT)
        self.assertIn('Build: 5.166.122.301026', SPLASH)

if __name__ == '__main__':
    unittest.main()
