#!/usr/bin/env python3
"""Stage 5.135: unified palette INDEX selection; do not alter .pal editing.

Qt6 graphical acceptance remains a separate Fedora test. The C runtime
checks confirm IDE palette UI standardisation didn't change generated games.
"""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
selector=(root/'gamepalettepicker.h').read_text()
assert 'namespace SidboxPalettePicker' in selector
assert 'return picker.exec() == QDialog::Accepted ? selected : -1;' in selector
assert 'selected = index;' in selector
assert 'cell->setFixedSize(28, 28);' in selector
assert 'swatch(22, 22)' in selector
assert 'cells->setSpacing(3);' in selector
assert 'index / 16, index % 16' in selector
assert 'index == 0 && !allowIndexZero' in selector
assert 'border: 2px solid #f5c747;' in selector
assert 'QDialogButtonBox::Cancel' in selector
assert 'colour.name(QColor::HexArgb)' in selector
assert 'QColorDialog' not in selector

for filename, marker in [
    ('gameadventureeditor.cpp','chooseAdventurePaletteIndex'),
    ('gamehudeditor.cpp','choosePaletteIndex'),
    ('gametitlescreeneditor.cpp','chooseTitleColour'),
    ('gamedesigner.cpp','Pick flash foreground CLUT colour'),
    ('gamedesigner.cpp','Choose reserved foreground palette index'),
]:
    src=(root/filename).read_text()
    assert '#include "gamepalettepicker.h"' in src
    assert 'SidboxPalettePicker::chooseIndex(' in src
    assert marker in src

adv=(root/'gameadventureeditor.cpp').read_text()
assert adv.count('chooseAdventurePaletteIndex(&dialog,foregroundPalette,')==3
hud=(root/'gamehudeditor.cpp').read_text()
assert 'choosePaletteIndex(&dialog,canvas->textColors,doc.colour' in hud
assert 'choosePaletteIndex(&dialog,canvas->textColors,doc.outlineColour' in hud
title=(root/'gametitlescreeneditor.cpp').read_text()
assert 'editTitlePalette(QWidget *parent,QVector<QRgb> &clut)' in title
assert 'QColorDialog::ShowAlphaChannel' in title, 'ARGB palette editing remains distinct from selecting a CLUT index'
world=(root/'gamedesigner.cpp').read_text()
assert 'SidboxGamePaletteEditor' in world, '.pal editor remains the resource editor'
assert 'maskIndex->setValue(selected)' in world
assert 'chosenHazardColour = selected;' in world
# GUI Designer keeps its special copy-index, copy-ARGB and use-default controls.
gui=(root/'guidesigner.cpp').read_text()
for marker in ('Copy pen index','Copy ARGB','Use default (-1)','Use selected pen',
               'QToolButton:checked { border: 2px solid #f5c747; }'):
    assert marker in gui
assert 'Build: 5.135.251026' in (root/'splashscreenwidget.cpp').read_text()

with tempfile.TemporaryDirectory(prefix='cg5135-') as temp:
    out=render_adventure_runtime(root,Path(temp),items=1)
    tests=root/'development/tests'
    for name in ('stage5133_npc_foot_range','stage5114_current_thought',
                 'stage5115_answerless_thought'):
        exe=out/name
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
            '-I',str(tests/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(tests/f'test_{name}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.135 shared CLUT selector & native runtime regressions PASS')
