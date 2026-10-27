#!/usr/bin/env python3
"""Check runtime ordinal mapping ignores hidden quests without changing IDs."""
from pathlib import Path
import tempfile,subprocess,sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
with tempfile.TemporaryDirectory(prefix='journal_hidden_') as work:
    d=Path(work)
    render_adventure_runtime(ROOT,d)
    (d/"apis.h").write_text((ROOT/"development/tests/stage429_mock_api/apis.h").read_text())
    (d/'test.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <stdio.h>
static uint16_t count(void){return 3u;}
static const char* title(uint16_t i){return i==0?"Secret":i==1?"Main":"Future";}
static uint8_t status(uint16_t i){return i==0?0u:1u;}
static uint8_t visible(uint16_t i){return i!=0u;}
static int16_t tracked(void){return 2;}
static uint8_t track(const char* id){(void)id;return 1u;}
static const game_adventure_quest_ui_t ui={count,title,title,title,title,status,tracked,track,visible};
static uint16_t visited=0xffffu;
static void on_node(uint16_t index){visited=index;}
int main(void){
    ga_quest_ui=&ui;
    assert(ga_quest_count()==2u);
    assert(ga_quest_index(0u)==1u);
    assert(ga_quest_index(1u)==2u);
    assert(ga_quest_index(2u)==0xffffu);
    static const game_adventure_node_t dialogue[1]={0};
    ga_nodes=dialogue; ga_node_count=1u;
    game_adventure_set_node_signal(on_node);
    ga_next_node(0);
    assert(visited==0u);
    ga_next_node(-1);
    assert(visited==0u); /* Closing is NOT a new offer. */
    puts("PASS Stage 5.166.7 journal visibility and dialogue node-entry callback");
    return 0;
}
''')
    command=['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
             '-Wl,--gc-sections','-I',str(d),str(d/'test.c'),'-o',str(d/'test')]
    subprocess.run(command,check=True)
    subprocess.run([str(d/'test')],check=True)
