#!/usr/bin/env python3
"""Stage 5.42: Sprite Stamp source PPB lookups and inventory atlas contracts.

No Qt SDK is required for these tests.  The C sample is compiled from the
actual generated rule's stamp drawer, not a rewritten approximation.
"""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
RULE = (ROOT / 'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
OBJECT = (ROOT / 'gamedesigner.cpp').read_text()
PROJECT = (ROOT / 'gamedesigner_project.cpp').read_text()
EXPORT = (ROOT / 'gamedesigner_export.cpp').read_text()
ADV = (ROOT / 'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
MAIN = (ROOT / 'idelibs/codehelpers/game/maingame.rulec').read_text()

assert 'stamp_%1.ppb' not in OBJECT
# Guard the preview lambda against missing explicit reference captures.
preview_capture = OBJECT.split('const auto updatePreview = [', 1)[1].split(']() {', 1)[0]
assert '&draftSpriteStamp' in preview_capture
assert 'The finished sprite is generated as one PPB' not in OBJECT
assert 'SidboxPpb::write(destination, picture' not in OBJECT
assert 'resource.path = storedPath(sourcePath);' in OBJECT
assert 'r.path = r.spriteStamp.sourcePath;' in PROJECT
assert 'r.spriteStamp.compose(source, &error)' in OBJECT
assert 'STAMP_DECLARATIONS' in EXPORT and 'HAS_STAMPS' in EXPORT
assert 'adventureIconAtlases.contains(r.id)' in EXPORT
assert 'ga_icon_registered[id] ? ga_icon_atlas[id] : ga_skin_pixels' in ADV
assert 'HAS_SCENERY_STAMPS' in EXPORT and 'SCENERY_STAMP_TABLES' in EXPORT
assert '@IDE{SCENERY_STAMP_TABLES}' in MAIN and 'gg_draw_scenery_stamp' in MAIN
assert 'SPRITE_STAMP_DRAW' in MAIN

begin = RULE.index('static int16_t cg_stamp_clamp(')
end = RULE.index('/* Replaces only drawing', begin)
drawer = RULE[begin:end]
decor_begin = MAIN.index('static int16_t gg_stamp_clamp(')
decor_end = MAIN.index('\n@IDE_END', decor_begin)
decor_drawer = MAIN[decor_begin:decor_end]
assert 'source->imgdat + (index/columns)' in drawer
assert 'code & 0x10000u' in drawer and 'code & 0x20000u' in drawer

source = r'''
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#define VIEW_W 480
#define VIEW_H 320
#define BLIT_FLAG_FLIP_X 4
#define BLIT_FLAG_FLIP_Y 8
#define BLIT_HANDLE_TOP_LEFT 0

typedef struct {
    const uint8_t *imgdat;
    uint8_t flags;
    uint16_t atlas_stride,atlas_height,width,height;
    int16_t drawx,drawy;
    uint16_t scale;
    uint8_t handle,index;
} gfxbob_t;
typedef struct {
    const uint32_t *cells;
    uint8_t columns,rows;
} cg_stamp_t;

static uint8_t pixels[256*128];
static uint8_t screen[480*320];
static int call_count;
static void gfx_drawbob(const gfxbob_t *bob)
{
    assert(bob->index == 0);
    assert(bob->width == 8 && bob->height == 8);
    assert(bob->atlas_stride == 256);
    ++call_count;
    for (int y=0;y<8;++y) for (int x=0;x<8;++x) {
        int sx = (bob->flags&BLIT_FLAG_FLIP_X) ? 7-x : x;
        int sy = (bob->flags&BLIT_FLAG_FLIP_Y) ? 7-y : y;
        uint8_t value = bob->imgdat[sy*bob->atlas_stride+sx];
        int dx = bob->drawx+x, dy = bob->drawy+y;
        if (value && dx >= 0 && dx < 480 && dy >= 0 && dy < 320)
            screen[dy*480+dx] = value;
    }
}
'''+drawer+'\n'+decor_drawer+r'''
static void mark(int cell, uint8_t first, uint8_t last)
{
    int x=(cell%32)*8,y=(cell/32)*8;
    pixels[y*256+x] = first;
    pixels[(y+7)*256+x+7] = last;
}
static uint8_t at(int x, int y) { return screen[y*480+x]; }
int main(void)
{
    gfxbob_t b = {0};
    b.imgdat=pixels; b.atlas_stride=256; b.atlas_height=128;
    b.width=8; b.height=8; b.scale=100;
    mark(300,3,4); // beyond gfxbob_t.index's 255 limit
    mark(1,5,6);
    static const uint32_t values[]={0x10000u|300u,0xFFFFFFFFu,0x20000u|1u,1u};
    static const cg_stamp_t stamp={values,2,2};
    cg_draw_stamp(&b,&stamp,20,30,0,0);
    assert(call_count==3);
    assert(at(27,30)==3 && at(20,37)==4); // per-cell flip X
    assert(at(20,45)==5 && at(27,38)==6); // per-cell flip Y
    assert(at(28,38)==5 && at(35,45)==6); // ordinary tile
    memset(screen,0,sizeof(screen));call_count=0;
    b.flags = BLIT_FLAG_FLIP_X|BLIT_FLAG_FLIP_Y;
    cg_draw_stamp(&b,&stamp,20,30,0,0);
    assert(call_count==3);
    assert(at(28,45)==3 && at(35,38)==4); // both flips: X cancels, Y acts
    assert(at(35,30)==5 && at(28,37)==6); // Y cancels, X acts
    assert(at(20,30)==6 && at(27,37)==5); // both flips on ordinary cell
    memset(screen,0,sizeof(screen));call_count=0;
    b.flags=0;
    cg_draw_stamp(&b,&stamp,25,35,5,5);
    assert(at(27,30)==3); // camera subtraction
    memset(screen,0,sizeof(screen));call_count=0;
    static const cg_stamp_t plain={0,0,0};
    b.imgdat=pixels + 300/32*8*256 + 300%32*8;
    cg_draw_stamp(&b,&plain,20,30,0,0);
    assert(call_count==1 && at(20,30)==3); // ordinary sprite fallback
    memset(screen,0,sizeof(screen));call_count=0;
    b.imgdat=pixels; b.flags=0;
    gg_draw_scenery_stamp(&b,values,2,2,20,30,0,0,BLIT_FLAG_FLIP_X);
    assert(call_count==3);
    assert(at(28,30)==3 && at(35,37)==4); // decoration: global X cancels cell X
    assert(at(35,45)==5 && at(28,38)==6); // decoration: X plus per-cell Y
    return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
    src=Path(d)/'test.c'
    binary=Path(d)/'test'
    src.write_text(source)
    subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-O2',str(src),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
print('Stage 5.42 managed/scenery stamp PPB lookup, flips, camera, and inventory atlas: PASS')
