from pathlib import Path
from subprocess import run
import re, os, shutil
root=Path(__file__).resolve().parents[2]
import tempfile
out=Path(tempfile.mkdtemp(prefix='codergirl-stage519-'))
(out/'gamehelpers').mkdir(parents=True,exist_ok=True)
header=(root/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
source=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
# render conditional blocks for shared player + no other optional features
for name, enable in {'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':False,'HAS_ADVENTURE_RUNTIME':False,'HAS_PLAYER_VISIBILITY':False,'HAS_SHARED_PLAYER':True}.items():
    patt=re.compile(r'@IDE_IF\{'+name+r'\}\n(.*?)@IDE_END\n',re.S)
    source,n=patt.subn((lambda m:m.group(1) if enable else ''),source)
    header,k=patt.subn((lambda m:m.group(1) if enable else ''),header)
    assert n+k>0,name
assert '@IDE_IF' not in source+header
mock='''static int init_assets(void) {return 1;}
static void close_assets(void) {}
static uint8_t init_objects(void) {return 1;}
'''
rows=['''    {.name="forest", .assets_init=init_assets, .assets_shutdown=close_assets,
       .objects_init=init_objects, .physics_profile=1}''', '''    {.name="world1", .assets_init=init_assets, .assets_shutdown=close_assets,
       .objects_init=init_objects, .physics_profile=7}''']
source=source.replace('@IDE{WORLD_DECLARATIONS}',mock).replace('@IDE{WORLD_RECORDS}',',\n'.join(rows))
assert '@IDE{' not in source+header
(out/'gamehelpers/gameworlds.h').write_text(header)
(out/'gamehelpers/gameworlds.c').write_text(source)
(out/'gamehelpers/gametilemap.h').write_text('''#ifndef TILEMOCK
#define TILEMOCK
#include <stdint.h>
typedef struct {int physics;} game_tile_player_t;
#endif
''')
(out/'gamehelpers/apis.h').write_text('void music_stop(void);\n')
(out/'gamehelpers/gameplayer.h').write_text('''#include "gametilemap.h"
#include <stdint.h>
uint8_t gameplayer_apply_physics(game_tile_player_t *p, uint8_t id);
''')
(out/'test.c').write_text('''#include <assert.h>
#include "gamehelpers/gameworlds.h"
#include <stdint.h>
static int calls;
void music_stop(void){}
uint8_t gameplayer_apply_physics(game_tile_player_t *p, uint8_t id) {
    ++calls; p->physics=id; return 1;
}
int main(void) {
    game_tile_player_t p={0};
    assert(gameworlds_physics_profile()==1);
    assert(gameworlds_start("forest"));
    assert(gameworlds_physics_profile()==1 && calls==0);
    assert(gameworlds_bind_player_physics(&p));
    assert(p.physics==1 && calls==1);
    assert(gameworlds_request("world1"));
    assert(gameworlds_apply_pending());
    assert(p.physics==7 && gameworlds_physics_profile()==7 && calls==2);
    assert(gameworlds_start("forest"));
    assert(p.physics==1 && calls==3);
    gameworlds_shutdown();
    assert(gameworlds_start("world1"));
    assert(calls==3); // shutdown clears the stale player binding
    return 0;
}
''')
r=run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-I'+str(out/'gamehelpers'),str(out/'gamehelpers/gameworlds.c'),str(out/'test.c'),'-o',str(out/'runtime-test')],capture_output=True,text=True)
assert r.returncode==0, r.stdout+r.stderr
r=run([str(out/'runtime-test')],capture_output=True,text=True)
assert r.returncode==0,r.stdout+r.stderr
player=(root/'gameplayerprofile.h').read_text(); game=(root/'gamedesigner.cpp').read_text(); snap=(root/'gameworldsnapshot.h').read_text()
assert 'worldPhysics' in player and 'worldPhysicsOverrides' in player and 'physicsForWorld' in player
for label in ('Starting physics for this world','Use default physics','worldPicker','worldStartProfile'):
    assert label in game
assert 'physicsForWorld(sharedPlayer, name)' in snap
assert 'worldPhysicsId' in snap
assert 'Build: 5.20.221026' in (root/'splashscreenwidget.cpp').read_text()
assert 'gameworlds_bind_player_physics(&player_physics)' in (root/'idelibs/codehelpers/game/maingame.rulec').read_text()
print('Stage 5.19: generated C compiled with gcc -Wall -Wextra -Werror, runtime transitions PASSED')
print('Stage 5.19: GUI and .sbpi contracts PASSED')
shutil.rmtree(out)
