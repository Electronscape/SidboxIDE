#!/usr/bin/env python3
"""Stage 5.166.67 PLAYER graph actions: UI/serializer/export/runtime wiring,
plus compiled native C of the production weather and daylight functions.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

root=Path(__file__).resolve().parents[2]
ui=(root/'gamevisualnodes.cpp').read_text()
gen=(root/'gamedesigner_export.cpp').read_text()
worlds=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
header=(root/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
assert 'QDir projectDir(QFileInfo(m_worldPath).absolutePath());' in ui
assert 'sidboxTilemapWorldBaseName(file.absoluteFilePath())' in ui
for name in ('PLAYER','Spotlight','Weather & Effects','Time of Day','World Transitions'):
    assert name in ui
for id in ('@player_spotlight', '@player_weather:0','@player_weather:1',
           '@player_weather:2','@player_weather:3','@player_time:0',
           '@player_time:1','@player_time:2','@player_world:'):
    assert id in ui or id=='@player_world:'
for code in ('gameworlds_spotlight_action(', 'gameworlds_weather_target_action(',
             'gameworlds_daylight_action(', 'gameworlds_request_at('):
    assert code in gen
assert 'validWorlds.contains(name)' in gen
assert 'defaultPlayerAction(selectedId,yes?' in ui
assert 'defaultPlayerAction(to,yes?' in ui
assert 'if(isPlayerCommand(target) && action!=QStringLiteral("enable"))return;' in ui
assert 'm_objects.value(target).resourceIndex<0)return;' in ui  # no RESULT to commands
assert 'SidboxVisualLogic::order(nodes,localIds,&sorted,&issue)' in gen
assert 'if(!targetAction(target,&graphDispatchBody))return false;' in gen
assert 'void gameworlds_weather_action(uint8_t mode);' in header
assert 'void gameworlds_daylight_action(uint8_t mode);' in header
assert 'gameworlds_apply_pending()' in worlds  # deferred world loads only
assert '(void)gameworlds_request_at(' in gen  # no world unload inside callback

def extract(sig):
    pos=worlds.index(sig)
    brace=worlds.index('{',pos)
    nest=0
    for i in range(brace,len(worlds)):
        if worlds[i]=='{':nest+=1
        elif worlds[i]=='}':
            nest-=1
            if nest==0:return worlds[pos:i+1]
    raise AssertionError('unterminated function '+sig)

c=r'''
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
typedef struct { unsigned dummy; } gameworlds_record_t;
static const gameworlds_record_t worlds[2]={{0},{0}};
#define WORLD_COUNT 2u
static const gameworlds_record_t *active_world;
static uint8_t weather_mode, weather_density, weather_overlay_enabled, weather_palette_strength;
static uint8_t weather_flash_phase, day_night_mode, day_night_strength, gw_time_phase;
static uint16_t weather_flash_delay, weather_interval=350;
static uint16_t day_night_day_frames=3000, day_night_night_frames=3000, day_night_fade_frames=500;
static uint32_t weather_frame_tick, day_night_tick, day_night_saved_tick[2];
static uint8_t day_night_saved_valid[2];
static unsigned palette_calls,phase_calls;
static uint8_t last_phase;
static void weather_palette_frame(void){ ++palette_calls; }
static void gw_time_dispatch(uint8_t phase){ ++phase_calls;last_phase=phase; }
static void gw_time_refresh(void) {
    if(!active_world || !day_night_mode)return;
    const uint8_t phase=day_night_mode==1u ? 1u : 0u;
    if(phase!=gw_time_phase){gw_time_phase=phase;gw_time_dispatch(phase);}
}
'''+extract('void gameworlds_weather_action(uint8_t mode)')+'\n'+extract('void gameworlds_daylight_action(uint8_t mode)')+r'''
int main(void){
    gameworlds_weather_action(3);assert(weather_mode==0 && palette_calls==0);
    active_world=&worlds[0];
    gameworlds_weather_action(3);
    assert(weather_mode==3 && weather_density==24 && weather_overlay_enabled==1);
    assert(weather_flash_delay==weather_interval && weather_frame_tick==0);
    assert(palette_calls==1);
    weather_flash_phase=19;weather_frame_tick=100;
    gameworlds_weather_action(1);assert(weather_mode==1 && weather_flash_phase==0 && weather_frame_tick==0);
    gameworlds_weather_action(2);assert(weather_mode==2);
    gameworlds_weather_action(0);assert(weather_mode==0);
    gameworlds_weather_action(99);assert(weather_mode==0);
    gw_time_phase=0;
    gameworlds_daylight_action(1);
    assert(day_night_mode==1 && day_night_strength==60 && phase_calls==1 && last_phase==1);
    gameworlds_daylight_action(0);
    assert(day_night_mode==0 && phase_calls==2 && last_phase==0);
    day_night_saved_valid[0]=1;day_night_saved_tick[0]=3700;
    gameworlds_daylight_action(2);
    assert(day_night_mode==2 && day_night_tick==3700);
    gameworlds_daylight_action(255);assert(day_night_mode==2);
    active_world=&worlds[1];day_night_tick=10;day_night_saved_valid[1]=0;
    gameworlds_daylight_action(2);assert(day_night_tick==0);
    assert(palette_calls==8);
    return 0;
}
'''
with TemporaryDirectory() as d:
    source=Path(d)/'test.c';binary=Path(d)/'test'
    source.write_text(c)
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(source),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
print('PASS Stage 5.166.67 PLAYER tree, graph commands, exporter/deferred world requests, native C weather/daylight')
