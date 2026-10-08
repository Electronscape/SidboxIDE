#ifndef SIDBOX_API_CRT_H
#define SIDBOX_API_CRT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define API_CRT_OVERSCAN_WIDTH      448u
#define API_CRT_OVERSCAN_HEIGHT     312u
#define API_CRT_WIDTH        320u
#define API_CRT_HEIGHT       240u

#define API_CRT_COLOUR_BLACK    0x00u
#define API_CRT_COLOUR_BLUE     0x01u
#define API_CRT_COLOUR_RED      0x02u
#define API_CRT_COLOUR_GREEN    0x04u
#define API_CRT_COLOUR_BRIGHT   0x08u
#define API_CRT_COLOUR_MAGENTA  (API_CRT_COLOUR_RED | API_CRT_COLOUR_BLUE)
#define API_CRT_COLOUR_CYAN     (API_CRT_COLOUR_GREEN | API_CRT_COLOUR_BLUE)
#define API_CRT_COLOUR_YELLOW   (API_CRT_COLOUR_RED | API_CRT_COLOUR_GREEN)
#define API_CRT_COLOUR_WHITE    (API_CRT_COLOUR_RED | API_CRT_COLOUR_GREEN | API_CRT_COLOUR_BLUE)
#define API_CRT_COLOUR_BBLUE    (API_CRT_COLOUR_BLUE | API_CRT_COLOUR_BRIGHT)
#define API_CRT_COLOUR_BRED     (API_CRT_COLOUR_RED | API_CRT_COLOUR_BRIGHT)
#define API_CRT_COLOUR_BGREEN   (API_CRT_COLOUR_GREEN | API_CRT_COLOUR_BRIGHT)
#define API_CRT_COLOUR_BMAGENTA (API_CRT_COLOUR_MAGENTA | API_CRT_COLOUR_BRIGHT)
#define API_CRT_COLOUR_BCYAN    (API_CRT_COLOUR_CYAN | API_CRT_COLOUR_BRIGHT)
#define API_CRT_COLOUR_BYELLOW  (API_CRT_COLOUR_YELLOW | API_CRT_COLOUR_BRIGHT)
#define API_CRT_COLOUR_BWHITE   (API_CRT_COLOUR_WHITE | API_CRT_COLOUR_BRIGHT)

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t  (*enable)    (void);
    void     (*disable)   (void);
    uint8_t  (*enabled)   (void);
    void     (*setborder) (uint8_t colour);
    uint8_t  (*getborder) (void);
    void     (*waitframe) (void);
    void     (*render)    (const uint8_t *pixels, uint8_t border);
    void     (*clear)     (uint8_t colour);
    void     (*plot)      (uint16_t x, uint16_t y, uint8_t colour);
    void     (*rect)      (uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                           uint8_t colour);
    void     (*text)      (uint16_t x, uint16_t y, const char *text,
                           uint8_t colour);
    void     (*flush)     (void);
    void     (*testcard)  (void);
    void     (*zxsplash)  (void);
} API_CRT;

#define CRTBase       (API->crt)
#define crt_enable()  (CRTBase->enable())
#define crt_disable() (CRTBase->disable())
#define crt_enabled() (CRTBase->enabled())
#define crt_setborder(colour) (CRTBase->setborder(colour))
#define crt_getborder() (CRTBase->getborder())
#define crt_vsync()   (CRTBase->waitframe())
#define crt_waitframe() (CRTBase->waitframe())
#define crt_render(pixels, border) (CRTBase->render(pixels, border))
#define crt_clear(colour) (CRTBase->clear(colour))
#define crt_plot(x, y, colour) (CRTBase->plot(x, y, colour))
#define crt_rect(x, y, w, h, colour) (CRTBase->rect(x, y, w, h, colour))
#define crt_text(x, y, str, colour) (CRTBase->text(x, y, str, colour))
#define crt_flush() (CRTBase->flush())
#define crt_testcard() (CRTBase->testcard())
#define crt_zxsplash() (CRTBase->zxsplash())

// SDK functions 
void CRT_DrawImage(uint8_t *src, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t *crt_pixel_buffer);
void CRT_FrameImage(uint8_t *src, uint8_t *crt_pixel_buffer);

#ifdef __cplusplus
}
#endif

#endif
