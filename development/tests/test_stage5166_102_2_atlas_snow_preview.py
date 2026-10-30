"""Stage 5.166.102.2 source regression: world preview renders the selected atlas snow tile.
Run: python3 development/tests/test_stage5166_102_2_atlas_snow_preview.py
"""
from pathlib import Path
import unittest
R = Path(__file__).resolve().parents[2]
H = (R/'gamedesigner.h').read_text()
C = (R/'gamedesigner.cpp').read_text()

class SnowPreview(unittest.TestCase):
    def test_atlas_pixel_source_matches_generator(self):
        self.assertIn('resource.id != m_weatherParticleAtlasId',C)
        self.assertIn('m_weatherParticleTile - 1',C)
        self.assertIn('sheet.copy((index % columns) * cell,',C)
        self.assertIn('colourPreviewBank(colours, true, true)',C)
        self.assertIn('glyph.scaled(m_weatherParticleSize,',C)
        self.assertIn('Qt::FastTransformation',C)
        self.assertIn('SidboxPpb::read(filename, &picture)',C)
    def test_atlas_graphics_actually_draw_in_world_preview(self):
        self.assertIn('m_weatherPreviewSnowTiles = m_scene->addPixmap(QPixmap())',C)
        self.assertIn('snowPainter.drawImage(QPoint(int(drawX), int(drawY)), m_weatherPreviewSnowGlyph)',C)
        self.assertIn('m_weatherPreviewSnowTiles->setPixmap(QPixmap::fromImage(snowOverlay))',C)
        self.assertIn('m_weatherPreviewSnowTiles->setPos(cameraX, cameraY)',C)
        self.assertIn('m_weatherPreviewSnowTiles->setZValue(10505)',C)
        self.assertIn('m_weatherPreviewSnowTiles->setAcceptedMouseButtons(Qt::NoButton)',C)
    def test_fallback_lifecycle_and_caching(self):
        self.assertIn('m_weatherPreviewSnowTiles->setVisible(false)',C)
        self.assertIn('m_weatherPreviewDrops->setVisible(!atlasSnow)',C)
        self.assertIn('drops.addEllipse(px,py,m_weatherParticleSize,m_weatherParticleSize)',C)
        self.assertIn('m_weatherPreviewSnowGlyphKey != cacheKey',C)
        self.assertIn('file.lastModified().toMSecsSinceEpoch()',C)
        self.assertIn('paletteStamp',C)
        self.assertIn('m_weatherPreviewSnowTiles = nullptr;',H)
        self.assertIn('m_weatherPreviewSnowTiles = nullptr;',C)
        self.assertIn('m_weatherPreviewSnowGlyphKey.clear()',C)
    def test_no_generated_runtime_changes(self):
        self.assertTrue((R/'idelibs/codehelpers/game/gameworlds.rulec').is_file())
        self.assertIn('Build: 5.166.105.291026', (R/'splashscreenwidget.cpp').read_text())

if __name__=='__main__': unittest.main()
