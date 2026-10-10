/* CGARM Phase 5: string-based scanf input, no FILE/stream support.
 * Provides sscanf/vsscanf: integers, decimal floating point, strings,
 * characters, scansets, %p, %n, assignment suppression and field widths.
 * Width-limited numeric fields use a small fixed temporary buffer;
 * hexadecimal floating point (%a/%A), locale and wide chars are unsupported.
 * As in standard sscanf, callers must size %s/%[ buffers themselves.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_scanf.c requires SIDBOX_APPLET_V2"
#endif
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

#define CG_SCAN_NUM_MAX 191u

enum { CG_SCAN_NONE, CG_SCAN_HH, CG_SCAN_H, CG_SCAN_L, CG_SCAN_LL,
       CG_SCAN_Z, CG_SCAN_T, CG_SCAN_J, CG_SCAN_CAP_L };

static int cg_space(int c) { return c == ' ' || (c >= 9 && c <= 13); }
static int cg_dec(int c) { return c >= '0' && c <= '9'; }
static int cg_hex(int c) {
    return cg_dec(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}
static int cg_scan_numeric(int ch, char spec)
{
    if (ch == '+' || ch == '-') return 1;
    if (spec == 'f' || spec == 'F' || spec == 'e' || spec == 'E' ||
        spec == 'g' || spec == 'G') {
        return cg_dec(ch) || ch == '.' ||
               (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }
    if (spec == 'd' || spec == 'u') return cg_dec(ch);
    if (spec == 'o') return ch >= '0' && ch <= '7';
    if (spec == 'i' || spec == 'x' || spec == 'X' || spec == 'p')
        return cg_hex(ch) || ch == 'x' || ch == 'X';
    return 0;
}

static void cg_store_signed(va_list *ap, int length, long long value)
{
    switch (length) {
    case CG_SCAN_HH: *va_arg(*ap, signed char *) = (signed char)value; break;
    case CG_SCAN_H:  *va_arg(*ap, short *) = (short)value; break;
    case CG_SCAN_L:  *va_arg(*ap, long *) = (long)value; break;
    case CG_SCAN_LL: *va_arg(*ap, long long *) = value; break;
    case CG_SCAN_Z: case CG_SCAN_T:
        *va_arg(*ap, ptrdiff_t *) = (ptrdiff_t)value; break;
    case CG_SCAN_J: *va_arg(*ap, intmax_t *) = (intmax_t)value; break;
    default: *va_arg(*ap, int *) = (int)value; break;
    }
}
static void cg_store_unsigned(va_list *ap, int length, unsigned long long value)
{
    switch (length) {
    case CG_SCAN_HH: *va_arg(*ap, unsigned char *) = (unsigned char)value; break;
    case CG_SCAN_H:  *va_arg(*ap, unsigned short *) = (unsigned short)value; break;
    case CG_SCAN_L:  *va_arg(*ap, unsigned long *) = (unsigned long)value; break;
    case CG_SCAN_LL: *va_arg(*ap, unsigned long long *) = value; break;
    case CG_SCAN_Z: case CG_SCAN_T:
        *va_arg(*ap, size_t *) = (size_t)value; break;
    case CG_SCAN_J: *va_arg(*ap, uintmax_t *) = (uintmax_t)value; break;
    default: *va_arg(*ap, unsigned *) = (unsigned)value; break;
    }
}

/* Format scanset into a 256-byte membership map, returning closing-bracket+1.
 * Leading ']' and '-' are literals; ranges such as a-z are supported.
 */
static const char *cg_scan_set(const char *fmt, unsigned char set[256])
{
    for (unsigned i=0; i<256; ++i) set[i] = 0;
    int invert = *fmt == '^';
    if (invert) ++fmt;
    int previous = -1;
    if (*fmt == ']') { set[(unsigned char)']'] = 1; previous = ']'; ++fmt; }
    while (*fmt && *fmt != ']') {
        unsigned char current = (unsigned char)*fmt++;
        if (current == '-' && previous >= 0 && *fmt && *fmt != ']') {
            unsigned char last = (unsigned char)*fmt++;
            if (last >= previous) {
                for (unsigned i = (unsigned)previous; i <= last; ++i) set[i] = 1;
            } else {
                set[(unsigned char)'-'] = 1;
                set[last] = 1;
            }
            previous = last;
        } else {
            set[current] = 1;
            previous = current;
        }
    }
    if (*fmt != ']') return NULL;
    if (invert) for (unsigned i=0; i<256; ++i) set[i] = (unsigned char)!set[i];
    return fmt + 1;
}

int vsscanf(const char *input, const char *format, va_list arguments)
{
    if (!input || !format) return -1;
    va_list ap;
    va_copy(ap, arguments);
    const char *p = input;
    const char *f = format;
    int assigned = 0, input_failure = 0;

    while (*f) {
        if (cg_space((unsigned char)*f)) {
            while (cg_space((unsigned char)*f)) ++f;
            while (cg_space((unsigned char)*p)) ++p;
            continue;
        }
        if (*f != '%') {
            if (*p != *f) { if (!*p) input_failure = 1; break; }
            ++p; ++f; continue;
        }
        ++f;
        if (*f == '%') {
            if (*p != '%') { if (!*p) input_failure = 1; break; }
            ++p; ++f; continue;
        }
        int suppress = *f == '*';
        if (suppress) ++f;
        unsigned width = 0;
        while (cg_dec((unsigned char)*f)) {
            unsigned digit = (unsigned)(*f++ - '0');
            width = width > (UINT_MAX - digit) / 10u ? UINT_MAX : width * 10u + digit;
        }
        if (!width) width = UINT_MAX;
        int length = CG_SCAN_NONE;
        if (*f == 'h') { ++f; length = *f == 'h' ? (++f, CG_SCAN_HH) : CG_SCAN_H; }
        else if (*f == 'l') { ++f; length = *f == 'l' ? (++f, CG_SCAN_LL) : CG_SCAN_L; }
        else if (*f == 'z') { ++f; length = CG_SCAN_Z; }
        else if (*f == 't') { ++f; length = CG_SCAN_T; }
        else if (*f == 'j') { ++f; length = CG_SCAN_J; }
        else if (*f == 'L') { ++f; length = CG_SCAN_CAP_L; }
        char spec = *f;
        if (!spec) break;
        ++f;

        if (spec == 'n') {
            if (!suppress) cg_store_signed(&ap, length, (long long)(p-input));
            continue;
        }
        if (spec == 'c') {
            if (width == UINT_MAX) width = 1;
            unsigned i=0;
            while (i < width && p[i]) ++i;
            if (i != width) { input_failure=1; break; }
            if (!suppress) {
                char *dest = va_arg(ap, char *);
                for (unsigned k=0; k<width; ++k) dest[k] = p[k];
                ++assigned;
            }
            p += width;
            continue;
        }

        if (spec == '[' || spec == 's') {
            unsigned char set[256];
            if (spec == '[') {
                const char *next = cg_scan_set(f, set);
                if (!next) break;
                f = next;
            } else {
                while (cg_space((unsigned char)*p)) ++p;
            }
            unsigned count = 0;
            while (count < width && p[count] &&
                   (spec == 's' ? !cg_space((unsigned char)p[count]) : set[(unsigned char)p[count]]))
                ++count;
            if (!count) { if (!*p) input_failure = 1; break; }
            if (!suppress) {
                char *dest = va_arg(ap, char *);
                for (unsigned k=0; k<count; ++k) dest[k] = p[k];
                dest[count] = '\0';
                ++assigned;
            }
            p += count;
            continue;
        }

        if (spec != 'd' && spec != 'i' && spec != 'u' && spec != 'o' &&
            spec != 'x' && spec != 'X' && spec != 'p' &&
            spec != 'f' && spec != 'F' && spec != 'e' && spec != 'E' &&
            spec != 'g' && spec != 'G') {
            /* Unsupported conversion (e.g. hex floating point or wide char). */
            break;
        }
        while (cg_space((unsigned char)*p)) ++p;
        if (!*p) { input_failure = 1; break; }
        char number[CG_SCAN_NUM_MAX+1];
        unsigned count=0;
        unsigned limit = width < CG_SCAN_NUM_MAX ? width : CG_SCAN_NUM_MAX;
        while (count < limit && p[count] && cg_scan_numeric((unsigned char)p[count], spec)) {
            number[count] = p[count]; ++count;
        }
        if (count == CG_SCAN_NUM_MAX && width > CG_SCAN_NUM_MAX &&
            cg_scan_numeric((unsigned char)p[count], spec)) break;
        number[count] = '\0';
        if (!count) break;
        char *end = NULL;
        int floating = spec=='f' || spec=='F' || spec=='e' || spec=='E' ||
                       spec=='g' || spec=='G';
        if (floating) {
            double value = strtod(number, &end);
            if (end == number) break;
            if (!suppress) {
                if (length == CG_SCAN_CAP_L) *va_arg(ap, long double *) = (long double)value;
                else if (length == CG_SCAN_L) *va_arg(ap, double *) = value;
                else *va_arg(ap, float *) = (float)value;
                ++assigned;
            }
        } else {
            int base = spec=='i' ? 0 : (spec=='x' || spec=='X' || spec=='p' ? 16 :
                       (spec=='o' ? 8 : 10));
            int signed_value = spec == 'd' || spec == 'i';
            if (signed_value) {
                long long value = strtoll(number, &end, base);
                if (end == number) break;
                if (!suppress) { cg_store_signed(&ap, length, value); ++assigned; }
            } else {
                unsigned long long value = strtoull(number, &end, base);
                if (end == number) break;
                if (!suppress) {
                    if (spec == 'p') *va_arg(ap, void **) = (void *)(uintptr_t)value;
                    else cg_store_unsigned(&ap, length, value);
                    ++assigned;
                }
            }
        }
        p += (size_t)(end - number);
    }
    va_end(ap);
    return input_failure && assigned == 0 ? -1 : assigned;
}

int sscanf(const char *input, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int result = vsscanf(input, format, ap);
    va_end(ap);
    return result;
}
