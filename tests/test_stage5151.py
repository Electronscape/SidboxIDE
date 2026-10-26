"""Stage 5.151 native firefly orbit, old-mode compatibility, and editor persistence."""
from pathlib import Path
import re, subprocess, tempfile
root=Path(__file__).resolve().parents[1]
model=(root/'gamedesigner.h').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
editor=(root/'gamedesigner.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
rule=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
for field in ('particleSwirlRadius','particleSwirlSpeed'):
    assert field in model and field in editor
    assert 'r.'+field+' = qBound(' in project
    assert 'object.insert(QStringLiteral("'+field+'"), r.'+field+');' in project
    assert 'draft.'+field+' = ' in editor
assert 'QStringLiteral("fireflies")' in project and 'Swirling fireflies' in editor
assert '.arg(r.particlePreset == QStringLiteral("fireflies") ? 1 : 0)' in export
assert '%19' in export
assert 'old.preset != r.particlePreset' in editor
assert 'old.swirlRadius != r.particleSwirlRadius' in editor
assert 'for (int frame = 0; frame < warmFrames; ++frame) stepParticles();' in editor
assert 's->swirl_mode' in rule and 'if (s->swirl_mode)' in rule
assert 'Build: 5.151.261026' in (root/'splashscreenwidget.cpp').read_text()
# Keep the LUT used in Qt's live preview numerically identical to firmware.
m1=re.search(r'static const int8_t cg_particle_sine\[64\] = \{([^}]+)\};',rule)
m2=re.search(r'static const qint8 swirlSine\[64\] = \{([^}]+)\};',editor)
assert m1 and m2
parse=lambda x:[int(v.strip()) for v in x.split(',') if v.strip()]
assert len(parse(m1.group(1)))==64
assert parse(m1.group(1))==parse(m2.group(1))
print('Stage 5.151 editor save/load/export and Qt/firmware orbit lookup parity PASS')

start=rule.index('@IDE_IF{HAS_PARTICLE_EMITTERS}\n')
end=rule.index('@IDE_END\n',start)
block=rule[start+len('@IDE_IF{HAS_PARTICLE_EMITTERS}\n'):end]
block=block.replace('@IDE{PARTICLE_EMITTER_COUNT}','2')
block=block.replace('@IDE{PARTICLE_EMITTER_ROWS}',
   '    {0u,128u,100u,600u,0,0,1,1,1,0,0,0,1,20,20,8,1,24,2},\n'
   '    {1u,128u,100u,600u,-63,40,1,1,1,4,22,0,1,20,20,8,0,24,2},\n')
assert '@IDE' not in block
harness=r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#define BLIT_FLAG_TYPE_FADE_VALUE 0
#define BLIT_FLAG_ALPHABLEND 2u
typedef struct {uint16_t width,height;int16_t drawx,drawy;uint8_t flags;uint8_t flagval[4];} gfxbob_t;
typedef struct {int32_t x,y;uint8_t active,type,draw_behind_tiles;gfxbob_t *sprite;} game_world_object_t;
static gfxbob_t sprite={4,4,0,0,0,{0}};
static game_world_object_t cg_gwi_platforms[2]={{100,100,1,10,0,&sprite},{100,100,1,10,0,&sprite}};
static unsigned calls;
static void gfx_drawbob(const gfxbob_t *s){(void)s;++calls;}
'''+block+r'''
int main(void) {
    cg_particle_reset();
    cg_particle_update(1);
    const cg_particle_t *fire=&cg_particles[0][0], *leaf=&cg_particles[1][0];
    assert(fire->active && leaf->active);
    assert(fire->swirl_radius>=12 && fire->swirl_radius<=24);
    assert(fire->x100!=fire->centre_x100 || fire->y100!=fire->centre_y100);
    int32_t fx=fire->x100, fy=fire->y100;
    uint8_t phase=fire->swirl_phase;
    int32_t lx=leaf->x100, ly=leaf->y100;
    cg_particle_update(128); /* Firefly returns to starting orbit phase. */
    assert(fire->active && fire->swirl_phase==phase);
    assert(fire->x100==fx && fire->y100==fy);
    assert(leaf->x100!=lx && leaf->y100>ly);
    /* Rendering still respects pass selection and world visibility. */
    cg_particle_draw(0,0,0,0);
    assert(calls>0);
    calls=0;cg_particle_draw(0,0,1,1);assert(calls==0);
    cg_particle_reset();
    cg_particle_prewarm();
    assert(cg_particles[0][0].active && cg_particles[0][0].age==1);
    cg_particle_reset();
    cg_particle_update(1);
    assert(fire->active && fire->age==1);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as t:
    src=Path(t)/'orbit.c';src.write_text(harness)
    exe=Path(t)/'orbit'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.151 native GCC firefly orbit, prewarm, legacy leaf physics, and render passes PASS')
