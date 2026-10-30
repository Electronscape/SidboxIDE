#!/usr/bin/env python3
"""Stage 5.166.110 event output source integration and native C behaviour tests.

Qt compilation and STM32 hardware dispatch remain acceptance tests.
"""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[2]
NODE=(ROOT/'gamevisualnodes.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
EDITOR=(ROOT/'gamedesigner.cpp').read_text()
PROJECT=(ROOT/'gamedesigner_project.cpp').read_text()
SNAP=(ROOT/'gameworldsnapshot.h').read_text()
RULE=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
WORLDS=(ROOT/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
OBJECTS=(ROOT/'idelibs/codehelpers/game/worldobjects.rulec').read_text()
SPLASH=(ROOT/'splashscreenwidget.cpp').read_text()

class EventOutputs(unittest.TestCase):
 def test_version(self):
  self.assertIn('Build: 5.166.111.1.291026',SPLASH)
 def test_all_requested_event_types(self):
  for type,events in [('breakable',['hit','destroy']),('collectable',['pickup']),('hazard',['player_hit']),('goto_world',['enter']),('save_checkpoint',['save']),('lift',['arrival']),('enemy',['hit'])]:
   self.assertIn('type==QStringLiteral("%s")'%type,NODE)
   for kind in events:self.assertIn('QStringLiteral("%s")'%kind,NODE)
  for label in ['ON HIT','ON DESTROY','ON PICKUP','ON PLAYER HIT','ON ENTER','ON SAVE','ON ARRIVAL']:
   self.assertIn(label,NODE)
 def test_visual_nodes_drag_menu_save_reload(self):
  for needle in ['eventLinks','event-output','event-link','appendEventConnection','isEventOutput(from)','eventOwner(from)','eventKey(from)','data.value(QStringLiteral("eventActions"))','object.insert(QStringLiteral("eventActions"),events)']:
   self.assertIn(needle,NODE)
  self.assertIn('eventActions',PROJECT)
  self.assertIn('reloadNamedEventLinks()',EDITOR)
  self.assertIn('propertyEventKinds(newType)',EDITOR)
 def test_generator_emits_existing_target_actions(self):
  for needle in ['EVENT_SAVE_ACTIONS','EVENT_ENTER_ACTIONS','WORLD_EVENT_ACTIONS','PICKUP_TARGET_ACTION','SAVE_PICKUP_ACTIVE','for(const QJsonValue &value:r.eventActions.value','if(!targetAction(target,&action))return false','cg_named_event_sources[%1u]|=','cg_named_pickup_sources[%1u]=1u']:
   self.assertIn(needle,EXPORT)
  for needle in ['break_hit_triggered','break_triggered','hazard_hit_triggered','arrival_triggered','trigger_fired']:
   self.assertIn(needle,EXPORT)
  self.assertIn('cg_gwi_platforms[@IDE{INDEX}].break_triggered',RULE) # enemy defeat preserved
 def test_multiworld_checkpoint_registry_and_success_path(self):
  self.assertIn('"gameworlditems_checkpoint_saved",',SNAP)
  self.assertIn('_gameworlditems_checkpoint_saved',SNAP)
  self.assertIn('void (*checkpoint_saved)(void)',WORLDS)
  self.assertIn('save_checkpoint_status==1u && active_world && active_world->checkpoint_saved',WORLDS)
  self.assertIn('gameworlditems_checkpoint_saved(void)',RULE)
  self.assertIn('cg_checkpoint_event_source=UINT16_MAX',RULE)
  self.assertIn('game_adventure_choose_save_slot(%2u)',EXPORT)
  self.assertIn('EVENT_SAVE_ACTIONS',RULE)
 def test_logic_reacts_only_to_relevant_event_owners(self):
  self.assertIn('if(graphInputs.contains(value.toObject().value(QStringLiteral("objectId"))',EXPORT)
  self.assertIn('activationEvents.append(QStringLiteral("(cg_named_event_sources[%1u] & %2u)")',EXPORT)
  self.assertIn('activationEvents.append(QStringLiteral("cg_named_pickup_sources[%1u]")',EXPORT)
  self.assertIn('if(cg_named_logic_fired)cg_run_trigger_actions();',RULE)
  self.assertIn('if(cg_named_pickup_logic)cg_run_trigger_actions();',RULE)
  self.assertIn('memset(cg_named_event_sources,0,sizeof(cg_named_event_sources));',RULE)
 def test_cross_world_copy_event_references_remapped_once(self):
  # Both dependency import and root import must remap the new event target IDs.
  self.assertEqual(EDITOR.count('QJsonObject importedEvents;'),2)
  self.assertEqual(EDITOR.count('r.eventActions=importedEvents;'),2)
  importStart=EDITOR.index('const auto remapFields =')
  importEnd=EDITOR.index('const auto remapRootFields =',importStart)
  rootEnd=EDITOR.index('attachAnimation(copy,',importEnd)
  self.assertEqual(EDITOR[importStart:importEnd].count('QJsonObject importedEvents;'),1)
  self.assertEqual(EDITOR[importEnd:rootEnd].count('QJsonObject importedEvents;'),1)
  self.assertIn('r.breakDropCollectableId = importById(r.breakDropCollectableId);',EDITOR[importStart:importEnd])
  self.assertIn('r.breakDropCollectableId = importById(r.breakDropCollectableId);',EDITOR[importEnd:rootEnd])
 def test_spline_waypoint_arrivals(self):
  self.assertIn('object->arrival_triggered = 0',OBJECTS)
  self.assertIn('object->arrival_triggered=(uint8_t)(new_segment>old_segment',OBJECTS)
  self.assertIn('path->next_pause_index!=old_knot',OBJECTS)
 def test_native_event_flags_and_logic_once(self):
  source=r'''
#include <stdint.h>
#include <assert.h>
#include <string.h>
typedef struct {uint8_t active,break_hit_triggered,break_triggered,hazard_hit_triggered,arrival_triggered;} object_t;
static object_t o[3];
static uint8_t event_sources[3];
static int actions,dialogues;
static void dispatch(void) {
 if(o[0].break_hit_triggered){event_sources[0]|=1;o[1].active=0;++actions;}
 if(o[0].break_triggered){event_sources[0]|=2;o[2].active=1;++actions;}
 if(o[2].arrival_triggered){event_sources[2]|=32;o[1].active=1;++actions;}
 if((event_sources[0]&1) && !o[1].active)++dialogues;
 memset(event_sources,0,sizeof(event_sources));
}
int main(void){
 o[0].break_hit_triggered=1;o[1].active=1;dispatch();
 assert(actions==1 && dialogues==1 && !o[1].active);
 o[0].break_hit_triggered=0;dispatch();assert(actions==1 && dialogues==1);
 o[0].break_triggered=1;dispatch();assert(actions==2 && o[2].active);
 o[0].break_triggered=0;o[2].arrival_triggered=1;dispatch();
 assert(actions==3 && o[1].active && dialogues==1);
 return 0;
}
'''
  with tempfile.TemporaryDirectory() as t:
   inp=Path(t)/'event.c';out=Path(t)/'event';inp.write_text(source)
   subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror',str(inp),'-o',str(out)],check=True,capture_output=True,text=True)
   subprocess.run([str(out)],check=True,capture_output=True,text=True)

if __name__=='__main__':unittest.main()
