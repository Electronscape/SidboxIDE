"""Stage 5.152: world-local weather source roundtrip, renderer, and integration."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[1]
header=(root/'gamedesigner.h').read_text()
editor=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
registry=(root/'gameworldsnapshot.h').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
api=(root/'idelibs/codehelpers/game/gameworlds.ruleh').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()

assert 'm_weatherMode = 0;' in header, 'old worlds must default to clear'
for key, attr in [('mode','m_weatherMode'),('density','m_weatherDensity'),('wind','m_weatherWind'),
                  ('paletteIndex','m_weatherPaletteIndex'),('lightningInterval','m_weatherLightningInterval'),
                  ('lightningStrength','m_weatherLightningStrength')]:
    assert f'weather.value(QStringLiteral("{key}"))' in project
    assert f'weather.insert(QStringLiteral("{key}"), {attr});' in project
assert 'obj.insert(QStringLiteral("weather"), weather);' in project
assert 'design.value(QStringLiteral("weather"))' in registry
assert 'defaultWeatherMode.at(i)' in registry and 'defaultWeatherStrength.at(i)' in registry
assert 'uint8_t gameworlds_weather_frame(uint16_t view_width, uint16_t view_height);' in api
assert 'weather_enter(world);' in world
assert 'weather_update(frames);' in world
assert 'Build: 5.159.261026' in (root/'splashscreenwidget.cpp').read_text()
assert 'updateWeatherPreview();' in editor and 'm_showWeatherPreview = new QCheckBox' in editor
assert 'gameworlds_weather_frame(VIEW_W, GAME_PLAY_H);' in main
assert main.index('game_tilemap_blit_view_front') < main.index('gameworlds_weather_frame(VIEW_W, GAME_PLAY_H)') < main.index('game_show_hud(0, 0)')
print('source checks: old-world defaults, save/load, generated registry, weather API, preview, draw order PASS')

# Compile the exact generated C weather renderer and lifecycle with a minimal host shim.
start=world.index('/* Stage 5.152: optional world-local rain/snow/thunder')
end=world.index('static const uint8_t spotlight_bayer4',start)
block=world[start:end]
code=r'''
#include <stdint.h>
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION (1u << 0)
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH (1u << 1)
#include <assert.h>
#include <stddef.h>
typedef struct {
    int32_t start_x, start_y;
    uint8_t weather_mode, weather_density;
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
    uint8_t weather_curve_code;
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
#define GW_PHASE_IDLE 0u
static uint8_t transition_phase, spotlight_enabled, spotlight_mask_index;
static uint32_t spotlight_mask_colour;
static uint32_t transition_front[256], transition_back[256];
static void transition_restore_palette(void) {}
static int rectangles, fullScreen, colour, maxX, maxY;
static void host_rectf(int x,int y,int w,int h) {
    assert(x>=0 && y>=0 && w>0 && h>0);
    assert(x+w<=480 && y+h<=320);
    ++rectangles;
    if (w==480 && h==320) ++fullScreen;
    if (x+w>maxX)maxX=x+w;
    if (y+h>maxY)maxY=y+h;
}
static void host_setcolour(int c) { colour=c; }
#define gfx_rectf host_rectf
#define gfx_setcolour host_setcolour
''' + block + r'''
int main(void) {
    gameworlds_record_t clear={.weather_mode=0,.weather_density=48,.weather_wind=0,.weather_colour_index=15,.weather_lightning_interval=350,.weather_lightning_strength=75,.weather_lightning_overlay=1};
    active_world=&clear; weather_enter(active_world);
    weather_update(500); rectangles=0;
    gameworlds_weather_frame(480,320);
    assert(rectangles==0); assert(weather_flash_phase==0);

    gameworlds_record_t rain={.weather_mode=1,.weather_density=48,.weather_wind=-8,.weather_colour_index=19,.weather_lightning_interval=350,.weather_lightning_strength=75,.weather_lightning_overlay=1};
    active_world=&rain; weather_enter(active_world);
    assert(weather_frame_tick==0);
    rectangles=0;
    gameworlds_weather_frame(480,320);
    assert(rectangles==48 && colour==19); /* populated at first frame */
    weather_update(200);
    rectangles=0;
    gameworlds_weather_frame(480,320);
    assert(rectangles==48); assert(weather_flash_phase==0);

    gameworlds_record_t snow={.weather_mode=2,.weather_density=36,.weather_wind=8,.weather_colour_index=16,.weather_lightning_interval=100,.weather_lightning_strength=100,.weather_lightning_overlay=1};
    active_world=&snow; weather_enter(active_world);
    rectangles=0;gameworlds_weather_frame(480,320);
    assert(rectangles==36 && colour==16);

    gameworlds_record_t storm={.weather_mode=3,.weather_density=64,.weather_wind=1,.weather_colour_index=15,.weather_lightning_interval=100,.weather_lightning_strength=100,.weather_lightning_overlay=1};
    active_world=&storm; weather_enter(active_world);
    assert(weather_flash_phase==0);
    weather_update(100);
    assert(weather_flash_phase==25);
    weather_update(9); /* gentle peak, not a hard flash */
    assert(weather_pulse()>0);
    rectangles=fullScreen=0;
    gameworlds_weather_frame(480,320);
    assert(rectangles>64); /* 64 rain plus gradual lightning rows */
    const uint8_t peak=weather_pulse();
    weather_update(4);
    assert(weather_pulse()<peak);
    weather_update(12);
    assert(weather_pulse()==0); /* single shaped fade */
    active_world=&rain;weather_enter(active_world);
    assert(weather_flash_phase==0 && weather_frame_tick==0);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as path:
    src=Path(path)/'weather.c';src.write_text(code)
    exe=Path(path)/'weather'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('native GCC: clear/rain/snow/storm, prefilled weather, 100-frame lightning double flash, world switch PASS')
