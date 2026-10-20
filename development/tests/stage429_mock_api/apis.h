#ifndef TEST_APIS_H
#define TEST_APIS_H
#include <stdint.h>
#define BTN_FIRE2 0x01u
#define BTN_UP 0x02u
#define BTN_DOWN 0x04u
typedef struct {const uint8_t *imgdat; uint16_t atlas_stride, atlas_height, width, height; int drawx,drawy; uint8_t index; uint16_t scale;} gfxbob_t;
void test_colour(uint8_t c);
void test_text(int x,int y,const char *text);
void test_rect(int x,int y,int w,int h);
void test_bob(gfxbob_t *s);
#define gfx_setcolour(c) test_colour(c)
#define gfx_drawtext(x,y,s) test_text(x,y,s)
#define gfx_rectf(x,y,w,h) test_rect(x,y,w,h)
#define gfx_drawbob(b) test_bob(b)
#endif
