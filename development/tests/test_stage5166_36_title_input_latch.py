#!/usr/bin/env python3
"""Stage 5.166.36: a death-confirm FIRE1 must not auto-start the title menu."""
from pathlib import Path
import subprocess, tempfile
root=Path(__file__).resolve().parents[2]
runtime=(root/'idelibs/codehelpers/game/gametitle-runtime.rulec').read_text()
start=runtime.index('uint8_t gametitle_run(const char **world, const char **start)')
fn=runtime[start:]
assert '@' not in fn
assert 'title_input_armed' in fn
assert 'if(!title_input_armed && !(buttons & (BTN_FIRE|BTN_FIRE2)))' in fn

stub=r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define BTN_FIRE  0x01u
#define BTN_FIRE2 0x02u
#define BTN_UP    0x04u
#define BTN_DOWN  0x08u
#define BTN_LEFT  0x10u
#define BTN_RIGHT 0x20u
#define TITLE_MENU_COUNT 2
#define TITLE_IMAGE_COUNT 1
typedef struct {uint8_t *bitmap;} gfx_bitmap_t;
typedef struct {uint8_t action; const char *world,*start;} title_item_t;
static uint8_t fb_bytes[2][480*320];
static gfx_bitmap_t fb[2]={{fb_bytes[0]},{fb_bytes[1]}};
static int frames, draw_calls;
static uint8_t keys[40];
static uint32_t title_clut[256];
static char title_load_marker[16];
static int8_t title_loaded_slot=-1;
static uint8_t title_slot_exists[10];
static const char *title_default_world="world1";
static const char *title_music_file="";
static uint8_t opt_music=1;
static const uint8_t title_options_visible[8]={1,1,1,1,1,1,1,1};
static const title_item_t title_menu[2]={ {1,"forest","forestgate"}, {3,0,0} };
static const int title_menu_length=2;
static uint8_t title_first_option(void){return 0;}
static uint8_t title_visible_option(uint8_t opt,int delta){return (uint8_t)((opt+delta+8)%8);}
static void title_adjust_option(uint8_t which,int direction){(void)which;(void)direction;}
static void title_set_background(gfx_bitmap_t *b,int style){(void)b;(void)style;}
static void title_load_frame(gfx_bitmap_t *b,int selected,int dual){(void)b;(void)selected;(void)dual;++draw_calls;}
static void title_options_frame(gfx_bitmap_t *b,int selected,int dual){(void)b;(void)selected;(void)dual;++draw_calls;}
static void title_frame(gfx_bitmap_t *b,int selected,int dual){(void)b;(void)selected;(void)dual;++draw_calls;}
static int title_load_images(void){return 1;}
static void title_release_images(void){}
static int gameworlds_slot_exists(uint8_t slot){(void)slot;return 0;}
static int gameworlds_request_at(const char *world,const char *start){(void)world;(void)start;return 1;}
static void gfx_lcdwait(void){++frames;assert(frames<40);}
static uint8_t getjoyport(void){return keys[frames-1];}
static gfx_bitmap_t *gfx_getfbuffer1(void){return &fb[0];}
static gfx_bitmap_t *gfx_getfbuffer2(void){return &fb[1];}
static gfx_bitmap_t *gfx_getbbuffer1(void){return 0;}
static void gfx_usefpalette(uint32_t *p){(void)p;}
static void gfx_scrollb(int x,int y){(void)x;(void)y;}
static void gfx_scrollf(int x,int y){(void)x;(void)y;}
static void gfx_usebuffer(gfx_bitmap_t *b){(void)b;}
static void gfx_cls(void){}
static void gfx_dispfbuffer(gfx_bitmap_t *a,gfx_bitmap_t *b){(void)a;(void)b;}
static void gfx_displaynow(void){}
static void set_audio_dma(int x){(void)x;}
static int set_music_dma;
static void music_play(char *p,int x){(void)p;(void)x;}
static void music_stop(void){}
static void music_update(void){}
'''
footer=r'''
static void clear_test(void){frames=0;draw_calls=0;memset(keys,0,sizeof(keys));}
int main(void){
  const char *world=0,*start=0;
  /* Returning from no-save defeat while FIRE1 is physically HELD.
     The first menu item is Forest, so leaked FIRE1 would auto-enter Forest. */
  clear_test();
  keys[0]=BTN_FIRE;keys[1]=BTN_FIRE;keys[2]=BTN_FIRE;
  keys[3]=0u;keys[4]=0u;
  keys[5]=BTN_FIRE;
  assert(gametitle_run(&world,&start)==1u);
  assert(frames==6); /* NEVER exits during the held FIRE1 at frames 1..3. */
  assert(draw_calls==5);
  assert(strcmp(world,"forest")==0 && strcmp(start,"forestgate")==0);

  /* Initially released input: first full FIRE1 press on next VBlank works. */
  clear_test();
  keys[0]=0u;keys[1]=BTN_FIRE;
  assert(gametitle_run(&world,&start)==1u);
  assert(frames==2);

  /* Holding FIRE2 when returning to title must not influence its menu. */
  clear_test();
  keys[0]=BTN_FIRE2;keys[1]=BTN_FIRE2;keys[2]=0u;
  keys[3]=BTN_FIRE;
  assert(gametitle_run(&world,&start)==1u);
  assert(frames==4);
  puts("PASS Stage 5.166.36 title key release gate (real title function)");
  return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage16636_title_') as tmp:
    tmp=Path(tmp)
    (tmp/'test.c').write_text(stub+'\n'+fn+'\n'+footer)
    subprocess.run(['gcc','-std=c11','-Werror','-Wall','-Wextra',str(tmp/'test.c'),'-o',str(tmp/'title')],check=True)
    subprocess.run([str(tmp/'title')],check=True)
print('PASS real title-runtime input source compiled and executed')
