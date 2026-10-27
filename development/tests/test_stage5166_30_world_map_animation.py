#!/usr/bin/env python3
"""Stage 5.166.30 native animated World Map, editor persistence and death zone contracts."""
from pathlib import Path
import subprocess, tempfile, sys
root=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(root/'development/tests'))
from stage442_render_test_helpers import render_adventure_runtime
with tempfile.TemporaryDirectory(prefix='cg516630_') as folder:
    p=Path(folder)
    render_adventure_runtime(root,p)
    (p/'apis.h').write_text((root/'development/tests/stage429_mock_api/apis.h').read_text())
    (p/'test.c').write_text(r'''
#include "adventureruntime.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static const char *current(void){return "World1";}
static uint8_t map_pixels[8u*16u];
static uint16_t cells[60u*40u];
static unsigned drawn;
static const uint8_t *last_pixel;
void test_colour(uint8_t c){(void)c;}
void test_rect(int x,int y,int w,int h){(void)x;(void)y;(void)w;(void)h;}
void test_text(int x,int y,const char *s){(void)x;(void)y;(void)s;}
void test_bob(gfxbob_t *bob){++drawn;last_pixel=bob->imgdat;}
int main(void){
    static const game_adventure_map_animation_t animations[]={
        {0u,4u,5u,1u,0u}, /* loop */
        {4u,3u,2u,0u,1u}, /* one-shot ping-pong */
        {8u,3u,2u,1u,1u}  /* looping ping-pong */
    };
    game_adventure_world_map_animations(animations,3u);
    ga_map_flash_frames=0u;assert(ga_map_animated_cell(0u)==0u);
    ga_map_flash_frames=5u;assert(ga_map_animated_cell(0u)==1u);
    ga_map_flash_frames=15u;assert(ga_map_animated_cell(0u)==3u);
    ga_map_flash_frames=20u;assert(ga_map_animated_cell(0u)==0u);
    ga_map_flash_frames=0u;assert(ga_map_animated_cell(4u)==4u);
    ga_map_flash_frames=2u;assert(ga_map_animated_cell(4u)==5u);
    ga_map_flash_frames=4u;assert(ga_map_animated_cell(4u)==6u);
    ga_map_flash_frames=6u;assert(ga_map_animated_cell(4u)==5u);
    ga_map_flash_frames=8u;assert(ga_map_animated_cell(4u)==4u);
    ga_map_flash_frames=100u;assert(ga_map_animated_cell(4u)==4u);
    ga_map_flash_frames=4u;assert(ga_map_animated_cell(8u)==10u);
    ga_map_flash_frames=6u;assert(ga_map_animated_cell(8u)==9u);
    ga_map_flash_frames=8u;assert(ga_map_animated_cell(8u)==8u);
    ga_map_flash_frames=10u;assert(ga_map_animated_cell(8u)==9u);
    ga_map_flash_frames=10u;assert(ga_map_animated_cell(11u)==11u);
    game_adventure_world_map_animations(0,0u);
    assert(ga_map_animated_cell(0u)==0u);
    game_adventure_world_map_animations(animations,3u);
    for(unsigned i=0;i<60u*40u;i++)cells[i]=65535u;
    cells[10u*60u+10u]=0u;
    static const game_adventure_map_point_t pt[]={{150,150,"World1",65535u,0u}};
    game_adventure_start(0,0,0,0,0,0,0,0,0,8,0,1,0,0);
    game_adventure_world_map(pt,1u,480u,320u,current);
    game_adventure_world_map_tiles(cells,60u,40u,map_pixels,"map.ppb",8u,16u,8u);
    game_adventure_world_map_animations(animations,3u);
    ga_map_open=1u;
    ga_map_pan_x=0;ga_map_pan_y=0;
    ga_map_flash_frames=5u;
    ga_world_map_window();
    assert(drawn==1u);
    assert(last_pixel==map_pixels+64u); /* second atlas cell */
    puts("PASS native map cell loop, bounce, hold and actual rendering");
    return 0;
}
''')
    subprocess.run(['gcc','-std=gnu11','-Wall','-Wextra','-Werror',
                    '-I',str(p),str(p/'test.c'),'-o',str(p/'native')],check=True)
    subprocess.run([str(p/'native')],check=True)
# Compile and execute the exact shipped Death Zone overlap/note functions.
objects=(root/'idelibs/codehelpers/game/worldobjects.rulec').read_text()
begin=objects.index('const char *game_world_objects_death_zone_note(')
end=objects.index('uint8_t game_world_objects_fire2_action(',begin)
with tempfile.TemporaryDirectory(prefix='cg516630_deathzone_') as folder:
    p=Path(folder)
    src='''#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#define GAME_OBJECT_DEATH_ZONE 6u
typedef struct { int32_t x,y; uint16_t width,height; uint8_t active,type; const char *death_note; } game_world_object_t;
'''+objects[begin:end]+'''
int main(void){
  game_world_object_t zone[2]={
      {.x=20,.y=20,.width=16,.height=16,.active=1,.type=GAME_OBJECT_DEATH_ZONE,.death_note="Killed by a spikey mushroom"},
      {.x=80,.y=80,.width=16,.height=16,.active=1,.type=GAME_OBJECT_DEATH_ZONE,.death_note="You landed on a cactus"}};
  assert(game_world_objects_death_zone(zone,2,23,25,8,8));
  assert(game_world_objects_death_zone_note(zone,2,23,25,8,8)==zone[0].death_note);
  assert(game_world_objects_death_zone_note(zone,2,80,83,8,8)==zone[1].death_note);
  assert(!game_world_objects_death_zone(zone,2,56,56,4,4));
  assert(!game_world_objects_death_zone_note(zone,2,56,56,4,4));
  zone[0].active=0;
  assert(!game_world_objects_death_zone_note(zone,2,23,25,8,8));
  puts("PASS native Death Zone source lookup / active and overlap rules");
  return 0;
}
'''
    (p/'zone.c').write_text(src)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',
                    str(p/'zone.c'),'-o',str(p/'zone')],check=True)
    subprocess.run([str(p/'zone')],check=True)
ui=(root/'gamerpguieditors.h').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
rule=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
for q in ('Paint map tiles','Choose flag art','Selected Tile Animation','VBlanks/frame',
          'cgRpgMapAnimationFrame','animationTimer->start()','animatedSections',
          'QStringLiteral("animations"),savedAnimations', 'sideScroll->setWidget(side)',
          'colourSettings->addLayout(boundaryRow)','colourSettings->addLayout(flashRow)'):
    assert q in ui,q
for q in ('WORLD_MAP_ANIM_COUNT','WORLD_MAP_ANIMATIONS','orderedAnimations','cell+frames>atlasCount'):
    assert q in gen,q
for q in ('static const game_adventure_map_animation_t map_animations[]=',
          'game_adventure_world_map_animations(map_animations,'):
    assert q in rule,q
obj=(root/'gamedesigner.cpp').read_text()
items=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
assert 'deathNoteCard.panel->setVisible(isHazard || isEnemy || behaviour == QStringLiteral("deathzone"))' in obj
assert '@IDE_IF{IS_DEATH_ZONE}' in items
assert 'game_world_objects_death_zone_note(' in items
assert 'game_adventure_defeat_note(note);' in items
assert 'sourceFields.insert(QStringLiteral("HAS_ADVENTURE"),flag(hasAdventure()))' in (root/'gamedesigner_export.cpp').read_text()
print('PASS Stage 5.166.30 world map designer/generator and death zone source contracts')
