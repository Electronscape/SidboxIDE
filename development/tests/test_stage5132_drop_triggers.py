"""Native test of Stage 5.132 template's actual drop-trigger C functions.
Usage: python3 tests_stage5132/test_drop_triggers.py
"""
from pathlib import Path
import subprocess, tempfile
ROOT=Path(__file__).resolve().parent.parent.parent
rule=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
assert 'static uint8_t cg_complete_item_interaction' in rule
code=rule.split('/* USE and falling-item contact deliberately share the SAME success path.',1)[1].split('@IDE_END',1)[0]
code='/* USE and falling-item contact deliberately share the SAME success path.\n'+code
code=code.replace('@IDE{WORLD_OBJECT_COUNT}','2')
code=code.replace('@IDE{INTERACT_WRONG_DIALOGUE_ACTIONS}','')
code=code.replace('@IDE{INTERACT_SOUND_ACTIONS}','')
code=code.replace('@IDE{INTERACT_PREFLIGHT_ACTIONS}', '''
    if(r->object==0u) {
        if (!game_adventure_can_reward_name("gem",1u,!dropped && r->consume ? r->item : 0)) return 3u;
        if (!dropped && !game_adventure_take_name(r->item,1u)) return 0u;
        if (!dropped) consumed_here=1u;
        if (!game_adventure_reward_name("gem",1u)) return 3u;
    }
''')
code=code.replace('@IDE{INTERACT_DIALOGUE_ACTIONS}', '''
    if (r->object==0u) game_adventure_trigger_message(5u);
    if (r->object==1u) game_adventure_trigger_message(6u);
''')
assert '@IDE' not in code
harness='''#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#define CHECK(c) do { if(!(c)){fprintf(stderr,"FAIL line %d: %s\\n",__LINE__,#c);return 1;} } while(0)
typedef struct {int32_t x,y;uint16_t width,height;uint8_t active,trigger_one_shot,trigger_fired;} game_world_object_t;
typedef struct {uint16_t object,reach;uint8_t consume,drop;const char *item;} cg_interaction_rule_t;
static game_world_object_t cg_gwi_platforms[2];
static const cg_interaction_rule_t cg_interaction_rules[]={
 {0u,32u,1u,1u,"stone"},{1u,32u,0u,1u,"coin"},{UINT16_MAX,0u,0u,0u,0}
};
static uint16_t cg_interaction_target=UINT16_MAX;
static unsigned action_count,dialogue_count,sound_count,take_count,reward_count;
static uint8_t rewards_allowed=1;
static void cg_run_trigger_actions(void){++action_count;}
static uint8_t game_adventure_can_reward_name(const char*a,uint16_t n,const char*used){(void)a;(void)n;(void)used;return rewards_allowed;}
static uint8_t game_adventure_take_name(const char*a,uint16_t n){(void)a;(void)n;++take_count;return 1;}
static uint8_t game_adventure_reward_name(const char*a,uint16_t n){(void)a;(void)n;++reward_count;return 1;}
static void game_adventure_trigger_message(uint16_t n){(void)n;++dialogue_count;}
static void gameworlditems_interaction_sound(uint8_t code){(void)code;++sound_count;}
'''
main='''
int main(void){
  cg_gwi_platforms[0]=(game_world_object_t){.x=50,.y=20,.width=24,.height=40,.active=1,.trigger_one_shot=1};
  cg_gwi_platforms[1]=(game_world_object_t){.x=120,.y=20,.width=30,.height=40,.active=1,.trigger_one_shot=0};
  /* No contact or wrong item: no reward/actions/dialogue. */
  CHECK(gameworlditems_drop_contact("stone",10,30)==0);
  CHECK(gameworlditems_drop_contact("coin",51,30)==0);
  CHECK(action_count==0 && dialogue_count==0 && take_count==0);
  /* Dropped matching item: consume physical sprite, NOT a second bag item. */
  CHECK(gameworlditems_drop_contact("stone",55,10)==2);
  CHECK(action_count==1 && dialogue_count==1 && reward_count==1 && take_count==0);
  CHECK(!cg_gwi_platforms[0].active); /* one-shot */
  CHECK(gameworlditems_drop_contact("stone",55,10)==0);
  /* Repeatable and non-consuming accepts matching drop but leaves it on ground. */
  CHECK(gameworlditems_drop_contact("coin",140,30)==1);
  CHECK(cg_gwi_platforms[1].active && action_count==2 && dialogue_count==2);
  /* Reward capacity failure must not consume a drop or activate a switch. */
  cg_gwi_platforms[0].active=1; rewards_allowed=0;
  CHECK(gameworlditems_drop_contact("stone",55,30)==0);
  CHECK(cg_gwi_platforms[0].active && take_count==0 && reward_count==1);
  /* Existing inventory USE still consumes one held item, and returns correct status. */
  rewards_allowed=1;cg_interaction_target=0;
  CHECK(gameworlditems_interaction_use("stone")==1);
  CHECK(take_count==1 && action_count==3 && dialogue_count==3);
  CHECK(gameworlditems_drop_contact("stone",55,30)==0);
  return 0;
}
'''
with tempfile.TemporaryDirectory() as tmp:
 p=Path(tmp)/'trigger.c';p.write_text(harness+code+main)
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(p),'-o',str(Path(tmp)/'trigger')],check=True)
 subprocess.run([str(Path(tmp)/'trigger')],check=True)
print('PASS: dropped item contact, wrong item, consume/no double consume, dialogue, rewards, one-shot, existing USE, preflight failure')
# Ensure generator produces the required 5-field row and preserves the saved key.
export=(ROOT/'gamedesigner_export.cpp').read_text()
assert '{%1u, %2u, %3u, %4u, %5}' in export
assert 'r.triggerDrop ? 1 : 0' in export
assert '!dropped && r->consume ? r->item : 0' in export
proj=(ROOT/'gamedesigner_project.cpp').read_text()
assert 'object.insert(QStringLiteral("triggerDrop"), r.triggerDrop)' in proj
assert 'r.triggerDrop = object.value(QStringLiteral("triggerDrop")).toBool(false)' in proj
adventure=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
assert 'ga_drop_touch_trigger(d)' in adventure and 'for (int32_t y=from+1; y<=final_y' in adventure
assert 'ga_drop_contact=0;' in adventure
assert 'd->armed |= 2u;' in adventure
assert 'ga_drops[i].armed = 0u' in adventure
assert 'game_adventure_set_drop_contact(gameworlditems_drop_contact);' in (ROOT/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
print('PASS: generator wiring, world setup and contact sweep contracts')
# Compile the REAL Adventure drop-step functions, injecting only mock world callbacks.
adventure=(ROOT/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
segment=adventure.split('void game_adventure_set_drop_contact(game_adventure_drop_contact_t contact)',1)[1].split('static uint8_t ga_confirm_yes;',1)[0]
segment='void game_adventure_set_drop_contact(game_adventure_drop_contact_t contact)'+segment
assert 'static void ga_step_drops(uint16_t frames)' in segment
physics_harness='''#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#define CHECK(c) do { if(!(c)){fprintf(stderr,"FAIL line %d: %s\\n",__LINE__,#c);return 1;} } while(0)
#define GAME_ADVENTURE_MAX_DROPS 16
struct ga_item {const char *name;};
static const struct ga_item items[1]={{"stone"}};
static const struct ga_item *ga_items=items;
static uint16_t ga_item_count=1;
typedef struct {int32_t x,y;uint16_t item_id;uint8_t active,armed;} game_adventure_drop_t;
static game_adventure_drop_t ga_drops[GAME_ADVENTURE_MAX_DROPS];
static uint16_t ga_drop_speed100[GAME_ADVENTURE_MAX_DROPS];
static uint16_t ga_drop_fraction100[GAME_ADVENTURE_MAX_DROPS];
static uint8_t ga_drop_landed[GAME_ADVENTURE_MAX_DROPS];
typedef uint8_t (*game_adventure_drop_contact_t)(const char*,int32_t,int32_t);
typedef int32_t (*game_adventure_drop_floor_t)(int32_t,int32_t,int32_t);
static game_adventure_drop_contact_t ga_drop_contact;
static game_adventure_drop_floor_t ga_drop_floor;
static unsigned events;
static uint8_t consume_drop;
static int32_t last_contact_y;
static uint8_t on_drop(const char *name,int32_t x,int32_t y){
 (void)x;CHECK(name && strcmp(name,"stone")==0);
 if(y+16<=30 || y>=36)return 0;
 ++events;last_contact_y=y;
 return consume_drop?2u:1u;
}
static int32_t no_floor(int32_t x,int32_t a,int32_t b){(void)x;(void)a;(void)b;return INT32_MAX;}
static int32_t floor_at70(int32_t x,int32_t a,int32_t b){(void)x;return a<=70 && b>=70 ? 70:INT32_MAX;}
'''
physics_main='''
int main(void){
 ga_drop_floor=no_floor;game_adventure_set_drop_contact(on_drop);
 ga_drops[0]=(game_adventure_drop_t){.x=40,.y=0,.item_id=0,.active=1};
 consume_drop=1;ga_step_drops(30);
 CHECK(events==1 && (ga_drops[0].armed&2u) && !ga_drops[0].active);
 CHECK(last_contact_y==15); /* First contact exactly at leading edge. */
 events=0;consume_drop=0;
 ga_drop_floor=floor_at70;
 memset(ga_drop_speed100,0,sizeof(ga_drop_speed100));
 memset(ga_drop_fraction100,0,sizeof(ga_drop_fraction100));
 ga_drops[0]=(game_adventure_drop_t){.x=40,.y=0,.item_id=0,.active=1};
 ga_step_drops(30);
 CHECK(events==1 && ga_drops[0].active && (ga_drops[0].armed&2u));
 CHECK(ga_drops[0].y==70 && ga_drop_landed[0]); /* Must continue falling after activation. */
 ga_step_drops(15); CHECK(events==1 && ga_drops[0].y==70); /* Never repeats. */
 game_adventure_drop_t saved=ga_drops[0];
 ga_drops[0]=saved;ga_step_drops(5);CHECK(events==1); /* Persisted flag */
 return 0;
}
'''
with tempfile.TemporaryDirectory() as tmp:
 p=Path(tmp)/'physics.c';p.write_text(physics_harness+segment+physics_main)
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(p),'-o',str(Path(tmp)/'physics')],check=True)
 subprocess.run([str(Path(tmp)/'physics')],check=True)
print('PASS: native drop-step mid-air contact, no tunnelling, consume/keep, one activation per drop, persisted flag')
