#!/usr/bin/env python3
"""Stage 5.57: compile the real generated HUD docking snippet and damage event."""
from pathlib import Path
import re,subprocess,tempfile
R=Path(__file__).resolve().parents[2]
hud=(R/'gamehudeditor.cpp').read_text()
main=(R/'idelibs/codehelpers/game/maingame.rulec').read_text()
obj=(R/'idelibs/codehelpers/game/worldobjects.rulec').read_text()
world=(R/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
adv=(R/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
# Guard schema, editor and export bindings against accidental partial updates.
for filename,tokens in {
    'gamedesigner.h':['damageTarget','damageDelta','damageConfigured'],
    'gamedesigner.cpp':['Damage target stat','Stat change (+/-)','Custom stat: %1'],
    'gamedesigner_project.cpp':['"damageTarget"','"damageDelta"'],
    'gamedesigner_export.cpp':['DAMAGE_TARGET','DAMAGE_DELTA','DAMAGE_NAME'],
    'idelibs/codehelpers/game/gameworlditems.rulec':['@IDE{DAMAGE_TARGET}','@IDE{DAMAGE_DELTA}','@IDE{DAMAGE_NAME}'],
    'idelibs/codehelpers/game/worldobjects.ruleh':['hurt_stat_target','hurt_stat_delta','damage_delta'],
}.items():
 s=(R/filename).read_text()
 for needle in tokens:assert needle in s,(filename,needle)
assert 'gamehud_apply_dock(front[draw_index]);' in main
assert 'GAME_PLAY_H' in main and 'game_tilemap_blit_view_front' in main
assert 'numericStats' in hud and 'kStatMime' in hud and 'Dock HUD at top' in hud
assert 'gameworlds_adjust_pickup' in world and 'game_adventure_adjust_pickup' in adv
assert 'p->hurt_stat_delta = o->damage_delta;' in obj
assert 'Build: 5.57.231026' in (R/'splashscreenwidget.cpp').read_text()

# Recover the C body emitted by the *actual* HUD QStringLiteral, no surrogate algorithm.
a=hud.index('    c+=QStringLiteral(\n        "/* SIDBOX foreground')
b=hud.index('    c+=QStringLiteral("void game_show_hud_at',a)
segment=hud[a:b]
parts=re.findall(r'"((?:\\.|[^"\\])*)"',segment)
assert parts,len(parts)
body=''.join(bytes(t,'utf-8').decode('unicode_escape') for t in parts)
assert 'void gamehud_apply_dock(' in body
CHEAD='''#include <stdint.h>\n#include <string.h>\n#include <assert.h>\n#include <stdio.h>\ntypedef struct {uint8_t*bitmap;uint16_t width,height,stride,pad;uint32_t memspacelen;} gfx_bitmap_t;\nstatic int dockMode;\nuint16_t gamehud_dock_height(void){return 40;}\nuint8_t gamehud_dock_top(void){return dockMode;}\n'''
# Test top and bottom with sentinels + non-contiguous stride.
runner='''
int main(void){
    static uint8_t pixels[480*336];gfx_bitmap_t b={pixels,480,320,336,0,sizeof(pixels)};
    for(int mode=0;mode<2;++mode){
        dockMode=mode;
        for(int x=0;x<480;++x)for(int y=0;y<336;++y)pixels[x*336+y]=(uint8_t)(y%251+1);
        gamehud_apply_dock(&b);
        for(int x=0;x<480;++x)for(int y=0;y<320;++y){
            uint8_t expected;
            if(mode) expected=y<40?0:(uint8_t)((y-40)%251+1);
            else expected=y>=280?0:(uint8_t)(y%251+1);
            assert(pixels[x*336+y]==expected);
        }
        for(int x=0;x<480;++x)for(int y=320;y<336;++y)
            assert(pixels[x*336+y]==(uint8_t)(y%251+1));
    }
    b.memspacelen=100;pixels[0]=123;gamehud_apply_dock(&b);assert(pixels[0]==123);
    puts("Stage 5.57 docked foreground clipping PASS");return 0;
}
'''
# Pull the exact hit-processing clause from generated starter main.
prefix='        if (world_player.hurt_triggered) {'
a=main.index(prefix)
start=main.index('{',a)
depth=0;end=None
for i in range(start,len(main)):
 if main[i]=='{': depth+=1
 if main[i]=='}':
  depth-=1
  if depth==0:end=i+1;break
assert end
hit=main[a:end]
hit=re.sub(r'^@IDE_(?:IF\{[^}]+\}|END)\n','',hit,flags=re.M)
assert '@IDE' not in hit and 'case 4' in hit
mock='''#include <stdint.h>\n#include <limits.h>\n#include <string.h>\n#include <assert.h>\n#include <stdio.h>\n
typedef struct {uint32_t health,lives,score;} state_t;\nstatic state_t state;\nstatic state_t *gameworlds_state(void){return &state;}\nstatic int32_t fear;static int32_t coins;\nstatic uint32_t player_health;\nstatic struct {int hurt_triggered;int32_t hurt_stat_delta;uint8_t hurt_stat_target;const char*hurt_stat_name;}world_player;\nstatic void gameworlds_adjust_pickup(uint16_t kind,int32_t delta){assert(kind==1);coins+=delta;if(coins<0)coins=0;}\nstatic int gameplayer_stat_get(const char *name,int32_t *result){if(strcmp(name,"Fear"))return 0;*result=fear;return 1;}\nstatic int gameplayer_stat_set(const char *name,int32_t value){if(strcmp(name,"Fear"))return 0;fear=value;return 1;}\nvoid apply(void){\n'''+hit+'\n}\n'+'''
int main(void){
  state.health=100;state.lives=4;state.score=10;coins=20;fear=40;
  world_player.hurt_triggered=1;world_player.hurt_stat_target=0;world_player.hurt_stat_delta=-10;apply();assert(state.health==90 && player_health==90);
  world_player.hurt_stat_delta=5;apply();assert(state.health==95);
  world_player.hurt_stat_delta=-200;apply();assert(state.health==0);
  world_player.hurt_stat_target=1;world_player.hurt_stat_delta=-3;apply();assert(state.lives==1);
  world_player.hurt_stat_target=2;world_player.hurt_stat_delta=12;apply();assert(state.score==22);
  world_player.hurt_stat_target=3;world_player.hurt_stat_delta=-10;apply();assert(coins==10);
  world_player.hurt_stat_target=4;world_player.hurt_stat_name="Fear";world_player.hurt_stat_delta=+9;apply();assert(fear==49);
  world_player.hurt_triggered=0;world_player.hurt_stat_delta=-20;apply();assert(fear==49);
  puts("Stage 5.57 accepted-hit signed stats PASS");return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage557-') as d:
 for name,code in [('hud',CHEAD+body+runner),('damage',mock)]:
  source=Path(d)/(name+'.c');exe=Path(d)/(name+'.bin');source.write_text(code)
  cmd=['cc','-std=c11','-Wall','-Wextra','-Werror',str(source),'-o',str(exe)]
  res=subprocess.run(cmd,text=True,capture_output=True)
  assert res.returncode==0,(name,res.stderr)
  res=subprocess.run([str(exe)],text=True,capture_output=True)
  assert res.returncode==0,(name,res.stderr)
  print(res.stdout.strip())
print('Stage 5.57 source + native integration PASS')
