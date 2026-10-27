#!/usr/bin/env python3
"""Stage 5.166.28: real native renderer validates four boundary-colour strips,
HUD viewport and map/text drawing order, without any Quest Journal colour bars.
"""
from pathlib import Path
import subprocess
import re
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime

source = (ROOT / 'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
begin = source.index('static void ga_world_map_window(void)\n{')
end = source.index('/* A compact, non-modal banner.', begin)
map_ui = source[begin:end]
assert 'ga_quest_style.background_colour' not in map_ui
assert 'gfx_rectf(0,view_top,480,header_h);' in map_ui
assert 'gfx_rectf(0,content_bottom,480,footer_h);' in map_ui
assert 'gfx_rectf(0,content_top,side_w,content_bottom-content_top);' in map_ui
assert 'gfx_rectf(480-side_w,content_top,side_w,content_bottom-content_top);' in map_ui
assert 'gfx_setcolour(ga_map_border_colour);' in map_ui
assert 'const int header_h=24,footer_h=32,side_w=8;' in map_ui
assert 'ga_map_view_height()' not in map_ui or 'const int view_height=ga_map_view_height();' in map_ui
assert (m := re.search(r'Build: 5\.166\.(\d+)\.271026', (ROOT/'splashscreenwidget.cpp').read_text())) and int(m.group(1)) >= 29
with tempfile.TemporaryDirectory(prefix='cg516628_') as td:
    p = Path(td)
    render_adventure_runtime(ROOT, p)
    api = (ROOT / 'development/tests/stage429_mock_api/apis.h').read_text()
    api = api.replace('#define BTN_FIRE2 0x01u', '#define BTN_FIRE2 0x02u')
    api = api.replace('#define BTN_UP 0x02u', '#define BTN_UP 0x04u')
    api = api.replace('#define BTN_DOWN 0x04u', '#define BTN_DOWN 0x08u')
    (p / 'apis.h').write_text(api)
    (p / 'test.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static uint8_t colour;
struct rectangle {int x,y,w,h; uint8_t colour; int order;};
static struct rectangle rects[64];
static unsigned nr, nt, nb;
static int order,first_text,last_bob;
static int map_top,map_height;
static const char *current(void){return "Forest";}
void test_colour(uint8_t c){colour=c;}
void test_rect(int x,int y,int w,int h){
    ++order;
    assert(nr<64);
    rects[nr++]=(struct rectangle){x,y,w,h,colour,order};
    assert(y>=map_top && y+h<=map_top+map_height);
    assert(x>=0 && x+w<=480);
}
void test_text(int x,int y,const char *text){
    ++order;
    ++nt;
    if(!first_text)first_text=order;
    assert(y>=map_top && y<map_top+map_height);
    assert(x>=8 && x<480);
    assert(!strcmp(text,"Forest") || !strcmp(text,"D-PAD PAN    FIRE2 JOURNAL"));
    assert((!strcmp(text,"Forest") && y==map_top+6) ||
           (!strcmp(text,"D-PAD PAN    FIRE2 JOURNAL") && y==map_top+map_height-22));
}
void test_bob(gfxbob_t *bob){
    ++order;
    last_bob=order;
    ++nb;
    assert(bob->imgdat);
    assert(bob->drawy>=map_top && bob->drawy+bob->height<=map_top+map_height);
}
static void require_rect(int x,int y,int w,int h,int after_bob){
    for(unsigned i=0;i<nr;++i){
        const struct rectangle *r=&rects[i];
        if(r->x==x && r->y==y && r->w==w && r->h==h){
            assert(r->colour==37u);
            assert(!after_bob || r->order>last_bob);
            assert(r->order<first_text);
            return;
        }
    }
    assert(!"missing World Map boundary rectangle");
}
static void draw_at(int top,int height){
    nr=nt=nb=0u; order=first_text=last_bob=0;
    map_top=top;map_height=height;
    game_adventure_quest_viewport((uint16_t)top,(uint16_t)height);
    assert(ga_map_view_top()==top && ga_map_view_height()==height);
    ga_world_map_window();
    assert(nb>0u); /* Painted tile and flag sprite are still visible. */
    assert(nt==2u); /* Both captions drawn after all four strips. */
    assert(nr==5u); /* Clear entire viewport, then precisely four strips. */
    require_rect(0,top,480,height,0);
    require_rect(0,top,480,24,1);
    require_rect(0,top+height-32,480,32,1);
    require_rect(0,top+24,8,height-24-32,1);
    require_rect(472,top+24,8,height-24-32,1);
    for(unsigned i=0;i<nr;++i)assert(rects[i].colour!=99u);
}
int main(void){
    static uint8_t art[16u*16u];
    static uint16_t tiles[60u*40u];
    for(unsigned i=0;i<60u*40u;++i)tiles[i]=65535u;
    tiles[10u*60u+10u]=0u;
    static const game_adventure_map_point_t point[]={{120,120,"Forest",1u,0u}};
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    ga_quest_style.background_colour=99u;
    game_adventure_world_map_boundary(37u);
    game_adventure_world_map(point,1u,480u,320u,current);
    game_adventure_world_map_tiles(tiles,60u,40u,art,"map.ppb",16u,16u,8u);
    ga_map_open=1u;
    ga_map_flash_frames=25u; /* no blinking rectangle to confuse spy */
    draw_at(0,320);   /* no dock */
    draw_at(0,272);   /* top dock: render already shifted by gamehud */
    draw_at(12,248);  /* explicitly offset framebuffer viewport */
    puts("PASS Stage 5.166.28 native: four strips only, HUD, captions, art and colour");
    return 0;
}
''')
    subprocess.run(['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror',
                    '-I',str(p),str(p/'test.c'),'-o',str(p/'native')],check=True)
    subprocess.run([str(p/'native')],check=True)
print('PASS Stage 5.166.28 renderer source contracts')
