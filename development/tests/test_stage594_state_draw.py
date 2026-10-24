#!/usr/bin/env python3
"""Compile and exercise the actual inactive-state renderer from the engine template."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
s=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
a=s.index('static void cg_draw_inactive_state_frames(')
b=s.index('@IDE_END',a)
function=s[a:b].replace('@IDE{WORLD_OBJECT_COUNT}','2u')
code='''#include <assert.h>
#include <stdint.h>
#include <stdio.h>
typedef struct { uint8_t index; int16_t drawx,drawy; uint16_t width,height; } gfxbob_t;
typedef struct { uint8_t active,draw_behind_tiles; gfxbob_t *sprite; int32_t x,y; } game_world_object_t;
static gfxbob_t door={0,0,0,32,48};
static game_world_object_t cg_gwi_platforms[2]={{0,0,&door,100,200},{1,0,0,0,0}};
static const uint16_t cg_inactive_state_frames[]={1u,65535u,UINT16_MAX};
static int drew;
static void gfx_drawbob(gfxbob_t *bob)
{assert(bob->index==1 && bob->drawx==80 && bob->drawy==180); ++drew;}
'''+function+'''
int main(void) {
 cg_draw_inactive_state_frames(20,20,1u); assert(drew==0);
 cg_draw_inactive_state_frames(20,20,0u); assert(drew==1 && door.index==0);
 cg_gwi_platforms[0].active=1u;
 cg_draw_inactive_state_frames(20,20,0u); assert(drew==1);
 cg_gwi_platforms[0].active=0;
 cg_draw_inactive_state_frames(900,20,0u); assert(drew==1);
 puts("Stage 5.94: inactive frame displays without collision/BOB mutation PASS");
 return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage594draw-') as td:
 o=Path(td);(o/'state.c').write_text(code)
 subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',str(o/'state.c'),'-o',str(o/'state')],check=True)
 subprocess.run([str(o/'state')],check=True)
