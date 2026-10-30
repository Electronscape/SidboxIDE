"""Native GCC checks: unchanged player_anim_step() handles optional melee automatically."""
from pathlib import Path
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
source = (ROOT/'idelibs/codehelpers/game/playeranim.ruleh').read_text()
starter = (ROOT/'idelibs/codehelpers/game/maingame.rulec').read_text()
editor = (ROOT/'gameanimationeditor.cpp').read_text()
assert '@IDE{PREFIX}_step_combat' not in source
assert 'player_anim_step_combat' not in starter
assert 'gameplayer_attack_started()' in source
assert 'defined(CODERGIRL_SHARED_PLAYER_H)' in source
assert '#define @IDE{PREFIX_UPPER}_HAS_MELEE_STATE @IDE{HAS_MELEE}' in source
assert 'HAS_MELEE' in editor and 'Qt::CaseInsensitive' in editor
assert 'player_anim_step(&player_anim, &GAMERGIRL_PLAYER_BOB,' in starter

source = re.sub(r'(?ms)^@IDE_SECTION\{.*?^@IDE_SECTION_END\s*', '', source)
source = source.replace('@IDE_IF{AUTO_STATE}', '#if 0').replace('@IDE_END', '#endif')
fields = {
 'PREFIX_UPPER':'PLAYER_ANIM', 'PREFIX':'player_anim',
 'FOOT_X':'0','FOOT_Y':'0','HITBOX_X':'0','HITBOX_Y':'0','HITBOX_W':'8','HITBOX_H':'8',
 'STATE_ENUMS':'''    PLAYER_ANIM_STATE_IDLE=0,\n    PLAYER_ANIM_STATE_HURT=1,\n    PLAYER_ANIM_STATE_MELEE=2,\n''',
 'DIRECTION_ENUMS':'    PLAYER_ANIM_DIR_RIGHT=0,\n    PLAYER_ANIM_DIR_LEFT=1,\n',
 'STATE_COUNT':'3','DIRECTION_COUNT':'2','HAS_HURT':'1','HAS_MELEE':'1',
 'CLIP_ARRAYS':'''static const uint8_t frames_idle[] = {0};
static const uint8_t frames_hurt[] = {9};
static const uint8_t frames_melee[] = {3,4,5};
static const uint8_t melee_ticks[] = {2,3,4};
''',
 'CLIP_COUNT':'6',
 'CLIP_ROWS':'''    {frames_idle,0,1u,4u,1,0},
    {frames_idle,0,1u,4u,1,1},
    {frames_hurt,0,1u,4u,1,0},
    {frames_hurt,0,1u,4u,1,1},
    {frames_melee,melee_ticks,3u,2u,0,0},
    {frames_melee,melee_ticks,3u,2u,0,1},
''', 'IDLE_ID':'0',
}
for key, value in fields.items(): source = source.replace('@IDE{'+key+'}',value)
source = re.sub(r'@IDE\{[A-Z_]+\}', '0', source)
assert '@IDE' not in source, re.findall(r'@IDE\S+',source)

apis='''#pragma once
#include <stdint.h>
#define BLIT_FLAG_FLIP_X 1
#define BLIT_FLAG_FLIP_Y 2
typedef struct { uint8_t *imgdat; uint8_t index; uint8_t flags; } gfxbob_t;
'''

def build_and_run(header, program):
    with tempfile.TemporaryDirectory() as d:
        p=Path(d)
        (p/'apis.h').write_text(apis)
        (p/'player_anim.h').write_text(header)
        (p/'main.c').write_text(program)
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-Werror=implicit-function-declaration','-I',str(p),str(p/'main.c'),'-o',str(p/'test')],check=True)
        subprocess.run([str(p/'test')],check=True)

# Shared Player Profile present, and gameplayer.h has been included BEFORE player_anim.h.
program='''#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#define CODERGIRL_SHARED_PLAYER_H
static uint8_t enabled=1, pulse=0;
static uint8_t gameplayer_combat_enabled(void) { return enabled; }
static uint8_t gameplayer_attack_started(void) { return pulse; }
#include "player_anim.h"
static void step(player_anim_playeranim_t *a, gfxbob_t *b, uint8_t state, uint8_t dir) {
    player_anim_step(a,b,state,dir,1);
    pulse=0;
}
int main(void) {
    uint8_t pixels[64]={0};
    gfxbob_t bob={0}; bob.imgdat=pixels;
    player_anim_playeranim_t a={0};
    // Ordinary gameplay call, no step_combat symbol or extra parameters.
    pulse=1; step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0);
    assert(a.state==PLAYER_ANIM_STATE_MELEE && bob.index==3 && a.melee_ticks_left==8);
    step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0); assert(bob.index==3);
    step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0); assert(bob.index==4);
    for(int i=0;i<6;i++)step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0);
    assert(bob.index==5 && a.melee_ticks_left==0);
    step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0);
    assert(a.state==PLAYER_ANIM_STATE_IDLE && bob.index==0);
    pulse=1; step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0);
    step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0);
    pulse=1; step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0);
    assert(bob.index==3 && a.melee_ticks_left==8);
    step(&a,&bob,PLAYER_ANIM_STATE_HURT,0);
    assert(a.melee_ticks_left==0 && a.state==PLAYER_ANIM_STATE_HURT && bob.index==9);
    enabled=0; pulse=1; step(&a,&bob,PLAYER_ANIM_STATE_IDLE,0);
    assert(a.melee_ticks_left==0 && a.state==PLAYER_ANIM_STATE_IDLE);
    enabled=1; pulse=1; step(&a,&bob,PLAYER_ANIM_STATE_IDLE,1);
    assert(a.state==PLAYER_ANIM_STATE_MELEE && (bob.flags & BLIT_FLAG_FLIP_X));
    player_anim_step(&a,&bob,PLAYER_ANIM_STATE_IDLE,1,0); // world entry reset
    assert(!a.melee_ticks_left);
    pulse=0; step(&a,&bob,PLAYER_ANIM_STATE_IDLE,1);
    assert(a.state==PLAYER_ANIM_STATE_IDLE);
    puts("Stage127.1 unchanged animation API: PASS");
    return 0;
}
'''
build_and_run(source,program)

# No shared Player Profile: no gameplayer dependency, normal animation still works.
build_and_run(source, '''#include "player_anim.h"
int main(void) {
    uint8_t px[8]={0}; gfxbob_t b={0}; b.imgdat=px;
    player_anim_playeranim_t a={0};
    player_anim_step(&a,&b,PLAYER_ANIM_STATE_IDLE,0,1);
    return a.state!=PLAYER_ANIM_STATE_IDLE || a.melee_ticks_left!=0;
}
''')

# No Melee state: generated header must not mention missing enum during C compilation.
no_melee=source.replace('#define PLAYER_ANIM_HAS_MELEE_STATE 1','#define PLAYER_ANIM_HAS_MELEE_STATE 0')
no_melee=no_melee.replace('    PLAYER_ANIM_STATE_MELEE=2,\n','')
build_and_run(no_melee,'''#include <stdint.h>
#define CODERGIRL_SHARED_PLAYER_H
uint8_t gameplayer_combat_enabled(void);
uint8_t gameplayer_attack_started(void);
#include "player_anim.h"
int main(void) {
    uint8_t px[8]={0}; gfxbob_t b={0}; b.imgdat=px;
    player_anim_playeranim_t a={0};
    player_anim_step(&a,&b,PLAYER_ANIM_STATE_IDLE,0,1);
    return a.state!=PLAYER_ANIM_STATE_IDLE || a.melee_ticks_left!=0;
}
''')
print('Stage127.1 source and native tests: PASS')

def test_stage127_1_native_and_source_contract():
    assert 'gameplayer_attack_started()' in source
