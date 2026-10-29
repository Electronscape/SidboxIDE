from pathlib import Path
import re
src = Path(__file__).resolve().parents[2]
cpp = (src/'gamevisualnodes.cpp').read_text()
splash = (src/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.100.291026' in splash
restore = cpp[cpp.index('    void restoreGraphHistory('):cpp.index('    void undoGraph()', cpp.index('    void restoreGraphHistory('))]
assert 'm_flowGroups.clear();' in restore
assert restore.index('m_flowGroups.clear();') < restore.index('m_scene->clear();')
assert restore.index('m_scene->clear();') < restore.index('renderCards();')
assert 'm_hiddenConversationRoots=snap.hiddenConversationRoots;' in restore
assert 'QSet<int> roots,hiddenConversationRoots;' in cpp
assert 'snap.hiddenConversationRoots=m_hiddenConversationRoots;' in cpp
assert 'data.insert(QStringLiteral("hiddenConversationRoots"),hidden);' in cpp
assert 'void ensureConversationFlowGroup(int root)' in cpp
assert 'if(m_flowGroups.contains(root))return;' in cpp
assert 'm_flowGroups.insert(root,group);' in cpp
print('PASS 5.166.95 - scene-owned flow groups invalidated before scene clear; visibility history restored')
