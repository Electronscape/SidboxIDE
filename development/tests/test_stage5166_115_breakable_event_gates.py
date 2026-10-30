"""Stage 5.166.115: breakable event pulses can gate existing logic without direct actions."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
VISUAL = (ROOT / 'gamevisualnodes.cpp').read_text()
GRAPH = (ROOT / 'gamevisualgraphlogic.h').read_text()
EXPORT = (ROOT / 'gamedesigner_export.cpp').read_text()
DESIGN = (ROOT / 'gamedesigner.cpp').read_text()

class BreakableGateTests(unittest.TestCase):
    def test_menu_offers_logic_on_destroy(self):
        self.assertIn('eventKey(from)==QStringLiteral("destroy")', VISUAL)
        self.assertIn('m_objects.value(eventOwner(from)).type==QStringLiteral("breakable")', VISUAL)
        self.assertIn('eventLogicSource',VISUAL)

    def test_logic_parser_and_export_agree(self):
        for key in ('hit', 'destroy'):
            self.assertIn('QStringLiteral("@event:'+key+':")', GRAPH)
            self.assertIn('QStringLiteral("@event:'+key+':")', EXPORT)
            self.assertIn('QStringLiteral("@event:'+key+':")', VISUAL)
        self.assertIn('hasNamedPlatformLogic=true;', EXPORT)
        self.assertIn('neededForLogic', EXPORT)
        self.assertIn('action.isEmpty() && !neededForLogic', EXPORT)

    def test_properties_and_remap(self):
        self.assertIn('tr("ON DESTROY pulse: %1")',DESIGN)
        self.assertIn('tr("ON HIT pulse: %1")',DESIGN)
        self.assertIn('const QString type=input.value(QStringLiteral("id"))',DESIGN)
        self.assertIn('m_objects.value(id).type==QStringLiteral("breakable")',VISUAL)

    def test_named_event_pulse_consumed_once(self):
        # Minimal C runtime reproduction of the generated named-event bit AND logic condition.
        # ON DESTROY is a one-frame bit, not a persistent boolean state.
        c='''#include <assert.h>\n#include <stdint.h>\nint main(void){\nuint8_t events=0, spring=1, switch_on=1, spotlight=0;\n#define UPDATE() do { if(events & 2u) { if ((events & 2u) && spring && switch_on) spotlight^=1u; } events=0; } while(0)\nevents|=2u; UPDATE(); assert(spotlight==1);\nUPDATE(); assert(spotlight==1);\nswitch_on=0; events|=2u; UPDATE(); assert(spotlight==1);\nspring=0; switch_on=1; events|=2u; UPDATE(); assert(spotlight==1);\nspring=1; switch_on=1; events|=2u; UPDATE(); assert(spotlight==0);\nreturn 0;}'''
        with tempfile.TemporaryDirectory() as temp:
            src=Path(temp)/'test.c';exe=Path(temp)/'test';src.write_text(c)
            subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True,capture_output=True)
            subprocess.run([str(exe)],check=True,capture_output=True)

if __name__=='__main__': unittest.main()
