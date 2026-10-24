#!/usr/bin/env python3
"""Stage 5.59 source/data regression checks. Not a Qt GUI compilation."""
from pathlib import Path
import json
import tarfile

base = Path(__file__).resolve().parents[2]
src = (base / 'gametitlescreeneditor.cpp').read_text()
assert 'QTableWidget' in src
assert 'QObject::tr("Option Name")' in src
assert 'QObject::tr("Destination World")' in src
assert 'QObject::tr("Player Start")' in src
assert 'QGraphicsItem::ItemIsMovable' in src
assert 'fitInView(QRectF(0,0,480,320)' in src
assert 'SidboxPpb::read' in src
assert 'QSaveFile' in src
assert 'QStringLiteral("titleArt")' in src
assert 'QStringLiteral("subtitleArt")' in src
assert 'QStringLiteral("display")' in src
assert 'QJsonValue(QJsonValue::Null)' in src
assert 'savedMenuExists' in src
assert 's.value(QStringLiteral("id"))' in src
assert 'e.start=startCombo->currentData()' not in src  # Actual source uses entries[row]
assert 'startCombo->currentData().toString()' in src
assert 'QStringLiteral("audio")' in src and 'QStringLiteral("music")' in src
assert 'Build: 5.63.231026' in (base / 'splashscreenwidget.cpp').read_text()
assert 'gametitlescreeneditor.cpp' in (base / 'CMakeLists.txt').read_text()

# Exercise the schema contract with the uploaded two-world design.
example = Path('/mnt/data/GameTest3 - 23-10-2026-1549.tar.gz')
if example.exists():
    with tarfile.open(example, 'r:gz') as tf:
        worlds = {}
        for member in tf:
            if member.name.endswith('.sbgm'):
                doc = json.load(tf.extractfile(member))
                worlds[Path(member.name).stem] = {s['id']:s.get('name','') for s in doc['playerStarts']}
        assert 'world1' in worlds and 'forest' in worlds
        assert any(name == 'Door 1 start' for name in worlds['forest'].values())
        assert any(name == 'Door 1 start' for name in worlds['world1'].values())
        assert 'audio/music1.spc' in tf.getnames()
print('Stage 5.59 Title Screen source and GameTest3 schema checks: PASS')
