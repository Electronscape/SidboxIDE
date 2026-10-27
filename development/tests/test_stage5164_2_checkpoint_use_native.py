#!/usr/bin/env python3
"""Compile the actual inventory-USE runtime path with a checkpoint callback.

The exporter-to-runtime handoff is source-contract checked separately because
Qt6 (required to run the exporter) is unavailable on this test host.
"""
from pathlib import Path
import subprocess
import tempfile
root=Path(__file__).resolve().parents[2]
s=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
a=s.index('static uint8_t cg_complete_item_interaction(uint16_t rule_index, uint8_t dropped)')
b=s.index('uint8_t gameworlditems_drop_contact(',a)
functions=s[a:b]
for key,value in {'@IDE{WORLD_OBJECT_COUNT}':'1u',
                  '@IDE{INTERACT_PREFLIGHT_ACTIONS}':'',
                  '@IDE{INTERACT_DIALOGUE_ACTIONS}':'',
                  '@IDE{INTERACT_WRONG_DIALOGUE_ACTIONS}':''}.items():
    functions=functions.replace(key,value)
assert '@IDE' not in functions
code=r'''#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
typedef struct { uint8_t active,trigger_fired,trigger_one_shot; } game_world_object_t;
typedef struct { uint16_t object,reach; uint8_t consume,drop; const char *item; } cg_interaction_rule_t;
static const cg_interaction_rule_t cg_interaction_rules[]={{0u,32u,0u,0u,"Key"},{UINT16_MAX,0,0,0,0}};
static uint16_t cg_interaction_target;
static game_world_object_t cg_gwi_platforms[1]={{1,0,0}};
static uint8_t checkpoint_pending;
static int requests,wrong_sounds,success_sounds;
static uint8_t gameworlds_checkpoint_request(uint8_t slot)
{ assert(slot==4u);checkpoint_pending=(uint8_t)(slot+1u);++requests;return 1u; }
static void cg_run_trigger_actions(void)
{ if(cg_gwi_platforms[0].trigger_fired) gameworlds_checkpoint_request(4u); }
static void gameworlditems_interaction_sound(uint8_t event)
{ assert(event<=2u);if(event==0u)++wrong_sounds;if(event==1u)++success_sounds; }
'''+functions+r'''
int main(void)
{
 assert(gameworlditems_interaction_use("Wrong") == 0u);
 assert(!checkpoint_pending && requests==0 && wrong_sounds==1 && !success_sounds);
 assert(gameworlditems_interaction_use("Key") == 1u);
 assert(checkpoint_pending == 5u && requests==1 && success_sounds==1);
 assert(cg_gwi_platforms[0].active && !cg_gwi_platforms[0].trigger_fired);
 checkpoint_pending=0u;
 cg_interaction_target=0u;
 assert(gameworlditems_interaction_use("Key") == 1u);
 assert(checkpoint_pending == 5u && requests==2);
 puts("PASS checkpoint: wrong item no save; matching USE queues slot 5; repeatable");
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='checkpoint_use_') as d:
    src=Path(d)/'test.c';out=Path(d)/'test'
    src.write_text(code)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(src),'-o',str(out)],check=True)
    subprocess.run([str(out)],check=True)
