#!/usr/bin/env python3
"""Stage 5.120/5.121: compact full-width bands; kind-first root cards.
Preserves all expandable card geometry and the older flow runtime.
"""
from pathlib import Path
import hashlib
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
source=(root/'gamefloweditor.cpp').read_text()
assert 'Build: 5.121.251026' in (root/'splashscreenwidget.cpp').read_text()
# Static root cards shade the kind label on the FIRST row (e.g. WORLD)
# rather than the second row (forest). Trigger cards keep the tall header.
assert 'expandableTrigger ? QRectF(7,0,card->rect().width()-7,60)' in source
assert ': QRectF(7,0,card->rect().width()-7,22)' in source
# Both sorts of nested members (manual-group and nested array) are covered.
assert source.count('expandableTrigger ? 58 : 25')==2
assert 'QRectF(0,0,width,27),card' in source  # non-expandable choice drilldown
# Group/array cards retain their 70px header; trigger events retain their rows.
assert source.count('QRectF(0,0,card->rect().width(),70),card')==1
assert source.count('QRectF(0,0,sub->rect().width(),70),sub')==1
for text in ('const bool expanded=!groups.value(id).expanded;',
             'card->setExpandableTrigger(true);',
             '94.0 + node.triggerEvents.size()*TriggerRowHeight',
             'drawTriggerEventRows(child,member,theme',
             'drawTriggerEventRows(mini,member,theme'):
    assert text in source,text
# No saved-layout, dependency guard or generated runtime changes.
base_hashes={
    'gameadventureeditor.cpp':'ae2b99c6158b1398735d627e3e571cfcfc3f9f6195e0efe39671150b6661314c',
    'gameadventuregen.cpp':'7bf96fc37865970b76d5b0624b43d6ec119822d75aff0afff4ae7d05a03b2a2e',
    'gamefloweditor.h':'ce8b1ecafcbd7d5b6d8966a7aa887fd7b0bca43f7c3dbac086f21895f4329014',
    'idetheme.h':'b0264a11741affe5d3fdcdbf4f0769b616d84d5e250d55295d68a2e8e8a4f330',
    'ideglobaltheme.h':'0f9cc4fa8d47ae859a92b1c1bf28c595c9d6e404862c8c4fff561c170acd3df8',
}
for file,expected in base_hashes.items():
    assert hashlib.sha256((root/file).read_bytes()).hexdigest()==expected,file
with tempfile.TemporaryDirectory(prefix='stage5120-') as temp:
    output=render_adventure_runtime(root,Path(temp))
    tests=root/'development/tests'
    for name in ('stage5114_current_thought','stage5115_answerless_thought'):
        exe=output/name
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
                        '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),
                        '-I',str(output),str(output/'adventureruntime.c'),
                        str(tests/f'test_{name}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.121 compact header layout and native thought-bubble regressions: PASS')
