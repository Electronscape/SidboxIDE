"""Static integration checks for Stage 3.80 without a Qt SDK."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
model = (r/'gametilemapmodel.cpp').read_text()
editor = (r/'gametilemap.cpp').read_text()
header = (r/'gametilemap.h').read_text()
c = (r/'idelibs/codehelpers/game/tilemap.c').read_text()
h = (r/'idelibs/codehelpers/game/tilemap.h').read_text()
assert 'int downhillBoost100 = 0;' in header
assert 'v.insert(QStringLiteral("downhillBoost100"), loop.downhillBoost100)' in model
assert 'toInt(0)' in model[model.index('loop.downhillBoost100 ='):]
assert 'loop.downhillBoost100 > 200' in model
assert 'l.downhillBoost100!=r.downhillBoost100' in editor
assert 'm_map.loops[i]=l;' in editor
assert 'loopBoostSlider->setRange(0, 200)' in editor
assert 'loopBoostSlider->setValue(l.downhillBoost100)' in editor
assert 'l.downhillBoost100=loopBoostSlider->value()' in editor
assert 'const QIcon loopIcon(loopIconPixmap)' in editor
assert 'loopList->setIconSize(QSize(16, 16))' in editor
assert 'new QListWidgetItem(loopIcon' in editor
assert 'm_stampTabs->addTab(loopPane, loopIcon' in editor
assert 'QByteArray::number(l.downhillBoost100)' in editor
assert 'uint16_t downhill_boost100' in h
assert 'if (!loop->downhill_boost100)' in c
assert 'p->loop_phase >= 32768' in c and 'p->loop_phase <= -32768' in c
assert 'p->loop_speed100 += loop->downhill_boost100' in c
assert 'p->loop_speed100 -= loop->downhill_boost100' in c
assert 'if (p->loop_speed100 > 3200)' in c
print('PASS: Stage 3.80 saved loop, UI, icons, codegen and runtime links')
