#!/usr/bin/env python3
"""Stage 4.44: rule substitutions exactly preserve stable world-object runtime."""
from pathlib import Path
import re
import tarfile
ROOT = Path(__file__).resolve().parents[2]
BASE = ROOT / 'idelibs/codehelpers/game'
VALUES = dict(re.findall(r'values.insert\(QStringLiteral\("([A-Z_]+)"\), QStringLiteral\("(\d+)"\)\);', (ROOT/'gamehelpertemplates.h').read_text()))
for ext in ('c','h'):
    template = (BASE / f'worldobjects.rule{ext}').read_text()
    assert '@IDE{' in template
    rendered = re.sub(r'@IDE\{([A-Z_][A-Z0-9_]*)\}', lambda m: VALUES[m.group(1)], template)
    assert '@IDE{' not in rendered
    assert not (BASE / f'worldobjects.{ext}').exists()
    if ext == 'c':
        assert 'object->spring_strength = 10;' in rendered
        assert 'object->enemy_defeat_frames = 20;' in rendered
    else:
        assert '#define GAME_WORLD_OBJECT_FIRST_TYPE 1u' in rendered
print('Stage 4.44 worldobjects render checks passed')
