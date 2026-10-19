from pathlib import Path
root=Path(__file__).resolve().parents[2]
load=(root/'gamedesigner_project.cpp').read_text()
hdr=(root/'gamedesigner.h').read_text()
ui=(root/'gamedesigner.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
helper=(root/'idelibs/codehelpers/game/worldobjects.c').read_text()
for key in ['breakTouch','breakBounce','breakHits','breakStrength','breakLaunchX']:
    assert key in hdr and f'object.value(QStringLiteral("{key}"))' in load
    assert f'object.insert(QStringLiteral("{key}"),' in load
assert 'QStringLiteral("breakable")' in load
assert 'GAME_OBJECT_BREAKABLE' in export and 'break_hits_required' in export
assert 'game_world_object_start' in helper and 'break_triggered' in helper
assert 'm_objectPreviewTimer->setInterval(20)' in ui
assert 'm_objectPreviewClock.elapsed() / 20' in ui
assert 'r.animMode == QStringLiteral("pingpong")' in ui
assert 'r.animMode == QStringLiteral("once")' in ui
assert 'tr("LOOP %1")' in ui and 'm_loopOverlayItems.append(ring)' in ui
assert 'setAcceptedMouseButtons(Qt::NoButton)' in ui
print('PASS: Stage 3.89 breakable settings save/load/export, previews and loop guides')
