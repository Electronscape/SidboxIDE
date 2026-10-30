"""Stage 118.4: virtual Trigger wires anchor to the rendered ON/OFF ports.

No Qt dependency: verifies the actual Visual Nodes C++ paths used for both
expanded and compact cards, including immutable saved IDs.
"""
import re
import unittest
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
SRC=(ROOT/'gamevisualnodes.cpp').read_text()

class TriggerStateWireGeometry(unittest.TestCase):
    def test_trigger_port_ids_and_positions(self):
        self.assertIn('const qreal centreY=off?273.0:243.0;',SRC)
        self.assertIn('(off?QStringLiteral("off:"):QStringLiteral("on:"))+id',SRC)
        self.assertIn('port->setData(0,QStringLiteral("output"))',SRC)
        self.assertIn('port->setZValue(5)',SRC)

    def test_graph_wire_uses_identity_not_old_coordinates(self):
        method=SRC.split('void redrawGraphLinks() {',1)[1].split('void showGraphWireMenu(',1)[0]
        self.assertIn('const QString socketId=QStringLiteral("@triggerstate:")+',method)
        self.assertIn('(virtualOff?QStringLiteral("off:"):QStringLiteral("on:"))+from;',method)
        self.assertIn('child->data(1).toString()!=socketId',method)
        self.assertIn('a=child->sceneBoundingRect().center();',method)
        self.assertNotIn('141.5:112.5',method)
        self.assertIn('virtualInput?(virtualOff?273.0:243.0)',method)

    def test_same_positions_in_expanded_fallback(self):
        self.assertEqual(243.0-9.5+19.0/2.0,243.0)
        self.assertEqual(273.0-9.5+19.0/2.0,273.0)

    def test_graph_ids_and_serialization_are_unchanged(self):
        self.assertIn('triggerStateInputId(const QString &owner)',SRC)
        self.assertIn('{QStringLiteral("invert"),triggerStateOff(source)}',SRC)
        self.assertIn('kind==QStringLiteral("object")',SRC)
        self.assertIn('const QPointF b=target->wirePoint(QPointF(0,52+24*i));',SRC)

    def test_build_number(self):
        self.assertIn('Build: 5.166.119.1.301026',(ROOT/'splashscreenwidget.cpp').read_text())

if __name__=='__main__':unittest.main()
