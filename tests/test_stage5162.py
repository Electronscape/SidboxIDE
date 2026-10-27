"""Stage 5.162: natural rain speed layers and per-world day/night clocks."""
from pathlib import Path
import re
import subprocess
import tempfile
root=Path(__file__).resolve().parents[1]
rule=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
editor=(root/'gamedesigner.cpp').read_text()
assert 'Build: 5.162.261026' in (root/'splashscreenwidget.cpp').read_text()
for needle in ('day_night_save_active();','day_night_restore_world(world);',
               'memset(day_night_saved_tick,0,sizeof(day_night_saved_tick));',
               'memset(day_night_saved_valid,0,sizeof(day_night_saved_valid));'):
    assert needle in rule
assert rule.index('day_night_restore_world(world);') < rule.index('weather_palette_frame(); /* Night/fog')
assert 'weather_flash_phase = weather_flash_duration;' in rule
assert 'const quint32 scatterSeed = scatterHash' in editor
assert 'const quint64 travel = ' in editor
assert 'qMin(len, height - y)' in editor
assert 'const uint64_t travel = ' in rule
assert '((uint32_t)i * 97u + 37u)' not in rule
assert '(i * 97 + 37)' not in editor
assert '++weather_frame_tick; /* 32-bit clock' in rule

weather=rule[rule.index('/* Stage 5.152: optional world-local rain/snow/thunder'):
             rule.index('static const uint8_t spotlight_bayer4')]
helpers=rule[rule.index('static void day_night_save_active(void)'):
             rule.index('/* Both effects on a Goto World doorway')]
assert '@IDE' not in weather + helpers
harness=r'''
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#define GW_PHASE_IDLE 0u
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION 1u
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH 2u
static uint8_t transition_phase, spotlight_enabled, spotlight_mask_index;
static uint32_t spotlight_mask_colour;
static uint32_t transition_front[256], transition_back[256];
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
static const gameworlds_record_t worlds[3] = {
    {.start_x=37,.start_y=20,.weather_mode=1,.weather_density=64,.weather_wind=0,
     .day_night_mode=2,.day_night_day_frames=50,.day_night_night_frames=70,
     .day_night_fade_frames=20,.day_night_strength=75,.day_night_colour=0xff1a2050u},
    {.start_x=221,.start_y=110,.weather_mode=3,.weather_density=40,
     .weather_lightning_interval=350,.weather_curve_code=13,
     .day_night_mode=2,.day_night_day_frames=80,.day_night_night_frames=120,
     .day_night_fade_frames=30,.day_night_start_at_night=1,
     .day_night_strength=70,.day_night_colour=0xff182a22u},
    {.start_x=18,.start_y=10,.weather_mode=0,.day_night_mode=1,
     .day_night_strength=80,.day_night_colour=0xff444444u}
};
#define WORLD_COUNT (sizeof(worlds)/sizeof(worlds[0]))
static uint32_t day_night_saved_tick[WORLD_COUNT];
static uint8_t day_night_saved_valid[WORLD_COUNT];
static const gameworlds_record_t *active_world;
static void transition_restore_palette(void) {}
static int nrect;
static int xpos[64],ypos[64],heights[64];
static void rect(int32_t x,int32_t y,int32_t w,int32_t h) {
    assert(x>=0 && x+w<=480 && y>=0 && y+h<=320);
    assert(w>0 && h>0);
    if(nrect<64) {xpos[nrect]=x;ypos[nrect]=y;heights[nrect]=h;}
    ++nrect;
}
static void colour(uint8_t c) {(void)c;}
#define gfx_rectf rect
#define gfx_setcolour colour
''' + weather + helpers + r'''
int main(void) {
    active_world=&worlds[0];weather_enter(active_world);
    assert(day_night_tick==0u);
    nrect=0;gameworlds_weather_frame(480,320);
    assert(nrect==64);
    int first_y[64], first_x[64], first_h[64];
    memcpy(first_y,ypos,sizeof first_y);
    memcpy(first_x,xpos,sizeof first_x);
    memcpy(first_h,heights,sizeof first_h);
    unsigned unique_columns=0;
    for(unsigned i=0;i<64;i++) {
        int seen=0;
        for(unsigned j=0;j<i;j++) if(first_x[j]==first_x[i]) seen=1;
        if(!seen) unique_columns++;
    }
    assert(unique_columns>=45u); /* no three lanes */
    weather_update(1);
    nrect=0;gameworlds_weather_frame(480,320);
    assert(nrect==64);
    int slow=0,middle=0,fast=0;
    for(unsigned i=0;i<64;i++) {
        int speed=(ypos[i]-first_y[i]+320)%320;
        assert(speed>=4 && speed<=15);
        if(speed<=6) slow++;
        else if(speed<=10) middle++;
        else fast++;
    }
    assert(slow>=8 && middle>=8 && fast>=8);
    /* By the time drops have completed several laps, many have a fresh X. */
    weather_update(320);
    nrect=0;gameworlds_weather_frame(480,320);
    assert(nrect==64);
    int changed=0;
    for(unsigned i=0;i<64;i++) if(xpos[i]!=first_x[i]) changed++;
    assert(changed>=45);
    /* No artificial old 16384-frame reset or out-of-viewport drawing. */
    weather_update(16384);
    assert(weather_frame_tick==16705u);
    nrect=0;gameworlds_weather_frame(480,320);
    assert(nrect==64);
    /* Enter and leave cycles: world A should resume mid-dusk, not at day 0. */
    day_night_saved_valid[0]=0;
    weather_enter(&worlds[0]);weather_update(61);
    assert(day_night_tick==61 && day_night_mix()>0 && day_night_mix()<75);
    day_night_save_active();
    assert(day_night_saved_tick[0]==61);
    active_world=&worlds[1];weather_enter(active_world);day_night_restore_world(active_world);
    assert(day_night_tick==110); /* World B starts at night */
    weather_update(37);
    assert(day_night_tick==147);
    day_night_save_active();
    active_world=&worlds[0];weather_enter(active_world);day_night_restore_world(active_world);
    assert(day_night_tick==61 && day_night_mix()>0);
    weather_update(40);
    day_night_save_active();
    active_world=&worlds[2];weather_enter(active_world);day_night_restore_world(active_world);
    assert(day_night_mix()==80); /* fixed fog doesn't inherit a cycle */
    active_world=&worlds[1];weather_enter(active_world);day_night_restore_world(active_world);
    assert(day_night_tick==147); /* World B also remembers its clock */
    active_world=&worlds[0];weather_enter(active_world);day_night_restore_world(active_world);
    assert(day_night_tick==101);
    /* New game/shutdown clears history; first entrance honours Start At Night. */
    memset(day_night_saved_valid,0,sizeof(day_night_saved_valid));
    active_world=&worlds[1];weather_enter(active_world);day_night_restore_world(active_world);
    assert(day_night_tick==110);
    return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
    src=Path(d)/'stage162.c';src.write_text(harness)
    exe=Path(d)/'test'
    subprocess.run(['gcc','-std=c11','-O2','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.162 native C: rain scattering, three speed layers, respawns, viewport, per-world day/night phase PASS')
