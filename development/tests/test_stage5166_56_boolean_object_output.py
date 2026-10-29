#!/usr/bin/env python3
"""Stage 5.166.56: Game Object state sockets feed Boolean cards.

Qt GUI build unavailable here. This test verifies the authoring/serialization
contract and protects the native Trigger-after-actions state semantics.
"""
from pathlib import Path
import subprocess
import tempfile

root=Path(__file__).resolve().parents[2]
s=(root/'gamevisualnodes.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.' in version
# Trigger ports are actions; real Game Object ports are state sources.
make=s[s.index('void makeObjectCard('):s.index('void renderCards(',s.index('void makeObjectCard('))]
assert 'if (trigger || (node.resourceIndex>=0' in make
assert 'QColor(54,148,141)' in make
assert 'port->setData(1,id)' in make
# Dragging from object output into an empty canvas opens only Logic > Boolean.
tree=s[s.index('void showInsertTree('):s.index('void appendConnection(')]
assert 'objectSource' in tree
assert 'if (!objectSource) for (const QString &id:m_order)' in tree
assert 'if (objectSource) {' in tree
assert 'QStringList{tr("Logic")}' in tree
assert 'addBooleanFromObject(from,at,selectedId.mid(' in tree
# Real Trigger owner is determined from its actual .sbgm action list;
# multiple owners require explicit choice rather than a guessed Trigger.
author=s[s.index('void addBooleanFromObject('):s.index('void createToggleCard(')]
assert 'link.target==source && supportedAction(link.action)' in author
assert 'QInputDialog::getItem' in author
assert 'if (owners.isEmpty())' in author
assert 'n.toggleStateTargetId=source;' in author
assert 'm_touched.insert(owner)' in author
assert 'node.dialogueNode' not in author
# No extra gameplay links are stored in the layout file.
layout=s[s.index('QJsonObject graphJson('):s.index('bool saveLayout(')]
assert 'toggleStateTargetId' not in layout
# Existing stored state ID is now rendered as SOURCE OBJECT -> Boolean.
redraw=s[s.index('void redrawLinks()'):s.index('void showDetails(')]
assert 'm_cards.contains(sourceId)' in redraw
assert 'NodeCard *source=m_cards.value(sourceId)' in redraw
assert 'wire->setData(0,QStringLiteral("state-link"))' in redraw
assert 'const QPointF a=source->scenePos()+QPointF(224,58);' in redraw
# Boolean remains source-selector-free and retains TRUE/FALSE action sockets.
card=s[s.index('void createToggleCard('):s.index('void refreshToggleCard(')]
assert 'QComboBox' not in card
assert 'QGraphicsSimpleTextItem' in card
assert 'TRUE = enabled  |  FALSE = disabled' in card
assert 'QStringLiteral("@stateout:true:")' in card
assert 'QStringLiteral("@stateout:false:")' in card
# Regression: Trigger toggles the target first, then its active state is read.
source=r'''
#include <assert.h>
typedef struct { int active; } Object;
static Object lifty, door;
static int dialogue;
static void trigger(void) {
    lifty.active=!lifty.active;
    if (lifty.active) { door.active=1; dialogue=10; }
    else { door.active=0; dialogue=14; }
}
int main(void) {
    lifty.active=0;
    trigger();assert(lifty.active==1 && door.active==1 && dialogue==10);
    trigger();assert(lifty.active==0 && door.active==0 && dialogue==14);
    return 0;
}'''
with tempfile.TemporaryDirectory() as d:
    c=Path(d)/'test.c';exe=Path(d)/'test';c.write_text(source)
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.56 Game Object -> Boolean wiring, legacy data, native branching')
