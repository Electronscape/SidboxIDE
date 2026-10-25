#!/usr/bin/env python3
"""Native runtime test: spotlight anchor/offset, world switching, opaque mask."""
from pathlib import Path
import re, tempfile, subprocess
root=Path(__file__).resolve().parents[2]
sdk=root/'idelibs/codehelpers/game'
flags={'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':True,
       'HAS_ADVENTURE_RUNTIME':False,'HAS_PLAYER_VISIBILITY':False}
def render(src):
    lines=[];stack=[True]
    for line in src.splitlines(keepends=True):
        m=re.fullmatch(r'@IDE_IF\{([A-Z_]+)\}\n?',line)
        if m:
            assert m.group(1) in flags,m.group(1)
            stack.append(stack[-1] and flags[m.group(1)])
        elif line.strip()=='@IDE_ELSE':stack[-1]=stack[-2] and not stack[-1]
        elif line.strip()=='@IDE_END':stack.pop()
        elif stack[-1]:lines.append(line)
    assert len(stack)==1
    return ''.join(lines)
with tempfile.TemporaryDirectory(prefix='stage5106-') as tmp:
    d=Path(tmp)
    (d/'apis.h').write_text('''#ifndef API_H
#define API_H
#include <stdint.h>
void music_stop(void);
void mock_palette(uint32_t*);void mock_colour(int);void mock_rect(int,int,int,int);void mock_plot(int,int);
#define gfx_usefpalette(p) mock_palette(p)
#define gfx_setcolour(c) mock_colour(c)
#define gfx_rectf(x,y,w,h) mock_rect(x,y,w,h)
#define gfx_plot(x,y) mock_plot(x,y)
#endif
''')
    (d/'gametilemap.h').write_text('''#ifndef TILE_H
#define TILE_H
typedef struct { int dummy; } game_tile_player_t;
#endif
''')
    (d/'gameplayer.h').write_text('''#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include "gametilemap.h"
typedef struct { uint16_t width,height,scale; } gfxbob_t;
extern gfxbob_t gameplayer_sprite;
uint8_t gameplayer_apply_physics(game_tile_player_t *,uint8_t);
uint8_t gameplayer_stat_get(const char*,int32_t*);
uint8_t gameplayer_stat_set(const char*,int32_t);
#endif
''')
    (d/'gameworlds.h').write_text(render((sdk/'gameworlds.ruleh').read_text()))
    decls='''#include "gameworlds.h"
int init(void);void shutdown(void);uint8_t objs_init(void);void update(uint16_t);
void draw(int32_t,int32_t);void plane(void);const uint32_t *front(void);
'''
    rows='''{.name="forest",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=12,.spotlight_feather=4,.spotlight_center=1,.spotlight_offset_x=10,.spotlight_offset_y=-5},
{.name="cellar",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=12,.spotlight_feather=0,.spotlight_center=0,.spotlight_offset_x=-15,.spotlight_offset_y=10},
{.name="daylight",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front}'''
    c=(sdk/'gameworlds.rulec').read_text().replace('@IDE{WORLD_DECLARATIONS}',decls).replace('@IDE{WORLD_RECORDS}',rows)
    c=render(c)
    assert '@IDE' not in c
    (d/'gameworlds.c').write_text(c)
    (d/'test.c').write_text('''#include "apis.h"
#include "gameworlds.h"
#include "gameplayer.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
uint32_t pal[256]; gfxbob_t gameplayer_sprite={32,48,150};
static uint8_t mask[320][480];static int colour, drawn;
void music_stop(void){}
void mock_palette(uint32_t*p){assert(p);}
void mock_colour(int c){colour=c;}
void mock_rect(int x,int y,int w,int h){
 assert(colour==255&&x>=0&&y>=0&&x+w<=480&&y+h<=320&&w>0&&h>0);
 drawn+=w*h;
 for(int a=y;a<y+h;a++)for(int b=x;b<x+w;b++)mask[a][b]=1;
}
void mock_plot(int x,int y){assert(colour==255&&x>=0&&x<480&&y>=0&&y<320);mask[y][x]=1;}
uint8_t gameplayer_apply_physics(game_tile_player_t*p,uint8_t id){(void)p;(void)id;return 1;}
uint8_t gameplayer_stat_get(const char*n,int32_t*v){(void)n;(void)v;return 0;}
uint8_t gameplayer_stat_set(const char*n,int32_t v){(void)n;(void)v;return 0;}
int init(void){return 1;}void shutdown(void){}
uint8_t objs_init(void){return 1;}void update(uint16_t f){(void)f;}
void draw(int32_t x,int32_t y){(void)x;(void)y;}void plane(void){}
const uint32_t *front(void){return pal;}
static void frame(void){memset(mask,0,sizeof(mask));drawn=0;
 gameworlds_spotlight_camera(35,45); gameworlds_spotlight_player(100,100);
 gameworlds_spotlight_frame(480,320);}
int main(void){
 for(int i=0;i<256;i++)pal[i]=0xffaabbccu;
 assert(gameworlds_start("forest"));
 // 32x48 BOB scaled to 150%: visible centre offset (+24,+36).
 // World light = (100+24+10,100+36-5) = (134,131).
 // Camera (35,45) -> (99,86) aperture.
 frame();assert(drawn>100000);
 assert(mask[86][99]==0);
 assert(mask[70][99]==1 && mask[86][130]==1);
 assert(mask[55][70]==1);
 // Switch to origin anchored with different signed offsets.
 assert(gameworlds_start("cellar"));
 // World light = (85,110); screen centre = (50,65).
 frame();assert(mask[65][50]==0 && mask[86][99]==1);
 assert(gameworlds_start("daylight"));
 frame();assert(drawn==0);
 gameworlds_shutdown();puts("PASS Stage 5.106: scaled BOB centre, X/Y offsets, world switch, disabled safety");return 0;
}
''')
    cc=subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-O2','-I',str(d),str(d/'gameworlds.c'),str(d/'test.c'),'-o',str(d/'test')],capture_output=True,text=True)
    if cc.returncode: print(cc.stderr)
    assert cc.returncode==0,cc.stderr
    done=subprocess.run([str(d/'test')],capture_output=True,text=True)
    if done.returncode: print(done.stdout,done.stderr)
    assert done.returncode==0,done.stderr
    print(done.stdout.strip())
# Source-level checks across save, load, editor, generator and unmodified old callers.
project=(root/'gamedesigner_project.cpp').read_text()
assert 'spotlightCenter' in project and 'spotlightOffsetX' in project and 'spotlightOffsetY' in project
assert 'spotlightCenter' in (root/'gameworldsnapshot.h').read_text()
assert 'spotlightAnchor->currentData().toBool()' in (root/'gamedesigner.cpp').read_text()
assert 'gameworlds_spotlight_player(player_physics.x100 / 100, player_physics.y100 / 100);' in (sdk/'maingame.rulec').read_text()
print('PASS Stage 5.106 source configuration and generated caller contract')
