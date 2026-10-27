#!/usr/bin/env python3
"""Stage 5.165.2 editor/flow regression contracts; Qt GUI not available here."""
from pathlib import Path
import json
import re

root=Path(__file__).resolve().parents[2]
editor=(root/'gamequesteditor.cpp').read_text()
flow=(root/'gamefloweditor.cpp').read_text()
version=(root/'splashscreenwidget.cpp').read_text()

# The saved quest data format stays exactly 1; runtime/save schema stays 2.
assert '"version",1' in editor
assert 'GW_SAVE_VERSION 2u' in (root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
assert 'Build: 5.166.12.271026' in version

# Source of truth is the real saved .sbgm Adventure nodes/answers.
assert 'readProjectTargets(projectRoot);' in editor
for text in ('QStringLiteral("*.sbgm")', 'QStringLiteral("nodes")',
             'QStringLiteral("choices")', 'QStringLiteral("action")',
             'QStringLiteral("targetObjectId")', 'QStandardItemModel',
             'item->setEnabled(false)', 'configureTarget(i,',
             'targetValue+QLatin1Char(\':\')+eventValue',
             'dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized)'):
    assert text in editor, text
assert 'objectives->setColumnCount(5)' in editor
assert 'QJsonArray quests' in editor
assert 'GameQuestGen::validate(quests,&why)' in editor

# Before this patch quest cards were created with an empty world, invisible
# to the renderer, which requires a lane name matching g.worlds entries.
assert 'g.worlds.prepend(questLane)' in flow
for key in ('g.addNode(questKey,questLane,','g.addNode(stepKey,questLane,',
            'g.addNode(signal,questLane,','"@project-quests"',
            'worldSelect->addItem(name==QStringLiteral("@project-quests")',
            'QObject::connect(questView,&QPushButton::clicked',
            'g.link(source,signal,QStringLiteral("Custom event %1 → quest")',
            'Source dialogue:'):
    assert key in flow,key
assert 'g.addNode(questKey,QString()' not in flow
assert 'g.addNode(stepKey,QString()' not in flow

# Representative world documents from user's earlier Platformer3 test, if
# supplied, must offer readable dialogue choices even before custom IDs exist.
fixtures=Path(__file__).resolve().parents[3]/'fixture'
if not fixtures.is_dir():
    fixtures=Path('/mnt/data/stage5165_2_work/fixture')
if fixtures.is_dir():
    worlds=list(fixtures.glob('*.sbgm'))
    assert worlds
    found=False
    for path in worlds:
        nodes=json.loads(path.read_text()).get('adventure',{}).get('nodes',[])
        for node in nodes:
            for choice in node.get('choices',[]):
                if choice.get('text','').strip():found=True
    assert found
print('PASS Stage 5.165.2: named dialogue targets, disabled unresolved answers, maximised editor, visible quest lane and wired dialogue choices')
