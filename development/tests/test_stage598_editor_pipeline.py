#!/usr/bin/env python3
"""Validate IDE/project/export/runtime wiring without requiring Qt6."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
def read(path):return (root/path).read_text()
editor=read('gameadventureeditor.cpp')
generator=read('gameadventuregen.cpp')
rule=read('idelibs/codehelpers/game/gameadventure.rulec')
runtime=read('idelibs/codehelpers/game/adventureruntime.rulec')
header=read('idelibs/codehelpers/game/adventureruntime.ruleh')
for v in ['thoughtBubble','thoughtSkinIndices','thoughtSkinFlips','thoughtX','thoughtY','thoughtWidth','thoughtHeight']:
    assert f'"{v}"' in editor,v
for symbol in ['thoughtChoiceFlags','THOUGHT_CHOICE_FLAGS','THOUGHT_SKIN_CELLS','THOUGHT_SKIN_FLIPS','THOUGHT_X','THOUGHT_Y','THOUGHT_WIDTH','THOUGHT_HEIGHT']:
    assert symbol in generator,symbol
for symbol in ['game_adventure_thought_choices','game_adventure_thought_box']:
    assert symbol in rule and symbol in header and symbol in runtime,symbol
assert 'Use as thought bubble' in editor
assert 'Dialogue + Thought Atlas' in editor
assert 'ga_trigger_message_mode==2u' in runtime
assert 'ga_set_thought(c->reply)' in runtime
assert '@IDE{THOUGHT_CHOICE_FLAGS}' in rule
assert re.search(r'Build: 5\.(?:98|99)\.241026',read('splashscreenwidget.cpp'))
for name in ['THOUGHT_CHOICE_FLAGS','THOUGHT_SKIN_CELLS','THOUGHT_SKIN_FLIPS','THOUGHT_X','THOUGHT_Y','THOUGHT_WIDTH','THOUGHT_HEIGHT']:
    assert f'@IDE{{{name}}}' in rule
    assert f'"{name}"' in generator
assert not re.search(r'\bstd::',runtime)
print('Stage 5.98: 26+ editor/export/runtime source checks PASS')
