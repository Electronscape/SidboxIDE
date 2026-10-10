/* CGARM Phase 11: dynamic line input and large-offset checked wrappers.
 * New symbols, no changes to SBOS file handle ownership or the Phase 10 ABI.
 * getdelim/getline allocate with the applet-local CGARM allocator.
 */
#ifndef SIDBOX_APPLET_V2
#error "Phase 11 stream code requires SIDBOX_APPLET_V2"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>

ssize_t getdelim(char **lineptr, size_t *n, int delimiter, FILE *stream)
{
    if (!lineptr || !n || !stream) { errno = EINVAL; return -1; }
    if (*lineptr == NULL || *n == 0) {
        char *initial = (char *)realloc(*lineptr, 64u);
        if (!initial) { errno = ENOMEM; return -1; }
        *lineptr = initial;
        *n = 64u;
    }
    size_t used = 0;
    for (;;) {
        int ch = fgetc(stream);
        if (ch == EOF) {
            if (ferror(stream)) return -1;
            break;
        }
        if (used >= (((size_t)-1) >> 1)) { errno = EOVERFLOW; return -1; }
        if (used + 1u >= *n) {
            size_t limit = (((size_t)-1) >> 1) + 1u;
            size_t grown = *n <= limit / 2u ? *n * 2u : limit;
            if (grown < used + 2u) { errno = EOVERFLOW; return -1; }
            char *expanded = (char *)realloc(*lineptr, grown);
            if (!expanded) { errno = ENOMEM; return -1; }
            *lineptr = expanded;
            *n = grown;
        }
        (*lineptr)[used++] = (char)ch;
        if ((unsigned char)ch == (unsigned char)delimiter) break;
    }
    if (!used) return -1;
    (*lineptr)[used] = '\0';
    return (ssize_t)used;
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
    return getdelim(lineptr, n, '\n', stream);
}

/* SBOS stream positions are currently 32-bit, like long on Cortex-M7.
 * Reject any wider host/off_t value rather than silently truncating it. */
int fseeko(FILE *stream, off_t offset, int whence)
{
    if (offset > (off_t)LONG_MAX || offset < (off_t)LONG_MIN) {
        errno = EOVERFLOW;
        return -1;
    }
    return fseek(stream, (long)offset, whence);
}

off_t ftello(FILE *stream)
{
    return (off_t)ftell(stream);
}
