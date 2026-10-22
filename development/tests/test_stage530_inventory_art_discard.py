#!/usr/bin/env python3
"""Test actual rendered Adventure runtime with mock gfx and regressions."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='gamergirl-530-') as temp:
    out=Path(temp)
    render_adventure_runtime(root,out,items=2,overrides={'GA_LINES': '6'})
    exe=out/'test'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=0x08u',
                    '-I',str(tests/'stage429_mock_api'),'-I',str(out),
                    str(out/'adventureruntime.c'),str(tests/'test_stage530_inventory_art_discard.c'),
                    '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)

editor=(root/'gameadventureeditor.cpp').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
rule=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert 'editAdventureInventoryIcon(' in editor
assert 'iconCells' in editor and 'icon2x2' in editor
assert 'dialogPadding' in editor and 'Dialogue box padding' in editor
assert 'ITEM_STYLE_ROWS' in gen and 'ITEM_STYLE_ROWS' in rule
assert 'DIALOG_PADDING' in gen and 'DIALOG_PADDING' in rule
assert 'requiredItemNames(payload, projectRoot)' in gen
assert 'game_adventure_item_styles(item_styles, GAME_ADVENTURE_STORY_ITEM_COUNT)' in rule
assert 'game_adventure_text_padding(@IDE{DIALOG_PADDING}u)' in rule
assert 'Build: 5.32.221026' in (root/'splashscreenwidget.cpp').read_text()
print('Stage 5.30: editor+generator/runtime integration invariants PASS')
