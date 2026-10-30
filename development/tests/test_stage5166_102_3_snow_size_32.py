"""Stage 5.166.102.3: all project/editor/export/runtime snow size caps agree."""
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[2]

def read(path): return (ROOT/path).read_text()

class SnowSize32(unittest.TestCase):
    def test_ide_slider_spinbox_and_help(self):
        code=read('gamedesigner.cpp')
        self.assertIn('weatherSizeSlider->setRange(2, 32);',code)
        self.assertIn('weatherSize->setRange(2, 32);',code)
        self.assertIn('Snowflake diameter (2-32 px).',code)
        self.assertIn('weatherSizeSlider->setValue(m_weatherParticleSize);',code)
        self.assertIn('weatherSize->setValue(m_weatherParticleSize);',code)
    def test_saved_project_load_allows_32(self):
        self.assertIn('m_weatherParticleSize = qBound(2, weather.value(QStringLiteral("particleSize")).toInt(5), 32);',read('gamedesigner_project.cpp'))
        self.assertIn('weather.insert(QStringLiteral("particleSize"), m_weatherParticleSize);',read('gamedesigner_project.cpp'))
    def test_generated_world_clamp_allows_32(self):
        self.assertIn('defaultWeatherSize << QString::number(qBound(2, weather.value(QStringLiteral("particleSize")).toInt(5), 32));',read('gameworldsnapshot.h'))
    def test_runtime_accepts_32(self):
        code=read('idelibs/codehelpers/game/gameworlds.rulec')
        self.assertIn('weather_particle_size >= 2u && world->weather_particle_size <= 32u',code)
        self.assertIn('weather_particle_size; /* 2..32;',code)
        self.assertIn('const int32_t size = weather_particle_size;',code)
        self.assertIn('bob.scale = (uint16_t)(((uint32_t)weather_particle_size * 100u) / tile_size)',code)
    def test_atlas_preview_and_default(self):
        code=read('gamedesigner.cpp')
        self.assertIn('glyph.scaled(m_weatherParticleSize,',code)
        self.assertIn('drops.addEllipse(px,py,m_weatherParticleSize,m_weatherParticleSize)',code)
        self.assertIn('m_weatherParticleSize = 5;',read('gamedesigner.h'))
        self.assertIn('Build: 5.166.105.291026',read('splashscreenwidget.cpp'))
    def test_no_old_limit_in_active_weather_code(self):
        for p in ('gamedesigner.cpp','gamedesigner.h','gamedesigner_project.cpp',
                  'gameworldsnapshot.h','idelibs/codehelpers/game/gameworlds.rulec'):
            code=read(p)
            self.assertNotIn('Snowflake diameter (2-16 px)',code)
            self.assertNotIn('weather_particle_size <= 16u',code)
            self.assertNotIn('weatherSizeSlider->setRange(2, 16);',code)

if __name__=='__main__': unittest.main()
