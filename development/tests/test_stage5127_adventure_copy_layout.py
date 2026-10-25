#!/usr/bin/env python3
"""Stage 5.127: verify complete cross-world field coverage and matching frame grids.

This is a source contract test. The actual Qt6 window must still be compiled
and checked on Fedora because this test environment lacks Qt6 development libs.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
s = (root / 'gameadventureeditor.cpp').read_text()

# These are the exact keys emitted when the Adventure dialog is saved.
position_fields = {
    'dialogX': 'dialogX', 'dialogY': 'dialogY',
    'dialogWidth': 'dialogW', 'dialogHeight': 'dialogH',
    'dialogPadding': 'textPadding',
    'thoughtX': 'thoughtX', 'thoughtY': 'thoughtY',
    'thoughtWidth': 'thoughtW', 'thoughtHeight': 'thoughtH',
    'dialogFontScaleX': 'dialogScaleX', 'dialogFontScaleY': 'dialogScaleY',
    'thoughtFontScaleX': 'thoughtScaleX', 'thoughtFontScaleY': 'thoughtScaleY',
    'thoughtAboveDialog': 'stacking',
    'textColourIndex': 'chosenText',
    'thoughtTextColourIndex': 'chosenThoughtText',
}
atlas_fields = [
    'skinAtlasId', 'tileSize', 'framesPerChar',
    'textColourIndex', 'thoughtTextColourIndex',
    'textOutline', 'outlineColourIndex',
    'skinIndices', 'skinFlips', 'thoughtSkinIndices', 'thoughtSkinFlips',
]

# Delimit both copy callbacks and saved-state writer without Qt parsing.
pos = s.split('QObject::connect(copyPosition, &QPushButton::clicked, &dialog, [&] {', 1)[1].split(
    'QObject::connect(placement,QOverload<int>::of(&QComboBox::currentIndexChanged)', 1)[0]
atlas = s.split('QObject::connect(copyAtlas, &QPushButton::clicked, &dialog, [&] {', 1)[1].split(
    'tabs->addTab(skinPage,QObject::tr("Dialogue + Thought Atlas"))', 1)[0]
saved = s.split('result.insert("npcs",outNpcs)', 1)[1].split('*payload=result;return true;', 1)[0]

for key, destination in position_fields.items():
    assert f'"{key}"' in saved, f'{key} is not saved'
    assert f'"{key}"' in pos, f'{key} missing from Dialogue Position copy'
    assert re.search(r'\b'+re.escape(destination)+r'(?:->set(?:Value|CurrentIndex)\(|\s*=)', pos), (
        f'{destination} is not updated on position copy')
for key in atlas_fields:
    assert f'"{key}"' in saved, f'{key} is not saved'
    assert f'"{key}"' in atlas, f'{key} missing from Atlas copy'

# Additional essential UX contract: updated preview and colour buttons.
assert 'decorateColour(textColour,chosenText)' in pos
assert 'decorateColour(thoughtTextColour,chosenThoughtText)' in pos
assert 'refreshPosition();' in pos
assert 'refreshFrameControls();' in atlas
assert 'refreshInventoryIcons();' in atlas
assert 'updatePreview();' in atlas
assert 'matchAdventureAtlas(&dialog, source, atlases)' in atlas
assert 'if (atlasIndex < 0) return;' in atlas

# Dialogue/Thought grid row geometry should now match.
assert 'tilePick[i]->setMinimumSize(94,58)' in s
assert 'thoughtPick[i]->setMinimumSize(94,58)' in s
assert 'flipRow->setSpacing(0)' in s
assert 'flips->setSpacing(0)' in s
assert 'thoughtPick[i]->setIconSize(QSize(40,40))' in s
assert 'tilePick[i]->setIconSize(QSize(40,40))' in s
assert 'thoughtDesignLayout->addWidget(thoughtPreview,1)' in s
assert 'dialogDesignLayout->addWidget(preview,1)' in s

# Saving, loading or copying a world must never modify the saved source world.
assert 'QIODevice::ReadOnly' in s.split('bool chooseAdventureSavedWorld(', 1)[1].split('int matchAdventureAtlas(', 1)[0]
print('PASS: all 16 Position keys and all 11 Atlas keys are copied; grids aligned')
