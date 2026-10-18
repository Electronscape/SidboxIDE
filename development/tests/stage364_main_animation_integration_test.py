"""Host C test for Stage 3.64's generated animation wiring.

Qt6 C++ generation itself must be compiled on the developer's machine; this
checks the emitted C statements and two switch configurations with strict C99.
"""
import re
import subprocess
import tempfile
from pathlib import Path

src = (Path(__file__).resolve().parents[2] / 'gamedesigner_export.cpp').read_text()
assert 'const bool hasPlayerAnimation = hasPhysics && !player->animationFile.isEmpty();' in src
assert 'static player_anim_playeranim_t player_anim = {0};' in src
assert 'player_anim_step(&player_anim, &' in src
assert 'game_tile_player_run(&player_physics, player_buttons, 1);' in src

# Use the real raw-C block in the generator, not a rewritten equivalent.
top = src.split('/* PLAYER ANIMATION -- ONE-SWITCH SETUP (Stage 3.64)', 1)[1]
top = '/* PLAYER ANIMATION -- ONE-SWITCH SETUP (Stage 3.64)' + top.split(')CG";', 1)[0]
loop = src.split('const uint8_t player_buttons = getjoyport();', 1)[1]
loop = 'const uint8_t player_buttons = getjoyport();' + loop.split(')CG";', 1)[0]
loop += 'player_anim_step(&player_anim, &player_bob, player_anim_state, player_anim_facing, 1);\n#endif\n'

with tempfile.TemporaryDirectory(prefix='sidbox364_') as root:
    path = Path(root)
    (path/'gameanimations').mkdir()
    (path/'gameanimations/player_anim.h').write_text('''#ifndef PLAYER_ANIM_H
#define PLAYER_ANIM_H
#include <stdint.h>
enum { PLAYER_ANIM_STATE_IDLE, PLAYER_ANIM_STATE_WALK, PLAYER_ANIM_STATE_RUN,
       PLAYER_ANIM_STATE_PUSH, PLAYER_ANIM_STATE_JUMP, PLAYER_ANIM_STATE_FALL };
enum { PLAYER_ANIM_DIR_RIGHT, PLAYER_ANIM_DIR_LEFT };
typedef struct { uint8_t state, direction; } player_anim_playeranim_t;
static inline void player_anim_step(player_anim_playeranim_t *a, gfxbob_t *b,
                                    uint8_t state, uint8_t dir, uint16_t ticks) {
    (void)ticks; a->state = state; a->direction = dir;
    b->index = (uint8_t)(state * 2 + dir);
}
#endif
''')
    for enabled in (0, 1):
        p = path/f'test{enabled}.c'
        p.write_text('''#include <stdint.h>
#include <assert.h>
#define BTN_LEFT 0x10u
#define BTN_RIGHT 0x20u
typedef struct { uint8_t index; } gfxbob_t;
typedef struct { uint8_t on_ground; int32_t vy100; } game_tile_player_t;
static game_tile_player_t player_physics={1,0};
static gfxbob_t player_bob={0};
static uint8_t buttons;
static uint8_t getjoyport(void) { return buttons; }
static void game_tile_player_run(game_tile_player_t *p, uint8_t joy, uint16_t frames)
{ (void)p; (void)joy; (void)frames; }
'''+re.sub(r'#define GAMERGIRL_PLAYER_ANIMATIONS 0', f'#define GAMERGIRL_PLAYER_ANIMATIONS {enabled}', top, count=1)+'''
static void tick(void) {
'''+loop+'''
}
int main(void) {
 buttons=BTN_RIGHT; player_physics.on_ground=1; tick();
#if GAMERGIRL_PLAYER_ANIMATIONS
 assert(player_anim.state==PLAYER_ANIM_STATE_WALK);
 assert(player_anim.direction==PLAYER_ANIM_DIR_RIGHT);
 buttons=0; tick(); assert(player_anim.state==PLAYER_ANIM_STATE_IDLE);
 buttons=BTN_LEFT; tick(); assert(player_anim.direction==PLAYER_ANIM_DIR_LEFT);
 buttons=0; player_physics.on_ground=0; player_physics.vy100=-30; tick();
 assert(player_anim.state==PLAYER_ANIM_STATE_JUMP);
 player_physics.vy100=30; tick(); assert(player_anim.state==PLAYER_ANIM_STATE_FALL);
 assert(player_anim.direction==PLAYER_ANIM_DIR_LEFT);
#endif
 (void)player_bob;
 return 0;
}
''')
        subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-pedantic',
                        '-Wno-unused-function', '-I',root,str(p),'-o',str(path/f'test{enabled}')],check=True)
        subprocess.run([str(path/f'test{enabled}')],check=True)
print('PASS: generated animation wiring compiles OFF/ON, C99; Idle/Walk/Jump/Fall/facing verified.')
