"""Stage 5.161: spotlight and incoming world tint, with active storm clocks during transitions."""
from pathlib import Path
import re, subprocess, tempfile
root=Path(__file__).resolve().parents[1]
rule=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
template=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
assert 'Build: 5.161.261026' in (root/'splashscreenwidget.cpp').read_text()
sp_start=rule.index('void gameworlds_spotlight_frame(uint16_t width, uint16_t height)')
sp_end=rule.index('void gameworlds_transition_frame(uint16_t width, uint16_t height)',sp_start)
sp=rule[sp_start:sp_end]
assert 'weather_palette_frame();' in sp, 'spotlight must recompose current tint'
assert 'spotlight_palette_copy(front);' not in sp, 'old untinted copy reintroduced'
assert 'active_world->assets_show_background();\n    /* Some display back-buffer' in rule
assert template.index('game_update_weather(1);') < template.index('if (!gameworlds_transition_busy()) {')
assert template.index('game_update_particles(1);') < template.index('if (!gameworlds_transition_busy()) {')
assert template.index('gameworlds_spotlight_frame(VIEW_W, GAME_PLAY_H);') < template.index('gameworlds_weather_frame(VIEW_W, GAME_PLAY_H);')

weather_start=rule.index('/* Stage 5.152: optional world-local rain/snow/thunder')
weather_end=rule.index('static const uint8_t spotlight_bayer4',weather_start)
weather=rule[weather_start:weather_end]
spotlight=re.sub(r'@IDE_IF\{HAS_SHARED_PLAYER\}\n.*?@IDE_END\n','',sp,count=1,flags=re.S)
assert '@IDE' not in spotlight
harness=r'''
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#define GAME_WEATHER_STATUS_NONE 0u
#define GAME_WEATHER_STATUS_PRECIPITATION 1u
#define GAME_WEATHER_STATUS_LIGHTNING_FLASH 2u
#define GW_PHASE_IDLE 0u
static uint8_t transition_phase, spotlight_enabled, spotlight_mask_index;
static uint32_t spotlight_mask_colour = 0xff000000u;
static uint32_t transition_front[256], transition_back[256];
static uint8_t spotlight_opacity=100u, spotlight_stable_dither;
static uint16_t spotlight_radius=48u;
static uint8_t spotlight_feather_current;
static int16_t spotlight_offset_x, spotlight_offset_y;
static int32_t spotlight_player_x, spotlight_player_y, spotlight_camera_x, spotlight_camera_y;
static uint32_t src_front[256], src_back[256], bound_front[256], bound_back[256];
static void usefront(const uint32_t *p) { memcpy(bound_front,p,sizeof bound_front); }
static void useback(const uint32_t *p) { memcpy(bound_back,p,sizeof bound_back); }
#define gfx_usefpalette usefront
#define gfx_usebpalette useback
static void mock_rectf(int x,int y,int w,int h) {(void)x;(void)y;(void)w;(void)h;}
static void mock_setcolour(int v) {(void)v;}
#define gfx_rectf mock_rectf
#define gfx_setcolour mock_setcolour
static void spotlight_animation_tick(void) {}
static void spotlight_dither_segment(int32_t a,int32_t b,int32_t y,uint16_t opacity)
{(void)a;(void)b;(void)y;(void)opacity;}
static uint32_t transition_isqrt(uint32_t n) {(void)n;return 10u;}
typedef struct {
    int32_t start_x,start_y;
    uint8_t weather_mode,weather_density;
    int8_t weather_wind;
    uint8_t weather_colour_index;
    uint16_t weather_lightning_interval;
    uint8_t weather_lightning_strength,weather_palette_flash_strength;
    uint8_t weather_suspend_spotlight,weather_lightning_overlay;
    const uint32_t *(*front_palette)(void);
    const uint32_t *(*back_palette)(void);
    uint8_t day_night_mode;
    uint32_t day_night_colour;
    uint8_t day_night_strength;
    uint16_t day_night_day_frames,day_night_night_frames,day_night_fade_frames;
    uint8_t day_night_start_at_night,weather_curve_code;
} gameworlds_record_t;
static const gameworlds_record_t *active_world;
static const uint32_t *front_palette(void) {return src_front;}
static const uint32_t *back_palette(void) {return src_back;}
static void transition_restore_palette(void) {if(active_world) {usefront(src_front);useback(src_back);}}
''' + weather + spotlight + r'''
int main(void) {
    for (unsigned i=0;i<256;++i) {src_front[i]=0xffa0b080u;src_back[i]=0xff5070c0u;}
    src_front[0]=0x00ffffffu;
    const gameworlds_record_t forest={
        .front_palette=front_palette,.back_palette=back_palette,
        .day_night_mode=1,.day_night_colour=0xff2a2a2au,.day_night_strength=65,
        .weather_mode=3,.weather_density=64,.weather_colour_index=187,
        .weather_palette_flash_strength=51,.weather_lightning_interval=100,
        .weather_lightning_overlay=0,.weather_curve_code=8
    };
    active_world=&forest;spotlight_enabled=1;spotlight_mask_index=32;
    weather_enter(&forest);
    gameworlds_weather_frame(480,320);
    const uint32_t night=weather_palette_blend(src_front[9],0xff2a2a2au,65);
    assert(bound_front[9]==night);
    /* THIS is the real-world fault: old spotlight copied raw .pal here. */
    gameworlds_spotlight_frame(8,8);
    assert(bound_front[9]==night);
    assert(bound_front[32]==spotlight_mask_colour);
    assert(bound_back[9]==weather_palette_blend(src_back[9],0xff2a2a2au,65));
    /* Repeated storm frames still retain the forest tint between flashes. */
    for (unsigned i=0;i<4;++i) {
        weather_update(1);
        gameworlds_spotlight_frame(8,8);
        gameworlds_weather_frame(8,8);
        assert(bound_front[9]==night);
    }
    return 0;
}
'''
with tempfile.TemporaryDirectory() as folder:
    src=Path(folder)/'test.c';src.write_text(harness)
    exe=Path(folder)/'test'
    subprocess.run(['gcc','-std=c11','-O0','-Wall','-Wextra','-Werror',str(src),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.161 native GCC: forest night-tint palette persists through spotlight render; ambient clocks run during transitions')
