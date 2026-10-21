"""GCC-executed inventory display test + source integration checks (5.4g behaviour)."""
from pathlib import Path
import tempfile, subprocess
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='gamergirl-54f-') as tmp:
    output=Path(tmp)
    runtime=render_adventure_runtime(root,output,items=5,overrides={'GA_LINES':2})
    exe=output/'inventory_test'
    run=subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(runtime),
        str(runtime/'adventureruntime.c'),str(tests/'test_stage54f_inventory_visibility.c'),
        '-o',str(exe)],capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    result=subprocess.run([str(exe)],capture_output=True,text=True)
    assert result.returncode==0,result.stdout+result.stderr
    print(result.stdout.strip())
code=(root/'gamedesigner.cpp').read_text()
assert 'Add Item for NPC...' in code
assert 'Secret / quest item' in code
assert 'GameNpcItemIndex::requestedItems(project)' in code
assert 'QStringLiteral("hidden")' in code
scan=(root/'gamenpcitemindex.h').read_text()
for field in ['"npcs"','"items"','"nodes"','"requires"','"next"','"doneNode"', 'QDirIterator::Subdirectories']:
    assert field in scan,field
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
assert 'game_adventure_set_inventory_filter(gameplayer_inventory_visible)' in world
reg=(root/'gameworldsnapshot.h').read_text()
assert 'HAS_PLAYER_VISIBILITY' in reg
player=(root/'gameplayerprofile.h').read_text()
assert 'QStringLiteral("hidden")' in player
print('Stage 5.4f NPC discovery + shared player runtime registration contract: PASS')
