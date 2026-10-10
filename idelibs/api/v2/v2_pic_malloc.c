/* CoderGirl V2 experimental applet-local heap allocator.
 *
 * Small first-fit allocator over V2 SDK _sbrk(). Source is compiled with
 * -fPIC and linked into EACH applet. No Newlib allocator or global _impure_ptr.
 *
 * Experimental! This supplies only malloc/free/realloc/calloc, not full libc.
 * The applet owns its allocator state and must never pass allocation pointers
 * between applets (or into a firmware API that later frees them).
 *
 * Caller must initialize the bounded SDK V2 heap before the first allocation.
 */
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

/* Applet-local errno; Newlib headers normally expose errno via __errno().
 * The allocator deliberately never imports Newlib's _impure_ptr. */
#undef errno
int errno = 0;
int *__errno(void) { return &errno; }

extern void *_sbrk(ptrdiff_t incr);

typedef struct MemBlock {
    struct MemBlock *next;
    size_t capacity;
    unsigned used;
} MemBlock;

static MemBlock *first_block;
static MemBlock *last_block;

#define MEM_ALIGN 8u
#define BLOCK_HEADER ((sizeof(MemBlock) + MEM_ALIGN - 1u) & ~(size_t)(MEM_ALIGN - 1u))

static int size_aligned(size_t original, size_t *aligned_size)
{
    if (original == 0) original = 1;
    if (original > SIZE_MAX - (MEM_ALIGN - 1u)) return 0;
    *aligned_size = (original + MEM_ALIGN - 1u) & ~(size_t)(MEM_ALIGN - 1u);
    return 1;
}

static int adjacent(const MemBlock *left, const MemBlock *right)
{
    return (uintptr_t)left + BLOCK_HEADER + left->capacity == (uintptr_t)right;
}

static void coalesce(void)
{
    MemBlock *b = first_block;
    while (b && b->next) {
        MemBlock *next = b->next;
        if (!b->used && !next->used && adjacent(b, next)) {
            b->capacity += BLOCK_HEADER + next->capacity;
            b->next = next->next;
            if (last_block == next) last_block = b;
        } else {
            b = b->next;
        }
    }
}

static void split_free_block(MemBlock *b, size_t requested)
{
    if (b->capacity - requested < BLOCK_HEADER + MEM_ALIGN) return;
    MemBlock *extra = (MemBlock *)((uint8_t *)b + BLOCK_HEADER + requested);
    extra->capacity = b->capacity - requested - BLOCK_HEADER;
    extra->used = 0;
    extra->next = b->next;
    if (last_block == b) last_block = extra;
    b->capacity = requested;
    b->next = extra;
}

void *malloc(size_t size)
{
    size_t wanted;
    if (!size_aligned(size, &wanted) || wanted > (size_t)PTRDIFF_MAX - BLOCK_HEADER) {
        errno = ENOMEM;
        return NULL;
    }
    for (MemBlock *b = first_block; b; b = b->next) {
        if (!b->used && b->capacity >= wanted) {
            split_free_block(b, wanted);
            b->used = 1;
            return (uint8_t *)b + BLOCK_HEADER;
        }
    }
    MemBlock *b = (MemBlock *)_sbrk((ptrdiff_t)(BLOCK_HEADER + wanted));
    if (b == (void *)-1) {
        errno = ENOMEM;
        return NULL;
    }
    b->capacity = wanted;
    b->used = 1;
    b->next = NULL;
    if (last_block) last_block->next = b;
    else first_block = b;
    last_block = b;
    return (uint8_t *)b + BLOCK_HEADER;
}

void free(void *ptr)
{
    if (!ptr) return;
    /* Like ordinary libc, passing a pointer not obtained from malloc is UB. */
    MemBlock *b = (MemBlock *)((uint8_t *)ptr - BLOCK_HEADER);
    b->used = 0;
    coalesce();
}

void *calloc(size_t count, size_t size)
{
    if (size && count > SIZE_MAX / size) {
        errno = ENOMEM;
        return NULL;
    }
    size_t bytes = count * size;
    uint8_t *result = (uint8_t *)malloc(bytes);
    if (!result) return NULL;
    for (size_t i = 0; i < bytes; ++i) result[i] = 0;
    return result;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr) return malloc(size);
    if (size == 0) { free(ptr); return NULL; }
    size_t wanted;
    if (!size_aligned(size, &wanted)) { errno = ENOMEM; return NULL; }
    MemBlock *b = (MemBlock *)((uint8_t *)ptr - BLOCK_HEADER);
    if (wanted <= b->capacity) {
        split_free_block(b, wanted);
        return ptr;
    }
    void *replacement = malloc(size);
    if (!replacement) return NULL; /* old buffer must remain valid */
    uint8_t *from = (uint8_t *)ptr;
    uint8_t *to = (uint8_t *)replacement;
    for (size_t i = 0; i < b->capacity; ++i) to[i] = from[i];
    free(ptr);
    return replacement;
}
