#!/usr/bin/env python3
"""Stage 5.37: compiled world-manager pickup routing + HUD counter tests (host GCC)."""
from pathlib import Path
import re, subprocess, tempfile
root=Path(__file__).resolve().parents[2]
sdk=root/'idelibs/codehelpers/game'
def render(src, flags):
    out=[]; enabled=[True]
    for line in src.splitlines(keepends=True):
        m=re.fullmatch(r'@IDE_IF\{([A-Z_]+)\}\n?',line)
        if m:
            assert m.group(1) in flags, m.group(1)
            enabled.append(enabled[-1] and flags[m.group(1)])
        elif line.strip() == '@IDE_ELSE':
            raise AssertionError('Unexpected ELSE in world template')
        elif line.strip() == '@IDE_END':
            assert len(enabled)>1
            enabled.pop()
        elif enabled[-1]:out.append(line)
    assert len(enabled)==1
    return ''.join(out)
with tempfile.TemporaryDirectory(prefix='stage537-pickups-') as temp:
    out=Path(temp); (out/'worlds/world1').mkdir(parents=True)
    (out/'gamecollectables.h').write_text('''#ifndef MOCK_COLLECTABLES_H
#define MOCK_COLLECTABLES_H
#include <stdint.h>
typedef struct {uint16_t kind,value;uint8_t tracking_configured,show_in_inventory,show_in_hud;} game_collectable_t;
typedef void (*game_pickup_callback_t)(game_collectable_t*,void*);
#endif
''')
    (out/'gameadventureruntime.h').write_text('''#include <stdint.h>
uint16_t game_adventure_collect_amount(uint16_t,uint16_t);
uint16_t game_adventure_collect(uint16_t);
uint8_t game_adventure_pickup_quantity(uint16_t,uint32_t*);
void game_adventure_managed_pickup_begin(uint16_t);
void game_adventure_managed_pickup_end(void);
void game_adventure_start(const void*,int,const void*,int,const void*,int,const void*,int,int,int,const void*,int,const void*,const void*);
''')
    (out/'apis.h').write_text('void music_stop(void);\n')
    flags={'HAS_WORLD_PHYSICS':False, 'HAS_PICKUPS':True,'HAS_PLAYER_VISIBILITY':False,'HAS_SHARED_PLAYER':False,'HAS_ADVENTURE_RUNTIME':True}
    (out/'gameworlds.h').write_text(render((sdk/'gameworlds.ruleh').read_text(),flags))
    (out/'worlds/world1/world_api.h').write_text('''#include "../../gameworlds.h"
int w_assets_init(void);void w_assets_shutdown(void);uint8_t w_objects_init(void);
void w_objects_update(uint16_t);void w_objects_draw(int32_t,int32_t);
void w_fg(void);void w_bg(void);void w_show_bg(void);
void w_adventure_setup(void);void w_store(gameworlds_inventory_put_t,void*);void w_load(gameworlds_inventory_get_t,void*);
uint16_t w_check(int32_t,int32_t,uint16_t,uint16_t,game_pickup_callback_t,void*);
''')
    record = (
        '{.name="world1", .assets_init=w_assets_init, .assets_shutdown=w_assets_shutdown, '
        '.objects_init=w_objects_init, .objects_update=w_objects_update, '
        '.objects_draw=w_objects_draw, .assets_foreground=w_fg, '
        '.assets_background=w_bg, .assets_show_background=w_show_bg, '
        '.adventure_setup=w_adventure_setup, .inventory_store=w_store, '
        '.inventory_load=w_load, .check=w_check}'
    )
    world=(sdk/'gameworlds.rulec').read_text().replace('@IDE{WORLD_DECLARATIONS}', '#include "worlds/world1/world_api.h"')
    world=world.replace('@IDE{WORLD_RECORDS}', record)
    world=render(world,flags)
    assert '@IDE' not in world
    (out/'gameworlds.c').write_text(world)
    (out/'test.c').write_text('''#include "gameworlds.h"
#include "gameadventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static game_collectable_t pickup;
static int collected=0, called=0, scope=0;static uint16_t scopekind;
void music_stop(void){}
void game_adventure_start(const void*a,int b,const void*c,int d,const void*e,int f,const void*g,int h,int i,int j,const void*k,int l,const void*m,const void*n)
{(void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h;(void)i;(void)j;(void)k;(void)l;(void)m;(void)n;}
int w_assets_init(void){return 1;}void w_assets_shutdown(void){}
uint8_t w_objects_init(void){return 1;}void w_objects_update(uint16_t f){(void)f;}
void w_objects_draw(int32_t x,int32_t y){(void)x;(void)y;}
void w_fg(void){}void w_bg(void){}void w_show_bg(void){}
void w_adventure_setup(void){}
void w_store(gameworlds_inventory_put_t f,void*u){(void)f;(void)u;}
void w_load(gameworlds_inventory_get_t f,void*u){(void)f;(void)u;}
void game_adventure_managed_pickup_begin(uint16_t k){scope=1;scopekind=k;}
void game_adventure_managed_pickup_end(void){scope=0;}
uint16_t game_adventure_collect_amount(uint16_t kind,uint16_t amount){
  if(kind==1){collected+=amount;return 1;}return 0;
}
uint8_t game_adventure_pickup_quantity(uint16_t kind,uint32_t *owned){
  if(kind!=1) return 0;
  *owned=(uint32_t)collected;
  return 1;
}
uint16_t game_adventure_collect(uint16_t kind){
  return scope && scopekind==kind ? 0 : game_adventure_collect_amount(kind,1);
}
uint16_t w_check(int32_t x,int32_t y,uint16_t w,uint16_t h,game_pickup_callback_t f,void*data){
  (void)x;(void)y;(void)w;(void)h; f(&pickup,data);return 1;
}
static void legacy_callback(game_collectable_t*p,void*user){
  (void)user;called++;game_adventure_collect(p->kind);
}
int main(void){
  assert(gameworlds_start("world1"));
  pickup.kind=1;pickup.value=10;
  pickup.tracking_configured=0;
  gameworlds_check(0,0,16,16,legacy_callback,0);
  assert(collected==1 && gameworlds_hud_total(1)==0 && called==1);
  pickup.tracking_configured=1;pickup.show_in_inventory=1;pickup.show_in_hud=1;
  gameworlds_check(0,0,16,16,legacy_callback,0);
  assert(collected==2 && gameworlds_hud_total(1)==2 && called==2);
  pickup.show_in_inventory=0;pickup.kind=2;
  gameworlds_check(0,0,16,16,legacy_callback,0);
  assert(collected==2 && gameworlds_hud_total(1)==2 && gameworlds_hud_total(2)==1 && called==3);
  pickup.kind=1;
  pickup.show_in_hud=0;pickup.show_in_inventory=1;pickup.value=3;
  gameworlds_check(0,0,16,16,legacy_callback,0);
  assert(collected==3 && gameworlds_hud_total(1)==3 && gameworlds_hud_total(2)==1 && called==4);
  collected-=2;assert(gameworlds_hud_total(1)==1);
  gameworlds_shutdown();assert(gameworlds_hud_total(1)==0);
  puts("Stage 5.38 pickup count independence from reward value: PASS");return 0;
}
''')
    cmd=['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(out),str(out/'gameworlds.c'),str(out/'test.c'),'-o',str(out/'run')]
    proc=subprocess.run(cmd,text=True,capture_output=True)
    assert proc.returncode==0,proc.stderr
    proc=subprocess.run([str(out/'run')],capture_output=True,text=True)
    assert proc.returncode==0,proc.stderr
    print(proc.stdout.strip())
source=(sdk/'tilemap.c').read_text()
assert 'if (hash != expected_hash)' not in source
assert 'hash != checksum' not in source
assert 'hash != cg_map_u32' not in source
assert 'file_width != width || file_height != height || file_length != count' in source
assert 'sfread(0, &trailing, 1u, &got)' in source
assert 'GAME_TILEMAP_MAX_SD_BYTES' in source
editor=(root/'gamedesigner.cpp').read_text()
for name in ['Show in Inventory','Show in HUD (track total)','pickupShowInventory->setChecked','pickupShowHud->setChecked']:
    assert name in editor,name
for key in ['createInventoryDefinition', 'inventoryDefinitions.size() >= 64',
            'item.insert(QStringLiteral("capacity"), 65535)',
            'm_adventure.insert(QStringLiteral("items"), inventoryDefinitions)']:
    assert key in editor,key
project=(root/'gamedesigner_project.cpp').read_text()
for name in ['pickupTrackingConfigured','pickupShowInventory','pickupShowHud']:
    assert project.count(name)>=2,name
print('Stage 5.37 PPB/map header safety + IDE settings: PASS')
