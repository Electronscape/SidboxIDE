#!/usr/bin/env python3
"""Stage 5.166.29: World Map skips expensive world rendering but keeps HUD/UI/audio.

Tests actual native Adventure modal state plus main.rulec generation contracts
with and without a world map / HUD.
"""
from pathlib import Path
import re
import subprocess
import tempfile
import sys

ROOT = Path(__file__).resolve().parents[2]
MAIN = (ROOT / 'idelibs/codehelpers/game/maingame.rulec').read_text()
ADVENTURE = (ROOT / 'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
HEADER = (ROOT / 'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
assert 'uint8_t game_adventure_world_map_is_open(void);' in HEADER
assert 'uint8_t game_adventure_world_map_is_open(void) { return ga_map_open; }' in ADVENTURE
assert (m := re.search(r'Build: 5\.166\.(\d+)\.271026', (ROOT/'splashscreenwidget.cpp').read_text())) and int(m.group(1)) >= 29

# Use the real IDE's @IDE_IF rendering conventions, including strict flag nesting.
def render(source, enabled):
    flags = set(re.findall(r'@IDE_IF\{([A-Z_][A-Z0-9_]*)\}', source))
    stack, active, lines = [], True, []
    for lineno, line in enumerate(source.splitlines(), 1):
        match = re.fullmatch(r'\s*@IDE_IF\{([A-Z_][A-Z0-9_]*)\}\s*', line)
        if match:
            assert match[1] in flags
            stack.append((active, match[1] in enabled, False))
            active = active and match[1] in enabled
        elif line.strip() == '@IDE_ELSE':
            assert stack and not stack[-1][2], lineno
            parent, condition, _ = stack[-1]
            stack[-1] = (parent, condition, True)
            active = parent and not condition
        elif line.strip() == '@IDE_END':
            assert stack, lineno
            active = stack.pop()[0]
        elif active:
            lines.append(line)
    assert not stack
    return '\n'.join(lines)

base_flags = {'PART_MAIN', 'HAS_MAP', 'HAS_PHYSICS', 'HAS_OBJECTS',
              'HAS_WORLD_PLAYER', 'HAS_ADVENTURE', 'HAS_ADVENTURE_PHYSICS'}
for enabled in (base_flags, base_flags | {'HAS_HUD', 'SINGLE_PLANE_BACKGROUND'},
                base_flags - {'HAS_ADVENTURE_PHYSICS', 'HAS_ADVENTURE'},
                {'PART_MAIN', 'HAS_MAP'}):
    output = render(MAIN, enabled)
    section = output[output.index('/* SCREEN RENDERING ORDER'):output.index('/* YOUR GAME LOGIC:')]
    if 'HAS_ADVENTURE_PHYSICS' in enabled:
        assert section.count('if (!game_adventure_world_map_is_open()) {') == 1
        # All expensive scene rendering sits within a single conditional scope.
        first = section.index('if (!game_adventure_world_map_is_open()) {')
        last = section.index('} /* Normal world render ends.')
        world = section[first:last]
        assert 'game_tilemap_animation_tick(1);' in world
        assert 'game_tilemap_blit_view_cleared(' in world
        assert 'game_tilemap_blit_view_front(' in world
        assert 'gameworlds_draw(' in world
        assert 'gameworlds_weather_frame(' in world
        assert 'gameworlds_spotlight_frame(' in world
        assert 'gfx_rectf(0, 0, VIEW_W, VIEW_H);' in section[:first]
        assert 'game_adventure_draw(' in section[last:]
        if 'HAS_HUD' in enabled:
            assert 'gamehud_apply_dock(front[draw_index])' in section[last:]
            assert 'game_show_hud(0, 0)' in section[last:]
        if 'SINGLE_PLANE_BACKGROUND' in enabled:
            assert 'gameworlds_draw_background()' in world
        assert 'gameworlds_transition_frame(VIEW_W, VIEW_H)' in output
        assert 'music_update();' in output
    else:
        assert 'game_adventure_world_map_is_open()' not in output
        assert 'game_tilemap_animation_tick(1);' in section
        assert 'game_tilemap_blit_view_cleared(' in section

sys.path.insert(0, str(ROOT / 'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
with tempfile.TemporaryDirectory(prefix='cg516629_') as tmp:
    p = Path(tmp)
    render_adventure_runtime(ROOT, p)
    (p / 'apis.h').write_text((ROOT / 'development/tests/stage429_mock_api/apis.h').read_text())
    (p / 'test.c').write_text('''
#include "adventureruntime.c"
#include <assert.h>
#include <stdio.h>
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char*s){(void)x;(void)y;(void)s;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t*b){(void)b;}
int main(void){
    ga_map_open=0u;ga_quest_open=0u;
    assert(!game_adventure_world_map_is_open());
    ga_quest_open=1u;
    assert(game_adventure_open());
    assert(!game_adventure_world_map_is_open()); /* Journal keeps scene */
    ga_quest_open=0u;ga_map_open=1u;
    assert(game_adventure_open());
    assert(game_adventure_world_map_is_open());
    ga_map_open=0u;
    assert(!game_adventure_world_map_is_open()); /* Restores world render */
    puts("PASS native modal state: map-only fast path");
    return 0;
}
''')
    subprocess.run(['gcc','-std=gnu11','-O0','-Werror','-Wall','-Wextra',
                    '-I',str(p),str(p/'test.c'),'-o',str(p/'native')],check=True)
    subprocess.run([str(p/'native')],check=True)
print('PASS Stage 5.166.29: World Map-only render gate, HUD/UI/audio and generation modes')
