/* SIDBOX / CoderGirl V2 Stage 6A: STACK MAPPING ONLY.
 * Verifies whether entry and GUI callbacks run on MSP or PSP, and whether the
 * reserved V2 stack area is currently unused. Does NOT switch stacks.
 * This is a small test applet, not a firmware patch.
 */
#include <stdint.h>
#include <stddef.h>
#include "apis.h"

#define WIN_INVALID ((CGWindow)0xffu)
#define STACK_RESERVE_BYTES 8192u
#define STACK_CANARY 0xB6u

#if defined(S6_APP_A)
# define WIN_TITLE "V2 STACK A"
# define START_TEXT "A: press PROBE"
# define BUTTON_TEXT "PROBE A"
# define SHARED_TEXT "A: MSP / shared"
# define PRIVATE_TEXT "A: PSP / private?"
# define ERR_TEXT "A: STACK ERROR"
# define XPOS 14
# define YPOS 18
#elif defined(S6_APP_B)
# define WIN_TITLE "V2 STACK B"
# define START_TEXT "B: press PROBE"
# define BUTTON_TEXT "PROBE B"
# define SHARED_TEXT "B: MSP / shared"
# define PRIVATE_TEXT "B: PSP / private?"
# define ERR_TEXT "B: STACK ERROR"
# define XPOS 141
# define YPOS 80
#else
# error "Define S6_APP_A or S6_APP_B"
#endif

extern uint8_t __stack_start__;
extern uint8_t __stack_end__;

static char title[] = WIN_TITLE;
static char label_start[] = START_TEXT;
static char label_shared[] = SHARED_TEXT;
static char label_private[] = PRIVATE_TEXT;
static char label_error[] = ERR_TEXT;
static char button_text[] = BUTTON_TEXT;
static CGWindow window_handle = WIN_INVALID;
static CGGadget label_handle;
static CGGadget button_handle;
static uint32_t clicks;

struct stack_regs {
    uintptr_t sp;
    uintptr_t msp;
    uintptr_t psp;
    uint32_t control;
};

__attribute__((noinline))
static void read_stack_regs(struct stack_regs *r)
{
    uintptr_t sp, msp, psp;
    uint32_t control;
    __asm volatile ("mov %0, sp" : "=r"(sp));
    __asm volatile ("mrs %0, msp" : "=r"(msp));
    __asm volatile ("mrs %0, psp" : "=r"(psp));
    __asm volatile ("mrs %0, control" : "=r"(control));
    r->sp = sp;
    r->msp = msp;
    r->psp = psp;
    r->control = control;
}

/* The linker reserves this memory, but it is not an active execution stack
 * until the OS deliberately switches to it. For this diagnostic ONLY, fill
 * the reservation with canaries. Never do this once private stacks are active.
 */
static uint32_t fill_reserved_stack(void)
{
    volatile uint8_t *start = &__stack_start__;
    uintptr_t begin = (uintptr_t)start;
    uintptr_t end = (uintptr_t)&__stack_end__;
    if (end < begin || end - begin != STACK_RESERVE_BYTES)
        return 1u;
    /* Future-proof: never overwrite an area already used as this applet's
     * execution stack. The Stage 6A test is deliberately shared-stack only. */
    uintptr_t current_sp;
    __asm volatile ("mov %0, sp" : "=r"(current_sp));
    if (current_sp >= begin && current_sp < end)
        return 4u;
    for (uintptr_t i = 0; i < end - begin; ++i)
        start[i] = STACK_CANARY;
    return 0u;
}

static uint32_t check_reserved_stack(void)
{
    volatile const uint8_t *start = &__stack_start__;
    uintptr_t begin = (uintptr_t)start;
    uintptr_t end = (uintptr_t)&__stack_end__;
    if (end < begin || end - begin != STACK_RESERVE_BYTES)
        return 2u;
    for (uintptr_t i = 0; i < end - begin; ++i)
        if (start[i] != STACK_CANARY)
            return 3u;
    return 0u;
}

/* About 5 * 96 bytes of harmless automatic data, to measure stack direction
 * without making large or dangerous demands of the CoderGirl main stack.
 * volatile and noinline prevent optimisation into a zero-stack tail call.
 */
__attribute__((noinline))
static uint32_t depth_probe(uint32_t depth, volatile uintptr_t *lowest)
{
    volatile uint8_t scratch[96];
    uintptr_t here;
    __asm volatile ("mov %0, sp" : "=r"(here));
    if (here < *lowest)
        *lowest = here;
    scratch[0] = (uint8_t)(depth + 3u);
    scratch[95] = (uint8_t)(depth + 7u);
    uint32_t result = (uint32_t)scratch[0] + (uint32_t)scratch[95];
    if (depth != 0u)
        result += depth_probe(depth - 1u, lowest);
    return result + (uint32_t)scratch[0];
}

static void log_stack(const char *where)
{
    struct stack_regs r;
    read_stack_regs(&r);
    uintptr_t min_sp = r.sp;
    volatile uint32_t sink = depth_probe(4u, &min_sp);
    uint32_t canary = check_reserved_stack();
    uint32_t using_psp = (r.control & 2u) != 0u;
    uintptr_t begin = (uintptr_t)&__stack_start__;
    uintptr_t end = (uintptr_t)&__stack_end__;
    uint32_t inside = (r.sp >= begin && r.sp < end);

    API->gui->console->printf(0,
        "%s %s #%lu: SP=%08lX MSP=%08lX PSP=%08lX CTRL=%08lX\n",
        title, where, (unsigned long)clicks,
        (unsigned long)r.sp, (unsigned long)r.msp,
        (unsigned long)r.psp, (unsigned long)r.control);
    API->gui->console->printf(0,
        " stack reserved %08lX..%08lX; SPinside=%lu canary=%lu lowSP=%08lX (sum=%lu)\n",
        (unsigned long)begin, (unsigned long)end,
        (unsigned long)inside, (unsigned long)canary,
        (unsigned long)min_sp, (unsigned long)sink);

    if (canary != 0u || inside != 0u) {
        SBOS_LabelSetText(label_handle, label_error);
    } else {
        SBOS_LabelSetText(label_handle, using_psp ? label_private : label_shared);
    }
}

static CGWindowProcRes proc(CGWindow win, const CGMessage_t *msg)
{
    if (!msg) return CGPROC_DEFAULT;
    if (msg->mtype == CGMSG_GADGET && msg->gadget == button_handle &&
        (msg->eventClass == CGEVT_GAD_PRESSED || msg->eventClass == CGEVT_GAD_ACTIVATED)) {
        ++clicks;
        log_stack("callback");
        return CGPROC_HANDLED;
    }
    if (msg->mtype == CGMSG_WINDOW && msg->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        SBOS_CloseWindow(win);
        window_handle = WIN_INVALID;
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

static MSGWndProc volatile callback = proc;

__attribute__((visibility("hidden")))
int applet_entry(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (window_handle != WIN_INVALID) return 0;
    uint32_t initial = fill_reserved_stack();
    struct stack_regs entry_regs;
    read_stack_regs(&entry_regs);
    CGWindow win = WIN_INVALID;
    SBOS_CreateWindow(&win, XPOS, YPOS, 315, 148, title,
                      SBX_WF_VISIBLE | SBX_WF_CLOSE | SBX_WF_TITLE_BAR |
                      SBX_WF_MOVEABLE | SBX_WF_ZORDER);
    if (win == WIN_INVALID) return 31;
    window_handle = win;
    SBOS_SetWindowProc(win, callback);
    label_handle = SBOS_CreateLabel(win, 12, 40, 278, 20,
                                   initial ? label_error : label_start, GAD_TOOL_DEFAULT);
    button_handle = SBOS_CreateButton(win, 12, 82, 108, 26,
                                     button_text, GAD_TOOL_DEFAULT);
    API->gui->console->printf(0,
        "%s entry: SP=%08lX MSP=%08lX PSP=%08lX CTRL=%08lX init=%lu\n",
        title, (unsigned long)entry_regs.sp, (unsigned long)entry_regs.msp,
        (unsigned long)entry_regs.psp, (unsigned long)entry_regs.control,
        (unsigned long)initial);
    SBOS_WindowToFront(win);
    return 0;
}
