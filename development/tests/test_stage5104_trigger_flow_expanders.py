#!/usr/bin/env python3
"""Static regression checks for read-only Trigger expanders (Qt6 build required on host)."""
import json
from pathlib import Path
root=Path(__file__).resolve().parents[2]
s=(root/'gamefloweditor.cpp').read_text()
assert 'QStringList triggerEvents;' in s
assert 'node.triggerEvents=events;' in s
assert 'display.nodes[display.byId.value(node.id)].triggerEvents=node.triggerEvents;' in s
for fragment in ('triggerExtraActions','targetObjectId','targetAction','interactDialogueNode',
                 'interactWrongDialogueNode','interactRewardItem','interactStatTarget',
                 'sfxInteractSuccess','triggerMusicAction','triggerOneShot','triggerPress'):
    assert fragment in s, fragment
assert 'drawTriggerEventRows(card,n,theme,layout.expanded.value(n.id,false));' in s
assert 'drawTriggerEventRows(child,member,theme,layout.expanded.value(memberId,false));' in s
assert 'drawTriggerEventRows(mini,member,theme,layout.expanded.value(memberId,false));' in s
assert 'const bool clickedToggle=pos()==m_pressPosition' in s
assert 'm_expandableTrigger &&' in s
assert 'bool m_expandableTrigger=false;' in s
assert 'layout.expanded.insert(id,!layout.expanded.value(id,false));' in s
assert 'redraw();savePositions();' in s
assert 'QMetaObject::invokeMethod(&dialog,[&,id]()' in s
assert 'triggerCardHeight(above,layout.expanded.value(above.id,false))' in s
assert 'const QPointF focus=view->mapToScene' in s
assert 'const qreal x=30+col*355;' in s
assert 'triggerCardWidth(graph.nodes.at(ix),layout.expanded.value(it.key(),false),200)' in s
assert 'const QString id=link.value(QStringLiteral("objectId")).toString();' in s
assert 'if (g.byId.contains(to))' in s
# Does not affect any data model/generation template; UI-only patch.
assert (root/'splashscreenwidget.cpp').read_text().count('Build: 5.104.251026')==1
print('PASS Stage5.104 source checks: trigger payload, nested cards, save/rebuild, wires and version')
