/* CGARM Phase 6: familiar BSD memory helpers, no shared state. */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_bsd_memory.c requires SIDBOX_APPLET_V2"
#endif
#include <stddef.h>
#include <string.h>

void bzero(void *destination, size_t length)
{
    memset(destination, 0, length);
}

void bcopy(const void *source, void *destination, size_t length)
{
    memmove(destination, source, length);
}

int bcmp(const void *left, const void *right, size_t length)
{
    return memcmp(left, right, length) != 0;
}

void *memrchr(const void *buffer, int byte, size_t length)
{
    const unsigned char *p = (const unsigned char *)buffer;
    while (length) {
        --length;
        if (p[length] == (unsigned char)byte) return (void *)(p + length);
    }
    return NULL;
}
