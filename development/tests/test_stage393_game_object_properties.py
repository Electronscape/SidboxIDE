#!/usr/bin/env python3
"""Source regression for Stage 3.93: Qt UI only, no existing game API changes."""
from pathlib import Path
import re
base = Path(__file__).resolve().parents[2]
source = (base / 'gamedesigner.cpp').read_text()
fn = source.split('void SidboxGameDesigner::configureGameObject(int index)', 1)[1].split('void SidboxGameDesigner::refreshObjectHitbox()', 1)[0]
assert 'QListWidget#GGObjectTypes' in fn
assert 'setObjectName(QStringLiteral("GGSectionHeader"))' in fn
assert 'setCheckable(true)' in fn
assert 'QSlider(Qt::Horizontal' in fn and 'QSpinBox::setValue' in fn
assert 'LIVE PREVIEW' in fn and 'COLLISION PREVIEW' in fn
assert 'QTimer::timeout' in fn and 'cachedImage(resolvedPath(old.path))' in fn
assert 'colour(m_theme.accent)' in fn
for section in ['General', 'Visual & Movement', 'Physics / Collision', 'Breakable',
                'Hazard / Murder Object', 'Collectable', 'Audio Events / Spring',
                'Audio Events / Hazard', 'Linked Object', 'Switch & Trigger']:
    assert f'makeCard(tr("{section}")' in fn, section
for ctrl in ['sfxBreakHit','sfxBreakBounce','sfxBreakFinish','sfxHazardHit',
             'sfxHazardBounce','sfxHazardAmbient','behindTiles','targetObject',
             'spline','hazardColour','springJumpBoost','triggerMusicAction']:
    assert ctrl in fn,ctrl
for behaviour in ['collectable','lift','conveyor','spring','trigger','door','deathzone','breakable','hazard','decoration']:
    assert f'QStringLiteral("{behaviour}")' in fn, behaviour
assert 'animationCard.panel->setVisible(isObject && animated->isChecked())' in fn
assert 'audioHazardCard.panel->setVisible(isHazard)' in fn
assert 'audioBreakCard.panel->setVisible(isBreak)' in fn
assert 'collectCard.panel->setVisible(isCollect)' in fn
assert 'linkedCard.panel->setVisible(isTrigger || isKey)' in fn
for field in ['objectType', 'pickupKind','sfxBreakHit','sfxBreakBounce',
              'sfxHazardHit','sfxHazardAmbient','drawBehindTiles',
              'hazardFlashColour','hazardFlashFrames','animTicks']:
    assert re.search(r'\br\.'+field+r'\s*=',fn),field
assert fn.count('form->addRow(') >= 30
assert 'No rounded' not in fn # Don't annoy Kim with the running joke :-)
print('PASS: Stage 3.93 grouped, contextual, theme-driven Game Object Properties')
