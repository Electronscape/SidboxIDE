/* CGARM V2-only overlay: keep the real ARM/Newlib type definitions. */
#ifndef CGARM_V2_STDIO_OVERLAY_H
#define CGARM_V2_STDIO_OVERLAY_H
#include_next <stdio.h>
#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif
ssize_t getdelim(char **lineptr, size_t *n, int delimiter, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);
#ifdef __cplusplus
}
#endif
#endif
