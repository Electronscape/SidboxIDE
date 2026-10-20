#!/usr/bin/env python3
"""Stage 4.01 structural regression: presentational changes only."""
from pathlib import Path
import re
ROOT = Path(__file__).resolve().parents[2]
common = (ROOT/'ideglobaltheme.h').read_text()
tile = (ROOT/'gametilemap.cpp').read_text()
world = (ROOT/'gamedesigner.cpp').read_text()
assert '#include "gameeditorcontrolstyle.h"' in tile
assert '#include "gameeditorcontrolstyle.h"' in world
assert 'setStyleSheet(QString());' in tile
assert 'setStyleSheet(QString());' in world
assert 'qApp->setStyleSheet(ideGlobalControlStyle(m_theme))' in (ROOT/'mainwindow.cpp').read_text()
# Theme tokens and style rules are reusable across both editors.
for widget in ['QPushButton', 'QToolButton', 'QCheckBox::indicator:checked',
               'QComboBox::drop-down', 'QSpinBox', 'QDoubleSpinBox',
               'QSlider::handle:horizontal', 'QTabBar::tab:selected',
               'QScrollBar::handle:vertical', 'QSplitter::handle',
               'QGroupBox', 'QTreeWidget::item:selected']:
    assert widget in common, widget
assert 'border-radius:0px' in common
for field in ['theme.accent', 'theme.panelBackground', 'theme.inputBackground',
              'theme.text', 'theme.border', 'theme.hover']:
    assert field in common
assert 'chosen.lightnessF() < 0.52' in common
# No hard-coded brand highlight colours in shared code.
assert not re.search(r'#[0-9a-fA-F]{6}', common)
# Avoid substring placeholder replacement errors (@hover vs @hoverHandle).
assert 'QStringLiteral("@hover")' in common
assert 'QStringLiteral("@chosen")' in common
assert 'QStringLiteral("@scroll")' in common
# Rehearse the replacement order with dummy values: no @tokens may be left
# nor partially substituted (e.g. @hoverHandle -> #112233Handle).
css = common.split('R"GGCONTROLS(', 1)[1].split(')GGCONTROLS"', 1)[0]
tokens = re.findall(r'\{"(@[A-Za-z]+)"', common)
for token in tokens:
    if token not in ('@chosen', '@scroll', '@hover'):
        css = css.replace(token, '#112233')
for token in ('@hover', '@chosen', '@scroll'):
    css = css.replace(token, '#112233')
css = css.replace('@untick', ':/icons/checkbox_unchecked.png')  # Stage 4.16 image for both states
css = css.replace('@tick', ':/icons/checkbox_tick.png')  # Stage 4.13 optional icon URL
assert '@' not in css
assert not re.search(r'#[0-9a-fA-F]{6}[A-Za-z]', css)
# All three Stage 4.00 stamp lists retain their own highlighted-card style.
for field in ['m_stampList', 'm_collisionList', 'GGLoopTrackBank',
              'bank->setStyleSheet(selectionStyle)']:
    assert field in tile
# A narrow Tilemap sidebar must stay narrow despite themed tabs.
assert 'm_stampTabs->findChild<QTabBar *>()' in tile
assert 'tabBar->setUsesScrollButtons(true)' in tile
assert 'm_stampTabs->setMinimumWidth(250)' in tile
# World canvas palette is still controlled by original render code.
assert 'refreshColours();' in world[world.index('void SidboxGameDesigner::setTheme('):]
assert 'refreshObjectHitbox();' in world[world.index('void SidboxGameDesigner::setTheme('):]
print('PASS: shared theme control stylesheet, light-theme contrast, editors and stamp cards')
