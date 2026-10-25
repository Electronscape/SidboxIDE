#!/usr/bin/env python3
"""Native GCC test: integer cached animated rings, fixed pattern, pulse and random."""
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
        if m: stack.append(stack[-1] and flags[m.group(1)])
        elif line.strip()=='@IDE_ELSE': stack[-1]=stack[-2] and not stack[-1]
        elif line.strip()=='@IDE_END': stack.pop()
        elif stack[-1]: lines.append(line)
    assert len(stack)==1
    return ''.join(lines)
with tempfile.TemporaryDirectory(prefix='stage5111-') as tmp:
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
typedef struct {const uint8_t *imgdat; uint8_t flags,flagval[7]; uint16_t atlas_stride,atlas_height,width,height;int16_t drawx,drawy;uint16_t scale;uint8_t handle,index;uint8_t pad[4];} gfxbob_t;
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
    rows='''{.name="fixed",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=15,.spotlight_feather=8,.spotlight_center=0,.spotlight_stable_dither=1,
.spotlight_opacity_code=101,.spotlight_mask_index=211,.spotlight_mask_colour=0xff000000u},
{.name="pulse",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=15,.spotlight_feather=8,.spotlight_center=0,.spotlight_stable_dither=1,
.spotlight_opacity_code=101,.spotlight_mask_index=211,.spotlight_mask_colour=0xff000000u,
.spotlight_anim_mode=2,.spotlight_anim_min=4,.spotlight_anim_max=12,.spotlight_pulse_delay=2},
{.name="random",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=15,.spotlight_feather=8,.spotlight_center=0,.spotlight_stable_dither=1,
.spotlight_opacity_code=101,.spotlight_mask_index=211,.spotlight_mask_colour=0xff000000u,
.spotlight_anim_mode=1,.spotlight_anim_min=2,.spotlight_anim_max=9,
.spotlight_random_min_frames=3,.spotlight_random_max_frames=7},
{.name="huge",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.spotlight_enabled=1,
.spotlight_radius=240,.spotlight_feather=96,.spotlight_center=0,.spotlight_stable_dither=1,
.spotlight_opacity_code=101,.spotlight_mask_index=211,.spotlight_mask_colour=0xff000000u,
.spotlight_anim_mode=2,.spotlight_anim_min=80,.spotlight_anim_max=96,.spotlight_pulse_delay=1}'''
    generated=render((sdk/'gameworlds.rulec').read_text().replace('@IDE{WORLD_DECLARATIONS}',decls).replace('@IDE{WORLD_RECORDS}',rows))
    assert '@IDE' not in generated
    (d/'gameworlds.c').write_text(generated)
    (d/'test.c').write_text('''#include "apis.h"
#include "gameworlds.h"
#include "gameplayer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static uint32_t pal[256];
gfxbob_t gameplayer_sprite={.width=32,.height=48,.scale=100};
static int bob_calls, plot_calls, last_side, last_cx, last_cy;
static const uint8_t *last_img;
void music_stop(void){}
void mock_palette(uint32_t *p){assert(p[211]==0xff000000u);}
void mock_colour(int c){assert(c==211);}
void mock_rect(int x,int y,int w,int h){assert(x>=0&&y>=0&&x+w<=480&&y+h<=320&&w>0&&h>0);}
void mock_plot(int x,int y){(void)x;(void)y;plot_calls++;}
void mock_bob(gfxbob_t *b){assert(b && b->imgdat && b->handle==0 && b->scale==100);
    ++bob_calls;last_side=b->width;last_cx=b->drawx+b->width/2;last_cy=b->drawy+b->height/2;last_img=b->imgdat;
    assert(b->atlas_stride==b->width && b->atlas_height==b->height && (b->width&1));
    for(int i=0;i<b->width*b->height;i++)assert(b->imgdat[i]==0||b->imgdat[i]==211);
}
uint8_t gameplayer_apply_physics(game_tile_player_t*p,uint8_t id){(void)p;(void)id;return 1;}
uint8_t gameplayer_stat_get(const char*n,int32_t*v){(void)n;(void)v;return 0;}
uint8_t gameplayer_stat_set(const char*n,int32_t v){(void)n;(void)v;return 0;}
int init(void){return 1;}void shutdown(void){}uint8_t objs_init(void){return 1;}
void update(uint16_t n){(void)n;}void draw(int32_t x,int32_t y){(void)x;(void)y;}
void plane(void){}const uint32_t*front(void){return pal;}
static void frame(int x,int y){gameworlds_spotlight_camera(0,0);gameworlds_spotlight_player(x,y);
 gameworlds_spotlight_frame(480,320);}
int main(void){
    for(int i=0;i<256;i++)pal[i]=0xff000000u;
    assert(gameworlds_start("fixed"));frame(101,102);assert(last_side==47&&last_cx==100&&last_cy==104);
    const uint8_t *fixed=last_img;
    frame(102,103);assert(last_cx==104&&last_cy==104&&last_img==fixed);
    frame(102,101);assert(last_cx==104&&last_cy==100&&last_img==fixed);
    assert(plot_calls==0);
    assert(gameworlds_start("pulse"));
    int sizes[80], n=0; const uint8_t *cache[8]={0};
    for(int i=0;i<60;i++) {frame(110,110);sizes[n++]=last_side;
        assert(last_side>=39&&last_side<=55);assert((last_cx&3)==0&&(last_cy&3)==0);
        assert(plot_calls==0);
        if(i==0)assert(last_side==39);
        if(i>0&&sizes[i]!=sizes[i-1])assert(i>=2);
        int known=0;
        for(int j=0;j<8;j++){if(cache[j]==last_img){known=1;break;}if(!cache[j]){cache[j]=last_img;known=1;break;}}
        assert(known);
    }
    int min=999,max=0;for(int i=0;i<n;i++){if(sizes[i]<min)min=sizes[i];if(sizes[i]>max)max=sizes[i];}
    assert(min==39&&max==55);
    assert(gameworlds_start("random"));
    const uint8_t *random_cache[8]={0};int unique=0,changes=0,last=-1,held=0;
    for(int i=0;i<180;i++){frame(101,105);assert(last_side>=35&&last_side<=49);assert(plot_calls==0);
        if(last_side==last){held++;}else{if(last>=0){assert(held>=2&&held<=6);++changes;}held=0;last=last_side;}
        int found=0;for(int j=0;j<unique;j++)if(random_cache[j]==last_img)found=1;
        if(!found){assert(unique<8);random_cache[unique++]=last_img;}
    }
    assert(changes>12 && unique>=3);
    assert(gameworlds_start("huge"));
    frame(240,160);assert(last_side==673);const uint8_t *huge_img=last_img;
    for(int i=0;i<10;i++){frame(240,160);assert(last_side==673&&last_img==huge_img);}
    gameworlds_shutdown();
    printf("PASS Stage 5.111: fixed 4px dither, precomputed 8-frame pulse, random hold timing, no per-frame pixel plotting\\n");
    return 0;
}
''')
    cc=subprocess.run(['cc','-std=c11','-O2','-Wall','-Wextra','-Werror','-I',str(d),str(d/'gameworlds.c'),str(d/'test.c'),'-o',str(d/'test')],capture_output=True,text=True)
    assert cc.returncode==0,cc.stderr
    run=subprocess.run([str(d/'test')],capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    print(run.stdout.strip())
for file, toks in {
    'gamedesigner.h':['m_playerSpotlightStableDither','m_playerSpotlightAnimMode','m_playerSpotlightAnimMin'],
    'gamedesigner_project.cpp':['spotlightStableDither','spotlightAnimMode','spotlightAnimPulseDelay'],
    'gameworldsnapshot.h':['defaultSpotlightStable','defaultSpotlightAnimMode','defaultSpotlightPulseDelay'],
    'gamedesigner.cpp':['Stable 4x4 dither','Random flicker','Pulse (ping-pong)'],
}.items():
    data=(root/file).read_text()
    for tok in toks: assert tok in data,(file,tok)
print('PASS Stage 5.111: persistence, editor and generator wiring')
