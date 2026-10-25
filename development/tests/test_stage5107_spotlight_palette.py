#!/usr/bin/env python3
"""Compiled test: spotlight CLUT slot stays pinned across title/world fade."""
from pathlib import Path
import subprocess, tempfile, re
root=Path(__file__).resolve().parents[2]
sdk=root/'idelibs/codehelpers/game'
# The title must flush both foreground buffers BEFORE the world changes its CLUT.
title=(sdk/'gametitle-runtime.rulec').read_text()
exit_path=title[title.index('    title_release_images();', title.index('uint8_t gametitle_run(')):]
assert exit_path.index('gfx_usebuffer(buffers[0]);') < exit_path.index('gfx_usebuffer(buffers[1]);')
assert exit_path.count('gfx_cls();') >= 2
# The saved per-world controls are present in IDE and registry export.
for file, words in {
    'gamedesigner_project.cpp':['spotlightMaskIndex','spotlightMaskColour'],
    'gamedesigner.cpp':['Reserved mask palette ID','QColorDialog::getColor'],
    'gameworldsnapshot.h':['defaultSpotlightMaskIndex','defaultSpotlightMaskColour'],
}.items():
    s=(root/file).read_text()
    for word in words: assert word in s,(file,word)
flags={'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,
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
with tempfile.TemporaryDirectory(prefix='stage5107-') as tmp:
    d=Path(tmp)
    (d/'apis.h').write_text('''#ifndef API_H
#define API_H
#include <stdint.h>
void music_stop(void);
void mock_palettef(uint32_t*);void mock_paletteb(uint32_t*);
void mock_colour(int);void mock_rect(int,int,int,int);void mock_plot(int,int);
#define gfx_usefpalette(p) mock_palettef(p)
#define gfx_usebpalette(p) mock_paletteb(p)
#define gfx_setcolour(c) mock_colour(c)
#define gfx_rectf(x,y,w,h) mock_rect(x,y,w,h)
#define gfx_plot(x,y) mock_plot(x,y)
#endif
''')
    (d/'gameworlds.h').write_text(render((sdk/'gameworlds.ruleh').read_text()))
    decls='''#include "gameworlds.h"
int init(void);void shutdown(void);uint8_t objs_init(void);void update(uint16_t);
void draw(int32_t,int32_t);void plane(void);
const uint32_t *front(void);const uint32_t *back(void);
'''
    rows='''{.name="cave",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.back_palette=back,
.transition_in=1,.transition_frames=4,
.spotlight_enabled=1,.spotlight_radius=60,.spotlight_feather=20,
.spotlight_center=0,.spotlight_mask_index=221,.spotlight_mask_colour=0xff204060u},
{.name="ordinary",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.back_palette=back,
.transition_in=1,.transition_frames=4,
.spotlight_enabled=0,.spotlight_radius=60,.spotlight_mask_index=220,.spotlight_mask_colour=0xff102030u},
{.name="other",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.back_palette=back,
.transition_in=1,.transition_frames=4,
.spotlight_enabled=1,.spotlight_radius=50,.spotlight_feather=0,
.spotlight_mask_index=195,.spotlight_mask_colour=0xff000000u}'''
    c=(sdk/'gameworlds.rulec').read_text().replace('@IDE{WORLD_DECLARATIONS}',decls).replace('@IDE{WORLD_RECORDS}',rows)
    c=render(c)
    assert '@IDE' not in c
    (d/'gameworlds.c').write_text(c)
    (d/'test.c').write_text('''#include "apis.h"
#include "gameworlds.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static uint32_t srcf[256],srcb[256],activef[256],activeb[256];
static int pen,f_copies,rects,plots,loads,unloads;
void music_stop(void){}
void mock_palettef(uint32_t *p){++f_copies;memcpy(activef,p,sizeof(activef));}
void mock_paletteb(uint32_t *p){memcpy(activeb,p,sizeof(activeb));}
void mock_colour(int c){pen=c;}
void mock_rect(int x,int y,int w,int h){assert(w>0&&h>0&&x>=0&&y>=0&&x+w<=480&&y+h<=320);++rects;}
void mock_plot(int x,int y){assert(x>=0&&y>=0&&x<480&&y<320);++plots;}
int init(void){++loads;mock_palettef(srcf);mock_paletteb(srcb);return 1;}
void shutdown(void){++unloads;}
uint8_t objs_init(void){return 1;}
void update(uint16_t n){(void)n;}
void draw(int32_t x,int32_t y){(void)x;(void)y;}
void plane(void){}
const uint32_t *front(void){return srcf;}
const uint32_t *back(void){return srcb;}
int main(void){
 for(int i=0;i<256;++i){srcf[i]=0xffcc4433u;srcb[i]=0xff667788u;}
 srcf[0]=0;srcf[221]=0xffaa2211u;srcf[195]=0xffeecc44u;
 assert(gameworlds_start("cave"));
 assert(activef[221]==0xff204060u); /* the title's red mask is removed before first frame */
 assert(srcf[221]==0xffaa2211u);   /* author's original palette never changed */
 assert(activef[195]==0xffeecc44u);
 gameworlds_transitions_enable(1);
 for(int i=0;i<4;++i){
    gameworlds_spotlight_camera(0,0);gameworlds_spotlight_player(240,160);
    gameworlds_spotlight_frame(480,320);
    assert(pen==221&&rects>0);
    assert(activef[221]==0xff204060u);
    gameworlds_transition_frame(480,320);
    assert(activef[221]==0xff204060u); /* Fade IN must not recolour the mask red */
 }
 assert(!gameworlds_transition_busy());assert(activef[221]==0xff204060u);
 assert(srcf[221]==0xffaa2211u);
 /* A world without spotlight MUST restore its own palette faithfully. */
 assert(gameworlds_start("ordinary"));
 assert(activef[221]==0xffaa2211u);
 assert(activef[195]==0xffeecc44u);
 assert(gameworlds_start("other"));
 assert(activef[195]==0xff000000u);
 assert(activef[221]==0xffaa2211u);
 gameworlds_spotlight_camera(0,0);gameworlds_spotlight_player(240,160);
 gameworlds_spotlight_frame(480,320);assert(pen==195);
 gameworlds_shutdown();assert(unloads==3);
 puts("PASS Stage 5.107: mask index/colour stays fixed across title handoff, fade, world switches; source palettes unchanged");
 return 0;
}
''')
    cc=subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(d),str(d/'gameworlds.c'),str(d/'test.c'),'-o',str(d/'test')],capture_output=True,text=True)
    assert cc.returncode==0,cc.stderr
    done=subprocess.run([str(d/'test')],capture_output=True,text=True)
    assert done.returncode==0,done.stderr
    print(done.stdout.strip())
