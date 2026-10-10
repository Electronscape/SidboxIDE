/* CGARM Phase 3 - fundamental floating-point operations for Cortex-M7.
 * PIC, freestanding; no libm/Newlib calls. Does not claim full libm coverage.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_math.c requires SIDBOX_APPLET_V2"
#endif
#include <stdint.h>
#include <math.h>

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
