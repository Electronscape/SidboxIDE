"""Stage 118.2: readable Trigger output labels must not be hidden under the settings widget."""
import re
import unittest
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
UI=(ROOT/'gamevisualnodes.cpp').read_text()

class TriggerLabels(unittest.TestCase):
    def test_outputs_have_visible_labels(self):
        self.assertIn('tr("ON ACTIVATE")',UI)
        self.assertIn('tr("STATE ON")',UI)
        self.assertIn('tr("STATE OFF")',UI)
        self.assertIn('tr("Virtual switch")',UI)
        self.assertIn('trigger?298:',UI)
    def test_labels_below_embedded_control_panel(self):
        # Panel is anchored at y=79 and is 112px high; this used to conceal the text.
        self.assertIn('panel->setFixedSize(258,112)',UI)
        self.assertIn('proxy->setPos(8,79)',UI)
        self.assertIn('const qreal centreY=off?273.0:243.0;',UI)
        self.assertIn('centreY-textBounds.center().y()',UI)
        for centre in (243,273):
            self.assertGreater(centre-9.5,79+112)
            self.assertLessEqual(centre+9.5,298)
    def test_event_identity_unchanged(self):
        self.assertIn('QStringLiteral("@triggerstate:")+',UI)
        self.assertIn('(off?QStringLiteral("off:"):QStringLiteral("on:"))+id',UI)
        self.assertIn('port->setData(0,QStringLiteral("output"))',UI)
        self.assertIn('port->setZValue(5)',UI)
    def test_build_version(self):
        self.assertIn('Build: 5.166.119.1.301026',(ROOT/'splashscreenwidget.cpp').read_text())

if __name__=='__main__':unittest.main()
