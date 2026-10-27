#!/usr/bin/env python3
"""Stage 5.166.15: V1 project budget bar and real ten-slot checkpoint modal."""
from pathlib import Path
import tempfile, subprocess, sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
main=(ROOT/'mainwindow.cpp').read_text()
body=main[main.index('void updateAppletMemoryPanel('):main.index('} // namespace',main.index('void updateAppletMemoryPanel('))]
for snippet in ('sidboxMemoryRow_heap', 'heapRow->setVisible(v2)',
                'sidboxMemoryLabel_stack', 'QObject::tr("Budget")',
                'sidboxMemoryBar_stack','elf.spanBytes, true',
                'sidboxMemSize(allowance)', 'Budget remaining: %1',
                'OVER %1%', 'QProgressBar::chunk'):
    assert snippet in body, snippet
assert '0xD05E0000ULL - elf.startAddress' not in body
assert 'game_adventure_choose_save_slot(%1u)' in (ROOT/'gamedesigner_export.cpp').read_text()
assert 'game_adventure_save_slot_callbacks(gameworlds_checkpoint_request' in (ROOT/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert '#include "gameadventureruntime.h" /* In-game save-slot picker */' in (ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
assert 'Build: 5.166.15.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
with tempfile.TemporaryDirectory(prefix='stage516615_save_') as d:
    d=Path(d);render_adventure_runtime(ROOT,d)
    mock=(ROOT/'development/tests/stage429_mock_api/apis.h').read_text()
    mock=mock.replace('#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u').replace('#define BTN_UP 0x02u','#define BTN_UP 0x04u').replace('#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u')
    mock=mock[:-len('#endif\n')]+'''#define BTN_FIRE 0x01u
#define BTN_LEFT 0x10u
#define BTN_RIGHT 0x20u
#endif
'''
    (d/'apis.h').write_text(mock)
    (d/'test.c').write_text(r'''
#include "adventureruntime.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
static unsigned requests,exists_calls,last_slot=255,windows;
static uint8_t occupied[10];
static uint8_t request(uint8_t slot){requests++;last_slot=slot;return 1u;}
static uint8_t exists(uint8_t slot){exists_calls++;return occupied[slot];}
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char*s){
    (void)x;(void)y;
    if(strstr(s,"CHOOSE SLOT"))windows++;
}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_bob(gfxbob_t *b){(void)b;}
static void input(uint8_t k){game_adventure_input(k,0,0,16,16,1);}
int main(void){
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_save_slot_callbacks(request,exists);
    occupied[7]=1;
    assert(game_adventure_choose_save_slot(7u));
    assert(exists_calls==10);assert(game_adventure_open());
    assert(game_adventure_gameplay_buttons(BTN_FIRE|BTN_RIGHT)==0u);
    game_adventure_draw(0,0,0,0);assert(windows==1);
    input(BTN_FIRE); /* occupied slot: confirmation, NOT a write */
    assert(requests==0);
    input(0);input(BTN_FIRE2); /* back to slots */
    assert(requests==0 && game_adventure_open());
    input(0);input(BTN_FIRE); /* confirm again */
    assert(requests==0);
    input(0);input(BTN_FIRE); /* final yes */
    assert(requests==1 && last_slot==7 && !game_adventure_open());
    assert(game_adventure_choose_save_slot(2));
    assert(exists_calls==20);
    input(0);input(BTN_DOWN);input(0);input(BTN_RIGHT); /* slot 8 */
    input(0);input(BTN_LEFT); /* slot 3 */
    input(0);input(BTN_FIRE); /* empty => direct deferred request */
    assert(requests==2 && last_slot==3 && !game_adventure_open());
    assert(game_adventure_choose_save_slot(1));
    input(0);input(BTN_FIRE2); /* cancel without write */
    assert(requests==2 && !game_adventure_open());
    assert(!game_adventure_choose_save_slot(10));
    puts("PASS Stage 5.166.15 native ten-slot save selector, overwrite, cancel, cached slots");
    return 0;
}
''')
    exe=d/'test'
    subprocess.run(['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror','-I',str(d),
                    str(d/'adventureruntime.c'),str(d/'test.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.15 V1 budget panel source assertions')
