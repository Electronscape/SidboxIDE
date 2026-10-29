from pathlib import Path
src=Path(__file__).resolve().parents[2]
cpp=(src/'gamevisualnodes.cpp').read_text()
assert 'Build: 5.166.100.291026' in (src/'splashscreenwidget.cpp').read_text()
assert 'class FlowGroupBox final' in cpp
assert 'QRectF(0,0,m_compactWidth,34.0)' in cpp
assert 'm_fold->setPos(rect().width()-30,3)' in cpp
assert 'm_dragOrigin=pos()' in cpp
assert 'setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges)' in cpp
assert 'QPainterPath shape() const override' in cpp
assert 'group->moved=[this,root](const QPointF &delta)' in cpp
assert 'card->setPos(card->pos()+delta)' in cpp
assert 'group->dragFinished=[this]' in cpp
assert 'updateConversationFlowGroups();' in cpp
assert 'if(!m_movingFlowGroup && (id.startsWith(QStringLiteral("@conversation:"))' in cpp
assert 'if(id.startsWith(QStringLiteral("@conversation:")) ||' in cpp
assert 'updateConversationFlowGroups();\n        updateCanvasBounds();' in cpp
assert 'hiddenConversationFlowRoots' in cpp
print('PASS stage 5.166.94 conversation group geometry source contracts')
