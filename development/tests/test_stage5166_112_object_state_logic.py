"""Stage 5.166.112: any stateful world object may host independent logic.

Exercises editor ownership/persistence and exporter state-change dispatch, plus a
native C simulation of arrival -> Toggle Springer -> AND gate -> Toggle target.
"""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
NODE = (ROOT/'gamevisualnodes.cpp').read_text()
EXPORT = (ROOT/'gamedesigner_export.cpp').read_text()
PROJECT = (ROOT/'gamedesigner_project.cpp').read_text()
DESIGNER = (ROOT/'gamedesigner.cpp').read_text()
SPLASH = (ROOT/'splashscreenwidget.cpp').read_text()
RULE = (ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()

class IndependentStateGraph(unittest.TestCase):
    def test_ownership_and_ports(self):
        self.assertIn('return source;\n    }\n    void createGraphLogic', NODE)
        self.assertNotIn('Connect a Trigger action to this Game Object first', NODE)
        self.assertIn('owner=graphOwnerForObject(source);', NODE)
        self.assertIn('tr("AND (all enabled)")', NODE)
        self.assertIn('input={{QStringLiteral("kind"),QStringLiteral("object")}', NODE)
        self.assertIn('createGraphLogic(from,at,selectedId.mid', NODE)

    def test_save_reload_and_display(self):
        self.assertIn('node.logicNodes=data.value(QStringLiteral("logicNodes")).toArray();', NODE)
        self.assertIn('if(trigger.logicNodes.isEmpty())continue;', NODE)
        self.assertIn('if(node.logicNodes.isEmpty())continue;', NODE)
        self.assertIn('object.insert(QStringLiteral("logicNodes"),node.logicNodes);', NODE)
        self.assertIn('const bool hadGraphField=resources.at(node.resourceIndex)', NODE)
        self.assertIn('object.insert(QStringLiteral("logicNodes"), r.logicNodes)', PROJECT)
        self.assertIn('candidate.logicNodes.isEmpty())continue;', DESIGNER)
        self.assertIn('if(!copy.logicNodes.isEmpty())', DESIGNER)
        self.assertIn('if(!dep.logicNodes.isEmpty())', DESIGNER)

    def test_codegen_runs_on_action_source_change(self):
        self.assertIn('if(owner.logicNodes.isEmpty())continue;', EXPORT)
        self.assertIn('else if(owner.objectType==QStringLiteral("lift"))', EXPORT)
        self.assertIn('graphInputs.contains(value.toObject().value(QStringLiteral("objectId")).toString())', EXPORT)
        self.assertIn('hasNamedPlatformLogic=true;', EXPORT)
        self.assertIn('activationEvents.append(QStringLiteral("(cg_named_event_sources[%1u] & %2u)")',EXPORT)
        self.assertIn('if(cg_named_logic_fired)cg_run_trigger_actions();',RULE)
        self.assertIn('@IDE{GRAPH_EVALUATIONS}', RULE)
        self.assertIn('@IDE{GRAPH_DISPATCH}', RULE)

    def test_compatibility_scope(self):
        self.assertIn('Build: 5.166.113.291026', SPLASH)
        self.assertIn('HAS_ENEMY_STATE_LOGIC', EXPORT)
        self.assertIn('if(owner.objectType==QStringLiteral("lift"))continue;',EXPORT)
        self.assertIn('GAME_OBJECT_ENEMY', RULE)
        self.assertIn('GRAPH_INITIAL_SYNC', EXPORT)

    def test_native_springer_gate_per_arrival(self):
        program = r'''
#include <stdint.h>
#include <assert.h>
#include <string.h>
static uint8_t active_spring=0, active_switch=1, active_target=0;
static uint8_t named_event[1];
static int gates_run=0;
static void cg_run_trigger_actions(void) {
    // Event action has already changed Springer's active state.
    // The generator watches the lift's event because it targets a graph input.
    const uint8_t run=(named_event[0] & 32u)!=0u;
    if (run) {
        const uint8_t gate=active_spring && active_switch;
        if(gate) active_target=(uint8_t)!active_target;
        gates_run++;
    }
}
static void after(uint8_t lift_arrival) {
    memset(named_event,0,sizeof(named_event));
    if(lift_arrival) { active_spring=(uint8_t)!active_spring; named_event[0]|=32u; }
    if(named_event[0])cg_run_trigger_actions();
    memset(named_event,0,sizeof(named_event));
    cg_run_trigger_actions(); // Later Trigger cannot replay an arrival event.
}
int main(void) {
    after(0);assert(active_target==0 && gates_run==0);
    after(1);assert(active_spring==1 && active_target==1 && gates_run==1);
    after(1);assert(active_spring==0 && active_target==1 && gates_run==2);
    after(1);assert(active_spring==1 && active_target==0 && gates_run==3);
    active_switch=0;
    after(1);after(1);
    assert(active_target==0 && gates_run==5); // Disabled switch prevents output.
    after(0);assert(gates_run==5);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as d:
            source=Path(d)/'springer.c'; source.write_text(program)
            binary=Path(d)/'springer'
            subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror',str(source),'-o',str(binary)],check=True)
            subprocess.run([str(binary)],check=True)

if __name__ == '__main__': unittest.main()
