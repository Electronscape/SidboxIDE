"""Source-level regression checks for Stage 3.90; Qt GUI still needs Fedora test."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
export = (root / 'gamedesigner_export.cpp').read_text()
editor = (root / 'gametilemap.cpp').read_text()
world = (root / 'idelibs/codehelpers/game/worldobjects.c').read_text()
hdr = (root / 'idelibs/codehelpers/game/worldobjects.h').read_text()
assert '/* COLLECTABLES — WHAT THIS CODE DOES' in export
assert "'user' carries your own game state" in export
assert 'The helper decides WHICH object was touched' in export
assert 'gameworlditems_check(player_physics.x100 / 100' in export
assert 'on_pickup, &score);' in export
assert 'p->break_stomp_armed = 1' in world
assert 'const uint8_t valid_hit = (uint8_t)(best_touch || p->break_stomp_armed)' in world
assert 'uint8_t break_stomp_armed;' in hdr
assert 'loopForm->addRow(tr("Center"), loopCenterRow)' in editor
assert 'loopCenterRow->addWidget(loopX, 1)' in editor
assert 'loopCenterRow->addWidget(loopY, 1)' in editor
assert 'loopForm->addRow(tr("Radius"), loopRadiusRow)' in editor
assert 'm_stampTabs->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding)' in editor
assert 'Sonic-style' not in editor
assert 'Yellow dot = loop entry/exit.' in editor
assert 'tr("Loop Tracks — optional' not in editor
print('PASS: generated collectable tutorial, jump-only stomps, compact loop pane and narrowable sidebar')
