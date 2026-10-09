#ifndef SBAPI_CONSOLE_H
#define SBAPI_CONSOLE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t CGWindow;


typedef struct  {
    void (*printf)(CGWindow ownerWin, const char *fmt, ...);
    void (*writec)(CGWindow ownerWin, const char *buf, uint32_t len);
} API_GUI_Console;





#ifdef __cplusplus
}
#endif
#endif