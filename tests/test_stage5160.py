"""Stage 5.160: lightning duration and two-world pre-transition palette binding."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[1]
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
editor=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
registry=(root/'gameworldsnapshot.h').read_text()
assert 'Build: 5.160.261026' in (root/'splashscreenwidget.cpp').read_text()
assert 'Lightning flash duration' in editor
assert 'Lightning curve softness' not in editor
assert 'm_weatherLightningCurve * 74' in editor
assert 'weather_flash_phase = weather_flash_duration;' in world
assert 'weather_flash_duration' in world
assert 'weather_flash_phase = 25u;' not in world
assert 'if (transition_phase != GW_PHASE_IDLE) return;' not in world[world.index('static void weather_palette_frame(void)'):world.index('uint8_t gameworlds_weather_frame')]
assert 'weather_palette_active = 1u;' in world[world.index('static void weather_enter('):world.index('static void weather_update')]
assert 'QStringLiteral("lightningCurve")' in project and 'defaultWeatherCurve.at(i)' in registry
print('Stage 5.160 source: duration slider, legacy field, active-world CLUT rebinding PASS')

start=world.index('/* Stage 5.152: optional world-local rain/snow/thunder')
end=world.index('static const uint8_t spotlight_bayer4',start)
weather_block=world[start:end]
start=world.index('void gameworlds_transition_frame(uint16_t width, uint16_t height)')
end=world.index('@IDE_IF{HAS_SHARED_PLAYER}',start)
transition_block=world[start:end]
assert '@IDE' not in weather_block+transition_block
unit=r'''
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION 1u
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH 2u
#define GW_PHASE_IDLE 0u
#define GW_PHASE_OUT 1u
#define GW_PHASE_OUT_DONE 2u
#define GW_PHASE_IN 3u
#define GW_TRANSITION_FADE 1u
static uint8_t transition_phase,transition_enabled,transition_mode,transition_frames,transition_step;
static uint8_t spotlight_enabled,spotlight_mask_index=255;
static uint32_t spotlight_mask_colour=0xff000000u;
static uint32_t transition_front[256],transition_back[256];
static uint32_t outgoing_front[256],outgoing_back[256],incoming_front[256],incoming_back[256];
static uint32_t front_display[256],back_display[256];
static void setfront(const uint32_t *p) {memcpy(front_display,p,sizeof(front_display));}
static void setback(const uint32_t *p) {memcpy(back_display,p,sizeof(back_display));}
#define gfx_usefpalette setfront
#define gfx_usebpalette setback
static void transition_restore_palette(void);
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
    uint8_t day_night_start_at_night,weather_curve_code;
    const uint32_t *(*front_palette)(void);
    const uint32_t *(*back_palette)(void);
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
static const uint32_t *oldfront(void) {return outgoing_front;}
static const uint32_t *oldback(void) {return outgoing_back;}
static const uint32_t *newfront(void) {return incoming_front;}
static const uint32_t *newback(void) {return incoming_back;}
static void transition_restore_palette(void) {
    if(!active_world) return;
    if(active_world->front_palette)setfront(active_world->front_palette());
    if(active_world->back_palette)setback(active_world->back_palette());
}
''' + weather_block + r'''
static uint32_t transition_dim(uint32_t source,uint16_t light) {
    return (source & 0xff000000u) |
        ((((source >> 16)&255u)*light/255u)<<16) |
        ((((source >> 8)&255u)*light/255u)<<8) |
        ((source&255u)*light/255u);
}
''' + transition_block + r'''
int main(void) {
    for (unsigned i=0;i<256;i++) {
        outgoing_front[i]=0xffb8dbb8u;outgoing_back[i]=0xffcae4bfu;
        incoming_front[i]=0xffc08070u;incoming_back[i]=0xff846040u;
    }
    outgoing_front[0]=0x00ffffffu;incoming_front[0]=0x00ffffffu;
    outgoing_front[15]=0xffd0eaffu;incoming_front[15]=0xffaeeeffu;
    gameworlds_record_t fog={0};
    fog.front_palette=oldfront;fog.back_palette=oldback;
    fog.day_night_mode=1;fog.day_night_colour=0xffa7b4aau;fog.day_night_strength=65;
    fog.weather_colour_index=15;
    active_world=&fog;weather_enter(active_world);weather_palette_frame();
    const uint32_t fog_rgb=front_display[9];
    assert(fog_rgb==weather_palette_blend(outgoing_front[9], fog.day_night_colour,65));
    transition_enabled=1;transition_phase=GW_PHASE_OUT;transition_mode=GW_TRANSITION_FADE;
    transition_frames=10;transition_step=9;
    gameworlds_transition_frame(480,320);
    assert(transition_phase==GW_PHASE_OUT_DONE);

    /* Incoming world has DIFFERENT source CLUTs AND a DIFFERENT tint.
       Force old fog to remain on display as previous transition left it. */
    gameworlds_record_t night={0};
    night.front_palette=newfront;night.back_palette=newback;
    night.day_night_mode=1;night.day_night_colour=0xff0a2050u;
    night.day_night_strength=85;night.weather_colour_index=15;
    active_world=&night;weather_enter(active_world);
    transition_phase=GW_PHASE_IN;transition_step=0;
    const uint32_t target_front=weather_palette_blend(incoming_front[9],night.day_night_colour,85);
    const uint32_t target_back=weather_palette_blend(incoming_back[9],night.day_night_colour,85);
    /* This emulates the weather_frame() call BEFORE transition_frame() in
       hand-owned main.c. It must already bind the destination, not the fog. */
    weather_palette_frame();
    assert(front_display[9]==target_front && back_display[9]==target_back);
    assert(front_display[9]!=fog_rgb);
    gameworlds_transition_frame(480,320);
    assert(front_display[9]==transition_dim(target_front,26u));
    assert(back_display[9]==transition_dim(target_back,26u));
    /* On the following frames, weather binds the untampered target again
       BEFORE the transition renderer dims it. */
    weather_palette_frame();
    assert(front_display[9]==target_front);
    transition_step=9;gameworlds_transition_frame(480,320);
    assert(transition_phase==GW_PHASE_IDLE && front_display[9]==target_front);
    assert(back_display[9]==target_back);
    assert((front_display[0]>>24)==0u);

    /* Lightning % affects DURATION (both attack and release), not peak. */
    night.weather_mode=3;night.weather_lightning_interval=100;
    night.weather_palette_flash_strength=80;
    night.weather_curve_code=13u; /* saved 12% */
    weather_enter(&night);
    assert(weather_flash_duration==14u);
    weather_update(100);assert(weather_flash_phase==14u);
    weather_flash_peak=100u;
    uint8_t max_short=0;
    for (unsigned i=0;i<14;i++) {
        const uint8_t p=weather_pulse();if(p>max_short)max_short=p;
        weather_update(1);
    }
    assert(max_short==100u && weather_flash_phase==0u);
    night.weather_curve_code=101u;weather_enter(&night);
    assert(weather_flash_duration==80u);
    weather_update(100);assert(weather_flash_phase==80u);
    weather_flash_peak=100u;
    uint8_t max_long=0;
    for (unsigned i=0;i<80;i++) {
        const uint8_t p=weather_pulse();if(p>max_long)max_long=p;
        weather_update(1);
    }
    assert(max_long==100u && weather_flash_phase==0u);
    night.weather_curve_code=1u;weather_enter(&night);
    assert(weather_flash_duration==6u);
    night.weather_curve_code=0u;weather_enter(&night);
    assert(weather_flash_duration==24u); /* reasonable old-world fallback */
    return 0;
}
'''
with tempfile.TemporaryDirectory() as tmp:
    src=Path(tmp)/'integration.c'; src.write_text(unit)
    exe=Path(tmp)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.160 native GCC: 2-world fog-to-night colour handoff, fade IN/OUT, alpha, 12%/100% lightning lengths PASS')
