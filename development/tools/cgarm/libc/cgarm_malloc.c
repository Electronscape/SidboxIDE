/* CoderGirl CGARM applet-local heap allocator.
 *
 * Bounded first-fit allocations within the V2 applet's private _sbrk() heap.
 * Validate the full adjacent-block chain in ONE pass per public operation;
 * while validating, find the exact live allocation or first suitable block.
 * This avoids repeating linear scans and merges only the freed block's
 * neighbours. Invalid/double-free pointers are never dereferenced.
 *
 * Deliberate out-of-bounds writes, aliased stale pointers after a slot is
 * reused, and external raw _sbrk() calls are outside this allocator's scope.
 */
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

/* Applet-local errno; no Newlib _impure_ptr dependency. */
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
static uintptr_t heap_first_addr;
static uintptr_t heap_end_addr;

#define MEM_ALIGN 8u
#define BLOCK_HEADER ((sizeof(MemBlock) + MEM_ALIGN - 1u) & ~(size_t)(MEM_ALIGN - 1u))

static int size_aligned(size_t original, size_t *aligned_size)
{
    if (original == 0u) original = 1u;
    if (original > SIZE_MAX - (MEM_ALIGN - 1u)) return 0;
    *aligned_size = (original + MEM_ALIGN - 1u) & ~(size_t)(MEM_ALIGN - 1u);
    return 1;
}

/* Validate the WHOLE chain before returning a candidate for modification.
 * Each next pointer is required to be the physically adjacent block, which
 * keeps corrupted pointers out of the traversal. This is a single walk,
 * instead of a validation walk plus a second search walk.
 *
 * live_ptr: optional exact allocation payload to find (must still be used).
 * wanted:   optional first-fit size to find (nonzero).
 * previous: preceding block of live_ptr for local coalescing.
 */
static int scan_heap(const void *live_ptr, size_t wanted,
                     MemBlock **live, MemBlock **previous, MemBlock **fit)
{
    if (live) *live = NULL;
    if (previous) *previous = NULL;
    if (fit) *fit = NULL;

    if (!first_block) {
        return last_block == NULL && heap_first_addr == 0u &&
               heap_end_addr == 0u;
    }
    if (!last_block || !heap_first_addr || heap_first_addr >= heap_end_addr ||
        (uintptr_t)first_block != heap_first_addr)
        return 0;

    uintptr_t cursor = heap_first_addr;
    MemBlock *b = first_block;
    MemBlock *prev = NULL;
    for (;;) {
        if ((uintptr_t)b != cursor || cursor >= heap_end_addr ||
            heap_end_addr - cursor < BLOCK_HEADER)
            return 0;

        uintptr_t remaining = heap_end_addr - cursor - BLOCK_HEADER;
        if (b->capacity < MEM_ALIGN ||
            (b->capacity & (MEM_ALIGN - 1u)) != 0u ||
            (uintptr_t)b->capacity > remaining || b->used > 1u)
            return 0;

        if (live_ptr && b->used &&
            (uintptr_t)live_ptr == cursor + BLOCK_HEADER) {
            if (live) *live = b;
            if (previous) *previous = prev;
        }
        if (fit && wanted && !*fit && !b->used && b->capacity >= wanted)
            *fit = b;

        cursor += BLOCK_HEADER + (uintptr_t)b->capacity;
        if (!b->next)
            return b == last_block && cursor == heap_end_addr;
        if ((uintptr_t)b->next != cursor || cursor >= heap_end_addr)
            return 0;
        prev = b;
        b = b->next;
    }
}

static void split_block(MemBlock *b, size_t requested)
{
    if (b->capacity - requested < BLOCK_HEADER + MEM_ALIGN) return;
    MemBlock *extra = (MemBlock *)((uint8_t *)b + BLOCK_HEADER + requested);
    extra->capacity = b->capacity - requested - BLOCK_HEADER;
    extra->used = 0u;
    extra->next = b->next;
    if (last_block == b) last_block = extra;
    b->capacity = requested;
    b->next = extra;
}

/* Merge only neighbours of the block that was freed. The full chain has
 * already been checked by scan_heap() before this function is called. */
static void coalesce_neighbours(MemBlock *b, MemBlock *prev)
{
    while (b->next && !b->next->used) {
        MemBlock *next = b->next;
        b->capacity += BLOCK_HEADER + next->capacity;
        b->next = next->next;
        if (last_block == next) last_block = b;
    }
    if (prev && !prev->used) {
        prev->capacity += BLOCK_HEADER + b->capacity;
        prev->next = b->next;
        if (last_block == b) last_block = prev;
    }
}

void *malloc(size_t size)
{
    size_t wanted;
    if (!size_aligned(size, &wanted) ||
        wanted > (size_t)PTRDIFF_MAX - BLOCK_HEADER) {
        errno = ENOMEM;
        return NULL;
    }

    MemBlock *fit;
    if (!scan_heap(NULL, wanted, NULL, NULL, &fit)) {
        errno = EINVAL;
        return NULL;
    }
    if (fit) {
        split_block(fit, wanted);
        fit->used = 1u;
        return (uint8_t *)fit + BLOCK_HEADER;
    }

    size_t total = BLOCK_HEADER + wanted;
    MemBlock *b = (MemBlock *)_sbrk((ptrdiff_t)total);
    if (b == (void *)-1) {
        errno = ENOMEM;
        return NULL;
    }
    /* A separate direct _sbrk() user is outside this allocator's contract. */
    if (last_block && (uintptr_t)b != heap_end_addr) {
        errno = EINVAL;
        return NULL;
    }
    if (!last_block) heap_first_addr = (uintptr_t)b;
    heap_end_addr = (uintptr_t)b + (uintptr_t)total;
    b->capacity = wanted;
    b->used = 1u;
    b->next = NULL;
    if (last_block) last_block->next = b;
    else first_block = b;
    last_block = b;
    return (uint8_t *)b + BLOCK_HEADER;
}

void free(void *ptr)
{
    if (!ptr) return;
    MemBlock *b;
    MemBlock *prev;
    if (!scan_heap(ptr, 0u, &b, &prev, NULL) || !b) {
        errno = EINVAL;
        return;
    }
    b->used = 0u;
    coalesce_neighbours(b, prev);
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
    for (size_t i = 0; i < bytes; ++i) result[i] = 0u;
    return result;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr) return malloc(size);
    if (size == 0u) { free(ptr); return NULL; }

    MemBlock *b;
    if (!scan_heap(ptr, 0u, &b, NULL, NULL) || !b) {
        errno = EINVAL;
        return NULL;
    }
    size_t wanted;
    if (!size_aligned(size, &wanted) ||
        wanted > (size_t)PTRDIFF_MAX - BLOCK_HEADER) {
        errno = ENOMEM;
        return NULL;
    }
    if (wanted <= b->capacity) {
        split_block(b, wanted);
        return ptr;
    }

    /* Failed growth always preserves the original allocation. */
    void *replacement = malloc(size);
    if (!replacement) return NULL;
    uint8_t *from = (uint8_t *)ptr;
    uint8_t *to = (uint8_t *)replacement;
    for (size_t i = 0; i < b->capacity; ++i) to[i] = from[i];
    free(ptr);
    return replacement;
}
