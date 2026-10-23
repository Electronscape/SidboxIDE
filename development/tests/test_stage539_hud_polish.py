#!/usr/bin/env python3
"""Stage 5.39 HUD upgrades: source contracts and strict C runtime smoke."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
s=(root/'gamehudeditor.cpp').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
assert '"outlineEnabled",outlineEnabled' in s
assert '"outlineColour",outlineColour' in s
assert '"hudX",hudX' in s and '"hudY",hudY' in s
assert 'doc.outlineEnabled' in s and 'doc.outlineColour' in s
assert 'gfx_drawtext(x-1,y,text)' in s and 'gfx_drawtext(x,y+1,text)' in s
assert 'snprintf(count,sizeof(count),\\"%u\\"' in s
assert 'snprintf(count,sizeof(count),\\"%%lu\\"' not in s
assert 'QDirIterator allPpbs' in s and '"*.ppb"' in s
assert 'QScrollArea' in s and 'HudZoomScroll' in s and 'wheelEvent(QWheelEvent *e)' in s
assert '8×16 pixel font preview' in s and 'previewText' in s
assert 'doc.tiles.fill(Tile(),' not in s
assert 'doc.resize(columns->value(),rows->value());doc.cw=cw->value()' in s
assert 'void game_show_hud_at(int32_t x, int32_t y)' in s
assert 'if (x==0 && y==0)' in s
assert 'HudScreenPreview' in s and 'screenPreview->moved' in s
assert 'game_show_hud(0, 0);' in main and 'game_show_hud_at(x,y)' in main
assert 'Build: 5.40.231026' in (root/'splashscreenwidget.cpp').read_text()
# Compile and run a faithful representative of generated HUD graphics code,
# including a real printf value, palette outline, and saved position override.
with tempfile.TemporaryDirectory(prefix='stage539-hud-') as d:
    p=Path(d)
    (p/'mock.h').write_text('''#include <stdint.h>
typedef struct {uint8_t *imgdat;uint16_t atlas_stride,atlas_height,width,height,scale;int32_t drawx,drawy;} gfxbob_t;
void gfx_drawbob(gfxbob_t*);void gfx_setcolour(unsigned);void gfx_drawtext(int32_t,int32_t,char*);
uint32_t gameworlds_hud_total(uint16_t);
''')
    (p/'generated.c').write_text('''#include "mock.h"
#include <stdio.h>
static const unsigned char hud_pixels[4] __attribute__((aligned(32)))={1,2,3,4};
static const unsigned char icon_0[4] __attribute__((aligned(32)))={1,2,3,4};
static void hud_draw_text(int32_t x,int32_t y,char *text) __attribute__((unused));
static void hud_draw_text(int32_t x,int32_t y,char *text){
    gfx_setcolour(2u);
    gfx_drawtext(x-1,y,text);gfx_drawtext(x+1,y,text);
    gfx_drawtext(x,y-1,text);gfx_drawtext(x,y+1,text);
    gfx_setcolour(15u);gfx_drawtext(x,y,text);
}
void game_show_hud_at(int32_t x,int32_t y){
    gfxbob_t background={0};background.imgdat=(uint8_t*)hud_pixels;
    background.atlas_stride=2u;background.atlas_height=2u;
    background.width=2u;background.height=2u;background.scale=100u;
    background.drawx=x;background.drawy=y;gfx_drawbob(&background);
    hud_draw_text(x+1,y+2,(char*)"Coins:");
    {gfxbob_t icon={0};icon.imgdat=(uint8_t*)icon_0;
     icon.atlas_stride=2u;icon.atlas_height=2u;icon.width=2u;icon.height=2u;
     icon.scale=100u;icon.drawx=x+14;icon.drawy=y+2;gfx_drawbob(&icon);
     char count[16];snprintf(count,sizeof(count),"%u",(unsigned int)gameworlds_hud_total(7u));
     hud_draw_text(x+18,y+2,count);}
}
void game_show_hud(int32_t x,int32_t y){
    if(x==0 && y==0){x=90;y=24;}
    game_show_hud_at(x,y);
}
''')
    (p/'test.c').write_text('''#include "mock.h"
#include <assert.h>
#include <string.h>
void game_show_hud(int32_t,int32_t);void game_show_hud_at(int32_t,int32_t);
static int draws,texts,numbers,front,outline;static int firstX,firstY;
void gfx_drawbob(gfxbob_t*b){assert(b && b->imgdat && b->scale==100u);if(draws%2==0){firstX=b->drawx;firstY=b->drawy;}draws++;}
void gfx_setcolour(unsigned n){if(n==15)front++;else if(n==2)outline++;else assert(0);}
void gfx_drawtext(int32_t x,int32_t y,char*t){(void)x;(void)y;assert(t);if(strcmp(t,"1234")==0)numbers++;texts++;}
uint32_t gameworlds_hud_total(uint16_t kind){assert(kind==7);return 1234u;}
int main(void){game_show_hud(0,0);assert(firstX==90&&firstY==24);
  assert(numbers==5&&texts==10&&front==2&&outline==2&&draws==2);
  game_show_hud_at(0,0);assert(firstX==0&&firstY==0);return 0;}
''')
    cmd=['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(p),str(p/'generated.c'),str(p/'test.c'),'-o',str(p/'test')]
    x=subprocess.run(cmd, text=True, capture_output=True)
    assert x.returncode==0,x.stderr
    x=subprocess.run([str(p/'test')],text=True,capture_output=True)
    assert x.returncode==0,x.stderr
print('PASS Stage 5.39 HUD source contracts, generated-style strict C, positions, counts and outline')
