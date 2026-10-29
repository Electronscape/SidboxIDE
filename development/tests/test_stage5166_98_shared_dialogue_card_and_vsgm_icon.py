"""Stage 5.166.98: shared dialogue-card source contracts.

This source-level regression does not substitute for a desktop Qt build.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
s = (root/'gamevisualnodes.cpp').read_text()
main = (root/'mainwindow.cpp').read_text()
ui = (root/'mainwindow_uiicons.cpp').read_text()
cmake = (root/'CMakeLists.txt').read_text()
sp = (root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.100.291026' in sp

# This field only appears in visual-layout serialization, never in gameplay codegen.
assert 'graph.value(QStringLiteral("graphDialogueRoutes"))' in s
assert 'root.insert(QStringLiteral("graphDialogueRoutes"),sharedDialogueRoutes)' in s
assert 'm_graphDialogueRoutes.insert(own,to)' in s
assert 'm_graphDialogueRoutes=snap.graphDialogueRoutes' in s
assert 'snap.graphDialogueRoutes=m_graphDialogueRoutes' in s
assert 'data.insert(QStringLiteral("graphDialogueRoutes"),sharedRoutes)' in s

# The drop binds the existing dialogue ID to the source action, eliminates
# the redundant source-owned visual card, and only then installs the route.
drop=s[s.index('if(from.startsWith(QStringLiteral("@graphbranch:")))',s.index('void addConnection(')):
       s.index('if (from.startsWith(QStringLiteral("@stateout:")))',s.index('void addConnection('))]
assert 'selectedDialogueOnCard(to)' in drop
assert 'const QPointF where=m_cards.value(to)->pos();' in drop
assert drop.index('setGraphDialogue(key,yes,selected,where);') < drop.index('m_graphDialogueRoutes.insert(own,to)')
assert drop.index('removeOrphanCard(own,true)') < drop.index('m_graphDialogueRoutes.insert(own,to)')
assert 'viewportInsertionPoint(QSizeF(345,380))' not in drop
assert 'if(to!=own && !dialogueCardHasLiveAction(to))' in drop

# Rendering uses an existing card only when the stored target is still valid
# and still represents the same dialogue number.
assert 'return selectedDialogueOnCard(to)==dialogue;' in s
assert 'graphDialogueVisualTarget(key,yes,dialogue)' in s
assert 'key,visualTo);' in s
assert 'if(!validSharedGraphDialogue(own,dialogue))' in s

# Project tree and editor tab are distinct paths; both need the extension.
assert 'suffix == QStringLiteral("vsgm")' in main
assert 'suffix == QStringLiteral("vsgm")' in ui
assert 'tree_vsgm.png' in main and 'tree_vsgm.png' in ui
assert 'toolbar_gamedesigner.png' in main and 'toolbar_gamedesigner.png' in ui
assert 'if(EXISTS' in cmake and 'icons/tree_vsgm.png' in cmake

print('PASS Stage 5.166.98 shared card reconnection, persistence, and file icon mapping')
