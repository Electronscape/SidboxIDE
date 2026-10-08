#include <stdint.h>
#include "graphics.h"
#include "apis.h"

// a custom Pixel-Pixel-Buffer image. 
// sidbox's graphics system uses some of the header parts, but if you just want the raw pixel colour index, skip the first header and palette data

void LoadPPB(char *filename, uint8_t *img){
    // [0] configbits
    // [1..2] width  (big-endian)
    // [3..4] height (big-endian)
    // [5..8] payload length (big-endian)
    // [9..15] reserved = 0
    // colour palette info
    // [16 + 1024]  // 1024 bytes of palette info
    // [1040 ... n] // the 8bit pixel data
    ppb_t head;
    uint8_t res;
    uint32_t readi;
    sfopen(0, filename, SD_READ);
    if(res == F_OK){
        sfread(0, &head, sizeof(head), &readi);
        sfread(0, img, head.length_be, &readi);
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