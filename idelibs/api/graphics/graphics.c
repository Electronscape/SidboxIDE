#include <stdint.h>
#include <stdlib.h>
#include "graphics.h"
#include "apis.h"

// a custom Pixel-Pixel-Buffer image. 
// sidbox's graphics system uses some of the header parts, but if you just want the raw pixel colour index, skip the first header and palette data

void LoadPPB(char *filename, uint8_t *img){
    /* PPB: 16-byte header (BE dimensions/length), 1024-byte palette,
       then indexed pixel bytes. Keep temporary buffers off the small stack. */
    uint8_t hdr[16];
    uint32_t got = 0;
    if (!filename || !img) return;
    if (sfopen(0, filename, SD_READ) != F_OK) return;

    if (sfread(0, hdr, sizeof(hdr), &got) == F_OK && got == sizeof(hdr)) {
        const uint32_t width = ((uint32_t)hdr[1] << 8) | hdr[2];
        const uint32_t height = ((uint32_t)hdr[3] << 8) | hdr[4];
        const uint32_t length = ((uint32_t)hdr[5] << 24) | ((uint32_t)hdr[6] << 16)
                              | ((uint32_t)hdr[7] << 8) | hdr[8];
        /* Caller must allocate width * height bytes BEFORE this call.
           This legacy void API cannot know the caller's buffer capacity. */
        if (width && height && length == width * height &&
            sflseek(0, 1040u) == F_OK) {
            got = 0;
            (void)sfread(0, img, length, &got);
        }
    }
    sfclose(0);
}

// initMalloc(); MUST be used before calling this
void gfx_createBitmap(gfx_bitmap_t *bitmap, int16_t w, int16_t h){

    bitmap->memspacelen = (w * h);
    bitmap->width = w;
    bitmap->height = h;
    bitmap->stride = h;   // should be the height of the bitmap
    bitmap->bitmap = malloc(w * h);//bitground;

}



const unsigned char bitMask[8] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

#define BB_INDEX(x, y) (((x) * 320) + (y))

void gfx_draw1bit(signed short lx, signed short ly, unsigned short w, unsigned short h, unsigned char *image, unsigned char colour, uint8_t *destbitmap) {
    signed short fx, fy;
    signed short dx, dy;
    unsigned short step, depth;

    dx = w;
    dy = h;
    fx = 0;

    for (fy = 0; fy != dy; fy++) {
        do {
            step = *image++;

            for (depth = 0; depth < 8; depth++) {
                if (fx >= dx) break;

                if (bitMask[depth] & step) {
                    signed short px = lx + fx;
                    signed short py = ly + fy;

                    // this was added: Strictly restrict Y to 0..319 so Y never leaks into adjacent X columns
                    if (py >= 0 && py < 320 && px >= 0) {
                        destbitmap[BB_INDEX(px, py)] = colour;
                    }
                }
                fx++;
            }

        } while (fx < dx);
        fx = 0;
    }
}