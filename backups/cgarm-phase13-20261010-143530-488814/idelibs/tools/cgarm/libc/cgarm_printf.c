/* SIDBOX CGARM - freestanding PIC stdio formatting (basic profile).
 * V1 is deliberately unaffected: only compile this file for SIDBOX_APPLET_V2.
 * Supports: %% %c %s %d %i %u %o %x %X %p %b, field width, precision,
 * left/zero padding, signs, #, and hh/h/l/ll/z/t/j length modifiers.
 * Supports bounded float formatting in Phase 3; no %a/%A, %n or wide strings.
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

/* Phase 3: bounded embedded floating-point formatting.
 * No libm, heap, or Newlib dependencies.  Handles f/F/e/E/g/G with
 * precision 0..9 (default 6); NaN/Inf/sign/width/flags.  The decimal
 * digit extraction is intentionally approximate beyond 15 significant
 * digits, not an IEEE correctly-rounded dtoa replacement.
 */
#define SB_FLOAT_PRECISION_MAX 9
#define SB_FLOAT_BUFFER 352

static int sb_fsign(double x)
{
    union { double d; uint64_t u; } bits;
    bits.d = x;
    return (int)(bits.u >> 63);
}

static int sb_fspecial(double x)
{
    union { double d; uint64_t u; } bits;
    bits.d = x;
    if (((bits.u >> 52) & 0x7ffu) != 0x7ffu) return 0;
    return (bits.u & UINT64_C(0xfffffffffffff)) ? 2 : 1;
}

/* Produces decimal digits from normalised |x|, with decimal exponent.
 * This requires only hardware double arithmetic on Cortex-M7. */
static void sb_fnormal(double x, double *scaled, int *exponent)
{
    int exp = 0;
    if (x != 0.0) {
        while (x >= 10.0 && exp < 308) { x /= 10.0; ++exp; }
        while (x < 1.0 && exp > -324) { x *= 10.0; --exp; }
    }
    *scaled = x;
    *exponent = exp;
}

static int sb_fnext(double *scaled)
{
    int digit = (int)*scaled; /* scaled is in [0,10). */
    if (digit < 0) digit = 0;
    if (digit > 9) digit = 9;
    *scaled = (*scaled - (double)digit) * 10.0;
    return digit;
}

static unsigned sb_f_fixed(char *out, double x, int precision, int alt)
{
    double scaled;
    int exp;
    sb_fnormal(x, &scaled, &exp);
    const int start = exp > 0 ? exp : 0;
    unsigned length = 0;
    int kept = 0;
    for (int pos = start; pos >= -precision - 1; --pos) {
        if (pos == -1 && (precision || alt)) out[length++] = '.';
        int digit = 0;
        if (x != 0.0 && pos <= exp) {
            digit = sb_fnext(&scaled);
            ++kept;
            if (kept > 17) digit = 0;
        }
        if (pos == -precision - 1) {
            if (digit > 5 || (digit == 5 &&
                (scaled > 1e-12 || (length && (out[length - 1] - '0') % 2 != 0)))) {
                int at = (int)length - 1;
                while (at >= 0) {
                    if (out[at] == '.') { --at; continue; }
                    if (out[at] < '9') { ++out[at]; break; }
                    out[at--] = '0';
                }
                if (at < 0) {
                    for (int i = (int)length; i > 0; --i) out[i] = out[i - 1];
                    out[0] = '1';
                    ++length;
                }
            }
        } else out[length++] = (char)('0' + digit);
    }
    return length;
}

static unsigned sb_f_exponent(char *out, double x, int precision, int alt, int upper)
{
    double scaled;
    int exp;
    sb_fnormal(x, &scaled, &exp);
    unsigned length = 0;
    /* A single integer digit, then precision fractional digits, then the rounding digit. */
    for (int i = 0; i <= precision + 1; ++i) {
        if (i == 1 && (precision || alt)) out[length++] = '.';
        int digit = x == 0.0 ? 0 : sb_fnext(&scaled);
        if (i == precision + 1) {
            if (digit > 5 || (digit == 5 &&
                (scaled > 1e-12 || (length && (out[length - 1] - '0') % 2 != 0)))) {
                int at = (int)length - 1;
                while (at >= 0) {
                    if (out[at] == '.') { --at; continue; }
                    if (out[at] < '9') { ++out[at]; break; }
                    out[at--] = '0';
                }
                if (at < 0) { /* 9.999 -> 1.000e+N+1 */
                    out[0] = '1';
                    ++exp;
                }
            }
        } else out[length++] = (char)('0' + digit);
    }
    out[length++] = upper ? 'E' : 'e';
    out[length++] = exp < 0 ? '-' : '+';
    unsigned magnitude = (unsigned)(exp < 0 ? -exp : exp);
    if (magnitude >= 100) out[length++] = (char)('0' + magnitude / 100);
    out[length++] = (char)('0' + (magnitude / 10) % 10);
    out[length++] = (char)('0' + magnitude % 10);
    return length;
}

static void sb_float(SB_Print *s, double value, char spec,
                     unsigned flags, unsigned width, int precision)
{
    char buffer[SB_FLOAT_BUFFER];
    unsigned n = 0;
    const int negative = sb_fsign(value);
    const char sign = negative ? '-' : (flags & SB_PLUS) ? '+' : (flags & SB_SPACE) ? ' ' : 0;
    const int upper = spec >= 'A' && spec <= 'Z';
    int special = sb_fspecial(value);
    if (special) {
        const char *str = special == 2 ? (upper ? "NAN" : "nan") : (upper ? "INF" : "inf");
        while (*str) buffer[n++] = *str++;
    } else if (precision > SB_FLOAT_PRECISION_MAX) {
        const char *str = "<prec?>";
        while (*str) buffer[n++] = *str++;
    } else {
        if (negative) value = -value;
        if (precision < 0) precision = 6;
        if (spec == 'g' || spec == 'G') {
            /* General format: precision is number of significant digits. */
            if (!precision) precision = 1;
            double norm;
            int exp;
            sb_fnormal(value, &norm, &exp);
            int scientific = exp < -4 || exp >= precision;
            if (!scientific) {
                int digits = precision - (exp + 1);
                n = sb_f_fixed(buffer, value, digits, flags & SB_ALT);
                unsigned integer_digits = 0;
                while (integer_digits < n && buffer[integer_digits] != '.')
                    ++integer_digits;
                /* Rounding may increase the exponent: 99.9 with %.2g becomes 1e+02. */
                if (exp >= 0 && integer_digits > (unsigned)precision)
                    scientific = 1;
            }
            if (scientific) {
                n = sb_f_exponent(buffer, value, precision - 1, flags & SB_ALT, upper);
                if (!(flags & SB_ALT)) {
                    unsigned suffix = n;
                    while (suffix && buffer[suffix - 1] != 'e' && buffer[suffix - 1] != 'E') --suffix;
                    if (suffix) {
                        unsigned before = suffix - 1;
                        while (before && buffer[before - 1] == '0') --before;
                        if (before && buffer[before - 1] == '.') --before;
                        for (unsigned i = suffix - 1; i < n; ++i) buffer[before + i - suffix + 1] = buffer[i];
                        n = before + n - (suffix - 1);
                    }
                }
            } else if (!(flags & SB_ALT)) {
                int dot = -1;
                for (unsigned j = 0; j < n; ++j)
                    if (buffer[j] == '.') { dot = (int)j; break; }
                if (dot >= 0) {
                    while (n > (unsigned)dot + 1 && buffer[n - 1] == '0') --n;
                    if (n == (unsigned)dot + 1) --n;
                }
            }
        } else if (spec == 'e' || spec == 'E') {
            n = sb_f_exponent(buffer, value, precision, flags & SB_ALT, upper);
        } else {
            n = sb_f_fixed(buffer, value, precision, flags & SB_ALT);
        }
    }
    unsigned padding = width > n + (sign != 0) ? width - n - (sign != 0) : 0;
    char pad = ((flags & SB_ZERO) && !(flags & SB_LEFT) && !special) ? '0' : ' ';
    if (!(flags & SB_LEFT) && pad == ' ') sb_pad(s, pad, padding);
    if (sign) sb_char(s, sign);
    if (!(flags & SB_LEFT) && pad == '0') sb_pad(s, pad, padding);
    for (unsigned i = 0; i < n; ++i) sb_char(s, buffer[i]);
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
                   spec == 'g' || spec == 'G') {
            sb_float(s, va_arg(*args, double), spec, flags, width, precision);
        } else if (spec == 'a' || spec == 'A') {
            (void)va_arg(*args, double);
            const char *message = "<hexfloat?>";
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
