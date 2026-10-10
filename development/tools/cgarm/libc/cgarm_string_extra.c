/* SIDBOX CGARM Phase 2: string and memory extras.
 * Built only into CGARM PIC applets. Never link into V1/Gaming.
 * strtok() state is local to the applet, not reentrant: prefer strtok_r().
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_string_extra.c requires SIDBOX_APPLET_V2"
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *memchr(const void *ptr, int ch, size_t n)
{
    const unsigned char *p = (const unsigned char *)ptr;
    const unsigned char c = (unsigned char)ch;
    for (size_t i = 0; i < n; ++i)
        if (p[i] == c) return (void *)(p + i);
    return NULL;
}

static int cg_contains(const char *set, unsigned char c)
{
    while (*set) {
        if ((unsigned char)*set++ == c) return 1;
    }
    return 0;
}

size_t strspn(const char *s, const char *accept)
{
    const char *p = s;
    while (*p && cg_contains(accept, (unsigned char)*p)) ++p;
    return (size_t)(p - s);
}

size_t strcspn(const char *s, const char *reject)
{
    const char *p = s;
    while (*p && !cg_contains(reject, (unsigned char)*p)) ++p;
    return (size_t)(p - s);
}

char *strpbrk(const char *s, const char *accept)
{
    while (*s) {
        if (cg_contains(accept, (unsigned char)*s)) return (char *)s;
        ++s;
    }
    return NULL;
}

char *strtok_r(char *s, const char *delim, char **saveptr)
{
    if (!s) s = *saveptr;
    if (!s) return NULL;
    s += strspn(s, delim);
    if (!*s) { *saveptr = s; return NULL; }
    char *end = s + strcspn(s, delim);
    if (*end) {
        *end = '\0';
        *saveptr = end + 1;
    } else {
        *saveptr = end;
    }
    return s;
}

char *strtok(char *s, const char *delim)
{
    static char *saveptr;
    return strtok_r(s, delim, &saveptr);
}

char *strdup(const char *s)
{
    size_t n = strlen(s);
    if (n == SIZE_MAX) return NULL;
    char *copy = (char *)malloc(n + 1u);
    if (copy) memcpy(copy, s, n + 1u);
    return copy;
}

char *strndup(const char *s, size_t maxlen)
{
    size_t n = strnlen(s, maxlen);
    if (n == SIZE_MAX) return NULL;
    char *copy = (char *)malloc(n + 1u);
    if (copy) {
        memcpy(copy, s, n);
        copy[n] = '\0';
    }
    return copy;
}
