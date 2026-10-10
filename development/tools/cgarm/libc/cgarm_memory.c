/* SIDBOX CGARM: applet-local freestanding memory functions.
 *
 * Compiled ONLY for V2 PIC applets.  No GNU/Newlib libc, global allocator,
 * syscalls, or firmware-side state required.
 *
 * Volatile byte accesses deliberately prevent an optimizing compiler from
 * replacing these implementations with calls back to memset/memcpy, etc.
 * V1 stays on its existing Newlib path.
 */

#include <stddef.h>
#include <stdint.h>

void *memset(void *dest, int value, size_t bytes)
{
    volatile unsigned char *d = (volatile unsigned char *)dest;
    unsigned char v = (unsigned char)value;
    while (bytes--) {
        *d++ = v;
    }
    return dest;
}

void *memcpy(void *dest, const void *src, size_t bytes)
{
    volatile unsigned char *d = (volatile unsigned char *)dest;
    const volatile unsigned char *s = (const volatile unsigned char *)src;
    while (bytes--) {
        *d++ = *s++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t bytes)
{
    volatile unsigned char *d = (volatile unsigned char *)dest;
    const volatile unsigned char *s = (const volatile unsigned char *)src;
    if (!bytes || dest == src) return dest;

    if ((uintptr_t)dest < (uintptr_t)src ||
        (uintptr_t)dest - (uintptr_t)src >= bytes) {
        while (bytes--) {
            *d++ = *s++;
        }
    } else {
        d += bytes;
        s += bytes;
        while (bytes--) {
            *--d = *--s;
        }
    }
    return dest;
}

int memcmp(const void *left, const void *right, size_t bytes)
{
    const volatile unsigned char *a = (const volatile unsigned char *)left;
    const volatile unsigned char *b = (const volatile unsigned char *)right;
    while (bytes--) {
        unsigned char x = *a++;
        unsigned char y = *b++;
        if (x != y) return (int)x - (int)y;
    }
    return 0;
}

/* ARM EABI signatures are (destination, count, value), unlike memset. */
void __aeabi_memset(void *dest, size_t bytes, int value)
{
    (void)memset(dest, value, bytes);
}
void __aeabi_memset4(void *dest, size_t bytes, int value)
{
    (void)memset(dest, value, bytes);
}
void __aeabi_memset8(void *dest, size_t bytes, int value)
{
    (void)memset(dest, value, bytes);
}
void __aeabi_memclr(void *dest, size_t bytes)
{
    (void)memset(dest, 0, bytes);
}
void __aeabi_memclr4(void *dest, size_t bytes)
{
    (void)memset(dest, 0, bytes);
}
void __aeabi_memclr8(void *dest, size_t bytes)
{
    (void)memset(dest, 0, bytes);
}
void __aeabi_memcpy(void *dest, const void *src, size_t bytes)
{
    (void)memcpy(dest, src, bytes);
}
void __aeabi_memcpy4(void *dest, const void *src, size_t bytes)
{
    (void)memcpy(dest, src, bytes);
}
void __aeabi_memcpy8(void *dest, const void *src, size_t bytes)
{
    (void)memcpy(dest, src, bytes);
}
void __aeabi_memmove(void *dest, const void *src, size_t bytes)
{
    (void)memmove(dest, src, bytes);
}
void __aeabi_memmove4(void *dest, const void *src, size_t bytes)
{
    (void)memmove(dest, src, bytes);
}
void __aeabi_memmove8(void *dest, const void *src, size_t bytes)
{
    (void)memmove(dest, src, bytes);
}
