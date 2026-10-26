from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[1]
editor=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
header=(root/'gamedesigner.h').read_text()
rule=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
worlds_h=(root/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
main_rule=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
snapshot=(root/'gameworldsnapshot.h').read_text()

assert 'particlePlayerLayerMix' in header
assert 'r.particlePlayerLayerMix = object.value(QStringLiteral("particlePlayerLayerMix")).toBool(false);' in project
assert 'object.insert(QStringLiteral("particlePlayerLayerMix"), r.particlePlayerLayerMix);' in project
assert 'particlePlayerMix' in editor
assert '.arg(r.particlePlayerLayerMix ? 1 : 0)' in export
assert '%15' in export
assert 'draw_after_player' in rule
assert 'cg_particle_draw(int32_t camera_x, int32_t camera_y, uint8_t behind, uint8_t overlay_pass)' in rule
assert 'void gameworlditems_draw_overlay(int32_t camera_x, int32_t camera_y)' in rule
assert 'void gameworlds_draw_overlay(int32_t camera_x, int32_t camera_y);' in worlds_h
assert 'gameworlds_draw_overlay(camera_x, camera_y);' in main_rule
assert 'gameworlditems_draw_overlay' in snapshot
print('source checks: player-layer mix persisted/exported and overlay render path published')

start=rule.index('@IDE_IF{HAS_PARTICLE_EMITTERS}\n')
end=rule.index('@IDE_END\n',start)
block=rule[start+len('@IDE_IF{HAS_PARTICLE_EMITTERS}\n'):end]
block=block.replace('@IDE{PARTICLE_EMITTER_COUNT}','1')
block=block.replace('@IDE{PARTICLE_EMITTER_ROWS}', '    {0u, 8u, 8u, 60u, 0, 0, 2, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 24, 2},\n')
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
    cg_particle_update(4);
    /* Force one particle into each render pass to verify separation. */
    cg_particles[0][0].active = 1; cg_particles[0][0].x100 = 2500; cg_particles[0][0].y100 = 1300; cg_particles[0][0].draw_after_player = 0;
    cg_particles[0][1].active = 1; cg_particles[0][1].x100 = 2600; cg_particles[0][1].y100 = 1400; cg_particles[0][1].draw_after_player = 1;
    draw_calls = 0;
    cg_particle_draw(0,0,0,0);
    assert(draw_calls == 1);
    draw_calls = 0;
    cg_particle_draw(0,0,0,1);
    assert(draw_calls == 1);
    draw_calls = 0;
    cg_particle_draw(0,0,1,0);
    assert(draw_calls == 0);
    /* Draw-behind emitters never switch into the overlay pass. */
    cg_gwi_platforms[0].draw_behind_tiles = 1;
    cg_particle_reset();
    cg_particle_update(2);
    for (unsigned i=0;i<2;++i) if (cg_particles[0][i].active) assert(cg_particles[0][i].draw_after_player == 0);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as folder:
    src=Path(folder)/'test.c'; src.write_text(harness)
    exe=Path(folder)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('native GCC: overlay-pass split and behind-tile suppression passed')
