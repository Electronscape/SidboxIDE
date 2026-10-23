#!/usr/bin/env python3
"""Regression for the actual Stage 5.49.1 animated HUD C generator templates.

The previous test used a simulated 13-placeholder substitution which missed Qt's
real generated output. Here each C++ QStringLiteral block is extracted verbatim,
expanded independently, and compiled and executed as C without a string repair.
"""
from pathlib import Path
import re
import subprocess
import tempfile

root=Path(__file__).resolve().parents[2]
s=(root/'gamehudeditor.cpp').read_text()
checks={
 'maximised editor': 'dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized)' in s,
 'HUD format v1 still readable': 'j.value("version").toInt()!=1' in s,
 'progress bars saved': 'j.insert("progressBars",progress)' in s,
 'drag and drop and edit': 'editProgressBar(-1)' in s and 'if(editBar)(void)editBar(selectedBar)' in s,
 'source atlas': 'for(const QString &path:atlasPaths)ppb->addItem(path,path);' in s,
 'frame sizes': '"8 x 8 cell"' in s and '"16 x 16 (2x2 8px cells)"' in s,
 'custom stat binding': 'gameplayer_stat_get(%1,&stat_value)' in s,
 'collectable binding': 'gameworlds_hud_total(%1u)' in s,
 'raw PPB index preservation': 'bytes.append(char(frame.pixelIndex(px,py)))' in s,
 'pixel clipped final cell': 'tile.width=(uint16_t)portion' in s,
 'one frame for every cell': 'tile.imgdat=hud_bar_%1_frames+frame*%2u' in s,
 'single tick per HUD draw': '++hud_bar_tick' in s,
 'no extra PPB': 'writeFile(QDir(hudFolder).filePath("gamehud.c")' in s,
 'hotfix splash': 'Build: 5.57.231026' in (root/'splashscreenwidget.cpp').read_text(),
}
for k,v in checks.items():print(('PASS' if v else 'FAIL'),k)
assert all(checks.values())

# Only match the bar C output, not its Qt editor UI.
start=s.index('        // Keep each QString::arg() template small.')
end=s.index('\n    }\n    if(customStatsUsed)',start)
segment=s[start:end]
blocks=re.findall(r'barDraws\+=QStringLiteral\((.*?)\)\s*((?:\.arg\([^;]*?\))+)\s*;',segment,re.S)
assert len(blocks)==5, f'Expected 5 bar C generator blocks, got {len(blocks)}'

# Decode the actual consecutive C++ string literals. These are the format
# strings passed into QString::arg(), not a parallel hand-made C template.
formats=[]
for literal,tail in blocks:
    strs=re.findall(r'"((?:\\.|[^"\\])*)"',literal)
    fmt=''.join(bytes(x,'utf8').decode('unicode_escape') for x in strs)
    references=[int(x) for x in re.findall(r'%([1-9][0-9]*)',fmt)]
    assert references and max(references)<=3,(fmt,references)
    assert not re.search(r'%1[0-9]|%2[0-9]|%3[0-9]',fmt)
    formats.append(fmt)
print('PASS every generator segment has at most 3 distinct placeholders')

# Verify exact C syntax for all 3 HUD source types. Replace only %N in each
# small block; leave a literal modulo '%' followed by whitespace untouched.
def expand(fmt,values):
    out=re.sub(r'%([1-9][0-9]*)',lambda m:values[int(m.group(1))-1],fmt)
    assert not re.search(r'%\d+',out),out
    return out

header='''#include <stdint.h>
#include <string.h>
typedef struct { const unsigned char *imgdat; uint16_t atlas_stride,atlas_height,width,height;
 int16_t drawx,drawy; uint16_t scale; } gfxbob_t;
static unsigned char screen[60][160];
static unsigned draw_calls;
static void gfx_drawbob(const gfxbob_t *b) {
 draw_calls++;
 for(unsigned y=0;y<b->height;++y)for(unsigned x=0;x<b->width;++x){
  if((unsigned)(b->drawx+x)<160 && (unsigned)(b->drawy+y)<60)
   screen[b->drawy+y][b->drawx+x]=b->imgdat[y*b->atlas_stride+x];
 }
}
static uint32_t hud_bar_tick;
static int32_t fear;
static uint32_t count;
static struct {uint32_t health,lives,score;} player;
#define gameworlds_state() (&player)
static int gameplayer_stat_get(const char *n,int32_t *v){*v=!strcmp(n,"Fear")?fear:0;return 1;}
static uint32_t gameworlds_hud_total(uint16_t k){return k==7?count:0;}
'''

def gen(size,width,count_frames,loop,binding,frame_tick,offset_x,offset_y):
    if binding=='health': expr='int64_t value=(int64_t)gameworlds_state()->health;\n'
    elif binding=='fear': expr='int32_t stat_value=0; (void)gameplayer_stat_get("Fear",&stat_value); int64_t value=(int64_t)stat_value;\n'
    else: expr='int64_t value=(int64_t)gameworlds_hud_total(7u);\n'
    groups=[
        ['0','"test"',expr],
        ['100',str(width),'0'],
        [str(frame_tick),str(loop),str(count_frames)],
        ['0',str(size*size),str(size)],
        [str(size),str(offset_x),str(offset_y)],
    ]
    body=''.join(expand(fmt,values) for fmt,values in zip(formats,groups))
    assert 'gfx_drawbob(&tile);' in body
    assert 'phase % '+str(count_frames)+'u' in body
    assert 'y+'+str(offset_y) in body
    assert not re.search(r'(?<![A-Za-z0-9_])%\d+\b',body),body
    return body

# Compile *exact C text* recovered above for all bar bindings and cell sizes.
# Test zero, half, full and animation frame selection after looping/saturation.
for size,width,num,loop,binding,half in [
    (8,19,3,1,'health',9),
    (16,33,2,0,'fear',16),
    (8,21,3,1,'pickup',10),
]:
    body=gen(size,width,num,loop,binding,2,3,4)
    array='static const unsigned char hud_bar_0_frames[%d]={'%(num*size*size)
    array+=','.join(str(17+i*19) for i in range(num) for _ in range(size*size))+'};\n'
    var={'health':'player.health','fear':'fear','pickup':'count'}[binding]
    tests='''static void draw(void){int32_t x=0,y=0;
'''+body+''' }
static int check(int expected,int pixel){
 if(draw_calls!=(unsigned)((expected+SIZE-1)/SIZE))return 1;
 for(int p=0;p<WIDTH;++p){
  unsigned char want=p<expected?(unsigned char)pixel:0;
  if(screen[4][3+p]!=want)return 2;
 }
 return 0;
}
int main(void){
 int ret;
 for(int test=0;test<4;++test){
  memset(screen,0,sizeof(screen)); draw_calls=0;
  hud_bar_tick=(test==3)?8u:0u;
  VALUE=(test==0)?0u:(test==1||test==3)?50u:100u;
  draw();
  int expected=(test==0)?0:(test==1||test==3)?HALF:WIDTH;
  int pixel=(test==3)?36:17;
  ret=check(expected,pixel);if(ret)return ret+test*10;
 }
 return 0;
}
'''
    tests=tests.replace('SIZE',str(size)).replace('WIDTH',str(width)).replace('HALF',str(half)).replace('VALUE',var)
    full=header+array+tests
    with tempfile.TemporaryDirectory() as tmp:
        src=Path(tmp)/'test.c'; exe=Path(tmp)/'test'
        src.write_text(full)
        cc=subprocess.run(['gcc','-std=c11','-Wall','-Werror','-Wno-unused-function','-Wno-unused-variable','-o',str(exe),str(src)],capture_output=True,text=True)
        if cc.returncode:
            print(full[-2500:]);print(cc.stderr);raise AssertionError('Generated C failed to compile')
        run=subprocess.run([str(exe)],capture_output=True,text=True)
        assert run.returncode==0,(size,binding,run.returncode)
    print('PASS generated C',binding,size,'px, clip, animation, zero/half/full')
print('Stage 5.49.1 generated HUD C regression PASS')
