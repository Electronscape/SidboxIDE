/* CGARM Phase 4: portable PIC elementary functions for ordinary applet math.
 * No libm, libgcc, Newlib, static TLS, or firmware dependency.
 * Trigonometric range reduction is accurate for ordinary-sized angles
 * (recommended |x| <= 1e6 radians). See README for limitations.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_math_extra.c requires SIDBOX_APPLET_V2"
#endif
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <errno.h>

#ifdef log2
#undef log2
#endif

#define CG_PI 3.14159265358979323846264338327950288
#define CG_HALFPI 1.57079632679489661923132169163975144
#define CG_PI4 0.78539816339744830961566084581987572
#define CG_LN2 0.69314718055994530941723212145817657
#define CG_LN2_LO 2.319046813846299558417771e-17
#define CG_PI2_LO 6.123233995736766035868820e-17

static double cg_nan(void) { volatile double z = 0.0; return z / z; }
static double cg_inf(void) { volatile double z = 0.0; return 1.0 / z; }
static int cg_isnan(double x) { return x != x; }
static int cg_isinf(double x) { return x > DBL_MAX || x < -DBL_MAX; }
static double cg_abs(double x) { return x < 0.0 ? -x : x; }
static int cg_signbit(double x) { union { double d; uint64_t u; } v; v.d=x; return (int)(v.u >> 63); }

/* Polynomial evaluation after folding to [-pi/4, pi/4]. */
static double cg_sin_small(double x)
{
    double z = x * x;
    return x + x*z*(-1.66666666666666657415e-1 + z*(8.33333333333333287074e-3 +
          z*(-1.98412698412698412530e-4 + z*(2.75573192239858925112e-6 +
          z*(-2.50521083854417187751e-8 + z*(1.60590438368216145994e-10 +
          z*(-7.64716373181981647590e-13 + z*2.81145725434552076320e-15)))))));
}
static double cg_cos_small(double x)
{
    double z = x*x;
    return 1.0 + z*(-0.5 + z*(4.16666666666666643537e-2 +
          z*(-1.38888888888888729937e-3 + z*(2.48015873015872990167e-5 +
          z*(-2.75573192239858906526e-7 + z*(2.08767569878680989792e-9 +
          z*(-1.14707455977297247139e-11 + z*4.77947733238738529744e-14)))))));
}
/* Never convert a huge double to an overflowing integer. */
static int cg_reduce(double x, double *small)
{
    if (cg_isnan(x) || cg_isinf(x) || cg_abs(x) > 1000000.0) {
        errno = EDOM;
        *small = cg_nan();
        return -1;
    }
    int n = (int)(x / CG_HALFPI + (x >= 0.0 ? 0.5 : -0.5));
    *small = (x - (double)n * CG_HALFPI) - (double)n * CG_PI2_LO;
    return n & 3;
}
static void cgarm_sincos(double x, double *out_sin, double *out_cos)
{
    double r, s, c;
    int q = cg_reduce(x, &r);
    if (q < 0) { if (out_sin) *out_sin=r; if (out_cos) *out_cos=r; return; }
    s = cg_sin_small(r); c = cg_cos_small(r);
    if (q == 1) { double t=s; s=c; c=-t; }
    else if (q == 2) { s=-s; c=-c; }
    else if (q == 3) { double t=s; s=-c; c=t; }
    if (out_sin) *out_sin=s;
    if (out_cos) *out_cos=c;
}
double sin(double x) { double s; cgarm_sincos(x, &s, 0); return s; }
double cos(double x) { double c; cgarm_sincos(x, 0, &c); return c; }
double tan(double x) { double s,c; cgarm_sincos(x,&s,&c); return s/c; }
float sinf(float x) { return (float)sin((double)x); }
float cosf(float x) { return (float)cos((double)x); }
float tanf(float x) { return (float)tan((double)x); }

/* atan Taylor on |z| <= sqrt(2)-1, with argument transformations. */
static double cg_atan_core(double z)
{
    double zz=z*z, term=z, sum=z;
    for (int k=3; k<=41; k+=2) {
        term *= -zz;
        sum += term/(double)k;
    }
    return sum;
}
double atan(double x)
{
    if (cg_isnan(x)) return x;
    if (cg_isinf(x)) return x < 0 ? -CG_HALFPI : CG_HALFPI;
    int neg=x<0.0;
    if (neg) x=-x;
    double result;
    if (x > 2.414213562373095) result=CG_HALFPI-cg_atan_core(1.0/x);
    else if (x > 0.414213562373095) result=CG_PI4+cg_atan_core((x-1.0)/(x+1.0));
    else result=cg_atan_core(x);
    return neg ? -result : result;
}
float atanf(float x) { return (float)atan(x); }
double atan2(double y, double x)
{
    if (cg_isnan(x) || cg_isnan(y)) return cg_nan();
    if (x > 0.0) return atan(y/x);
    if (x < 0.0) return (y < 0.0 || (y==0.0 && cg_signbit(y))) ? atan(y/x)-CG_PI : atan(y/x)+CG_PI;
    if (y > 0.0) return CG_HALFPI;
    if (y < 0.0) return -CG_HALFPI;
    return 0.0;
}
float atan2f(float y,float x) { return (float)atan2((double)y,(double)x); }
double asin(double x)
{
    if (cg_isnan(x)) return x;
    if (x < -1.0 || x > 1.0) { errno=EDOM; return cg_nan(); }
    if (x==1.0) return CG_HALFPI;
    if (x==-1.0) return -CG_HALFPI;
    return atan2(x, sqrt((1.0-x)*(1.0+x)));
}
double acos(double x)
{
    if (cg_isnan(x)) return x;
    if (x < -1.0 || x > 1.0) { errno=EDOM; return cg_nan(); }
    if (x==1.0) return 0.0;
    if (x==-1.0) return CG_PI;
    return atan2(sqrt((1.0-x)*(1.0+x)),x);
}
float asinf(float x) { return (float)asin(x); }
float acosf(float x) { return (float)acos(x); }

/* 2^n constructed using IEEE-754 bits. Correct for normal/subnormal powers. */
static double cg_two_to(int n)
{
    union { double d; uint64_t u; } a;
    if (n>1023) return cg_inf();
    if (n<-1074) return 0.0;
    if (n>=-1022) a.u=(uint64_t)(n+1023)<<52;
    else a.u=UINT64_C(1) << (n+1074);
    return a.d;
}
double scalbn(double x,int n)
{
    if (x==0.0 || cg_isnan(x) || cg_isinf(x)) return x;
    /* Avoid spurious intermediate underflow/overflow. */
    while (n>900) { x *= cg_two_to(900); n-=900; if(cg_isinf(x)) return x; }
    while (n < -900) { x *= cg_two_to(-900); n+=900; if(x==0.0) return x; }
    return x * cg_two_to(n);
}
double ldexp(double x,int n) { return scalbn(x,n); }
float scalbnf(float x,int n) { return (float)scalbn((double)x,n); }
float ldexpf(float x,int n) { return (float)scalbn((double)x,n); }

double exp(double x)
{
    if (cg_isnan(x)) return x;
    if (x > 709.78271289338397) { errno=ERANGE; return cg_inf(); }
    if (x < -745.1332191019411) { errno=ERANGE; return 0.0; }
    int n=(int)(x/CG_LN2 + (x>=0 ? 0.5 : -0.5));
    double r=(x - n*CG_LN2) - n*CG_LN2_LO;
    double sum=1.0, term=1.0;
    for(int i=1;i<=19;++i) { term *= r/(double)i; sum += term; }
    return scalbn(sum,n);
}
float expf(float x) { return (float)exp((double)x); }

double log(double x)
{
    if (cg_isnan(x)) return x;
    if (x < 0.0) { errno=EDOM; return cg_nan(); }
    if (x == 0.0) { errno=ERANGE; return -cg_inf(); }
    if (cg_isinf(x)) return x;
    union { double d; uint64_t u; } a;
    a.d=x;
    int k;
    if ((a.u>>52 & 2047u)==0) { x *= 4503599627370496.0; a.d=x; k=-52; }
    else k=0;
    k += (int)((a.u>>52)&2047u)-1023;
    a.u=(a.u & UINT64_C(0x000fffffffffffff)) | UINT64_C(0x3ff0000000000000);
    double m=a.d;
    if (m>1.4142135623730951) { m*=0.5; ++k; }
    double z=(m-1.0)/(m+1.0), z2=z*z, term=z, sum=z;
    for(int i=3;i<=29;i+=2) { term *= z2; sum += term/(double)i; }
    return 2.0*sum + k*CG_LN2;
}
double log10(double x) { return log(x)*0.43429448190325182765; }
double log2(double x) { return log(x)*1.4426950408889634074; }
float logf(float x) { return (float)log((double)x); }
float log10f(float x) { return (float)log10((double)x); }
float log2f(float x) { return (float)log2((double)x); }

double pow(double x,double y)
{
    if (y == 0.0 || x == 1.0) return 1.0;
    if (cg_isnan(x) || cg_isnan(y)) return cg_nan();
    if (x == 0.0) {
        if (y<0.0) { errno=ERANGE; return cg_inf(); }
        return 0.0;
    }
    /* Exact integer powers through squaring, including negative bases. */
    if (trunc(y)==y && y>=-1024.0 && y<=1024.0) {
        int n=(int)y;
        unsigned count=(unsigned)(n<0 ? -n : n);
        double result=1.0, factor=x;
        while(count) {
            if(count&1u) result*=factor;
            count>>=1;
            if(count) factor*=factor;
        }
        return n<0 ? 1.0/result : result;
    }
    if (x<0.0) {
        if (trunc(y)!=y) { errno=EDOM; return cg_nan(); }
        double result=exp(y*log(-x));
        return trunc(y*0.5)==y*0.5 ? result : -result;
    }
    return exp(y*log(x));
}
float powf(float x,float y) { return (float)pow((double)x,(double)y); }

double hypot(double x,double y)
{
    x=cg_abs(x); y=cg_abs(y);
    if(cg_isinf(x) || cg_isinf(y)) return cg_inf();
    if(cg_isnan(x) || cg_isnan(y)) return cg_nan();
    if(x<y) { double t=x; x=y; y=t; }
    if(x==0.0) return 0.0;
    return x*sqrt(1.0+(y/x)*(y/x));
}
float hypotf(float x,float y) { return (float)hypot(x,y); }
double fmin(double x,double y) { if(cg_isnan(x)) return y; if(cg_isnan(y)) return x; return x<y ? x : y; }
double fmax(double x,double y) { if(cg_isnan(x)) return y; if(cg_isnan(y)) return x; return x>y ? x : y; }
float fminf(float x,float y) { return (float)fmin(x,y); }
float fmaxf(float x,float y) { return (float)fmax(x,y); }

/* Remaining useful C99 math primitives. */
double fmod(double x,double y)
{
    if(cg_isnan(x)||cg_isnan(y)||cg_isinf(x)||y==0.0) {
        errno=EDOM; return cg_nan();
    }
    if(cg_isinf(y)) return x;
    double ax=cg_abs(x), ay=cg_abs(y);
    /* Binary reduction avoids an overflowing integer quotient. */
    while(ax>=ay) {
        double t=ay;
        while(t<=ax*0.5 && t < DBL_MAX*0.5) t*=2.0;
        ax-=t;
    }
    return x<0.0 ? -ax : (x==0.0 ? x : ax);
}
float fmodf(float x,float y) { return (float)fmod(x,y); }
double modf(double x,double *whole)
{
    if(!whole) { errno=EINVAL; return cg_nan(); }
    if(cg_isnan(x)) { *whole=x; return x; }
    if(cg_isinf(x)) { *whole=x; return x<0.0 ? -0.0 : 0.0; }
    *whole=trunc(x);
    return x-*whole;
}
float modff(float x,float *whole)
{
    if(!whole) { errno=EINVAL; return (float)cg_nan(); }
    double i, frac=modf((double)x,&i); *whole=(float)i;
    return (float)frac;
}
double sinh(double x) { return 0.5*(exp(x)-exp(-x)); }
double cosh(double x) { return 0.5*(exp(x)+exp(-x)); }
double tanh(double x)
{
    if(x>20.0) return 1.0;
    if(x< -20.0) return -1.0;
    double v=exp(2.0*x);
    return (v-1.0)/(v+1.0);
}
float sinhf(float x) { return (float)sinh((double)x); }
float coshf(float x) { return (float)cosh((double)x); }
float tanhf(float x) { return (float)tanh((double)x); }
