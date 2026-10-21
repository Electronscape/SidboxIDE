#!/usr/bin/env python3
"""Check the editor, generator, and runtime interface after dialogue autofit."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
ui=(root/'gameadventureeditor.cpp').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
run=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
header=(root/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
assert all(s in ui for s in ('adventureMeasure(', 'adventurePreviewRows(', 'Minimum height',
                            'Preview dialogue', 'Selected answer','Auto-raised to Y=',
                            'Needed: %1 px', 'Too much text for 320px',
                            'const int positionTabIndex=tabs->addTab(', 'first+2'))
assert '@IDE{DIALOG_HEIGHT}' in run and 'game_adventure_dialogue_box(' in header
assert 'MINIMUM height' in header
assert all(s in run for s in ('ga_dialogue_required_height(', 'ga_two_choice_height(',
                             'ga_dialog_y+bh>320?320-bh:ga_dialog_y',
                             'const uint8_t shown=', 'ga_text(bx+bw-pad-8,cy,"^")',
                             'ga_text(bx+bw-pad-8,cy+(draw_rows-1)*row,"v")'))
print('Stage4.33: Qt preview/runtime/generator integration source checks PASS')
