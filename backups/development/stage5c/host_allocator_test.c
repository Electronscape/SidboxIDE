#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>

void *sb_malloc(size_t);
void sb_free(void *);
void *sb_calloc(size_t, size_t);
void *sb_realloc(void *, size_t);

static union { uint64_t align; unsigned char space[16384]; } area;
static size_t cursor;

void *_sbrk(ptrdiff_t delta)
{
    if (delta < 0 || (size_t)delta > sizeof(area.space) - cursor) {
        errno = ENOMEM;
        return (void *)-1;
    }
    void *p = area.space + cursor;
    cursor += (size_t)delta;
    return p;
}

int main(void)
{
    unsigned char *a = sb_malloc(96);
    unsigned char *b = sb_malloc(192);
    assert(a && b && (uintptr_t)a % 8 == 0 && (uintptr_t)b % 8 == 0);
    for (size_t i=0; i<96; ++i) a[i]=(unsigned char)(i+9);
    for (size_t i=0; i<192; ++i) b[i]=(unsigned char)(i+31);
    unsigned char *grown=sb_realloc(b,600);
    assert(grown);
    for (size_t i=0; i<192; ++i) assert(grown[i]==(unsigned char)(i+31));
    unsigned char *z=sb_calloc(24,4);
    assert(z);
    for (size_t i=0; i<96; ++i) assert(z[i]==0);
    assert(sb_calloc(SIZE_MAX, 2)==NULL);
    sb_free(z);
    unsigned char *reuse=sb_malloc(32);
    assert(reuse==z);
    void *pressure[50];
    size_t count=0;
    while (count<50 && (pressure[count]=sb_malloc(384))) ++count;
    assert(count>0 && sb_malloc(20480)==NULL);
    for (size_t i=0;i<96;++i) assert(a[i]==(unsigned char)(i+9));
    for (size_t i=0;i<count;++i) sb_free(pressure[i]);
    assert(sb_malloc(1024)!=NULL); // coalescing adjacent freed blocks
    sb_free(grown);
    sb_free(reuse);
    sb_free(a);
    puts("PASS: native allocator malloc/free/calloc/realloc, reuse, overflow and coalescing");
    return 0;
}
