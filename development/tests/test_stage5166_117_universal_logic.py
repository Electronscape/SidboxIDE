"""Source-integrity contract for universal event and state logic, Stage 5.166.117.
Qt GUI compilation and real hardware testing remain separate acceptance steps.
"""
import re
import unittest
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
UI = (ROOT/'gamevisualnodes.cpp').read_text()
LOGIC = (ROOT/'gamevisualgraphlogic.h').read_text()
EXPORT = (ROOT/'gamedesigner_export.cpp').read_text()
PROPS = (ROOT/'gamedesigner.cpp').read_text()
RUNTIME = (ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()

class UniversalLogicContract(unittest.TestCase):
    def test_named_sources_cover_all_existing_game_object_events(self):
        for key in ('hit', 'destroy', 'pickup', 'player_hit', 'enter', 'save', 'arrival'):
            self.assertIn(f'QStringLiteral("{key}")', LOGIC)
            self.assertIn(f'QStringLiteral("{key}")', EXPORT)
            self.assertIn(f'QStringLiteral("{key}")', UI)
        for key in ('defeat', 'trigger'):
            self.assertIn(f'QStringLiteral("{key}")', LOGIC)
            self.assertIn(f'QStringLiteral("{key}")', EXPORT)

    def test_nodes_have_normalized_event_to_gate_paths(self):
        self.assertIn('const bool eventLogicSource=eventOutputPort || enemyOutput || triggerLogicSource;', UI)
        self.assertIn('eventKinds(m_objects.value(eventOwner(source)).type).contains(eventKey(source))', UI)
        self.assertIn('eventOutput(QStringLiteral("defeat"),owner)', UI)
        self.assertIn('eventOutput(QStringLiteral("trigger"),owner)', UI)
        self.assertIn('source==owner && m_objects.value(owner).type==QStringLiteral("trigger")', UI)

    def test_save_load_validator_recognizes_real_event_source(self):
        self.assertIn('locals.insert(eventOutput(kind,id));', UI)
        self.assertIn('ref.value(QStringLiteral("id")).toString().section(QLatin1Char(\':\'),2)==id', UI)
        self.assertIn('SidboxVisualLogic::order(parsed,locals,&schedule,&issue)', UI)
        self.assertIn('sourceId=input.id.section(QLatin1Char(\':\'),2)', LOGIC)

    def test_live_event_source_kept_even_without_action_wire(self):
        self.assertIn('if(action.isEmpty() && !neededForLogic)continue;', EXPORT)
        self.assertIn('if(!action.isEmpty() || pickupGraph)', EXPORT)
        self.assertIn('SAVE_PICKUP_ACTIVE', EXPORT)
        self.assertIn('cg_named_pickup_sources[%1u]=1u;', EXPORT)
        self.assertIn('cg_named_event_sources[%1u]|=8u;', EXPORT)

    def test_no_replay_of_event_based_false_action_or_on_save_load(self):
        self.assertIn('if(nodePulseGate.contains(node.id))', EXPORT)
        self.assertIn('if(nodeDependsOnPulse.value(node.id))continue;', EXPORT)
        self.assertIn('if(action==QStringLiteral("toggle")', EXPORT)
        self.assertIn('cg_named_event_sources,0', RUNTIME)

    def test_pickup_graph_receives_generated_callbacks(self):
        self.assertIn('ownerIndex<nw+np', EXPORT)
        self.assertIn('const bool pickupOwner=ownerIndex>=nw;', EXPORT)
        self.assertIn('activationEvents.append(QStringLiteral("cg_named_pickup_sources[%1u]")', EXPORT)
        self.assertIn('if(!r.logicNodes.isEmpty())pickupGraph=true;', EXPORT)

    def test_properties_doesnt_strip_new_inputs_or_invert(self):
        for k in ('defeat', 'trigger', 'pickup', 'save', 'enter', 'player_hit'):
            self.assertIn('QStringLiteral("'+k+'")', PROPS)
        self.assertIn('inputs.append(oldInput)', PROPS)
        self.assertIn('checked.removeAt(i)', PROPS)
        self.assertIn('node.insert(QStringLiteral("inputs"),inputs)', PROPS)

    def test_visual_numbered_sockets_and_real_input_limits(self):
        self.assertIn('syncGraphCardSockets(key)', UI)
        self.assertIn('INPUT %1: %2', UI)
        self.assertIn('rawInputs.size()>8', LOGIC)
        self.assertIn('rawInputs.size()>16', LOGIC)
        self.assertIn('nodePulseGate', EXPORT)

    def test_save_schema_and_version(self):
        self.assertIn('Build: 5.166.117.301026', (ROOT/'splashscreenwidget.cpp').read_text())
        self.assertTrue((ROOT/'idelibs/codehelpers/game/gameworlds.rulec').exists())

if __name__=='__main__': unittest.main()
