#!/usr/bin/env python3
"""Static wiring checks: the Qt GUI cannot be compiled without Qt6."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
ui=(root/'gamedesigner.cpp').read_text()
model=(root/'gamedesigner.h').read_text()
save=(root/'gamedesigner_project.cpp').read_text()
gen=(root/'gamedesigner_export.cpp').read_text()
helper=(root/'idelibs/codehelpers/game/worldobjects.h').read_text()
rt=(root/'idelibs/codehelpers/game/worldobjects.c').read_text()
for token in ('enemyStompSideKick','enemyAttackDirection'):
    assert token in model
    assert f'"{token}"' in save
    assert f'r.{token} =' in ui
    assert f'{token}->set' in ui
assert 'enemy_stomp_side_kick = ' in gen
assert 'enemy_attack_direction = ' in gen
assert 'enemy_stomp_side_kick' in helper and 'enemy_attack_direction' in helper
assert 'enemy_vulnerable_hit(o, p, 1)' in rt
assert 'enemy_vulnerable_hit(best, p, 0)' in rt
assert 'p->break_stomp_armed && *p->vy100 < 0' in rt
assert 'enemy_stomp_side_kick && o->break_launch_x' in rt
# Enemy reward launch must share the already-tested collectable drop system:
assert 'enemyRewardImpulse->isChecked() : breakRewardImpulse->isChecked()' in ui
assert 'enemyRewardVx->value() : breakRewardVx->value()' in ui
assert 'enemyRewardVy->value() : breakRewardVy->value()' in ui
assert 'breakRewardImpulse ? block.breakRewardVx * 100 : 0' in gen
assert 'breakRewardImpulse ? block.breakRewardVy * 100 : 0' in gen
assert 'if (platforms[' in gen and '].break_triggered) {' in gen
assert 'enemyRewardImpulse->setChecked(old.breakRewardImpulse)' in ui
assert '(candidate.objectType == QStringLiteral("enemy"))' in ui or 'candidate.objectType == QStringLiteral("enemy")' in ui
# Stage 4.39 green/red live overlay & Stage 4.40 visual frame picker preserved.
assert 'sprite.united(body).united(stomp)' in ui
assert 'Choose from atlas...' in ui
print('PASS: persistence, generated code, reward speed, legacy editor visuals and runtime wiring')
