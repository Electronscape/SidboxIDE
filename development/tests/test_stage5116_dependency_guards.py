#!/usr/bin/env python3
"""Stage 5.116 UI dependency contract checks + actual native dialogue runtime.

Qt6's developer SDK is not available on the CI host, so the UI checks inspect
source wiring while the game behaviour runs as compiled C.
"""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
e=(root/'gameadventureeditor.cpp').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.116.251026' in splash
assert 'const auto refreshChoiceControls = [&]()' in e
assert 'fields[i].reply,&QTextEdit::textChanged' in e
assert 'fields[i].next,QOverload<int>::of(&QComboBox::currentIndexChanged)' in e
assert 'fields[i].requires,QOverload<int>::of(&QComboBox::currentIndexChanged)' in e
assert 'fields[i].npcTargets[effect],QOverload<int>::of(&QComboBox::currentIndexChanged)' in e
assert 'f.thought->setEnabled(selectable && hasSpeech && hasNext)' in e
assert 'f.thoughtThis->setEnabled(canThinkNow)' in e
assert 'firstTerminalThought!=choiceIndex' in e
assert 'f.missingNext->setEnabled(selectable && hasRequirement)' in e
assert 'f.mode->setEnabled(selectable && kind!=QStringLiteral("none") && kind!=QStringLiteral("custom"))' in e
assert 'f.customId->setEnabled(selectable && kind==QStringLiteral("custom"))' in e
assert 'const bool canEdit=terminal || selectable' in e
assert 'f.npcTargets[effect]->setEnabled(canEdit)' in e
assert 'f.npcModes[effect]->setEnabled(canEdit && hasTarget)' in e
assert 'onCloseGroup->setEnabled(terminal)' in e
assert 'mirrorCloseNpc(effect);' in e and 'mirrorCloseGift();' in e
assert 'onCloseNpcMode[effect]->setEnabled(terminal && hasTarget)' in e
assert 'f.dependencyNote->setVisible(!problems.isEmpty());' in e
assert 'auto refreshExchangeControls=[=]()' in e
assert 'const bool repeat=active && required>0 && repeatEnabled->isChecked()' in e
assert 'const bool canIncrement=active && logic->currentData().toString()==QStringLiteral("all") && required>=2' in e
assert 'QObject::connect(enabled,&QCheckBox::toggled,&dlg' in e
assert 'const auto refreshFrameControls=[&]' in e
assert 'refreshFrameControls();' in e
assert 'inventoryIconCell->setEnabled(customIconAtlas)' in e
assert 'const auto refreshUseControls=[&]' in e
assert 'const auto refreshItemButtons=[&]' in e
assert 'const auto refreshNpcButtons=[&]' in e
assert 'const auto refreshDialogueButtons=[&]' in e
assert 'const auto refreshTimeline=[&,state,add,remove,up,down]' in e
assert 'previewAnswer->setEnabled(hasAnswers)' in e
# No C layout ABI or resource format change.
assert (root/'gameadventuregen.cpp').exists()
with tempfile.TemporaryDirectory(prefix='stage5116-') as tmp:
    out=render_adventure_runtime(root,Path(tmp))
    tests=root/'development/tests'
    for stem in ('stage5114_current_thought','stage5115_answerless_thought'):
        exe=out/stem
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
            '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(tests/f'test_{stem}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.116: guard source wiring + both real thought-bubble runtime tests PASS')
