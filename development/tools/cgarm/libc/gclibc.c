/* CGARM standard C string/character support - first version.
 * Freestanding and applet-local. Avoid Newlib binary dependencies.
 * Formatting, allocation and memory primitives are in separate files.
 * Only enabled by the IDE's V2/CGARM build path.
 */
#include "gclibc.h"
#include <stddef.h>

size_t strlen(const char *s)
{
    const char *p = s;
    while (*p) ++p;
    return (size_t)(p - s);
}

size_t strnlen(const char *s, size_t maxlen)
{
    size_t i = 0;
    while (i < maxlen && s[i]) ++i;
    return i;
}

int strcmp(const char *a, const char *b)
{
    while (*a && *a == *b) { ++a; ++b; }
    return (int)(unsigned char)*a - (int)(unsigned char)*b;
}

int strncmp(const char *a, const char *b, size_t n)
{
    while (n) {
        unsigned char ca = (unsigned char)*a++;
        unsigned char cb = (unsigned char)*b++;
        if (ca != cb) return (int)ca - (int)cb;
        if (!ca) return 0;
        --n;
    }
    return 0;
}

char *strcpy(char *dst, const char *src)
{
    char *result = dst;
    while ((*dst++ = *src++) != '\0') {}
    return result;
}

char *strncpy(char *dst, const char *src, size_t n)
{
    char *result = dst;
    while (n && *src) { *dst++ = *src++; --n; }
    while (n) { *dst++ = '\0'; --n; }
    return result;
}

char *strcat(char *dst, const char *src)
{
    char *result = dst;
    while (*dst) ++dst;
    while ((*dst++ = *src++) != '\0') {}
    return result;
}

char *strncat(char *dst, const char *src, size_t n)
{
    char *result = dst;
    while (*dst) ++dst;
    while (n && *src) { *dst++ = *src++; --n; }
    *dst = '\0';
    return result;
}

char *strchr(const char *s, int ch)
{
    unsigned char c = (unsigned char)ch;
    for (;;) {
        if ((unsigned char)*s == c) return (char *)s;
        if (!*s) return NULL;
        ++s;
    }
}

char *strrchr(const char *s, int ch)
{
    const char *last = NULL;
    unsigned char c = (unsigned char)ch;
    for (;;) {
        if ((unsigned char)*s == c) last = s;
        if (!*s) return (char *)last;
        ++s;
    }
}

char *strstr(const char *haystack, const char *needle)
{
    if (!*needle) return (char *)haystack;
    for (const char *h = haystack; *h; ++h) {
        const char *a = h, *b = needle;
        while (*a && *b && *a == *b) { ++a; ++b; }
        if (!*b) return (char *)h;
    }
    return NULL;
}

/* ASCII/C-locale classification; no locale framework yet. */
int isdigit(int c)  { return c >= '0' && c <= '9'; }
int islower(int c)  { return c >= 'a' && c <= 'z'; }
int isupper(int c)  { return c >= 'A' && c <= 'Z'; }
int isalpha(int c)  { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
int isalnum(int c)  { return (c >= '0' && c <= '9') || isalpha(c); }
int isxdigit(int c) { return (c >= '0' && c <= '9') ||
                             (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
int isspace(int c)  { return c == ' ' || (c >= 9 && c <= 13); }
int isblank(int c)  { return c == ' ' || c == '\t'; }
int iscntrl(int c)  { return (c >= 0 && c < 32) || c == 127; }
int isprint(int c)  { return c >= 32 && c <= 126; }
int isgraph(int c)  { return c >= 33 && c <= 126; }
int ispunct(int c)  { return isgraph(c) && !isalnum(c); }
int tolower(int c)  { return isupper(c) ? c + ('a' - 'A') : c; }
int toupper(int c)  { return islower(c) ? c - ('a' - 'A') : c; }
