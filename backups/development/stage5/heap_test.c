/* SIDBOX V2 Stage 5A: test the SDK's ACTUAL _sbrk(), no newlib or malloc.
 * No firmware/API/legacy-app changes. Every instance has its own heap state.
 * Test: A and B may coexist, each keeps a small live allocation, each must
 * reject over-allocation without modifying the next applet's memory.
 */
#include <stdint.h>
#include <stddef.h>
#include "apis.h"

#define WIN_INVALID ((CGWindow)0xffu)
#define HEAP_BYTES 16384u
#define ENOMEM_CODE 12

extern void *_sbrk(ptrdiff_t increment);
extern void initMalloc(void);
extern uint8_t __v2_heap_start__;
extern void *heap_base;
extern uint32_t heap_size;
extern int errno;
int errno;

#ifdef STAGE5_APP_A
#define WINDOW_TITLE "V2 HEAP A"
#define START_TEXT "A: press TEST"
#define PASS_TEXT "A: HEAP BOUNDS PASS"
#define RECHECK_TEXT "A: STILL INTACT"
#define FAIL_TEXT "A: HEAP TEST FAILED"
#define BUTTON_TEXT "TEST A"
#define WINDOW_X 18
#define WINDOW_Y 19
#define MAGIC_BYTE 0xA6u
#elif defined(STAGE5_APP_B)
#define WINDOW_TITLE "V2 HEAP B"
#define START_TEXT "B: press TEST"
#define PASS_TEXT "B: HEAP BOUNDS PASS"
#define RECHECK_TEXT "B: STILL INTACT"
#define FAIL_TEXT "B: HEAP TEST FAILED"
#define BUTTON_TEXT "TEST B"
#define WINDOW_X 152
#define WINDOW_Y 95
#define MAGIC_BYTE 0x5Bu
#else
#error "Must define STAGE5_APP_A or STAGE5_APP_B"
#endif

static CGWindow win_handle = WIN_INVALID;
static CGGadget button_handle, label_handle;
static uint8_t *persistent_block = 0;
static uint8_t stage = 0;
static uint32_t fail_step = 0;
static char start_text[] = START_TEXT;
static char pass_text[] = PASS_TEXT;
static char recheck_text[] = RECHECK_TEXT;
static char fail_text[] = FAIL_TEXT;
static char window_title[] = WINDOW_TITLE;
static char button_text[] = BUTTON_TEXT;

/* Returns 0 for success; each other number identifies a precise failure.
 * All arithmetic is 32-bit on STM32H743, but guard before subtraction. */
static uint32_t heap_probe(void)
{
    uintptr_t base = (uintptr_t)&__v2_heap_start__;
    uintptr_t limit = base + HEAP_BYTES;
    if (heap_size != HEAP_BYTES || (uintptr_t)heap_base != base) return 1;
    if (limit < base) return 2;

    uintptr_t start = (uintptr_t)_sbrk(0);
    if (start != base || (start & 7u)) return 3;

    uint8_t *block = (uint8_t *)_sbrk(64);
    if ((uintptr_t)block != start) return 4;
    for (uint32_t i = 0; i < 64u; ++i) block[i] = (uint8_t)(MAGIC_BYTE + i);
    persistent_block = block;

    uintptr_t midway = (uintptr_t)_sbrk(0);
    if (midway != start + 64u || midway > limit) return 5;

    /* Allocate through the LAST byte of the heap. This must be safe: the
       applet loader reserves the full HEAP_BYTES after the linker image. */
    uintptr_t remaining = limit - midway;
    uint8_t *tail = (uint8_t *)_sbrk((ptrdiff_t)remaining);
    if ((uintptr_t)tail != midway || remaining == 0u) return 6;
    tail[0] = MAGIC_BYTE;
    tail[remaining - 1u] = (uint8_t)(MAGIC_BYTE ^ 0xffu);
    if ((uintptr_t)_sbrk(0) != limit) return 7;

    /* Both an overflow and a one-byte request must fail without moving break. */
    errno = 0;
    if (_sbrk(1) != (void *)-1 || errno != ENOMEM_CODE) return 8;
    if ((uintptr_t)_sbrk(0) != limit) return 9;
    errno = 0;
    if (_sbrk(4096) != (void *)-1 || errno != ENOMEM_CODE) return 10;
    if ((uintptr_t)_sbrk(0) != limit) return 11;

    /* Rewind 32 bytes, reclaim them, and ensure it doesn't corrupt data. */
    if ((uintptr_t)_sbrk(-32) != limit) return 12;
    if ((uintptr_t)_sbrk(32) != limit - 32u) return 13;
    if ((uintptr_t)_sbrk(0) != limit) return 14;
    if (tail[remaining - 1u] != (uint8_t)(MAGIC_BYTE ^ 0xffu)) return 15;
    for (uint32_t i = 0; i < 64u; ++i)
        if (block[i] != (uint8_t)(MAGIC_BYTE + i)) return 16;
    return 0;
}

static CGWindowProcRes window_proc(CGWindow h, const CGMessage_t *m)
{
    if (!m) return CGPROC_DEFAULT;
    if (m->mtype == CGMSG_GADGET && m->gadget == button_handle &&
       (m->eventClass == CGEVT_GAD_PRESSED || m->eventClass == CGEVT_GAD_ACTIVATED)) {
        if (stage == 0) {
            /* initMalloc initialises the SDK's V2 bookkeeping. */
            initMalloc();
            fail_step = heap_probe();
            stage = (fail_step == 0) ? 1u : 2u;
            SBOS_LabelSetText(label_handle, stage == 1 ? pass_text : fail_text);
            API->gui->console->printf(0, "%s - HEAP TEST step %lu\n", window_title,
                                      (unsigned long)fail_step);
        } else if (stage == 1) {
            uint32_t i;
            for (i = 0; i < 64u; ++i) {
                if (persistent_block[i] != (uint8_t)(MAGIC_BYTE + i)) break;
            }
            if (i == 64u && (uintptr_t)_sbrk(0) ==
                (uintptr_t)&__v2_heap_start__ + HEAP_BYTES) {
                SBOS_LabelSetText(label_handle, recheck_text);
                API->gui->console->printf(0, "%s - PERSISTENCE PASS\n", window_title);
            } else {
                stage = 2;
                fail_step = 17;
                SBOS_LabelSetText(label_handle, fail_text);
                API->gui->console->printf(0, "%s - HEAP TEST step %lu\n", window_title,
                                          (unsigned long)fail_step);
            }
        }
        return CGPROC_HANDLED;
    }
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        SBOS_CloseWindow(h);
        win_handle = WIN_INVALID;
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

static MSGWndProc volatile callback = window_proc;

__attribute__((visibility("hidden")))
int applet_entry(int argc, char **argv)
{
    (void)argc; (void)argv;
    if (win_handle != WIN_INVALID) return 0;
    CGWindow h = WIN_INVALID;
    SBOS_CreateWindow(&h, WINDOW_X, WINDOW_Y, 300, 150, window_title,
                      SBX_WF_VISIBLE | SBX_WF_CLOSE | SBX_WF_TITLE_BAR |
                      SBX_WF_MOVEABLE | SBX_WF_ZORDER);
    if (h == WIN_INVALID) return 31;
    win_handle = h;
    SBOS_SetWindowProc(h, callback);
    label_handle = SBOS_CreateLabel(h, 12, 42, 270, 20, start_text, GAD_TOOL_DEFAULT);
    button_handle = SBOS_CreateButton(h, 12, 84, 100, 26, button_text, GAD_TOOL_DEFAULT);
    SBOS_WindowToFront(h);
    return 0;
}
