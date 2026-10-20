#!/usr/bin/env python3
"""Stage 3.95: theme integration, object flags and generated Hurt-state guard."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
read=lambda name:(root/name).read_text()
ui=read('gamedesigner.cpp')
proj=read('gamedesigner_project.cpp')
header=read('gamedesigner.h')
export=read('gamedesigner_export.cpp')
anim=read('gameanimationeditor.cpp')
animh=read('gameanimationeditor.h')

assert 'GameObjectProperties/maximized' in ui
assert 'objectWindowWasMaximized' in ui and 'objectWindowSettings.setValue' in ui
assert 'Visual & Movements' in ui
assert 'gr_icon_spline.png' in ui and 'splineResourceIcon, path.name, path.id' in ui
assert 'r.objectFlipX = objectFlipX->isChecked();' in ui
assert 'r.objectFlipY = objectFlipY->isChecked();' in ui
assert 'frameImage = frameImage.flipped(flipDirections);' in ui
assert 'frame = frame.flipped(flipDirections);' in ui
assert 'bool objectFlipX = false, objectFlipY = false' in header
for field in ('objectFlipX','objectFlipY'):
    assert f'QJsonLiteral("{field}")' not in proj # Uses QStringLiteral consistently.
    assert f'QStringLiteral("{field}")' in proj
    assert f'r.{field}' in proj
    assert f'r.{field}' in export
assert export.count('BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y') == 4 # object + 3 decoration draw paths
assert '#ifdef PLAYER_ANIM_STATE_HURT' not in export
assert '#if defined(PLAYER_ANIM_HAS_HURT_STATE) && PLAYER_ANIM_HAS_HURT_STATE' in export
assert '#define %1_HAS_HURT_STATE %2' in anim
assert 'm_states.contains(QStringLiteral("Hurt"), Qt::CaseInsensitive)' in anim
assert 'const IDETheme &theme = defaultIDETheme()' in animh
assert 'this, m_theme);' in ui
assert 'QColor(244, 70, 95)' not in anim
assert '#f0465d' not in anim
assert 'new AnimationFrameCardDelegate(m_theme, m_timeline)' in anim
assert 'QColor(16, 25, 35)' not in anim
assert 'QDialog { background:#10161e' not in anim
assert 'atlas->accent = m_theme.accent' in anim
print('PASS: Stage 3.95 object flips, persistence, accent themes, maximized state, spline icons, Hurt guard')
