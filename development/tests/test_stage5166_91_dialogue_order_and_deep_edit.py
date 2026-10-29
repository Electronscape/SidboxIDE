"""Stage 5.166.91 source contracts: consistent dialogue socket order and direct edit-return.
This is not a Qt desktop graphics test; hardware/gameplay generator is unchanged.
"""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
ui=(r/'gamevisualnodes.cpp').read_text()
designer=(r/'gamedesigner.cpp').read_text()
adv=(r/'gameadventureeditor.cpp').read_text()
assert 'Build: 5.166.99.291026' in (r/'splashscreenwidget.cpp').read_text()
card=ui[ui.index('class NodeCard final'):ui.index('class NodeCanvas final')]
assert 'std::stable_sort(compactOutputs.begin(),compactOutputs.end()' in card
for tag,rank in [('give-anchor',0),('conversation-missing-output',1),('conversation-output',2)]:
    assert f'kind==QStringLiteral("{tag}"))return {rank};' in card
assert '14.0+17.0*slot-original.center().y()' in card
assert 'compactOutputs.indexOf(port)' in card
expanded=ui[ui.index('void redrawLinks()'):ui.index('void showDetails(',ui.index('void redrawLinks()'))]
assert 'kind==QStringLiteral("give-anchor")?-15.0:' in expanded
assert 'kind==QStringLiteral("conversation-missing-output")?0.0:15.0' in expanded
assert 'kind==QStringLiteral("conversation-output")?7.5:-7.5' in expanded
assert 'for (;;)' in designer[designer.index('connect(visualNodesButton'):designer.index('auto *titleScreenButton')]
assert 'openAdventureEditor(QString(),openDialogue,true)' in designer
assert 'if (m_dirty && !saveDesign())break;' in designer
assert 'editFocusedDialogueDirectly' in designer and 'editFocusedDialogueDirectly' in (r/'gamedesigner.h').read_text()
assert 'editFocusedDialogueDirectly' in (r/'gameadventureeditor.h').read_text()
assert 'QTimer::singleShot(0,&dialog,[&dialog,&doNodeEdit]' in adv
assert 'if(doNodeEdit())dialog.accept();' in adv
assert 'else dialog.reject();' in adv
assert 'bool editNode(' in adv and 'if (dialog.exec() != QDialog::Accepted) return false;' in adv
assert 'const bool accepted=editNode(' in adv
assert 'redrawNodes(focusDialogueIndex)' in adv
assert 'tabs->setCurrentWidget(dialoguePage)' in adv
assert 'done(3);' in ui and 'if(m_dirty && !saveAll())return;' in ui and 'if(!saveViewportOnly())' in ui
print('PASS Stage 5.166.91: socket order, direct node editor, save/reload/return, cancel safety')
