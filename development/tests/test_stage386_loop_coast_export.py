"""Stage 3.86: static integration checks for no-friction loop exits."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
model = (r/'gametilemapmodel.cpp').read_text()
editor = (r/'gametilemap.cpp').read_text()
header = (r/'gametilemap.h').read_text()
c = (r/'idelibs/codehelpers/game/tilemap.c').read_text()
h = (r/'idelibs/codehelpers/game/tilemap.h').read_text()
assert 'bool coastAfterExit = false;' in header
assert 'v.insert(QStringLiteral("coastAfterExit"), loop.coastAfterExit)' in model
assert 'v.value(QStringLiteral("coastAfterExit")).toBool(false)' in model
assert 'l.coastAfterExit!=r.coastAfterExit' in editor
assert 'loopCoast->setChecked(l.coastAfterExit)' in editor
assert 'l.coastAfterExit=loopCoast->isChecked()' in editor
assert 'connect(loopCoast,&QCheckBox::toggled' in editor
assert 'QByteArray::number(l.coastAfterExit ? 1 : 0)' in editor
assert 'uint8_t coast_after_exit;' in h
assert 'uint8_t loop_coast_active;' in h
assert 'p->loop_coast_active = loop->coast_after_exit != 0;' in c
assert 'if (buttons & (BTN_LEFT | BTN_RIGHT))' in c
assert 'p->loop_coast_active = 0; /* Wall collision' in c
assert 'if (p->force_vx100 && damping && !p->loop_coast_active)' in c
print('PASS: Stage 3.86 UI, JSON, C generator, runtime friction override, legacy default')
