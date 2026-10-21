#!/usr/bin/env python3
"""Stage 5.1 namespace ABI/link smoke test. Requires host gcc, not Qt.

Construct two representative world module trees and a legacy canonical module.
Verify that namespaced world assets, animations, world objects, adventure and
map code coexist at link time with legacy main.c calling its old API.
"""
import pathlib
import subprocess
import tempfile
import re

function_re = re.compile(r'(?m)^\s*(?:extern\s+)?[A-Za-z_][A-Za-z_0-9 \t\*]*?\s*\*?\s*([A-Za-z_][A-Za-z_0-9]*)\s*\(')
extern_re = re.compile(r'(?m)^\s*extern\s+[^;\n]*?\b([A-Za-z_][A-Za-z_0-9]*)\s*(?:\[[^;\n]*\])?\s*;')
mandatory = "gameassets_init gameassets_shutdown gameassets_find_ppb gameworlditems_init gameworlditems_update gameworlditems_draw gameadventure_setup gameadventure_on_event drawworld".split()

def put(root, name, value):
    path = root / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(value)
    return path

def exported(root):
    names = set(mandatory)
    for relative in ["gameassets/gameassets.h", "gamehelpers/gameworlditems.h", "gamehelpers/gameadventure.h", "gamehelpers/splinepaths.h"]:
        f = root / relative
        if f.exists():
            txt = f.read_text()
            names.update(function_re.findall(txt))
            names.update(extern_re.findall(txt))
    return sorted(names)

with tempfile.TemporaryDirectory(prefix='sidbox-stage51-') as temp:
    root = pathlib.Path(temp)
    put(root, "gamehelpers/gametilemap.h", "#pragma once\ntypedef struct {int width;} game_tilemap_t;\n")
    put(root, "gamehelpers/gamespline.h", "#pragma once\ntypedef struct {int x;} game_spline_point_t;\n")
    put(root, "gameassets/gameassets.c", '''int gameassets_init(void) { return 7; }
void gameassets_shutdown(void) {}\n''')
    put(root, "main.c", '''#include "worlds/world1/world_api.h"
#include "worlds/forest/world_api.h"
extern int gameassets_init(void);
int main(void) {
    if (gameassets_init() != 7) return 1;
    if (world1_gameassets_init() != 1 || forest_gameassets_init() != 2) return 2;
    if (world1_gameworlditems_init() != 11 || forest_gameworlditems_init() != 12) return 3;
    if (world1_man != 13 || forest_man != 14) return 4;
    if (game_world1.width != 101 || game_forest.width != 102) return 5;
    if (world1_walking_count != 15 || forest_walking_count != 16) return 6;
    return 0;
}
''')
    world_src = []
    for i, name in enumerate(['world1', 'forest'], 1):
        base = root / 'worlds' / name
        put(base, 'gameassets/gameassets.h', '''#ifndef CODERGIRL_GENERATED_GAMEASSETS_H
#define CODERGIRL_GENERATED_GAMEASSETS_H
int gameassets_init(void);
void gameassets_shutdown(void);
extern int man;
void drawman(void);
#endif
''')
        put(base, 'gameassets/gameassets.c', '''#include "../world_symbols.h"
#include "gameassets.h"
int man = @MAN@;
int gameassets_init(void) { return @N@; }
void gameassets_shutdown(void) {}
void drawman(void) {}
'''.replace('@MAN@', str(i+12)).replace('@N@', str(i)))
        put(base, 'gamehelpers/gameworlditems.h', '''#ifndef CODERGIRL_V1_GAMEWORLDITEMS_H
#define CODERGIRL_V1_GAMEWORLDITEMS_H
int gameworlditems_init(void);
#endif
''')
        put(base, 'gamehelpers/gameworlditems.c', '''#include "../world_symbols.h"
#include "gameworlditems.h"
#include "../gameassets/gameassets.h"
int gameworlditems_init(void) { drawman(); return @N@; }
'''.replace('@N@', str(i+10)))
        put(base, 'gamehelpers/gameadventure.h', '''#ifndef GAMERGIRL_GENERATED_ADVENTURE_H
#define GAMERGIRL_GENERATED_ADVENTURE_H
void gameadventure_setup(void);
#endif
''')
        put(base, 'gamehelpers/gameadventure.c', '''#include "../world_symbols.h"
#include "gameadventure.h"
#include "../gameassets/gameassets.h"
void gameadventure_setup(void) { drawman(); }
''')
        put(base, 'gamehelpers/splinepaths.h', '''#ifndef CODERGIRL_V1_SPLINEPATHS_H
#define CODERGIRL_V1_SPLINEPATHS_H
#include "gamespline.h"
extern const int walking_count;
#endif
''')
        put(base, 'gamehelpers/splinepaths.c', '''#include "../world_symbols.h"
#include "splinepaths.h"
const int walking_count = @N@;
'''.replace('@N@', str(i+14)))
        put(base, f'gamelevels/{name}.h', f'''#ifndef WORLD_{name.upper()}_H
#define WORLD_{name.upper()}_H
#include "../../../gamehelpers/gametilemap.h"
extern game_tilemap_t game_{name};
#endif
''')
        put(base, f'gamelevels/{name}.c', f'''#include "../world_symbols.h"
#include "{name}.h"
#include "../gameassets/gameassets.h"
game_tilemap_t game_{name} = {{ {100+i} }};
''')
        aliases = ''.join(f'#define {sym} {name}_{sym}\n' for sym in exported(base))
        put(base, 'world_symbols.h', aliases)
        put(base, 'world_api.h', f'''#ifndef WORLD_PUBLIC_{name.upper()}
#define WORLD_PUBLIC_{name.upper()}
#include "gamelevels/{name}.h"
extern int {name}_gameassets_init(void);
extern int {name}_gameworlditems_init(void);
extern int {name}_man;
extern const int {name}_walking_count;
#endif
''')
        world_src.extend(sorted(base.glob('**/*.c')))

    output = root / 'game'
    cmd = ['gcc','-std=c11','-Wall','-Wextra','-Werror','-pedantic',
           '-I',str(root/'gamehelpers'),'-I',str(root/'gameassets'),
           '-I',str(root),'-o',str(output),str(root/'main.c'),
           str(root/'gameassets/gameassets.c'), *map(str,world_src)]
    subprocess.run(cmd, check=True, capture_output=True, text=True)
    subprocess.run([str(output)], check=True)
    syms = subprocess.run(['nm','-g','--defined-only',str(output)], check=True,capture_output=True,text=True).stdout
    for x in ['gameassets_init','world1_gameassets_init','forest_gameassets_init',
              'world1_drawman','forest_drawman','world1_man','forest_man',
              'world1_walking_count','forest_walking_count',
              'game_world1','game_forest']:
        assert re.search(r'\s'+x+r'\b',syms), f'no emitted symbol: {x}'
    print('PASS: legacy + two world link, resource/spline namespacing, map names, world API headers')
