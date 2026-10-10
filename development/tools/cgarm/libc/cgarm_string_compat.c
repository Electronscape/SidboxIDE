/* CGARM Phase 5: extra string/memory functions, ASCII/C locale.
 * One applet owns all memory it passes to these functions.
 * No Newlib runtime, fixed addresses, static TLS, or firmware changes.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_string_compat.c requires SIDBOX_APPLET_V2"
#endif
#include <stddef.h>
#include <string.h>
#include <errno.h>

static unsigned char cg_ascii_lower(unsigned char c)
{
    return (c >= 'A' && c <= 'Z') ? (unsigned char)(c + ('a' - 'A')) : c;
}

int strcasecmp(const char *a, const char *b)
{
    for (;;) {
        unsigned char ac = cg_ascii_lower((unsigned char)*a++);
        unsigned char bc = cg_ascii_lower((unsigned char)*b++);
        if (ac != bc) return (int)ac - (int)bc;
        if (ac == 0) return 0;
    }
}

int strncasecmp(const char *a, const char *b, size_t n)
{
    while (n--) {
        unsigned char ac = cg_ascii_lower((unsigned char)*a++);
        unsigned char bc = cg_ascii_lower((unsigned char)*b++);
        if (ac != bc) return (int)ac - (int)bc;
        if (ac == 0) return 0;
    }
    return 0;
}

char *strcasestr(const char *haystack, const char *needle)
{
    if (!*needle) return (char *)haystack;
    for (; *haystack; ++haystack) {
        const char *h = haystack, *n = needle;
        while (*h && *n && cg_ascii_lower((unsigned char)*h) ==
                          cg_ascii_lower((unsigned char)*n)) { ++h; ++n; }
        if (!*n) return (char *)haystack;
    }
    return NULL;
}

char *strchrnul(const char *s, int c)
{
    unsigned char wanted = (unsigned char)c;
    while (*s && (unsigned char)*s != wanted) ++s;
    return (char *)s;
}

char *strsep(char **stringp, const char *delim)
{
    if (!*stringp) return NULL;
    char *start = *stringp;
    for (char *p = start;; ++p) {
        const char *q = delim;
        while (*q && *q != *p) ++q;
        if (*q) { *p = '\0'; *stringp = p + 1; return start; }
        if (!*p) { *stringp = NULL; return start; }
    }
}

size_t strlcpy(char *dst, const char *src, size_t dstsize)
{
    const size_t n = strlen(src);
    if (dstsize) {
        size_t count = n < dstsize - 1 ? n : dstsize - 1;
        for (size_t i = 0; i < count; ++i) dst[i] = src[i];
        dst[count] = '\0';
    }
    return n;
}

size_t strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t d = 0;
    while (d < dstsize && dst[d]) ++d;
    size_t s = strlen(src);
    if (d == dstsize) return dstsize + s;
    size_t available = dstsize - d - 1;
    size_t copy = s < available ? s : available;
    for (size_t i = 0; i < copy; ++i) dst[d+i] = src[i];
    dst[d+copy] = '\0';
    return d + s;
}

void *memccpy(void *dst, const void *src, int c, size_t n)
{
    unsigned char *d = dst;
    const unsigned char *s = src;
    unsigned char stop = (unsigned char)c;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
        if (s[i] == stop) return d + i + 1;
    }
    return NULL;
}

void *memmem(const void *haystack, size_t haylen, const void *needle, size_t neelen)
{
    const unsigned char *h = haystack;
    const unsigned char *n = needle;
    if (neelen == 0) return (void *)haystack;
    if (haylen < neelen) return NULL;
    for (size_t i = 0; i <= haylen - neelen; ++i) {
        size_t j = 0;
        while (j < neelen && h[i+j] == n[j]) ++j;
        if (j == neelen) return (void *)(h+i);
    }
    return NULL;
}

/* In the absence of a locale engine, C-locale collation is bytewise. */
int strcoll(const char *a, const char *b) { return strcmp(a,b); }
size_t strxfrm(char *dst, const char *src, size_t n)
{
    size_t length = strlen(src);
    if (n) {
        size_t count = length < n - 1 ? length : n - 1;
        for (size_t i = 0; i < count; ++i) dst[i] = src[i];
        dst[count] = '\0';
    }
    return length;
}

char *strerror(int error)
{
    switch (error) {
    case 0: return "No error";
    case EDOM: return "Numerical argument out of domain";
    case ERANGE: return "Numerical result out of range";
    case ENOMEM: return "Out of memory";
    case EINVAL: return "Invalid argument";
#ifdef ENOENT
    case ENOENT: return "No such file or directory";
#endif
#ifdef EIO
    case EIO: return "Input/output error";
#endif
#ifdef ENOSPC
    case ENOSPC: return "No space left on device";
#endif
#ifdef EACCES
    case EACCES: return "Permission denied";
#endif
#ifdef EBADF
    case EBADF: return "Bad file descriptor";
#endif
    default: return "Unknown error";
    }
}
