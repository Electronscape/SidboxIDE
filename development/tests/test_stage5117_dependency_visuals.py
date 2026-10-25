#!/usr/bin/env python3
"""Stage 5.117 dependency colours, minimal scoped UI changes and C regression.

Qt6 Widgets development headers are unavailable in the build container.
Source checks prove coverage and token order; native gcc exercises existing
Adventure game runtime to ensure this visual change didn't alter behavior.
"""
from pathlib import Path
import hashlib
import re
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root = Path(__file__).resolve().parents[2]
ed = (root/'gameadventureeditor.cpp').read_text()
qss = (root/'ideglobaltheme.h').read_text()
splash = (root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.117.251026' in splash
assert 'void adventureMarkDependent(QWidget *control)' in ed
assert 'control->setProperty("adventureGuard", true)' in ed
assert 'control->style()->unpolish(control)' in ed
assert 'control->style()->polish(control)' in ed
# Every Stage 5.116 availability toggle must tag its own target first.
lines = [line.strip() for line in ed.splitlines() if '->setEnabled(' in line]
assert len(lines) == 45, len(lines)
for line in lines:
    match = re.search(r'adventureMarkDependent\((.*?)\);\s*\1->setEnabled\(', line)
    assert match, f'Missing visual marker for guarded control: {line}'
for component in ('QComboBox','QLineEdit','QSpinBox','QDoubleSpinBox',
                  'QPushButton','QToolButton','QTextEdit','QCheckBox',
                  'QRadioButton','QGroupBox'):
    for state in (':enabled',':disabled'):
        assert f'{component}[adventureGuard="true"]{state}' in qss,(component,state)
# The replacement order matters: @advGreenBg before @advGreen, etc.
for prefix in ('Green','Red'):
    assert qss.index('{"@adv'+prefix+'Bg"') < qss.index('{"@adv'+prefix+'"')
assert 'const bool lightTheme =' in qss
assert 'Green outline = editable' in ed
assert 'Red border + faded background' in ed
assert 'Hover for the missing requirement' in ed
# All old dependency predicates are preserved verbatim (no game logic changed).
assert 'f.thought->setEnabled(selectable && hasSpeech && hasNext)' in ed
assert 'f.thoughtThis->setEnabled(canThinkNow)' in ed
assert 'f.npcModes[effect]->setEnabled(canEdit && hasTarget)' in ed
assert 'onCloseGroup->setEnabled(terminal)' in ed
assert 'const bool canIncrement=active && logic->currentData().toString()==QStringLiteral("all") && required>=2' in ed
assert 'const bool repeat=active && required>0 && repeatEnabled->isChecked()' in ed
assert 'Q_UNUSED(i); refreshChoiceControls();' in ed
with tempfile.TemporaryDirectory(prefix='stage5117-') as directory:
    out = render_adventure_runtime(root, Path(directory))
    tests = root/'development/tests'
    for stem in ('stage5114_current_thought','stage5115_answerless_thought'):
        exe=out/stem
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
                        '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),'-I',str(out),
                        str(out/'adventureruntime.c'),str(tests/f'test_{stem}.c'),'-o',str(exe)], check=True)
        subprocess.run([str(exe)], check=True)
print('Stage 5.117: visual guard contracts + thought bubble C runtime PASS')
