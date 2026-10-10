/* CGARM Phase 3 - fundamental floating-point operations for Cortex-M7.
 * PIC, freestanding; no libm/Newlib calls. Does not claim full libm coverage.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_math.c requires SIDBOX_APPLET_V2"
#endif
#include <stdint.h>
#include <math.h>


#ifndef SIDBOX_APPLET_V2
#error "Phase 11 maths require SIDBOX_APPLET_V2"
#endif
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <errno.h>
#ifdef frexp
#undef frexp
#endif
#ifdef frexpf
#undef frexpf
#endif
#ifdef cbrt
#undef cbrt
#endif
#ifdef cbrtf
#undef cbrtf
#endif
#ifdef log1p
#undef log1p
#endif
#ifdef expm1
#undef expm1
#endif


double frexp(double x, int *exponent)
{
    union { double d; uint64_t bits; } b;
    b.d = x;
    unsigned field = (unsigned)((b.bits >> 52) & 2047u);
    if (exponent) *exponent = 0;
    if (!field && (b.bits & UINT64_C(0x000fffffffffffff)) == 0) return x;
    if (field == 2047u) return x;
    int correction = 0;
    if (!field) {
        b.d *= 0x1p54;
        field = (unsigned)((b.bits >> 52) & 2047u);
        correction = -54;
    }
    if (exponent) *exponent = (int)field - 1022 + correction;
    b.bits = (b.bits & UINT64_C(0x800fffffffffffff)) | UINT64_C(0x3fe0000000000000);
    return b.d;
}

float frexpf(float x, int *exponent)
{
    union { float f; uint32_t bits; } b;
    b.f = x;
    unsigned field = (b.bits >> 23) & 255u;
    if (exponent) *exponent = 0;
    if (!field && (b.bits & UINT32_C(0x007fffff)) == 0) return x;
    if (field == 255u) return x;
    int correction = 0;
    if (!field) {
        b.f *= 0x1p25f;
        field = (b.bits >> 23) & 255u;
        correction = -25;
    }
    if (exponent) *exponent = (int)field - 126 + correction;
    b.bits = (b.bits & UINT32_C(0x807fffff)) | UINT32_C(0x3f000000);
    return b.f;
}

double cbrt(double x)
{
    if (x == 0.0 || x != x || x > DBL_MAX || x < -DBL_MAX) return x;
    int negative = x < 0.0;
    double v = negative ? -x : x;
    int e = 0;
    double m = frexp(v, &e);
    int shift = e / 3;
    int remainder = e - shift * 3;
    if (remainder < 0) { --shift; remainder += 3; }
    double y = pow(scalbn(m, remainder), 1.0 / 3.0);
    double target = scalbn(m, remainder);
    for (int i = 0; i < 4; ++i) y = (2.0*y + target/(y*y)) / 3.0;
    double answer = scalbn(y, shift);
    return negative ? -answer : answer;
}
float cbrtf(float x) { return (float)cbrt((double)x); }

double expm1(double x)
{
    if (x != x || x > DBL_MAX || x < -DBL_MAX) return exp(x);
    double a = x < 0.0 ? -x : x;
    if (a >= 0.125) return exp(x) - 1.0;
    double term = x, result = x;
    for (int n = 2; n <= 18; ++n) {
        term *= x / (double)n;
        result += term;
    }
    return result;
}
float expm1f(float x) { return (float)expm1((double)x); }

double log1p(double x)
{
    if (x != x || x > DBL_MAX || x < -DBL_MAX) return log(1.0 + x);
    if (x <= -1.0) return log(1.0 + x); /* preserves EDOM/ERANGE */
        double a = x < 0.0 ? -x : x;
    if (a >= 0.125) return log(1.0 + x);
    /* Alternating series with |x| <= 0.125, 20 terms gives good precision. */
    double term = x, result = x;
    for (int n = 2; n <= 20; ++n) {
        term *= -x;
        result += term / (double)n;
    }
    return result;
}
float log1pf(float x) { return (float)log1p((double)x); }


static double cg_trunc_d(double x)
{
    union { double d; uint64_t u; } v;
    v.d = x;
    int exponent = (int)((v.u >> 52) & 0x7ffu) - 1023;
    if (exponent < 0) {
        v.u &= UINT64_C(0x8000000000000000);
    } else if (exponent < 52) {
        v.u &= ~((UINT64_C(1) << (52 - exponent)) - 1u);
    }
    return v.d;
}

static float cg_trunc_f(float x)
{
    union { float f; uint32_t u; } v;
    v.f = x;
    int exponent = (int)((v.u >> 23) & 0xffu) - 127;
    if (exponent < 0) {
        v.u &= UINT32_C(0x80000000);
    } else if (exponent < 23) {
        v.u &= ~((UINT32_C(1) << (23 - exponent)) - 1u);
    }
    return v.f;
}

double fabs(double x)
{
    union { double d; uint64_t u; } v;
    v.d = x;
    v.u &= UINT64_C(0x7fffffffffffffff);
    return v.d;
}

float fabsf(float x)
{
    union { float f; uint32_t u; } v;
    v.f = x;
    v.u &= UINT32_C(0x7fffffff);
    return v.f;
}

double copysign(double x, double y)
{
    union { double d; uint64_t u; } a, b;
    a.d = x;
    b.d = y;
    a.u = (a.u & UINT64_C(0x7fffffffffffffff)) |
          (b.u & UINT64_C(0x8000000000000000));
    return a.d;
}

float copysignf(float x, float y)
{
    union { float f; uint32_t u; } a, b;
    a.f = x;
    b.f = y;
    a.u = (a.u & UINT32_C(0x7fffffff)) | (b.u & UINT32_C(0x80000000));
    return a.f;
}

double trunc(double x) { return cg_trunc_d(x); }
float truncf(float x) { return cg_trunc_f(x); }

double floor(double x)
{
    double t = cg_trunc_d(x);
    return t > x ? t - 1.0 : t;
}

float floorf(float x)
{
    float t = cg_trunc_f(x);
    return t > x ? t - 1.0f : t;
}

double ceil(double x)
{
    double t = cg_trunc_d(x);
    return t < x ? t + 1.0 : t;
}

float ceilf(float x)
{
    float t = cg_trunc_f(x);
    return t < x ? t + 1.0f : t;
}

double round(double x)
{
    double t = cg_trunc_d(x);
    double frac = x - t;
    if (frac >= 0.5) return t + 1.0;
    if (frac <= -0.5) return t - 1.0;
    return t;
}

float roundf(float x)
{
    float t = cg_trunc_f(x);
    float frac = x - t;
    if (frac >= 0.5f) return t + 1.0f;
    if (frac <= -0.5f) return t - 1.0f;
    return t;
}

/* Hardware FPv5-D16 has native square-root instructions. */
double sqrt(double x)
{
    double result;
#if defined(__arm__) && defined(__ARM_FP)
    __asm__ volatile ("vsqrt.f64 %P0, %P1" : "=w"(result) : "w"(x));
#else
    result = __builtin_sqrt(x); /* Native host tests only. */
#endif
    return result;
}

float sqrtf(float x)
{
    float result;
#if defined(__arm__) && defined(__ARM_FP)
    __asm__ volatile ("vsqrt.f32 %0, %1" : "=t"(result) : "t"(x));
#else
    result = __builtin_sqrtf(x); /* Native host tests only. */
#endif
    return result;
}
