#!/usr/bin/env python3
"""Source-contract checks for Stage 121's editor, generated paths and persistence."""
import unittest
from pathlib import Path
R=Path(__file__).resolve().parents[2]
def s(name):return (R/name).read_text()
class Quest121(unittest.TestCase):
    def test_quest_designer_choice_defaults_ordered(self):
        ui=s('gamequesteditor.cpp')
        self.assertIn('Allow objectives in ANY ORDER',ui)
        self.assertIn('q["unordered"]=unordered->isChecked()',ui)
        self.assertIn('q["unordered"]=false',ui)
        self.assertIn('q.value("unordered").toBool(false)',ui)
    def test_generated_definition_contains_flag(self):
        gen=s('gamequestgen.h')
        self.assertIn('initially_hidden,unordered;',gen)
        self.assertIn('q.value("unordered").toBool(false)',gen)
        self.assertIn('{0,0,0,0,0,0,0,0,0}',gen)
    def test_c_runtime_preserves_ordered_events_and_bitset(self):
        c=s('idelibs/codehelpers/game/gameworlds.rulec')
        self.assertIn('gw_quest_done[(256u+7u)/8u]',c)
        self.assertIn('if(!q->unordered)break; /* one ordered event per dispatch */',c)
        self.assertIn('if(gw_quest_is_done(index))return 0u;',c)
        self.assertIn('active_world->quest_completed(q->id)',c)
        self.assertIn('if(!applying && active_world && active_world->quest_completed)',c)
    def test_v4_loads_previous_v3_and_checks_bitcounts(self):
        c=s('idelibs/codehelpers/game/gameworlds.rulec')
        self.assertIn('#define GW_SAVE_VERSION 4u',c)
        self.assertIn('temp.version!=3u && temp.version!=GW_SAVE_VERSION',c)
        self.assertIn('sizeof(questData)-sizeof(questData.done)',c)
        self.assertIn('if(bits!=questData.step[i])return 0;',c)
        self.assertIn('gw_quest_notice_ready=0u',c)
    def test_visual_quest_completed_source_real_sbgm(self):
        v=s('gamevisualnodes.cpp')
        self.assertIn('QStringLiteral("@quest_complete:")+questId',v)
        self.assertIn('QStringLiteral("quest_completed")',v)
        self.assertIn('QStringLiteral("questCompletionActions")',v)
        self.assertIn('node.type==QStringLiteral("quest_completed")',v)
        self.assertIn('eventLinks[QStringLiteral("complete")]',v)
        self.assertIn('return QStringLiteral("ON COMPLETED");',v)
        self.assertIn('if(!linking) {\n            QTreeWidgetItem *completedRoot',v)
    def test_exporter_queued_actions_and_registry(self):
        exporter=s('gamedesigner_export.cpp')
        manager=s('gameworldsnapshot.h')
        template=s('idelibs/codehelpers/game/gameworlditems.rulec')
        self.assertIn('QUEST_COMPLETE_ACTIONS',exporter)
        self.assertIn('if(!queueTargetAction(action,&commands))return false;',exporter)
        self.assertIn('questCompleteActions+=QStringLiteral',exporter)
        self.assertIn('gameworlditems_quest_completed',manager)
        self.assertIn('gameworlditems_quest_completed',template)
        self.assertIn('@IDE{QUEST_COMPLETE_ACTIONS}',template)
        self.assertIn('gameworlditems_quest_completed(const char *quest_id) { (void)quest_id; }',template)
    def test_release_stage(self):
        self.assertRegex(s('splashscreenwidget.cpp'),r'Build: 5\.\d+\.\d+\.\d{6}')
if __name__=='__main__':unittest.main()
