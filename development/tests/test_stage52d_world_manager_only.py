#!/usr/bin/env python3
"""Stage 5.2d: legacy V1 single-world entry points retired from generated starter/build.
Static integration + representative real rule rendering, including no-map scenarios.
Run: python3 development/tests/test_stage52d_world_manager_only.py
"""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
cpp=(root/'mainwindow.cpp').read_text()
h=(root/'mainwindow.h').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
rule=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
verify=cpp.split('bool MainWindow::gameBuildFilesOutdated(',1)[1].split('bool MainWindow::checkGameBuildGeneration()',1)[0]
check=cpp.split('bool MainWindow::checkGameBuildGeneration()',1)[1].split('void MainWindow::compileActiveFile()',1)[0]
build=cpp.split('QStringList MainWindow::projectFilesForCompile()',1)[1].split('QStringList MainWindow::projectFunctionSignatures()',1)[0]
assert 'bool gameBuildFilesOutdated(const QString &designPath) const;' in h
assert 'active-world.json' not in verify
assert 'world-build.json' in verify and 'world_api.h' in verify
assert 'Choose Game Design' not in check
assert 'gameworlds_start' in check and 'Multi-World Migration Required' in check
assert 'gameBuildFilesOutdated(path)' in check
assert 'm_gameBuildFirstCheckPending ? designs : outdated' in check
assert 'updateGameWorldPaths(targets, true)' in check
assert 'bool MainWindow::updateGameWorldPaths(' in cpp
assert 'worldManagerMain' not in build
for filename in ['gameassets/gameassets.c','gamehelpers/gameworlditems.c','gamehelpers/gameadventure.c','gamehelpers/splinepaths.c']:
    assert filename in build, filename
assert 'worlds/' in build
assert '2048LL * 1024LL' in cpp
assert 'mainFields.insert(QStringLiteral("WORLD_BASE"), worldBase);' in export
assert '@IDE_IF{PART_SPRITE_DRAW}' in rule
for oldCall in ['    if (!gameassets_init()', '    if (!gameworlditems_init()', '    gameassets_shutdown();', '    @IDE{WORLD_SYMBOL}_unload', '#include "gameassets/gameassets.h"']:
    assert oldCall not in rule, oldCall

# Mirror GameHelperTemplates::renderConditionals() exactly: nested conditions,
# an @IDE_ELSE per block and validation of every flag even if inactive.
def render(src, flags, values):
    stack=[]; active=True; rendered=[]
    for line in src.splitlines():
        m=re.fullmatch(r'\s*@IDE_IF\{([A-Z_][A-Z0-9_]*)\}\s*',line)
        if m:
            key=m.group(1)
            assert key in flags, f'unknown condition {key}'
            stack.append((active,bool(flags[key]),False))
            active=active and bool(flags[key]);continue
        if line.strip()=='@IDE_ELSE':
            assert stack and not stack[-1][2]
            parent,condition,_=stack[-1]
            stack[-1]=(parent,condition,True);active=parent and not condition;continue
        if line.strip()=='@IDE_END':
            assert stack
            active=stack.pop()[0];continue
        if active: rendered.append(line)
    assert not stack
    output='\n'.join(rendered)
    output=re.sub(r'@IDE\{([A-Z_][A-Z0-9_]*)\}',lambda m:values.get(m.group(1),'0'),output)
    assert '@IDE' not in output
    return output

flagNames=set(re.findall(r'@IDE_IF\{([A-Z_][A-Z0-9_]*)\}',rule))
values={'WORLD_BASE':'world1','PLAYER_SYMBOL':'player','WORLD_HEADER_FILENAME':'world1.h','WORLD_MAP_FILENAME':'world1.map','TILEMAP_DESCRIPTION':'embedded C','PLAYER_DESCRIPTION':'player','SCENERY_BEHIND_TILES':'','SCENERY_IN_FRONT_OF_TILES':''}
for keys in [set(), {'HAS_MAP'}, {'HAS_MAP','HAS_PHYSICS','HAS_OBJECTS','HAS_WORLD_PLAYER','HAS_PICKUPS','HAS_ADVENTURE','HAS_ADVENTURE_PHYSICS','HAS_FRONT_TILES'}, {'HAS_MAP','HAS_PHYSICS','HAS_OBJECTS','HAS_WORLD_PLAYER','HAS_PLAYER_ANIMATION','HAS_CUSTOM_ZONES','HAS_SPLINES','HAS_MURDER_OBJECTS','HAS_PICKUPS','HAS_PLAYER_HAZARDS'}, {'HAS_NO_MAP','HAS_OBJECTS'}, {'HAS_MAP','HAS_BACKGROUND_PLANE','DUAL_PLANE','HAS_BACKGROUND_SPRITES','HAS_MUSIC'}]:
    flags={key:int(key in keys) for key in flagNames};flags['PART_MAIN']=1;flags['PART_SPRITE_DRAW']=0
    out=render(rule,flags,values)
    assert 'gameworlds_start("world1")' in out
    assert 'gameworlds_apply_pending()' in out
    assert 'gameworlds_shutdown()' in out
    assert 'worlds/world1/world_api.h' in out
    assert 'gameassets_init();' not in out
    assert 'gameworlditems_init();' not in out
    assert '#include "gameassets/gameassets.h"' not in out
    assert out.count('int main(')==1
    if 'HAS_PHYSICS' in keys:
        assert 'world1_player' in out and 'game_tile_player_start' in out
        assert 'gameworlds_map()' in out
    else:
        assert 'game_tile_player_start' not in out
    if 'HAS_PICKUPS' in keys:
        assert 'gameworlds_check(' in out
    if 'HAS_WORLD_PLAYER' in keys:
        assert 'gameworlds_before(&world_player)' in out
        assert 'gameworlds_after(&world_player)' in out
    if 'HAS_ADVENTURE' in keys:
        assert 'gameadventureruntime.h' in out
        assert 'game_adventure_input(' in out

flags={key:0 for key in flagNames};flags['PART_SPRITE_DRAW']=1
sprites=render(rule,flags,{**values,'SPRITE_SYMBOL':'tree','SPRITE_FLIP_X':'0','SPRITE_FLIP_Y':'0','SPRITE_X':'10','SPRITE_Y':'20'})
assert 'extern gfxbob_t world1_tree;' in sprites
assert 'gfx_drawbob(&world1_tree)' in sprites
print('PASS Stage 5.2d: manager-only build/F5 and 6 rule variants + sprite decorations')
