"""Source contract for optional Player Profile melee foundation (Stage 124)."""
from pathlib import Path
import re
r=Path(__file__).resolve().parents[2]
def text(path): return (r/path).read_text()
profile=text('gameplayerprofile.h')
editor=text('gamedesigner.cpp')
player=text('idelibs/codehelpers/game/gameplayer.rulec')
player_h=text('idelibs/codehelpers/game/gameplayer.ruleh')
world=text('idelibs/codehelpers/game/gameworlds.rulec')
items=text('idelibs/codehelpers/game/gameworlditems.rulec')
obj=text('idelibs/codehelpers/game/worldobjects.rulec')
snap=text('gameworldsnapshot.h')
main=text('idelibs/codehelpers/game/maingame.rulec')
assert 'combatEnabled' in profile and 'attackReach' in profile and 'attackCooldown' in profile
assert 'combatEnabled' in profile and 'toBool()' in profile
assert 'combatEnabled->isChecked()' in editor and 'attackDamage->value()' in editor
assert 'gameplayer_attack_step' in player_h and 'gameplayer_attack_started' in player_h
assert 'gp_attack_armed' in player and 'gp_cooldown_left' in player
assert 'gameworlditems_player_attack' in items and 'game_world_objects_attack' in obj
assert 'enemy_take_damage(o, 1u)' in obj and 'enemy_take_damage(o, damage)' in obj
assert 'active_world->player_attack' in world and 'gameplayer_attack_register_hits' in world
assert 'attackFns <<' in snap and 'attackFns.at(i)' in snap
assert '@IDE_IF{HAS_SHARED_PLAYER}' in main and 'gameplayer_movement_buttons' in main
assert re.search(r'Build: 5\.\d+\.\d+\.\d{6}', text('splashscreenwidget.cpp'))
for p in ('idelibs/codehelpers/game/maingame.rulec','idelibs/codehelpers/game/gameworlds.rulec','idelibs/codehelpers/game/gameworlditems.rulec'):
  x=text(p)
  assert len(re.findall(r'@IDE_IF\{', x)) == len(re.findall(r'@IDE_END\b',x)),p
print('Stage124 combat source-contract tests: PASS')
