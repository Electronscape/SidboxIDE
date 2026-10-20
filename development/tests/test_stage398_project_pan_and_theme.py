#!/usr/bin/env python3
"""Source integration: save/load of per-design pan, visual theme and delay export."""
from pathlib import Path
p=Path(__file__).resolve().parents[2]
read=lambda n:(p/n).read_text()
tile=read('gametilemap.cpp'); model=read('gametilemapmodel.cpp'); hdr=read('gametilemap.h')
assert 'int viewPanX = 0' in hdr and 'int viewPanY = 0' in hdr
assert 'result.insert(QStringLiteral("viewPanX"), viewPanX)' in model
assert 'result.insert(QStringLiteral("viewPanY"), viewPanY)' in model
assert 'viewPanX = qBound(0, object.value(QStringLiteral("viewPanX")).toInt(0)' in model
assert 'm_map.viewPanX = m_canvas->horizontalScrollBar()->value()' in tile
assert 'm_map.viewPanY = m_canvas->verticalScrollBar()->value()' in tile
assert 'm_canvas->horizontalScrollBar()->setValue(m_map.viewPanX * m_canvas->zoom)' in tile
assert 'm_canvas->verticalScrollBar()->setValue(m_map.viewPanY * m_canvas->zoom)' in tile
assert 'GameTilemapEditor/pan/' not in tile
assert 'if (result == QDialog::Accepted && m_canvas)' in tile
anim=read('gameanimationeditor.cpp')
for old in ['background:#10161e', 'background:#24282c','QColor(16, 25, 35)', 'QColor(21, 33, 46)', '#f0465d']:
    assert old not in anim,old
for themefield in ['m_theme.windowBackground','m_theme.panelBackground','m_theme.inputBackground',
                   'm_theme.accent','m_theme.border','m_theme.mutedText','m_theme.hover']:
    assert themefield in anim
assert 'new AnimationFrameCardDelegate(m_theme, m_timeline)' in anim
assert 'animationStateIcon(state, m_theme)' in anim
assert 'directionModeGlyph(n, m_theme)' in anim
ui=read('gamedesigner.cpp'); exp=read('gamedesigner_export.cpp'); proj=read('gamedesigner_project.cpp'); rh=read('gamedesigner.h')
assert 'Spline start delay' in ui and 'splineDelay->setEnabled' in ui
assert 'r.objectSplineStartDelay = splineDelay->value()' in ui
assert 'int objectSplineStartDelay = 0' in rh
assert 'QStringLiteral("splineStartDelay")' in proj
assert 'r.objectSplineStartDelay' in exp
assert 'spline_start_delay' in exp
for type in ('worldobjects','collectables'):
    assert 'spline_start_delay' in read(f'idelibs/codehelpers/game/{type}.h')
    assert 'move_frames -= waiting;' in read(f'idelibs/codehelpers/game/{type}.c')
print('PASS: project pan JSON, light-theme coverage, per-object spline delay save/export/runtime')
