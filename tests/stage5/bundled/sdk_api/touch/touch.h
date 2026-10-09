#ifndef TOUCH_API_H
#define TOUCH_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct {
    void     (*init)        (void);
    uint8_t  (*ispressed)   (void);
    uint8_t  (*getxy)       (int16_t *x, int16_t *y);
    uint8_t  (*getrawxy)    (uint16_t *x, uint16_t *y);
    uint16_t (*getpressure) (void);
} API_TOUCH;



// touch screen interfacing
#define TOUCHBase           (API->touch)
#define apiTouchInit()      (TOUCHBase->init())
#define apiTouchDown()      (TOUCHBase->ispressed())
#define apiTouchGetXY(x, y) (TOUCHBase->getxy(x,y))
#define apiTouchGetRawXY(x,y) (TOUCHBase->getrawxy(x,y))
#define apiTouchPressure()  (TOUCHBase->getpressure())
#define touch_init()        (TOUCHBase->init())
#define touch_down()        (TOUCHBase->ispressed())
#define touch_getxy(x, y)   (TOUCHBase->getxy(x,y))
#define touch_getrawxy(x,y) (TOUCHBase->getrawxy(x,y))
#define touch_pressure()    (TOUCHBase->getpressure())


#ifdef __cplusplus
extern "C" }
#endif

#endif
