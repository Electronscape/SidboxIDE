import pathlib
import re
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[2]
NODE = (ROOT / "gamevisualnodes.cpp").read_text()
SPLASH = (ROOT / "splashscreenwidget.cpp").read_text()

class ArrivalPicker(unittest.TestCase):
    def test_event_classification(self):
        self.assertIn('const bool arrivalLogicSource=eventOutputPort', NODE)
        self.assertIn('eventKey(from)==QStringLiteral("arrival")', NODE)
        self.assertIn('m_objects.value(eventOwner(from)).type==QStringLiteral("lift")', NODE)

    def test_logic_creation_is_supported(self):
        self.assertIn('if (objectSource || arrivalLogicSource)', NODE)
        self.assertIn('createGraphLogic(from,at,selectedId.mid(QStringLiteral("@logic:").size()))', NODE)
        self.assertIn('if (!objectSource && !arrivalLogicSource)return;', NODE)
        for op in ('boolean','and','or','not'):
            self.assertIn('QStringLiteral("@logic:%s")'%op, NODE)

    def test_menu_is_first_and_expanded(self):
        self.assertIn('tree->takeTopLevelItem(previousIndex)', NODE)
        self.assertIn('tree->insertTopLevelItem(0,first)', NODE)
        self.assertIn('logicRoot->setExpanded(true)', NODE)
        self.assertIn('ON ARRIVAL: choose Logic below', NODE)

    def test_save_runtime_unchanged_and_build_label(self):
        self.assertIn('Build: 5.166.111.1.291026', SPLASH)
        self.assertIn('GOLD ON ARRIVAL', NODE)

if __name__=='__main__': unittest.main()
