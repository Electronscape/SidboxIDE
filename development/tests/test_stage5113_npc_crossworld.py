#!/usr/bin/env python3
"""Stage5.113: compile the real queued NPC visibility routines and audit UI/export wiring."""
from pathlib import Path
import subprocess,tempfile
root=Path(__file__).resolve().parents[2]
rule=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
editor=(root/'gamedesigner.cpp').read_text()
generator=(root/'gameadventuregen.cpp').read_text()
exporter=(root/'gamedesigner_export.cpp').read_text()
adv=(root/'gameadventureeditor.cpp').read_text()
flow=(root/'gamefloweditor.cpp').read_text()

def fn(source,signature):
    i=source.index(signature);j=source.index('{',i);depth=1;k=j+1
    while depth:
        if source[k]=='{':depth+=1
        if source[k]=='}':depth-=1
        k+=1
    return source[i:k]

names=['gameadventure_npc_action','gameadventure_npc_remote_action','gameadventure_npc_remote_reset','gameadventure_restore_progress']
funcs='\n\n'.join(fn(rule,'void '+x+'(') for x in names)
# Use the production C functions unchanged. The mock mimics renderer visibility
# and verifies that unrelated story state is not restored on the first visit.
src='''#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#define GAME_ADVENTURE_STORY_NPC_COUNT 2u
#define GAME_ADVENTURE_NPC_VISIBILITY_BYTES 256u
#define GAME_ADVENTURE_USED_CHOICE_BYTES 96u
#define GAME_ADVENTURE_COMPLETED_NPC_BYTES 256u
#define GAME_ADVENTURE_CLOSE_GIFT_BYTES 32u
#define GAME_ADVENTURE_MAX_DROPS 32u
#define GAME_ADVENTURE_EXCHANGE_SLOTS 256u
typedef struct {uint8_t active;} game_adventure_drop_t;
static const uint8_t npc_initial_visibility[2]={1,0};
static uint8_t cg_saved_story_choices[96], cg_saved_story_npcs[256],cg_saved_npc_visibility[256],cg_saved_close_gifts[32];
static uint8_t cg_saved_story_valid, cg_saved_world_drops[32],cg_saved_exchanges[256],cg_saved_wrong_repeats[256];
static uint8_t cg_pending_npc_mask[256],cg_pending_npc_state[256];
static uint8_t visible[2]={1,0};
static int story_restores;
static void game_adventure_npc_action(uint16_t n,uint8_t a) {
  if(n>=2)return;
  if(a==0)visible[n]=0;
  else if(a==1)visible[n]=1;
  else if(a==2)visible[n]^=1;
}
static void game_adventure_set_npc_visible(uint16_t n,uint8_t v){if(n<2)visible[n]=v;}
static void game_adventure_restore_progress(const uint8_t *a,const uint8_t *b){(void)a;(void)b;story_restores++;}
static void game_adventure_restore_npc_visibility(const uint8_t *a){memcpy(visible,a,2);}
static void game_adventure_restore_close_gifts(const uint8_t *a){(void)a;}
static void game_adventure_restore_drops(const uint8_t *a){(void)a;}
static void game_adventure_restore_exchanges(const uint8_t *a){(void)a;}
static void game_adventure_restore_wrong_repeats(const uint8_t *a){(void)a;}
'''+funcs+'''
int main(void) {
  /* Forest first visit: original naked Steve visible, dressed Steve hidden. */
  gameadventure_npc_remote_action(0,0);
  gameadventure_npc_remote_action(1,1);
  gameadventure_restore_progress();
  assert(visible[0]==0 && visible[1]==1 && story_restores==0);
  assert(!cg_pending_npc_mask[0] && !cg_pending_npc_mask[1]);
  /* Saved appearance after first visit, then two remote toggles. */
  cg_saved_story_valid=1;cg_saved_npc_visibility[0]=0;cg_saved_npc_visibility[1]=1;
  gameadventure_npc_remote_action(1,2); gameadventure_npc_remote_action(1,2);
  visible[0]=1;visible[1]=0;
  gameadventure_restore_progress();
  assert(visible[0]==0 && visible[1]==1 && story_restores==1);
  /* Single toggle from stored value really hides dressed Steve. */
  gameadventure_npc_remote_action(1,2);
  gameadventure_restore_progress();
  assert(visible[1]==0);
  /* Fresh game clears pending state and any world story snapshot. */
  gameadventure_npc_remote_action(0,1);
  gameadventure_npc_remote_reset();
  assert(!cg_pending_npc_mask[0] && !cg_saved_story_valid);
  visible[0]=1;visible[1]=0;
  gameadventure_restore_progress();
  assert(visible[0]==1 && visible[1]==0 && story_restores==2);
  puts("PASS Stage 5.113 remote NPC hide/show/toggle, world restore and reset");
  return 0;
}'''
with tempfile.TemporaryDirectory() as d:
    srcfile=Path(d)/'npc.c';srcfile.write_text(src)
    exe=Path(d)/'npc'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',str(srcfile),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
for check,src in [
  ('gameworlds_npc_action',world),('_gameadventure_npc_remote_action', (root/'gameworldsnapshot.h').read_text()),
  ('remoteNpcActionRows',generator),('REMOTE_NPC_ACTION_ROWS',generator),
  ('npcTarget(r.targetObjectId',exporter),('npcTarget(link.objectId',exporter),
  ('gameworlds_npc_action(',exporter),('NPC: %1 [%2]',editor),
  ('appendNpcTargets',adv),('npcActionNode',flow),
  ('game_adventure_remote_npc_actions(remote_npc_actions',rule)]:
    assert check in src,check
print('PASS Stage 5.113 editor/generator/action/flow integration checks')
