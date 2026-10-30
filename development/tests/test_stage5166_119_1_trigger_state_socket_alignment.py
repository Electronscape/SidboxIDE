"""Stage 119.1: Trigger virtual-state labels and wires share real socket centres."""
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
UI = (ROOT / 'gamevisualnodes.cpp').read_text()
SPLASH = (ROOT / 'splashscreenwidget.cpp').read_text()


class TriggerStateSocketAlignment(unittest.TestCase):
    def test_full_card_fits_two_state_rows_with_bottom_padding(self):
        self.assertIn('trigger?298:', UI)
        on, off, radius, bottom = 243., 273., 9.5, 298.
        self.assertGreater(off - on, 2 * radius)
        self.assertGreater(bottom - (off + radius), 12.)
        self.assertGreater(on - radius, 208. + 19.)

    def test_labels_and_ports_share_same_vertical_centre(self):
        card = UI.split('void makeObjectCard(', 1)[1].split('if (node.type==QStringLiteral("enemy")) {', 1)[0]
        self.assertIn('const qreal centreY=off?273.0:243.0;',card)
        self.assertIn('centreY-textBounds.center().y()',card)
        self.assertIn('centreY-9.5,19,19',card)
        self.assertNotIn('label->setPos(184,y-3)', card)
        self.assertNotIn('const qreal y=off?239.0:210.0;', card)

    def test_labels_end_before_the_socket(self):
        self.assertIn('width-25.0-textBounds.right()',UI)
        # Label ends x=width-25; port starts at width-9.5.
        self.assertEqual((280-9.5)-(280-25.),15.5)

    def test_graph_wire_finds_correct_named_socket(self):
        drawing=UI.split('void redrawGraphLinks() {',1)[1].split('void showGraphWireMenu(',1)[0]
        self.assertIn('const QString socketId=QStringLiteral("@triggerstate:")+',drawing)
        self.assertIn('(virtualOff?QStringLiteral("off:"):QStringLiteral("on:"))+from;',drawing)
        self.assertIn('child->data(1).toString()!=socketId',drawing)
        self.assertIn('a=child->sceneBoundingRect().center();',drawing)
        self.assertIn('virtualInput?(virtualOff?273.0:243.0):',drawing)
        self.assertNotIn('virtualInput?(virtualOff?248.5:219.5):',drawing)

    def test_saved_ids_and_actions_are_not_modified(self):
        self.assertIn('(off?QStringLiteral("off:"):QStringLiteral("on:"))+id',UI)
        self.assertIn('triggerStateInputId(const QString &owner)',UI)
        self.assertIn('const QPointF b=target->wirePoint(QPointF(0,52+24*i));',UI)
        self.assertIn('Build: 5.166.119.1.301026',SPLASH)


if __name__=='__main__':
    unittest.main()
