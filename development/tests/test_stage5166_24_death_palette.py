#!/usr/bin/env python3
"""Stage 5.166.24: runtime death-note, unsaved death dismiss, map flash and map painter palette."""
from pathlib import Path
import tempfile, subprocess, sys
root=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(root/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
with tempfile.TemporaryDirectory(prefix='cg516624_') as folder:
    p=Path(folder)
    render_adventure_runtime(root,p)
    api=(root/'development/tests/stage429_mock_api/apis.h').read_text()
    api=api.replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u')
    api=api.replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u')
    api=api.replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u')
    (p/'apis.h').write_text(api)
    (p/'test.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <string.h>
#include <stdio.h>
static uint32_t hp=5u;
static uint8_t permitted=0u, title_calls=0u, reload_calls=0u;
static uint8_t allow(void){return permitted;}
static uint8_t go_title(void){++title_calls;return 1u;}
static uint8_t save_exists(uint8_t slot){return slot==3u;}
static uint8_t load(uint8_t slot){assert(slot==3u);++reload_calls;return 1u;}
static uint8_t last_save(void){return 3u;}
static const char *current_world(void){return "Current";}
static char captured[1024];
static uint8_t palette_color;
static uint8_t flash_found;
void test_colour(uint8_t c){palette_color=c;}
void test_rect(int x,int y,int w,int h){
    if(palette_color==27u && x==98 && y==98 && w==16 && h==1)flash_found=1u;
}
void test_text(int x,int y,const char *s){(void)x;(void)y;
    if(strlen(captured)+strlen(s)+2u<sizeof(captured)){strcat(captured,s);strcat(captured,"|");}
}
void test_bob(gfxbob_t *b){(void)b;}
static void keys(uint8_t b){(void)game_adventure_input(b,0,0,16,16,1);}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_defeat_setup(&hp,load,save_exists,last_save,1,"YOU ARE DEAD","You carc'd it",2,15,15,14,50,40);
    game_adventure_defeat_session(allow,go_title,0);
    game_adventure_defeat_note("You were killed by the extraordinary, exceptionally spikey mushroom in the dangerous forest of doom");
    keys(0);hp=0u;keys(0);
    for(int i=0;i<50;++i)keys(0);
    ga_defeat_window();
    assert(strstr(captured,"YOU ARE DEAD")!=NULL);
    assert(strstr(captured,"You were killed")!=NULL);
    assert(strstr(captured,"mushroom")!=NULL);
    assert(strstr(captured,"FIRE1 / FIRE2  RETURN TO TITLE")!=NULL);
    assert(reload_calls==0u);
    keys(BTN_FIRE2);assert(title_calls==1u);
    /* Saved session still loads, rather than returning to title. */
    hp=5u;permitted=1u;
    game_adventure_defeat_setup(&hp,load,save_exists,last_save,1,"YOU ARE DEAD","You carc'd it",2,15,15,14,50,40);
    game_adventure_defeat_session(allow,go_title,0);
    keys(0);hp=0u;keys(0);
    for(int i=0;i<50;++i)keys(0);
    keys(BTN_FIRE);assert(reload_calls==1u && title_calls==1u);
    game_adventure_world_map_flag_flash(27u);
    assert(ga_map_flag_flash_colour==27u);
    {static const game_adventure_map_point_t pts[]={{100,100,"Current",65535u,0u}};
     game_adventure_world_map(pts,1u,480u,320u,current_world);
     ga_map_open=1u;ga_map_flash_frames=0u;
     ga_world_map_window();assert(flash_found);
     ga_map_open=0u;
    }
    puts("PASS Stage 5.166.24 native death-note and title/save policy");
    return 0;
}
''')
    subprocess.run(['gcc','-std=gnu11','-Wall','-Wextra','-Werror','-I',str(p),str(p/'test.c'),'-o',str(p/'runtime')],check=True)
    subprocess.run([str(p/'runtime')],check=True)
ui=(root/'gamerpguieditors.h').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
rule=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
for string in ('Preview palette (game resources)','paletteChoice->currentData().toString()',
    'sheet.setColorTable(currentBank)','flagFlashColour','activePalette()',
    '{QStringLiteral("palette"),paletteChoice->currentData().toString()}',
    '{QStringLiteral("flagFlashColour"),flagFlashColour->value()}'):
    assert string in ui,string
assert 'WORLD_MAP_FLAG_FLASH_COLOUR' in gen
assert 'game_adventure_world_map_flag_flash(@IDE{WORLD_MAP_FLAG_FLASH_COLOUR}u);' in rule
assert 'r.deathNote' in (root/'gamedesigner_export.cpp').read_text()
assert 'deathNote' in (root/'gamedesigner_project.cpp').read_text()
print('PASS Stage 5.166.24 map resource palette, flag flash colour and death note persistence contracts')
