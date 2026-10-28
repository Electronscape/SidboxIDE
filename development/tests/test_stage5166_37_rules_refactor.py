#!/usr/bin/env python3
"""Source contract: Stage 5.166.37 shared Adventure drop queries."""
from pathlib import Path
import re

root=Path(__file__).resolve().parents[2]
base=root/'idelibs/codehelpers/game'
story=(base/'gameadventure.rulec').read_text()
core=(base/'tilemap.c').read_text()
hdr=(base/'tilemap.h').read_text()
assert story.count('game_adventure_set_drop_floor(gameadventure_drop_floor)')==1
assert story.count('game_adventure_set_drop_sweep(gameadventure_drop_sweep)')==1
assert 'return game_tilemap_drop_sweep((const game_tilemap_t *)gameworlds_map()' in story
assert 'return game_tilemap_drop_floor((const game_tilemap_t *)gameworlds_map()' in story
assert 'gameadventure_live_sprite_origin' not in story
assert 'gameadventure_live_pickup_rect' not in story
assert 'game_adventure_set_drop_anchor(gameworlds_player_sprite_origin,' in story
assert 'game_adventure_set_pickup_rect(gameworlds_player_pickup_rect);' in story
for fn in ('game_tilemap_drop_floor','game_tilemap_drop_sweep'):
    assert core.count('int32_t '+fn+'(')==1
    assert hdr.count('int32_t '+fn+'(')==1
assert '#if defined(__GNUC__) && !defined(__clang__)' in core
assert (lambda v: v and int(v.group(1)) >= 37)(re.search(r'Build: 5\.166\.(\d+)\.\d{6}', (root/'splashscreenwidget.cpp').read_text()))
print('PASS Stage 5.166.37: shared item-drop query, active-world callbacks, compile flags, splash')
