#!/usr/bin/env python3
"""Stage 5.102: execute actual generated fade C, test editor serialization/connection."""
from pathlib import Path
import tempfile, subprocess, sys
root=Path(__file__).resolve().parents[2]
code=(root/'idelibs/codehelpers/game/gameassets.rulec').read_text()
start=code.index('typedef struct {\n    gfxbob_t *bob;\n    uint8_t low, high, step, pingpong;')
end=code.index('@IDE_ELSE',start)
runtime=code[start:end].replace('@IDE{FADE_ANIM_ROWS}', '''    { &ghost, 20u, 80u, 7u, 1u, 2u, 0u, 0u },
    { &lamp, 0u, 100u, 25u, 0u, 1u, 0u, 0u },
    { &still, 10u, 10u, 5u, 1u, 1u, 0u, 0u },
''')
source=r'''#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BLIT_FLAG_ALPHABLEND 0x02u
#define BLIT_FLAG_TYPE_FADE_VALUE 0u
#define BLIT_FLAG_FLIP_X 0x04u
typedef struct { uint8_t flags; uint8_t flagval[4]; } gfxbob_t;
static gfxbob_t ghost = {BLIT_FLAG_FLIP_X, {0}}, lamp={0,{0}}, still={0,{0}};
''' + runtime + r'''
#define CHECK(pred) do { if (!(pred)) { fprintf(stderr, "FAIL line %d: %s\n",__LINE__,#pred); exit(1); } } while (0)
static unsigned val(gfxbob_t *b) { return b->flagval[BLIT_FLAG_TYPE_FADE_VALUE]; }
int main(void) {
    cg_bob_fade_reset();
    CHECK(val(&ghost) == 20 && val(&lamp) == 0 && val(&still) == 10);
    CHECK((ghost.flags & BLIT_FLAG_FLIP_X) && (ghost.flags & BLIT_FLAG_ALPHABLEND));
    CHECK((lamp.flags & BLIT_FLAG_ALPHABLEND) == 0);
    gameassets_fade_update(0);
    CHECK(val(&ghost) == 20);
    gameassets_fade_update(1); CHECK(val(&ghost)==20 && val(&lamp)==25);
    gameassets_fade_update(1); CHECK(val(&ghost)==27 && val(&lamp)==50);
    gameassets_fade_update(2); CHECK(val(&ghost)==34 && val(&lamp)==100);
    gameassets_fade_update(1); CHECK(val(&lamp)==0);  /* wrapping, no pingpong */
    gameassets_fade_update(13); CHECK(val(&ghost)==80); /* ninth step endpoint */
    gameassets_fade_update(2); CHECK(val(&ghost)==76); /* reverse, no double dwell */
    CHECK(ghost.flags & BLIT_FLAG_FLIP_X);
    CHECK(val(&still)==10);
    gameassets_fade_update(1000); CHECK(val(&ghost) <= 80 && val(&ghost) >= 20);
    gameassets_fade_update(65535); CHECK(val(&ghost) <= 80 && val(&ghost) >= 20);
    cg_bob_fade_reset(); CHECK(val(&ghost)==20 && val(&lamp)==0);
    puts("Stage 5.102 C animation: PASS");
    return 0;
}
'''
with tempfile.TemporaryDirectory() as tmp:
    t=Path(tmp); (t/'test.c').write_text(source)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-pedantic',str(t/'test.c'),'-o',str(t/'test')],check=True)
    subprocess.run([str(t/'test')],check=True)

def check(rel,*tokens):
    s=(root/rel).read_text()
    for x in tokens:
        assert x in s, (rel,x)

check('gamedesigner.h','objectFadeAnimated','objectFadeLow','objectFadeHigh','objectFadeStep','objectFadeDelay','objectFadePingpong')
check('gamedesigner_project.cpp','objectFadeAnimated','objectFadeLow','objectFadeHigh','objectFadeStep','objectFadeDelay','objectFadePingpong')
check('gamedesigner_export.cpp','a.fadeAnimated','a.fadeLow','a.fadeHigh','a.fadeStep','a.fadeDelay','a.fadePingpong')
check('gamedesigner.cpp','Animate patterned fade','Frames per fade step','bobAnimatedFade(','fadePreviewTimer','previewFadeOnCanvas','m_objectPreviewTimer->stop()')
check('gamecodegen.h','bool fadeAnimated = false','fadeStep = 5')
check('gamecodegen.cpp','FADE_ANIM_ROWS','HAS_FADE_ANIM','fadeAnimated','fadePingpong')
check('idelibs/codehelpers/game/gameworlditems.rulec','gameassets_fade_update(frames);','../gameassets/gameassets.h')
check('idelibs/codehelpers/game/gameassets.ruleh','void gameassets_fade_update(uint16_t frames);')
check('splashscreenwidget.cpp','Build: 5.102.251026')
assert 'objectFadeAnimated' not in (root/'gamecodegen.cpp').read_text(), 'generator must use Asset input, not designer struct'
print('Stage 5.102 generator/editor wiring: PASS')
