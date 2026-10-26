#!/usr/bin/env python3
"""Stage 5.139: asset import/export, canvas gestures, and help/validation.

This checks the Qt source flow, with native C regressions below for unaffected
runtime integrations. Fedora Qt 6.11.2 GUI acceptance remains necessary.
"""
from pathlib import Path
import subprocess
import tempfile
import hashlib
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
prior=Path('/mnt/data/ide_251026_stage5138')
src={name:(root/name).read_text() for name in (
    'ppbcodec.cpp','ppbcodec.h','mainwindow.cpp','gamedesigner.cpp',
    'gametilemap.cpp','gamefloweditor.cpp','gameanimationeditor.cpp',
    'gametitlescreeneditor.cpp','splashscreenwidget.cpp')}

assert 'Build: 5.139.251026' in src['splashscreenwidget.cpp']
assert 'bool exportPng(const QString &path, const Picture &picture' in src['ppbcodec.h']
codec=src['ppbcodec.cpp']
start=codec.index('bool exportPng('); end=codec.index('bool fromImage(', start)
fn=codec[start:end]
for needle in ('QSaveFile file(path);','QImageWriter writer(&file, "png")',
               'writer.write(picture.indexed)', 'file.cancelWriting()', 'file.commit()',
               'picture.indexed.colorCount() != 256'):
    assert needle in fn, needle
assert 'picture.indexed.convertToFormat' not in fn

view=src['mainwindow.cpp']; start=view.index('class SidboxPpbView final')
end=view.index('// Do not accidentally interpret binary SIDBOX game assets',start)
viewer=view[start:end]
for needle in ('Export PNG...', 'files/ppbPngExportLastDirectory',
               'SidboxPpb::exportPng(destination, picture, &exportError)',
               'QFileDialog::getSaveFileName','QMessageBox::warning',
               'QMessageBox::information','Qt::MiddleButton','Qt::Key_1',
               'Qt::Key_F','Qt::Key_Plus','Qt::Key_Minus'):
    assert needle in viewer, needle
assert 'PPB was not modified' in viewer
assert 'SaveFileName' in viewer and 'if (destination.isEmpty()) return;' in viewer

resource=src['gamedesigner.cpp']
for needle in ('Export This PPB as PNG...',
               'SidboxPpb::exportPng(destination, picture, &issue)',
               'files/ppbPngExportLastDirectory',
               'files/gameResourceImportLastDirectory',
               'files/pngImportLastDirectory',
               'Tile atlases must use a .ppb file.'):
    assert needle in resource, needle
assert 'if (path.isEmpty()) return;' in resource
assert 'if (pngPath.isEmpty()) return;' in resource

for name,needles in {
    'gametilemap.cpp':['Qt::ControlModifier', 'Qt::Key_0','Qt::Key_F',
                       'Qt::Key_Equal','Middle-drag: pan'],
    'gamefloweditor.cpp':['flowCanvasShortcut(Qt::CTRL | Qt::Key_Plus',
                          'flowCanvasShortcut(Qt::CTRL | Qt::Key_1','flowCanvasShortcut(Qt::CTRL | Qt::Key_F'],
    'gameanimationeditor.cpp':['setToolTip(QObject::tr("Wheel or Ctrl+/-',
                               'void keyPressEvent(QKeyEvent *event) override',
                               'Qt::Key_1','Qt::MiddleButton'],
    'gametitlescreeneditor.cpp':['void keyPressEvent(QKeyEvent *event) override',
                                 'Qt::Key_1','Qt::Key_F','Qt::MiddleButton'],
}.items():
    for needle in needles:
        assert needle in src[name], (name,needle)

# The full .pal editor and all game-facing/runtime templates are byte-for-byte identical.
for name in ('gamepaletteeditor.cpp','gamepaletteeditor.h','gameadventuregen.cpp',
             'idelibs/codehelpers/game/adventureruntime.rulec',
             'idelibs/codehelpers/game/adventureruntime.ruleh'):
    assert hashlib.sha256((root/name).read_bytes()).digest() == \
           hashlib.sha256((prior/name).read_bytes()).digest(),name

with tempfile.TemporaryDirectory(prefix='cg5139-test-') as td:
    generated=render_adventure_runtime(root,Path(td),items=1)
    tests=root/'development/tests'
    for name in ('stage5133_npc_foot_range','stage5114_current_thought',
                 'stage5115_answerless_thought'):
        exe=generated/name
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
            '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),'-I',str(generated),
            str(generated/'adventureruntime.c'),str(tests/f'test_{name}.c'),
            '-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.139 source, unchanged runtime, and three compiled C regressions PASS')
