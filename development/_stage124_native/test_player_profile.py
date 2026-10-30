from pathlib import Path
import tempfile,subprocess
root=Path(__file__).resolve().parents[2]
sdk=root/'idelibs/codehelpers/game'
C=(sdk/'gameplayer.rulec').read_text()
H=(sdk/'gameplayer.ruleh').read_text()
fields={
'HEALTH':'100','LIVES':'3','SCORE':'0','CUSTOM_HITBOX':'0','PHYSICS_PRESET':'0',
'HITBOX_X':'0','HITBOX_Y':'0','HITBOX_W':'32','HITBOX_H':'32',
'PPB_PATH':'"unused.ppb"','ATLAS_W':'32','ATLAS_H':'32','CELL_W':'32','CELL_H':'32',
'INVENTORY_ROWS':'','INVENTORY_COUNT':'0','CUSTOM_STAT_ROWS':'','CUSTOM_STAT_COUNT':'0',
'PHYSICS_PROFILE_COUNT':'2',
'PHYSICS_PROFILE_ROWS':'    {0u,0u,3,7,35,9,12u,0u,1u,24u,15u},\n    {9u,0u,3,7,35,9,12u,1u,2u,30u,4u},\n'
}
for k,v in fields.items():C=C.replace('@IDE{'+k+'}',v)
assert '@IDE{' not in C
with tempfile.TemporaryDirectory(prefix='cg-combat124-') as td:
 d=Path(td)
 (d/'gameplayer.c').write_text(C)
 (d/'gameplayer.h').write_text(H)
 (d/'apis.h').write_text('''#include <stdint.h>
#define BTN_FIRE 16u
#define BTN_UP 1u
#define BTN_LEFT 2u
#define BTN_RIGHT 4u
#define F_OK 0
#define SD_READ 1
int sfopen(int,char*,int);int sfclose(int);int sfread(int,void*,uint32_t,uint32_t*);int sflseek(int,uint32_t);
typedef struct{const uint8_t*imgdat;uint16_t atlas_stride,atlas_height,width,height,scale;}gfxbob_t;
''')
 (d/'gametilemap.h').write_text('''#include <stdint.h>
typedef struct{int16_t walk_speed,jump_speed,gravity,max_fall_speed;uint8_t mode,drag;}game_tile_player_t;
void game_tile_player_set_physics(game_tile_player_t*,uint8_t);void game_tile_player_set_force_drag(game_tile_player_t*,uint8_t);
''')
 (d/'test.c').write_text('''#include "gameplayer.h"
#include <assert.h>
#include <stdio.h>
void game_tile_player_set_physics(game_tile_player_t*p,uint8_t m){p->mode=m;}
void game_tile_player_set_force_drag(game_tile_player_t*p,uint8_t d){p->drag=d;}
int sfopen(int a,char*b,int c){(void)a;(void)b;(void)c;return 1;}
int sfclose(int a){(void)a;return 0;}
int sfread(int a,void*b,uint32_t c,uint32_t*d){(void)a;(void)b;(void)c;(void)d;return 1;}
int sflseek(int a,uint32_t b){(void)a;(void)b;return 1;}
int main(void){game_tile_player_t p={0};
assert(gameplayer_apply_physics(&p,0));assert(!gameplayer_combat_enabled());
assert(gameplayer_movement_buttons(BTN_FIRE|BTN_UP)==(BTN_FIRE|BTN_UP));
assert(!gameplayer_attack_step(BTN_FIRE));
assert(gameplayer_apply_physics(&p,9));assert(gameplayer_combat_enabled());
assert(gameplayer_attack_damage()==2 && gameplayer_attack_reach()==30);
assert(gameplayer_movement_buttons(BTN_FIRE|BTN_UP)==BTN_UP);
assert(!gameplayer_attack_step(BTN_FIRE)); /* held after mode switch: safe */
assert(!gameplayer_attack_step(0));
assert(gameplayer_attack_step(BTN_FIRE));assert(gameplayer_attack_started());
assert(!gameplayer_attack_step(BTN_FIRE));assert(!gameplayer_attack_step(0));
assert(!gameplayer_attack_step(BTN_FIRE));
for(int i=0;i<4;i++)gameplayer_attack_step(0);
assert(gameplayer_attack_step(BTN_FIRE));assert(gameplayer_attack_total()==2);
gameplayer_attack_register_hits(2);assert(gameplayer_attack_hits()==2);
assert(gameplayer_attack_hit_total()==2);
assert(gameplayer_apply_physics(&p,0));assert(!gameplayer_combat_enabled());
puts("Stage124 native player profile combat: PASS");return 0;}
''')
 res=subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Wno-type-limits','-Wno-missing-field-initializers','-Wno-unused-function','-I',str(d),str(d/'gameplayer.c'),str(d/'test.c'),'-o',str(d/'run')],capture_output=True,text=True)
 if res.returncode:raise RuntimeError(res.stderr)
 proc=subprocess.run([str(d/'run')],capture_output=True,text=True)
 if proc.returncode:raise RuntimeError(proc.stderr+proc.stdout)
 print(proc.stdout.strip())
