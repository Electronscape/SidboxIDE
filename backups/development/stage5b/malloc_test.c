/* SIDBOX / CoderGirl — Applet V2 Stage 5B.
 * REAL newlib/newlib-nano malloc, calloc, realloc and free hardware test.
 * The applet contains no stand-in implementation of these functions.
 * Two variant applets can be launched together, with separate malloc state.
 * Both use the existing V2 firmware loader; no firmware patch required.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include "apis.h"

#define WIN_INVALID ((CGWindow)0xffu)
#define EXPECTED_HEAP_BYTES 16384u
#define PRESSURE_BLOCK 384u
#define PRESSURE_COUNT 48u

extern void initMalloc(void);
extern void *_sbrk(ptrdiff_t);
extern uint8_t __v2_heap_start__;
extern void *heap_base;
extern uint32_t heap_size;

#if defined(STAGE5B_APP_A)
# define WIN_TITLE "V2 MALLOC A"
# define LABEL_START "A: press TEST"
# define LABEL_PASS  "A: MALLOC PASS"
# define LABEL_RECHECK "A: STILL INTACT"
# define LABEL_FAIL  "A: MALLOC FAILED"
# define BUTTON_CAPTION "TEST A"
# define WIN_X 15
# define WIN_Y 18
# define PATTERN 0x3Du
#elif defined(STAGE5B_APP_B)
# define WIN_TITLE "V2 MALLOC B"
# define LABEL_START "B: press TEST"
# define LABEL_PASS "B: MALLOC PASS"
# define LABEL_RECHECK "B: STILL INTACT"
# define LABEL_FAIL "B: MALLOC FAILED"
# define BUTTON_CAPTION "TEST B"
# define WIN_X 142
# define WIN_Y 86
# define PATTERN 0xA7u
#else
# error "Build with -DSTAGE5B_APP_A or -DSTAGE5B_APP_B"
#endif

static char title[] = WIN_TITLE;
static char text_start[] = LABEL_START;
static char text_pass[] = LABEL_PASS;
static char text_recheck[] = LABEL_RECHECK;
static char text_fail[] = LABEL_FAIL;
static char text_button[] = BUTTON_CAPTION;

static CGWindow window_handle = WIN_INVALID;
static CGGadget button_handle, label_handle;
static volatile uint8_t stage = 0; /* 0=initial, 1=allocated, 2=failed */
static uint32_t result_step = 0;
static uint8_t *persistent = NULL;
static uint8_t *resized = NULL;
static uint8_t *zeroed = NULL;
static uint8_t *reused = NULL;
static uint32_t peak_allocations = 0;

static void fill(uint8_t *p, uint32_t length, uint8_t seed)
{
    for (uint32_t i = 0; i != length; ++i) p[i] = (uint8_t)(seed + i);
}

/* Ensure an unexpectedly broken allocator cannot turn our test into a
 * neighbouring-applet memory write. Stage 5A already verified _sbrk, but
 * Stage 5B explicitly checks every returned pointer before using it. */
static int in_heap(const void *ptr, uint32_t length)
{
    uintptr_t start = (uintptr_t)&__v2_heap_start__;
    uintptr_t address = (uintptr_t)ptr;
    uintptr_t end = start + EXPECTED_HEAP_BYTES;
    return end >= start && address >= start && address <= end &&
           length <= end - address;
}

static int check(const uint8_t *p, uint32_t length, uint8_t seed)
{
    if (!p) return 0;
    for (uint32_t i = 0; i != length; ++i)
        if (p[i] != (uint8_t)(seed + i)) return 0;
    return 1;
}

/* The test does not require any particular malloc freelist strategy; it
 * checks valid pointers, stored data and the bounded *applet* heap. */
static uint32_t run_allocator_probe(void)
{
    uintptr_t base = (uintptr_t)&__v2_heap_start__;
    uintptr_t limit = base + EXPECTED_HEAP_BYTES;
    uint8_t *blocks[PRESSURE_COUNT] = { 0 };
    uint32_t count = 0;

    if (heap_size != EXPECTED_HEAP_BYTES || (uintptr_t)heap_base != base) return 1;
    if (limit < base) return 2;
    if ((uintptr_t)_sbrk(0) < base || (uintptr_t)_sbrk(0) > limit) return 3;

    persistent = (uint8_t *)malloc(96);
    if (!persistent) return 4;
    if (!in_heap(persistent, 96)) return 26;
    fill(persistent, 96, PATTERN);

    resized = (uint8_t *)malloc(192);
    if (!resized) return 5;
    if (!in_heap(resized, 192)) return 27;
    fill(resized, 192, (uint8_t)(PATTERN ^ 0x50u));

    uint8_t *grown = (uint8_t *)realloc(resized, 600);
    if (!grown) return 6;
    if (!in_heap(grown, 600)) return 28;
    resized = grown;
    if (!check(resized, 192, (uint8_t)(PATTERN ^ 0x50u))) return 7;
    fill(resized, 600, (uint8_t)(PATTERN ^ 0x50u));

    zeroed = (uint8_t *)calloc(24, 4);
    if (!zeroed) return 8;
    if (!in_heap(zeroed, 96)) return 29;
    for (uint32_t i = 0; i != 96; ++i)
        if (zeroed[i] != 0) return 9;
    fill(zeroed, 96, (uint8_t)(PATTERN + 3u));

    uint8_t *released = (uint8_t *)malloc(128);
    if (!released) return 10;
    if (!in_heap(released, 128)) return 30;
    fill(released, 128, (uint8_t)(PATTERN + 9u));
    free(released);
    /* Newlib may reuse the same block, but we do not demand identical
     * addresses; different malloc implementations have different policies. */
    reused = (uint8_t *)malloc(64);
    if (!reused) return 11;
    if (!in_heap(reused, 64)) return 31;
    fill(reused, 64, (uint8_t)(PATTERN + 11u));

    while (count < PRESSURE_COUNT) {
        uint8_t *p = (uint8_t *)malloc(PRESSURE_BLOCK);
        if (!p) break;
        if (!in_heap(p, PRESSURE_BLOCK)) return 32;
        blocks[count++] = p;
        fill(p, PRESSURE_BLOCK, (uint8_t)(PATTERN + count));
    }
    peak_allocations = count;
    if (!count) return 12;

    /* Request is larger than the entire 16 KiB heap. Must be refused. */
    if (malloc(EXPECTED_HEAP_BYTES + 4096u) != NULL) return 13;
    if ((uintptr_t)_sbrk(0) > limit) return 14;
    if (!check(persistent, 96, PATTERN) ||
        !check(resized, 600, (uint8_t)(PATTERN ^ 0x50u)) ||
        !check(zeroed, 96, (uint8_t)(PATTERN + 3u)) ||
        !check(reused, 64, (uint8_t)(PATTERN + 11u))) return 15;

    for (uint32_t i = 0; i != count; ++i) {
        if (!check(blocks[i], PRESSURE_BLOCK, (uint8_t)(PATTERN + i + 1u))) return 16;
        free(blocks[i]);
    }
    /* Freed blocks should be available again, even after heap exhaustion. */
    uint8_t *after_free = (uint8_t *)malloc(128);
    if (!after_free) return 17;
    if (!in_heap(after_free, 128)) return 33;
    fill(after_free, 128, PATTERN);
    free(after_free);

    if ((uintptr_t)_sbrk(0) > limit) return 18;
    if (!check(persistent, 96, PATTERN)) return 19;
    return 0;
}

static uint32_t check_persistence(void)
{
    uintptr_t base = (uintptr_t)&__v2_heap_start__;
    if (!check(persistent, 96, PATTERN)) return 20;
    if (!check(resized, 600, (uint8_t)(PATTERN ^ 0x50u))) return 21;
    if (!check(zeroed, 96, (uint8_t)(PATTERN + 3u))) return 22;
    if (!check(reused, 64, (uint8_t)(PATTERN + 11u))) return 23;
    if ((uintptr_t)_sbrk(0) > base + EXPECTED_HEAP_BYTES) return 24;
    /* Additional allocations after the other applet has run. */
    uint8_t *extra = (uint8_t *)malloc(80);
    if (!extra) return 25;
    if (!in_heap(extra, 80)) return 34;
    fill(extra, 80, PATTERN);
    if (!check(extra, 80, PATTERN)) return 26;
    free(extra);
    return 0;
}

static CGWindowProcRes proc(CGWindow window, const CGMessage_t *message)
{
    if (!message) return CGPROC_DEFAULT;
    if (message->mtype == CGMSG_GADGET && message->gadget == button_handle &&
        (message->eventClass == CGEVT_GAD_PRESSED || message->eventClass == CGEVT_GAD_ACTIVATED)) {
        if (stage == 0u) {
            initMalloc();
            result_step = run_allocator_probe();
            stage = result_step == 0u ? 1u : 2u;
            SBOS_LabelSetText(label_handle, stage == 1u ? text_pass : text_fail);
            API->gui->console->printf(0, "%s: malloc step %lu; pressure blocks %lu\n",
                                      title, (unsigned long)result_step,
                                      (unsigned long)peak_allocations);
        } else if (stage == 1u) {
            result_step = check_persistence();
            if (result_step == 0u) {
                SBOS_LabelSetText(label_handle, text_recheck);
                API->gui->console->printf(0, "%s: PERSISTENCE PASS\n", title);
            } else {
                stage = 2u;
                SBOS_LabelSetText(label_handle, text_fail);
                API->gui->console->printf(0, "%s: malloc step %lu\n", title,
                                          (unsigned long)result_step);
            }
        }
        return CGPROC_HANDLED;
    }
    if (message->mtype == CGMSG_WINDOW && message->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        if (stage == 1u) {
            free(persistent);
            free(resized);
            free(zeroed);
            free(reused);
            persistent = resized = zeroed = reused = NULL;
        }
        SBOS_CloseWindow(window);
        window_handle = WIN_INVALID;
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

/* The pointer is genuinely relocatable and survives applet_entry returning. */
static MSGWndProc volatile callback = proc;

__attribute__((visibility("hidden")))
int applet_entry(int argc, char **argv)
{
    (void)argc; (void)argv;
    if (window_handle != WIN_INVALID) return 0;
    CGWindow win = WIN_INVALID;
    SBOS_CreateWindow(&win, WIN_X, WIN_Y, 302, 150, title,
                      SBX_WF_VISIBLE | SBX_WF_CLOSE | SBX_WF_TITLE_BAR |
                      SBX_WF_MOVEABLE | SBX_WF_ZORDER);
    if (win == WIN_INVALID) return 31;
    window_handle = win;
    SBOS_SetWindowProc(win, callback);
    label_handle = SBOS_CreateLabel(win, 12, 42, 270, 20, text_start, GAD_TOOL_DEFAULT);
    button_handle = SBOS_CreateButton(win, 12, 84, 100, 26, text_button, GAD_TOOL_DEFAULT);
    SBOS_WindowToFront(win);
    return 0;
}
