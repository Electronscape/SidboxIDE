/* CGARM Phase 8: unbuffered C file streams using OS-managed SBFS handles.
 * Never touches the four legacy numbered SBOS file slots.
 * Requires the Phase 7 SBOS_FILEIO ABI extension in the firmware.
 * FILE is opaque: this implementation does not access Newlib's FILE layout.
 */
#ifndef SIDBOX_APPLET_V2
#error "CGARM file streams are only for CGARM V2 applets"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include "apis.h"

#define CGARM_FILE_MAGIC 0x43474637u
#define CGARM_F_READ  1u
#define CGARM_F_WRITE 2u
#define CGARM_F_APPEND 4u

typedef struct CGARM_File {
    uint32_t magic;
    void *handle;
    unsigned flags;
    unsigned eof;
    unsigned error;
    unsigned pushed;
    unsigned char pushed_char;
    struct CGARM_File *next;
} CGARM_File;

/* Registry is inside each loaded applet image, never shared with another applet. */
static CGARM_File *cgarm_open_files = NULL;

static void cgarm_unlink_file(CGARM_File *f)
{
    CGARM_File **link = &cgarm_open_files;
    while (*link) {
        if (*link == f) { *link = f->next; return; }
        link = &(*link)->next;
    }
}

static CGARM_File *cgf(FILE *stream)
{
    CGARM_File *f = (CGARM_File *)(void *)stream;
    if (!f || f->magic != CGARM_FILE_MAGIC || !f->handle) {
        errno = EBADF;
        return NULL;
    }
    return f;
}

static int cgerr(FRESULT result)
{
    switch (result) {
    case FR_OK: return 0;
    case FR_NO_FILE: case FR_NO_PATH: return ENOENT;
    case FR_DENIED: case FR_WRITE_PROTECTED: return EACCES;
    case FR_EXIST: return EEXIST;
    case FR_TOO_MANY_OPEN_FILES: return EMFILE;
    case FR_NOT_READY: case FR_INVALID_DRIVE: return ENODEV;
    case FR_INVALID_NAME: case FR_INVALID_PARAMETER: return EINVAL;
    case FR_TIMEOUT: case FR_LOCKED: return EBUSY;
    default: return EIO;
    }
}

static void cgseterr(CGARM_File *f, FRESULT code)
{
    errno = cgerr(code);
    if (f) f->error = 1u;
}

FILE *fopen(const char *path, const char *mode)
{
    uint8_t smode;
    unsigned flags;
    void *handle = NULL;
    if (!path || !mode || !mode[0]) { errno = EINVAL; return NULL; }
    switch (mode[0]) {
    case 'r': smode = SD_READ | SD_OPEN_EXISTING; flags = CGARM_F_READ; break;
    case 'w': smode = SD_WRITE | SD_CREATE_ALWAYS; flags = CGARM_F_WRITE; break;
    case 'a': smode = SD_WRITE | SD_OPEN_APPEND; flags = CGARM_F_WRITE | CGARM_F_APPEND; break;
    default: errno = EINVAL; return NULL;
    }
    unsigned plus = 0;
    for (const char *p = mode + 1; *p; ++p) {
        if (*p == '+') { if (plus++) { errno = EINVAL; return NULL; } }
        else if (*p != 'b' && *p != 't') { errno = EINVAL; return NULL; }
    }
    if (plus) { smode |= SD_READ | SD_WRITE; flags |= CGARM_F_READ | CGARM_F_WRITE; }
    CGARM_File *f = (CGARM_File *)malloc(sizeof(*f));
    if (!f) { errno = ENOMEM; return NULL; }
    FRESULT res = API->system->sys_fileio->sbstream_open(path, smode, &handle);
    if (res != FR_OK || !handle) {
        cgseterr(NULL, res != FR_OK ? res : FR_INT_ERR);
        free(f);
        return NULL;
    }
    f->magic = CGARM_FILE_MAGIC;
    f->handle = handle;
    f->flags = flags;
    f->eof = 0;
    f->error = 0;
    f->pushed = 0;
    f->pushed_char = 0;
    f->next = cgarm_open_files;
    cgarm_open_files = f;
    return (FILE *)(void *)f;
}

int fclose(FILE *stream)
{
    CGARM_File *f = cgf(stream);
    if (!f) return EOF;
    FRESULT result = API->system->sys_fileio->sbstream_close(f->handle);
    cgarm_unlink_file(f);
    f->magic = 0;
    f->handle = NULL;
    free(f);
    if (result != FR_OK) { cgseterr(NULL, result); return EOF; }
    return 0;
}

size_t fread(void *buffer, size_t size, size_t count, FILE *stream)
{
    CGARM_File *f = cgf(stream);
    if (!f) return 0;
    if (size == 0 || count == 0) return 0;
    if (!(f->flags & CGARM_F_READ) || !buffer) { errno = EINVAL; f->error = 1; return 0; }
    if (size > UINT32_MAX || count > UINT32_MAX / size) {
        errno = EOVERFLOW; f->error = 1; return 0;
    }
    uint32_t request = (uint32_t)(size * count);
    uint32_t consumed = 0;
    uint8_t *out = (uint8_t *)buffer;
    if (f->pushed) {
        out[0] = f->pushed_char;
        f->pushed = 0;
        consumed = 1;
    }
    if (consumed < request) {
        uint32_t received = 0;
        FRESULT result = API->system->sys_fileio->sbstream_read(
            f->handle, out + consumed, request - consumed, &received);
        if (received > request - consumed) {
            errno = EIO; f->error = 1;
            return consumed / size;
        }
        consumed += received;
        if (result != FR_OK) cgseterr(f, result);
        else if (consumed < request) f->eof = 1;
    }
    return consumed / size;
}

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream)
{
    CGARM_File *f = cgf(stream);
    if (!f) return 0;
    if (size == 0 || count == 0) return 0;
    if (!(f->flags & CGARM_F_WRITE) || !buffer) { errno = EINVAL; f->error = 1; return 0; }
    if (size > UINT32_MAX || count > UINT32_MAX / size) { errno = EOVERFLOW; f->error = 1; return 0; }
    if (f->pushed) {
        /* A write following pushback targets the logical read position. */
        uint32_t pos = 0;
        FRESULT step = API->system->sys_fileio->sbstream_tell(f->handle, &pos);
        if (step != FR_OK) { cgseterr(f, step); return 0; }
        if (pos > 0) --pos;
        step = API->system->sys_fileio->sbstream_seek(f->handle, pos);
        if (step != FR_OK) { cgseterr(f, step); return 0; }
        f->pushed = 0;
    }
    uint32_t bytes = 0, request = (uint32_t)(size * count);
    FRESULT result = API->system->sys_fileio->sbstream_write(f->handle, buffer, request, &bytes);
    if (result != FR_OK) cgseterr(f, result);
    else if (bytes < request) { errno = ENOSPC; f->error = 1; }
    return bytes / size;
}

int fseek(FILE *stream, long offset, int whence)
{
    CGARM_File *f = cgf(stream);
    if (!f) return -1;
    uint32_t base = 0;
    FRESULT result = FR_OK;
    if (whence == SEEK_CUR) {
        result = API->system->sys_fileio->sbstream_tell(f->handle, &base);
        if (result == FR_OK && f->pushed && base > 0) --base;
    }
    else if (whence == SEEK_END) result = API->system->sys_fileio->sbstream_size(f->handle, &base);
    else if (whence != SEEK_SET) { errno = EINVAL; f->error = 1; return -1; }
    if (result != FR_OK) { cgseterr(f, result); return -1; }
    int64_t target = (int64_t)base + (int64_t)offset;
    if (target < 0 || target > UINT32_MAX) { errno = EINVAL; f->error = 1; return -1; }
    result = API->system->sys_fileio->sbstream_seek(f->handle, (uint32_t)target);
    if (result != FR_OK) { cgseterr(f, result); return -1; }
    f->eof = 0;
    f->pushed = 0;
    return 0;
}

long ftell(FILE *stream)
{
    CGARM_File *f = cgf(stream);
    if (!f) return -1L;
    uint32_t pos = 0;
    FRESULT result = API->system->sys_fileio->sbstream_tell(f->handle, &pos);
    if (result != FR_OK) { cgseterr(f, result); return -1L; }
    if (f->pushed && pos > 0) --pos;
    if (sizeof(long) == 4u && pos > (uint32_t)LONG_MAX) { errno = EOVERFLOW; f->error = 1; return -1L; }
    return (long)pos;
}

int fflush(FILE *stream)
{
    if (!stream) {
        int bad = 0;
        for (CGARM_File *item = cgarm_open_files; item; item = item->next) {
            if (!(item->flags & CGARM_F_WRITE)) continue;
            FRESULT step = API->system->sys_fileio->sbstream_flush(item->handle);
            if (step != FR_OK) { cgseterr(item, step); bad = 1; }
        }
        return bad ? EOF : 0;
    }
    CGARM_File *f = cgf(stream);
    if (!f) return EOF;
    if (!(f->flags & CGARM_F_WRITE)) return 0;
    FRESULT result = API->system->sys_fileio->sbstream_flush(f->handle);
    if (result != FR_OK) { cgseterr(f, result); return EOF; }
    return 0;
}

int feof(FILE *stream) { CGARM_File *f=cgf(stream); return f ? (int)f->eof : 0; }
int ferror(FILE *stream) { CGARM_File *f=cgf(stream); return f ? (int)f->error : 1; }
void clearerr(FILE *stream) { CGARM_File *f=cgf(stream); if (f) { f->eof=0; f->error=0; } }
void rewind(FILE *stream) { if (fseek(stream, 0L, SEEK_SET) == 0) clearerr(stream); }

/* One-byte pushback is guaranteed by ISO C. Works without OS seeking. */
int ungetc(int ch, FILE *stream)
{
    CGARM_File *f = cgf(stream);
    if (!f) return EOF;
    if (ch == EOF || !(f->flags & CGARM_F_READ) || f->pushed) {
        errno = EINVAL;
        return EOF;
    }
    f->pushed_char = (unsigned char)ch;
    f->pushed = 1;
    f->eof = 0;
    return (int)f->pushed_char;
}

/* fpos_t is opaque in Newlib. Store the 32-bit seek position in its bytes. */
int fgetpos(FILE *stream, fpos_t *position)
{
    if (!position) { errno = EINVAL; return -1; }
    long where = ftell(stream);
    if (where < 0) return -1;
    if (sizeof(*position) < sizeof(where)) { errno = EOVERFLOW; return -1; }
    unsigned char *dst = (unsigned char *)(void *)position;
    for (size_t i = 0; i < sizeof(*position); ++i) dst[i] = 0;
    const unsigned char *src = (const unsigned char *)(const void *)&where;
    for (size_t i = 0; i < sizeof(where); ++i) dst[i] = src[i];
    return 0;
}

int fsetpos(FILE *stream, const fpos_t *position)
{
    if (!position) { errno = EINVAL; return -1; }
    if (sizeof(*position) < sizeof(long)) { errno = EOVERFLOW; return -1; }
    long where = 0;
    unsigned char *dst = (unsigned char *)(void *)&where;
    const unsigned char *src = (const unsigned char *)(const void *)position;
    for (size_t i = 0; i < sizeof(where); ++i) dst[i] = src[i];
    return fseek(stream, where, SEEK_SET);
}

/* Streams remain unbuffered; do not falsely accept buffered modes. */
int setvbuf(FILE *stream, char *buffer, int mode, size_t size)
{
    (void)buffer;
    (void)size;
    if (!cgf(stream)) return -1;
    if (mode == _IONBF) return 0;
    errno = ENOSYS;
    return -1;
}

void setbuf(FILE *stream, char *buffer)
{
    (void)setvbuf(stream, buffer, buffer ? _IOFBF : _IONBF, BUFSIZ);
}

int fgetc(FILE *stream)
{
    unsigned char c;
    if (fread(&c, 1, 1, stream) != 1) return EOF;
    return (int)c;
}
int fputc(int c, FILE *stream)
{
    unsigned char ch = (unsigned char)c;
    return fwrite(&ch, 1, 1, stream) == 1 ? (int)ch : EOF;
}
char *fgets(char *out, int capacity, FILE *stream)
{
    if (!out || capacity <= 0) { errno=EINVAL; return NULL; }
    int i=0;
    while (i < capacity-1) {
        int c=fgetc(stream);
        if (c==EOF) break;
        out[i++]=(char)c;
        if (c=='\n') break;
    }
    if (!i) return NULL;
    out[i]=0;
    return out;
}
int fputs(const char *str, FILE *stream)
{
    if (!str) { errno=EINVAL; return EOF; }
    size_t len=0;
    while (str[len]) ++len;
    return fwrite(str, 1, len, stream) == len ? 0 : EOF;
}
int vfprintf(FILE *stream, const char *fmt, va_list args)
{
    if (!cgf(stream)) return -1;
    if (!fmt) { errno = EINVAL; return -1; }
    va_list copy;
    va_copy(copy,args);
    int needed=vsnprintf(NULL, 0, fmt, copy);
    va_end(copy);
    if (needed < 0) return -1;
    if (needed == 0) return 0;
    char *buffer = (char *)malloc((size_t)needed + 1u);
    if (!buffer) { errno=ENOMEM; return -1; }
    va_copy(copy,args);
    int formatted=vsnprintf(buffer, (size_t)needed+1u, fmt, copy);
    va_end(copy);
    int result=-1;
    if (formatted == needed && fwrite(buffer, 1, (size_t)needed, stream) == (size_t)needed)
        result=needed;
    free(buffer);
    return result;
}
int fprintf(FILE *stream, const char *fmt, ...)
{
    va_list args;
    va_start(args,fmt);
    int r=vfprintf(stream,fmt,args);
    va_end(args);
    return r;
}
