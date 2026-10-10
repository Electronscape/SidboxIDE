/* CGARM V2-only overlay: retain the real ARM/Newlib declarations. */
#ifndef CGARM_V2_STDLIB_OVERLAY_H
#define CGARM_V2_STDLIB_OVERLAY_H
#include_next <stdlib.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
void *reallocarray(void *ptr, size_t nmemb, size_t size);
#ifdef __cplusplus
}
#endif
#endif
