#!/usr/bin/env python3
"""Stage 5.137: Game Object Previous/Next dirty-check regression contracts."""
from pathlib import Path
import hashlib
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
base=Path('/mnt/data/ide_251026_stage5136')
s=(root/'gamedesigner.cpp').read_text()
function=s[s.index('void SidboxGameDesigner::configureGameObject(int index)'):s.index('void SidboxGameDesigner::refreshObjectHitbox()')]
nav=function[function.index('const auto navigateObject'):function.index('auto *buttons = new QDialogButtonBox', function.index('const auto navigateObject'))]
# No changes: switch without touching the saved object or asking a question.
assert 'if (draftSnapshot() != loadedDraft)' in nav
assert nav.index('if (draftSnapshot() != loadedDraft)') < nav.index('QMessageBox::question(')
assert nav.count('showObject(destination);')==1
assert nav.index('showObject(destination);') > nav.index('if (draftSnapshot() != loadedDraft)')
# Three-way response is intentional; Cancel stays, Save validates/commits,
# No reloads rather than committing and restores other unsaved draft state.
assert 'QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel' in nav
assert 'answer == QMessageBox::Cancel || answer == QMessageBox::NoButton' in nav
assert 'if (answer == QMessageBox::Save)' in nav
assert 'if (!commitObject()) return;' in nav
assert 'answer == QMessageBox::No' in nav
assert 'customPickupTypes = m_adventure.value(QStringLiteral("pickupTypes")).toArray();' in nav
assert 'previewFadeOnCanvas();' in nav
assert 'confirmSaveNavigation' not in function
# Both arrows use one procedure, and snapshots reset after programmatic reloads.
assert 'navigateObject(previousIndex);' in function
assert 'navigateObject(nextIndex);' in function
assert 'loadedDraft = draftSnapshot();' in function
assert function.index('loadedDraft = draftSnapshot();') < function.index('const auto navigateObject')
assert 'pickupOptionsTouched = false;' in function
assert 'pickupStatTouched = false;' in function
# Don't mistake animated preview / scrolling for saved changes. Do detect
# draft changes outside the simple controls (stamp, linked rows, palette).
snap=function[function.index('const auto draftSnapshot'):function.index('QVariantList loadedDraft')]
for token in ('QComboBox','QCheckBox','QSpinBox','QDoubleSpinBox','QLineEdit','QSlider',
              'linkedActionRows->rowCount()', 'draftSpriteStamp.toJson()',
              'customPickupTypes','chosenHazardColour','pickupOptionsTouched','pickupStatTouched'):
    assert token in snap,token
assert 'QScrollBar' not in snap
assert 'Build: 5.137.251026' in (root/'splashscreenwidget.cpp').read_text()
# Important: this release must not modify game code or saved data format.
for name in ('gameadventureeditor.cpp','gameadventuregen.cpp','gamedesigner_export.cpp',
             'gamedesigner.h','gamefloweditor.cpp','gamepaletteeditor.cpp',
             'idelibs/codehelpers/game/adventureruntime.rulec'):
    assert hashlib.sha256((root/name).read_bytes()).digest() == hashlib.sha256((base/name).read_bytes()).digest(),name
# Existing generated runtime still builds/executes with the native tests.
with tempfile.TemporaryDirectory(prefix='stage5137-') as tmp:
    out=render_adventure_runtime(root,Path(tmp),items=1)
    tests=root/'development/tests'
    for name in ('stage5133_npc_foot_range','stage5114_current_thought','stage5115_answerless_thought'):
        exe=out/name
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
            '-I',str(tests/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(tests/f'test_{name}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.137: navigation choices, draft tracking, source integrity and native runtime PASS')
