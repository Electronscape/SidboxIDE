"""Stage 5.150: runtime particle prewarm, opt-out, save/load, preview parity."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[1]
rule=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
editor=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
model=(root/'gamedesigner.h').read_text()
for s in ('particlePrepopulate', 'Pre-populate on world load'):
    assert s in editor and s in model or s == 'Pre-populate on world load' and s in editor
assert 'r.particlePrepopulate = object.value(QStringLiteral("particlePrepopulate")).toBool(true);' in project
assert 'object.insert(QStringLiteral("particlePrepopulate"), r.particlePrepopulate);' in project
assert '.arg(r.particlePrepopulate ? 1 : 0)' in export
assert '    cg_particle_prewarm();' in rule
assert 'if (!s->prepopulate || !o->active || !o->sprite) continue;' in rule
assert 'if (newlyCreated && r.particlePrepopulate)' in editor
assert 'const int warmFrames = qMin(lifetime - 1, limit * interval);' in editor
assert 'for (int frame = 0; frame < warmFrames; ++frame) stepParticles();' in editor
assert 'old.prepopulate != r.particlePrepopulate' in editor
assert 'Build: 5.158.261026' in (root/'splashscreenwidget.cpp').read_text()

start=rule.index('@IDE_IF{HAS_PARTICLE_EMITTERS}\n')
end=rule.index('@IDE_END\n',start)
block=rule[start+len('@IDE_IF{HAS_PARTICLE_EMITTERS}\n'):end]
block=block.replace('@IDE{PARTICLE_EMITTER_COUNT}', '3')
block=block.replace('@IDE{PARTICLE_EMITTER_ROWS}',
    '    {0u,240u,96u,400u,-63,40,32,6,1,4,22,1,1,20,20,8, 0, 24, 2},\n'
    '    {1u,240u,96u,250u,45,0,24,12,0,0,4,0,0,20,20,8, 0, 24, 2},\n'
    '    {2u,240u,96u,250u,45,0,24,12,1,0,4,0,0,20,20,8, 0, 24, 2},\n')
assert '@IDE' not in block
harness = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#define BLIT_FLAG_TYPE_FADE_VALUE 0
#define BLIT_FLAG_ALPHABLEND 2u
typedef struct { uint16_t width,height; int16_t drawx,drawy; uint8_t flags; uint8_t flagval[4]; } gfxbob_t;
typedef struct { int32_t x,y; uint8_t active,type,draw_behind_tiles; gfxbob_t *sprite; } game_world_object_t;
static gfxbob_t sprite={8,8,0,0,0,{0}};
static game_world_object_t cg_gwi_platforms[3]={{24,12,1,10,0,&sprite},{25,13,1,10,0,&sprite},{24,12,0,10,0,&sprite}};
static void gfx_drawbob(const gfxbob_t *s) {(void)s;}
''' + block + r'''
int main(void) {
    (void)cg_particle_draw;
    cg_particle_reset();
    cg_particle_prewarm();
    unsigned filled=0, aged=0, drifting=0;
    for(unsigned i=0;i<32;++i) {
       cg_particle_t *p=&cg_particles[0][i];
       filled += p->active != 0;
       aged += p->active && p->age > 1;
       drifting += p->active && p->x100 < 2400;
    }
    assert(filled==32 && aged>=30 && drifting>0);
    assert(cg_particle_ticks[0]==0);
    /* Disabled or opted-out spawners start empty, not pre-warmed. */
    for(unsigned e=1;e<3;++e) {
        assert(cg_particle_ticks[e]==0);
        for(unsigned i=0;i<32;++i) assert(!cg_particles[e][i].active);
    }
    /* A deterministic reset + warmup produces the same seasoned field. */
    cg_particle_t before[32];
    memcpy(before,cg_particles[0],sizeof(before));
    cg_particle_reset();
    cg_particle_prewarm();
    assert(memcmp(before,cg_particles[0],sizeof(before))==0);
    /* Starting fresh with no prewarm remains valid for scripted arrivals. */
    cg_particle_reset();
    assert(!cg_particles[0][0].active);
    cg_particle_update(6);
    assert(cg_particles[0][0].active);
    assert(!cg_particles[2][0].active);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as tmp:
    src=Path(tmp)/'test.c'; src.write_text(harness)
    exe=Path(tmp)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.150: native GCC startup-density, preview, opt-out and disabled-spawner tests passed')
