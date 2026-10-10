/* SIDBOX V2 Stage 6B: LIMITED PROCESS STACK EXPERIMENT.
 *
 * We do NOT modify the firmware or install PSP permanently. Entry and the
 * outer GUI callback remain on the existing CoderGirl MSP. A naked ARM Thumb
 * bridge briefly selects the applet's 8 KiB reserved PSP stack, calls a
 * small, freestanding calculation, then restores BOTH CONTROL and the old PSP
 * before returning to GUI code on MSP.
 *
 * Only use with the already-tested experimental V2 loader on Cortex-M7.
 * This proves one private execution interval, NOT isolation for general
 * window callbacks / OS API calls / multitasking.
 */
#include <stdint.h>
#include <stddef.h>
#include "apis.h"

#define WIN_INVALID ((CGWindow)0xffu)
#define STACK_RESERVE_BYTES 8192u
#define STACK_CANARY 0xA6u
#define STACK_GUARD_BYTES 256u

#if defined(S6B_APP_A)
#define WIN_TITLE "V2 PRIVATE STACK A"
#define INIT_TEXT "A: Press PSP test"
#define PASS_TEXT "A: PRIVATE PSP PASS"
#define FAIL_TEXT "A: PSP TEST FAILED"
#define BUTTON_TEXT "TEST PSP A"
#define APP_ID "A"
#define XPOS 13
#define YPOS 19
#elif defined(S6B_APP_B)
#define WIN_TITLE "V2 PRIVATE STACK B"
#define INIT_TEXT "B: Press PSP test"
#define PASS_TEXT "B: PRIVATE PSP PASS"
#define FAIL_TEXT "B: PSP TEST FAILED"
#define BUTTON_TEXT "TEST PSP B"
#define APP_ID "B"
#define XPOS 140
#define YPOS 80
#else
#error "Define S6B_APP_A or S6B_APP_B"
#endif

extern uint8_t __stack_start__;
extern uint8_t __stack_end__;

static char title[] = WIN_TITLE;
static char label_init[] = INIT_TEXT;
static char label_pass[] = PASS_TEXT;
static char label_fail[] = FAIL_TEXT;
static char button_text[] = BUTTON_TEXT;

static CGWindow window_handle = WIN_INVALID;
static CGGadget label_handle;
static CGGadget button_handle;
static uint32_t click_count;

struct stack_regs {
    uintptr_t sp;
    uintptr_t msp;
    uintptr_t psp;
    uint32_t control;
    uint32_t ipsr;
};

struct probe_result {
    struct stack_regs inside;
    uintptr_t low_sp;
    uint32_t checksum;
};
static volatile struct probe_result g_probe;

__attribute__((noinline))
static void read_regs(struct stack_regs *r)
{
    uintptr_t sp, msp, psp;
    uint32_t control, ipsr;
    __asm volatile("mov %0, sp" : "=r"(sp));
    __asm volatile("mrs %0, msp" : "=r"(msp));
    __asm volatile("mrs %0, psp" : "=r"(psp));
    __asm volatile("mrs %0, control" : "=r"(control));
    __asm volatile("mrs %0, ipsr" : "=r"(ipsr));
    r->sp = sp;
    r->msp = msp;
    r->psp = psp;
    r->control = control;
    r->ipsr = ipsr;
}

/* Called only while PSP is selected. No CoderGirl API call is made here. */
__attribute__((noinline))
static uint32_t stack_work(uint32_t depth, volatile uintptr_t *lowest)
{
    volatile uint8_t scratch[96];
    uintptr_t here;
    __asm volatile("mov %0, sp" : "=r"(here));
    if (here < *lowest)
        *lowest = here;
    scratch[0] = (uint8_t)(depth + 3u);
    scratch[95] = (uint8_t)(depth + 7u);
    uint32_t sum = (uint32_t)scratch[0] + (uint32_t)scratch[95];
    if (depth != 0u)
        sum += stack_work(depth - 1u, lowest);
    return sum + (uint32_t)scratch[0];
}

__attribute__((noinline))
static void private_work(void)
{
    struct stack_regs regs;
    read_regs(&regs);
    g_probe.inside.sp = regs.sp;
    g_probe.inside.msp = regs.msp;
    g_probe.inside.psp = regs.psp;
    g_probe.inside.control = regs.control;
    g_probe.inside.ipsr = regs.ipsr;
    uintptr_t lowest = regs.sp;
    g_probe.checksum = stack_work(5u, &lowest);
    g_probe.low_sp = lowest;
}

/* AAPCS-safe ARMv7-M bridge. Saves LR, r4 and r5 (plus r6 for 8-byte
 * alignment) on the original MSP, swaps to PSP only across the supplied
 * test callback, then restores the original CONTROL AND previous PSP.
 * CONTROL includes the FPCA bit observed as 0x04.
 *
 * Interrupts are NOT disabled. Cortex-M exception handlers continue using
 * MSP; hardware can stack the interrupted Thread-mode frame on PSP.
 * The reserved stack must therefore have generous extra headroom.
 *
 * Requirements: invoked in privileged Thread mode on MSP, no nested PSP
 * activity, psp_top is 8-byte aligned, fn returns normally (no longjmp).
 */
__attribute__((naked, noinline))
static void invoke_on_psp(uintptr_t psp_top, void (*fn)(void))
{
    __asm volatile(
        "push {r4, r5, r6, lr}\n"
        "mrs r4, control\n"
        "mrs r5, psp\n"
        "msr psp, r0\n"
        "orr r0, r4, #2\n"
        "msr control, r0\n"
        "isb\n"
        "blx r1\n"
        "msr control, r4\n"
        "isb\n"
        "msr psp, r5\n"
        "pop {r4, r5, r6, pc}\n"
    );
}

static uint32_t prepare_stack(void)
{
    uintptr_t begin = (uintptr_t)&__stack_start__;
    uintptr_t end = (uintptr_t)&__stack_end__;
    if (end <= begin || end - begin != STACK_RESERVE_BYTES ||
        (end & 7u) != 0u || (begin & 7u) != 0u)
        return 1u;
    volatile uint8_t *p = (volatile uint8_t *)begin;
    for (uint32_t i = 0; i < STACK_RESERVE_BYTES; ++i)
        p[i] = STACK_CANARY;
    return 0u;
}

static uint32_t used_stack_bytes(void)
{
    volatile const uint8_t *p = (volatile const uint8_t *)&__stack_start__;
    for (uint32_t i = 0; i < STACK_RESERVE_BYTES; ++i) {
        if (p[i] != STACK_CANARY)
            return STACK_RESERVE_BYTES - i;
    }
    return 0u;
}

static void test_psp(void)
{
    struct stack_regs before, after;
    uint32_t issue = prepare_stack();
    read_regs(&before);
    if ((before.control & 3u) != 0u || before.ipsr != 0u ||
        before.sp != before.msp || issue != 0u) {
        issue = issue ? issue : 2u;
    } else {
        g_probe.checksum = 0u;
        g_probe.low_sp = 0u;
        invoke_on_psp((uintptr_t)&__stack_end__, private_work);
    }
    read_regs(&after);
    uintptr_t begin = (uintptr_t)&__stack_start__;
    uintptr_t end = (uintptr_t)&__stack_end__;
    uint32_t used = issue ? 0u : used_stack_bytes();
    if (!issue) {
        if (after.ipsr != 0u || (after.control & 2u) != 0u ||
            after.sp != after.msp || after.psp != before.psp ||
            after.control != before.control)
            issue = 3u;
        else if ((g_probe.inside.control & 2u) == 0u ||
                 g_probe.inside.ipsr != 0u ||
                 g_probe.inside.sp != g_probe.inside.psp ||
                 g_probe.inside.sp < begin + STACK_GUARD_BYTES ||
                 g_probe.inside.sp >= end)
            issue = 4u;
        else if (g_probe.low_sp < begin + STACK_GUARD_BYTES ||
                 g_probe.low_sp >= end ||
                 used == 0u || used > STACK_RESERVE_BYTES - STACK_GUARD_BYTES ||
                 g_probe.checksum == 0u)
            issue = 5u;
    }
    /* All OS output happens AFTER we've returned to CoderGirl's MSP. */
    API->gui->console->printf(0,
        "STAGE6B " APP_ID " #%lu BEFORE SP=%08lX MSP=%08lX PSP=%08lX CTRL=%08lX\n",
        (unsigned long)click_count,
        (unsigned long)before.sp, (unsigned long)before.msp,
        (unsigned long)before.psp, (unsigned long)before.control);
    API->gui->console->printf(0,
        "STAGE6B " APP_ID " PRIVATE SP=%08lX PSP=%08lX CTRL=%08lX lowSP=%08lX\n",
        (unsigned long)g_probe.inside.sp,
        (unsigned long)g_probe.inside.psp,
        (unsigned long)g_probe.inside.control,
        (unsigned long)g_probe.low_sp);
    API->gui->console->printf(0,
        "STAGE6B " APP_ID " AFTER SP=%08lX MSP=%08lX PSP=%08lX CTRL=%08lX USED=%lu ISSUE=%lu\n",
        (unsigned long)after.sp, (unsigned long)after.msp,
        (unsigned long)after.psp, (unsigned long)after.control,
        (unsigned long)used, (unsigned long)issue);
    SBOS_LabelSetText(label_handle, issue ? label_fail : label_pass);
}

static CGWindowProcRes window_proc(CGWindow win, const CGMessage_t *msg)
{
    if (!msg) return CGPROC_DEFAULT;
    if (msg->mtype == CGMSG_GADGET && msg->gadget == button_handle &&
        (msg->eventClass == CGEVT_GAD_PRESSED || msg->eventClass == CGEVT_GAD_ACTIVATED)) {
        ++click_count;
        test_psp();
        return CGPROC_HANDLED;
    }
    if (msg->mtype == CGMSG_WINDOW && msg->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        SBOS_CloseWindow(win);
        window_handle = WIN_INVALID;
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

static MSGWndProc volatile callback = window_proc;

__attribute__((visibility("hidden")))
int applet_entry(int argc, char **argv)
{
    (void)argc; (void)argv;
    if (window_handle != WIN_INVALID) return 0;
    CGWindow win = WIN_INVALID;
    SBOS_CreateWindow(&win, XPOS, YPOS, 319, 145, title,
                      SBX_WF_VISIBLE | SBX_WF_CLOSE | SBX_WF_TITLE_BAR |
                      SBX_WF_MOVEABLE | SBX_WF_ZORDER);
    if (win == WIN_INVALID) return 31;
    window_handle = win;
    SBOS_SetWindowProc(win, callback);
    label_handle = SBOS_CreateLabel(win, 12, 40, 286, 20,
                                   label_init, GAD_TOOL_DEFAULT);
    button_handle = SBOS_CreateButton(win, 12, 82, 118, 26,
                                     button_text, GAD_TOOL_DEFAULT);
    SBOS_WindowToFront(win);
    return 0;
}
