"""Stage 5.166.111: existing Toggle + lift ON ARRIVAL one-frame Boolean graph."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[2]
NODE=(ROOT/'gamevisualnodes.cpp').read_text()
GRAPH=(ROOT/'gamevisualgraphlogic.h').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
WORLD=(ROOT/'gamedesigner_project.cpp').read_text()
DESIGNER=(ROOT/'gamedesigner.cpp').read_text()
RULE=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()

class ArrivalLogic(unittest.TestCase):
    def test_existing_toggle_not_a_new_node(self):
        self.assertIn('action == QStringLiteral("toggle")',NODE)
        self.assertIn('@IDE_SECTION{TARGET_ACTION}',RULE)
        self.assertIn('@IDE_IF{TARGET_TOGGLE}',RULE)
        self.assertIn('active = (uint8_t)!',RULE)
        self.assertNotIn('QStringLiteral("flipflop")',NODE)

    def test_drag_from_event_creates_existing_logic_node(self):
        self.assertIn('const bool arrivalLogicSource=eventOutputPort',NODE)
        self.assertIn('createGraphLogic(from,at,selectedId.mid',NODE)
        self.assertIn('isEventOutput(source) && eventKey(source)==QStringLiteral("arrival")',NODE)
        self.assertIn('if(to.startsWith(QStringLiteral("@graph:")) && eventKey(from)==QStringLiteral("arrival"))',NODE)
        self.assertIn('QStringLiteral("kind"),QStringLiteral("event")',NODE)
        self.assertIn('kind==QStringLiteral("event")?88:58',NODE)

    def test_graph_expression_uses_one_frame_pulse_not_active_state(self):
        self.assertIn('in.kind!=QStringLiteral("event")',GRAPH)
        self.assertIn('input.kind==QStringLiteral("event") ? objects.value(input.id)',GRAPH)
        self.assertIn('QStringLiteral("@event:arrival:")+platforms.at(i)->id',EXPORT)
        self.assertIn('QStringLiteral("(cg_named_event_sources[%1u] & 32u)")',EXPORT)
        self.assertIn('owner.objectType==QStringLiteral("lift")',EXPORT)
        self.assertIn('owner.objectType!=QStringLiteral("lift")',EXPORT)
        self.assertIn('if(owner.objectType==QStringLiteral("lift"))continue;',EXPORT)
        self.assertIn('memset(cg_named_event_sources,0,sizeof(cg_named_event_sources));',RULE)
        self.assertIn('if(cg_named_logic_fired)cg_run_trigger_actions();',RULE)

    def test_save_load_properties_and_export_are_all_consistent(self):
        self.assertIn('type==QStringLiteral("enemy") || type==QStringLiteral("lift")',NODE)
        self.assertIn('if(node.type==QStringLiteral("lift"))',NODE)
        self.assertIn('object.insert(QStringLiteral("logicNodes"),node.logicNodes)',NODE)
        self.assertIn('r.objectType==QStringLiteral("lift"))',WORLD)
        self.assertIn('candidate.objectType!=QStringLiteral("lift")',DESIGNER)
        self.assertIn('tr("ON ARRIVAL pulse: %1")',DESIGNER)
        self.assertIn('input.id!=QStringLiteral("@event:arrival:")+r->id',EXPORT)
        self.assertIn('input.id!=QStringLiteral("@event:arrival:")+owner.id',EXPORT)
        self.assertIn('QStringLiteral("@event:arrival:")+s_copiedWorldObject.id',DESIGNER)
        self.assertIn('Build: 5.166.113.291026',(ROOT/'splashscreenwidget.cpp').read_text())

    def test_native_pulse_and_condition_toggle_only_on_arrivals(self):
        program=r'''
#include <stdint.h>
#include <string.h>
#include <assert.h>
typedef struct { uint8_t active, arrival_triggered; } Object;
static Object o[3]; /* lift, switch, target */
static uint8_t events[3];
static int trigger_count;
static void graph_run(void) {
    /* Generated event input expression: (cg_named_event_sources[0] & 32u) */
    if (!(events[0] & 32u)) return;
    trigger_count++;
    if ((events[0] & 32u) && o[1].active) o[2].active=(uint8_t)!o[2].active;
}
static void after(void) {
    memset(events,0,sizeof(events));
    if(o[0].arrival_triggered)events[0]|=32u;
    if(events[0])graph_run();
    memset(events,0,sizeof(events));
    graph_run(); /* Later Trigger in the same frame cannot repeat the action. */
    o[0].arrival_triggered=0;
}
int main(void) {
    o[0].active=1;
    o[1].active=0;
    after();assert(!o[2].active && !trigger_count); /* Loading does not fire. */
    o[0].arrival_triggered=1;after();assert(!o[2].active && trigger_count==1);
    o[1].active=1;
    after();assert(!o[2].active && trigger_count==1); /* Switch alone not an arrival. */
    o[0].arrival_triggered=1;after();assert(o[2].active && trigger_count==2);
    o[0].arrival_triggered=1;after();assert(!o[2].active && trigger_count==3);
    after();assert(!o[2].active && trigger_count==3);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as d:
            src=Path(d)/'arrival.c'; exe=Path(d)/'arrival'
            src.write_text(program)
            subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
            subprocess.run([str(exe)],check=True)

if __name__=='__main__':unittest.main()
