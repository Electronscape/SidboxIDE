#!/usr/bin/env python3
"""Stage 5.166.33: saved death FIRE2 quits to title, FIRE1 loads selected save."""
from pathlib import Path
import tempfile, subprocess, sys
root=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(root/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
with tempfile.TemporaryDirectory(prefix='cg516633_ui_') as td:
    p=Path(td)
    render_adventure_runtime(root,p)
    api=(root/'development/tests/stage429_mock_api/apis.h').read_text()
    api=api.replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u').replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u').replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u')
    (p/'apis.h').write_text(api)
    (p/'test.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#define BTN_FIRE 0x01u
static uint32_t hp;
static uint8_t allowed,title_calls,reload_calls,loaded_slot;
static char footer[256];
static uint8_t can_load(void){return allowed;}
static uint8_t title(void){++title_calls;return 1u;}
static uint8_t saved(uint8_t slot){return slot==3u || slot==7u;}
static uint8_t last(void){return 3u;}
static uint8_t reload(uint8_t slot){loaded_slot=slot;++reload_calls;return 1u;}
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
void test_text(int x,int y,const char *s){(void)x;(void)y;
    if(strstr(s,"FIRE2") || strstr(s,"FIRE1 LOAD"))strcpy(footer,s);
}
static void keys(uint8_t b){game_adventure_input(b,0,0,16u,16u,1u);}
static void die(uint8_t with_save){
    hp=5u;allowed=with_save;footer[0]=0;
    keys(0u);
    game_adventure_defeat_setup(&hp,reload,saved,last,1u,"DEAD","Carc'd it",2u,15u,15u,14u,50u,40u);
    game_adventure_defeat_session(can_load,title,0);
    keys(0u);hp=0u;keys(0u);
    for(int n=0;n<50;++n)keys(0u);
    assert(ga_defeat_open);
    ga_defeat_window();
}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    die(1u);
    assert(strstr(footer,"FIRE1 LOAD SLOT  FIRE2 TITLE"));
    keys(BTN_FIRE2);
    assert(title_calls==1u && reload_calls==0u);
    /* Real title/world callback creates the next run. Simulate the new UI. */
    die(1u);
    assert(ga_defeat_slot==3u);
    keys(BTN_FIRE);
    assert(reload_calls==1u && loaded_slot==3u && title_calls==1u);
    die(1u);
    keys(BTN_FIRE); /* FIRE1 still respects D-pad-selected slots. */
    assert(reload_calls==2u && loaded_slot==3u);
    die(0u);
    keys(BTN_FIRE2);
    assert(title_calls==2u && reload_calls==2u);
    die(0u);
    keys(BTN_FIRE);
    assert(title_calls==3u && reload_calls==2u);
    puts("PASS Stage 5.166.33 death UI FIRE2 title / FIRE1 save");
}
''')
    subprocess.run(['gcc','-std=gnu11','-Wall','-Wextra','-Werror','-I',str(p),str(p/'test.c'),'-o',str(p/'test')],check=True)
    subprocess.run([str(p/'test')],check=True)

source=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
assert 'if(!active_world || applying)return 0u;' in source
assert 'gw_reset_title_session();' in source
assert 'gameplayer_reset_stats();' in source
assert 'if(selected_slot>=0)' in source
assert 'gameworlds_request_at(title_world,title_start)' in source
assert 'void gameplayer_reset_stats(void)' in (root/'idelibs/codehelpers/game/gameplayer.rulec').read_text()
print('PASS Stage 5.166.33 saved-session title manager contract')
