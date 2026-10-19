"""Stage 3.88 source wiring checks for per-loop coast falloff."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
model = (r / 'gametilemapmodel.cpp').read_text()
editor = (r / 'gametilemap.cpp').read_text()
header = (r / 'gametilemap.h').read_text()
c = (r / 'idelibs/codehelpers/game/tilemap.c').read_text()
h = (r / 'idelibs/codehelpers/game/tilemap.h').read_text()
assert 'int coastFalloffPermille = 0;' in header
assert 'v.insert(QStringLiteral("coastFalloffPermille"), loop.coastFalloffPermille)' in model
assert 'v.value(QStringLiteral("coastFalloffPermille")).toInt(0)' in model
assert 'loop.coastFalloffPermille > 200' in model
assert 'l.coastFalloffPermille!=r.coastFalloffPermille' in editor
assert 'loopFalloffSlider->setRange(0, 200)' in editor
assert 'loopFalloffSlider->setValue(l.coastFalloffPermille)' in editor
assert 'l.coastFalloffPermille=loopFalloffSlider->value();' in editor
assert 'QByteArray::number(l.coastFalloffPermille) + "},\\n";' in editor
assert 'uint16_t coast_falloff_permille;' in h
assert 'uint16_t loop_coast_falloff_permille;' in h
assert 'p->loop_coast_falloff_permille = p->loop_coast_active' in c
assert 'p->force_vx100 = (int32_t)((int64_t)p->force_vx100 * (1000 - falloff) / 1000);' in c
assert 'if (p->force_vx100 && damping && !p->loop_coast_active)' in c
assert 'p->loop_coast_active = 0; /* Wall collision' in c
print('PASS: Stage 3.88 editor, save/load, export, runtime falloff, legacy defaults')
