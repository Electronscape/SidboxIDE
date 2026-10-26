from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
source=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
start=source.index('@IDE_IF{HAS_PARTICLE_EMITTERS}\n')
end=source.index('@IDE_END\n',start)
block=source[start + len('@IDE_IF{HAS_PARTICLE_EMITTERS}\n'):end]
block=block.replace('@IDE{PARTICLE_EMITTER_COUNT}','1').replace('@IDE{PARTICLE_EMITTER_ROWS}','{0u, 140u, 70u, 210u, 65, 40, 12, 2, 1, 2, 20, 0, 0, 0, 0, 8, 0, 24, 2},\n')
assert '@IDE' not in block
harness = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#define GAME_OBJECT_PARTICLE_EMITTER 10u
#define BLIT_FLAG_TYPE_FADE_VALUE 0
#define BLIT_FLAG_ALPHABLEND 0x02u
typedef struct { uint16_t width,height; int16_t drawx,drawy; uint8_t flags; uint8_t flagval[16]; } gfxbob_t;
typedef struct { int32_t x,y; uint8_t active,type,draw_behind_tiles; gfxbob_t *sprite; } game_world_object_t;
static gfxbob_t object_sprite = {8,8,0,0,0,{0}};
static game_world_object_t cg_gwi_platforms[1]={{24,12,1,GAME_OBJECT_PARTICLE_EMITTER,0,&object_sprite}};
static int draw_calls=0, last_x=0, last_y=0;
static void gfx_drawbob(const gfxbob_t *o) { ++draw_calls; last_x=o->drawx; last_y=o->drawy; }
''' + block + r'''
int main(void) {
    (void)cg_particle_prewarm;
  cg_particle_reset();
  for (int i=0; i<60; ++i) cg_particle_update(1);
  int active=0;
  for (int i=0; i<12; ++i) active+=cg_particles[0][i].active!=0;
  assert(active>0 && active<=12);
  int count=draw_calls;
  cg_particle_draw(0,0,1,0);
  assert(draw_calls==count); /* emitter configured for foreground */
  cg_particle_draw(0,0,0,0);
  assert(draw_calls>count);
  assert(last_x>=-8 && last_y>=-8);
  count=draw_calls;
  cg_gwi_platforms[0].draw_behind_tiles=1;
  cg_particle_draw(0,0,0,0);
  assert(draw_calls==count);
  cg_particle_draw(0,0,1,0);
  assert(draw_calls>count);
  cg_gwi_platforms[0].active=0;
  count=draw_calls;
  cg_particle_draw(0,0,1,0);
  assert(draw_calls==count);
  cg_gwi_platforms[0].active=1;
  cg_particle_reset();
  for (int i=0;i<12;++i) assert(cg_particles[0][i].active==0);
  return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
    c=Path(d)/'particle_test.c';c.write_text(harness)
    exe=Path(d)/'particles'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.143 native particle runtime test PASSED (emission, culling, layers, disable, reset)')
for needle in ['GAME_OBJECT_PARTICLE_EMITTER', 'o->type == GAME_OBJECT_PARTICLE_EMITTER']:
    assert needle in (root/'idelibs/codehelpers/game/worldobjects.rulec').read_text()
for needle in ['particleAreaW','particleAreaH','particleCount','particleInterval','particleLifetime','particleWind','particleFall','particleGravity','particleFlutter','particlePreset']:
    assert needle in (root/'gamedesigner.h').read_text()
    assert needle in (root/'gamedesigner_project.cpp').read_text()
    assert needle in (root/'gamedesigner.cpp').read_text()
print('Stage 5.143 editor field and runtime guards PASSED')
