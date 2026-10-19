"""Stage 3.92a: catch accidental duplicated Resource field declarations.

The compiler caught duplicated hazard fields in Stage 3.92. This lightweight
check runs even on machines without the Qt6 development headers installed.
"""
from collections import Counter
from pathlib import Path
import re

header = (Path(__file__).resolve().parents[2] / 'gamedesigner.h').read_text()
assert '    struct Resource {' in header
resource = header.split('    struct Resource {', 1)[1].split('    };', 1)[0]
fields = []
for line in resource.splitlines():
    line = line.split('//', 1)[0].strip()
    match = re.match(r'^(?:bool|int|QString|SidboxAudioSettings)\s+(.+?);$', line)
    if match:
        fields.extend(part.split('=', 1)[0].strip() for part in match.group(1).split(','))
duplicates = sorted(name for name, count in Counter(fields).items() if count > 1)
assert not duplicates, f'Duplicate SidboxGameDesigner::Resource members: {duplicates}'
for name in (
    'drawBehindTiles', 'hazardDamage', 'hazardKickX', 'hazardKickY',
    'hazardKick', 'hazardHurtAnimation', 'hazardFlash',
    'hazardFlashColour', 'hazardFlashCount', 'hazardFlashFrames',
    'sfxHazardHit', 'sfxHazardBounce', 'sfxHazardAmbient'
):
    assert fields.count(name) == 1, f'Missing or repeated member: {name}'
print('PASS: all Resource members unique; hazard properties/sound IDs declared exactly once')
