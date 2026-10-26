"""Stage 5.154: named weather status and optional lightning/spotlight coupling."""
from pathlib import Path
import re
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
editor = (root/'gamedesigner.cpp').read_text()
header = (root/'gamedesigner.h').read_text()
project = (root/'gamedesigner_project.cpp').read_text()
registry = (root/'gameworldsnapshot.h').read_text()
world = (root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
api = (root/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
main = (root/'idelibs/codehelpers/game/maingame.rulec').read_text()

assert 'm_weatherSuspendSpotlight = false' in header
assert 'weather.value(QStringLiteral("suspendSpotlightOnLightning")).toBool(false)' in project
assert 'weather.insert(QStringLiteral("suspendSpotlightOnLightning"), m_weatherSuspendSpotlight);' in project
assert 'defaultWeatherSuspendSpotlight.at(i)' in registry
assert 'Suspend spotlight during lightning flashes' in editor
assert 'weatherSuspendSpotlight->setEnabled(mode == 3)' in editor
assert 'weather_suspend_spotlight' in world
assert '#define GAME_WEATHER_STATUS_LIGHTNING_FLASH' in api
assert '#define GAME_WEATHER_STATUS_PRECIPITATION' in api
assert 'uint8_t gameworlds_weather_status(void);' in api
assert 'uint8_t gameworlds_weather_frame(uint16_t view_width, uint16_t view_height);' in api
assert 'effective_spotlight_opacity = (uint8_t)((uint16_t)spotlight_opacity *' in world
assert 'gameworlds_spotlight_frame(VIEW_W, GAME_PLAY_H);' in main
assert main.index('gameworlds_spotlight_frame(VIEW_W, GAME_PLAY_H);') < main.index('gameworlds_weather_frame(VIEW_W, GAME_PLAY_H);')
assert 'Build: 5.158.261026' in (root/'splashscreenwidget.cpp').read_text()
print('source: opt-in UI + .sbgm read/write + registry export + named API + no main.c changes PASS')

begin = world.index('/* Stage 5.152: optional world-local rain/snow/thunder')
end = world.index('static const uint8_t spotlight_bayer4', begin)
weather_block = world[begin:end]
start = world.index('void gameworlds_spotlight_frame(uint16_t width, uint16_t height)')
finish = world.index('void gameworlds_transition_frame(uint16_t width, uint16_t height)', start)
spotlight = world[start:finish]
spotlight = re.sub(r'@IDE_IF\{HAS_SHARED_PLAYER\}\n.*?@IDE_END\n', '', spotlight, count=1, flags=re.S)
assert '@IDE' not in spotlight, 'unexpected generator branch in spotlight'

code = r'''
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION (1u<<0)
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH (1u<<1)
#define GW_PHASE_IDLE 0u
static uint8_t transition_phase, spotlight_enabled, spotlight_mask_index;
static uint32_t spotlight_mask_colour;
static uint32_t transition_front[256], transition_back[256];
static uint8_t spotlight_opacity = 100u, spotlight_stable_dither;
static uint16_t spotlight_radius = 48u;
static uint8_t spotlight_feather_current;
static int16_t spotlight_offset_x, spotlight_offset_y;
static int32_t spotlight_player_x, spotlight_player_y, spotlight_camera_x, spotlight_camera_y;
static int darkness_segments;
static uint16_t last_darkness_opacity;
static void spotlight_animation_tick(void) {}
static void spotlight_palette_copy(const uint32_t *pal) { (void)pal; }
static void spotlight_dither_segment(int32_t x1,int32_t x2,int32_t y,uint16_t opacity) {
    (void)x1;(void)x2;(void)y; last_darkness_opacity=opacity; ++darkness_segments;
}
static uint32_t transition_isqrt(uint32_t value) { (void)value; return 10u; }
static void transition_restore_palette(void) {}
typedef struct {
    int32_t start_x,start_y;
    uint8_t weather_mode,weather_density;
    int8_t weather_wind;
    uint8_t weather_colour_index;
    uint16_t weather_lightning_interval;
    uint8_t weather_lightning_strength;
    uint8_t weather_palette_flash_strength;
    uint8_t weather_suspend_spotlight;
    uint8_t weather_lightning_overlay;
    const uint32_t *(*front_palette)(void);
    const uint32_t *(*back_palette)(void);
    uint8_t day_night_mode;
    uint32_t day_night_colour;
    uint8_t day_night_strength;
    uint16_t day_night_day_frames, day_night_night_frames, day_night_fade_frames;
    uint8_t day_night_start_at_night;
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
static void mock_rectf(int x,int y,int w,int h) { (void)x;(void)y;(void)w;(void)h; }
static void mock_setcolour(int colour) { (void)colour; }
#define gfx_rectf mock_rectf
#define gfx_setcolour mock_setcolour
''' + weather_block + spotlight + r'''
int main(void) {
    gameworlds_record_t clear = {.weather_mode=0};
    gameworlds_record_t storm = {.weather_mode=3, .weather_density=8,
        .weather_colour_index=15, .weather_lightning_interval=100,
        .weather_lightning_strength=75, .weather_suspend_spotlight=1,
        .weather_lightning_overlay=1};
    gameworlds_record_t storm_manual = {.weather_mode=3, .weather_density=8,
        .weather_colour_index=15, .weather_lightning_interval=100,
        .weather_lightning_strength=75, .weather_suspend_spotlight=0,
        .weather_lightning_overlay=1};
    gameworlds_record_t rain = {.weather_mode=1, .weather_density=8,
        .weather_colour_index=15, .weather_lightning_interval=100};
    assert(gameworlds_weather_status() == GAME_WEATHER_STATUS_NONE);
    active_world=&clear; weather_enter(active_world);
    assert(gameworlds_weather_frame(480,320) == GAME_WEATHER_STATUS_NONE);
    active_world=&rain; weather_enter(active_world);
    assert(gameworlds_weather_status() == GAME_WEATHER_STATUS_PRECIPITATION);
    assert(gameworlds_weather_frame(480,320) == GAME_WEATHER_STATUS_PRECIPITATION);
    spotlight_enabled=1;
    gameworlds_spotlight_frame(480,320);
    assert(darkness_segments>0);  /* Normal weather preserves spotlight. */

    active_world=&storm; weather_enter(active_world);
    weather_update(109); /* Gradual lightning envelope near peak. */
    assert(weather_flash_phase == 16u);
    assert(gameworlds_weather_status() ==
        (GAME_WEATHER_STATUS_PRECIPITATION | GAME_WEATHER_STATUS_LIGHTNING_FLASH));
    darkness_segments=0;
    gameworlds_spotlight_frame(480,320);
    assert(darkness_segments==0 || last_darkness_opacity < 100u); /* Soft fade, not binary. */
    assert(spotlight_enabled==1); /* Never flip the spotlight state. */
    assert(gameworlds_weather_frame(480,320)==gameworlds_weather_status());
    const uint8_t peak = weather_pulse();
    weather_update(4); /* Smoothly decaying, no dark gap/double pulse. */
    assert(weather_pulse() < peak && weather_pulse() > 0);
    darkness_segments=0;
    gameworlds_spotlight_frame(480,320);
    assert(darkness_segments>0 && last_darkness_opacity < 100u); /* Lightning gradually lightens. */
    weather_update(12); /* Fade finishes. */
    assert(gameworlds_weather_status() == GAME_WEATHER_STATUS_PRECIPITATION);
    darkness_segments=0;
    gameworlds_spotlight_frame(480,320);
    assert(darkness_segments>0 && last_darkness_opacity==100u); /* Darkness returns gradually. */

    active_world=&storm_manual; weather_enter(active_world);
    weather_update(109);
    assert(gameworlds_weather_status() & GAME_WEATHER_STATUS_LIGHTNING_FLASH);
    darkness_segments=0;
    gameworlds_spotlight_frame(480,320);
    assert(darkness_segments>0 && last_darkness_opacity==100u); /* Opt-out full darkness. */

    active_world=&rain; weather_enter(active_world);
    assert(!(gameworlds_weather_status() & GAME_WEATHER_STATUS_LIGHTNING_FLASH));
    darkness_segments=0;
    gameworlds_spotlight_frame(480,320);
    assert(darkness_segments>0); /* Old world reset/normal rain. */
    return 0;
}
'''
with tempfile.TemporaryDirectory() as folder:
    source = Path(folder)/'test.c'
    source.write_text(code)
    exe=Path(folder)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(source),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('native GCC: pulse status, soft lightning decline, proportional spotlight dim/restore, opt-out, world reset PASS')
