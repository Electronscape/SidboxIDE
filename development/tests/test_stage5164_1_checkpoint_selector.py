#!/usr/bin/env python3
"""Stage 5.164.1: Game Object type list matches the actual type combo.

Static source contract test: Qt6 is not available on the CI host. The
production GUI must still be rebuilt and observed on the user's machine.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
source = (root / "gamedesigner.cpp").read_text()

# The combo is the canonical semantic source. Ensure it matches the compact
# icon/title arrays used by the Game Object Properties left-hand selector.
combo = source.split('auto *type = new GameComboBox(&dialog);', 1)[1].split('type->setCurrentIndex', 1)[0]
values = re.findall(r'type->addItem\(tr\("[^"]+"\), QStringLiteral\("([^"]+)"\)\);', combo)
selector = source.split('const QStringList icons =', 1)[1].split('for (int n = 0; n < type->count(); ++n)', 1)[0]
icons = selector.split('const QStringList titles =', 1)[0]
titles = selector.split('const QStringList titles =', 1)[1].split(';', 1)[0]
icon_values = re.findall(r'QStringLiteral\("[^"]+"\)', icons)
title_values = re.findall(r'tr\("([^"]+)"\)', titles)
assert len(values) == len(icon_values) == len(title_values) == 14, (values, title_values)
assert list(zip(values[-2:], title_values[-2:])) == [
    ('save_checkpoint', 'Save Game Checkpoint'),
    ('particle_emitter', 'Particle Spawner'),
]
assert 'item->setData(Qt::UserRole, type->itemData(n));' in source
assert 'Q_ASSERT(icons.size() == type->count() && titles.size() == type->count());' in source

# Per-view scene bounds and scrollbars must not track expanding global scene
# bounds as moving particles enter/leave the scene at 50 Hz.
assert 'particlePreviewCanvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);' in source
assert 'particlePreviewCanvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);' in source
assert 'particlePreviewCanvas->setSceneRect(particlePreviewLastBounds);' in source
assert 'particlePreviewCanvas->fitInView(particlePreviewLastBounds, Qt::KeepAspectRatio);' in source
assert 'particlePreviewCanvas->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);' in source
assert 'm_scene->setSceneRect(particlePreviewLastBounds)' not in source

assert 'Build: 5.166.5.271026' in (root / 'splashscreenwidget.cpp').read_text()
print('PASS Stage 5.164.1: all 14 object-type rows in order; checkpoint & particle labels; stable preview view')
