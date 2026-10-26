"""Stage 5.157: soft lightning curve, collapsible settings, cyclic & fixed palette tint."""
from pathlib import Path
import subprocess
import tempfile
root=Path(__file__).resolve().parents[1]
editor=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
registry=(root/'gameworldsnapshot.h').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
header=(root/'gamedesigner.h').read_text()
assert 'Build: 5.158.261026' in (root/'splashscreenwidget.cpp').read_text()
for name in ('Player Start','Weather','Spotlight','Day & Night / Palette Tint'):
    assert f'makeSection(tr("{name}"))' in editor
for key,field in [('mode','m_dayNightMode'),('targetColour','m_dayNightColour'),('strength','m_dayNightStrength'),
                  ('dayFrames','m_dayNightDayFrames'),('nightFrames','m_dayNightNightFrames'),
                  ('fadeFrames','m_dayNightFadeFrames'),('startAtNight','m_dayNightStartAtNight')]:
    assert field in header
    assert f'dayNight.value(QStringLiteral("{key}"))' in project
    assert f'dayNight.insert(QStringLiteral("{key}"), {field});' in project
assert 'obj.insert(QStringLiteral("dayNight"), dayNight);' in project
assert 'design.value(QStringLiteral("dayNight"))' in registry
assert 'defaultDayNightColour.at(i)' in registry
assert 'weather_palette_blend(colour, lightning_tint, flash_mix)' in world
assert 'weather_palette_frame(); /* Also drives CLEAR worlds' in world
assert 'm_weatherPreviewDayNightTint->setOpacity(nightMix / 100.0);' in editor
assert 'if (weather_flash_delay < 150u)' in world
assert '((uint32_t)y * 37u + 13u)' in world
print('Stage5.157 source checks: UI, JSON, registry, preview, CLUT compositing and gentle lightning PASS')

start=world.index('/* Stage 5.152: optional world-local rain/snow/thunder')
end=world.index('static const uint8_t spotlight_bayer4',start)
block=world[start:end]
assert '@IDE' not in block
unit = r'''
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION (1u<<0)
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH (1u<<1)
#define GW_PHASE_IDLE 0u
#define GW_PHASE_IN 3u
static uint8_t transition_phase,spotlight_enabled,spotlight_mask_index=255;
static uint32_t spotlight_mask_colour=0xff000000u;
static uint32_t transition_front[256],transition_back[256];
static uint32_t front_src[256],back_src[256],front_display[256],back_display[256];
static int palette_updates, rectangles;
static const uint32_t *getfront(void) { return front_src; }
static const uint32_t *getback(void) { return back_src; }
static void setfront(const uint32_t *p) {memcpy(front_display,p,sizeof(front_display));++palette_updates;}
static void setback(const uint32_t *p) {memcpy(back_display,p,sizeof(back_display));}
#define gfx_usefpalette setfront
#define gfx_usebpalette setback
static void transition_restore_palette(void) {setfront(front_src);setback(back_src);}
static void rect(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;++rectangles;}
static void colour(int c) {(void)c;}
#define gfx_rectf rect
#define gfx_setcolour colour
typedef struct {
    int32_t start_x,start_y;
    uint8_t weather_mode,weather_density;
    int8_t weather_wind;
    uint8_t weather_colour_index;
    uint16_t weather_lightning_interval;
    uint8_t weather_lightning_strength,weather_palette_flash_strength;
    uint8_t weather_suspend_spotlight,weather_lightning_overlay;
    uint8_t day_night_mode;
    uint32_t day_night_colour;
    uint8_t day_night_strength;
    uint16_t day_night_day_frames,day_night_night_frames,day_night_fade_frames;
    uint8_t day_night_start_at_night;
    const uint32_t *(*front_palette)(void);
    const uint32_t *(*back_palette)(void);
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
''' + block + r'''
int main(void) {
    for (int i=0;i<256;i++) {front_src[i]=0xff80a0c0u;back_src[i]=0xff4080a0u;}
    front_src[0]=0x0080a0c0u;
    front_src[15]=0xffe0f0ffu;
    transition_restore_palette();
    gameworlds_record_t clear={0};
    clear.weather_colour_index=15;
    clear.day_night_mode=1;clear.day_night_colour=0x00102040u;
    clear.day_night_strength=50;
    clear.front_palette=getfront; clear.back_palette=getback;
    active_world=&clear; weather_enter(active_world);
    assert(day_night_mix()==50);
    gameworlds_weather_frame(480,320);
    assert(weather_palette_active && rectangles==0);
    assert(front_display[4]==weather_palette_blend(front_src[4],0xff102040u,50));
    assert(back_display[4]==weather_palette_blend(back_src[4],0xff102040u,50));
    assert((front_display[0]>>24)==0); /* transparency preserved */
    spotlight_enabled=1;spotlight_mask_index=255;
    gameworlds_weather_frame(480,320);
    assert(front_display[255]==spotlight_mask_colour);
    spotlight_enabled=0;
    clear.day_night_mode=2;clear.day_night_day_frames=50;
    clear.day_night_night_frames=50;clear.day_night_fade_frames=50;
    clear.day_night_strength=80;clear.day_night_start_at_night=0;
    weather_enter(active_world);
    assert(day_night_mix()==0);
    weather_update(50);
    assert(day_night_mix()==0);
    weather_update(25);
    assert(day_night_mix()>=35 && day_night_mix()<=45); /* midpoint ease */
    weather_update(25);
    assert(day_night_mix()==80); /* night */
    weather_update(50);
    assert(day_night_mix()==80);
    weather_update(25);
    assert(day_night_mix()>=35 && day_night_mix()<=45); /* dawn */
    weather_update(25);
    assert(day_night_mix()==0); /* day restored */
    clear.day_night_start_at_night=1;
    weather_enter(active_world);
    assert(day_night_mix()==80); /* begins at night */
    /* Transition owns the palette copies and the day/night overlay yields. */
    transition_phase=GW_PHASE_IN;
    int count=palette_updates;
    gameworlds_weather_frame(480,320);
    assert(palette_updates==count);
    transition_phase=GW_PHASE_IDLE;
    gameworlds_weather_frame(480,320);
    assert(palette_updates>count);
    /* Storm's gentle pulse and palette compositing over existing night tint. */
    gameworlds_record_t storm=clear;
    storm.weather_mode=3;storm.weather_density=1;
    storm.weather_lightning_interval=100;
    storm.weather_lightning_strength=80;
    storm.weather_palette_flash_strength=50;
    storm.weather_lightning_overlay=0;
    storm.day_night_mode=1;storm.day_night_strength=50;
    active_world=&storm;weather_enter(active_world);
    weather_update(100);
    assert(weather_flash_phase==25);
    assert(weather_pulse()==0); /* slow onset */
    weather_update(1);
    const uint8_t very_early=weather_pulse();
    weather_update(9);
    const uint8_t near_peak=weather_pulse();
    assert(very_early>0 && very_early<near_peak);
    assert(near_peak>=50 && near_peak<=100);
    assert(gameworlds_weather_status() & GAME_WEATHER_STATUS_LIGHTNING_FLASH);
    gameworlds_weather_frame(480,320);
    uint32_t base=weather_palette_blend(front_src[4],0xff102040u,50);
    assert(front_display[4]==weather_palette_blend(base,front_src[15],near_peak*50/100));
    const uint8_t previous=weather_pulse();
    weather_update(4);
    assert(weather_pulse()<previous);
    weather_update(12);
    assert(weather_pulse()==0);
    assert(weather_flash_delay>=120); /* cooldown began at 150 and ticks during fade */
    /* Switching worlds to untinted/clear restores original palettes on frame. */
    gameworlds_record_t ordinary={0};
    ordinary.weather_colour_index=15;
    ordinary.front_palette=getfront;ordinary.back_palette=getback;
    active_world=&ordinary;weather_enter(active_world);
    gameworlds_weather_frame(480,320);
    assert(front_display[4]==front_src[4]);
    assert(back_display[4]==back_src[4]);
    assert(!weather_palette_active);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as folder:
    src=Path(folder)/'stage157.c'; src.write_text(unit)
    exe=Path(folder)/'stage157'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage5.157 native GCC: gradual pulse, cooldown, static tint, cycle, spotlight mask, alpha, transition, world switch PASS')
