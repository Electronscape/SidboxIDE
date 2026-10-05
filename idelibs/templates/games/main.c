#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "apis.h"
/*

    This is a shell starter for programs that dont use the GUI

*/

#define SCREEN_W 480
#define SCREEN_H 320

MEMALIGN32 static uint32_t app_palette[256];
MEMALIGN32 static volatile gfx_bitmap_t *front_a;
MEMALIGN32 static volatile gfx_bitmap_t *front_b;
MEMALIGN32 static volatile gfx_bitmap_t backbitmap;


#define TXTAPP_TITLE    "BLANK PROGRAM - Gaming"

static uint8_t db = 0;  // double buffering the front graphics array
static void flip_front_buffer(void)
{
    db = (uint8_t)(1u - db);
    if (db) { gfx_dispfbuffer((gfx_bitmap_t *)front_a, (gfx_bitmap_t *)front_b);
    } else {  gfx_dispfbuffer((gfx_bitmap_t *)front_b, (gfx_bitmap_t *)front_a);
    }
}


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;


    configure_runmode(GAMEMODE_PROFILE_0);
    suspend_desktop();
    initMalloc();
    // sound options if we're using sound
    set_audio_dma(512);
    set_music_dma = 1;
    //enable_audio_dma(); // use this if you want music to be playing without having to watch dog the music routing
    //////////////////////////////////////

    // display set up
    gfx_setlcd(DEFAULT_RENDER_ORDER, FPS_50);
    gfx_mode(SCREEN_W, SCREEN_H, SCREEN_W, SCREEN_H, DISPFLAG_DUALLAYER | DISPFLAG_SCROLLABLE);

    front_a = gfx_getdrawbuffer(); 
    front_b = gfx_getshowbuffer();

    
    while (1) {
        gfx_lcdwait();
        gfx_cls();

        {
            // your graphics and content on screen
        }

        flip_front_buffer();
        gfx_displaynow();
        music_update(); // dma watch dog not switched on so will need this

    }


    return 0x00;
}
