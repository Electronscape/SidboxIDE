#!/usr/bin/env python3
"""Stage 5.166.63: snapshot independent graph inputs before actions.

Regresses multi-trigger AND over two managed Decorations, owner-independent
updates, no idle repeats, and compatibility with owner-trigger activation.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

ROOT=Path(__file__).resolve().parents[2]
generator=(ROOT/'gamedesigner_export.cpp').read_text()
rule=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
properties=(ROOT/'gamedesigner.cpp').read_text()

assert 'QString graphSnapshotsBody, graphEvaluationBody, graphDispatchBody;' in generator
assert 'graphInputs.values()' in generator
assert 'graphInputIds.sort()' in generator
assert 'cg_logic_before_%1_%2' in generator
assert 'activationEvents.append(QStringLiteral("(%1 != (%2.active != 0u))")' in generator
assert 'graphSnapshotsBody+=QStringLiteral(' in generator
assert 'activationEvents.join(QStringLiteral(" || "))' in generator
assert 'sourceFields.insert(QStringLiteral("GRAPH_SNAPSHOTS"), graphSnapshotsBody);' in generator
assert rule.index('@IDE{GRAPH_SNAPSHOTS}') < rule.index('@IDE{TRIGGER_ACTIONS}') < rule.index('@IDE{GRAPH_EVALUATIONS}') < rule.index('@IDE{GRAPH_DISPATCH}')
assert 'Legacy Trigger state condition (optional)' in properties
assert 'their connected state inputs do not require any tick boxes here' in properties
assert 'targetedByBranch' in properties

# C scenario uses the actual generated-code shape and execution order, with
# deliberately *no* precomputed list of "Triggers which might affect logic".
# Snapshot each live state, execute ordinary trigger actions, compare live
# values, evaluate nodes, dispatch actions. A second switch must work even
# though the graph is stored on the first switch's Trigger resource.
program=r'''
#include <assert.h>
#include <stdint.h>
typedef struct {uint8_t active,trigger_fired;} Obj;
static Obj obj[5]; /* trigger0 trigger1 decoration0 decoration1 output */
static unsigned evaluations;
static void frame(void) {
    const unsigned char cg_logic_before_0_0 = (obj[2].active != 0u);
    const unsigned char cg_logic_before_0_1 = (obj[3].active != 0u);
    if (obj[0].trigger_fired) obj[2].active=(uint8_t)!obj[2].active;
    if (obj[1].trigger_fired) obj[3].active=(uint8_t)!obj[3].active;
    const unsigned char cg_logic_run_0 =
        (obj[0].trigger_fired ||
         (cg_logic_before_0_0 != (obj[2].active != 0u)) ||
         (cg_logic_before_0_1 != (obj[3].active != 0u))) ? 1u : 0u;
    unsigned char cg_logic_0_0=0u;
    if(cg_logic_run_0) cg_logic_0_0=((obj[2].active && obj[3].active)?1u:0u);
    if(cg_logic_run_0) {
        if(cg_logic_0_0) obj[4].active=1u;
        else obj[4].active=0u;
        ++evaluations;
    }
    obj[0].trigger_fired=obj[1].trigger_fired=0u;
}
int main(void) {
    frame(); assert(evaluations==0u);
    obj[0].trigger_fired=1;frame();
    assert(obj[2].active && !obj[3].active && !obj[4].active);
    obj[1].trigger_fired=1;frame();
    assert(obj[2].active && obj[3].active && obj[4].active);
    obj[0].trigger_fired=1;frame();
    assert(!obj[2].active && obj[3].active && !obj[4].active);
    obj[1].trigger_fired=1;frame();
    assert(!obj[2].active && !obj[3].active && !obj[4].active);
    frame(); assert(evaluations==4u);
    obj[1].trigger_fired=1;frame();
    obj[0].trigger_fired=1;frame();
    assert(obj[2].active && obj[3].active && obj[4].active);
    assert(evaluations==6u);
    return 0;
}
'''
with TemporaryDirectory() as d:
    c=Path(d)/'test.c'; exe=Path(d)/'test'
    c.write_text(program)
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.63: live Decoration state deltas drive independent AND outputs')
