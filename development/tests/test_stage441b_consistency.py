#!/usr/bin/env python3
"""Catches compiler breakage caused by mismatching Stage 4.41 editor/source headers."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[2]
ui = (root / 'gamedesigner.cpp').read_text()
model = (root / 'gamedesigner.h').read_text()
save = (root / 'gamedesigner_project.cpp').read_text()
gen = (root / 'gamedesigner_export.cpp').read_text()
for member, declared, default in (
    ('enemyStompSideKick', r'bool\s+enemyStompSideKick\s*=\s*false', 'false'),
    ('enemyAttackDirection', r'int\s+enemyAttackDirection\s*=\s*0', '0'),
):
    assert re.search(declared, model), f'Missing Resource declaration: {member}'
    assert f'old.{member}' in ui, f'Missing UI read: {member}'
    assert f'r.{member} =' in ui, f'Missing UI write: {member}'
    assert f'"{member}"' in save, f'Missing saved setting: {member}'
assert 'enemy_stomp_side_kick' in gen and 'enemy_attack_direction' in gen
assert 'Reward speed X (px/frame)' in ui and 'Reward speed Y (px/frame)' in ui
for path in ('idelibs/codehelpers/game/worldobjects.c', 'idelibs/codehelpers/game/worldobjects.h'):
    assert (root/path).is_file(), f'Missing template {path}'
print('PASS: IDE/header/resource fields, persistence, generator, reward UI and templates all in sync')
