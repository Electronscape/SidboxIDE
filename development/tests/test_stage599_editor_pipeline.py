#!/usr/bin/env python3
"""Static integration guards for native dialogue typography and layering."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
ed=(r/'gameadventureeditor.cpp').read_text()
gen=(r/'gameadventuregen.cpp').read_text()
rule=(r/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
rt=(r/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
hdr=(r/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
assert '#include "guidesigner_detail.h"' in ed
assert 'GuiDesignerDetail::drawCoderGirlText' in ed
assert 'Qt::FastTransformation' in ed
for k in ['dialogFontScaleX','dialogFontScaleY','thoughtFontScaleX','thoughtFontScaleY','thoughtAboveDialog']:
    assert f'old.value("{k}")' in ed,k
    assert f'result.insert("{k}"' in ed,k
    assert f'"{k}"' in gen,k
for field in ['DIALOG_FONT_SCALE_X','DIALOG_FONT_SCALE_Y','THOUGHT_FONT_SCALE_X','THOUGHT_FONT_SCALE_Y','THOUGHT_ABOVE']:
    assert f'@IDE{{{field}}}' in rule,field
assert 'game_adventure_dialogue_typography(' in rt
assert 'game_adventure_dialogue_typography(' in hdr
assert 'if(!ga_thought_on_top)ga_draw_thought();' in rt
assert 'if(ga_thought_on_top)ga_draw_thought();' in rt
assert 'if(thoughtsOnTop){paintDialogue();paintThought();}' in ed
assert 'else {paintThought();paintDialogue();}' in ed
assert 'screenPreview->thoughtAboveDialog=thoughtsOnTop;' in ed
assert 'Build: 5.99.241026' in (r/'splashscreenwidget.cpp').read_text()
print('Stage 5.99: editor/generator/preview/runtime integration checks PASS')
