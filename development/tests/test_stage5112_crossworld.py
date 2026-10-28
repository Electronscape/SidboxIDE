#!/usr/bin/env python3
"""Stage 5.112: compile the actual queued remote state functions; source contract."""
from pathlib import Path
import re,subprocess,tempfile
root=Path(__file__).resolve().parents[2]
files=lambda name:(root/name).read_text()
impl=files('idelibs/codehelpers/game/gameworlditems.rulec')
world=files('idelibs/codehelpers/game/gameworlds.rulec')
codegen=files('gamedesigner_export.cpp')
snapshot=files('gameworldsnapshot.h')
editor=files('gamedesigner.cpp')
flow=files('gamefloweditor.cpp')
for val in ('cgCrossWorldLink(world,id)','cgDecodeCrossWorldLink','%1: %2 [%3]', 'QDir::Files'):
    assert val in editor or val in files('gamecrossworldlinks.h'),val
for val in ('remoteTarget(r.targetObjectId','remoteTarget(link.objectId', 'gameworlds_object_action(', 'WORLD_OBJECT_INITIAL_ACTIVE'):
    assert val in codegen,val
for val in ('_gameworlditems_remote_action','_gameworlditems_remote_reset','_gameworlditems_apply_remote'):
    assert val in snapshot,val
for val in ('object_remote_action','object_apply_remote','world->object_apply_remote','worlds[i].object_remote_reset'):
    assert val in world,val
assert 'objectKey(foreignWorld,foreignId)' in flow
# Compile the exact function bodies using minimal object state stubs.
def function(name):
    begin=impl.find('void '+name+'(')
    # skip C forward declarations
    while begin >= 0 and impl.find(';',begin,impl.find('{',begin)) >= 0:
        begin=impl.find('void '+name+'(',begin+1)
    assert begin>=0, name
    brace=impl.index('{',begin);depth=1;end=brace+1
    while depth:
        if impl[end]=='{': depth+=1
        if impl[end]=='}': depth-=1
        end+=1
    return impl[begin:end]
set_active=function('gameworlditems_set_active')
remote=function('gameworlditems_remote_action')
# Old unit fixture has no reward variables; strip optional template-only block.
reset=re.sub(r'(?ms)^@IDE_IF\{HAS_REWARDS\}\n.*?^@IDE_END\n','',function('gameworlditems_remote_reset'))
apply=function('gameworlditems_apply_remote')
source='''#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#define GAMEWORLDITEMS_PLATFORM_COUNT 2
struct sprite { int index; };
typedef struct { uint8_t active; struct sprite *sprite; } object;
typedef struct { uint8_t active; } snapshot;
static object cg_gwi_platforms[2];
static snapshot cg_saved_objects[2];
static uint8_t cg_initial_active[2]={0,1};
static uint8_t cg_remote_valid[2];
static uint8_t cg_remote_active[2];
static uint8_t cg_world_snapshot_valid;
static uint16_t cg_active_state_frames[2]={65535,65535};
'''+set_active+'\n'+remote+'\n'+reset+'\n'+apply+'''
int main(void) {
 /* First visit: two remote toggles must cancel one another. */
 gameworlditems_remote_action(0,2); gameworlditems_remote_action(0,2);
 cg_gwi_platforms[0].active=0; cg_gwi_platforms[1].active=1;
 gameworlditems_apply_remote();
 assert(cg_gwi_platforms[0].active==0 && cg_remote_valid[0]==0);
 /* Turning Steve on before first visit works, even from World1. */
 gameworlditems_remote_action(0,1);gameworlditems_remote_action(1,0);
 gameworlditems_apply_remote();
 assert(cg_gwi_platforms[0].active==1 && cg_gwi_platforms[1].active==0);
 /* Once world has visited, toggling uses saved state, not original defaults. */
 cg_world_snapshot_valid=1;cg_saved_objects[0].active=1;
 gameworlditems_remote_action(0,2);
 gameworlditems_remote_action(0,2);
 cg_gwi_platforms[0].active=cg_saved_objects[0].active;
 gameworlditems_apply_remote();
 assert(cg_gwi_platforms[0].active==1);
 gameworlditems_remote_action(0,0);
 cg_gwi_platforms[0].active=cg_saved_objects[0].active;
 gameworlditems_apply_remote();
 assert(cg_gwi_platforms[0].active==0);
 gameworlditems_remote_action(0,1);gameworlditems_remote_reset();
 assert(cg_remote_valid[0]==0 && cg_world_snapshot_valid==0);
 puts("PASS cross-world queued object states / repeated toggles / reset");
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage5112_') as d:
    p=Path(d)/'test.c';p.write_text(source)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O2',str(p),'-o',d+'/a'],check=True)
    subprocess.run([d+'/a'],check=True)
print('Stage5.112 source integration PASS')
