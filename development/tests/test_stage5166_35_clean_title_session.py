#!/usr/bin/env python3
"""Stage 5.166.35: an authoritative title start/slot, never stale state."""
from pathlib import Path
import re, subprocess, tempfile
root=Path(__file__).resolve().parents[2]
source=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
header=(root/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
assert 'gw_reset_title_session();' in source
assert 'const int8_t selected_slot=gametitle_load_slot();' in source
assert 'gameworlds_request_at(title_world,title_start)' in source
assert 'worlds[fresh_world_index].name' not in source
assert 'gw_bound_world_player->hurt_anim_active=0u;' in source
assert 'gw_bound_world_player->hurt_ticks_remaining=0u;' in source
assert 'if(p)gw_bound_world_player=p;' in source
assert 'player_anim.started=0u;' in main
assert 'PLAYER_ANIM_STATE_IDLE,player_anim_facing,0u' in main

def render(src,flags):
    out=[]; stack=[]; active=True
    for raw in src.splitlines():
        m=re.fullmatch(r'\s*@IDE_IF\{([A-Z_][A-Z0-9_]*)\}\s*',raw)
        if m:
            assert m[1] in flags,m[1]
            stack.append((active,flags[m[1]]));active=active and flags[m[1]]
        elif raw.strip()=='@IDE_ELSE':
            parent,enabled=stack[-1];active=parent and not enabled
        elif raw.strip()=='@IDE_END':
            active=stack.pop()[0]
        elif active:out.append(raw)
    assert not stack
    return '\n'.join(out)+'\n'
quest='''#define GW_QUEST_COUNT 0u
#define GW_OBJECTIVE_COUNT 0u
typedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;
typedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;
static const gw_quest_def_t gw_quest_defs[]={{0}};
static const gw_objective_def_t gw_objective_defs[]={{0}};'''
decls='''static int remote_clears;
static void reset_remote(void){++remote_clears;}
static void bg(void){}
static int init(void){return 1;}
static void close_assets(void){}
static uint8_t init_objects(void){return 1;}
static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);
static const gameworlds_named_spawn_t camp[]={{"camp",222,88,0,0,0,0,0}};
static const gameworlds_named_spawn_t gate[]={{"gate",333,77,1,0,0,0,0}};
'''
records=','.join('''{.name="%s",.assets_init=init,.assets_shutdown=close_assets,
.objects_init=init_objects,.assets_show_background=bg,.start_x=%d,.start_y=20,.start_facing=1,
.named_spawns=%s,.named_spawn_count=1,.object_remote_reset=reset_remote,.npc_remote_reset=reset_remote,
.object_disk_export=fake_save,.story_disk_export=fake_save,.object_disk_import=fake_import,.story_disk_import=fake_import}'''
%(name,x,spawn) for name,x,spawn in [('forest',40,'gate'),('world1',10,'camp')])
native=(root/'development/tests/test_stage5164_save_load_native.c').read_text()
native=native[:native.index('int main(void)')].replace('#include "gameworlds.c"','#undef music_stop\n#define music_stop() ((void)0)\n#include "gameworlds.c"')
for has_title,has_physics in ((True,False),(False,False),(True,True)):
    flags={n:False for n in ['HAS_WORLD_PHYSICS','HAS_PICKUPS','HAS_SHARED_PLAYER','HAS_PLAYER_VISIBILITY','HAS_ADVENTURE_RUNTIME']}
    flags['HAS_TITLE']=has_title
    flags['HAS_MAP']=False
    flags['HAS_WORLD_PHYSICS']=has_physics
    c=render(source,flags).replace('@IDE{WORLD_DECLARATIONS}',decls).replace('@IDE{WORLD_RECORDS}',records).replace('@IDE{SAVE_KEY}','123').replace('@IDE{SAVE_IDENTITY}', '0x0123456789abcdef').replace('@IDE{QUEST_DATA}',quest)
    h=render(header,flags)
    assert '@IDE{' not in c and '@IDE{' not in h
    with tempfile.TemporaryDirectory(prefix='stage16635_') as d:
        d=Path(d)
        (d/'gameworlds.c').write_text(c)
        (d/'gameworlds.h').write_text(h)
        if has_physics:
            (d/'gameworldobjects.h').write_text('''#ifndef MOCK_GAMEWORLDOBJECTS_H
#define MOCK_GAMEWORLDOBJECTS_H
#include <stdint.h>
typedef struct {
uint16_t hurt_damage_this_frame; int32_t hurt_stat_delta; uint8_t hurt_stat_target;
const char *hurt_stat_name,*hurt_death_note; uint8_t hurt_triggered,hurt_anim_active,
hurt_flash_active,hurt_flash_colour,hurt_flash_frames;
uint16_t hurt_ticks_remaining,hurt_elapsed;
int32_t spring_x100,spring_remainder_x100;uint8_t spring_sliding,break_stomp_armed;
} game_world_player_t;
#endif
''')
        (d/'gametitle.h').write_text('#include <stdint.h>\nuint8_t gametitle_run(const char **world,const char **start);\nint8_t gametitle_load_slot(void);\n')
        harness=native+'''
static int8_t load_choice=-1;
static int new_choice;
static unsigned calls;
uint8_t gametitle_run(const char **world,const char **start){
    ++calls;
    if(new_choice==0){*world="world1";*start="camp";}
    else {*world="forest";*start="gate";}
    return 1;
}
int8_t gametitle_load_slot(void){return load_choice;}
int main(void){
    mock_api.system=&systems;
    (void)mkdir(TEST_FS_ROOT,0700);(void)mkdir(TEST_FS_ROOT "/game",0700);
    gameworlds_fresh_start_enable(1u);
    assert(gameworlds_start("world1"));
    assert(gameworlds_save_slot(3u));
#if HAS_PHYSICS
    game_world_player_t world_player={0};
    world_player.hurt_anim_active=1u;
    world_player.hurt_ticks_remaining=200u;
    world_player.hurt_triggered=1u;
    gameworlds_before(&world_player);
#endif
    persistent.health=88;fake_data=88;
    assert(gameworlds_save_slot(3u));
#if HAS_PHYSICS
    /* In-game defeat FIRE1 must also clear Hurt while restoring the slot. */
    assert(gameworlds_reload_request(3u));
    assert(gameworlds_apply_pending());
    assert(!world_player.hurt_anim_active && !world_player.hurt_ticks_remaining);
    world_player.hurt_anim_active=1u;
    world_player.hurt_ticks_remaining=120u;
#endif
    assert(gameworlds_request_at("forest","gate"));
    assert(gameworlds_apply_pending());
    assert(strcmp(gameworlds_active(),"forest")==0);
    persistent.health=0;fake_data=999;
#if TITLE_ON
    assert(gameworlds_title_request());
    assert(gameworlds_apply_pending());
    gameworlds_spawn_t where={0};
    assert(strcmp(gameworlds_active(),"world1")==0);
#if HAS_PHYSICS
    assert(!world_player.hurt_anim_active && !world_player.hurt_ticks_remaining && !world_player.hurt_triggered);
#endif
    assert(gameworlds_player_start(&where) && where.x==222 && where.y==88 && where.facing==0);
    assert(!saved_position_valid && !gw_session_can_reload);
    assert(persistent.health==0 && inventory_count==0);
    assert(gw_last_save_slot==255u && remote_clears>=4);
    assert(strcmp(active_spawn_id,"camp")==0);
    assert(pending_world==NULL && pending_title_load_slot==0 && !pending_has_exit);
    /* Die in world1, start title's alternate forest spawn. */
    assert(gameworlds_request_at("forest","gate"));assert(gameworlds_apply_pending());
    new_choice=1;assert(gameworlds_title_request());assert(gameworlds_apply_pending());
    assert(strcmp(gameworlds_active(),"forest")==0);
    assert(gameworlds_player_start(&where) && where.x==333 && where.y==77);
    assert(!gw_session_can_reload);
    /* Save loading must ignore the New Game target and use disk's World1. */
    load_choice=3;
    assert(gameworlds_title_request());assert(gameworlds_apply_pending());
    assert(strcmp(gameworlds_active(),"world1")==0);
    assert(gameworlds_player_start(&where) && where.x==10 && where.y==20);
    assert(persistent.health==88 && fake_data==88);
    assert(gw_session_can_reload && gw_last_save_slot==3u);
    /* Return from LOADED game, switch back to New Game: no old save state. */
    load_choice=-1;new_choice=0;
    assert(gameworlds_title_request());assert(gameworlds_apply_pending());
    assert(gameworlds_player_start(&where) && where.x==222 && where.y==88);
    assert(persistent.health==0 && !gw_session_can_reload);
    assert(gw_last_save_slot==255u);
    assert(calls==4);
#else
    assert(!gameworlds_title_request());
#endif
    gameworlds_shutdown();
    puts("PASS Stage 5.166.35: title New/Load authoritative session boundaries");
}
'''
        (d/'test.c').write_text('#define TITLE_ON %d\n#define HAS_PHYSICS %d\n'%(int(has_title),int(has_physics))+harness)
        cmd=['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Wno-unused-function','-Wno-unused-variable','-Wno-type-limits','-ffunction-sections','-fdata-sections','-Wl,--gc-sections','-I',str(d),'-I',str(root/'idelibs/api'),'-I',str(root/'idelibs/codehelpers/game'),f'-DTEST_FS_ROOT="{d}/fs"',str(d/'test.c'),'-o',str(d/'test')]
        subprocess.run(cmd,check=True)
        subprocess.run([str(d/'test')],check=True)
print('PASS Stage 5.166.35: both title configurations and generated source checks')
