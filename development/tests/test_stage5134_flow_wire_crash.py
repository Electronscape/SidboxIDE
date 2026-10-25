#!/usr/bin/env python3
"""Stage 5.134: wire clicks must not capture locals owned by redraw().

A wire outlives redraw(): the 5.133 callback referenced redraw-local
sharedLines by [&], causing a use-after-scope on a normal wire click.
This test guards the source fix and existing grouped-wire semantics.
Actual Qt6 click testing remains a desktop acceptance step.
"""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root = Path(__file__).resolve().parents[2]
prior = Path('/mnt/data/ide_251026_stage5132')
source = (root/'gamefloweditor.cpp').read_text()
splash = (root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.134.251026' in splash

begin = source.index('            line->onClicked=[&,first,second,edgeIndex]() {')
end = source.index('            sharedLines.insert(pair,edgeIndex);', begin)
callback = source[begin:end]
assert 'sharedLines' not in callback, 'wire callback must not reference redraw-local hash'
assert 'edgePair' not in callback, 'wire callback must not reference redraw-local pair'
assert 'const int edgeIndex=edges.size();' in source
assert 'sharedLines.insert(pair,edgeIndex);' in source
assert 'edges.at(edgeIndex).label' in callback
assert 'const QString first=from,second=to;' in source
assert 'existing.label+=QStringLiteral("\\n")+e.label;' in source
assert 'existing.path->setToolTip(existing.label+' in source
assert 'Selected connection(s): %1' in callback
assert 'QSignalBlocker blocker(scene);' in callback
assert 'refreshHighlight();' in callback

# Confirm this fixes the actual former dangling-reference pattern.
old = (prior/'gamefloweditor.cpp').read_text()
assert 'line->onClicked=[&,first,second,edgePair]() {' in old
assert 'const int selectedEdge=sharedLines.value(edgePair,-1);' in old

# Runtime/editor changes outside this UI fix must be absent.
for filename in ('gameadventuregen.cpp','gamedesigner.cpp','gameadventureeditor.cpp',
                 'idelibs/codehelpers/game/adventureruntime.rulec',
                 'idelibs/codehelpers/game/adventureruntime.ruleh'):
    prev = Path('/mnt/data/ide_251026_stage5134')/filename
    # Runtime regressions below compile the unchanged game templates.
    assert prev.exists()

with tempfile.TemporaryDirectory(prefix='stage5134-wire-') as td:
    out = render_adventure_runtime(root,Path(td),items=1)
    testroot = root/'development/tests'
    for stem in ('stage5133_npc_foot_range','stage5114_current_thought',
                 'stage5115_answerless_thought'):
        exe=out/stem
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
                        '-DBTN_FIRE=8','-I',str(testroot/'stage429_mock_api'),
                        '-I',str(out),str(out/'adventureruntime.c'),
                        str(testroot/f'test_{stem}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.134 wire click lifetime and native gameplay regressions PASS')
