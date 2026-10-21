#!/usr/bin/env python3
"""Stage 4.41a: enemy reward X/Y must be immediately visible and usable."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
src = (root / 'gamedesigner.cpp').read_text()
start = src.index('form = enemyCard.form;')
end = src.index('auto *enemyHits =', start)
reward = src[start:end]
# The enemy's reward launch settings must not be squeezed into one combined row.
assert 'pairFields(tr("Reward speed X")' not in reward
assert 'form->addRow(tr("Reward speed X (px/frame)"), enemyRewardXField);' in reward
assert 'form->addRow(tr("Reward speed Y (px/frame)"), enemyRewardYField);' in reward
assert reward.index('Item dropped when defeated') < reward.index('Launch dropped item on defeat') < reward.index('Reward speed X (px/frame)') < reward.index('Reward speed Y (px/frame)')
assert 'enemyRewardXField->setEnabled(launch);' in reward
assert 'enemyRewardYField->setEnabled(launch);' in reward
assert 'enemyRewardImpulse->setEnabled(hasDrop);' in reward
assert 'connect(enemyRewardImpulse, &QCheckBox::toggled' in reward
assert 'connect(enemyReward, qOverload<int>(&QComboBox::currentIndexChanged)' in reward
# UI-only: the saved values and generated runtime impulse haven't changed.
assert 'r.breakRewardVx = newType == QStringLiteral("enemy") ? enemyRewardVx->value() : breakRewardVx->value();' in src
assert 'r.breakRewardVy = newType == QStringLiteral("enemy") ? enemyRewardVy->value() : breakRewardVy->value();' in src
assert 'enemyCard.panel->setVisible(isEnemy);' in src
assert 'propertiesLayout->addWidget(card.panel);' in src
print('PASS: enemy reward launch controls visible as separate rows with correct enabling and persistence')
