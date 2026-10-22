#!/usr/bin/env python3
from pathlib import Path
import subprocess, tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='cg-stage531-') as temp:
    out=Path(temp)
    render_adventure_runtime(root,out,items=12,overrides={'GA_LINES':'6'})
    exe=out/'test'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-DBTN_FIRE=0x08u','-DBTN_LEFT=0x10u','-DBTN_RIGHT=0x20u',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'), str(tests/'test_stage531_inventory_runtime.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
source=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
assert '*cg_fire2_player->x100/100+cg_fire2_player->offset_x' in source
assert '*cg_fire2_player->y100/100+cg_fire2_player->offset_y' in source
assert 'cg_fire2_player=player' in source
assert 'cg_fire2_player=0' in source
story=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert 'game_adventure_save_drops(cg_saved_world_drops)' in story
assert 'game_adventure_restore_drops(cg_saved_world_drops)' in story
assert 'game_adventure_text_padding(@IDE{DIALOG_PADDING}u)' in story
editor=(root/'gameadventureeditor.cpp').read_text()
assert 'Dialogue box padding (0 / 8 px)' in editor
assert 'Build: 5.33.221026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.31: collision geometry and generated-world integrations PASS')
