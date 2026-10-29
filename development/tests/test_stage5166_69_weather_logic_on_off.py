#!/usr/bin/env python3
"""Stage 5.166.69: real weather command ON/OFF/Toggle, compatibility, no other regression."""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

root=Path(__file__).resolve().parents[2]
ui=(root/'gamevisualnodes.cpp').read_text()
props=(root/'gamedesigner.cpp').read_text()
gen=(root/'gamedesigner_export.cpp').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
header=(root/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
assert 'void gameworlds_weather_target_action(uint8_t mode, uint8_t action);' in header
assert 'gameworlds_weather_target_action(%1u, %2u)' in gen
assert 'const int action = r.targetAction==QStringLiteral("enable") ? 1 :' in gen
assert 'r.targetAction==QStringLiteral("disable") ? 0 :' in gen
assert 'r.targetAction==QStringLiteral("toggle") ? 2 : -1;' in gen
assert 'bool isWeatherTarget(const QString &id)' in ui
assert 'return isPlayerCommand(id)?QStringLiteral("enable"):ordinary;' in ui
assert 'node.logicNodes.replace(gi,graphNode)' in ui  # stage67 saved wires upgraded in editor
assert 'm_touched.insert(id);m_dirty=true;' in ui
assert 'target.targetAction=QStringLiteral("disable");' in gen  # exporter compatibility
assert gen.count('trueLink.value(QStringLiteral("action")).toString()==QStringLiteral("enable")')==2
# The static validator must restrict time/world, not weather actions.
validator=gen[gen.index('// One target-type contract for *every*'):gen.index('    // Resolve item interactions')]
assert 'r->targetObjectId.startsWith(QStringLiteral("@player_weather:")) ||' not in validator
assert 'link.objectId.startsWith(QStringLiteral("@player_weather:")) ||' not in validator
assert 'id.startsWith(QStringLiteral("@player_weather:")) ||' not in validator
assert 'targetId.startsWith(QStringLiteral("@player_world:"))' in gen
# The node tree must allow a weather action to be changed via right-click.
assert 'if(!isPlayerCommand(target))' in ui
assert 'isPlayerCommand(id)?tr("Runs this PLAYER command' in ui
assert 'id.startsWith(QStringLiteral("@player_time:")) ||' in props
assert 'id.startsWith(QStringLiteral("@player_weather:")) ||\n                               id.startsWith(QStringLiteral("@player_time:"))' not in props
assert 'if(action==QStringLiteral("toggle")' in gen # no toggles on initial sync


def extract(signature):
    p=world.index(signature)
    i=world.index('{',p)
    depth=0
    for j in range(i,len(world)):
        if world[j]=='{':depth+=1
        elif world[j]=='}':
            depth-=1
            if not depth:return world[p:j+1]
    raise RuntimeError(signature)

c=r'''
#include <assert.h>
#include <stdint.h>
static void weather_palette_frame(void);
static uint8_t active_flag, weather_mode, weather_density, weather_overlay_enabled, weather_palette_strength;
static uint8_t weather_flash_phase;
static uint16_t weather_flash_delay, weather_interval=90;
static uint32_t weather_frame_tick;
static uint32_t palette_calls;
static void *active_world;
static void weather_palette_frame(void){++palette_calls;}
'''+extract('void gameworlds_weather_action(uint8_t mode)')+'\n'+extract('void gameworlds_weather_target_action(uint8_t mode, uint8_t action)')+r'''
int main(void) {
    gameworlds_weather_target_action(2,1);assert(weather_mode==0 && palette_calls==0);
    active_world=&active_flag;
    gameworlds_weather_target_action(2,1);assert(weather_mode==2 && weather_density==24);
    const uint32_t c=palette_calls;
    weather_frame_tick=18;
    gameworlds_weather_target_action(2,1);assert(weather_frame_tick==18 && palette_calls==c);
    // TRUE to Snow, FALSE to SAME Snow: the compiler emits 1 and 0.
    gameworlds_weather_target_action(2,0);assert(weather_mode==0);
    gameworlds_weather_target_action(2,1);assert(weather_mode==2);
    // FALSE Snow must not erase a newer Rain command from another Trigger.
    gameworlds_weather_target_action(1,1);assert(weather_mode==1);
    gameworlds_weather_target_action(2,0);assert(weather_mode==1);
    gameworlds_weather_target_action(1,0);assert(weather_mode==0);
    // Direct Toggle: off->snow->off->snow.
    gameworlds_weather_target_action(2,2);assert(weather_mode==2);
    gameworlds_weather_target_action(2,2);assert(weather_mode==0);
    gameworlds_weather_target_action(3,2);assert(weather_mode==3 && weather_overlay_enabled==1);
    gameworlds_weather_target_action(3,2);assert(weather_mode==0);
    gameworlds_weather_target_action(3,1);assert(weather_mode==3);
    gameworlds_weather_target_action(0,1);assert(weather_mode==0);
    gameworlds_weather_target_action(1,1);assert(weather_mode==1);
    gameworlds_weather_target_action(0,2);assert(weather_mode==0);
    const uint32_t before=palette_calls;
    gameworlds_weather_target_action(3,0); // already clear
    gameworlds_weather_target_action(0,0); // Clear's disable is no-op
    gameworlds_weather_target_action(4,1);
    gameworlds_weather_target_action(1,3);
    assert(weather_mode==0 && palette_calls==before);
    return 0;
}
'''
with TemporaryDirectory() as d:
    path=Path(d)/'test.c'; binary=Path(d)/'test'
    path.write_text(c)
    subprocess.run(['cc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(path),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)
print('PASS Stage 5.166.69 weather branch ON/OFF, direct Toggle, idempotence, mode isolation, editor/export compatibility')
