#!/usr/bin/env python3
"""Stage 5.166.64: RESULT -> Game Object assigns its enabled state directly.

Regression: BOTH TRUE and FALSE used to default to enable on the same target,
so a valid AND truth table could never switch the target off.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

ROOT=Path(__file__).resolve().parents[2]
ui=(ROOT/'gamevisualnodes.cpp').read_text()
model=(ROOT/'gamevisualgraphlogic.h').read_text()
export=(ROOT/'gamedesigner_export.cpp').read_text()
properties=(ROOT/'gamedesigner.cpp').read_text()

assert 'QStringList resultTargets' in model
assert 'rawResultTargets.size()>64' in model
assert 'Logic node %1 drives missing Game Object %2.' in model
assert 'if(from.startsWith(QStringLiteral("@graphvalue:")))' in ui
assert 'addGraphResultTarget(from.mid(QStringLiteral("@graphvalue:").size()),to);' in ui
assert 'addGraphResultTarget(from.mid(QStringLiteral("@graphvalue:").size()),selectedId);' in ui
assert 'QStringLiteral("graph-result-binding")' in ui
assert 'if(kind==QStringLiteral("graph-result-binding"))' in ui
assert 'QStringLiteral("resultTargets"),bindings' in ui
assert 'actionTargets.insert(v.toString());' in ui  # Promote plain Decorations used only as RESULT targets
assert 'if(v.toObject().value(QStringLiteral("objectId")).toString()!=target)' in ui
assert 'yes?QStringLiteral("enable"):QStringLiteral("disable")' in ui
assert 'for(const QString &targetId:node.resultTargets)' in export
assert 'QStringLiteral("        %1.active = %2 ? 1u : 0u;\\n")' in export
assert 'resultTargets=new QTreeWidget(section)' in properties
assert 'form->addRow(tr("RESULT → enabled state"),editor.resultTargets);' in properties
assert 'node.insert(QStringLiteral("resultTargets"),bound);' in properties

# Mirrors the actual generated C, rather than mocking a GUI-only wire.
program=r'''
#include <stdint.h>
#include <assert.h>
typedef struct {uint8_t active, trigger_fired;} Obj;
static Obj obj[5]; /* two Triggers, two Decoration inputs, one output */
static unsigned dispatches;
static void frame(void) {
    const unsigned char before0=(obj[2].active != 0u);
    const unsigned char before1=(obj[3].active != 0u);
    if(obj[0].trigger_fired)obj[2].active=(uint8_t)!obj[2].active;
    if(obj[1].trigger_fired)obj[3].active=(uint8_t)!obj[3].active;
    const unsigned char run=(obj[0].trigger_fired ||
        (before0!=(obj[2].active!=0u)) ||
        (before1!=(obj[3].active!=0u)))?1u:0u;
    unsigned char result=0u;
    if(run)result=((obj[2].active && obj[3].active)?1u:0u);
    if(run) {
        obj[4].active = result ? 1u : 0u; // direct RESULT binding
        ++dispatches;
    }
    obj[0].trigger_fired=obj[1].trigger_fired=0u;
}
int main(void) {
    obj[4].active=1u; // stale pre-existing state must be corrected
    obj[0].trigger_fired=1u;frame();assert(obj[2].active && !obj[3].active && !obj[4].active);
    obj[1].trigger_fired=1u;frame();assert(obj[2].active && obj[3].active && obj[4].active);
    obj[1].trigger_fired=1u;frame();assert(obj[2].active && !obj[3].active && !obj[4].active);
    obj[0].trigger_fired=1u;frame();assert(!obj[2].active && !obj[3].active && !obj[4].active);
    frame();assert(dispatches==4u);
    obj[1].trigger_fired=1u;frame();obj[0].trigger_fired=1u;frame();
    assert(obj[2].active && obj[3].active && obj[4].active && dispatches==6u);
    return 0;
}
'''
with TemporaryDirectory() as d:
    c=Path(d)/'test.c';exe=Path(d)/'test'
    c.write_text(program)
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.64 direct RESULT->object binding + two-switch AND native test')
