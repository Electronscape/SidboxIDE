"""Stage 5.166.119: compile production queue cores and verify ordered semantics.

No Qt dependency or handwritten replacement queue implementations: these tests
extract the actual C from the shipped templates, compile and run it.
"""
from pathlib import Path
import re,subprocess,tempfile,unittest,shutil
from test_stage5166_110_template_render import render
ROOT=Path(__file__).resolve().parents[2]
WORLD=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
ADV=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()

def compile_run(source):
    if not shutil.which('cc'):raise unittest.SkipTest('C compiler missing')
    with tempfile.TemporaryDirectory() as directory:
        path=Path(directory)/'test.c'; path.write_text(source)
        binary=Path(directory)/'test'
        subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-Wno-unused-function','-Wno-unused-variable',str(path),'-o',str(binary)],check=True,capture_output=True,text=True)
        subprocess.run([str(binary)],check=True,capture_output=True,text=True)

class QueueCore(unittest.TestCase):
 def test_action_fifo_native(self):
    core=WORLD.split('#define CG_ACTION_QUEUE_CAPACITY',1)[1].split('@IDE_IF{HAS_NAMED_EVENTS}',1)[0]
    core='#define CG_ACTION_QUEUE_CAPACITY'+core
    core=core.replace('@IDE{ACTION_QUEUE_CASES}',
      'case 1u: result=result*10+1; break;\ncase 2u: result=result*10+2; break;\n')
    # The action code's generated commands can reference a live result.
    code='''#include <stdint.h>
#include <assert.h>
#include <limits.h>
static int result=0;
'''+core+'''
int main(void) {
 assert(cg_action_enqueue(1u));assert(cg_action_enqueue(2u));
 assert(cg_action_enqueue(1u));cg_action_drain();assert(result==121);
 assert(!cg_action_size);
 for(unsigned i=0;i<CG_ACTION_QUEUE_CAPACITY;i++)assert(cg_action_enqueue(2u));
 assert(!cg_action_enqueue(1u));assert(gameworlditems_action_overflow_count()==1u);
 cg_action_drain();assert(!cg_action_size);
 return 0;
}'''
    compile_run(code)
 def test_event_source_fifo_native(self):
    queue=WORLD.split('#define CG_ACTION_QUEUE_CAPACITY',1)[1].split('@IDE_IF{HAS_NAMED_EVENTS}',1)[0]
    queue='#define CG_ACTION_QUEUE_CAPACITY'+queue
    queue=queue.replace('@IDE{ACTION_QUEUE_CASES}','')
    core='@IDE_IF{HAS_LOGIC_DISPATCH}\n'+WORLD.split('@IDE_IF{HAS_LOGIC_DISPATCH}\n',1)[1].split('@IDE_END\n@IDE_IF{HAS_PICKUPS}\n',1)[0]+'@IDE_END\n'
    flags=dict(HAS_LOGIC_DISPATCH=True,HAS_WORLDS=True,HAS_TRIGGERS=True,HAS_ENEMY_STATE_LOGIC=True,
        HAS_NAMED_EVENTS=True,HAS_NAMED_PICKUP_EVENTS=True)
    core=render(core,flags)
    for token in ['GRAPH_SNAPSHOTS','GRAPH_EVALUATIONS','GRAPH_DISPATCH','TRIGGER_ACTIONS','EVENT_ENTER_ACTIONS']:
        core=core.replace('@IDE{'+token+'}','')
    core=core.replace('    cg_action_drain();\n}', '''    if(cg_gwi_platforms[0].trigger_fired)events[used++]=1;
    if(cg_current_defeat_owner==1u)events[used++]=2;
    if(cg_named_event_sources[0]&1u)events[used++]=3;
    if(cg_named_event_sources[0]&2u)events[used++]=4;
    if(cg_named_pickup_sources[0])events[used++]=5;
    cg_action_drain();
}''',1)
    code='''#include <stdint.h>
#include <assert.h>
#include <limits.h>
#define GAME_OBJECT_ENEMY 7
static uint8_t events[32],used;
typedef struct {uint8_t trigger_fired,break_triggered,type;} Obj;
static Obj cg_gwi_platforms[2];
static uint8_t cg_named_event_sources[2],cg_named_pickup_sources[1];
static uint8_t cg_enemy_logic_event_handled;
'''+queue+core.replace('@IDE{WORLD_OBJECT_COUNT}','2').replace('@IDE{PICKUP_COUNT}','1')+'''
int main(void) {
 cg_gwi_platforms[0].trigger_fired=1;
 cg_gwi_platforms[1].type=GAME_OBJECT_ENEMY;
 cg_gwi_platforms[1].break_triggered=1;
 cg_named_event_sources[0]=3u;cg_named_pickup_sources[0]=1u;
 cg_run_trigger_actions();
 assert(used==5);
 for(unsigned i=0;i<5;i++)assert(events[i]==i+1u);
 cg_run_trigger_actions();assert(used==5);
 assert(!cg_event_size);
 assert(!cg_named_event_sources[0]);assert(!cg_named_pickup_sources[0]);
 return 0;
}'''
    compile_run(code)
 def test_pickup_only_world_native(self):
    queue=WORLD.split('#define CG_ACTION_QUEUE_CAPACITY',1)[1].split('@IDE_IF{HAS_NAMED_EVENTS}',1)[0]
    queue='#define CG_ACTION_QUEUE_CAPACITY'+queue
    queue=queue.replace('@IDE{ACTION_QUEUE_CASES}','')
    core='@IDE_IF{HAS_LOGIC_DISPATCH}\n'+WORLD.split('@IDE_IF{HAS_LOGIC_DISPATCH}\n',1)[1].split('@IDE_END\n@IDE_IF{HAS_PICKUPS}\n',1)[0]+'@IDE_END\n'
    flags=dict(HAS_LOGIC_DISPATCH=True,HAS_WORLDS=False,HAS_TRIGGERS=False,
        HAS_ENEMY_STATE_LOGIC=False,HAS_NAMED_EVENTS=False,HAS_NAMED_PICKUP_EVENTS=True)
    core=render(core,flags)
    for token in ['GRAPH_SNAPSHOTS','GRAPH_EVALUATIONS','GRAPH_DISPATCH','TRIGGER_ACTIONS','EVENT_ENTER_ACTIONS']:
        core=core.replace('@IDE{'+token+'}','')
    core=core.replace('    cg_action_drain();\n}', '    if(cg_named_pickup_sources[0])++pickup_calls;\n    cg_action_drain();\n}',1)
    prologue='''#include <stdint.h>
#include <assert.h>
#include <limits.h>
static unsigned pickup_calls;
static uint8_t cg_named_pickup_sources[1];
'''
    epilogue='''
int main(void) {
 cg_named_pickup_sources[0]=1u;
 cg_run_trigger_actions(); assert(pickup_calls==1u);
 cg_run_trigger_actions(); assert(pickup_calls==1u);
 return 0;
}'''
    compile_run(prologue+queue+core.replace('@IDE{PICKUP_COUNT}','1')+epilogue)
 def test_dialogue_sequential_native(self):
    core=ADV.split('#define GA_DIALOGUE_QUEUE_CAPACITY',1)[1].split('static void ga_dialogue_start_pending(void);',1)[0]
    core='#define GA_DIALOGUE_QUEUE_CAPACITY'+core+'static void ga_dialogue_start_pending(void);\n'
    rest=ADV.split('static uint8_t ga_dialogue_queue_push(',1)[1].split('uint8_t game_adventure_open(void)',1)[0]
    # queue declaration extends to other runtime functions; isolate just push and counter
    rest='static uint8_t ga_dialogue_queue_push('+rest.split('static uint8_t ga_dialogue_queue_push(',1)[0]
    rest=rest.split('uint32_t game_adventure_dialogue_overflow_count(void) {return ga_dialogue_overflow;}')[0]+'uint32_t game_adventure_dialogue_overflow_count(void) {return ga_dialogue_overflow;}\n'
    main=ADV.split('static void ga_dialogue_begin(uint16_t node,uint8_t mode)\n',1)[1].split('/* Both selected-answer and answerless-dialogue-close effects',1)[0]
    main='static void ga_dialogue_begin(uint16_t node,uint8_t mode)\n'+main
    code='''#include <stdint.h>
#include <limits.h>
#include <assert.h>
static uint8_t ga_state,ga_quest_open,ga_save_menu_open,ga_defeat_open,ga_map_open;
static uint16_t ga_node,ga_node_count=32u,ga_active_npc;
static const uint8_t *ga_nodes=(const uint8_t *)1;
static uint8_t ga_trigger_message_mode,ga_choice;
static void ga_next_node(int16_t node) {ga_node=(uint16_t)node;ga_state=1u;}
static uint8_t ga_choice_visible(uint16_t node,uint8_t choice){(void)node;return choice==0u;}
static void ga_refresh_thought_for_choice(void) {}
static void ga_bracket_restart(void) {}
'''+core+rest+main+'''
static uint8_t game_adventure_open(void) {ga_dialogue_start_pending();return ga_state!=0u;}
int main(void) {
 assert(game_adventure_trigger_message(3u));assert(ga_node==3u&&ga_state==1u);
 assert(game_adventure_trigger_dialogue(4u));assert(ga_dialogue_size==1u&&ga_node==3u);
 assert(game_adventure_trigger_sequence(5u));assert(ga_dialogue_size==2u);
 ga_state=0u;assert(game_adventure_open());assert(ga_node==4u&&ga_trigger_message_mode==0u);
 ga_state=0u;assert(game_adventure_open());assert(ga_node==5u&&ga_trigger_message_mode==2u);
 ga_state=0u;assert(!game_adventure_open());
 for(unsigned i=0;i<17;i++)assert(game_adventure_trigger_message(2u));
 assert(!game_adventure_trigger_message(6u));assert(game_adventure_dialogue_overflow_count()==1u);
 return 0;
}'''
    compile_run(code)
 def test_integration_and_save_guard(self):
    self.assertIn('queueGeneratedDialogues',EXPORT)
    self.assertIn('queueTargetAction(target,&graphDispatchBody)',EXPORT)
    self.assertIn('HAS_LOGIC_DISPATCH',EXPORT)
    self.assertIn('cg_current_defeat_owner',EXPORT)
    for forbidden in ('CG_SAVE_BYTES(cg_event_queue)','CG_SAVE_BYTES(cg_action_queue)','CG_LOAD_BYTES(cg_event_queue)','CG_LOAD_BYTES(cg_action_queue)'):
        self.assertNotIn(forbidden,WORLD)
    self.assertIn('ga_dialogue_head=ga_dialogue_tail=ga_dialogue_size=0u;',ADV)
    self.assertRegex((ROOT/'splashscreenwidget.cpp').read_text(),r'Build: 5\.166\.119(?:\.\d+)?\.301026')

if __name__=='__main__':unittest.main()
