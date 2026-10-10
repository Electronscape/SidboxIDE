/* SIDBOX CGARM - freestanding PIC stdio formatting (basic profile).
 * V1 is deliberately unaffected: only compile this file for SIDBOX_APPLET_V2.
 * Supports: %% %c %s %d %i %u %o %x %X %p %b, field width, precision,
 * left/zero padding, signs, #, and hh/h/l/ll/z/t/j length modifiers.
 * Does not yet support floating-point formatting, %n or wide strings.
 * No Newlib, malloc, libgcc division helpers, shared mutable state or fixed
 * printf output limit. Output goes to the existing console writec() API.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_printf.c must only be built for SIDBOX_APPLET_V2"
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <limits.h>
#include "apis.h"

#define SB_CHUNK 128u
#define SB_MAX_FIELD 8192u

typedef struct {
    char *dst;
    size_t cap;
    size_t length;
    unsigned console;
    char chunk[SB_CHUNK];
    unsigned buffered;
} SB_Print;

static void sb_flush(SB_Print *s)
{
    if (s->console && s->buffered) {
        API->gui->console->writec(0, s->chunk, s->buffered);
        s->buffered = 0;
    }
}

static void sb_char(SB_Print *s, char c)
{
    if (s->console) {
        s->chunk[s->buffered++] = c;
        if (s->buffered == SB_CHUNK) sb_flush(s);
    } else if (s->dst && s->length < s->cap - (s->cap != 0)) {
        s->dst[s->length] = c;
    }
    if (s->length < (size_t)INT_MAX) ++s->length;
}

static void sb_pad(SB_Print *s, char c, unsigned n)
{
    while (n--) sb_char(s, c);
}

static unsigned sb_width(unsigned n)
{
    return n > SB_MAX_FIELD ? SB_MAX_FIELD : n;
}

static unsigned sb_digits(const char **p)
{
    unsigned n = 0;
    while (**p >= '0' && **p <= '9') {
        unsigned digit = (unsigned)(*(*p)++ - '0');
        n = n > (SB_MAX_FIELD - digit) / 10u ? SB_MAX_FIELD : n * 10u + digit;
    }
    return n;
}

/* Long division by a tiny radix avoids libgcc's __aeabi_uldivmod,
 * which is unavailable to this V2 PIE linker. */
static uint64_t sb_divmod(uint64_t n, unsigned radix, unsigned *rem)
{
    uint64_t q = 0, r = 0;
    for (int bit = 63; bit >= 0; --bit) {
        r = (r << 1) | ((n >> bit) & 1u);
        if (r >= radix) {
            r -= radix;
            q |= (UINT64_C(1) << bit);
        }
    }
    *rem = (unsigned)r;
    return q;
}

enum { SB_LEFT = 1, SB_ZERO = 2, SB_PLUS = 4, SB_SPACE = 8, SB_ALT = 16 };
enum { SB_NORMAL, SB_HH, SB_H, SB_L, SB_LL, SB_Z, SB_T, SB_J };

static int64_t sb_signed(va_list *args, unsigned length)
{
    switch (length) {
    case SB_HH: return (signed char)va_arg(*args, int);
    case SB_H:  return (short)va_arg(*args, int);
    case SB_L:  return va_arg(*args, long);
    case SB_LL: return va_arg(*args, long long);
    case SB_Z:  return (int64_t)va_arg(*args, ptrdiff_t);
    case SB_T:  return va_arg(*args, ptrdiff_t);
    case SB_J:  return va_arg(*args, intmax_t);
    default:    return va_arg(*args, int);
    }
}

static uint64_t sb_unsigned(va_list *args, unsigned length)
{
    switch (length) {
    case SB_HH: return (unsigned char)va_arg(*args, unsigned int);
    case SB_H:  return (unsigned short)va_arg(*args, unsigned int);
    case SB_L:  return va_arg(*args, unsigned long);
    case SB_LL: return va_arg(*args, unsigned long long);
    case SB_Z:  return va_arg(*args, size_t);
    case SB_T:  return (uint64_t)va_arg(*args, size_t);
    case SB_J:  return va_arg(*args, uintmax_t);
    default:    return va_arg(*args, unsigned int);
    }
}

static void sb_number(SB_Print *s, uint64_t number, unsigned base,
                      int negative, unsigned flags, unsigned width,
                      int precision, int upper, int pointer)
{
    static const char lo[] = "0123456789abcdef";
    static const char hi[] = "0123456789ABCDEF";
    const char *hex = upper ? hi : lo;
    char reversed[65];
    unsigned count = 0;
    const uint64_t original = number;

    if (number || precision != 0) {
        do {
            unsigned rem;
            number = sb_divmod(number, base, &rem);
            reversed[count++] = hex[rem];
        } while (number && count < sizeof(reversed));
    }

    char sign = negative ? '-' : ((flags & SB_PLUS) ? '+' : ((flags & SB_SPACE) ? ' ' : 0));
    const char *prefix = "";
    unsigned prefix_len = 0;
    if (pointer || ((flags & SB_ALT) && original)) {
        if (base == 16) { prefix = upper ? "0X" : "0x"; prefix_len = 2; }
        else if (base == 2) { prefix = "0b"; prefix_len = 2; }
        else if (base == 8 && !(count && reversed[count-1] == '0')) {
            prefix = "0"; prefix_len = 1;
        }
    } else if ((flags & SB_ALT) && base == 8 && count == 0) {
        reversed[count++] = '0';
    }

    unsigned zeros = precision > (int)count ? (unsigned)precision - count : 0;
    unsigned occupied = count + zeros + prefix_len + (sign != 0);
    unsigned padding = width > occupied ? width - occupied : 0;
    if ((flags & SB_ZERO) && !(flags & SB_LEFT) && precision < 0) {
        zeros += padding;
        padding = 0;
    }
    if (!(flags & SB_LEFT)) sb_pad(s, ' ', padding);
    if (sign) sb_char(s, sign);
    for (unsigned i = 0; i < prefix_len; ++i) sb_char(s, prefix[i]);
    sb_pad(s, '0', zeros);
    while (count) sb_char(s, reversed[--count]);
    if (flags & SB_LEFT) sb_pad(s, ' ', padding);
}

static int sb_format(SB_Print *s, const char *format, va_list *args)
{
    if (!format) return -1;
    while (*format) {
        if (*format != '%') { sb_char(s, *format++); continue; }
        ++format;
        if (*format == '%') { sb_char(s, '%'); ++format; continue; }

        unsigned flags = 0;
        for (;;) {
            switch (*format) {
            case '-': flags |= SB_LEFT;  break;
            case '0': flags |= SB_ZERO;  break;
            case '+': flags |= SB_PLUS;  break;
            case ' ': flags |= SB_SPACE; break;
            case '#': flags |= SB_ALT;   break;
            default: goto flags_done;
            }
            ++format;
        }
flags_done: ;
        unsigned width = 0;
        if (*format == '*') {
            int w = va_arg(*args, int);
            ++format;
            if (w < 0) {
                flags |= SB_LEFT;
                width = w == INT_MIN ? SB_MAX_FIELD : sb_width((unsigned)-w);
            } else width = sb_width((unsigned)w);
        } else width = sb_digits(&format);

        int precision = -1;
        if (*format == '.') {
            ++format;
            if (*format == '*') {
                int p = va_arg(*args, int);
                ++format;
                if (p >= 0) precision = (int)sb_width((unsigned)p);
            } else precision = (int)sb_digits(&format);
        }

        unsigned length = SB_NORMAL;
        if (*format == 'h') {
            length = SB_H; ++format;
            if (*format == 'h') { length = SB_HH; ++format; }
        } else if (*format == 'l') {
            length = SB_L; ++format;
            if (*format == 'l') { length = SB_LL; ++format; }
        } else if (*format == 'z') { length = SB_Z; ++format; }
        else if (*format == 't') { length = SB_T; ++format; }
        else if (*format == 'j') { length = SB_J; ++format; }

        char spec = *format;
        if (!spec) break;
        ++format;

        if (spec == 'd' || spec == 'i') {
            int64_t n = sb_signed(args, length);
            uint64_t mag = n < 0 ? (uint64_t)(-(n + 1)) + 1u : (uint64_t)n;
            sb_number(s, mag, 10, n < 0, flags, width, precision, 0, 0);
        } else if (spec == 'u' || spec == 'x' || spec == 'X' ||
                   spec == 'o' || spec == 'b') {
            unsigned base = spec == 'o' ? 8 : (spec == 'x' || spec == 'X') ? 16 : spec == 'b' ? 2 : 10;
            sb_number(s, sb_unsigned(args, length), base, 0,
                      flags & ~(SB_PLUS | SB_SPACE), width, precision, spec == 'X', 0);
        } else if (spec == 'p') {
            void *p = va_arg(*args, void *);
            sb_number(s, (uintptr_t)p, 16, 0, flags & ~(SB_PLUS | SB_SPACE),
                      width, precision, 0, 1);
        } else if (spec == 's') {
            const char *p = va_arg(*args, const char *);
            if (!p) p = "(null)";
            unsigned n = 0;
            while (p[n] && (precision < 0 || n < (unsigned)precision)) ++n;
            unsigned padding = width > n ? width - n : 0;
            if (!(flags & SB_LEFT)) sb_pad(s, ' ', padding);
            for (unsigned i = 0; i < n; ++i) sb_char(s, p[i]);
            if (flags & SB_LEFT) sb_pad(s, ' ', padding);
        } else if (spec == 'c') {
            unsigned padding = width > 1 ? width - 1 : 0;
            if (!(flags & SB_LEFT)) sb_pad(s, ' ', padding);
            sb_char(s, (char)va_arg(*args, int));
            if (flags & SB_LEFT) sb_pad(s, ' ', padding);
        } else if (spec == 'f' || spec == 'F' || spec == 'e' || spec == 'E' ||
                   spec == 'g' || spec == 'G' || spec == 'a' || spec == 'A') {
            /* Intentionally visible until a tested PIC float formatter exists. */
            (void)va_arg(*args, double);
            const char *message = "<float?>";
            while (*message) sb_char(s, *message++);
        } else {
            sb_char(s, '%'); sb_char(s, spec);
        }
    }
    sb_flush(s);
    if (!s->console && s->dst && s->cap) {
        size_t end = s->length < s->cap ? s->length : s->cap - 1;
        s->dst[end] = '\0';
    }
    return (int)s->length;
}

int vsnprintf(char *dst, size_t cap, const char *fmt, va_list args)
{
    SB_Print s = {0};
    s.dst = dst;
    s.cap = cap;
    va_list copy;
    va_copy(copy, args);
    int result = sb_format(&s, fmt, &copy);
    va_end(copy);
    return result;
}

int snprintf(char *dst, size_t cap, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int result = vsnprintf(dst, cap, fmt, args);
    va_end(args);
    return result;
}

int vsprintf(char *dst, const char *fmt, va_list args)
{
    return vsnprintf(dst, (size_t)-1, fmt, args);
}

int sprintf(char *dst, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int result = vsprintf(dst, fmt, args);
    va_end(args);
    return result;
}

int vprintf(const char *fmt, va_list args)
{
    SB_Print s = {0};
    s.console = 1;
    va_list copy;
    va_copy(copy, args);
    int result = sb_format(&s, fmt, &copy);
    va_end(copy);
    return result;
}

int printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int result = vprintf(fmt, args);
    va_end(args);
    return result;
}

int putchar(int c)
{
    char ch = (char)c;
    API->gui->console->writec(0, &ch, 1);
    return (unsigned char)ch;
}

int puts(const char *str)
{
    if (!str) return -1;
    unsigned char *p = (unsigned char *)str;
    while (*p) {
        size_t n = 0;
        while (p[n] && n < SB_CHUNK) ++n;
        API->gui->console->writec(0, (const char*)p, (uint32_t)n);
        p += n;
    }
    API->gui->console->writec(0, "\n", 1);
    return 0;
}
