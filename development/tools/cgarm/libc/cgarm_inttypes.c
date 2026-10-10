/* SIDBOX CGARM Phase 6: inttypes-compatible conversions and arithmetic.
 * Avoids libgcc 64-bit division helpers in the freestanding ARM PIC build. */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_inttypes.c requires SIDBOX_APPLET_V2"
#endif
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

intmax_t strtoimax(const char *text, char **endptr, int base)
{
    return (intmax_t)strtoll(text, endptr, base);
}

uintmax_t strtoumax(const char *text, char **endptr, int base)
{
    return (uintmax_t)strtoull(text, endptr, base);
}

intmax_t imaxabs(intmax_t value)
{
    return value < 0 ? -value : value; /* C signed abs(INTMAX_MIN) is undefined. */
}

static uintmax_t cg_udiv(uintmax_t n, uintmax_t d, uintmax_t *rem)
{
    uintmax_t quotient = 0, remainder = 0;
    /* Restoring division, no 64-bit divide helper required. */
    for (int i = (int)(sizeof(uintmax_t) * 8u) - 1; i >= 0; --i) {
        uintmax_t next = (n >> i) & 1u;
        uintmax_t high = remainder >> (sizeof(uintmax_t) * 8u - 1u);
        remainder = (remainder << 1) | next;
        if (high || remainder >= d) {
            remainder -= d;
            quotient |= (uintmax_t)1 << i;
        }
    }
    *rem = remainder;
    return quotient;
}

imaxdiv_t imaxdiv(intmax_t numerator, intmax_t denominator)
{
    imaxdiv_t result = {0, 0};
    if (!denominator || (numerator == INTMAX_MIN && denominator == -1))
        return result; /* Division overflow/zero: not defined by C, return zero. */
    int negq = (numerator < 0) != (denominator < 0);
    uintmax_t un = numerator < 0 ? 0u - (uintmax_t)numerator : (uintmax_t)numerator;
    uintmax_t ud = denominator < 0 ? 0u - (uintmax_t)denominator : (uintmax_t)denominator;
    uintmax_t r;
    uintmax_t q = cg_udiv(un, ud, &r);
    result.quot = negq ? (intmax_t)((uintmax_t)0 - q) : (intmax_t)q;
    result.rem = numerator < 0 ? -(intmax_t)r : (intmax_t)r;
    return result;
}

lldiv_t lldiv(long long numerator, long long denominator)
{
    imaxdiv_t d = imaxdiv((intmax_t)numerator, (intmax_t)denominator);
    lldiv_t result = {(long long)d.quot, (long long)d.rem};
    return result;
}
