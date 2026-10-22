"""Stage 5.18 shared player movement physics editable profile contract."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
profile=(root/'gameplayerprofile.h').read_text()
editor=(root/'gamedesigner.cpp').read_text()
engine=(root/'idelibs/codehelpers/game/tilemap.c').read_text()
player_c=(root/'idelibs/codehelpers/game/gameplayer.rulec').read_text()
player_h=(root/'idelibs/codehelpers/game/gameplayer.ruleh').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
assert 'defaultPhysicsProfiles()' in profile and 'physicsProfiles' in profile
assert 'startingPhysicsId' in profile and 'physicsPresetId' in profile
assert 'PHYSICS_PROFILE_ROWS' in profile and 'PHYSICS_PROFILE_COUNT' in profile
for field in ('walkSpeed','jumpSpeed','gravity','maxFallSpeed','forceDrag','mode'):
    assert field in profile and field in editor
assert 'Add' in editor and 'Remove' in editor and 'Remove Movement Physics' in editor
assert 'gameworlds_bind_player_physics(&player_physics)' in main and 'gameplayer_apply_physics' in player_c
assert 'gameplayer_apply_physics' in player_h
assert 'game_tile_player_set_physics(player, physics->mode)' in player_c
assert 'game_tile_player_set_force_drag(player, physics->drag)' in player_c
assert 'if (p->physics_mode == GAME_PHYSICS_ICE)' in engine
assert 'Build: 5.20.221026' in splash
print('Stage 5.18 physics profile source contract: PASS')
