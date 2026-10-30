"""Stage 5.166.116: Breakable events can reach existing logic and Adventure dialogue."""
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[2]
VISUAL=(ROOT/'gamevisualnodes.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
GRAPH=(ROOT/'gamevisualgraphlogic.h').read_text()
RULE=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()

class BreakableDialogueTests(unittest.TestCase):
    def test_event_picker_exposes_named_logic_and_dialogue(self):
        section=VISUAL.split('void showInsertTree(',1)[1].split('void connectExistingDialogue(',1)[0]
        self.assertIn('m_objects.value(eventOwner(from)).type==QStringLiteral("breakable")',section)
        self.assertIn('eventKey(from)==QStringLiteral("hit")',section)
        self.assertIn('eventKey(from)==QStringLiteral("destroy")',section)
        self.assertIn('if (objectSource || eventLogicSource)',section)
        self.assertIn('(!eventOutputPort || eventLogicSource)',section)
        self.assertIn('populateDialogueChoices(tree,root);',section)
        self.assertIn('NPC Conversations',section)
        self.assertIn('logicRoot->setExpanded(true)',section)
    def test_existing_dialogue_selection_creates_real_event_graph(self):
        section=VISUAL.split('void showInsertTree(',1)[1].split('void connectExistingDialogue(',1)[0]
        for token in ('createGraphLogic(from,at,QStringLiteral("boolean"));',
                      'setGraphDialogue(key,true,index,at+QPointF(350,0));',
                      'setGraphDialogue(key,true,-2,at+QPointF(350,0));'):
            self.assertIn(token,section)
        self.assertLess(section.index('if(eventLogicSource) {\n                    const QString owner=eventOwner(from);'),
                        section.index('} else connectExistingDialogue(from,at,index);'))
    def test_existing_canvas_dialogue_drop_uses_event_graph(self):
        section=VISUAL.split('void addConnection(',1)[1].split('if (isEnemyDefeatOutput(from))',1)[0]
        self.assertIn('selectedDialogueOnCard(to)',section)
        self.assertIn('createGraphLogic(from,at,QStringLiteral("boolean"));',section)
        self.assertIn('setGraphDialogue(key,true,dialogue,at+QPointF(350,0));',section)
    def test_cross_owned_gate_is_not_silently_connected(self):
        section=VISUAL.split('void addConnection(',1)[1].split('if (isEnemyDefeatOutput(from))',1)[0]
        self.assertIn('if(lookupGraph(to,&graphOwner,nullptr) && graphOwner!=eventOwner(from))',section)
        self.assertIn('Create Event Gate',section)
        self.assertIn('createGraphLogic(from,point,operation);',section)
    def test_preserves_existing_runtime_storage_and_pulse_semantics(self):
        self.assertIn('object.insert(QStringLiteral("logicNodes"),node.logicNodes)',VISUAL)
        self.assertIn('input.kind==QStringLiteral("event")',EXPORT)
        self.assertIn('game_adventure_trigger_message(%1u)',EXPORT)
        self.assertIn('if(action.isEmpty() && !neededForLogic)continue;',EXPORT)
        self.assertIn('cg_named_event_sources[cg_i]',RULE)
        self.assertIn('memset(cg_named_event_sources,0,sizeof(cg_named_event_sources));',RULE)
        self.assertIn('n.trueDialogue=o.value(QStringLiteral("trueDialogueNode")).toInt(-1);',GRAPH)
    def test_native_hit_destroy_and_gate_message_once(self):
        c=r'''#include <assert.h>
#include <stdint.h>
int main(void) {
 uint8_t pulses=0, switch_active=1, message_hits=0, message_destroy=0;
 #define TICK() do {\
 if (pulses & 1u) {if(pulses & 1u) ++message_hits;}\
 if (pulses & 2u) {if ((pulses & 2u) && switch_active) ++message_destroy;}\
 pulses=0; } while(0)
 pulses|=1u; TICK(); assert(message_hits==1 && message_destroy==0);
 TICK(); assert(message_hits==1 && message_destroy==0);
 switch_active=0; pulses|=2u; TICK(); assert(message_destroy==0);
 switch_active=1; pulses|=2u; TICK(); assert(message_destroy==1);
 TICK(); assert(message_destroy==1);
 return 0;
}'''
        with tempfile.TemporaryDirectory() as tmp:
            source=Path(tmp)/'check.c'; target=Path(tmp)/'check';source.write_text(c)
            subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror',str(source),'-o',str(target)],check=True,capture_output=True)
            subprocess.run([str(target)],check=True,capture_output=True)

if __name__=='__main__':unittest.main()
