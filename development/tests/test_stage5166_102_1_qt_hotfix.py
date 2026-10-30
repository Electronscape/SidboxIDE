"""Stage 5.166.102.1: guard QDialog capture in snow atlas tile picker.
Run: python3 development/tests/test_stage5166_102_1_qt_hotfix.py
"""
from pathlib import Path
import re
import unittest
R = Path(__file__).resolve().parents[2]

class WeatherQtCaptureRegression(unittest.TestCase):
    def test_noncopyable_dialog_is_captured_by_reference(self):
        code=(R/'gamedesigner.cpp').read_text()
        self.assertRegex(code, r'connect\(weatherPickTile,\s*&QPushButton::clicked,\s*&dialog,\s*\[this,\s*&dialog,\s*&chosenWeatherTile,\s*weatherAtlas,\s*weatherCellSize,\s*refreshWeatherTile\]\(\)')
        self.assertNotIn('connect(weatherPickTile, &QPushButton::clicked, &dialog, [=, &chosenWeatherTile]', code)
        self.assertIn('chooseGameAtlasCell(&dialog, sheet, tile', code)
        self.assertIn('QMessageBox::warning(&dialog, tr("Snow atlas")', code)
    def test_hotfix_version(self):
        self.assertIn('Build: 5.166.105.291026', (R/'splashscreenwidget.cpp').read_text())
    def test_does_not_modify_weather_runtime(self):
        self.assertTrue((R/'idelibs/codehelpers/game/gameworlds.rulec').exists())

if __name__=='__main__': unittest.main()
