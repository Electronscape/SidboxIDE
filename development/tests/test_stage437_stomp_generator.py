from pathlib import Path
r=Path(__file__).resolve().parents[2]
ui=(r/'gamedesigner.cpp').read_text()
gen=(r/'gamedesigner_export.cpp').read_text()
model=(r/'gamedesigner.h').read_text()
project=(r/'gamedesigner_project.cpp').read_text()
for fld in ['enemyRoam', 'enemyRoamSpeed', 'enemyStepHeight', 'enemyRoamLeft']:
    assert fld in model and fld in ui
    assert f'object.value(QStringLiteral("{fld}"))' in project
    assert f'object.insert(QStringLiteral("{fld}"),' in project
assert 'game_world_objects_roam(platforms,' in gen
assert 'cg_enemy_tile_blocked' in gen
assert 'r.enemyRoam && m_tilemapEnabled' in gen
assert 'r.enemyRoam' in gen and 'r.enemyRoamSpeed' in gen
assert 'enemy_base_flip_x' in gen
for field in ['hazard_kick', 'hazard_kick_x', 'hazard_kick_y', 'hazard_hurt_animation',
              'hazard_flash', 'hazard_flash_colour', 'hazard_flash_count', 'hazard_flash_frames']:
    assert field in gen
assert 'hazardCard.panel->setVisible(isHazard || isEnemy)' in ui
assert 'Hits before enemy dies' in ui
assert 'Item dropped when defeated' in ui
print('PASS: Stage 4.37 enemy editor, persistence, generator and existing drop/hit links')
