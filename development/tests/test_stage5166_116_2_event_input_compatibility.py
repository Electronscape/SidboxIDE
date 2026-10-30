from pathlib import Path
import unittest, re, json
ROOT=Path(__file__).resolve().parents[2]
HEADER=(ROOT/'gamevisualgraphlogic.h').read_text()
UI=(ROOT/'gamevisualnodes.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()

class BreakableEventInputs(unittest.TestCase):
    def test_parser_uses_all_three_event_names(self):
        for kind in ['arrival','hit','destroy']:
            self.assertIn(f'StringLiteral("@event:{kind}:")', HEADER)
    def test_error_reports_correct_input(self):
        self.assertIn('Logic node %1 INPUT %2 is invalid', HEADER)
        self.assertIn('arg(inputIndex+1)', HEADER)
        self.assertIn('in.id.section(QLatin1Char(\':\'),2).isEmpty()',HEADER)
    def test_pulses_pass_to_stored_graph_inputs(self):
        self.assertIn('input={{QStringLiteral("kind"),QStringLiteral("event")}', UI)
        self.assertIn('input={{QStringLiteral("kind"),QStringLiteral("object")}', UI)
        self.assertIn('QStringLiteral("@event:destroy:")+platforms.at(i)->id', EXPORT)
        self.assertIn('QStringLiteral("@event:hit:")+platforms.at(i)->id', EXPORT)
        self.assertIn('SidboxVisualLogic::expression(node,objectSlot,expressionNames)',EXPORT)
    def test_two_real_inputs_not_visual_spare(self):
        self.assertIn('static_cast<int>(inputs.size())+1',UI)
        self.assertIn('i<inputs.size()',UI)
        self.assertIn('QJsonArray inputs=node.value(QStringLiteral("inputs")).toArray()',UI)
        self.assertIn('inputs.append(input);node.insert(QStringLiteral("inputs"),inputs);',UI)
    def test_splash(self):
        self.assertRegex((ROOT/'splashscreenwidget.cpp').read_text(),r'Build: 5\.166\.116\.(?:2|3|4)\.301026')

if __name__=='__main__':unittest.main()
