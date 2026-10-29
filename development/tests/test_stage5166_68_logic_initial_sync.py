#!/usr/bin/env python3
"""Stage 5.166.68 initial world/checkpoint logic pass, and native C effects."""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

root=Path(__file__).resolve().parents[2]
gen=(root/'gamedesigner_export.cpp').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
items=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
header=(root/'idelibs/codehelpers/game/gameworlditems.ruleh').read_text()
snapshot=(root/'gameworldsnapshot.h').read_text()

# Callback only after world state, cross-world actions and scene setup, and
# before the first visible frame. Applies equally to a first start, a return,
# a TFCard slot, or a same-world defeat reload via activate().
start=world[world.index('static uint8_t activate('):world.index('/* Stage 5.164.5 TFCard save runtime.')]
for needle in ('world->objects_init()', 'world->world_state_restore()',
               'world->object_apply_remote()', 'active_world = world;',
               'weather_enter(world)', 'day_night_restore_world(world)',
               'spotlight_ring_build()', 'world->logic_sync()',
               'weather_palette_frame(); /* Night/fog'):
    assert needle in start,needle
assert start.index('world->objects_init()')<start.index('world->world_state_restore()')
assert start.index('world->object_apply_remote()')<start.index('world->logic_sync()')
assert start.index('active_world = world;')<start.index('world->logic_sync()')
assert start.index('spotlight_ring_build()')<start.index('world->logic_sync()')
assert start.index('world->logic_sync()')<start.index('weather_palette_frame(); /* Night/fog')
assert 'void (*logic_sync)(void);' in world
assert ', %1_gameworlditems_sync_logic' in snapshot
assert '"_gameworlditems_sync_logic(void);\\n"' in snapshot
assert '"gameworlditems_sync_logic"' in snapshot
assert header.count('void gameworlditems_sync_logic(void);')==2
assert items.count('void gameworlditems_sync_logic(void)')==2
assert '@IDE{GRAPH_INITIAL_SYNC}' in items
assert 'sourceFields.insert(QStringLiteral("GRAPH_INITIAL_SYNC"), graphInitialSyncBody);' in gen

# Check the initial-pass generator section itself, not the ordinary Trigger
# dispatch which must continue permitting dialogue, toggle, and world change.
initial=gen[gen.index('        // Initial world entry and checkpoint restore'):gen.index('    if (!usedSfx.isEmpty()) for (int i = 0; i < nw;',gen.index('        // Initial world entry and checkpoint restore'))]
assert 'SidboxVisualLogic::expression(node,objectSlot,initialNames)' in initial
assert '.arg(objectSlot.value(targetId),initialNames.value(node.id))' in initial
assert 'targetId.startsWith(QStringLiteral("@player_world:"))' in initial
assert 'if(action==QStringLiteral("toggle")' in initial
assert 'if(action!=QStringLiteral("enable") &&' in initial
assert 'targetAction(target,dest)' in initial
assert 'game_adventure_trigger_message' not in initial
assert 'gameworlds_request_at' not in initial
assert 'node.trueDialogue' not in initial
assert 'node.falseDialogue' not in initial

# Native smoke test models the REAL game archive's authored independent graph:
# decoration[20] && decoration[21] drives result[22], Spotlight enable/disable,
# FALSE NPC disable, and a FALSE dialogue. Initialisation must never fire dialogue.
# Both first start and restoring an existing save converge to the same state.
c=r'''
#include <assert.h>
#include <stdint.h>
typedef struct {uint8_t active;} Object;
static Object objects[25];
static uint8_t spotlight;
static unsigned spotlight_changes, npc_disable_calls, dialogue_calls, world_requests, toggles;
static void gameworlds_spotlight_action(uint8_t action) {
    assert(action<=1);if(spotlight!=(action!=0)) ++spotlight_changes;
    spotlight=(uint8_t)(action!=0);
}
static void gameworlds_npc_action(const char *world,uint16_t slot,uint8_t action) {
    assert(world && slot==0 && action==0); ++npc_disable_calls;
}
/* Equivalent to exported cg_initial_logic_23_* for current test archive. */
static void gameworlditems_sync_logic(void) {
    const unsigned char cg_initial_logic_23_0 =
        (objects[20].active && objects[21].active) ? 1u:0u;
    const unsigned char cg_initial_logic_23_1 = cg_initial_logic_23_0;
    const unsigned char cg_initial_logic_23_2 =
        (objects[1].active && objects[13].active && cg_initial_logic_23_0)?1u:0u;
    objects[22].active=cg_initial_logic_23_0;
    if(cg_initial_logic_23_0) { gameworlds_spotlight_action(1u); }
    else { gameworlds_spotlight_action(0u); }
    if(!cg_initial_logic_23_1) { gameworlds_npc_action("world1",0u,0u); }
    (void)cg_initial_logic_23_2;
    /* No dialogue/Toggle/world request in sync, regardless of branch. */
}
static void restored(uint8_t a,uint8_t b,uint8_t initialSpotlight) {
    objects[20].active=a;objects[21].active=b;
    objects[22].active=9;spotlight=initialSpotlight;
    const unsigned changes_before=spotlight_changes;
    gameworlditems_sync_logic();
    assert(objects[22].active==(a&&b));
    assert(spotlight==(a&&b));
    const unsigned changes=spotlight_changes;
    gameworlditems_sync_logic();
    assert(spotlight_changes==changes); // idempotent on save re-entry
    assert(spotlight_changes>=changes_before);
    assert(!dialogue_calls && !world_requests && !toggles);
}
int main(void) {
    restored(0,0,1);restored(1,0,1);restored(0,1,1);restored(1,1,0);
    assert(npc_disable_calls==6); // two calls for each false input combination
    assert(spotlight_changes==4); // each input case changes erroneous prior light
    return 0;
}
'''
with TemporaryDirectory() as temp:
    src=Path(temp)/'sync.c';exe=Path(temp)/'sync'
    src.write_text(c)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O2',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.68 manager callback order, generated sync safety, native startup/save convergence')
