"""Stage 5.153: two-palette lightning blending, old world compatibility, and CLUT restoration."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
editor = (root / 'gamedesigner.cpp').read_text()
header = (root / 'gamedesigner.h').read_text()
project = (root / 'gamedesigner_project.cpp').read_text()
registry = (root / 'gameworldsnapshot.h').read_text()
world = (root / 'idelibs/codehelpers/game/gameworlds.rulec').read_text()

assert 'm_weatherPaletteFlashStrength = 0;' in header
assert 'weather.value(QStringLiteral("paletteFlashStrength")).toInt(0)' in project
assert 'weather.insert(QStringLiteral("paletteFlashStrength"), m_weatherPaletteFlashStrength);' in project
assert 'defaultWeatherPaletteStrength <<' in registry
assert 'defaultWeatherPaletteStrength.at(i)' in registry
assert 'Palette flash strength' in editor
assert 'weatherPaletteSlider->setRange(0, 100);' in editor
assert 'm_weatherPreviewPaletteFlash->setVisible' in editor
assert 'weather_palette_flash_strength' in world
assert 'uint8_t gameworlds_weather_frame(' in world
assert 'Build: 5.159.261026' in (root/'splashscreenwidget.cpp').read_text()
print('source: 0..100 strength UI, save/load, world-registry export, live preview and build string PASS')

start = world.index('/* Stage 5.152: optional world-local rain/snow/thunder')
end = world.index('static const uint8_t spotlight_bayer4',start)
block = world[start:end]
code = r'''
#include <stdint.h>
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION (1u << 0)
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH (1u << 1)
#include <stddef.h>
#include <assert.h>
#include <string.h>
#define GW_PHASE_IDLE 0u
#define GW_PHASE_IN 3u
static uint8_t transition_phase, spotlight_enabled, spotlight_mask_index;
static uint32_t spotlight_mask_colour;
static uint32_t transition_front[256], transition_back[256];
static uint32_t front_src[256], back_src[256];
static uint32_t front_display[256], back_display[256];
static int use_front_count, use_back_count, restored;
static const uint32_t *front_source(void) { return front_src; }
static const uint32_t *back_source(void) { return back_src; }
static void mock_usefront(const uint32_t *p) { memcpy(front_display,p,sizeof(front_display));++use_front_count; }
static void mock_useback(const uint32_t *p) { memcpy(back_display,p,sizeof(back_display));++use_back_count; }
#define gfx_usefpalette mock_usefront
#define gfx_usebpalette mock_useback
static void transition_restore_palette(void) { ++restored;mock_usefront(front_src);mock_useback(back_src); }
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
static int rectangles;
static void mock_rectf(int x,int y,int w,int h) { (void)x;(void)y;(void)w;(void)h; ++rectangles; }
static void mock_setcolour(int c) { (void)c; }
#define gfx_rectf mock_rectf
#define gfx_setcolour mock_setcolour
''' + block + r'''
static gameworlds_record_t world = {.weather_mode=3,.weather_density=16,.weather_colour_index=15,.weather_lightning_interval=100,.weather_lightning_strength=100,.weather_lightning_overlay=1,.front_palette=front_source,.back_palette=back_source};
static void init_pals(void) {
    for(unsigned i=0;i<256;i++){
        front_src[i]=0xff123456u;
        back_src[i]=0xff203040u;
    }
    front_src[0]=0x00123456u; // preserve transparent front
    front_src[15]=0xffc0e0ffu; // icy-blue lightning
    back_src[0]=0xff203040u; // background index zero is opaque
    mock_usefront(front_src);mock_useback(back_src);
}
int main(void) {
    init_pals(); active_world=&world;weather_enter(active_world);
    weather_update(100);
    assert(weather_flash_phase==25);
    int old_front=use_front_count, old_back=use_back_count;
    gameworlds_weather_frame(480,320); // 0%: no CLUT modifications
    assert(use_front_count==old_front && use_back_count==old_back);
    assert(front_display[9]==front_src[9] && back_display[3]==back_src[3]);

    world.weather_palette_flash_strength=100;
    weather_enter(&world); weather_update(109); weather_flash_peak=100u;
    gameworlds_weather_frame(480,320);
    assert(front_display[9]==weather_palette_brighten(front_src[9],front_src[15],100));
    assert(back_display[9]==weather_palette_brighten(back_src[9],front_src[15],100));
    assert(front_display[0] >> 24 == 0); // front zero alpha preserved
    assert(back_display[0] >> 24 == 0xffu); // background zero stays opaque
    assert(weather_palette_active);

    weather_update(1); // gently fading after the peak
    gameworlds_weather_frame(480,320);
    weather_update(15); // fade completes; restore exactly
    gameworlds_weather_frame(480,320);
    assert(!weather_palette_active);
    assert(front_display[9]==front_src[9] && back_display[9]==back_src[9]);
    assert(restored >= 1);

    world.weather_palette_flash_strength=50;
    weather_enter(&world); weather_update(109); weather_flash_peak=100u;
    gameworlds_weather_frame(480,320);
    assert(front_display[9]==weather_palette_brighten(front_src[9],front_src[15],50));
    assert(back_display[9]==weather_palette_brighten(back_src[9],front_src[15],50));

    // The spotlight mask's dedicated palette entry must stay unmodified.
    spotlight_enabled=1;
    spotlight_mask_index=254u;
    spotlight_mask_colour=0xff010203u;
    gameworlds_weather_frame(480,320);
    assert(front_display[254]==spotlight_mask_colour);
    spotlight_enabled=0;

    transition_phase=GW_PHASE_IN;
    int before=use_front_count;
    gameworlds_weather_frame(480,320); // ownership goes to transition CLUT
    assert(use_front_count==before);
    assert(weather_palette_active);
    transition_phase=GW_PHASE_IDLE;
    gameworlds_weather_frame(480,320); // resumed when transition ends
    assert(front_display[9]==weather_palette_brighten(front_src[9],front_src[15],50));

    world.weather_palette_flash_strength=0;
    weather_enter(&world);
    mock_usefront(front_src); mock_useback(back_src);
    gameworlds_weather_frame(480,320);
    assert(front_display[9]==front_src[9] && back_display[9]==back_src[9]);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
    source=Path(d)/'test.c'
    source.write_text(code)
    exe=Path(d)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(source),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('native GCC: 0% no-op, 50/100% blending, FRONT/BACK palettes, alpha preservation, spotlight mask, transitions and restoration PASS')
