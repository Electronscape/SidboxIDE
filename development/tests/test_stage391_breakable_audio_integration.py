"""Stage 3.91 structural coverage for GUI/save/export audio integration."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
ui=(root/'gamedesigner.cpp').read_text()
header=(root/'gamedesigner.h').read_text()
load=(root/'gamedesigner_project.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
helper=(root/'idelibs/codehelpers/game/worldobjects.c').read_text()
for key in ('sfxBreakHit', 'sfxBreakBounce', 'sfxBreakFinish'):
    assert key in header
    assert f'soundPicker(old.{key})' in ui
    assert f'r.{key} = ' in ui
    assert f'object.value(QStringLiteral("{key}"))' in load
    assert f'object.insert(QStringLiteral("{key}"),' in load
    assert f'obj->{key}' in export
    assert f'r.{key}' in export
for flag in ('break_hit_triggered','break_bounce_triggered','break_triggered'):
    assert f'{flag})' in export
    assert flag in helper
assert 'cSfxCall(r.sfxBreakHit, pos, r.audioRadius)' in export
assert 'cSfxCall(r.sfxBreakBounce, pos, r.audioRadius)' in export
assert 'cSfxCall(r.sfxBreakFinish, pos, r.audioRadius)' in export
assert 'usedSfx.insert(id)' in export
print('PASS: Stage 3.91 audio GUI, save/load, resource validation and C export')
