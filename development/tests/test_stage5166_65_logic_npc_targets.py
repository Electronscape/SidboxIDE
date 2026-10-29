#!/usr/bin/env python3
"""Stage 5.166.65: independent logic branch action targets share ordinary Trigger semantics.

Test the actual NPC action functions extracted from the shipping runtime rules.
The full Qt generator cannot be built here; structural checks assert that the
validated local/NPC/remote/spotlight contract feeds the existing action emitter.
"""
from pathlib import Path
import subprocess
from tempfile import TemporaryDirectory

root = Path(__file__).resolve().parents[2]
export = (root / 'gamedesigner_export.cpp').read_text()
designer = (root / 'gamedesigner.cpp').read_text()
editor = (root / 'gamevisualnodes.cpp').read_text()
worlds = (root / 'idelibs/codehelpers/game/gameworlds.rulec').read_text()
adventure = (root / 'idelibs/codehelpers/game/adventureruntime.rulec').read_text()

# The *same* compatibility check is used by the Trigger and logic compilers.
assert export.count('actionTargetExists(') >= 3
assert 'return remoteTarget(id,&targetWorld,&targetSlot) ||\n               npcTarget(id,&targetWorld,&targetSlot);' in export
assert 'QString wantedWorld=worldBase;' in export
assert 'QString wantedSprite=id;' in export  # Old Visual Nodes NPC sprite-ID links.
assert 'if (id.startsWith(QStringLiteral("@npc:"))) {' in export  # Full canonical NPC targets.
assert 'if (npcs[n].toObject().value(QStringLiteral("spriteId")).toString()!=wantedSprite) continue;' in export
assert 'gameworlds_npc_action(\\"%1\\", %2u, %3u);' in export
assert 'if(!targetAction(target,&graphDispatchBody))return false;' in export
assert 'SidboxVisualLogic::order(nodes,localIds,&sorted,&issue)' in export
assert 'for(const QString &targetId:node.resultTargets)' in export
assert 'if(graphValue && (object.type==QStringLiteral("trigger") ||' in editor
assert 'object.type==QStringLiteral("npc") || object.resourceIndex<0))continue;' in editor
assert 'npcIds.contains(candidate.id)\n                                ? tr("NPC: %1")' in designer
assert 'm_objects.value(target).type==QStringLiteral("npc") ||' in editor
assert 'm_objects.value(source).type!=QStringLiteral("npc")' in editor
assert 'm_objects.value(id).type!=QStringLiteral("npc")' in editor

# Exercise actual native C for the runtime's Action type: SHOW/HIDE/TOGGLE.
def extract(text, sig):
    start = text.index(sig)
    brace = text.index('{', start)
    level = 0
    for i in range(brace, len(text)):
        if text[i] == '{': level += 1
        elif text[i] == '}':
            level -= 1
            if level == 0:
                return text[start:i+1]
    raise AssertionError('unclosed function ' + sig)

npc_world_action = extract(worlds, 'uint8_t gameworlds_npc_action(')
npc_visibility_action = extract(adventure, 'void game_adventure_npc_action(')
program = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#define GAME_ADVENTURE_NPC_HIDE 0u
#define GAME_ADVENTURE_NPC_SHOW 1u
#define GAME_ADVENTURE_NPC_TOGGLE 2u
static uint16_t ga_npc_count = 1;
static uint8_t ga_npc_visibility[256];
typedef struct {
  const char *name;
  void (*npc_set_active)(uint16_t,uint8_t);
  void (*npc_remote_action)(uint16_t,uint8_t);
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
static const gameworlds_record_t *find_world(const char *name);
''' + npc_visibility_action + '\n' + npc_world_action + r'''
static const gameworlds_record_t worlds[]={{"world1",game_adventure_npc_action,game_adventure_npc_action},
                                           {"forest",game_adventure_npc_action,game_adventure_npc_action}};
static const gameworlds_record_t *find_world(const char *name) {
  for (unsigned i=0;i<sizeof(worlds)/sizeof(worlds[0]);i++)
    if(!strcmp(worlds[i].name,name))return &worlds[i];
  return 0;
}
int main(void) {
  active_world=&worlds[0];
  ga_npc_visibility[0]=1;
  uint8_t switch0=0, switch1=0;
  // Independent AND -> Boolean RESULT -> FALSE branch -> Disable Guardian.
  for(int seq=0;seq<4;seq++) {
    switch0=(uint8_t)((seq==1)||(seq==3));
    switch1=(uint8_t)(seq>=2);
    const uint8_t logic1=(uint8_t)(switch0 && switch1);
    const uint8_t logic2=logic1;
    if(!logic2)assert(gameworlds_npc_action("world1",0u,0u));
    else assert(gameworlds_npc_action("world1",0u,1u));
    assert(ga_npc_visibility[0]==logic2);
  }
  assert(gameworlds_npc_action("world1",0u,2u));assert(!ga_npc_visibility[0]);
  assert(gameworlds_npc_action("forest",0u,1u));assert(ga_npc_visibility[0]);
  assert(!gameworlds_npc_action("missing",0u,0u));
  assert(!gameworlds_npc_action("world1",0u,3u));
  return 0;
}
'''
with TemporaryDirectory() as d:
    source = Path(d) / 'logic_npc.c'
    binary = Path(d) / 'logic_npc'
    source.write_text(program)
    subprocess.run(['gcc', '-std=c11', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source), '-o', str(binary)], check=True)
    subprocess.run([str(binary)], check=True)
print('PASS Stage 5.166.65 shared target compatibility and actual native NPC visibility actions')
