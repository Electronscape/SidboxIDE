#!/usr/bin/env python3
"""Native GCC regression and editor/generator integration (no Qt needed)."""
from pathlib import Path
import re
import subprocess, tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
editor=(root/'gameadventureeditor.cpp').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
rt=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
header=(root/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
for marker in ['"thoughtBubble"','"thoughtBubbleThis"','Use as thought bubble (show with next dialogue)',
               'Use as thought bubble (show with this dialogue)','fields[i].thoughtThis->setChecked(false)',
               'fields[i].thought->setChecked(false)']:
    assert marker in editor,marker
for marker in ['"thoughtBubbleThis"','thoughtNext ? 1 : (thoughtThis ? 2 : 0)','THOUGHT_CHOICE_FLAGS']:
    assert marker in gen,marker
for marker in ['ga_is_thought_this(node,choice)','ga_refresh_thought_for_choice()',
               'ga_inherited_thought','ga_trigger_message_mode=2u']:
    assert marker in rt,marker
assert 'bit 1 means show on THIS dialogue' in header
assert int(re.search(r'Build: 5\.(\d+)\.', (root/'splashscreenwidget.cpp').read_text()).group(1)) >= 114
with tempfile.TemporaryDirectory(prefix='sidbox5114-') as td:
    out=render_adventure_runtime(root,Path(td))
    exe=out/'stage5114'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-I',str(root/'development/tests/stage429_mock_api'),
        '-I',str(out),str(out/'adventureruntime.c'),
        str(root/'development/tests/test_stage5114_current_thought.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.114: editor + generator + runtime wiring PASS')
