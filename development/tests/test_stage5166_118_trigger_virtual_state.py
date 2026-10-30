"""Stage 118: Trigger virtual latch source contracts and native latch semantics."""
import subprocess, tempfile, unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
UI=(ROOT/'gamevisualnodes.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
PROPS=(ROOT/'gamedesigner.cpp').read_text()
RUNTIME=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()

class VirtualTriggerState(unittest.TestCase):
    def test_two_outputs_read_same_persistent_state_with_inversion(self):
        self.assertIn('QStringLiteral("@triggerstate:on:")',UI)
        self.assertIn('QStringLiteral("@triggerstate:off:")',UI)
        self.assertIn('{QStringLiteral("invert"),triggerStateOff(source)}',UI)
        self.assertIn('entry.value(QStringLiteral("invert")).toBool(false)',UI)
        self.assertIn('locals.insert(triggerStateInputId(id));',UI)
        self.assertIn('void addGraphInput(const QString &source,const QString &key)',UI)
    def test_runtime_uses_real_latch_not_trigger_active_flag(self):
        self.assertIn('typedef struct { uint8_t active; } cg_trigger_virtual_t;',RUNTIME)
        self.assertIn('cg_trigger_state[r->object].active ^= 1u;',RUNTIME)
        self.assertIn('cg_trigger_state[i].active ^= 1u;',RUNTIME)
        self.assertIn('QStringLiteral("cg_trigger_state[%1]")',EXPORT)
        self.assertIn('stateId.startsWith(QStringLiteral("@triggerstate:"))',EXPORT)
        self.assertIn('activationEvents.append(QStringLiteral("cg_gwi_platforms[%1].trigger_fired")',EXPORT)
    def test_save_new_game_and_properties(self):
        for fragment in ['cg_saved_trigger_state,cg_trigger_state','CG_SAVE_BYTES(cg_saved_trigger_state)',
                         'CG_LOAD_BYTES(cg_saved_trigger_state)','cg_trigger_state,cg_saved_trigger_state',
                         'memset(cg_trigger_state,0,sizeof(cg_trigger_state))']:
            self.assertIn(fragment,RUNTIME)
        self.assertIn('Qt::UserRole+2,inverted',PROPS)
        self.assertIn('Trigger %1: STATE ON',PROPS)
        self.assertIn('Trigger %1: STATE OFF',PROPS)
        self.assertIn('"Build: 5.166.118.3.301026"',(ROOT/'splashscreenwidget.cpp').read_text())
    def test_native_latched_on_off_and_save_restore(self):
        code=r'''
#include <stdint.h>
#include <assert.h>
#include <string.h>
#define N 4
struct V { uint8_t active; } state[N], saved[N];
static void activate(unsigned i, int fired) { if(fired)state[i].active ^= 1u; }
static void snapshot(void) { memcpy(saved,state,sizeof(state)); }
static void restore(void) { memcpy(state,saved,sizeof(state)); }
static int cond(unsigned trigger, int invert, int pickup) {
    int on=state[trigger].active != 0;
    return pickup && (invert?!on:on);
}
int main(void) {
  assert(cond(0,1,1)); assert(!cond(0,0,1));
  activate(0,1); assert(cond(0,0,1)); assert(!cond(0,1,1));
  activate(0,0); assert(cond(0,0,1));
  assert(!cond(0,0,0));
  activate(1,1); assert(state[0].active && state[1].active);
  snapshot(); activate(0,1); assert(cond(0,1,1));
  restore(); assert(cond(0,0,1));
  activate(0,1); assert(cond(0,1,1));
  return 0;
}
'''
        with tempfile.TemporaryDirectory() as tmp:
            source=Path(tmp)/'verify.c'; binary=Path(tmp)/'verify'; source.write_text(code)
            subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror',str(source),'-o',str(binary)],check=True)
            subprocess.run([str(binary)],check=True)
if __name__=='__main__':unittest.main()
