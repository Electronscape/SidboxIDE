#!/usr/bin/env python3
"""Stage 5.123 viewport persistence + compact status legend source contracts.

The Qt6 GUI build/render still requires the user's desktop Qt6 SDK.
"""
from pathlib import Path
import hashlib
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
s=(root/'gamefloweditor.cpp').read_text()
prior=(Path('/mnt/data/ide_251026_stage5122')/'gamefloweditor.cpp').read_text()
assert 'Build: 5.123.251026' in (root/'splashscreenwidget.cpp').read_text()

# Per-project JSON, independent All Worlds / per-world cameras, robust validation.
for fragment in (
    'struct FlowViewport {', 'QHash<QString,FlowViewport> viewports;',
    'QString lastWorld;', 'QStringLiteral("viewports")',
    'QStringLiteral("lastWorld")', 'QStringLiteral("version"),5',
    'world.isEmpty()?QStringLiteral("all-worlds"):QStringLiteral("world:")+world',
    'std::isfinite(zoom) && zoom>=0.04 && zoom<=5.0',
    'layout.viewports.insert(activeViewKey,FlowViewport{center,zoom})',
    'const QPointF center=view->mapToScene(view->viewport()->rect().center());',
    'QTimer::singleShot(0,&dialog,[&]() {',
    'viewSaveTimer.setInterval(450)',
    'view->onViewportChanged=scheduleViewSave;',
    'QObject::connect(view->horizontalScrollBar()',
    'QObject::connect(view->verticalScrollBar()',
    'captureView(); // save the PREVIOUS world\'s camera before changing filters',
    'restoreView(); // the selected world has its own saved pan and zoom',
    'captureView(); // also save the final camera when closing immediately',
):
    assert fragment in s, fragment
assert s.index('captureView(); // save the PREVIOUS world') < s.index('trackingView=false;\n        layout.lastWorld=worldSelect->currentData().toString();')
assert s.index('reloadGraph();\n    // Apply saved view') < s.index('dialog.exec();')

# The large instructional block no longer occupies the right inspector.
assert 'auto *help=new QLabel(QObject::tr("Drag cards to rearrange' not in s
assert 'auto *statusBox=new QFrame(&dialog);' in s
assert 'rootLayout->addWidget(statusBox);' in s
assert 'statusLayout->addWidget(status);' in s
assert 'statusLayout->addWidget(quickHelp);' in s
assert s.index('statusLayout->addWidget(status);') < s.index('statusLayout->addWidget(quickHelp);')
assert 'quickHelp->setToolTip(QObject::tr(' in s
assert 'View auto-saved' in s
assert 'rightLayout->addWidget(details,1);' in s

# Styling, wiring and runtime output deliberately remain unchanged.
for fragment in (
    'kind->setParentItem(card);kind->setPos(36,4)',
    'name->setParentItem(card);name->setPos(14,24)',
    ': QRectF(7,0,card->rect().width()-7,22),card',
    'label->setPos(12,5)',
    'existing.label+=QStringLiteral("\\n")+e.label;',
    'g.worlds.contains(destination) ? destination : QString()',
):
    assert fragment in prior and fragment in s
for name in ('gameadventuregen.cpp','gameadventureeditor.cpp',
             'gamefloweditor.h','ideglobaltheme.h','gamedesigner_export.cpp'):
    assert hashlib.sha256((root/name).read_bytes()).digest()==hashlib.sha256((root.parent/'ide_251026_stage5122'/name).read_bytes()).digest(),name

with tempfile.TemporaryDirectory(prefix='stage5123-') as td:
    output=render_adventure_runtime(root,Path(td))
    tests=root/'development/tests'
    for stem in ('stage5114_current_thought','stage5115_answerless_thought'):
        exe=output/stem
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
                        '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),
                        '-I',str(output),str(output/'adventureruntime.c'),
                        str(tests/f'test_{stem}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.123: saved view, compact status footer and native thought bubbles PASS')
