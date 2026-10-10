/* CGARM: stdio compatibility for seekable SBOS FILE streams.
 * Uses the standard CGARM fgetc/ungetc/fseek interface: no firmware changes.
 * vfscanf/fscanf implement common ISO C conversions. Hexadecimal floating
 * input, wide-character conversions and locale are not yet supported.
 * Numeric fields use a bounded buffer matching CGARM's vsscanf limit.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_stdio.c is for CGARM applets only"
#endif
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#ifdef getc
#undef getc
#endif
#ifdef putc
#undef putc
#endif

#define CG_SCAN_LIMIT 190u

enum { CG_S_NONE, CG_S_HH, CG_S_H, CG_S_L, CG_S_LL, CG_S_J, CG_S_Z, CG_S_T, CG_S_LDOUBLE };

static int cg_whitespace(int c) { return c==' ' || (c>=9 && c<=13); }
static int cg_digit(int c) { return c>='0' && c<='9'; }
static int cg_hex(int c) { return cg_digit(c) || (c>='a' && c<='f') || (c>='A' && c<='F'); }

static int cg_num_candidate(int ch, char spec)
{
    if (ch=='+' || ch=='-') return 1;
    if (spec=='d' || spec=='u') return cg_digit(ch);
    if (spec=='o') return ch>='0' && ch<='7';
    if (spec=='x' || spec=='X' || spec=='i' || spec=='p')
        return cg_hex(ch) || ch=='x' || ch=='X';
    return cg_digit(ch) || ch=='.' || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z');
}

static void cg_store_n(va_list *ap, int length, long consumed)
{
    switch (length) {
    case CG_S_HH: *va_arg(*ap,signed char *)=(signed char)consumed; break;
    case CG_S_H: *va_arg(*ap,short *)=(short)consumed; break;
    case CG_S_L: *va_arg(*ap,long *)=consumed; break;
    case CG_S_LL: *va_arg(*ap,long long *)=(long long)consumed; break;
    case CG_S_J: *va_arg(*ap,intmax_t *)=(intmax_t)consumed; break;
    case CG_S_Z: case CG_S_T: *va_arg(*ap,ptrdiff_t *)=(ptrdiff_t)consumed; break;
    default: *va_arg(*ap,int *)=(int)consumed; break;
    }
}

static const char *cg_scanset(const char *p, unsigned char set[256])
{
    for (int i=0;i<256;++i) set[i]=0;
    int inverse=*p=='^';
    if (inverse) ++p;
    int previous=-1;
    if (*p==']') { set[']']=1; previous=']'; ++p; }
    while (*p && *p!=']') {
        unsigned char c=(unsigned char)*p++;
        if (c=='-' && previous>=0 && *p && *p!=']') {
            unsigned char end=(unsigned char)*p++;
            if (end >= previous) {
                for (int j=previous; j<=end; ++j) set[j]=1;
            } else { set['-']=1; set[end]=1; }
            previous=end;
        } else { set[c]=1; previous=c; }
    }
    if (*p!=']') return NULL;
    if (inverse) for (int i=0;i<256;++i) set[i]=(unsigned char)!set[i];
    return p+1;
}

/* sscanf already has the established CGARM type-correct assignment logic.
 * For numeric input we give it exactly one conversion plus %n to determine
 * the consumed prefix. SBOS streams are seekable, so unread suffix bytes are
 * restored by fseek, without needing more than one byte of pushback.
 */
static int cg_numeric_assign(const char *value, const char *format, char spec,
                             int length, int suppress, va_list *ap, int *used)
{
    *used=-1;
    if (suppress) { (void)sscanf(value, format, used); return *used >= 0; }
#define CG_SCAN_TO(type) do { \
    type *dest = va_arg(*ap, type *); \
    return sscanf(value,format,dest,used)==1 && *used>=0; \
} while (0)
    if (spec=='p') CG_SCAN_TO(void *);
    if (spec=='f' || spec=='F' || spec=='e' || spec=='E' || spec=='g' || spec=='G') {
        if (length==CG_S_LDOUBLE) CG_SCAN_TO(long double);
        if (length==CG_S_L) CG_SCAN_TO(double);
        CG_SCAN_TO(float);
    }
    if (spec=='d' || spec=='i') {
        switch (length) {
        case CG_S_HH: CG_SCAN_TO(signed char);
        case CG_S_H: CG_SCAN_TO(short);
        case CG_S_L: CG_SCAN_TO(long);
        case CG_S_LL: CG_SCAN_TO(long long);
        case CG_S_J: CG_SCAN_TO(intmax_t);
        case CG_S_Z: case CG_S_T: CG_SCAN_TO(ptrdiff_t);
        default: CG_SCAN_TO(int);
        }
    }
    switch (length) {
    case CG_S_HH: CG_SCAN_TO(unsigned char);
    case CG_S_H: CG_SCAN_TO(unsigned short);
    case CG_S_L: CG_SCAN_TO(unsigned long);
    case CG_S_LL: CG_SCAN_TO(unsigned long long);
    case CG_S_J: CG_SCAN_TO(uintmax_t);
    case CG_S_Z: CG_SCAN_TO(size_t);
    case CG_S_T: CG_SCAN_TO(ptrdiff_t);
    default: CG_SCAN_TO(unsigned);
    }
#undef CG_SCAN_TO
}

int vfscanf(FILE *stream, const char *format, va_list arguments)
{
    if (!format) { errno=EINVAL; return EOF; }
    va_list ap;
    va_copy(ap,arguments);
    int assigned=0;
    int input_failure=0;
    long consumed=0;
    const char *p=format;

    while (*p) {
        if (cg_whitespace((unsigned char)*p)) {
            while (cg_whitespace((unsigned char)*p)) ++p;
            int ch;
            while ((ch=fgetc(stream))!=EOF && cg_whitespace(ch)) ++consumed;
            if (ch!=EOF) ungetc(ch,stream);
            continue;
        }
        if (*p!='%' || p[1]=='%') {
            int wanted=(*p=='%') ? '%' : (unsigned char)*p;
            p += *p=='%' ? 2 : 1;
            int ch=fgetc(stream);
            if (ch != wanted) {
                if (ch==EOF) input_failure=1;
                else ungetc(ch,stream);
                break;
            }
            ++consumed;
            continue;
        }
        ++p;
        int suppress=(*p=='*');
        if (suppress) ++p;
        unsigned width=0;
        while (cg_digit((unsigned char)*p)) {
            unsigned d=(unsigned)(*p++-'0');
            width=(width>(UINT_MAX-d)/10u) ? UINT_MAX : width*10u+d;
        }
        if (!width) width=UINT_MAX;
        int length=CG_S_NONE;
        if (*p=='h') { ++p; length=(*p=='h') ? (++p,CG_S_HH) : CG_S_H; }
        else if (*p=='l') { ++p; length=(*p=='l') ? (++p,CG_S_LL) : CG_S_L; }
        else if (*p=='j') { ++p; length=CG_S_J; }
        else if (*p=='z') { ++p; length=CG_S_Z; }
        else if (*p=='t') { ++p; length=CG_S_T; }
        else if (*p=='L') { ++p; length=CG_S_LDOUBLE; }
        char spec=*p;
        if (!spec) break;
        ++p;
        if (spec=='n') {
            if (!suppress) cg_store_n(&ap,length,consumed);
            continue;
        }
        if (spec=='[' || spec=='s' || spec=='c') {
            unsigned char set[256];
            if (spec=='[') {
                const char *after=cg_scanset(p,set);
                if (!after) { errno=EINVAL; break; }
                p=after;
            }
            if (spec=='s') {
                int ch;
                while ((ch=fgetc(stream))!=EOF && cg_whitespace(ch)) ++consumed;
                if (ch!=EOF) ungetc(ch,stream);
            }
            if (spec=='c' && width==UINT_MAX) width=1;
            char *dst=suppress ? NULL : va_arg(ap,char *);
            unsigned count=0;
            while (count<width) {
                int ch=fgetc(stream);
                if (ch==EOF) { input_failure=1; break; }
                int good=(spec=='c') || (spec=='s' ? !cg_whitespace(ch) : set[(unsigned char)ch]);
                if (!good) { ungetc(ch,stream); break; }
                if (dst) dst[count]=(char)ch;
                ++count;
            }
            if ((spec=='c' && count != width) || count==0) break;
            consumed+=(long)count;
            if (dst) {
                if (spec!='c') dst[count]='\0';
                ++assigned;
            }
            continue;
        }
        if (spec!='d' && spec!='i' && spec!='u' && spec!='o' && spec!='x' && spec!='X' &&
            spec!='p' && spec!='f' && spec!='F' && spec!='e' && spec!='E' &&
            spec!='g' && spec!='G') { errno=EINVAL; break; }
        int ch;
        while ((ch=fgetc(stream))!=EOF && cg_whitespace(ch)) ++consumed;
        if (ch==EOF) { input_failure=1; break; }
        ungetc(ch,stream);
        long start=ftell(stream);
        if (start<0) break;
        char number[CG_SCAN_LIMIT+1];
        unsigned cap=width<CG_SCAN_LIMIT ? width : CG_SCAN_LIMIT;
        unsigned count=0;
        while (count<cap) {
            ch=fgetc(stream);
            if (ch==EOF) break;
            if (!cg_num_candidate(ch,spec)) { ungetc(ch,stream); break; }
            number[count++]=(char)ch;
        }
        number[count]='\0';
        char mini[32];
        unsigned k=0;
        mini[k++]='%';
        if (suppress) mini[k++]='*';
        /* Width is bounded by the field buffer, not by the destination. */
        unsigned digits=cap, divisor=1;
        while (digits/divisor>=10u) divisor*=10u;
        do { mini[k++]=(char)('0'+(digits/divisor)%10u); divisor/=10u; } while (divisor);
        switch (length) {
        case CG_S_HH: mini[k++]='h'; mini[k++]='h'; break;
        case CG_S_H: mini[k++]='h'; break;
        case CG_S_L: mini[k++]='l'; break;
        case CG_S_LL: mini[k++]='l'; mini[k++]='l'; break;
        case CG_S_J: mini[k++]='j'; break;
        case CG_S_Z: mini[k++]='z'; break;
        case CG_S_T: mini[k++]='t'; break;
        case CG_S_LDOUBLE: mini[k++]='L'; break;
        default: break;
        }
        mini[k++]=spec; mini[k++]='%'; mini[k++]='n'; mini[k]='\0';
        int used=-1;
        int valid = count>0 && cg_numeric_assign(number,mini,spec,length,suppress,&ap,&used);
        if (!valid) { (void)fseek(stream,start,SEEK_SET); if (!count) input_failure=(ch==EOF); break; }
        if (fseek(stream,start+(long)used,SEEK_SET)!=0) break;
        consumed+=used;
        if (!suppress) ++assigned;
    }
    va_end(ap);
    return (input_failure && assigned==0) ? EOF : assigned;
}

int fscanf(FILE *stream, const char *format, ...)
{
    va_list ap;
    va_start(ap,format);
    int result=vfscanf(stream,format,ap);
    va_end(ap);
    return result;
}

/* Newlib sometimes exposes these as FILE-layout-dependent macros. The CGARM
 * overlay undefines those macros, ensuring calls use opaque CGARM FILEs. */
int getc(FILE *stream) { return fgetc(stream); }
int putc(int c, FILE *stream) { return fputc(c,stream); }

void perror(const char *prefix)
{
    int saved=errno;
    if (prefix && *prefix) printf("%s: %s\n",prefix,strerror(saved));
    else printf("%s\n",strerror(saved));
    errno=saved;
}
