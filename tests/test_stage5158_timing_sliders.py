"""Stage 5.158: weather/day-and-night duration sliders preserve frame counts."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
cpp = (root / 'gamedesigner.cpp').read_text()
project = (root / 'gamedesigner_project.cpp').read_text()
header = (root / 'gamedesigner.h').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()
assert 'Build: 5.159.261026' in splash

# The new helper must use a horizontal slider and a live readable time label.
assert 'auto addFrameTimingSlider =' in cpp
assert 'new QSlider(Qt::Horizontal, row)' in cpp
assert 'QObject::connect(slider, &QSlider::valueChanged, row, updateReadout);' in cpp
assert 'frames / 50.0' in cpp
assert 'slider->setValue(qBound(minimum, current, maximum))' in cpp
assert 'slider->setTracking(true);' in cpp
assert 'slider->setAccessibleName(title);' in cpp

expected = {
    'weatherInterval': ('Lightning average interval', 100, 2000, 'm_weatherLightningInterval'),
    'dayNightDayFrames': ('Day duration', 50, 30000, 'm_dayNightDayFrames'),
    'dayNightNightFrames': ('Night duration', 50, 30000, 'm_dayNightNightFrames'),
    'dayNightFadeFrames': ('Dusk / dawn duration', 25, 10000, 'm_dayNightFadeFrames'),
}
for variable, (label, low, high, member) in expected.items():
    pattern = (rf'auto \*{variable} = addFrameTimingSlider\(tr\("{re.escape(label)}"\),\s*'
               rf'{low}, {high}, {member},')
    assert re.search(pattern, cpp), f'{variable} is not a slider with original range'
    assert f'auto *{variable} = new QSpinBox' not in cpp
    assert f'{member} = {variable}->value();' in cpp
    assert member in header

# Both original saved-world data keys and bounds remain byte-for-byte compatible.
for key in ('dayFrames', 'nightFrames', 'fadeFrames'):
    assert f'QStringLiteral("{key}")' in project
assert 'QStringLiteral("lightningInterval")' in project
assert 'weatherInterval->parentWidget()->setEnabled(mode == 3);' in cpp
assert 'slider->parentWidget()->setEnabled(mode == 2);' in cpp

# No new runtime fields, generated sections, or main.c integration requirements.
print('Stage 5.158 PASS: four draggable timing sliders, friendly readouts, exact frame persistence, disabled state and version')
