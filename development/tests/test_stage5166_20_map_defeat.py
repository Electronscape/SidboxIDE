#!/usr/bin/env python3
"""Native runtime coverage: map art, highlighted flags, auto-pan and defeat fade."""
from pathlib import Path
import subprocess,sys,tempfile
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
with tempfile.TemporaryDirectory(prefix='cg16620_') as d:
 p=Path(d)
 render_adventure_runtime(ROOT,p)
 (p/'apis.h').write_text((ROOT/'development/tests/stage429_mock_api/apis.h').read_text().replace(
     '#define BTN_FIRE2 0x01u','#define BTN_FIRE2 0x02u').replace(
     '#define BTN_UP 0x02u','#define BTN_UP 0x04u').replace(
     '#define BTN_DOWN 0x04u','#define BTN_DOWN 0x08u'))
 (p/'test.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static unsigned bob_count,rect_count;
static const char *current(void){return "Forest";}
static uint32_t health=100u;
static uint8_t reload(uint8_t s){return s==2u;}
static uint8_t exists(uint8_t s){return s==2u;}
static uint8_t last(void){return 2u;}
void test_colour(uint8_t c){(void)c;}
void test_text(int x,int y,const char *str){(void)x;(void)y;(void)str;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;++rect_count;}
void test_bob(gfxbob_t *b){ assert(b && b->imgdat);++bob_count; }
int main(void){
    static uint8_t art[24u*24u];
    static uint16_t tiles[128u*96u];
    for(unsigned i=0;i<128u*96u;++i)tiles[i]=65535u;
    tiles[51u*128u+71u]=0u;
    static const game_adventure_map_point_t pts[]={
      {576,408,"Forest",0u,1u},
      {100,80,"World1",3u,0u}};
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_world_map(pts,2u,1024u,768u,current);
    game_adventure_world_map_tiles(tiles,128u,96u,art,"map.ppb",16u,16u,8u);
    ga_map_open=1u;
    ga_map_center_current();
    assert(ga_map_pan_x==336 && ga_map_pan_y==248);
    assert(!ga_map_drag); /* Ensure this compile fails if touch-drag is reintroduced. */
    ga_world_map_window();
    assert(bob_count>=5u); /* One painted tile and 2x2 flag art. */
    assert(ga_map_flash_frames==0u);
    (void)game_adventure_input(BTN_RIGHT|BTN_DOWN,0,0,16u,16u,1u);
    assert(ga_map_pan_x==340 && ga_map_pan_y==252);
    assert(ga_map_flash_frames==1u);
    (void)game_adventure_input(BTN_FIRE2,0,0,16u,16u,1u);
    assert(!ga_map_open);
    game_adventure_defeat_setup(&health,reload,exists,last,1u,"YOU ARE DEAD","Retry?",2u,15u,15u,14u,50u,40u);
    static const uint16_t nine[]={0u,1u,2u,3u,4u,5u,6u,7u,8u};
    static const uint8_t flip[9]={0};
    game_adventure_defeat_style(1u,2u,1u,3u,art,"",24u,24u,8u,nine,flip);
    assert(ga_defeat_skin_pixels==art);
    /* 5.166.21: Defeat styling honours the Journal's larger native glyphs. */
    game_adventure_defeat_style(4u,8u,1u,3u,art,"",24u,24u,8u,nine,flip);
    assert(ga_defeat_scale_x==4u && ga_defeat_scale_y==8u);
    game_adventure_defeat_style(1u,2u,1u,3u,art,"",24u,24u,8u,nine,flip);
    (void)game_adventure_input(0u,0,0,16u,16u,1u); /* health arms */
    health=0u;
    (void)game_adventure_input(0u,0,0,16u,16u,1u);
    assert(ga_defeat_open && ga_defeat_fade_tick<=1u);
    ga_defeat_window();assert(rect_count>0u); /* Fade-out mask */
    for(int i=0;i<50;++i) (void)game_adventure_input(0u,0,0,16u,16u,1u);
    assert(ga_defeat_fade_tick==50u);
    ga_defeat_window();assert(bob_count>10u); /* Nine-slice frame draws */
    puts("PASS Stage 5.166.20: painted map, 2x2 flag, center, D-pad and defeat styling");
    return 0;
}
'''.replace('assert(!ga_map_drag); /* Ensure this compile fails if touch-drag is reintroduced. */','/* The drag state and touchscreen-move path no longer exist. */'))
 subprocess.run(['gcc','-std=gnu11','-O0','-Wall','-Wextra','-Werror','-I',str(p),str(p/'test.c'),'-o',str(p/'native')],check=True)
 subprocess.run([str(p/'native')],check=True)
print('PASS Stage 5.166.20: editor has tile-painting, saved map cells and defeat skin settings')
ui=(ROOT/'gamerpguieditors.h').read_text()
assert 'CgRpgMapCanvas' in ui and 'Paint map tiles' in ui and 'onPaint' in ui
assert 'fontScaleX' in ui and 'outlineEnabled' in ui and 'Nine-slice PPB frame' in ui
source=(ROOT/'gameadventuregen.cpp').read_text()
for key in ['WORLD_MAP_TILES','WORLD_MAP_ATLAS','WORLD_MAP_TILE_SIZE','DEFEAT_ATLAS','DEFEAT_CELLS','DEFEAT_SCALE_Y']:
 assert key in source

# Backward compatibility and V1 memory: schematic legacy maps stay unpainted.
gen=(ROOT/'gameadventuregen.cpp').read_text()
assert 'const bool schematicOnly=atlasRel.isEmpty() && !hasPaint;' in gen
assert 'const int count=schematicOnly?0:' in gen
assert 'QString::number(schematicOnly?0:mapW/tile)' in gen
print('PASS Stage 5.166.20: schematic legacy map keeps compact export')
