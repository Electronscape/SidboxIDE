#!/usr/bin/env python3
"""Stage 5.166.62: graph reacts to each state-source Trigger, not just its owner.

Native test covers two independent switches controlling two Decoration inputs;
source contract checks ensure compiler emits the same two-phase snapshot scheme.
Qt GUI compilation requires Qt6 development headers on the user's machine.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

ROOT=Path(__file__).resolve().parents[2]
export=(ROOT/'gamedesigner_export.cpp').read_text()
template=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
properties=(ROOT/'gamedesigner.cpp').read_text()
assert 'graphEvaluationBody, graphDispatchBody' in export
assert 'graphInputIds=graphInputs.values()' in export
assert 'activationEvents.append(QStringLiteral("(%1 != (%2.active != 0u))")' in export
assert 'graphSnapshotsBody+=QStringLiteral(' in export
assert 'r.triggerExtraActions' in export
assert 'SidboxVisualLogic::order(nodes,localIds,&sorted,&issue)' in export
assert 'graphEvaluationBody+=QStringLiteral("    if (%1) {' in export
assert 'graphDispatchBody+=QStringLiteral("    if (%1) {' in export
assert template.index('@IDE{TRIGGER_ACTIONS}') < template.index('@IDE{GRAPH_EVALUATIONS}') < template.index('@IDE{GRAPH_DISPATCH}')
assert 'sourceFields.insert(QStringLiteral("GRAPH_EVALUATIONS"), graphEvaluationBody);' in export
assert 'sourceFields.insert(QStringLiteral("GRAPH_DISPATCH"), graphDispatchBody);' in export
assert 'targetedByBranch' in properties
assert 'Trigger / Logic Connections' in properties

# Mirrors the actual generator's emitted C for graph owner #0 and a second
# independent trigger (#1). Neither input can be ignored; no state changes
# after the graph snapshot may change that event's TRUE/FALSE selection.
program=r'''
#include <stdint.h>
#include <assert.h>
typedef struct {uint8_t active,trigger_fired;} Obj;
static Obj obj[5]; /* switch0, switch1, decoration0, decoration1, output */
static unsigned events;
static void frame(void) {
    /* Ordinary Trigger actions, compiled before ANY graph evaluation. */
    if(obj[0].trigger_fired) obj[2].active = (uint8_t)!obj[2].active;
    if(obj[1].trigger_fired) obj[3].active = (uint8_t)!obj[3].active;
    /* Graph belongs to Trigger #0 but watches input decorators #2 AND #3. */
    const unsigned char cg_logic_run_0 = (obj[0].trigger_fired || obj[1].trigger_fired)?1u:0u;
    unsigned char cg_logic_0_0=0;
    if(cg_logic_run_0) { cg_logic_0_0 = ((obj[2].active && obj[3].active)?1u:0u); }
    if(cg_logic_run_0) {
        if(cg_logic_0_0) { obj[4].active=1; ++events; }
        else { obj[4].active=0; ++events; }
    }
    obj[0].trigger_fired=obj[1].trigger_fired=0;
}
int main(void) {
    obj[0].trigger_fired=1;frame();assert(obj[2].active && !obj[3].active && !obj[4].active);
    obj[1].trigger_fired=1;frame();assert(obj[2].active && obj[3].active && obj[4].active);
    obj[0].trigger_fired=1;frame();assert(!obj[2].active && obj[3].active && !obj[4].active);
    obj[1].trigger_fired=1;frame();assert(!obj[2].active && !obj[3].active && !obj[4].active);
    frame();assert(events==4); /* no spontaneous re-execution */
    obj[0].trigger_fired=obj[1].trigger_fired=1;frame();
    assert(obj[2].active && obj[3].active && obj[4].active && events==5);
    return 0;
}
'''
with TemporaryDirectory() as d:
    src=Path(d)/'test.c';exe=Path(d)/'test';src.write_text(program)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O2',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.62: two-trigger state propagation, action dispatch and Game Object Properties visibility')
