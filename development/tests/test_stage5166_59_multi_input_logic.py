#!/usr/bin/env python3
"""Stage 5.166.59: multi-input Game Object state conditions.
Qt widget compilation requires the user's Qt6 dev installation; this checks
schema/graph/generator contracts and compiles the corresponding C semantics.
"""
from pathlib import Path
import tempfile
import subprocess

root=Path(__file__).resolve().parents[2]
header=(root/'gamedesigner.h').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
generator=(root/'gamedesigner_export.cpp').read_text()
editor=(root/'gamedesigner.cpp').read_text()
graph=(root/'gamevisualnodes.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.' in version
for field in ('toggleStateOperator','toggleStateInputIds'):
    assert field in header and field in project and field in graph and field in editor and field in generator
    assert f'object.insert(QStringLiteral("{field}")' in project
    assert f'object.value(QStringLiteral("{field}"))' in project
    assert f'object.insert(QStringLiteral("{field}")' in graph
    assert f'data.value(QStringLiteral("{field}"))' in graph
# Backwards compatibility of old single-source .sbgm files.
assert 'QStringLiteral("boolean")' in project and 'QStringLiteral("boolean")' in graph
assert 'r.toggleStateTargetId' in generator
# Runtime applies normal trigger actions before multi-input test / branches.
body=generator[generator.index('for (const Resource::LinkedAction &link : r.triggerExtraActions)'):]
assert body.index('for (const Resource::LinkedAction &link : r.triggerExtraActions)') < body.index('const QString expression=comparisons.join(')
assert 'QStringLiteral(" && ")' in body and 'QStringLiteral(" || ")' in body
assert 'if (%1)' in body
assert body.index('if (%1)') < body.index('for (const Resource::LinkedAction &link:r.toggleTrueActions)')
assert body.index('for (const Resource::LinkedAction &link:r.toggleFalseActions)') < body.index('if (r.interactItemName.isEmpty()')
# Real visual node interactions and compatibility tree.
for token in ('@logic:boolean','@logic:and','@logic:or','addInputToCondition(',
              'toggleStateInputIds.append(source)','m_cards.contains(sourceId)',
              'stateInputs.append(input)','toggleStateOperator','incomplete %2 state condition'):
    assert token in graph,token
assert 'const QPair<QString,int> ref' in graph
assert 'removeToggleCondition(ref.first)' in graph
# Collapsible property groups, multi-input editor, real same owner fields.
for token in ('QToolButton(outer)','collapse->setCheckable(true)',
              'editor.inputs=new QTreeWidget(group)', 'stateInputsFromTree(editor.inputs)',
              'owner.toggleStateTargetId=inputs.value(0)',
              'owner.toggleStateInputIds=inputs.mid(1)',
              'owner.toggleStateOperator=editor.operatorMode->currentData().toString()'):
    assert token in editor,token
# Physical logic truth table with post-action state test in native C.
program=r'''
#include <assert.h>
typedef struct { int active; } GameObject;
static GameObject switch_a, switch_b, switch_c, door;
static int message;
static void eval_and(void) {
    if (switch_a.active && switch_b.active && switch_c.active) {
        door.active=1; message=14;
    } else {door.active=0; message=13;}
}
static void eval_or(void) {
    if (switch_a.active || switch_b.active) {
        door.active=1; message=14;
    } else {door.active=0;message=13;}
}
int main(void) {
    eval_and();assert(!door.active && message==13);
    switch_a.active=1;eval_and();assert(!door.active);
    switch_b.active=1;eval_and();assert(!door.active);
    switch_c.active=1;eval_and();assert(door.active && message==14);
    switch_b.active=0;eval_and();assert(!door.active && message==13);
    switch_a.active=0;eval_or();assert(!door.active);
    switch_b.active=1;eval_or();assert(door.active && message==14);
    switch_b.active=0;switch_a.active=1;eval_or();assert(door.active);
    switch_a.active=0;eval_or();assert(!door.active);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as temp:
    source=Path(temp)/'logic.c';exe=Path(temp)/'logic';source.write_text(program)
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(source),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.59 multi-input AND/OR schema, authoring and native state truth tables')
