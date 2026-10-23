#!/usr/bin/env python3
"""Stage 5.48 compiled transition regression: target entrance, exit origin, camera."""
from pathlib import Path
import tempfile, subprocess, re
root=Path(__file__).resolve().parents[2]
sdk=root/'idelibs/codehelpers/game'
flags={'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,
       'HAS_ADVENTURE_RUNTIME':False,'HAS_PLAYER_VISIBILITY':False}
def render(src):
    lines=[];stack=[True]
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
with tempfile.TemporaryDirectory(prefix='stage548-') as tmp:
    d=Path(tmp)
    (d/'apis.h').write_text('''#ifndef API_H
#define API_H
#include <stdint.h>
void music_stop(void);
void mock_palettef(uint32_t*);void mock_paletteb(uint32_t*);
void mock_colour(int);void mock_rect(int,int,int,int);
#define gfx_usefpalette(p) mock_palettef(p)
#define gfx_usebpalette(p) mock_paletteb(p)
#define gfx_setcolour(c) mock_colour(c)
#define gfx_rectf(x,y,w,h) mock_rect(x,y,w,h)
#endif
''')
    (d/'gameworlds.h').write_text(render((sdk/'gameworlds.ruleh').read_text()))
    decls='''#include "gameworlds.h"
extern uint32_t palette_f[256],palette_b[256];
int init(void);void shutdown(void);uint8_t objs_init(void);void update(uint16_t);
void draw(int32_t,int32_t);void plane(void);
const uint32_t *front(void);const uint32_t *back(void);
static const gameworlds_named_spawn_t forest_starts[] = {
 {"door",100,200,1,6,6,5,1}, /* circular IN/OUT, centre on location */
 {"other",300,220,0,2,3,4,0} /* swipe IN and OUT, centred */
};
'''
    rows='''{.name="world1",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.back_palette=back,
.transition_in=1,.transition_out=1,.transition_frames=4,.circle_origin=0},
{.name="forest",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objs_init,
.objects_update=update,.objects_draw=draw,.assets_foreground=plane,.assets_background=plane,
.assets_show_background=plane,.front_palette=front,.back_palette=back,
.named_spawns=forest_starts,.named_spawn_count=2,
.transition_in=6,.transition_out=2,.transition_frames=4,.circle_origin=0}'''
    s=(sdk/'gameworlds.rulec').read_text().replace('@IDE{WORLD_DECLARATIONS}',decls).replace('@IDE{WORLD_RECORDS}',rows)
    s=render(s)
    assert '@IDE' not in s
    (d/'gameworlds.c').write_text(s)
    (d/'test.c').write_text('''#include "apis.h"
#include "gameworlds.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
uint32_t palette_f[256],palette_b[256];
static unsigned char mask[320][480];
static int loads, unloads, colour, rects, f_calls, b_calls;
void music_stop(void){}
void mock_palettef(uint32_t*p){++f_calls;assert(p);}
void mock_paletteb(uint32_t*p){++b_calls;assert(p);}
void mock_colour(int c){colour=c;}
void mock_rect(int x,int y,int w,int h){
 assert(colour==255);assert(x>=0 && y>=0 && w>0 && h>0);
 assert(x+w<=480 && y+h<=320);++rects;
 for(int yy=y;yy<y+h;++yy)for(int xx=x;xx<x+w;++xx)mask[yy][xx]=1;
}
int init(void){++loads;return 1;}
void shutdown(void){++unloads;}
uint8_t objs_init(void){return 1;}
void update(uint16_t n){(void)n;}
void draw(int32_t x,int32_t y){(void)x;(void)y;}
void plane(void){}
const uint32_t *front(void){return palette_f;}
const uint32_t *back(void){return palette_b;}
static void tick(int cx,int cy){memset(mask,0,sizeof(mask));gameworlds_transition_camera(cx,cy);gameworlds_transition_frame(480,320);}
static void frames(int n,int cx,int cy){for(int i=0;i<n;++i)tick(cx,cy);}
int main(void){
 for(int i=0;i<256;++i){palette_f[i]=0xff80a0c0u;palette_b[i]=0xff224466u;}
 palette_f[0]=0x00000000u;
 assert(gameworlds_start("world1"));assert(loads==1);
 gameworlds_transitions_enable(1);
 assert(gameworlds_transition_busy());frames(4,0,0);assert(!gameworlds_transition_busy());
 /* World1 arrived via FADE. Forest/door owns OUT=CIRCLE, so it MUST be circle
    here, not the previous World's default fade. Its OUT centre is the door. */
 assert(gameworlds_request_at_from("forest","door",55,66));
 assert(gameworlds_apply_pending());assert(gameworlds_transition_busy());
 int oldb=b_calls;frames(3,0,0);tick(0,0);
 assert(!mask[66][55]);assert(mask[160][240]); /* Door centre, not screen centre */
 assert(b_calls==oldb); /* Circle mask rather than old world fade CLUT */
 tick(0,0);assert(gameworlds_transition_busy());
 assert(gameworlds_apply_pending());assert(!strcmp(gameworlds_active(),"forest"));
 gameworlds_spawn_t spawn={0};assert(gameworlds_player_start(&spawn));
 assert(spawn.x==100 && spawn.y==200 && spawn.facing==1);
 /* Arrival IN centre is new Player Start, corrected for camera scroll. */
 tick(20,30);assert(!mask[170][80]);assert(mask[160][240]);
 frames(4,20,30);assert(!gameworlds_transition_busy());
 /* Next door targets World1 default: destination OUT=FADE, IN=FADE. */
 assert(gameworlds_request_at_from("world1","default",60,70));
 assert(gameworlds_apply_pending());oldb=b_calls;frames(4,0,0);
 assert(b_calls>oldb);assert(gameworlds_apply_pending());
 assert(!strcmp(gameworlds_active(),"world1"));frames(4,0,0);
 /* Repeat passage: should again honour the selected destination start. */
 assert(gameworlds_request_at_from("forest","other",80,88));
 assert(gameworlds_apply_pending());oldb=b_calls;rects=0;frames(4,0,0);
 assert(rects>0 && b_calls==oldb);assert(gameworlds_apply_pending());
 assert(!strcmp(gameworlds_active(),"forest"));frames(4,0,0);
 assert(loads==4 && unloads==3);
 gameworlds_shutdown();assert(unloads==4);
 puts("PASS Stage 5.48: destination transition modes, repeat trips, centred doorway circle, scroll-aware arrival circle");
 return 0;
}
''')
    cc=subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-I',str(d),str(d/'gameworlds.c'),str(d/'test.c'),'-o',str(d/'test')],capture_output=True,text=True)
    assert cc.returncode==0,cc.stderr
    done=subprocess.run([str(d/'test')],capture_output=True,text=True)
    assert done.returncode==0,done.stderr
    print(done.stdout.strip())
