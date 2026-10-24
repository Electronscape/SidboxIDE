#ifndef TEST_APIS_H
#define TEST_APIS_H
#include <stdint.h>
/* In host tests there is no SIDBOX TFCard. Portable PPB reads must fail
   cleanly unless a test supplies a disk backend of its own. */
#define SD_READ 1
#define FR_OK 0
#ifdef TEST_PORTABLE_PPB
int sfopen(int slot,char *path,int mode);
int sfread(int slot,void *buf,uint32_t count,uint32_t *got);
int sflseek(int slot,uint32_t pos);
int sfclose(int slot);
#else
static inline int sfopen(int slot, char *path, int mode)
{(void)slot;(void)path;(void)mode;return 1;}
static inline int sfread(int slot, void *buf, uint32_t count, uint32_t *got)
{(void)slot;(void)buf;(void)count;if(got)*got=0;return 1;}
static inline int sflseek(int slot, uint32_t at)
{(void)slot;(void)at;return 1;}
static inline int sfclose(int slot) {(void)slot;return 0;}
#endif
#define BTN_FIRE2 0x01u
#define BTN_UP 0x02u
#define BTN_DOWN 0x04u
#define BLIT_FLAG_FLIP_X 0x0004u
#define BLIT_FLAG_FLIP_Y 0x0008u
typedef struct {const uint8_t *imgdat; uint16_t atlas_stride, atlas_height, width, height; int drawx,drawy; uint8_t index; uint16_t scale; uint8_t flags;} gfxbob_t;
void test_colour(uint8_t c);
void test_text(int x,int y,const char *text);
void test_rect(int x,int y,int w,int h);
void test_bob(gfxbob_t *s);
#define gfx_setcolour(c) test_colour(c)
#define gfx_drawtext(x,y,s) test_text(x,y,s)
/* Native 8x8 scaled glyph drawing, share the text spy in host tests. */
#define gfx_drawtextf(x,y,s,sx,sy) test_text(x,y,s)
#define gfx_rectf(x,y,w,h) test_rect(x,y,w,h)
#define gfx_drawbob(b) test_bob(b)
#endif
