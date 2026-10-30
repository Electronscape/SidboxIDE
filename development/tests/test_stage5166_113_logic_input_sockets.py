"""Stage 5.166.113: dynamic numbered input ports, display-only graph editor."""
from pathlib import Path
import re
import unittest

ROOT=Path(__file__).resolve().parents[2]
S=(ROOT/'gamevisualnodes.cpp').read_text()
OLD=(ROOT/'gamevisualgraphlogic.h').read_text()

class GraphPorts(unittest.TestCase):
    def test_existing_semantics_unchanged(self):
        self.assertIn('n.op==QStringLiteral("or") ? (rawInputs.size()<2 || rawInputs.size()>8) : rawInputs.size()<2',OLD)
        self.assertIn('if(rawInputs.size()>16',OLD)
        self.assertIn('op==QStringLiteral("and")?',S)
        self.assertIn('qMin(16,qMax(2,static_cast<int>(inputs.size())+1))',S)
        self.assertIn('op==QStringLiteral("or")?qMin(8,qMax(2,static_cast<int>(inputs.size())+1)):1',S)

    def test_visible_minimum_and_expansion(self):
        for inputs in range(0,17):
            and_slots=min(16,max(2,inputs+1))
            self.assertGreaterEqual(and_slots,2)
            self.assertLessEqual(and_slots,16)
            if inputs < 16: self.assertGreater(and_slots,inputs)
            else: self.assertEqual(and_slots,16)
            result_y=86+24*(and_slots-1)
            bottom=result_y+60+59
            self.assertGreater(result_y,52+24*(and_slots-1)+14)
            self.assertGreater(bottom,result_y+60)
        self.assertIn('graph-input-label',S)
        self.assertIn('INPUT %1: (connect)',S)
        self.assertIn('INPUT %1: %2',S)

    def test_endpoint_per_input_instead_of_stack(self):
        self.assertIn('target->wirePoint(QPointF(0,52+24*i))',S)
        self.assertNotIn('const QPointF b=target->wirePoint(QPointF(0,58));\n                    append(a,b,QColor(105,206,207)',S)
        self.assertIn('socket->setRect(QRectF(-7,45+24*i,14,14));',S)
        self.assertIn('label->setPos(10,43+24*i);',S)
        self.assertIn('syncGraphCardSockets(cardId);',S)
        self.assertIn('syncGraphCardSockets(key);',S)

    def test_collapsed_and_outputs_follow_layout(self):
        self.assertIn('graphInputs)*17.0',S)
        self.assertIn('child->data(2).toInt()',S)
        self.assertIn('original.y()<132.0?',S)
        for role in ('graph-result-port','graph-true-port','graph-false-port','graph-operator'):
            self.assertIn(role,S)
        self.assertIn('card->setFullHeight(falseY+59)',S)
        self.assertIn('if(folded)card->setCollapsed(true)',S)

    def test_disconnect_and_save_unchanged(self):
        self.assertIn('inputs.removeAt(index);n.insert(QStringLiteral("inputs"),inputs);',S)
        self.assertIn('inputs.append(input);node.insert(QStringLiteral("inputs"),inputs);',S)
        self.assertIn('object.insert(QStringLiteral("logicNodes"),node.logicNodes);',S)
        self.assertIn('Build: 5.166.114.291026',(ROOT/'splashscreenwidget.cpp').read_text())

if __name__=='__main__': unittest.main()
