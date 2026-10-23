#!/usr/bin/env python3
"""Two-world shared inventory and HUD total smoke, compiled with host GCC."""
from pathlib import Path
import re,subprocess,tempfile
root=Path(__file__).resolve().parents[2]
sdk=root/'idelibs/codehelpers/game'
def render(src, flags):
    lines=[];enabled=[True]
    for line in src.splitlines(keepends=True):
        m=re.fullmatch(r'@IDE_IF\{([A-Z_]+)\}\n?',line)
        if m:
            assert m.group(1) in flags,m.group(1)
            enabled.append(enabled[-1] and flags[m.group(1)])
        elif line.strip()=='@IDE_END':
            assert len(enabled)>1
            enabled.pop()
        elif line.strip()=='@IDE_ELSE':
            enabled[-1]=enabled[-2] and not enabled[-1]
        elif enabled[-1]:lines.append(line)
    assert len(enabled)==1
    return ''.join(lines)
with tempfile.TemporaryDirectory(prefix='stage541-worlds-') as tmp:
    d=Path(tmp)
    for name in ('world1','world2'):
        (d/f'worlds/{name}').mkdir(parents=True)
    (d/'gamecollectables.h').write_text('''#ifndef MOCK_GAMECOLLECTABLES_H
#define MOCK_GAMECOLLECTABLES_H
#include <stdint.h>
typedef struct{uint16_t kind,value;uint8_t tracking_configured,show_in_inventory,show_in_hud,persistent,active;}game_collectable_t;
typedef void(*game_pickup_callback_t)(game_collectable_t*,void*);
#endif
''')
    (d/'gameadventureruntime.h').write_text('''#include <stdint.h>
uint16_t game_adventure_collect_amount(uint16_t,uint16_t);
uint8_t game_adventure_pickup_quantity(uint16_t,uint32_t*);
void game_adventure_managed_pickup_begin(uint16_t);
void game_adventure_managed_pickup_end(void);
void game_adventure_start(const void*,int,const void*,int,const void*,int,const void*,int,int,int,const void*,int,const void*,const void*);
''')
    (d/'apis.h').write_text('void music_stop(void);\n')
    flags={'HAS_WORLD_PHYSICS':False,'HAS_PICKUPS':True,'HAS_PLAYER_VISIBILITY':False,
           'HAS_SHARED_PLAYER':False,'HAS_ADVENTURE_RUNTIME':True}
    (d/'gameworlds.h').write_text(render((sdk/'gameworlds.ruleh').read_text(),flags))
    decls=[];records=[]
    for name in ('world1','world2'):
        head='''#include "../../gameworlds.h"
int {n}_assets_init(void);void {n}_assets_shutdown(void);
uint8_t {n}_objects_init(void);void {n}_objects_update(uint16_t);
void {n}_objects_draw(int32_t,int32_t);
void {n}_fg(void);void {n}_bg(void);void {n}_show_bg(void);
void {n}_adventure_setup(void);
void {n}_store(gameworlds_inventory_put_t,void*);
void {n}_load(gameworlds_inventory_get_t,void*);
void {n}_save_state(void);void {n}_restore_state(void);
uint16_t {n}_check(int32_t,int32_t,uint16_t,uint16_t,game_pickup_callback_t,void*);
'''.format(n=name)
        (d/f'worlds/{name}/world_api.h').write_text(head)
        decls.append(f'#include "worlds/{name}/world_api.h"')
        records.append('''{{.name="{n}",.assets_init={n}_assets_init,.assets_shutdown={n}_assets_shutdown,
         .objects_init={n}_objects_init,.objects_update={n}_objects_update,.objects_draw={n}_objects_draw,
         .assets_foreground={n}_fg,.assets_background={n}_bg,.assets_show_background={n}_show_bg,
         .adventure_setup={n}_adventure_setup,.inventory_store={n}_store,.inventory_load={n}_load,
         .world_state_save={n}_save_state,.world_state_restore={n}_restore_state,.check={n}_check}}'''.format(n=name))
    world=(sdk/'gameworlds.rulec').read_text().replace('@IDE{WORLD_DECLARATIONS}','\n'.join(decls)).replace('@IDE{WORLD_RECORDS}',',\n'.join(records))
    world=render(world,flags)
    assert '@IDE' not in world
    (d/'gameworlds.c').write_text(world)
    (d/'test.c').write_text('''#include "gameworlds.h"
#include "gameadventureruntime.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
static unsigned inv[2];static int activeWorld;
static uint8_t w1Remember=0;
static game_collectable_t coin={.kind=1,.value=100,.tracking_configured=1,
  .show_in_inventory=1,.show_in_hud=1,.persistent=1,.active=1};
void music_stop(void){}
void game_adventure_start(const void*a,int b,const void*c,int d,const void*e,int f,
    const void*g,int h,int i,int j,const void*k,int l,const void*m,const void*n){
 (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h;(void)i;(void)j;(void)k;(void)l;(void)m;(void)n;
}
uint16_t game_adventure_collect_amount(uint16_t kind,uint16_t n){
 assert(kind==1);inv[activeWorld]+=n;return 1;
}
uint8_t game_adventure_pickup_quantity(uint16_t kind,uint32_t *out){
 if(kind!=1)return 0;
 *out=inv[activeWorld];
 return 1;
}
void game_adventure_managed_pickup_begin(uint16_t kind){(void)kind;}
void game_adventure_managed_pickup_end(void){}
#define WORLD_DEF(N,I) \\
int N##_assets_init(void){return 1;} \\
void N##_assets_shutdown(void){} \\
uint8_t N##_objects_init(void){return 1;} \\
void N##_objects_update(uint16_t n){(void)n;} \\
void N##_objects_draw(int32_t x,int32_t y){(void)x;(void)y;} \\
void N##_fg(void){}void N##_bg(void){}void N##_show_bg(void){} \\
void N##_adventure_setup(void){activeWorld=I;inv[I]=0;} \\
void N##_store(gameworlds_inventory_put_t f,void*u){f("Coins",(uint16_t)inv[I],u);} \\
void N##_load(gameworlds_inventory_get_t f,void*u){uint32_t n=f("Coins",u);if(n!=UINT32_MAX)inv[I]=n;}
WORLD_DEF(world1,0)
WORLD_DEF(world2,1)
void world1_save_state(void){w1Remember=!coin.active;}
void world1_restore_state(void){if(w1Remember)coin.active=0;}
void world2_save_state(void){}
void world2_restore_state(void){}
uint16_t world1_check(int32_t x,int32_t y,uint16_t w,uint16_t h,game_pickup_callback_t cb,void*user){
 (void)x;(void)y;(void)w;(void)h;if(!coin.active)return 0;coin.active=0;cb(&coin,user);return 1;
}
uint16_t world2_check(int32_t x,int32_t y,uint16_t w,uint16_t h,game_pickup_callback_t cb,void*user){
 (void)x;(void)y;(void)w;(void)h;(void)cb;(void)user;return 0;
}
int main(void){
 assert(gameworlds_start("world1"));
 assert(gameworlds_check(0,0,16,16,0,0)==1);
 assert(inv[0]==1 && gameworlds_hud_total(1)==1);
 /* Inventory-linked HUD reflects USE/DROP/DESTROY/TURN-IN, not lifetime pickups. */
 inv[0]=0;assert(gameworlds_hud_total(1)==0);
 inv[0]=3;assert(gameworlds_hud_total(1)==3);
 inv[0]=1;assert(gameworlds_hud_total(1)==1);
 assert(gameworlds_start("world2"));
 assert(inv[1]==1 && gameworlds_hud_total(1)==1);
 assert(gameworlds_start("world1"));
 assert(inv[0]==1 && gameworlds_hud_total(1)==1 && !coin.active);
 assert(gameworlds_check(0,0,16,16,0,0)==0);
 gameworlds_shutdown();assert(gameworlds_hud_total(1)==0);
 puts("PASS HUD follows inventory removals/restoration across two worlds + collected state");
 return 0;
}
''')
    cmd=['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(d),str(d/'gameworlds.c'),str(d/'test.c'),'-o',str(d/'test')]
    run=subprocess.run(cmd,capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    run=subprocess.run([str(d/'test')],capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    print(run.stdout.strip())
