"""Regression for Stage 5.143's invisible particle settings card."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
source = (root / 'gamedesigner.cpp').read_text()

assert 'const PropertyCard particleCard = makeCard(tr("Scenery Particle Spawner"));' in source
assert 'form = particleCard.form;' in source
assert 'particleCard.panel->setVisible(behaviour == QStringLiteral("particle_emitter"));' in source

# Qt widgets must be inserted into the actual scrolled column: construction
# and setVisible() alone leave an unparented card invisible forever.
layout = re.search(r'for \(const PropertyCard &card : \{(.*?)\}\) \{\s*propertiesLayout->addWidget\(card\.panel\);', source, re.S)
assert layout, 'Properties card list/layout missing'
cards = re.findall(r'\b\w+Card\b', layout.group(1))
assert cards.count('particleCard') == 1, 'Particle card is not in the properties layout exactly once'
assert cards.index('particleCard') > cards.index('enemyCard')
assert cards.index('particleCard') < cards.index('gotoCard')

for control in ('particlePreset', 'particleW', 'particleH', 'particleCount',
                'particleInterval', 'particleLifetime', 'particleWind',
                'particleFall', 'particleGravity', 'particleFlutter'):
    assert control in source

print('Stage 5.144: Particle Spawner card is displayed in properties layout (PASS)')
