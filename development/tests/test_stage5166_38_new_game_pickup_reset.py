#!/usr/bin/env python3
"""Stage 5.166.38: compile REAL world reset and disk snapshot functions.

Check multi-world New Game resets collection flags while Load Game still
restores each world's persistent pickups. Covers worlds with and without
managed platforms, and reward state.
"""
from pathlib import Path
import re, subprocess, tempfile

root=Path(__file__).resolve().parents[2]
source=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
story=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert 'if(worlds[i].object_remote_reset)worlds[i].object_remote_reset();' in world
assert 'if(worlds[i].npc_remote_reset)worlds[i].npc_remote_reset();' in world
assert 'gw_reset_title_session();' in world
assert 'gameworlds_load_slot((uint8_t)selected_slot)' in world
assert 'memset(cg_saved_story_choices, 0, sizeof(cg_saved_story_choices));' in story
assert 'memset(cg_saved_world_drops, 0, sizeof(cg_saved_world_drops));' in story

def body_fn(text, sign, occurrence=0):
    i=-1
    for _ in range(occurrence+1):
        i=text.index(sign,i+1)
    j=text.index('{',i)
    d=1;k=j+1
    while d:
        if text[k]=='{':d+=1
        elif text[k]=='}':d-=1
        k+=1
    return text[i:k]

def render_optional(text, options):
    lines=[]; st=[]; active=True
    for line in text.splitlines():
        m=re.fullmatch(r'@IDE_IF\{(\w+)\}',line.strip())
        if m:
            st.append((active,options.get(m[1],False)))
            active=active and options.get(m[1],False)
        elif line.strip()=='@IDE_ELSE':
            base,enabled=st[-1];active=base and not enabled
        elif line.strip()=='@IDE_END':
            active=st.pop()[0]
        elif active:lines.append(line)
    assert not st
    return '\n'.join(lines)+'\n'

# World0 has managed platforms/rewards; world1 has pickups but no platforms.
# Both compile production reset + production disk export/import functions.
with tempfile.TemporaryDirectory(prefix='stage516638_') as t:
    directory=Path(t)
    for n,managed in enumerate((True,False)):
        options={'HAS_REWARDS':True}
        reset=render_optional(body_fn(source,'void gameworlditems_remote_reset(void)',0 if managed else 1),options)
        exports=render_optional(body_fn(source,'void gameworlditems_disk_export('),{'HAS_WORLDS':managed,'HAS_PICKUPS':True,'HAS_REWARDS':True})
        imports=render_optional(body_fn(source,'uint8_t gameworlditems_disk_import('),{'HAS_WORLDS':managed,'HAS_PICKUPS':True,'HAS_REWARDS':True})
        code=r'''#include <stdint.h>
#include <string.h>
#include <assert.h>
#define GAMEWORLDITEMS_PICKUP_COUNT 2
static uint8_t cg_world_snapshot_valid;
static uint8_t cg_saved_pickups[2][60];
static uint8_t cg_pickup_permanently_collected[2];
static uint8_t cg_saved_reward_falling[2];
static int32_t cg_saved_reward_x100[2],cg_saved_reward_y100[2],cg_saved_reward_vx100[2],cg_saved_reward_vy100[2];
'''
        if managed:
            code+='''static uint8_t cg_remote_valid[2],cg_remote_active[2];
static uint8_t cg_saved_objects[2][60];
'''
        code+=(reset+'\n'+exports+'\n'+imports+'\n').replace('gameworlditems_remote_reset',f'gw_reset_{n}').replace('gameworlditems_disk_export',f'gw_export_{n}').replace('gameworlditems_disk_import',f'gw_import_{n}')
        code+=f'''
uint8_t collected_{n}(void){{return cg_pickup_permanently_collected[0];}}
uint8_t valid_{n}(void){{return cg_world_snapshot_valid;}}
void collect_{n}(void){{
  cg_world_snapshot_valid=1u;
  cg_saved_pickups[0][0]=0;
  cg_saved_pickups[1][0]=1;
  cg_pickup_permanently_collected[0]=1u;
  cg_saved_reward_falling[0]=1u;
  cg_saved_reward_x100[0]=444;
}}
void reset_{n}(void){{gw_reset_{n}();}}
void export_{n}(void (*cb)(const void*,uint32_t,void*),void *ctx){{gw_export_{n}(cb,ctx);}}
uint8_t import_{n}(uint8_t (*cb)(void*,uint32_t,void*),void *ctx){{return gw_import_{n}(cb,ctx);}}
uint8_t fresh_{n}(void){{
    const uint8_t b[2]={{0}};
    (void)b;
    return !cg_world_snapshot_valid &&
           !cg_pickup_permanently_collected[0] && !cg_pickup_permanently_collected[1] &&
           !cg_saved_pickups[0][0] && !cg_saved_pickups[1][0] &&
           !cg_saved_reward_falling[0] && !cg_saved_reward_x100[0];
}}
'''
        (directory/f'world{n}.c').write_text(code)
    harness=r'''#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct { uint8_t bytes[4096]; uint32_t size, pos; } stream_t;
static void emit(const void *p,uint32_t len,void *ctx){
 stream_t *s=ctx;assert(s->pos+len<=sizeof(s->bytes));
 memcpy(s->bytes+s->pos,p,len);s->pos+=len;s->size=s->pos;
}
static uint8_t take(void *p,uint32_t len,void *ctx){
 stream_t *s=ctx;if(s->pos+len>s->size)return 0;
 memcpy(p,s->bytes+s->pos,len);s->pos+=len;return 1;
}
#define DECL(n) \
void collect_##n(void);void reset_##n(void);uint8_t collected_##n(void); \
uint8_t valid_##n(void);uint8_t fresh_##n(void); \
void export_##n(void(*)(const void*,uint32_t,void*),void*); \
uint8_t import_##n(uint8_t(*)(void*,uint32_t,void*),void*);
DECL(0) DECL(1)
int main(void){
  stream_t a={0},b={0};
  collect_0();collect_1();
  assert(collected_0() && collected_1());
  export_0(emit,&a);export_1(emit,&b);
  /* Death -> Title -> New Game resets every world's memory. */
  reset_0();reset_1();
  assert(fresh_0() && fresh_1());
  /* The same New Game must not resurrect a pickup upon world revisit. */
  assert(!collected_0() && !collected_1());
  /* Load a saved slot: its collected flags must come back. */
  a.pos=0;b.pos=0;
  assert(import_0(take,&a) && import_1(take,&b));
  assert(collected_0() && collected_1() && valid_0() && valid_1());
  /* Another New Game clears the loaded session too. */
  reset_0();reset_1();
  assert(fresh_0() && fresh_1());
  puts("PASS Stage 5.166.38: per-world pickup reset, saved reward reset, save restoration");
  return 0;
}
'''
    (directory/'test.c').write_text(harness)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O2',str(directory/'test.c'),str(directory/'world0.c'),str(directory/'world1.c'),'-o',str(directory/'test')],check=True)
    subprocess.run([str(directory/'test')],check=True)
print('PASS Stage 5.166.38 real reset functions for worlds with/without platforms')
