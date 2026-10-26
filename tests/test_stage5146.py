from pathlib import Path
import re,subprocess,tempfile
root=Path(__file__).resolve().parents[1]
editor=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
header=(root/'gamedesigner.h').read_text()
rule=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
# Data round-trip: the persisted type must be accepted by the loading whitelist,
# and all particle fields must be read and written with their exact JSON keys.
assert 'QStringLiteral("particle_emitter")}.contains(type)' in project
start=project.index('const QString type = object.value(')
end=project.index('r.pickupKind =',start)
assert 'QStringLiteral("particle_emitter")' in project[start:end]
fields=('particlePreset','particleAreaW','particleAreaH','particleCount','particleInterval','particleLifetime',
        'particleWind','particleFall','particleGravity','particleFlutter',
        'particleFadeEnabled','particleFadeIn','particleFadeOut','particleFadeSpeed')
for field in fields:
    assert 'r.' + field + ' = ' in project, field+' missing load'
    assert 'object.insert(QStringLiteral("'+field+'"), r.'+field+');' in project, field+' missing save'
    assert field in header
assert 'spin(1, 32, old.particleCount)' in editor
assert 'qBound(1, object.value(QStringLiteral("particleCount")).toInt(12), 32)' in project
assert 'qBound(1, r.particleCount, 32)' in export
assert '#define CG_PARTICLES_PER_EMITTER 32u' in rule
assert 'x < o->x - 96' not in rule
assert 'if (++particle->age >= s->lifetime)' in rule
assert 'if (dx <= -(int32_t)o->sprite->width' in rule
print('source checks: recognized world type, save/load fields, 32 cap and age-only recycle passed')

start=rule.index('@IDE_IF{HAS_PARTICLE_EMITTERS}\n')
end=rule.index('@IDE_END\n',start)
block=rule[start+len('@IDE_IF{HAS_PARTICLE_EMITTERS}\n'):end]
block=block.replace('@IDE{PARTICLE_EMITTER_COUNT}','1')
block=block.replace('@IDE{PARTICLE_EMITTER_ROWS}', '    {0u, 8u, 8u, 800u, -63, 40, 32, 1, 1, 4, 22, 0, 1, 20, 20, 8, 0, 24, 2},\n')
assert '@IDE' not in block
harness = r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#define GAME_OBJECT_PARTICLE_EMITTER 10u
#define BLIT_FLAG_TYPE_FADE_VALUE 0
#define BLIT_FLAG_ALPHABLEND 2u
typedef struct { uint16_t width,height; int16_t drawx,drawy; uint8_t flags; uint8_t flagval[4]; } gfxbob_t;
typedef struct { int32_t x,y; uint8_t active,type,draw_behind_tiles; gfxbob_t *sprite; } game_world_object_t;
static gfxbob_t bob = { 8,8,0,0,0,{0,0,0,0} };
static game_world_object_t cg_gwi_platforms[1] = { { 24,12,1,GAME_OBJECT_PARTICLE_EMITTER,0,&bob } };
static int draw_calls;
static void gfx_drawbob(const gfxbob_t *s) { (void)s; ++draw_calls; }
''' + block + r'''
int main(void) {
    (void)cg_particle_prewarm;
    cg_particle_reset();
    cg_particle_update(300);
    int active = 0;
    int beyond_old_limit = 0;
    for (unsigned int i = 0; i < CG_PARTICLES_PER_EMITTER; ++i) {
        const cg_particle_t *p = &cg_particles[0][i];
        active += p->active != 0;
        if (p->active && (p->x100/100 < cg_gwi_platforms[0].x-96 ||
            p->y100/100 > cg_gwi_platforms[0].y+8+96)) beyond_old_limit=1;
    }
    assert(active == 32);
    assert(beyond_old_limit);
    assert(cg_particles[0][0].active && cg_particles[0][0].age == 300);
    assert(cg_particles[0][0].fade == 0);
    /* Age, not travel distance, eventually retires a particle. */

    cg_particles[0][0].age=799;
    cg_particle_update(1);
    assert(cg_particles[0][0].active == 0);
    /* Drawing culls offscreen particles without destroying them. */
    cg_particle_reset();
    cg_particle_update(1);
    assert(cg_particles[0][0].active);
    cg_particle_draw(9999,9999,0,0);
    assert(draw_calls == 0);
    assert(cg_particles[0][0].active);
    cg_particle_draw(0,0,0,0);
    assert(cg_particles[0][0].active);
    /* World reset clears all particles. */
    cg_particle_reset();
    for (unsigned i=0; i<32; ++i) assert(!cg_particles[0][i].active);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as folder:
    src=Path(folder)/'test.c'; src.write_text(harness)
    exe=Path(folder)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('native GCC: 32 particles, distant movement, 800-frame expiry, draw cull and reset passed')
