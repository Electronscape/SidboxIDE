"""Stage 5.159: tint continuity over world transitions, actual additive lightning, curve slider."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[1]
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
editor=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
registry=(root/'gameworldsnapshot.h').read_text()
header=(root/'gamedesigner.h').read_text()
assert 'Build: 5.159.261026' in (root/'splashscreenwidget.cpp').read_text()
assert 'weather_curve_softness' in world and 'weather_curve_envelope' in world
assert 'weather_palette_brighten' in world and 'weather_scene_colour' in world
assert 'transition_dim(\n                    weather_scene_colour(front[i]' in world
assert 'transition_dim(\n                    weather_scene_colour(back[i]' in world
assert 'weather_palette_frame(); /* No untinted single-frame pop' in world
assert 'weather_palette_frame(); /* Night/fog is ready before the first visible frame.' in world
assert 'weather_scene_colour(front[i], lightning_tint, night_mix, flash_mix)' in world
assert 'weather_scene_colour(back[i], lightning_tint, night_mix, flash_mix)' in world
assert 'weatherCurve->setRange(0, 100)' in editor
assert 'm_weatherLightningCurve = weatherCurve->value();' in editor
assert 'm_weatherLightningCurve' in header
assert 'weather.insert(QStringLiteral("lightningCurve"), m_weatherLightningCurve);' in project
assert 'weather.value(QStringLiteral("lightningCurve"))' in project
assert 'defaultWeatherCurve.at(i)' in registry
assert 'weather_curve_code' in world
print('Stage 5.159: source settings and transition paths PASS')

start=world.index('/* Stage 5.152: optional world-local rain/snow/thunder')
end=world.index('static const uint8_t spotlight_bayer4',start)
weather_block=world[start:end]
transition_start=world.index('void gameworlds_transition_frame(uint16_t width, uint16_t height)')
transition_end=world.index('@IDE_IF{HAS_SHARED_PLAYER}',transition_start)
transition_block=world[transition_start:transition_end]
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
static uint32_t front_src[256],back_src[256],front_display[256],back_display[256];
static void setfront(const uint32_t *p) {memcpy(front_display,p,sizeof(front_display));}
static void setback(const uint32_t *p) {memcpy(back_display,p,sizeof(back_display));}
#define gfx_usefpalette setfront
#define gfx_usebpalette setback
static void transition_restore_palette(void) {setfront(front_src);setback(back_src);}
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
static const uint32_t *getfront(void) {return front_src;}
static const uint32_t *getback(void) {return back_src;}
''' +weather_block+r'''
static uint32_t transition_dim(uint32_t source,uint16_t light) {
    return (source & 0xff000000u) |
        ((((source >> 16)&255u)*light/255u)<<16) |
        ((((source >> 8)&255u)*light/255u)<<8) |
        ((source&255u)*light/255u);
}
'''+transition_block+r'''
int main(void) {
    for(int i=0;i<256;i++) {front_src[i]=0xff80a0c0u;back_src[i]=0xff406080u;}
    front_src[0]=0x0080a0c0u;front_src[15]=0xffc0eaffu;
    gameworlds_record_t night={0};
    night.front_palette=getfront;night.back_palette=getback;
    night.day_night_mode=1;night.day_night_colour=0x00204080u;
    night.day_night_strength=70;night.weather_colour_index=15;
    active_world=&night;weather_enter(active_world);
    weather_palette_frame();
    const uint32_t night_front=weather_palette_blend(front_src[9],0xff204080u,70);
    const uint32_t night_back=weather_palette_blend(back_src[9],0xff204080u,70);
    assert(front_display[9]==night_front && back_display[9]==night_back);
    assert((front_display[0]>>24)==0u);
    transition_enabled=1; transition_phase=GW_PHASE_OUT;
    transition_mode=GW_TRANSITION_FADE;transition_frames=10;transition_step=0;
    gameworlds_transition_frame(480,320);
    const uint16_t fade_light=230u; /* 255 - 25: (1 * 255 / 10) */
    assert(front_display[9]==transition_dim(night_front,fade_light));
    assert(back_display[9]==transition_dim(night_back,fade_light));
    assert(front_display[9]!=transition_dim(front_src[9],fade_light));

    /* A different world with its own tint arrives. Its FIRST transition frame
       must already be tinted, and its LAST frame must stay tinted. */
    gameworlds_record_t destination=night;
    destination.day_night_colour=0x00001848u;
    destination.day_night_strength=90;
    active_world=&destination;weather_enter(active_world);
    transition_phase=GW_PHASE_IN;transition_step=0;
    const uint32_t new_night=weather_palette_blend(front_src[9],0xff001848u,90);
    gameworlds_transition_frame(480,320);
    assert(front_display[9]==transition_dim(new_night,26u));
    transition_step=9;
    gameworlds_transition_frame(480,320);
    assert(transition_phase==GW_PHASE_IDLE);
    assert(front_display[9]==new_night); /* no untinted final frame */
    assert(back_display[9]==weather_palette_blend(back_src[9],0xff001848u,90));

    /* Non-fade transition still retains the tint in FRONT and BACK. */
    transition_enabled=1;transition_phase=GW_PHASE_IN;
    transition_mode=2u;transition_step=0;
    gameworlds_transition_frame(480,320);
    assert(front_display[9]==new_night);
    assert(back_display[9]==weather_palette_blend(back_src[9],0xff001848u,90));
    transition_phase=GW_PHASE_IDLE;

    /* Lightning MUST brighten an already dark palette without dimming any RGB channel. */
    destination.weather_mode=3;
    destination.weather_lightning_interval=100;
    destination.weather_palette_flash_strength=90;
    destination.weather_lightning_overlay=0;
    active_world=&destination;weather_enter(active_world);
    weather_update(109);weather_flash_peak=100u;
    weather_palette_frame();
    uint32_t flash=front_display[9];
    for(int shift=0;shift<=16;shift+=8) {
        assert(((flash>>shift)&255u)>=((new_night>>shift)&255u));
    }
    assert(flash!=new_night);
    weather_update(16);
    weather_palette_frame();
    assert(front_display[9]==new_night); /* back to NIGHT, not day palette */

    /* Curve slider changes attack/tail smoothness without changing endpoints. */
    assert(weather_curve_envelope(0,0)==0u);
    assert(weather_curve_envelope(9,100)==100u);
    assert(weather_curve_envelope(24,70)==0u);
    assert(weather_curve_envelope(2,100)<weather_curve_envelope(2,0));
    assert(weather_curve_envelope(21,100)<weather_curve_envelope(21,0));
    destination.weather_curve_code=1u;weather_enter(&destination);
    assert(weather_curve_softness==0u);
    destination.weather_curve_code=101u;weather_enter(&destination);
    assert(weather_curve_softness==100u);
    destination.weather_curve_code=0u;weather_enter(&destination);
    assert(weather_curve_softness==70u); /* legacy worlds preserve gentle default */
    return 0;
}
'''
with tempfile.TemporaryDirectory() as folder:
    source=Path(folder)/'stage159.c';source.write_text(unit)
    output=Path(folder)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(source),'-o',str(output)],check=True)
    subprocess.run([str(output)],check=True)
print('Stage 5.159 native GCC: transitions, lightning, tint restoration and easing PASS')
