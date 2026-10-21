"""Strict GCC regression for dynamic quantity-driven backpack visibility."""
from pathlib import Path
import tempfile, subprocess
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
with tempfile.TemporaryDirectory(prefix='gamergirl-54g-') as tmp:
    output=Path(tmp)
    runtime=render_adventure_runtime(root,output,items=5,overrides={'GA_LINES':2})
    exe=output/'inventory_test'
    run=subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',
        '-I',str(tests/'stage429_mock_api'),'-I',str(runtime),
        str(runtime/'adventureruntime.c'),str(tests/'test_stage54g_inventory_reveal.c'),
        '-o',str(exe)],capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    result=subprocess.run([str(exe)],capture_output=True,text=True)
    assert result.returncode==0,result.stdout+result.stderr
    print(result.stdout.strip())
code=(root/'gamedesigner.cpp').read_text()
assert 'Secret / quest item' in code
assert 'Items with quantity 0 never appear' in code
assert 'once owned, this item appears in the backpack' in code
assert 'QStringLiteral("hidden")' in code
runtime=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
assert 'return i < ga_item_count && ga_counts[i] != 0u;' in runtime
assert 'ga_inventory_clamp_offset();' in runtime
print('Stage 5.4g editor wording and .sbpi hidden-metadata compatibility: PASS')
