"""Stage 3.92b: C generator must teach draw ordering and hurt flashing.

Source-level assertions only: Qt6 UI compilation is a separate Fedora check.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
source = (root / 'gamedesigner_export.cpp').read_text()

behind_marker = '/* GAME OBJECTS BEHIND THE TILEMAP — WHY DRAW THEM HERE?'
flash_marker = '/* PLAYER HURT FLASH — WHY MAKE A COPY OF THE SPRITE?'
assert source.count(behind_marker) == 1
assert source.count(flash_marker) == 1

# The comment is emitted only when those pieces of the game are present.
assert f'if (hasObjects) out << R"CG(        {behind_marker}' in source
assert f'if (hasMurderObjects) {{\n            out << R"CG(        {flash_marker}' in source

behind = source[source.index(behind_marker):source.index(')CG";', source.index(behind_marker))]
flash = source[source.index(flash_marker):source.index(')CG";', source.index(flash_marker))]

for detail in ('"Draw behind tilemap"', 'BEFORE the tilemap', 'gameworlditems_draw()',
               'camera_x and camera_y', 'VISUAL layering only',
               'game_tilemap_blit_view_cleared()',
               'gameworlditems_draw_behind(camera_x, camera_y);'):
    assert detail in behind, detail
for detail in ('gfxbob_t', 'player_visible', 'flash_colour',
               'foreground', 'palette INDEX', 'BLIT_FLAG_SOLIDCOLOUR',
               'BLIT_FLAG_TYPE_TINT_VALUE', 'gfx_drawbob()'):
    assert detail in flash, detail

# Comments must not alter the real rendering statements or their order.
assert behind.endswith('gameworlditems_draw_behind(camera_x, camera_y);\n')
assert re.search(r'gfxbob_t player_visible = " << playerName << ";\\n"', source)
assert source.count('player_visible.flags |= BLIT_FLAG_SOLIDCOLOUR') == 1
assert source.count('player_visible.flagval[BLIT_FLAG_TYPE_TINT_VALUE]') == 1
assert source.index('gameworlditems_draw_behind(camera_x, camera_y);') < source.index(
    'game_tilemap_blit_view_cleared(&game_level1, camera_x, camera_y, VIEW_W, VIEW_H);')
assert source.index('game_tilemap_blit_view_cleared(&game_level1, camera_x, camera_y, VIEW_W, VIEW_H);') < source.index(
    'gameworlditems_draw(camera_x, camera_y);')
assert source.index('game_tile_player_screen(&player_physics, camera_x, camera_y);') < source.index(flash_marker)
print('PASS: generated in-code tutorial explains draw-behind and solid-colour hurt flash without changing behaviour')
