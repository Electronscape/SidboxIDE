"""Host GCC test of Stage 5.2 conditional APIs with different-feature worlds.
Use: python3 development/tests/stage52_world_features_test.py
"""
from pathlib import Path
import re, subprocess, tempfile

sdk = Path(__file__).resolve().parents[2] / 'idelibs/codehelpers/game'

def render(text, flags):
    for key, on in flags.items():
        pattern = re.compile(r'@IDE_IF\{' + key + r'\}\n(.*?)@IDE_END\n', re.S)
        text = pattern.sub(lambda m: m.group(1) if on else '', text)
    assert '@IDE' not in text, text[:1000]
    return text

with tempfile.TemporaryDirectory(prefix='stage52-feature-test-') as temp:
    root = Path(temp)
    gh = root / 'gamehelpers'
    gh.mkdir()
    (gh / 'gameworldobjects.h').write_text('#ifndef TEST_GWO_H\n#define TEST_GWO_H\ntypedef struct {int touched;} game_world_player_t;\n#endif\n')
    (gh / 'gamecollectables.h').write_text('#ifndef TEST_GC_H\n#define TEST_GC_H\ntypedef void (*game_pickup_callback_t)(int,void*);\n#endif\n')
    (gh / 'apis.h').write_text('void music_stop(void);\n')
    (gh / 'gameadventureruntime.h').write_text('void game_adventure_start(const void*,int,const void*,int,const void*,int,const void*,int,int,int,const void*,int,const void*,const void*);\n')
    flags = {'HAS_WORLD_PHYSICS': True, 'HAS_PICKUPS': True, 'HAS_ADVENTURE_RUNTIME': True, 'HAS_PLAYER_VISIBILITY': False}
    (gh / 'gameworlds.h').write_text(render((sdk/'gameworlds.ruleh').read_text(), flags))
    worlds = ['world1', 'forest']
    for world in worlds:
        directory = root / 'worlds' / world
        directory.mkdir(parents=True)
        base = f'{world}_'
        decl = '''#include "../../gamehelpers/gameworlds.h"
int PREFIXgameassets_init(void);
void PREFIXgameassets_shutdown(void);
unsigned char PREFIXgameworlditems_init(void);
void PREFIXgameworlditems_update(unsigned short);
void PREFIXgameworlditems_draw(int,int);
void PREFIXgameassets_draw_foreground(void);
void PREFIXgameassets_draw_background(void);
void PREFIXgameassets_show_background(void);
void PREFIXgameadventure_setup(void);
void PREFIXgameadventure_store_inventory(gameworlds_inventory_put_t,void*);
void PREFIXgameadventure_load_inventory(gameworlds_inventory_get_t,void*);
'''.replace('PREFIX',base)
        if world == 'world1':
            decl += '''void PREFIXgameworlditems_draw_behind(int,int);
void PREFIXgameworlditems_before(game_world_player_t*);
void PREFIXgameworlditems_after(game_world_player_t*);
unsigned short PREFIXgameworlditems_check(int,int,unsigned short,unsigned short,game_pickup_callback_t,void*);
'''.replace('PREFIX', base)
        (directory / 'world_api.h').write_text(decl)
    records=[]
    for world in worlds:
        base=f'{world}_'
        has_feats=world=='world1'
        values=[f'"{world}"',base+'gameassets_init',base+'gameassets_shutdown',base+'gameworlditems_init',base+'gameworlditems_update',base+'gameworlditems_draw', base+'gameworlditems_draw_behind' if has_feats else '0',base+'gameassets_draw_foreground',base+'gameassets_draw_background',base+'gameassets_show_background',base+'gameadventure_setup',base+'gameadventure_store_inventory',base+'gameadventure_load_inventory','0','0','0','0','0','0',base+'gameworlditems_before' if has_feats else '0',base+'gameworlditems_after' if has_feats else '0',base+'gameworlditems_check' if has_feats else '0', '120' if has_feats else '50', '80' if has_feats else '20', '1' if has_feats else '0']
        records.append('    {'+', '.join(values)+'}')
    c = (sdk/'gameworlds.rulec').read_text()
    c = c.replace('@IDE{WORLD_DECLARATIONS}', '\n'.join(f'#include "../worlds/{w}/world_api.h"' for w in worlds))
    c = c.replace('@IDE{WORLD_RECORDS}', ',\n'.join(records))
    (gh / 'gameworlds.c').write_text(render(c, flags))
    mock = '''#include "gamehelpers/gameworlds.h"
#include <assert.h>
#include <string.h>
static int current; static int before_count,after_count,check_count;
static int save_count,restore_count,stops;
void music_stop(void){++stops;}
void game_adventure_start(const void*a,int b,const void*c,int d,const void*e,int f,const void*g,int h,int i,int j,const void*k,int l,const void*m,const void*n){}
#define WORLD(w,num) \\
int w##_gameassets_init(void){ current=num; return 1; } \\
void w##_gameassets_shutdown(void){} \\
unsigned char w##_gameworlditems_init(void){return 1;} \\
void w##_gameworlditems_update(unsigned short n){(void)n;} \\
void w##_gameworlditems_draw(int x,int y){(void)x;(void)y;} \\
void w##_gameassets_draw_foreground(void){} \\
void w##_gameassets_draw_background(void){} \\
void w##_gameassets_show_background(void){} \\
void w##_gameadventure_setup(void){} \\
void w##_gameadventure_store_inventory(gameworlds_inventory_put_t put,void*c){put("Coin",(unsigned short)num,c);} \\
void w##_gameadventure_load_inventory(gameworlds_inventory_get_t get,void*c){(void)get("Coin",c);}
WORLD(world1,1)
WORLD(forest,2)
void world1_gameworlditems_draw_behind(int x,int y){(void)x;(void)y;}
void world1_gameworlditems_before(game_world_player_t*p){p->touched=1;++before_count;}
void world1_gameworlditems_after(game_world_player_t*p){p->touched=2;++after_count;}
unsigned short world1_gameworlditems_check(int x,int y,unsigned short w,unsigned short h,game_pickup_callback_t cb,void*u){(void)x;(void)y;(void)w;(void)h;(void)cb;(void)u;++check_count;return 7;}
static void save(gameworlds_player_state_t*s,void*u){(void)u;++save_count;s->health=99;}
static void restore(gameworlds_player_state_t*s,void*u){(void)u;++restore_count;assert(s->health==99);}
int main(void){
 game_world_player_t player={0};
 gameworlds_player_hooks(save,restore,0);
 assert(gameworlds_start("world1"));
 assert(current==1); assert(restore_count==0);
 gameworlds_spawn_t pos={0};assert(gameworlds_player_start(&pos) && pos.x==120 && pos.y==80 && pos.facing==1); /* never restore zeros at startup */
 gameworlds_before(&player);assert(player.touched==1 && before_count==1);
 gameworlds_after(&player);assert(player.touched==2 && after_count==1);
 assert(gameworlds_check(0,0,3,3,0,0)==7 && check_count==1);
 assert(gameworlds_request("forest"));assert(current==1); /* deferred */
 assert(gameworlds_apply_pending());assert(current==2 && save_count==1 && restore_count==1);
 assert(gameworlds_player_start(&pos) && pos.x==50 && pos.y==20 && pos.facing==0);
 player.touched=0;gameworlds_before(&player);gameworlds_after(&player);
 assert(!player.touched && before_count==1 && after_count==1);
 assert(gameworlds_check(0,0,3,3,0,0)==0 && check_count==1);
 assert(gameworlds_request("world1"));assert(gameworlds_apply_pending());
 assert(current==1 && save_count==2 && restore_count==2);
 assert(stops>=2); gameworlds_shutdown();assert(save_count==3);
 return 0;
}
'''
    (root/'test.c').write_text(mock)
    args=['gcc','-std=c11','-Wall','-Wextra','-Werror','-Wno-unused-parameter','-I',str(gh),str(gh/'gameworlds.c'),str(root/'test.c'),'-o',str(root/'test')]
    p = subprocess.run(args,capture_output=True,text=True)
    if p.returncode: raise SystemExit(f'Compile failed: {p.stderr}')
    p=subprocess.run([str(root/'test')],capture_output=True,text=True)
    if p.returncode: raise SystemExit(f'Run failed: {p.returncode}: {p.stderr}')
    print('Stage 5.2 mixed-world conditional callbacks: PASS')
