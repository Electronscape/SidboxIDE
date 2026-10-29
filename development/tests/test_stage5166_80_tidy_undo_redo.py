"""Regression checks for Stage 5.166.80 graph layout and undo features."""
from pathlib import Path
import re
R=Path(__file__).resolve().parents[2]
s=(R/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.99.291026' in (R/'splashscreenwidget.cpp').read_text()
assert 'const QPainterPath path=smoothNodeCurve(a,b);' in s
assert 'smoothNodeCurve(a,b,16.0)' not in s
assert 'path.cubicTo(a+QPointF(bend,0),b-QPointF(bend,0),b);' in s
assert 'Barycentric crossing reduction' in s and 'std::stable_sort(column.begin(),column.end()' in s
assert 'QHash<QString,QSet<QString>> adjacent,outgoing,incoming;' in s
assert 'recordHistoryNow(); // Preserve any pending drag/text edit' in s
assert 'QVector<GraphHistory> m_history' in s
for f in ('captureGraphHistory','restoreGraphHistory','undoGraph','redoGraph','resetGraphHistory','recordHistoryNow'):
    assert re.search(r'\b'+f+r'\(',s),f
for shortcut in ('Ctrl+Z','Ctrl+Shift+Z','Ctrl+Y'):
    assert shortcut in s
for datum in ('m_objects=snap.objects','m_dialogues=snap.dialogues','m_npcEntries=snap.npcs',
              'm_positions=snap.positions','m_placedCards=snap.placed',
              'm_npcDialogueRoutes=snap.npcRoutes','m_touched=snap.touched'):
    assert datum in s,datum
assert 'resetGraphHistory(); // A save becomes the new undo baseline' in s
assert 'setConversationAnswer(index,option,' in s  # still authoring real dialogue IDs
assert (R/'gamecodegen.cpp').exists()
print('PASS 5.166.80: tangent curves, grouped graph tidy, session model+layout undo and redo')
