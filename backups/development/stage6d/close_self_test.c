/* SIDBOX V2 Stage 6D — self-close and deferred unload hardware test.
 * Firmware handles PSP switching; the applet never changes CONTROL/PSP.
 * Closing its primary window from a button callback must defer freeing its
 * image until after the callback returns to CoderGirl on MSP.
 * An armed one-shot timer is deliberately left outstanding when closing;
 * applet unregistration must also release that timer.
 */
#include <stdint.h>
#include <stddef.h>
#include "apis.h"

#define INVALID_WIN ((CGWindow)0xffu)
#if defined(S6D_APP_A)
# define ID "A"
# define W_TITLE "V2 CLOSE SELF A"
# define W_X 12
# define W_Y 18
# define INIT_TEXT "A: private stack test"
# define OK_TEXT "A: PSP WORKS"
# define FAIL_TEXT "A: PSP FAILED"
# define TEST_TEXT "TEST PSP A"
# define CLOSE_TEXT "CLOSE SELF A"
#elif defined(S6D_APP_B)
# define ID "B"
# define W_TITLE "V2 CLOSE SELF B"
# define W_X 125
# define W_Y 95
# define INIT_TEXT "B: private stack test"
# define OK_TEXT "B: PSP WORKS"
# define FAIL_TEXT "B: PSP FAILED"
# define TEST_TEXT "TEST PSP B"
# define CLOSE_TEXT "CLOSE SELF B"
#else
# error S6D_APP_A or S6D_APP_B required
#endif

extern uint8_t __stack_start__, __stack_end__;
static char title[] = W_TITLE;
static char label_init[] = INIT_TEXT;
static char label_pass[] = OK_TEXT;
static char label_fail[] = FAIL_TEXT;
static char test_caption[] = TEST_TEXT;
static char close_caption[] = CLOSE_TEXT;

static CGWindow window_handle = INVALID_WIN;
static CGGadget label_handle;
static CGGadget test_button;
static CGGadget close_button;
static CGTimer timer_handle = CGTIMER_INVALID;
static uint32_t presses;
static uint32_t timer_fired;

struct regs {uint32_t sp, psp, msp, control, ipsr;};
__attribute__((noinline)) static void cpu_regs(struct regs *r)
{
    __asm volatile("mov %0, sp" : "=r"(r->sp));
    __asm volatile("mrs %0, psp" : "=r"(r->psp));
    __asm volatile("mrs %0, msp" : "=r"(r->msp));
    __asm volatile("mrs %0, control" : "=r"(r->control));
    __asm volatile("mrs %0, ipsr" : "=r"(r->ipsr));
}

__attribute__((noinline)) static int check_private_stack(const char *where)
{
    struct regs r;
    cpu_regs(&r);
    uint32_t low = (uint32_t)(uintptr_t)&__stack_start__;
    uint32_t high = (uint32_t)(uintptr_t)&__stack_end__;
    int good = ((r.control & 2u) != 0u) && r.ipsr == 0u &&
               r.sp == r.psp && r.sp >= low + 256u && r.sp < high &&
               high - low == 8192u;
    API->gui->console->printf(0,
        "S6D " ID " %s PSP=%08lX CTRL=%08lX ISSUE=%lu\n",
        where, (unsigned long)r.psp, (unsigned long)r.control,
        (unsigned long)!good);
    return good;
}

/* If this fires after the applet has closed, the system has a dangling
 * callback. Leave a pending timer on purpose to probe that cleanup path. */
static void on_timer(void *unused)
{
    (void)unused;
    ++timer_fired;
    (void)check_private_stack("TIMER");
    if (window_handle != INVALID_WIN)
        SBOS_LabelSetText(label_handle, label_pass);
}

static void close_from_private_callback(CGWindow win)
{
    /* This is the critical test: we are still using the image's OWN PSP. */
    if (!check_private_stack("CLOSE-INSIDE-CALLBACK")) {
        SBOS_LabelSetText(label_handle, label_fail);
        return;
    }
    /* Arm a future callback that the OS MUST cancel/free when unloading. */
    if (timer_handle != CGTIMER_INVALID)
        (void)SBOS_TimerSet(timer_handle, 1800u, 0u, on_timer, 0);
    API->gui->console->printf(0, "S6D " ID " requesting self-close now\n");
    SBOS_CloseWindow(win);
    window_handle = INVALID_WIN;
    /* No applet memory may be freed until this callback has returned. */
}

static CGWindowProcRes on_window(CGWindow win, const CGMessage_t *m)
{
    if (!m)
        return CGPROC_DEFAULT;
    if (m->mtype == CGMSG_GADGET && m->eventClass == CGEVT_GAD_ACTIVATED) {
        if (m->gadget == test_button) {
            ++presses;
            int good = check_private_stack("BUTTON");
            SBOS_LabelSetText(label_handle, good ? label_pass : label_fail);
            return CGPROC_HANDLED;
        }
        if (m->gadget == close_button) {
            close_from_private_callback(win);
            return CGPROC_HANDLED;
        }
    }
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        close_from_private_callback(win);
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

static MSGWndProc volatile window_proc_ptr = on_window;
__attribute__((visibility("hidden")))
int applet_entry(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (window_handle != INVALID_WIN)
        return 0;
    CGWindow win = INVALID_WIN;
    SBOS_CreateWindow(&win, W_X, W_Y, 335, 152, title,
        SBX_WF_VISIBLE|SBX_WF_CLOSE|SBX_WF_TITLE_BAR|
        SBX_WF_MOVEABLE|SBX_WF_ZORDER);
    if (win == INVALID_WIN)
        return 41;
    window_handle = win;
    SBOS_SetWindowProc(win, window_proc_ptr);
    label_handle = SBOS_CreateLabel(win, 12, 40, 285, 20,
                                   label_init, GAD_TOOL_DEFAULT);
    test_button = SBOS_CreateButton(win, 12, 82, 138, 26,
                                   test_caption, GAD_TOOL_DEFAULT);
    close_button = SBOS_CreateButton(win, 166, 82, 145, 26,
                                    close_caption, GAD_TOOL_DEFAULT);
    timer_handle = SBOS_CreateTimer();
    SBOS_WindowToFront(win);
    return 0;
}
