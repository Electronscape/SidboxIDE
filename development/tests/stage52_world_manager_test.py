from pathlib import Path
import tempfile,subprocess,re,shutil
sdk=Path(__file__).resolve().parents[2]/'idelibs/codehelpers/game'
out=Path(tempfile.mkdtemp(prefix='stage52-worldmanager-'))
# Dedicated temporary test directory only
(out/'gamehelpers').mkdir(parents=True)
for name in ['forest','world1']:
    (out/'worlds'/name).mkdir(parents=True)
(out/'gamehelpers'/'gametilemap.h').write_text('typedef struct {int width;} game_tilemap_t;\n')
(out/'gamehelpers'/'apis.h').write_text('void music_stop(void);\n')
(out/'gamehelpers'/'gameadventureruntime.h').write_text('void game_adventure_start(const void*,int,const void*,int,const void*,int,const void*,int,int,int,const void*,int,const void*,const void*);\n')
def render_flags(s, values):
    for key, enabled in values.items():
        pattern = re.compile(r'@IDE_IF\{'+key+r'\}\n(.*?)@IDE_END\n',re.S)
        s = pattern.sub(lambda m:m.group(1) if enabled else '',s)
    assert '@IDE' not in s
    return s
(out/'gamehelpers'/'gameworlds.h').write_text(render_flags((sdk/'gameworlds.ruleh').read_text(),{'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':False,'HAS_PLAYER_VISIBILITY':False,'HAS_SHARED_PLAYER':False}))
record=lambda name,map_yes,modern: (
    '    {"'+name+'", '+name+'_gameassets_init, '+name+'_gameassets_shutdown,\n'
    '     '+name+'_gameworlditems_init, '+name+'_gameworlditems_update, '+name+'_gameworlditems_draw, 0,\n'
    '     '+name+'_gameassets_draw_foreground, '+name+'_gameassets_draw_background, '+name+'_gameassets_show_background,\n'
    '     '+name+'_gameadventure_setup, '+name+'_gameadventure_store_inventory, '+name+'_gameadventure_load_inventory,\n'
    '     '+(('&game_'+name+', game_'+name+'_load_map, game_'+name+'_unload_map, game_'+name+'_load_atlas, game_'+name+'_unload_atlas, "gamelevels/'+name+'.map"') if map_yes else '0, 0, 0, 0, 0, 0') + (', 120, 80, 1, 0' if name=='world1' else ', 50, 20, 0, 0') + '}')
code=(sdk/'gameworlds.rulec').read_text()
code=code.replace('@IDE{WORLD_DECLARATIONS}', '#include "../worlds/world1/world_api.h"\n#include "../worlds/forest/world_api.h"')
code=code.replace('@IDE{WORLD_RECORDS}', record('world1',True,True)+',\n'+record('forest',False,True))
code=render_flags(code,{'HAS_ADVENTURE_RUNTIME':True,'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':False,'HAS_PLAYER_VISIBILITY':False,'HAS_SHARED_PLAYER':False})
assert '@IDE' not in code,code[:2000]
(out/'gamehelpers'/'gameworlds.c').write_text(code)
for name in ['world1','forest']:
    s='''#include "../../gamehelpers/gameworlds.h"
int {n}_gameassets_init(void);void {n}_gameassets_shutdown(void);
unsigned char {n}_gameworlditems_init(void);void {n}_gameworlditems_update(unsigned short);
void {n}_gameworlditems_draw(int,int);void {n}_gameassets_draw_foreground(void);
void {n}_gameassets_draw_background(void);void {n}_gameassets_show_background(void);
void {n}_gameadventure_setup(void);
void {n}_gameadventure_store_inventory(gameworlds_inventory_put_t,void*);
void {n}_gameadventure_load_inventory(gameworlds_inventory_get_t,void*);
'''.replace('{n}',name)
    if name=='world1':
        s+='''#include "../../gamehelpers/gametilemap.h"
extern game_tilemap_t game_world1;
unsigned char game_world1_load_map(const char*);
void game_world1_unload_map(void);
unsigned char game_world1_load_atlas(void);
void game_world1_unload_atlas(void);
'''
    (out/'worlds'/name/'world_api.h').write_text(s)
# namespaced simulated runtime and checking
h='''#include "gamehelpers/gameworlds.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
static int inits[2],stops[2],maploads,atlasloads,tot_music_stops;
static int inventory_val=7;
static int fail_forest=0;
game_tilemap_t game_world1 = {12};
void music_stop(void){++tot_music_stops;}
void game_adventure_start(const void*a,int b,const void*c,int d,const void*e,int f,const void*g,int h,int i,int j,const void*k,int l,const void*m,const void*n){}
#define MOCK(n,idx) \\
int n##_gameassets_init(void){++inits[idx];return (idx != 1 || !fail_forest);} \\
void n##_gameassets_shutdown(void){++stops[idx];} \\
unsigned char n##_gameworlditems_init(void){return 1;} \\
void n##_gameworlditems_update(unsigned short x){(void)x;} \\
void n##_gameworlditems_draw(int a,int b){(void)a;(void)b;} \\
void n##_gameassets_draw_foreground(void){} \\
void n##_gameassets_draw_background(void){} \\
void n##_gameassets_show_background(void){} \\
void n##_gameadventure_setup(void){} \\
void n##_gameadventure_store_inventory(gameworlds_inventory_put_t sink,void*u){sink("Magic Key",inventory_val,u);} \\
void n##_gameadventure_load_inventory(gameworlds_inventory_get_t getter,void*u){unsigned long count=getter("Magic Key",u);if(count!=0xffffffffu)inventory_val=(int)count;}
MOCK(world1,0)
MOCK(forest,1)
unsigned char game_world1_load_map(const char*x){assert(!strcmp(x,"gamelevels/world1.map"));++maploads;return 1;}
void game_world1_unload_map(void){}
unsigned char game_world1_load_atlas(void){++atlasloads;return 1;}
void game_world1_unload_atlas(void){}
static void save(gameworlds_player_state_t*s,void*user){(void)user;s->score+=5;}
static void restore(gameworlds_player_state_t*s,void*user){(void)user;assert(s->health==3);}
int main(void){
 assert(gameworlds_count()==2);
 gameworlds_state()->health=3;
 gameworlds_player_hooks(save,restore,0);
 assert(gameworlds_start(0)); assert(!strcmp(gameworlds_active(),"world1"));
 assert(gameworlds_map()==&game_world1);
 gameworlds_spawn_t start={0}; assert(gameworlds_player_start(&start) && start.x==120 && start.y==80 && start.facing==1);
 assert(gameworlds_request("forest"));
 assert(!strcmp(gameworlds_active(),"world1"));
 assert(gameworlds_apply_pending());assert(!strcmp(gameworlds_active(),"forest"));
 assert(gameworlds_map()==0);assert(gameworlds_state()->score==5);
 assert(gameworlds_player_start(&start) && start.x==50 && start.y==20 && start.facing==0);
 assert(gameworlds_request("world1"));
 assert(gameworlds_apply_pending()); assert(gameworlds_map()==&game_world1);
 assert(gameworlds_state()->score==10);assert(inventory_val==7);
 assert(!gameworlds_request("nothere"));
 assert(gameworlds_request("forest"));fail_forest=1;
 assert(!gameworlds_apply_pending());assert(gameworlds_active()==0);
 assert(tot_music_stops>0);printf("Stage 5.2 manager: PASS\\n");
 return 0;
}
'''
# fix macro backslash in Python string (above escaped backslash)
(out/'test.c').write_text('#include "gamehelpers/gametilemap.h"\n'+h)
cmd=['gcc','-std=c11','-Wall','-Wextra','-Werror','-Wno-unused-parameter','-I',str(out/'gamehelpers'),str(out/'gamehelpers'/'gameworlds.c'),str(out/'test.c'),'-o',str(out/'test')]
a=subprocess.run(cmd,text=True,capture_output=True);print('compilation:',a.returncode,a.stderr[:5000]);
if a.returncode==0:
 b=subprocess.run([str(out/'test')],text=True,capture_output=True);print('execution:',b.returncode,b.stdout,b.stderr)
