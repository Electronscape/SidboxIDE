/* CGARM Phase 11: overflow-checked array resizing (BSD/POSIX extension). */
#ifndef SIDBOX_APPLET_V2
#error "Phase 11 allocator extensions require SIDBOX_APPLET_V2"
#endif
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (size != 0 && nmemb > SIZE_MAX / size) {
        errno = ENOMEM;
        return NULL;
    }
    return realloc(ptr, nmemb * size);
}
