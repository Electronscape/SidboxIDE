#!/usr/bin/env python3
"""Regression: multiple worlds own their box, colours, atlas, speed and empty-story setup.

Compile the actual gameadventure.rulec twice as separate namespaced C translation
units; exercise the shared runtime API against both to catch global defaults.
"""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess
import re

root = Path(__file__).resolve().parents[2]
rule = (root / 'idelibs/codehelpers/game/gameadventure.rulec').read_text()
gen = (root / 'gameadventuregen.cpp').read_text()
designer = (root / 'gamedesigner.cpp').read_text()
assert '|| !m_adventure.value(QStringLiteral("skinAtlasId")).toString().isEmpty()' in designer
assert '|| m_adventure.contains(QStringLiteral("dialogX"))' in designer
for key in ('SKIN_TILE_SIZE','FRAMES_PER_CHAR','TEXT_COLOUR_INDEX',
            'TEXT_OUTLINE_ENABLED','OUTLINE_COLOUR_INDEX','DIALOG_X',
            'DIALOG_Y','DIALOG_WIDTH','DIALOG_HEIGHT'):
    assert f'@IDE{{{key}}}' in rule
    assert f'"{key}"' in gen
assert rule.index('game_adventure_start(') < rule.index('game_adventure_text_style(')
assert rule.index('game_adventure_start(') < rule.index('game_adventure_dialogue_box(')

mock_runtime_h = r'''#ifndef MOCK_RUNTIME_H
#define MOCK_RUNTIME_H
#include <stdint.h>
typedef struct { const char *name; uint8_t pickup_kind; uint16_t icon, capacity, initial; } game_adventure_item_t;
typedef struct { uint16_t icon_cells[4]; uint8_t icon_2x2,discardable; } game_adventure_item_style_t;
typedef struct { const char *label, *reply; int16_t next, missing_next, requires, give, take, action; } game_adventure_choice_t;
typedef struct { const char *speaker, *text; game_adventure_choice_t choices[3]; } game_adventure_node_t;
typedef struct { int32_t x,y; uint16_t width,height,radius,first_node; } game_adventure_npc_t;
typedef struct { uint8_t index,delay; } game_adventure_npc_frame_t;
typedef struct { void *sprite; uint8_t first,count,speed; } game_adventure_npc_animation_t;
#define GAME_ADVENTURE_USED_CHOICE_BYTES 96u
#define GAME_ADVENTURE_COMPLETED_NPC_BYTES 256u
#define GAME_ADVENTURE_MAX_DROPS 16u
typedef struct { int32_t x,y; uint16_t item_id; uint8_t active,armed; } game_adventure_drop_t;
typedef void (*game_adventure_action_t)(uint16_t, void*);
void game_adventure_start(const game_adventure_item_t*,uint16_t,const game_adventure_node_t*,uint16_t,
 const game_adventure_npc_t*,uint16_t,const uint8_t*,uint16_t,uint16_t,uint8_t,
 const uint16_t[9],uint8_t,game_adventure_action_t,void*);
void game_adventure_save_progress(uint8_t[96],uint8_t[256]);
void game_adventure_restore_progress(const uint8_t[96],const uint8_t[256]);
void game_adventure_save_drops(game_adventure_drop_t[GAME_ADVENTURE_MAX_DROPS]);
void game_adventure_restore_drops(const game_adventure_drop_t[GAME_ADVENTURE_MAX_DROPS]);
void game_adventure_item_styles(const game_adventure_item_style_t*,uint16_t);
void game_adventure_text_padding(uint8_t);
void game_adventure_story_flags(const uint8_t*,const uint16_t*);
void game_adventure_skin_flips(const uint8_t[9]);
void game_adventure_npc_animations(const game_adventure_npc_animation_t*,uint16_t);
void game_adventure_text_style(uint8_t,uint8_t,uint8_t);
void game_adventure_dialogue_box(int16_t,int16_t,uint16_t,uint16_t);
uint16_t game_adventure_quantity(uint16_t);
void game_adventure_add(uint16_t,uint16_t);
void game_adventure_remove(uint16_t,uint16_t);
extern uint8_t got_colour,got_outline,got_outline_colour,got_tile,got_speed;
extern int16_t got_x,got_y;
extern uint16_t got_w,got_h;
extern const uint8_t *got_skin;
#endif
'''
mock_worlds_h = r'''#ifndef MOCK_WORLDS_H
#define MOCK_WORLDS_H
#include <stdint.h>
typedef void (*gameworlds_inventory_put_t)(const char*,uint16_t,void*);
typedef uint32_t (*gameworlds_inventory_get_t)(const char*,void*);
#endif
'''
impl = r'''#include "gameadventureruntime.h"
#include <stdint.h>
uint8_t got_colour,got_outline,got_outline_colour,got_tile,got_speed;
int16_t got_x,got_y; uint16_t got_w,got_h;
const uint8_t *got_skin;
void game_adventure_start(const game_adventure_item_t*a,uint16_t b,const game_adventure_node_t*c,uint16_t d,
 const game_adventure_npc_t*e,uint16_t f,const uint8_t*skin,uint16_t w,uint16_t h,uint8_t tile,
 const uint16_t ix[9],uint8_t speed,game_adventure_action_t ac,void*u)
{ (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)w;(void)h;(void)ix;(void)ac;(void)u;
  got_skin=skin;got_tile=tile;got_speed=speed;got_colour=15;got_x=20;got_y=148; }
void game_adventure_save_progress(uint8_t a[96],uint8_t b[256]){(void)a;(void)b;}
void game_adventure_restore_progress(const uint8_t a[96],const uint8_t b[256]){(void)a;(void)b;}
void game_adventure_save_drops(game_adventure_drop_t a[GAME_ADVENTURE_MAX_DROPS]){(void)a;}
void game_adventure_restore_drops(const game_adventure_drop_t a[GAME_ADVENTURE_MAX_DROPS]){(void)a;}
void game_adventure_item_styles(const game_adventure_item_style_t*a,uint16_t n){(void)a;(void)n;}
void game_adventure_text_padding(uint8_t n){(void)n;}
void game_adventure_story_flags(const uint8_t*a,const uint16_t*b){(void)a;(void)b;}
void game_adventure_skin_flips(const uint8_t a[9]){(void)a;}
void game_adventure_npc_animations(const game_adventure_npc_animation_t*a,uint16_t b){(void)a;(void)b;}
void game_adventure_text_style(uint8_t a,uint8_t b,uint8_t c){got_colour=a;got_outline=b;got_outline_colour=c;}
void game_adventure_dialogue_box(int16_t x,int16_t y,uint16_t w,uint16_t h){got_x=x;got_y=y;got_w=w;got_h=h;}
uint16_t game_adventure_quantity(uint16_t n){(void)n;return 0;}
void game_adventure_add(uint16_t n,uint16_t a){(void)n;(void)a;}
void game_adventure_remove(uint16_t n,uint16_t a){(void)n;(void)a;}
static const uint8_t forest_pixels[128]={1};
static const uint8_t world1_pixels[128]={2};
const uint8_t *forest_gameassets_find_ppb(const char *s,uint16_t *w,uint16_t *h)
{(void)s;*w=32;*h=32;return forest_pixels;}
const uint8_t *world1_gameassets_find_ppb(const char *s,uint16_t *w,uint16_t *h)
{(void)s;*w=32;*h=32;return world1_pixels;}
'''

with TemporaryDirectory(prefix='stage54i-') as td:
    base = Path(td)
    (base / 'gameadventureruntime.h').write_text(mock_runtime_h)
    (base / 'gameworlds.h').write_text(mock_worlds_h)
    (base / 'stub.c').write_text(impl)
    setups = [
        ('world1', {'SKIN_TILE_SIZE':8,'FRAMES_PER_CHAR':2,'TEXT_COLOUR_INDEX':15,'TEXT_OUTLINE_ENABLED':0,'OUTLINE_COLOUR_INDEX':1,'DIALOG_X':20,'DIALOG_Y':148,'DIALOG_WIDTH':440,'DIALOG_HEIGHT':96,'DIALOG_PADDING':8}),
        ('forest', {'SKIN_TILE_SIZE':16,'FRAMES_PER_CHAR':4,'TEXT_COLOUR_INDEX':9,'TEXT_OUTLINE_ENABLED':1,'OUTLINE_COLOUR_INDEX':6,'DIALOG_X':33,'DIALOG_Y':98,'DIALOG_WIDTH':372,'DIALOG_HEIGHT':120,'DIALOG_PADDING':0}),
    ]
    for name, style in setups:
        dest=base / name
        (dest / 'gamehelpers').mkdir(parents=True)
        (dest / 'gameassets').mkdir()
        (dest / 'gameassets/gameassets.h').write_text('''#include <stdint.h>\nconst uint8_t *gameassets_find_ppb(const char *, uint16_t *, uint16_t *);\n''')
        headers='''#include "gameadventureruntime.h"\n#include "gameworlds.h"\n#define GAME_ADVENTURE_STORY_ITEM_COUNT 0u\n#define GAME_ADVENTURE_STORY_NODE_COUNT 0u\n#define GAME_ADVENTURE_STORY_NPC_COUNT 0u\n'''
        (dest / 'gamehelpers/gameadventure.h').write_text(headers)
        symbols='\n'.join(f'#define {x} {name}_{x}' for x in (
            'gameadventure_setup','gameadventure_store_inventory','gameadventure_load_inventory',
            'gameadventure_save_progress','gameadventure_restore_progress',
            'gameadventure_on_event','gameassets_find_ppb'))+'\n'
        (dest / 'world_symbols.h').write_text(symbols)
        source = rule
        source = re.sub(r'(?ms)^@IDE_SECTION\{LINKED_ACTION\}.*?^@IDE_SECTION_END\n?', '', source)
        source = re.sub(r'(?ms)^@IDE_IF\{HAS_WORLD_OBJECTS\}\n.*?^@IDE_END\n', '', source)
        source = re.sub(r'(?m)^@IDE_IF\{HAS_SKIN\}\n(.*?)^@IDE_END\n', lambda m:m.group(1), source, flags=re.S)
        fields = {**style,'ITEM_ROWS':'{0,0,0,0,0},','ITEM_STYLE_ROWS':'{{0u,0u,0u,0u},0u,0u},','NODE_ROWS':'{0},','CHOICE_FLAGS':'0',
          'NPC_ROWS':'{0},','NPC_COMPLETED_NODES':'65535u','NPC_FRAME_ROWS':'{0},',
          'NPC_ANIMATION_ROWS':'{0},','SKIN_CELLS':','.join(map(str,range(9))),
          'SKIN_FLIPS':','.join('0' for _ in range(9)),
          'LINKED_ACTION_CASES':'','SKIN_PATH':'"graphics/box.ppb"'}
        for field,value in fields.items():
            source=source.replace(f'@IDE{{{field}}}',str(value))
        assert '@IDE' not in source, source
        (dest / 'gamehelpers/gameadventure.c').write_text('#include "../world_symbols.h"\n'+source)
    main = r'''#include "gameadventureruntime.h"
#include <assert.h>
void world1_gameadventure_setup(void);
void forest_gameadventure_setup(void);
int main(void) {
    world1_gameadventure_setup();
    assert(got_skin && got_tile==8 && got_speed==2 && got_colour==15);
    assert(got_x==20 && got_y==148 && got_w==440 && got_h==96);
    forest_gameadventure_setup();
    assert(got_skin && got_tile==16 && got_speed==4);
    assert(got_colour==9 && got_outline==1 && got_outline_colour==6);
    assert(got_x==33 && got_y==98 && got_w==372 && got_h==120);
    world1_gameadventure_setup();
    assert(got_colour==15 && got_x==20 && got_w==440);
    return 0;
}
'''
    (base/'main.c').write_text(main)
    args=['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(base),
           str(base/'stub.c'),str(base/'main.c')]
    args += [str(base/name/'gamehelpers/gameadventure.c') for name,_ in setups]
    args += ['-o',str(base/'test')]
    subprocess.run(args, check=True)
    subprocess.run([str(base/'test')], check=True)
print('Stage 5.4i: two namespaced worlds independently configure one shared Adventure runtime: PASS')
