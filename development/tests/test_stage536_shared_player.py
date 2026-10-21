"""Host GCC V1 shared player generator smoke-test, no Qt required."""
from pathlib import Path
import subprocess
import tempfile

sdk = Path(__file__).resolve().parents[2] / "idelibs/codehelpers/game"
template_c = (sdk / "gameplayer.rulec").read_text()
template_h = (sdk / "gameplayer.ruleh").read_text()
fields = {"PPB_PATH": '"players/hero.ppb"',"ATLAS_W":"64","ATLAS_H":"32",
          "CELL_W":"16","CELL_H":"16","HEALTH":"100","LIVES":"3",
          "SCORE":"250","CUSTOM_HITBOX":"1", "PHYSICS_PRESET":"2",
          "HITBOX_X":"2", "HITBOX_Y":"3", "HITBOX_W":"12", "HITBOX_H":"13",
          "INVENTORY_COUNT":"2",
          "INVENTORY_ROWS":'    {"key", 1u, 1u},\n    {"gold", 7u, 0u},\n',
          "CUSTOM_STAT_COUNT":"0", "CUSTOM_STAT_ROWS":""}
for key, val in fields.items(): template_c = template_c.replace('@IDE{' + key + '}',val)
assert '@IDE{' not in template_c
with tempfile.TemporaryDirectory(prefix="sbpi-stage536-") as tmp:
    root = Path(tmp)
    (root / "gameplayer.c").write_text(template_c)
    (root / "gameplayer.h").write_text(template_h)
    (root / "apis.h").write_text('''#ifndef MOCK_APIS_H
#define MOCK_APIS_H
#include <stdint.h>
#define F_OK 0
#define SD_READ 1
int sfopen(int,const char*,int); int sfclose(int);
int sfread(int,void*,uint32_t,uint32_t*);int sflseek(int,uint32_t);
typedef struct {
 const uint8_t *imgdat; uint8_t flags,flagval[7];
 uint16_t atlas_stride, atlas_height, width, height;
 int16_t drawx,drawy;uint16_t scale;uint8_t handle,index;
} gfxbob_t;
#endif
''')
    (root / "main.c").write_text('''#include "gameplayer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static uint8_t ppb[1040+64*32];static uint32_t offset;
static int open_flag,close_count;
int sfopen(int f,const char *path,int mode){assert(f==0 && mode==1 && !strcmp(path,"players/hero.ppb"));open_flag=1;offset=0;return 0;}
int sfclose(int f){assert(f==0 && open_flag);open_flag=0;++close_count;return 0;}
int sfread(int f,void*out,uint32_t len,uint32_t*got){assert(f==0 && open_flag);if(offset+len>sizeof(ppb))return 1;memcpy(out,ppb+offset,len);offset+=len;*got=len;return 0;}
int sflseek(int f,uint32_t pos){assert(f==0 && open_flag);offset=pos;return 0;}
int main(void){
 ppb[1]=0;ppb[2]=64;ppb[3]=0;ppb[4]=32;ppb[5]=0;ppb[6]=0;ppb[7]=8;ppb[8]=0;
 for(int i=0;i<64*32;i++)ppb[1040+i]=(uint8_t)(i&255);
 assert(gameplayer_defaults.health==100 && gameplayer_defaults.lives==3 && gameplayer_defaults.score==250);
 uint16_t n=0;const gameplayer_inventory_entry_t* inv=gameplayer_initial_inventory(&n);
 assert(n==2 && !strcmp(inv[0].name,"key") && inv[1].initial==7);
 assert(!gameplayer_inventory_visible("key") && gameplayer_inventory_visible("gold") && gameplayer_inventory_visible("not-listed"));
 assert(gameplayer_defaults.custom_hitbox==1 && gameplayer_defaults.physics_preset==2);
 assert(gameplayer_defaults.hitbox_x==2 && gameplayer_defaults.hitbox_h==13);
 assert(gameplayer_init());assert(gameplayer_sprite.atlas_stride==64 && gameplayer_sprite.width==16);
 assert(gameplayer_sprite.imgdat[17]==17 && gameplayer_sprite.scale==100);
 assert(gameplayer_init()); assert(close_count==1);
 gameplayer_shutdown(); assert(gameplayer_sprite.imgdat==0 && close_count==1);
 puts("Stage 5.3 shared PPB + inventory: PASS");return 0;}
''')
    cmd = ['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(root),str(root/'gameplayer.c'),str(root/'main.c'),'-o',str(root/'run')]
    proc = subprocess.run(cmd,capture_output=True,text=True)
    assert proc.returncode==0, proc.stderr
    exe = subprocess.run([str(root/'run')],capture_output=True,text=True)
    assert exe.returncode==0,exe.stderr
    print(exe.stdout.strip())
