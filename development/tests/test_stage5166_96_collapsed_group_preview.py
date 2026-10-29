from pathlib import Path

src = Path(__file__).resolve().parents[2]
cpp = (src/'gamevisualnodes.cpp').read_text()
splash = (src/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.100.291026' in splash
flow = cpp[cpp.index('class FlowGroupBox final'):cpp.index('class NodeCard final')]
assert 'm_input=new QGraphicsRectItem' in flow
assert 'm_input->setVisible(collapsed);' in flow
assert 'QPointF inputPoint() const' in flow
assert 'setAcceptedMouseButtons(Qt::NoButton)' in flow
redraw = cpp[cpp.index('    void redrawLinks() {'):cpp.index('    void showDetails(', cpp.index('    void redrawLinks() {'))]
assert redraw.index('updateConversationFlowGroups();') < redraw.index('m_liveWiresByCard.clear();')
assert 'const bool compact=group && group->isVisible() && group->collapsed();' in redraw
assert 'if(!m_conversationRoots.contains(root) || flowRootHidden(root))continue;' in redraw
assert 'compact?group->inputPoint():target->wirePoint(QPointF(0,110))' in redraw
assert 'compact?flowGroupId(root):conversationCardId(root)' in redraw
assert 'to.startsWith(QStringLiteral("@flowgroup:"))' in redraw
ensure = cpp[cpp.index('    void ensureConversationFlowGroup('):cpp.index('    void updateConversationFlowGroups()',cpp.index('    void ensureConversationFlowGroup('))]
assert 'm_liveWiresByCard.value(flowGroupId(root))' in ensure
assert 'wire->setPath(path);' in ensure
restore = cpp[cpp.index('    void restoreGraphHistory('):cpp.index('    void undoGraph()', cpp.index('    void restoreGraphHistory('))]
assert restore.index('m_flowGroups.clear();') < restore.index('m_scene->clear();')
print('PASS 5.166.96 collapsed group NPC link + live drag + safe undo lifetime')
