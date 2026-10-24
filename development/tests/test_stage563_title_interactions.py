#!/usr/bin/env python3
"""Stage 5.63 source-level checks. Interactive Qt GUI acceptance remains separate."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
s=(root/'gametitlescreeneditor.cpp').read_text()
assert 'Build: 5.63.231026' in (root/'splashscreenwidget.cpp').read_text()
for item in ('brackets','rect','arrow','underline'):
    assert f'QStringLiteral("{item}")' in s
assert 'selectorOverlay->setZValue(1.5)' in s
assert 'item->setZValue(2)' in s
assert 'setAcceptedMouseButtons(Qt::NoButton)' in s
assert 'selectorOverlay->setPath(outlinePath)' in s
assert 'QStringLiteral("menuSelector")' in s
assert 'QStringLiteral("selectorColour")' in s
assert 'QStringLiteral("snapGrid")' in s
assert 'QStringLiteral("fire1")' in s and 'QStringLiteral("fire2")' in s
assert 'setCurrentIndex(qMax(0,snapCombo->findData(snapGrid)))' in s
assert 'for(const int grid : {0,1,2,4,8})' in s
assert 'void wheelEvent(QWheelEvent *event) override' in s
assert 'm_fitOnResize = false;' in s
assert 'columns->addLayout(previewColumn,5)' in s
assert 'columns->addLayout(right,3)' in s
assert 'remember=[&]()' in s
assert 'restoreHistory=[&](int index)' in s
assert 'while(history.size()>historyCursor+1) history.removeLast();' in s
assert 'if(history.size()>256)history.removeFirst();' in s
assert 'QSignalBlocker b0(enabled)' in s
assert 'QJsonDocument(obj).toJson(QJsonDocument::Indented)' in s
assert 'std::round(pos.x()/step)*step' in s
assert 'std::round(pos.y()/step)*step' in s
assert 'GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,Qt::white);' in s
# The regression from Stage 5.60.1 must stay fixed, especially now that the selector
# is reacting to item selection. Never destroy an item in a selection callback.
a=s.index('QObject::connect(scene,&QGraphicsScene::selectionChanged')
b=s.index('QObject::connect(target,qOverload<int>(&QComboBox::currentIndexChanged)',a)
c=s.index('QObject::connect(titleEdit,&QLineEdit::textChanged',b)
assert 'render();' not in s[a:b]
assert 'scene->clear()' not in s[a:b]
assert 'render();' not in s[b:c]
assert 'if(updateSelector)updateSelector();' in s[a:c]
assert 'QSignalBlocker blocker(scene);' in s[b:c]
# Old title-screen layouts must retain their default text/PPB styling.
assert 'obj.value(QStringLiteral("menuSelector")).toString(QStringLiteral("brackets"))' in s
assert 'artFromJson(' in s
assert 'obj.insert(QStringLiteral("version"),5);' in s
print('Stage 5.63 title-screen selector/zoom/grid/history source checks: PASS')
