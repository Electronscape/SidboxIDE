from pathlib import Path
import tempfile,subprocess
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='stage5712-') as td:
    out=Path(td);render_adventure_runtime(root,out,items=2)
    exe=out/'close_reward'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(tests/'test_stage5712_close_reward.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
E=(root/'gameadventureeditor.cpp').read_text()
G=(root/'gameadventuregen.cpp').read_text()
R=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert 'Give item when dialogue closes' in E and 'closeGiveItem' in E
assert 'legacyCloseGive' in E and 'if (noAnswers)' in E
assert 'setEnabled(hasAnswer)' in E
assert 'CLOSE_GIFT_ROWS' in G and 'closeGiftRows' in G
assert 'game_adventure_close_gifts(close_gifts' in R
assert 'game_adventure_save_close_gifts' in R and 'game_adventure_restore_close_gifts' in R
assert 'Build: 5.71.5.241026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.71.2 generator/editor/persistence checks PASS')
