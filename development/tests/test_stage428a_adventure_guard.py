#!/usr/bin/env python3
"""Regression: the nested adventure pause guard has a readable generated body."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
export = (root / 'gamedesigner_export.cpp').read_text()
assert 'Stage 4.28a: the adventure-only pause guard' in export
assert 'program.replace(bodyAt, closeAt - bodyAt, lines.join' in export
assert 'line.prepend(QStringLiteral("    "))' in export
assert 'if (adventureEnabled && hasPhysics)' in export
assert 'gameadventure_setup();' in export
assert 'game_adventure_input(adventure_buttons' in export
assert 'game_adventure_draw(camera_x' in export
print('Stage 4.28a adventure generator formatting checks passed')
