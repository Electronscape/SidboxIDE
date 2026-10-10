/* CGARM standard-I/O overlay: preserve ARM toolchain types and declarations,
 * but never allow Newlib FILE-layout macros to inspect opaque SBOS streams.
 * Included ONLY in the CGARM (SIDBOX_APPLET_V2) compiler path.
 */
#ifndef CGARM_V2_STDIO_OVERLAY_H
#define CGARM_V2_STDIO_OVERLAY_H
#include_next <stdio.h>
#include <sys/types.h>
/* The bundled Newlib headers may implement these with private FILE fields. */
#ifdef getc
#undef getc
#endif
#ifdef putc
#undef putc
#endif
#ifdef feof
#undef feof
#endif
#ifdef ferror
#undef ferror
#endif
#ifdef clearerr
#undef clearerr
#endif
#ifdef getc_unlocked
#undef getc_unlocked
#endif
#ifdef putc_unlocked
#undef putc_unlocked
#endif
#ifdef __cplusplus
extern "C" {
#endif
ssize_t getdelim(char **lineptr, size_t *n, int delimiter, FILE *stream);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);
int getc(FILE *stream);
int putc(int c, FILE *stream);
int vfscanf(FILE *stream, const char *format, va_list args);
int fscanf(FILE *stream, const char *format, ...);
void perror(const char *prefix);
#ifdef __cplusplus
}
#endif
#endif
