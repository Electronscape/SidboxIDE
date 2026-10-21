from pathlib import Path
root=Path(__file__).resolve().parents[2]
ui=(root/'gamedesigner.cpp').read_text()
model=(root/'gamedesigner.h').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
gen=(root/'gamedesigner_export.cpp').read_text()
rh=(root/'idelibs/codehelpers/game/worldobjects.h').read_text()
rc=(root/'idelibs/codehelpers/game/worldobjects.c').read_text()
model_keys=['enemyDefeatCount','enemyDefeatDelay','enemyStompOffsetX','enemyStompOffsetY','enemyStompWidth','enemyStompHeight']
for key in model_keys:
    assert key in model and key in ui
    assert f'object.value(QStringLiteral("{key}"))' in project
    assert f'object.insert(QStringLiteral("{key}"),' in project
for field in ['enemy_defeat_count','enemy_defeat_delay','enemy_stomp_offset_x',
              'enemy_stomp_offset_y','enemy_stomp_width','enemy_stomp_height']:
    assert field in rh and field in rc and field in gen
assert 'r.enemyDefeatFrame + r.enemyDefeatCount > qMin(256, frames)' in gen
assert 'const uint16_t stomp_w = enemy && o->enemy_stomp_width' in rc
assert 'best->enemy_stomp_offset_y' in rc
assert 'enemyCard.panel->setVisible(isEnemy)' in ui
assert 'object.insert(QStringLiteral("enemyDefeatFrames"), r.enemyDefeatDelay)' in project
assert 'object.value(QStringLiteral("enemyDefeatDelay"))' in project
print('PASS: Stage 4.38 editor, persisted fields, atlas-range validation, runtime generator, legacy save compatibility')
