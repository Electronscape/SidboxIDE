#!/usr/bin/env python3
"""Build actual template's Stage 5.94 use path, with generated sample actions."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
s=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
a=s.index('static uint8_t cg_complete_item_interaction(uint16_t rule_index, uint8_t dropped)')
b=s.index('uint8_t gameworlditems_drop_contact(',a)
func=s[a:b].replace('@IDE{WORLD_OBJECT_COUNT}', '2u')
assert 'consumed_here' in func
func=func.replace('@IDE{INTERACT_WRONG_DIALOGUE_ACTIONS}', '')
func=func.replace('@IDE{INTERACT_PREFLIGHT_ACTIONS}',
    '''    if (r->object==0u) {
        if (!game_adventure_can_reward_name("Gem",1u,r->consume ? r->item : 0)) return 3u;
        if (!gameadventure_apply_item_stat("health",10)) return 0u;
        if (!game_adventure_take_name(r->item,1u)) return 0u;
        consumed_here=1u;
        if (!game_adventure_reward_name("Gem",1u)) return 3u;
    }''')
func=func.replace('@IDE{INTERACT_DIALOGUE_ACTIONS}',
    '    if(r->object==0u)game_adventure_trigger_dialogue(0u);')
code='''#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
typedef struct { uint8_t active, trigger_fired, trigger_one_shot; } game_world_object_t;
typedef struct { uint16_t object,reach; uint8_t consume,drop; const char *item; } cg_interaction_rule_t;
static const cg_interaction_rule_t cg_interaction_rules[]={{0u,32u,1u,0u,"Key"},{65535u,0u,0u,0u,0}};
static uint16_t cg_interaction_target;
static game_world_object_t cg_gwi_platforms[2]={{1,0,1},{1,0,0}};
static int reward_full,awarded,spent,dialogue,stat,sounds;
static uint8_t game_adventure_can_reward_name(const char *name,uint16_t count,const char *item)
{ assert(!strcmp(name,"Gem")&&count==1&&item&&!strcmp(item,"Key"));return !reward_full; }
static uint8_t gameadventure_apply_item_stat(const char *name,int32_t amount)
{assert(!strcmp(name,"health")&&amount==10);++stat;return 1;}
static uint8_t game_adventure_take_name(const char *name,uint16_t n)
{assert(!strcmp(name,"Key")&&n==1);++spent;return 1;}
static uint8_t game_adventure_reward_name(const char *name,uint16_t n)
{assert(!strcmp(name,"Gem")&&n==1);++awarded;return 1;}
static uint8_t game_adventure_trigger_dialogue(uint16_t node)
{assert(node==0);++dialogue;return 1;}
static void cg_run_trigger_actions(void)
{if(cg_gwi_platforms[0].trigger_fired)cg_gwi_platforms[1].active=0;}
static void gameworlditems_interaction_sound(uint8_t event)
{assert(event<=2);++sounds;}
'''+func+'''
int main(void) {
 assert(gameworlditems_interaction_use("Feather")==0);
 assert(cg_gwi_platforms[1].active==1 && !spent && !awarded);
 reward_full=1;
 assert(gameworlditems_interaction_use("Key")==3u);
 assert(cg_gwi_platforms[0].active && cg_gwi_platforms[1].active && !spent && !awarded && !stat);
 reward_full=0;
 assert(gameworlditems_interaction_use("Key")==1u);
 assert(!cg_gwi_platforms[0].active && !cg_gwi_platforms[1].active);
 assert(spent==1 && awarded==1 && stat==1 && dialogue==1 && sounds==2);
 puts("Stage 5.94: real generated interaction use path PASS");
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage594world-') as td:
    out=Path(td); (out/'world.c').write_text(code)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(out/'world.c'),'-o',str(out/'world')],check=True)
    subprocess.run([str(out/'world')],check=True)
