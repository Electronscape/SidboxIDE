#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "apis.h"
/*
 * SIDBOX IDE - V1 Gaming starter
 *
 * For a beginner-friendly platformer, open Game Designer, add a tilemap,
 * a PPB sprite named "player" and optional backgrounds or game objects.
 * Save the design, then choose Update Game Project.
 *
 * GamerGirl generates maingame.c.txt containing a COMPLETE main.c example
 * specifically for your current design. While main.c is IDE-owned and
 * unchanged, GamerGirl can regenerate it. Saving your own edits transfers
 * ownership to you; the IDE then updates only maingame.c.txt.
 *
 * The default loop below is intentionally a blank graphics-only starting
 * point for games not using the Platformer helpers.
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
