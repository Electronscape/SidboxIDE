#!/usr/bin/env python3
"""Stage 5.122 flow relationship audit. Source-only UI checks plus native game regressions.

The graph uses Qt6, so its visual behaviour must still be checked in the IDE.
"""
from pathlib import Path
import hashlib
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
flow=(root/'gamefloweditor.cpp').read_text()
generator=(root/'gameadventuregen.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.122.251026' in splash

# Only run relevant saved actions, including enemy reward drops, and reject
# world names that the exporter rejects on a case-sensitive TFCard/project.
for needle in ('targetActive && targetSupported', 'const bool targetActive=targetAction==QStringLiteral("enable")',
               'type==QStringLiteral("enemy")',
               'obj.value(QStringLiteral("pickupKind")).toInt(1)==3',
               'unsupported remote action target',
               'type==QStringLiteral("breakable") ||',
               'g.nodes.at(rewardNode).kind==QStringLiteral("Collectable pickup")',
               'g.worlds.contains(destination) ? destination : QString()'):
    assert needle in flow,needle
assert 'r.objectType != QStringLiteral("breakable") && r.objectType != QStringLiteral("enemy")' in export
assert 'r->objectType != QStringLiteral("trigger")' in export

# Saved partial GIVE controls are not generated as runnable branches.
assert 'const int partialAction=-1;' in generator
assert '.arg(-1)' in generator
assert 'next(exchange.value(QStringLiteral("wrongNext"))' in flow
assert 'partial hand-ins are silent in the game runtime' in flow
assert 'qMakePair("partialNext","Partial items")' not in flow
assert 'for (const auto &key : {"wrongTargetObjectId","partialTargetObjectId"})' not in flow
assert 'Repeated wrong item (third offer only)' in flow

# Grouped/parallel actions must retain all labels on hover AND click.
assert 'existing.label+=QStringLiteral("\\n")+e.label;' in flow
assert 'existing.path->setToolTip(existing.label+' in flow
assert 'edges.at(selectedEdge).label' in flow
assert 'display.edges[shared.value(key)].label+=QStringLiteral("\\n")+edge.label;' in flow
assert 'Selected connection(s): %1' in flow

# Preserve the previous stage's card appearance, actual generator and ABI.
prior=Path('/mnt/data/ide_251026_stage5121')
if prior.exists():
    for name in ('gameadventuregen.cpp','gameadventureeditor.cpp',
                 'gamefloweditor.h','ideglobaltheme.h'):
        assert hashlib.sha256((root/name).read_bytes()).digest()==hashlib.sha256((prior/name).read_bytes()).digest(),name
    before=(prior/'gamefloweditor.cpp').read_text()
    for needle in ('kind->setParentItem(card);kind->setPos(36,4)',
                   'name->setParentItem(card);name->setPos(14,24)',
                   'expandableTrigger ? 58 : 25',
                   ': QRectF(7,0,card->rect().width()-7,22),card',
                   'label->setPos(12,5)'):
        assert needle in before and needle in flow,needle

with tempfile.TemporaryDirectory(prefix='stage5122-flow-') as temp:
    output=render_adventure_runtime(root,Path(temp))
    tests=root/'development/tests'
    for stem in ('stage5114_current_thought','stage5115_answerless_thought'):
        exe=output/stem
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
                        '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),
                        '-I',str(output),str(output/'adventureruntime.c'),
                        str(tests/f'test_{stem}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.122: flow connection audit and native thought-bubble regressions PASS')
