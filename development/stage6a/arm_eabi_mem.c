/* Minimal PIC-compatible ARM EABI memory clear helpers for the tiny test app.
 * Not a general replacement for the complete compiler runtime. */
#include <stddef.h>
void __aeabi_memclr4(void *dest, size_t bytes)
{
    volatile unsigned char *p = (volatile unsigned char *)dest;
    for (size_t i = 0; i < bytes; ++i) p[i] = 0;
}
void __aeabi_memclr(void *dest, size_t bytes)
{
    __aeabi_memclr4(dest, bytes);
}
void __aeabi_memclr8(void *dest, size_t bytes)
{
    __aeabi_memclr4(dest, bytes);
}
