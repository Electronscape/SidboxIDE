"""Stage 3.92: source-level settings, save/load, runtime, generation and drawing contract."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
read=lambda f:(root/f).read_text()
model=read('gamedesigner.h'); ui=read('gamedesigner.cpp')
proj=read('gamedesigner_project.cpp'); gen=read('gamedesigner_export.cpp')
worldc=read('idelibs/codehelpers/game/worldobjects.c')
worldh=read('idelibs/codehelpers/game/worldobjects.h')
pickc=read('idelibs/codehelpers/game/collectables.c')
pickh=read('idelibs/codehelpers/game/collectables.h')
assert 'Hazard / Murder Object' in ui
for key in ('hazardDamage','hazardKick','hazardKickX','hazardKickY',
            'hazardHurtAnimation','hazardFlash','hazardFlashColour',
            'hazardFlashCount','hazardFlashFrames',
            'sfxHazardHit','sfxHazardBounce','sfxHazardAmbient'):
    assert key in model and key in ui and key in proj and key in gen, key
    assert f'object.value(QStringLiteral("{key}"))' in proj
    assert f'object.insert(QStringLiteral("{key}"),' in proj
assert 'drawBehindTiles' in model and 'drawBehindTiles' in ui
assert 'a.insert(QStringLiteral("drawBehindTiles"),' in proj
assert 'a.value(QStringLiteral("drawBehindTiles"))' in proj
assert 'GAME_OBJECT_HAZARD' in gen and 'GAME_OBJECT_HAZARD' in worldh
assert 'game_world_objects_hazards(platforms' in gen
assert 'hazard_swept_contact' in worldc
assert 'BLIT_FLAG_SOLIDCOLOUR' in gen and 'BLIT_FLAG_TYPE_TINT_VALUE' in gen
assert 'PLAYER_ANIM_STATE_HURT' in gen and 'hasMurderObjects' in gen
assert 'gameworlditems_draw_behind' in gen and 'draw_behind_tiles' in gen
assert gen.index('gameworlditems_draw_behind(camera_x, camera_y)') < gen.index('game_tilemap_blit_view_cleared(&game_level1')
assert 'draw_layer(' in worldc and 'draw_layer(' in pickc
assert 'draw_behind_tiles' in worldh and 'draw_behind_tiles' in pickh
assert 'r.drawBehindTiles' in gen
for flag in ('hazard_hit_triggered', 'hazard_bounce_triggered'):
    assert flag in worldh and flag in worldc and flag in gen
assert 'r.sfxHazardAmbient' in gen and 'cg_loop_target' in gen
assert 'hurt_damage_this_frame' in gen and 'player_health' in gen
print('PASS: hazard UI, palette, save/load, sounds, world physics, layers, C generation')
