from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
source=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
a=source.index('@IDE_IF{HAS_PARTICLE_EMITTERS}\n')
b=source.index('@IDE_END\n',a)
block=source[a + len('@IDE_IF{HAS_PARTICLE_EMITTERS}\n'):b]
block=block.replace('@IDE{PARTICLE_EMITTER_COUNT}','1').replace('@IDE{PARTICLE_EMITTER_ROWS}',
    '{0u, 140u, 70u, 100u, 65, 40, 1u, 2u, 1u, 2u, 20u, 0u, 1u, 20u, 20u, 10u, 0, 24, 2},\n')
assert '@IDE' not in block
harness=r'''
#include <assert.h>
#include <stdint.h>
#include <string.h>
#define BLIT_FLAG_TYPE_FADE_VALUE 0
#define BLIT_FLAG_ALPHABLEND 0x02u
typedef struct {uint16_t width,height;int16_t drawx,drawy;uint8_t flags;uint8_t flagval[16];}gfxbob_t;
typedef struct {int32_t x,y;uint8_t active,type,draw_behind_tiles;gfxbob_t *sprite;}game_world_object_t;
static gfxbob_t object_sprite={8,8,0,0,0,{0}};
static game_world_object_t cg_gwi_platforms[1]={{24,12,1,10,0,&object_sprite}};
static int draw_calls, last_fade; static uint8_t last_flags;
static void gfx_drawbob(const gfxbob_t *bob){++draw_calls;last_fade=bob->flagval[0];last_flags=bob->flags;}
''' + block + r'''
int main(void){
    (void)cg_particle_prewarm;
 cg_particle_reset();
 cg_particle_update(2);
 assert(cg_particles[0][0].active);
 assert(cg_particles[0][0].fade>=90);
 cg_particle_draw(0,0,0,0);
 assert(draw_calls>0 && last_flags & BLIT_FLAG_ALPHABLEND);
 int first=last_fade;
 for(int i=0;i<15;++i)cg_particle_update(1);
 cg_particle_draw(0,0,0,0);
 assert(last_fade<first);
 for(int i=0;i<30;++i)cg_particle_update(1);
 cg_particle_draw(0,0,0,0);
 assert(last_fade==0 && !(last_flags & BLIT_FLAG_ALPHABLEND));
 /* Turn off new births to assess the final fade of the same leaf. */
 cg_particle_ticks[0]=0;
 for(int i=0;i<43;++i)cg_particle_update(1);
 assert(cg_particles[0][0].active);
 cg_particle_draw(0,0,0,0);
 assert(last_fade>0);
 /* Disabling spawner still disables rendering. */
 cg_gwi_platforms[0].active=0;
 int prev=draw_calls;
 cg_particle_draw(0,0,0,0);
 assert(prev==draw_calls);
 return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
 c=Path(d)/'test.c';c.write_text(harness)
 exe=Path(d)/'test'
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(c),'-o',str(exe)],check=True)
 subprocess.run([str(exe)],check=True)
print('Stage 5.145 particle fade native test PASSED')
model=(root/'gamedesigner.h').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
ui=(root/'gamedesigner.cpp').read_text()
gen=(root/'gamedesigner_export.cpp').read_text()
for field in ('particleFadeEnabled','particleFadeIn','particleFadeOut','particleFadeSpeed'):
 assert field in model and field in project and field in ui and field in gen
for needed in ('m_particleResizeHandles','m_particleResizeStart','m_particleResizeHandle'):
 assert needed in (root/'gamedesigner.h').read_text() and needed in ui
assert 'rememberResourceEdit(); // One Ctrl+Z entry for the complete drag.' in ui
print('Stage 5.145 property and canvas source checks PASSED')
