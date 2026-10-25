#!/usr/bin/env python3
from pathlib import Path
import tempfile, subprocess, json
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
get=lambda p:(root/p).read_text()
assert 'Build: 5.129.251026' in get('splashscreenwidget.cpp')
assert 'root["footX"] = m_footX->value()' in get('gameanimationeditor.cpp')
assert 'FOOT_X @IDE{FOOT_X}u' in get('idelibs/codehelpers/game/playeranim.ruleh')
assert 'QStringLiteral("footX")' in get('gameadventuregen.cpp')
assert 'QStringLiteral("animationFile")' in get('gameadventuregen.cpp')
assert 'game_adventure_set_drop_anchor(gameadventure_live_sprite_origin' in get('idelibs/codehelpers/game/gameadventure.rulec')
assert 'gameworlds_player_sprite_origin(int32_t *x, int32_t *y)' in get('idelibs/codehelpers/game/gameworlds.rulec')
assert '*x=bound_player_physics->x100/100;' in get('idelibs/codehelpers/game/gameworlds.rulec')
assert 'foot_y-height/2-8' in get('idelibs/codehelpers/game/adventureruntime.rulec')
assert 'ga_drop_facing_right' in get('idelibs/codehelpers/game/adventureruntime.rulec')
assert 'player_physics.x100 / 100 + player_physics.hitbox_x' in get('idelibs/codehelpers/game/maingame.rulec')
anim=json.loads(Path('/mnt/data/game_snapshot/gameanimations/player_anim.sbanim').read_text())
assert (anim['footX'],anim['footY'])==(32,63)
assert (anim['hitboxW'],anim['hitboxH'])==(25,62)
with tempfile.TemporaryDirectory(prefix='cg5129-') as d:
    out=render_adventure_runtime(root,Path(d),items=1)
    test=root/'development/tests'
    for name in ('test_stage5129_drop_foot.c', 'test_stage5128_drop_gravity.c', 'test_stage5126_directional_drop.c','test_stage5126_thought_colours.c'):
        exe=out/name.replace('.c','')
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
            '-I',str(test/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(test/name),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.129 generated sources and native C regressions PASS')
