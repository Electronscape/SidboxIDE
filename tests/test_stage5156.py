"""Stage 5.156: independent dialogue-paused gameplay, ambient particles, weather."""
from pathlib import Path
import subprocess
import tempfile
import re

root = Path(__file__).resolve().parents[1]
world = (root / 'idelibs/codehelpers/game/gameworlds.rulec').read_text()
world_h = (root / 'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
item = (root / 'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
item_h = (root / 'idelibs/codehelpers/game/gameworlditems.ruleh').read_text()
main = (root / 'idelibs/codehelpers/game/maingame.rulec').read_text()
registry = (root / 'gameworldsnapshot.h').read_text()

for name in ('gameplay', 'particles', 'weather'):
    assert f'void gameworlds_update_{name}(uint16_t frames)' in world
    assert f'void gameworlds_update_{name}(uint16_t frames);' in world_h
    assert f'void game_update_{name}(uint16_t frames)' in world
    assert f'void game_update_{name}(uint16_t frames);' in world_h

for name in ('gameplay', 'particles'):
    assert f'void gameworlditems_update_{name}(uint16_t frames)' in item
    assert f'void gameworlditems_update_{name}(uint16_t frames);' in item_h
    assert f'gameworlditems_update_{name}' in registry

assert 'void gameworlditems_update(uint16_t frames)\n{\n    gameworlditems_update_gameplay(frames);\n    gameworlditems_update_particles(frames);\n}' in item
assert '@IDE{UPDATE_BODY}\n}' in item
assert 'cg_particle_update(frames);' in item[item.index('void gameworlditems_update_particles('):]
assert 'if (active_world->objects_update_gameplay)' in world
assert 'else if (active_world->objects_update)' in world
assert 'if (active_world && active_world->objects_update_particles)' in world
assert 'objectsGameplay, objectsParticles' in registry
assert '"     %2gameworlditems_init, %2gameworlditems_update, %3, %4,' in registry
assert 'Build: 5.159.261026' in (root/'splashscreenwidget.cpp').read_text()

# Main template must tick visual effects outside the Adventure-dialogue guard,
# and gameplay only after the guard. Also preserve the transition guard.
position = main.index('if (!gameworlds_transition_busy()) {')
weather_at = main.index('game_update_weather(1);',position)
particle_at = main.index('game_update_particles(1);',position)
dialogue_at = main.index('if (!game_adventure_open()) {',position)
gameplay_at = main.index('gameworlds_update_gameplay(1);',dialogue_at)
assert position < weather_at < dialogue_at < gameplay_at
assert position < particle_at < dialogue_at
assert '        gameworlds_update(1);' not in main
print('source checks: published registry, aliases, generated main and compatible update OK')

# Compile the REAL world-manager dispatcher extracted from the template.
start = world.index('void gameworlds_update_gameplay(uint16_t frames)')
end = world.index('void gameworlds_draw(int32_t x, int32_t y)', start)
dispatch = world[start:end]
assert '@IDE' not in dispatch
harness = r'''
#include <stdint.h>
#include <assert.h>
#include <stddef.h>
typedef struct {
    void (*objects_update)(uint16_t);
    void (*objects_update_gameplay)(uint16_t);
    void (*objects_update_particles)(uint16_t);
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
static uint32_t gameplay_ticks, particle_ticks, weather_ticks, legacy_ticks;
static void tick_gameplay(uint16_t n) { gameplay_ticks += n; }
static void tick_particles(uint16_t n) { particle_ticks += n; }
static void tick_legacy(uint16_t n) { legacy_ticks += n; gameplay_ticks += n; particle_ticks += n; }
static void weather_update(uint16_t n) { weather_ticks += n; }
''' + dispatch + r'''
int main(void) {
    const gameworlds_record_t new_world = {tick_legacy, tick_gameplay, tick_particles};
    const gameworlds_record_t old_world = {tick_legacy, NULL, NULL};
    // With no world active none of the three visual/gameplay clocks changes.
    game_update_weather(1); game_update_particles(1); game_update_gameplay(1);
    assert(gameplay_ticks==0 && particle_ticks==0 && weather_ticks==0);
    active_world = &new_world;
    // Simulated 30-frame dialogue: only the weather and ambient sprites tick.
    for (int i=0;i<30;++i) { game_update_weather(1); game_update_particles(1); }
    assert(gameplay_ticks==0 && particle_ticks==30 && weather_ticks==30 && legacy_ticks==0);
    // Afterwards, the pause ends. All three clocks move once per frame.
    for (int i=0;i<10;++i) {
        gameworlds_update_gameplay(1);
        gameworlds_update_particles(1);
        gameworlds_update_weather(1);
    }
    assert(gameplay_ticks==10 && particle_ticks==40 && weather_ticks==40 && legacy_ticks==0);
    // The older combined call remains identical (no double-ticks).
    gameworlds_update(1);
    assert(gameplay_ticks==11 && particle_ticks==41 && weather_ticks==41 && legacy_ticks==1);
    // Older published world falls back to its combined updater; the separate
    // particles updater does not repeat the particle physics without its API.
    active_world = &old_world;
    gameworlds_update_gameplay(1);
    gameworlds_update_particles(1);
    gameworlds_update_weather(1);
    assert(gameplay_ticks==12 && particle_ticks==42 && weather_ticks==42 && legacy_ticks==2);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as folder:
    src = Path(folder)/'test.c'; src.write_text(harness)
    exe = Path(folder)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('native GCC: dialogue effects continue; enemies pause; legacy combined and old-world fallback PASS')

# Compile the actual generated world-item wrappers with particles enabled
# and disabled to catch conditional compilation and double ticking.
functions = item[item.index('void gameworlditems_update_particles(uint16_t frames)'):item.index('@IDE_IF{HAS_TILEMAP_WORLDS}',item.index('void gameworlditems_update_particles(uint16_t frames)'))]
pre, conditional = functions.split('@IDE_IF{HAS_PARTICLE_EMITTERS}\n', 1)
if_enabled, conditional = conditional.split('@IDE_ELSE\n', 1)
if_disabled, post = conditional.split('@IDE_END\n', 1)
for enabled in (True, False):
    functions_c = pre + (if_enabled if enabled else if_disabled) + post
    assert '@IDE' not in functions_c
    particle_stub = ('static void cg_particle_update(uint16_t n) { particle_ticks += n; }\n'
                     if enabled else '')
    unit = r'''
#include <stdint.h>
#include <assert.h>
static uint32_t gameplay_ticks, particle_ticks;
static void gameworlditems_update_gameplay(uint16_t n) { gameplay_ticks += n; }
''' + particle_stub + functions_c + r'''
int main(void) {
    gameworlditems_update_gameplay(3);
    gameworlditems_update_particles(2);
    assert(gameplay_ticks == 3);
''' + ('    assert(particle_ticks == 2);\n' if enabled else '    assert(particle_ticks == 0);\n') + r'''
    gameworlditems_update(4);
    assert(gameplay_ticks == 7);
''' + ('    assert(particle_ticks == 6);\n' if enabled else '    assert(particle_ticks == 0);\n') + r'''
    return 0;
}
'''
    with tempfile.TemporaryDirectory() as folder:
        src=Path(folder)/'items.c'; src.write_text(unit)
        exe=Path(folder)/'items'
        subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('native GCC: generated item split/legacy wrapper for emitter and empty world PASS')
