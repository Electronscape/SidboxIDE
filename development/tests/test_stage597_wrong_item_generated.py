#!/usr/bin/env python3
"""Compile the actual generated GameWorldItem USE template with wrong dialogue hooks."""
from pathlib import Path
import subprocess,tempfile
r=Path(__file__).resolve().parents[2]
s=(r/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
a=s.index('uint8_t gameworlditems_interaction_use(const char *item_name)')
b=s.index('@IDE_END',a)
fn=s[a:b]
fn=fn.replace('@IDE{WORLD_OBJECT_COUNT}','2u')
fn=fn.replace('@IDE{INTERACT_PREFLIGHT_ACTIONS}','')
fn=fn.replace('@IDE{INTERACT_DIALOGUE_ACTIONS}','    game_adventure_trigger_sequence(1u);')
fn=fn.replace('@IDE{INTERACT_WRONG_DIALOGUE_ACTIONS}',
    '        if (r->object == 0u) { game_adventure_trigger_sequence(2u); return 0u; }\n')
assert '@IDE{' not in fn
code='''#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
typedef struct {uint8_t active, trigger_fired, trigger_one_shot;} game_world_object_t;
typedef struct {uint16_t object,reach;uint8_t consume;const char *item;} cg_interaction_rule_t;
static const cg_interaction_rule_t cg_interaction_rules[]={{0u,16u,0u,"Key"}};
static uint16_t cg_interaction_target;
static game_world_object_t cg_gwi_platforms[2]={{1u,0u,1u},{1u,0u,0u}};
static uint16_t dialogue_node=65535u;
static uint8_t wrong_sounds,success_sounds;
static void gameworlditems_interaction_sound(uint8_t event)
{if(event==0)++wrong_sounds;else if(event==1)++success_sounds;}
static uint8_t game_adventure_trigger_sequence(uint16_t node)
{dialogue_node=node;return 1u;}
static void cg_run_trigger_actions(void)
{if(cg_gwi_platforms[0].trigger_fired)cg_gwi_platforms[1].active=0u;}
'''+fn+'''
int main(void) {
 assert(gameworlditems_interaction_use("Wrong") == 0u);
 assert(dialogue_node==2u && wrong_sounds==1u && !success_sounds);
 assert(cg_gwi_platforms[0].active && cg_gwi_platforms[1].active);
 assert(gameworlditems_interaction_use("Key") == 1u);
 assert(dialogue_node==1u && success_sounds==1u);
 assert(!cg_gwi_platforms[0].active && !cg_gwi_platforms[1].active);
 puts("Stage 5.97: generated wrong and success branches PASS");
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='s597-world-') as td:
 p=Path(td)
 (p/'test.c').write_text(code)
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(p/'test.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
