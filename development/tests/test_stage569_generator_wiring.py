"""Source wiring coverage for Stage 5.69: editor/serializer/gen/World state."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
editor=(root/'gameadventureeditor.cpp').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
world=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
code=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
head=(root/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
for key in ('wrongRepeatEnabled','wrongRepeatItem','wrongRepeatFirst','wrongRepeatSecond',
            'wrongRepeatThird','wrongRepeatLater','wrongRepeatAction',
            'wrongRepeatTargetObjectId','wrongRepeatTargetAction'):
    assert key in editor and key in gen, key
for field in ('WRONG_REPEAT_ROWS','WRONG_REPEAT_COUNT'):
    assert field in gen and ('@IDE{'+field+'}') in world,field
for symbol in ('game_adventure_wrong_repeat_rules','game_adventure_save_wrong_repeats',
               'game_adventure_restore_wrong_repeats'):
    assert symbol in head and symbol in code and symbol in world,symbol
assert 'exchange.insert("wrongRepeatItem",-1)' in editor
assert 'for(const char *repeatKey:' in editor
assert 'if (*count<4u) ++*count;' in code
assert 'Build: 5.71.4.241026' in (root/'splashscreenwidget.cpp').read_text()
assert '2048' in (root/'mainwindow.cpp').read_text()
print('Stage 5.69 editor/generator/quest-state wiring PASS')
