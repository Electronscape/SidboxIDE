/* CGARM Phase 4: decimal <-> floating-point and simple stdlib arithmetic.
 * Freestanding PIC, applet-local errno. No Newlib/libm dependencies except
 * CGARM's own exp/log equivalents; no firmware API modifications.
 * Decimal parser deliberately does NOT accept hexadecimal floating literals.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_stdlib_extra.c requires SIDBOX_APPLET_V2"
#endif
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <errno.h>
#include <math.h>

static int cg_space(int c) { return c==32 || (c>=9 && c<=13); }
static int cg_digit(int c) { return c>='0' && c<='9'; }
static int cg_same(int c,int expected) {
    return c==expected || (expected>='a' && expected<='z' && c==expected-'a'+'A');
}
static double cg_inf(void) { volatile double z=0.0; return 1.0/z; }
static double cg_nan(void) { volatile double z=0.0; return z/z; }
static double cg_scale10(double x, int e)
{
    /* Scale in chunks: 5e-324 and 1e308 must not overflow an intermediary. */
    while(e>300) { x *= 1e300; e-=300; }
    while(e< -300) { x /= 1e300; e+=300; }
    unsigned n=(unsigned)(e<0 ? -e : e);
    double scale=1.0, base=10.0;
    while(n) {
        if(n&1u) scale *= base;
        n>>=1;
        if(n) base *= base;
    }
    return e<0 ? x/scale : x*scale;
}
double strtod(const char *text,char **endptr)
{
    const char *original=text, *p=text;
    while(cg_space((unsigned char)*p)) ++p;
    int neg=0;
    if(*p=='+' || *p=='-') { neg=(*p=='-'); ++p; }
    if(cg_same(p[0],'i') && cg_same(p[1],'n') && cg_same(p[2],'f')) {
        p+=3;
        if(cg_same(p[0],'i') && cg_same(p[1],'n') && cg_same(p[2],'i') &&
           cg_same(p[3],'t') && cg_same(p[4],'y')) p+=5;
        if(endptr) *endptr=(char *)p;
        return neg ? -cg_inf() : cg_inf();
    }
    if(cg_same(p[0],'n') && cg_same(p[1],'a') && cg_same(p[2],'n')) {
        p+=3;
        if(endptr) *endptr=(char *)p;
        double v=cg_nan(); return neg ? -v : v;
    }
    double result=0.0;
    int significant=0, decimal=0, saw_digit=0, exponent10=0;
    while(*p) {
        if (*p=='.' && !decimal) { decimal=1; ++p; continue; }
        if (!cg_digit((unsigned char)*p)) break;
        int d=*p++-'0'; saw_digit=1;
        if(significant==0 && d==0) {
            if(decimal && exponent10 > -100000) --exponent10;
            continue;
        }
        if(significant<17) {
            result=result*10.0+(double)d;
            ++significant;
            if(decimal && exponent10>-100000) --exponent10;
        } else if(!decimal && exponent10<100000) ++exponent10;
    }
    if(!saw_digit) {
        if(endptr) *endptr=(char *)original;
        return 0.0;
    }
    if(*p=='e' || *p=='E') {
        const char *start=p;
        ++p;
        int eneg=0, exp=0;
        if(*p=='+' || *p=='-') { eneg=(*p=='-'); ++p; }
        if(!cg_digit((unsigned char)*p)) p=start;
        else {
            while(cg_digit((unsigned char)*p)) {
                int d=*p++-'0';
                if(exp<10000) exp=exp*10+d;
            }
            if(eneg) exponent10 -= exp;
            else exponent10 += exp;
        }
    }
    if(endptr) *endptr=(char *)p;
    if(result==0.0) return neg ? -0.0 : 0.0;
    /* Avoid the intermediate 10^308 overflow in a 1e-308 conversion. */
    if(exponent10 > 1000) { errno=ERANGE; return neg ? -cg_inf() : cg_inf(); }
    if(exponent10 < -1000) { errno=ERANGE; return neg ? -0.0 : 0.0; }
    double v=cg_scale10(result,exponent10);
    if(v>DBL_MAX || v==0.0) errno=ERANGE;
    return neg ? -v : v;
}
float strtof(const char *text,char **endptr)
{
    double value=strtod(text,endptr);
    if (value > FLT_MAX || value < -FLT_MAX) errno=ERANGE;
    float f=(float)value;
    if (f==0.0f && value!=0.0) errno=ERANGE;
    return f;
}
double atof(const char *text) { return strtod(text,(char **)0); }
div_t div(int num,int den) { div_t v={num/den,num%den}; return v; }
ldiv_t ldiv(long num,long den) { ldiv_t v={num/den,num%den}; return v; }
