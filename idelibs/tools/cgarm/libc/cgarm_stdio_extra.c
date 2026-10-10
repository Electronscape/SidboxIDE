/* CGARM Phase 5: GNU/BSD asprintf and vasprintf convenience functions.
 * Allocation is applet-local; caller must release *result with free().
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_stdio_extra.c requires SIDBOX_APPLET_V2"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

int vasprintf(char **result, const char *format, va_list ap)
{
    if (!result || !format) { errno = EINVAL; return -1; }
    *result = NULL;
    va_list copy;
    va_copy(copy, ap);
    int length = vsnprintf(NULL, 0, format, copy);
    va_end(copy);
    if (length < 0) return -1;
    char *memory = malloc((size_t)length + 1u);
    if (!memory) { errno = ENOMEM; return -1; }
    va_copy(copy, ap);
    int written = vsnprintf(memory, (size_t)length + 1u, format, copy);
    va_end(copy);
    if (written < 0 || written != length) {
        free(memory);
        return -1;
    }
    *result = memory;
    return written;
}

int asprintf(char **result, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int written = vasprintf(result, format, ap);
    va_end(ap);
    return written;
}
