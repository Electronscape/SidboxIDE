#!/usr/bin/env python3
"""Stage 5.115 native GCC regression and source pipeline checks (no Qt required)."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root = Path(__file__).resolve().parents[2]
editor = (root/'gameadventureeditor.cpp').read_text()
rt = (root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
gen = (root/'gameadventuregen.cpp').read_text()
for marker in ['For an NPC speech with NO Answer', 'No Answer text is needed',
               'Shows this Player speech with the CURRENT NPC dialogue',
               'thoughtBubbleThis', 'if(selectedAnswer<0)',
               'Fire2-only dialogues have no highlighted answer']:
    assert marker in editor, marker
for marker in ['if(!has_answer) for(uint8_t i=0u;i<3u;++i)',
               'ga_thought_flags[index]&2u',
               'node->choices[i].label && node->choices[i].label[0]']:
    assert marker in rt, marker
assert 'thoughtChoiceFlags << QStringLiteral' in gen
assert 'Build: 5.115.251026' in (root/'splashscreenwidget.cpp').read_text()
with tempfile.TemporaryDirectory(prefix='sidbox5115-') as td:
    out = render_adventure_runtime(root, Path(td))
    exe = out/'stage5115'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-I',str(root/'development/tests/stage429_mock_api'),
        '-I',str(out),str(out/'adventureruntime.c'),
        str(root/'development/tests/test_stage5115_answerless_thought.c'),
        '-o',str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
print('Stage 5.115: editor + generator + runtime wiring PASS')
