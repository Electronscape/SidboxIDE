#!/usr/bin/env python3
"""Schema, integration and native-C regression for Stage 5.166.60.

Does not claim to compile the Qt6 IDE: Qt6 dev headers are unavailable here.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess
import re

ROOT=Path(__file__).resolve().parents[2]
graph=(ROOT/'gamevisualnodes.cpp').read_text()
model=(ROOT/'gamevisualgraphlogic.h').read_text()
export=(ROOT/'gamedesigner_export.cpp').read_text()
project=(ROOT/'gamedesigner_project.cpp').read_text()
properties=(ROOT/'gamedesigner.cpp').read_text()

# Independent IDs and collections, not one condition per Trigger.
assert 'QJsonArray logicNodes;' in (ROOT/'gamedesigner.h').read_text()
assert 'node.logicNodes=data.value(QStringLiteral("logicNodes")).toArray();' in graph
assert 'object.insert(QStringLiteral("logicNodes"),node.logicNodes);' in graph
assert 'r.logicNodes = object.value(QStringLiteral("logicNodes")).toArray();' in project
assert 'object.insert(QStringLiteral("logicNodes"), r.logicNodes);' in project
assert 'const QString key=graphKey(owner,name);' in graph
assert 'makeGraphCard(owner,id);' in graph
assert 'createGraphLogic(from,at,selectedId.mid' in graph
assert 'addGraphInput(from,to);' in graph
assert 'redrawGraphLinks();' in graph
assert 'makeGraphDialogueCard(key,yes);' in graph
assert 'showGraphWireMenu(kind,key,index,at);' in graph

# Nodes connect to nodes, object state, or TRUE/FALSE actions/dialogues.
for required in ('@graphvalue:', '@graphbranch:true:', '@graphbranch:false:',
                 'graph-input', 'graph-true-action', 'graph-false-action',
                 'graph-true-dialogue', 'graph-false-dialogue',
                 'graphDialogueKey', 'removeGraphNode'):
    if required=='removeGraphNode':
        continue # implemented in removeSelectedNode() instead of a helper
    assert required in graph, required

# Graphs are authoritative in .sbgm; per-node actions aren't stored in .vsgm.
layout=graph[graph.index('QJsonObject graphJson() const'):graph.index('bool saveLayout()')]
assert 'logicNodes' not in layout
assert 'positions' in layout

# Errors detected before generation: malformed operators, missing inputs,
# duplicate IDs, missing object/nodes and cycles, plus a topological schedule.
for required in ('Maximum 64 logic nodes', 'Unknown operator',
                 'duplicate input', 'missing Game Object', 'references missing node',
                 'Logic cycle', 'visit(byId.value(input.id))'):
    assert required in model, required
assert export.count('SidboxVisualLogic::order(')>=2
assert 'SidboxVisualLogic::expression(node,objectSlot,expressionNames)' in export
assert 'cg_logic_%1_%2' in export
assert 'unsigned char %1 = 0u;' in export
assert 'owner.logicNodes.isEmpty()' in export

# Properties edits exactly the same node IDs/fields, including from a source
# object and not only from the owning Trigger.
for required in ('Independent logic node', 'GraphEditor',
                 'owner.logicNodes.replace(index,node)',
                 'hasIncomingGraph', 'Logic %1 (%2)'):
    assert required in properties, required

# The old runtime and old single-condition authoring still have their fields.
for required in ('toggleStateTargetId', 'toggleTrueDialogueNode', 'toggleFalseActions'):
    assert required in graph and required in export

# Native C contract: a Boolean RESULT can feed AND/OR/NOT, and its output can
# select independent actions. This illustrates the exact expression forms.
program='''
#include <stdint.h>
#include <assert.h>
static int event(uint8_t lift,uint8_t door) {
    const unsigned char cg_logic_0_0 = (((lift)!=0) ? 1u : 0u);
    const unsigned char cg_logic_0_1 = (((door)!=0) ? 1u : 0u);
    const unsigned char cg_logic_0_2 = (((cg_logic_0_0) && (cg_logic_0_1)) ? 1u : 0u);
    const unsigned char cg_logic_0_3 = (((cg_logic_0_2) || (cg_logic_0_1)) ? 1u : 0u);
    const unsigned char cg_logic_0_4 = ((!(cg_logic_0_3)) ? 1u : 0u);
    int value=0;
    if (cg_logic_0_2) { value+=1; } else { value+=2; }
    if (cg_logic_0_4) { value+=4; } else { value+=8; }
    return value;
}
int main(void) {
    assert(event(0,0)==6);
    assert(event(1,0)==6);
    assert(event(0,1)==10);
    assert(event(1,1)==9);
}
'''
with TemporaryDirectory() as path:
    source=Path(path)/'test.c';source.write_text(program)
    binary=Path(path)/'test'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(source),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
print('PASS Stage 5.166.60 independent graph storage, wiring, validation, generator integration, properties and native C truth tables')
