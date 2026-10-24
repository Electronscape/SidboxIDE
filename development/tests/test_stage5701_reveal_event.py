#!/usr/bin/env python3
"""Build and run the *real* generated linked-action ID range, not just 61."""
from pathlib import Path
import tempfile, subprocess
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
header=(root/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
engine=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
generator=(root/'gameadventuregen.cpp').read_text()
assert 'uint16_t reveal_action;' in header
assert 'repeat->reveal_action!=UINT16_MAX' in engine
assert '33000 + nodeIndex*3 + i' in generator
assert 'gameworlditems_set_active' in (root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
with tempfile.TemporaryDirectory(prefix='stage5701-') as td:
    out=Path(td)
    render_adventure_runtime(root,out,items=3)
    for event_id in (33000,33767):
        exe=out/f'reveal_{event_id}'
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
            '-DBTN_FIRE=8','-DBTN_LEFT=16','-DBTN_RIGHT=32',
            '-DREVEAL_EVENT='+str(event_id),
            '-I',str(tests/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(tests/'test_stage5701_reveal_event.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.70.1 linked actions 33000 and 33767 PASS')
