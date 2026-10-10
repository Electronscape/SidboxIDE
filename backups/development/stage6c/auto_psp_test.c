/* SIDBOX V2 Stage 6C: firmware-managed automatic private PSP callbacks.
 * Applet contains NO stack switch code. Only firmware selects PSP.
 * Entry deliberately stays on MSP for this first bridge experiment.
 */
#include <stdint.h>
#include <stddef.h>
#include "apis.h"

#define INVALID_WIN ((CGWindow)0xffu)
#if defined(S6C_APP_A)
#define ID "A"
#define W_TITLE "V2 AUTO PSP A"
#define W_X 12
#define W_Y 18
#define INIT_TEXT "A: press TEST"
#define BTN_TEXT "TEST AUTO PSP A"
#define BUTTON_OK "A: BUTTON PSP PASS"
#define TIMER_OK "A: TIMER PSP PASS"
#define FAIL_TEXT "A: PSP FAILED"
#elif defined(S6C_APP_B)
#define ID "B"
#define W_TITLE "V2 AUTO PSP B"
#define W_X 145
#define W_Y 86
#define INIT_TEXT "B: press TEST"
#define BTN_TEXT "TEST AUTO PSP B"
#define BUTTON_OK "B: BUTTON PSP PASS"
#define TIMER_OK "B: TIMER PSP PASS"
#define FAIL_TEXT "B: PSP FAILED"
#else
#error Define S6C_APP_A or S6C_APP_B
#endif

extern uint8_t __stack_start__, __stack_end__;
static char title[] = W_TITLE;
static char label_init[] = INIT_TEXT;
static char label_button_pass[] = BUTTON_OK;
static char label_timer_pass[] = TIMER_OK;
static char label_failure[] = FAIL_TEXT;
static char button_caption[] = BTN_TEXT;

static CGWindow window_handle = INVALID_WIN;
static CGGadget label_handle;
static CGGadget button_handle;
static CGTimer timer_handle = CGTIMER_INVALID;
static uint32_t button_count, timer_count;

struct cpu_regs { uint32_t sp, msp, psp, control, ipsr; };
__attribute__((noinline)) static void regs(struct cpu_regs *r)
{
    __asm volatile("mov %0, sp" : "=r"(r->sp));
    __asm volatile("mrs %0, msp" : "=r"(r->msp));
    __asm volatile("mrs %0, psp" : "=r"(r->psp));
    __asm volatile("mrs %0, control" : "=r"(r->control));
    __asm volatile("mrs %0, ipsr" : "=r"(r->ipsr));
}

__attribute__((noinline)) static int verify_psp(const char *kind)
{
    struct cpu_regs r;
    regs(&r);
    uint32_t start=(uint32_t)(uintptr_t)&__stack_start__;
    uint32_t end=(uint32_t)(uintptr_t)&__stack_end__;
    int ok = (r.control & 2u) && r.ipsr==0u && r.sp==r.psp &&
             r.sp >= start + 256u && r.sp < end &&
             end-start == 8192u;
    API->gui->console->printf(0,
        "S6C " ID " %s PSP=%08lX MSP=%08lX CTRL=%08lX RANGE=%08lX..%08lX ISSUE=%lu\n",
        kind, (unsigned long)r.psp, (unsigned long)r.msp,
        (unsigned long)r.control, (unsigned long)start, (unsigned long)end,
        (unsigned long)!ok);
    return ok;
}

static void on_timer(void *user)
{
    (void)user;
    ++timer_count;
    int ok=verify_psp("TIMER");
    SBOS_LabelSetText(label_handle,ok?label_timer_pass:label_failure);
}

static CGWindowProcRes on_window(CGWindow win, const CGMessage_t *m)
{
    if (!m) return CGPROC_DEFAULT;
    if (m->mtype == CGMSG_GADGET && m->gadget == button_handle &&
        m->eventClass == CGEVT_GAD_ACTIVATED) {
        ++button_count;
        int ok=verify_psp("BUTTON");
        SBOS_LabelSetText(label_handle,ok?label_button_pass:label_failure);
        if (timer_handle != CGTIMER_INVALID)
            SBOS_TimerSet(timer_handle,600u,0u,on_timer,0);
        return CGPROC_HANDLED;
    }
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        /* Important: window destruction happens while the private stack is
         * active, so firmware must postpone reclaiming the slot until MSP. */
        SBOS_CloseWindow(win);
        window_handle = INVALID_WIN;
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}
static MSGWndProc volatile window_proc_ptr = on_window;
__attribute__((visibility("hidden")))
int applet_entry(int argc, char **argv)
{
    (void)argc; (void)argv;
    if (window_handle != INVALID_WIN) return 0;
    CGWindow win = INVALID_WIN;
    SBOS_CreateWindow(&win, W_X, W_Y, 320, 150, title,
        SBX_WF_VISIBLE|SBX_WF_CLOSE|SBX_WF_TITLE_BAR|SBX_WF_MOVEABLE|SBX_WF_ZORDER);
    if (win == INVALID_WIN) return 41;
    window_handle=win;
    SBOS_SetWindowProc(win,window_proc_ptr);
    label_handle=SBOS_CreateLabel(win,12,40,285,20,label_init,GAD_TOOL_DEFAULT);
    button_handle=SBOS_CreateButton(win,12,83,174,26,button_caption,GAD_TOOL_DEFAULT);
    timer_handle=SBOS_CreateTimer();
    SBOS_WindowToFront(win);
    return 0;
}
