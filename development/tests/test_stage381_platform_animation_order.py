#!/usr/bin/env python3
"""Ensure generated animation uses final world-contact results, not tile physics alone."""
from pathlib import Path

base = Path(__file__).resolve().parents[2]
source = (base / 'gamedesigner_export.cpp').read_text()
frame = source.split('/* 3. The frame loop. Leave the helper calls in this order. */', 1)[1]
frame = frame.split('if (pickups) {', 1)[0]

before = frame.index('gameworlditems_before(&world_player);')
tile_step = frame.index('game_tile_player_run(&player_physics, player_buttons, 1);')
world_after = frame.index('gameworlditems_after(&world_player);')
state = frame.index('uint8_t player_anim_state = PLAYER_ANIM_STATE_IDLE;')
anim_step = frame.index('player_anim_step(&player_anim, &')
assert before < tile_step < world_after < state < anim_step
assert frame.count('gameworlditems_after(&world_player);') == 1
assert 'if (worldObjects) out << "        gameworlditems_after(&world_player);\\n";' in frame
assert 'if (player_buttons & (BTN_LEFT | BTN_RIGHT))' in frame
assert 'if (!player_physics.on_ground)' in frame
assert 'player_anim_state = (player_physics.vy100 < 0)' in frame
assert 'GAMERGIRL_PLAYER_ANIMATIONS' in frame
assert 'game_tile_player_run(&player_physics, getjoyport(), 1);' in frame

# A user's edited main.c is not replaced with the generated example.
assert 'IMPORTANT: Existing USER-OWNED main.c is NEVER replaced by Update Project.' in source
assert 'maingame.c.txt' in source
print('PASS: world-object support/launch resolves before Idle/Walk/Jump/Fall animation')
