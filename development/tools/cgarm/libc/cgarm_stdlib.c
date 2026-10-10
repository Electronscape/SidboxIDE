/* SIDBOX CGARM Phase 2: integer conversions, sorting/search, RNG.
 * Freestanding PIE, no newlib runtime calls or ARM 64-bit division helpers.
 * Keep the existing applet-local errno/malloc implementation unchanged.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_stdlib.c requires SIDBOX_APPLET_V2"
#endif
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>

static int cg_digit(unsigned char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

/* Division using shifts/subtractions: prevents __aeabi_uldivmod imports. */
static unsigned long long cg_div_u64(unsigned long long number, unsigned divisor,
                                     unsigned *remainder)
{
    unsigned long long quotient = 0;
    unsigned long long rem = 0;
    for (int i = 63; i >= 0; --i) {
        rem = (rem << 1) | ((number >> i) & 1u);
        if (rem >= divisor) {
            rem -= divisor;
            quotient |= (1ULL << i);
        }
    }
    *remainder = (unsigned)rem;
    return quotient;
}

typedef struct {
    unsigned long long number;
    const char *end;
    int negative;
    int digits;
    int overflow;
} CG_Number;

static CG_Number cg_parse_integer(const char *nptr, int base,
                                  unsigned long long positive_limit,
                                  unsigned long long negative_limit)
{
    CG_Number out = {0};
    const char *p = nptr;
    out.end = nptr;

    while (*p == ' ' || (*p >= '\t' && *p <= '\r')) ++p;
    if (*p == '+' || *p == '-') {
        out.negative = (*p == '-');
        ++p;
    }
    /* Only consume 0x if a valid hexadecimal digit follows. */
    if ((base == 0 || base == 16) && p[0] == '0' &&
        (p[1] == 'x' || p[1] == 'X') && cg_digit((unsigned char)p[2]) >= 0 &&
        cg_digit((unsigned char)p[2]) < 16) {
        p += 2;
        base = 16;
    }
    if (base == 0) base = *p == '0' ? 8 : 10;

    unsigned remainder = 0;
    unsigned long long limit = out.negative ? negative_limit : positive_limit;
    unsigned long long cutoff = cg_div_u64(limit, (unsigned)base, &remainder);
    for (;;) {
        int digit = cg_digit((unsigned char)*p);
        if (digit < 0 || digit >= base) break;
        out.digits = 1;
        if (!out.overflow) {
            if (out.number > cutoff ||
                (out.number == cutoff && (unsigned)digit > remainder)) {
                out.overflow = 1;
                out.number = limit;
            } else {
                out.number = out.number * (unsigned)base + (unsigned)digit;
            }
        }
        ++p;
    }
    if (out.digits) out.end = p;
    return out;
}

static CG_Number cg_convert(const char *s, char **endptr, int base,
                            unsigned long long pos, unsigned long long neg)
{
    if (base && (base < 2 || base > 36)) {
        errno = EINVAL;
        if (endptr) *endptr = (char *)s;
        CG_Number fail = {0};
        return fail;
    }
    CG_Number number = cg_parse_integer(s, base, pos, neg);
    if (endptr) *endptr = (char *)number.end;
    if (number.overflow) errno = ERANGE;
    return number;
}

long strtol(const char *s, char **endptr, int base)
{
    CG_Number n = cg_convert(s, endptr, base, (unsigned long long)LONG_MAX,
                             (unsigned long long)LONG_MAX + 1ULL);
    if (n.negative) return -(long)(n.number - (n.number != 0)) - (n.number != 0);
    return (long)n.number;
}

unsigned long strtoul(const char *s, char **endptr, int base)
{
    CG_Number n = cg_convert(s, endptr, base, (unsigned long long)ULONG_MAX,
                             (unsigned long long)ULONG_MAX);
    unsigned long result = (unsigned long)n.number;
    return (!n.overflow && n.negative) ? 0UL - result : result;
}

long long strtoll(const char *s, char **endptr, int base)
{
    CG_Number n = cg_convert(s, endptr, base, (unsigned long long)LLONG_MAX,
                             (unsigned long long)LLONG_MAX + 1ULL);
    if (n.negative) return -(long long)(n.number - (n.number != 0)) - (n.number != 0);
    return (long long)n.number;
}

unsigned long long strtoull(const char *s, char **endptr, int base)
{
    CG_Number n = cg_convert(s, endptr, base, ULLONG_MAX, ULLONG_MAX);
    return (!n.overflow && n.negative) ? 0ULL - n.number : n.number;
}

int atoi(const char *s)             { return (int)strtol(s, NULL, 10); }
long atol(const char *s)            { return strtol(s, NULL, 10); }
long long atoll(const char *s)      { return strtoll(s, NULL, 10); }
int abs(int n)                      { return n < 0 ? -n : n; }
long labs(long n)                   { return n < 0 ? -n : n; }
long long llabs(long long n)        { return n < 0 ? -n : n; }

static void cg_swap(unsigned char *a, unsigned char *b, size_t width)
{
    for (size_t i = 0; i < width; ++i) {
        unsigned char temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

static void cg_sift(unsigned char *base, size_t root, size_t end,
                    size_t width, int (*cmp)(const void *, const void *))
{
    while (end > 0 && root <= (end - 1u) / 2u) {
        size_t child = root * 2u + 1u;
        size_t swap_index = root;
        if (cmp(base + swap_index * width, base + child * width) < 0)
            swap_index = child;
        if (child < end &&
            cmp(base + swap_index * width, base + (child + 1u) * width) < 0)
            swap_index = child + 1u;
        if (swap_index == root) return;
        cg_swap(base + root * width, base + swap_index * width, width);
        root = swap_index;
    }
}

void qsort(void *base, size_t count, size_t width,
           int (*cmp)(const void *, const void *))
{
    if (count < 2 || !width || count > SIZE_MAX / width) return;
    unsigned char *array = (unsigned char *)base;
    for (size_t start = count / 2u; start > 0; --start)
        cg_sift(array, start - 1u, count - 1u, width, cmp);
    for (size_t end = count - 1u; end > 0; --end) {
        cg_swap(array, array + end * width, width);
        cg_sift(array, 0, end - 1u, width, cmp);
    }
}

void *bsearch(const void *key, const void *base, size_t count, size_t width,
              int (*cmp)(const void *, const void *))
{
    if (!width || count > SIZE_MAX / width) return NULL;
    const unsigned char *array = (const unsigned char *)base;
    size_t low = 0, high = count;
    while (low < high) {
        size_t mid = low + (high - low) / 2u;
        int result = cmp(key, array + mid * width);
        if (!result) return (void *)(array + mid * width);
        if (result > 0) low = mid + 1u;
        else high = mid;
    }
    return NULL;
}

/* Per-applet pseudo-random sequence; not cryptographic. */
static uint32_t cg_rng_state = 1u;
void srand(unsigned seed) { cg_rng_state = seed; }
int rand(void)
{
    cg_rng_state = cg_rng_state * UINT32_C(1103515245) + UINT32_C(12345);
    return (int)((cg_rng_state >> 1) & (uint32_t)RAND_MAX);
}
