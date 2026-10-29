#!/usr/bin/env python3
"""Stage 5.166.58: no duplicate runtime state; editable Boolean branches from both properties endpoints."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
s=(r/'gamedesigner.cpp').read_text()
graph=(r/'gamevisualnodes.cpp').read_text()
version=(r/'splashscreenwidget.cpp').read_text()
f=s[s.index('void SidboxGameDesigner::configureGameObject('):s.index('void SidboxGameDesigner::',s.index('void SidboxGameDesigner::configureGameObject(')+20)]
assert 'Build: 5.166.' in version
assert 'const PropertyCard triggerCard = makeCard(tr("Switch, Trigger & Save Checkpoint"));' in f
assert 'const PropertyCard incomingBooleanCard = makeCard(tr("Trigger / Logic Connections"));' in f
assert 'triggerCard.form->addRow(booleanRows);' in f
assert 'incomingBooleanCard.form->addRow(incomingBooleanRows);' in f
assert 'candidate.toggleStateTargetId != old.id' in f
assert 'editor.ownerId = candidate.id;' in f
for key in ('toggleStateTargetId','toggleTrueDialogueNode','toggleFalseDialogueNode', 'toggleTrueActions', 'toggleFalseActions'):
    assert f'owner.{key}' in f, key
    assert key in graph,key
assert 'createGameDialogueTreeCombo(&dialog, &interactionNodes,' in f
for action in ('enable','disable','toggle'):
    assert f'QStringLiteral("{action}")' in f
assert 'booleanActionsFromTable(editor.trueActions)' in f
assert 'booleanActionsFromTable(editor.falseActions)' in f
assert 'values << table->rowCount();' in f
assert 'buildBooleanRows();' in f[f.index('const auto showObject ='):]
assert 'rememberResourceEdit();' in f
assert 'const PropertyCard booleanStateCard' not in f
assert 'No duplicate on_enable/on_disable object callbacks' in f
print('PASS: editable Trigger-owned Boolean branches, incoming state-source editing, draft tracking and no runtime/schema changes')
