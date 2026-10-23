#!/usr/bin/env python3
"""A PPB sprite called pickups[0] must never shadow managed pickup structs.

Compile initializer C emitted from the real World Items rule for both an
object named pickups[0] and an object named platforms[0]. The world-symbols
header's macro mapping is deliberately present, as in generated world modules.
"""
from pathlib import Path
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
TEMPLATE = (ROOT / 'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
EXPORT = (ROOT / 'gamedesigner_export.cpp').read_text()

assert 'static game_collectable_t cg_gwi_pickups[' in TEMPLATE
assert 'static game_world_object_t cg_gwi_platforms[' in TEMPLATE
assert 'QStringLiteral("cg_gwi_pickups[%1]")' in EXPORT
assert 'QStringLiteral("cg_gwi_platforms[%1]")' in EXPORT
assert 'QStringLiteral("cg_gwi_pickups") : QStringLiteral("cg_gwi_platforms")' in EXPORT
assert not re.search(r'\b(?:pickups|platforms)\[', TEMPLATE)

section = re.search(r'(?ms)^@IDE_SECTION\{OBJECT_INIT\}\s*\n(.*?)^@IDE_SECTION_END', TEMPLATE)
assert section, 'Missing source initializer template'

def init_for(collectable):
    flags = {'IS_PICKUP': collectable}
    output = []
    stack = []
    active = True
    for line in section.group(1).splitlines():
        if match := re.fullmatch(r'@IDE_IF\{(\w+)\}', line):
            condition = flags.get(match.group(1), False)
            stack.append((active, condition))
            active = active and condition
        elif line == '@IDE_ELSE':
            parent, condition = stack[-1]
            active = parent and not condition
        elif line == '@IDE_END':
            active = stack.pop()[0]
        elif active:
            output.append(line)
    assert not stack
    values = {'OBJECT_LABEL': 'Collectable' if collectable else 'World Object',
              'OBJECT_NAME': 'pickups[0]' if collectable else 'platforms[0]',
              'INDEX': '0', 'SPRITE_SYMBOL': 'pickups[0]' if collectable else 'platforms[0]',
              'PICKUP_KIND': '2', 'PICKUP_VALUE': '10', 'OBJECT_KIND': '1',
              'WIDTH': '8', 'HEIGHT': '8', 'X': '5', 'Y': '6',
              'INIT_ACTIVE': '1', 'DRAW_BEHIND': '0',
              'FLIP_X': 'BLIT_FLAG_FLIP_X', 'FLIP_Y': '0',
              'PICKUP_TRACKING': '0', 'PICKUP_INVENTORY': '1', 'PICKUP_HUD': '1',
              'PICKUP_PERSISTENT': '0', 'RESPAWN_FRAMES': '0'}
    result = '\n'.join(output)
    result = re.sub(r'@IDE\{(\w+)\}',lambda match: values[match.group(1)],result)
    assert '@IDE' not in result
    return result

src = r'''
#include <stdint.h>
#include <assert.h>
#define BLIT_FLAG_FLIP_X 4u
#define BLIT_FLAG_FLIP_Y 8u
/* These aliases are automatically generated in worlds/forest/world_symbols.h. */
#define pickups forest_pickups
#define platforms forest_platforms
typedef struct { uint16_t flags; } gfxbob_t;
typedef struct {
    gfxbob_t *sprite;
    uint16_t width, height, respawn_frames;
    uint8_t tracking_configured, show_in_inventory, show_in_hud;
    uint8_t persistent, active, draw_behind_tiles;
} game_collectable_t;
typedef struct { gfxbob_t *sprite; uint8_t active, draw_behind_tiles; } game_world_object_t;
static gfxbob_t pickups[1], platforms[1];
static game_collectable_t cg_gwi_pickups[1];
static game_world_object_t cg_gwi_platforms[1];
static int game_collectable_start(game_collectable_t *obj, gfxbob_t *gfx, int type, int amount)
{ (void)type; (void)amount; obj->sprite = gfx; return 1; }
static int game_world_object_start(game_world_object_t *obj, int kind, gfxbob_t *gfx,
                                   int x, int y, int width, int height)
{ (void)kind; (void)x; (void)y; (void)width; (void)height; obj->sprite = gfx; return 1; }
static int gameworlditems_init(void)
{
'''+init_for(True)+'\n'+init_for(False)+r'''
    return 1;
}
int main(void)
{
    assert(gameworlditems_init());
    assert(cg_gwi_pickups[0].sprite == &pickups[0]);
    assert(cg_gwi_platforms[0].sprite == &platforms[0]);
    assert(pickups[0].flags == BLIT_FLAG_FLIP_X);
    assert(platforms[0].flags == BLIT_FLAG_FLIP_X);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as directory:
    source = Path(directory) / 'repro.c'
    binary = Path(directory) / 'repro'
    source.write_text(src)
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror',
                    str(source), '-o', str(binary)], check=True)
    subprocess.run([str(binary)], check=True)
print('Stage 5.44.1: PPB sprite names pickups[0]/platforms[0] compile and bind correctly: PASS')
