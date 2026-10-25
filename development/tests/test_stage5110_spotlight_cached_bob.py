#!/usr/bin/env python3
"""Stage 5.110 native test: cached feather BOB, flipped offsets, opacity, world restore."""
from pathlib import Path
import re, subprocess, tempfile
root=Path(__file__).resolve().parents[2]
sdk=root/'idelibs/codehelpers/game'
flags={'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':True,
       'HAS_ADVENTURE_RUNTIME':False,'HAS_PLAYER_VISIBILITY':False}
def render(src):
    lines=[]; stack=[True]
    for line in src.splitlines(keepends=True):
        m=re.fullmatch(r'@IDE_IF\{([A-Z_]+)\}\n?',line)
        if m:
            assert m.group(1) in flags,m.group(1)
            stack.append(stack[-1] and flags[m.group(1)])
        elif line.strip()=='@IDE_ELSE': stack[-1]=stack[-2] and not stack[-1]
        elif line.strip()=='@IDE_END': stack.pop()
        elif stack[-1]: lines.append(line)
    assert len(stack)==1
    return ''.join(lines)
with tempfile.TemporaryDirectory(prefix='stage5110-') as tmp:
    d=Path(tmp)
    (d/'apis.h').write_text('''#ifndef APIS_H
#define APIS_H
#include <stdint.h>
#define BLIT_FLAG_FLIP_X 0x04
#define BLIT_FLAG_FLIP_Y 0x08
#define BLIT_HANDLE_TOP_LEFT 0
#define gfx_usefpalette(p) mock_palette(p)
#define gfx_rectf(x,y,w,h) mock_rect(x,y,w,h)
#define gfx_plot(x,y) mock_plot(x,y)
#define gfx_setcolour(c) mock_colour(c)
#define gfx_drawbob(b) mock_bob(b)
typedef struct {const uint8_t *imgdat; uint8_t flags,flagval[7]; uint16_t atlas_stride,atlas_height,width,height; int16_t drawx,drawy;uint16_t scale;uint8_t handle,index;uint8_t pad[4];} gfxbob_t;
void mock_palette(uint32_t*);void mock_colour(int);void mock_rect(int,int,int,int);
void mock_plot(int,int);void mock_bob(gfxbob_t*);void music_stop(void);
#endif
''')
    (d/'gametilemap.h').write_text('#ifndef TILE_H\n#define TILE_H\ntypedef struct {int dummy;} game_tile_player_t;\n#endif\n')
    (d/'gameplayer.h').write_text('''#ifndef PLAYER_H
#define PLAYER_H
#include "apis.h"
#include "gametilemap.h"
extern gfxbob_t gameplayer_sprite;
uint8_t gameplayer_apply_physics(game_tile_player_t*,uint8_t);
uint8_t gameplayer_stat_get(const char*,int32_t*);
uint8_t gameplayer_stat_set(const char*,int32_t);
#endif
''')
    (d/'gameworlds.h').write_text(render((sdk/'gameworlds.ruleh').read_text()))
    decls='''#include "gameworlds.h"
int init(void);void shutdown(void);uint8_t objs_init(void);void update(uint16_t);
void draw(int32_t,int32_t);void plane(void);const uint32_t *front(void);
'''
    rows='''{.name="cave",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=15,.spotlight_feather=8,.spotlight_center=1,.spotlight_offset_x=20,
.spotlight_offset_y=10,.spotlight_flip_x=1,.spotlight_flip_y=1,.spotlight_opacity_code=101,
.spotlight_mask_index=211,.spotlight_mask_colour=0xff000000u},
{.name="hazy",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=15,.spotlight_feather=8,.spotlight_center=0,.spotlight_opacity_code=51,
.spotlight_mask_index=211,.spotlight_mask_colour=0xff000000u},
{.name="clear",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=15,.spotlight_feather=8,.spotlight_center=0,.spotlight_opacity_code=1,
.spotlight_mask_index=211,.spotlight_mask_colour=0xff000000u}'''
    c=render((sdk/'gameworlds.rulec').read_text().replace('@IDE{WORLD_DECLARATIONS}',decls).replace('@IDE{WORLD_RECORDS}',rows))
    assert '@IDE' not in c
    (d/'gameworlds.c').write_text(c)
    (d/'test.c').write_text('''#include "apis.h"
#include "gameworlds.h"
#include "gameplayer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static uint32_t pal[256];
gfxbob_t gameplayer_sprite={.width=32,.height=48,.scale=100};
static int lastcx,lastcy,prevx,prevy,bob_calls,rect_calls,plot_calls,dark_pixels;
void music_stop(void){}
void mock_palette(uint32_t *p){assert(p[211]==0xff000000u);}
void mock_colour(int c){assert(c==211);}
void mock_rect(int x,int y,int w,int h){assert(x>=0&&y>=0&&x+w<=480&&y+h<=320&&w>0&&h>0);rect_calls++;dark_pixels+=w*h;}
void mock_plot(int x,int y){assert(x>=0&&y>=0&&x<480&&y<320);plot_calls++;}
void mock_bob(gfxbob_t *b){assert(b&&b->imgdat&&b->width==47&&b->height==47&&b->handle==0&&b->scale==100);
 ++bob_calls; prevx=lastcx;prevy=lastcy;lastcx=b->drawx+23;lastcy=b->drawy+23;
 int coloured=0,transparent=0;
 for(int i=0;i<47*47;i++){assert(b->imgdat[i]==0||b->imgdat[i]==211);if(b->imgdat[i])coloured++;else transparent++;}
 assert(transparent>0&&coloured>0);}
uint8_t gameplayer_apply_physics(game_tile_player_t*p,uint8_t id){(void)p;(void)id;return 1;}
uint8_t gameplayer_stat_get(const char*n,int32_t*v){(void)n;(void)v;return 0;}
uint8_t gameplayer_stat_set(const char*n,int32_t v){(void)n;(void)v;return 0;}
int init(void){return 1;}void shutdown(void){}uint8_t objs_init(void){return 1;}
void update(uint16_t n){(void)n;}void draw(int32_t x,int32_t y){(void)x;(void)y;}
void plane(void){}const uint32_t*front(void){return pal;}
static void frame(void){rect_calls=0;plot_calls=0;dark_pixels=0;
 gameworlds_spotlight_camera(0,0);gameworlds_spotlight_player(100,100);
 gameworlds_spotlight_frame(480,320);}
int main(void){for(int i=0;i<256;i++)pal[i]=0xff000000;
 assert(gameworlds_start("cave"));frame();assert(bob_calls==1&&lastcx==136&&lastcy==134&&plot_calls==0);assert(dark_pixels>100000);
 gameplayer_sprite.flags=BLIT_FLAG_FLIP_X|BLIT_FLAG_FLIP_Y;frame();assert(bob_calls==2&&lastcx==96&&lastcy==114);
 gameplayer_sprite.flags=0;assert(gameworlds_start("hazy"));frame();assert(bob_calls==3&&lastcx==100&&lastcy==100);
 assert(dark_pixels>0&&dark_pixels<150000);assert(plot_calls==0);
 assert(gameworlds_start("clear"));frame();assert(bob_calls==3&&rect_calls==0&&plot_calls==0);
 gameworlds_shutdown();puts("PASS Stage 5.110: cached ring BOB, flipped offsets, half darkness, zero darkness, world switching");return 0;}
''')
    cc=subprocess.run(['cc','-std=c11','-O2','-Wall','-Wextra','-Werror','-I',str(d),str(d/'gameworlds.c'),str(d/'test.c'),'-o',str(d/'test')],capture_output=True,text=True)
    assert cc.returncode==0,cc.stderr
    run=subprocess.run([str(d/'test')],capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    print(run.stdout.strip())
# Editor persistence/generation/UI contract.
checks={
 'gamedesigner.h':['m_playerSpotlightFlipX','m_playerSpotlightFlipY','m_playerSpotlightOpacity'],
 'gamedesigner_project.cpp':['spotlightFlipX','spotlightFlipY','spotlightOpacity'],
 'gameworldsnapshot.h':['defaultSpotlightFlipX','defaultSpotlightFlipY','defaultSpotlightOpacity'],
 'gamedesigner.cpp':['Mirror X offset','Mirror Y offset','Outside darkness opacity','dialog.showMaximized()'],
 'codeeditor.cpp':['setInterval(400)'],
}
for file, tokens in checks.items():
    data=(root/file).read_text()
    for tok in tokens:assert tok in data,(file,tok)
print('PASS Stage 5.110: editor settings and persistence contract')
