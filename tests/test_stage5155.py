"""Stage 5.155: independently switchable lightning screen overlay and palette tint."""
from pathlib import Path
import subprocess
import tempfile
root = Path(__file__).resolve().parents[1]
editor = (root / 'gamedesigner.cpp').read_text()
header = (root / 'gamedesigner.h').read_text()
project = (root / 'gamedesigner_project.cpp').read_text()
registry = (root / 'gameworldsnapshot.h').read_text()
world = (root / 'idelibs/codehelpers/game/gameworlds.rulec').read_text()

# The old default must retain the original patterned flash.
assert 'm_weatherLightningOverlay = true' in header
assert 'weather.value(QStringLiteral("lightningOverlayEnabled")).toBool(true)' in project
assert 'weather.insert(QStringLiteral("lightningOverlayEnabled"), m_weatherLightningOverlay);' in project
assert 'defaultWeatherOverlay << (weather.value(QStringLiteral("lightningOverlayEnabled")).toBool(true)' in registry
assert '.arg(defaultWeatherOverlay.at(i))' in registry
assert 'Enable lightning screen overlay' in editor
assert 'weatherOverlay->setEnabled(mode == 3)' in editor
assert 'weatherStrength->setEnabled(mode == 3 && weatherOverlay->isChecked())' in editor
assert 'm_weatherPreviewFlash->setVisible(m_weatherMode == 3 && m_weatherLightningOverlay && pulse != 0)' in editor
assert 'm_weatherPreviewPaletteFlash->setOpacity(pulse * m_weatherPaletteFlashStrength / 10000.0);' in editor
assert 'weather_lightning_overlay' in world and 'weather_overlay_enabled' in world
assert 'if (weather_mode == 3u && weather_overlay_enabled && weather_flash_phase)' in world
assert 'weather_palette_strength / 100u' in world
assert 'Build: 5.158.261026' in (root / 'splashscreenwidget.cpp').read_text()
print('source checks: UI, save/load, old-world default, registry, canvas preview, runtime and splash PASS')

begin=world.index('/* Stage 5.152: optional world-local rain/snow/thunder')
end=world.index('static const uint8_t spotlight_bayer4',begin)
block=world[begin:end]
code=r'''
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION (1u << 0)
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH (1u << 1)
#define GW_PHASE_IDLE 0u
static uint8_t transition_phase, spotlight_enabled, spotlight_mask_index;
static uint32_t spotlight_mask_colour;
static uint32_t transition_front[256], transition_back[256];
static uint32_t front_src[256], back_src[256];
static uint32_t front_display[256], back_display[256];
static uint16_t palette_front_count, palette_back_count;
static const uint32_t *front_source(void) { return front_src; }
static const uint32_t *back_source(void) { return back_src; }
static void mock_usefront(const uint32_t *p) { memcpy(front_display,p,sizeof(front_display)); ++palette_front_count; }
static void mock_useback(const uint32_t *p) { memcpy(back_display,p,sizeof(back_display)); ++palette_back_count; }
#define gfx_usefpalette mock_usefront
#define gfx_usebpalette mock_useback
static void transition_restore_palette(void) { mock_usefront(front_src); mock_useback(back_src); }
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
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
static int rectangles, full_screen;
static void mock_rectf(int x,int y,int w,int h) {
    (void)x;(void)y;
    ++rectangles;
    if (w==480 && h==320) ++full_screen;
}
static void mock_setcolour(int c) { (void)c; }
#define gfx_rectf mock_rectf
#define gfx_setcolour mock_setcolour
''' + block + r'''
static gameworlds_record_t storm = {
    .weather_mode=3, .weather_density=4, .weather_colour_index=15,
    .weather_lightning_interval=100, .weather_lightning_strength=25,
    .weather_palette_flash_strength=100, .weather_suspend_spotlight=1,
    .weather_lightning_overlay=0, .front_palette=front_source,
    .back_palette=back_source
};
static void start_storm(void) {
    /* Real gameworlds_start restores the display CLUT before world activation. */
    transition_restore_palette();
    active_world=&storm;
    weather_enter(&storm);
    weather_update(109);
    weather_flash_peak=100u; /* exact peak for palette-strength assertions */
    assert(weather_flash_phase==16u);
    rectangles=0; full_screen=0;
}
int main(void) {
    for(unsigned i=0;i<256;i++){
        front_src[i]=0xff102030u;
        back_src[i]=0xff203040u;
    }
    front_src[0]=0x00102030u; front_src[15]=0xffd0eaffu;
    mock_usefront(front_src); mock_useback(back_src);
    /* Palette-only: no lightning rectangles, full palette intensity despite
       the low 25% overlay strength. Weather rain is still drawn. */
    start_storm();
    assert(gameworlds_weather_status() & GAME_WEATHER_STATUS_LIGHTNING_FLASH);
    gameworlds_weather_frame(480,320);
    assert(rectangles==4 && full_screen==0);
    assert(front_display[9]==front_src[15] && back_display[9]==front_src[15]);
    assert(front_display[0] >> 24 == 0u);
    assert(back_display[0] >> 24 == 255u);
    assert(weather_palette_active);
    /* Palette flash returns to its source when the pulse goes dark. */
    weather_update(16);
    assert(!(gameworlds_weather_status() & GAME_WEATHER_STATUS_LIGHTNING_FLASH));
    gameworlds_weather_frame(480,320);
    assert(front_display[9]==front_src[9] && back_display[9]==back_src[9]);
    assert(!weather_palette_active);

    /* Overlay-only: patterned light, no palette changes. */
    storm.weather_palette_flash_strength=0;
    storm.weather_lightning_overlay=1;
    storm.weather_lightning_strength=100;
    start_storm();
    uint16_t palettes_before=palette_front_count;
    assert(gameworlds_weather_status() & GAME_WEATHER_STATUS_LIGHTNING_FLASH);
    gameworlds_weather_frame(480,320);
    assert(rectangles>4); /* stable dither rows at peak, not an abrupt full-screen fill */
    assert(palette_front_count==palettes_before);
    assert(front_display[9]==front_src[9]);

    /* Both: overlay + independent 50% palette. */
    storm.weather_palette_flash_strength=50;
    start_storm();
    assert(gameworlds_weather_status() & GAME_WEATHER_STATUS_LIGHTNING_FLASH);
    gameworlds_weather_frame(480,320);
    assert(rectangles>4); /* stable dither rows at peak, not an abrupt full-screen fill */
    assert(front_display[9]==weather_palette_blend(front_src[9],front_src[15],50));

    /* Neither: no flash flag and no unwanted spotlight suspension, although
       thunderstorm precipitation still remains active. */
    storm.weather_lightning_overlay=0;
    storm.weather_palette_flash_strength=0;
    start_storm();
    assert(gameworlds_weather_status()==GAME_WEATHER_STATUS_PRECIPITATION);
    gameworlds_weather_frame(480,320);
    assert(rectangles==4 && full_screen==0);
    assert(front_display[9]==front_src[9]);

    /* Switching worlds cannot continue a lightning pulse. */
    gameworlds_record_t clear={.weather_mode=0, .weather_lightning_overlay=1};
    active_world=&clear; weather_enter(active_world);
    assert(gameworlds_weather_status()==GAME_WEATHER_STATUS_NONE);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as directory:
    src=Path(directory)/'weather_overlay.c';src.write_text(code)
    exe=Path(directory)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('native GCC: palette-only, overlay-only, both, neither, status, CLUT restore, legacy lightning semantics PASS')
