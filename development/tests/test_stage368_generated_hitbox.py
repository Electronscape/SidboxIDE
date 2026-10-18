"""Check C code emitted by Game Designer for opt-in physics hitbox setup."""
from pathlib import Path
import re, subprocess, tempfile
src=(Path(__file__).resolve().parents[2]/'gamedesigner_export.cpp').read_text()
assert 'const bool hasPlayerAnimation = hasPhysics && !player->animationFile.isEmpty();' in src
block=re.search(r'out << R"CG\(\n(#if GAMERGIRL_PLAYER_ANIMATIONS\n    /\* Stage 3\.68:.*?\n#endif\n)\)CG";',src,re.S)
assert block, 'Stage 3.68 generated C block missing'
block=block.group(1)
assert 'PLAYER_ANIM_HITBOX_X' in block
editor=(Path(__file__).resolve().parents[2]/'gameanimationeditor.cpp').read_text()
for s in ('_HITBOX_X','_HITBOX_Y','_HITBOX_W','_HITBOX_H'):
    assert s in editor, s
assert 'm_boxX->value() + m_boxW->value() > m_cellW' in editor
assert 'm_boxY->value() + m_boxH->value() > m_cellH' in editor
with tempfile.TemporaryDirectory() as d:
    d=Path(d)
    for enabled in (0,1):
        code='''#include <stdint.h>
#define GAMERGIRL_PLAYER_ANIMATIONS %d
#define PLAYER_ANIM_HITBOX_X 16
#define PLAYER_ANIM_HITBOX_Y 12
#define PLAYER_ANIM_HITBOX_W 32
#define PLAYER_ANIM_HITBOX_H 52
static int called=0;
typedef struct { int h; } test_player;
static test_player player_physics={64};
static int game_tile_player_set_hitbox(test_player *p, int x,int y,int w,int h)
{ ++called; return p->h==64 && x==16 && y==12 && w==32 && h==52; }
int main(void) {
 int result=0;
''' % enabled
        code+=block
        code+='''if (called!=GAMERGIRL_PLAYER_ANIMATIONS) return 1;
(void)player_physics; if (0) goto cleanup;
cleanup: return result;
}'''
        fn=d/f'check{enabled}.c'; fn.write_text(code)
        subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-Wno-unused-function',str(fn),'-o',str(d/f'check{enabled}')],check=True)
        subprocess.run([str(d/f'check{enabled}')],check=True)
print('PASS: generated player hitbox setup C99 compiles ON/OFF and preserves fallback.')
