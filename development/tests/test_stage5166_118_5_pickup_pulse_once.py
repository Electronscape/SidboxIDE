"""Stage 5.166.118.5: a collectable pulse must not replay on later trigger dispatch."""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
RULE = (ROOT / 'idelibs/codehelpers/game/gameworlditems.rulec').read_text()

class PickupPulseOnce(unittest.TestCase):
    def test_clear_is_after_pickup_logic_but_before_return(self):
        section=RULE.split('uint16_t gameworlditems_check(',1)[1].split('return count;',1)[0]
        self.assertIn('@IDE{CHECK_ACTIONS}',section)
        self.assertIn('if(cg_named_pickup_logic)cg_run_trigger_actions();',section)
        self.assertIn('memset(cg_named_pickup_sources,0,sizeof(cg_named_pickup_sources));',section)
        self.assertLess(section.index('@IDE{CHECK_ACTIONS}'),section.index('if(cg_named_pickup_logic)cg_run_trigger_actions();'))
        self.assertLess(section.index('if(cg_named_pickup_logic)cg_run_trigger_actions();'),section.rindex('memset(cg_named_pickup_sources,0,sizeof(cg_named_pickup_sources));'))
        self.assertIn('@IDE_IF{HAS_NAMED_PICKUP_EVENTS}',section)
    def test_native_one_pulse_one_dispatch(self):
        if not shutil.which('cc'):
            self.skipTest('No native C compiler')
        needle='''@IDE_IF{HAS_NAMED_PICKUP_LOGIC}
    uint8_t cg_named_pickup_logic=0u;'''
        self.assertIn(needle,RULE)
        fragment=RULE.split(needle,1)[1].split('    return count;',1)[0]
        # Use production C statements, not a handwritten equivalent.
        fragment='    uint8_t cg_named_pickup_logic=0u;'+fragment
        fragment=re.sub(r'@IDE_IF\{[^}]+\}\n|@IDE_END\n','',fragment)
        fragment=fragment.replace('@IDE{PICKUP_COUNT}','1')
        code='''#include <stdint.h>
#include <string.h>
#include <assert.h>
static uint8_t cg_named_pickup_sources[1];
static unsigned calls;
static void cg_run_trigger_actions(void) { if(cg_named_pickup_sources[0])++calls; }
static void pickup_check_dispatch(void) {
'''+fragment+''' }
int main(void) {
    cg_named_pickup_sources[0]=1;
    pickup_check_dispatch();
    assert(calls==1);
    cg_run_trigger_actions(); /* Later Trigger evaluation in the same frame. */
    assert(calls==1);
    cg_named_pickup_sources[0]=1; /* A genuine second pickup event. */
    pickup_check_dispatch();
    assert(calls==2);
    cg_run_trigger_actions();
    assert(calls==2);
    pickup_check_dispatch(); /* No event, no action. */
    assert(calls==2);
    return 0;
}
'''
        with tempfile.TemporaryDirectory() as work:
            src=Path(work)/'pulse.c'
            binary=Path(work)/'pulse'
            src.write_text(code)
            subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror',str(src),'-o',str(binary)],check=True,capture_output=True,text=True)
            subprocess.run([str(binary)],check=True,capture_output=True,text=True)
    def test_no_save_schema_change(self):
        self.assertIn('cg_named_pickup_sources', RULE)
        self.assertNotIn('CG_SAVE_BYTES(cg_named_pickup_sources)',RULE)

if __name__=='__main__':
    unittest.main()
