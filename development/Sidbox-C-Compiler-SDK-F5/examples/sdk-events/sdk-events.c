#include "apis.h"

static CGGadget status;
static CGGadget progress;
static CGGadget tap_button;
static int taps;
static int allowed = 1;
static int reset_timer = CGTIMER_INVALID;

static void reset_counter(void)
{
    if (reset_timer != CGTIMER_INVALID) {
        SBOS_TimerCancel(reset_timer);
        SBOS_FreeTimer(reset_timer);
        reset_timer = CGTIMER_INVALID;
    }
    taps = 0;
    SBOS_ProgressbarSetValue(progress, 0);
    SBOS_ButtonSetText(tap_button, "Tap +1", -1);
    SBOS_GadgetEnabled(tap_button, allowed);
    if (allowed)
        SBOS_LabelSetText(status, "Tap five times.");
    else
        SBOS_LabelSetText(status, "Counting paused.");
}

static void on_timeout(void *user)
{
    reset_counter();
}

static void on_reset(void *gadget, int32_t a, int32_t b, int32_t c, int32_t d)
{
    reset_counter();
}

static void on_tap(void *gadget, int32_t a, int32_t b, int32_t c, int32_t d)
{
    if (!allowed || taps == 5)
        return;

    taps = taps + 1;
    SBOS_ProgressbarSetValue(progress, taps * 20);
    if (taps < 5)
        return;

    SBOS_ButtonSetText(tap_button, "Full", -1);
    SBOS_GadgetEnabled(tap_button, 0);
    reset_timer = SBOS_CreateTimer();
    if (reset_timer != CGTIMER_INVALID) {
        if (SBOS_TimerSet(reset_timer, 2000, 0, on_timeout, NULL) == 0) {
            SBOS_LabelSetText(status, "Five taps! Resetting...");
            return;
        }
        SBOS_FreeTimer(reset_timer);
        reset_timer = CGTIMER_INVALID;
    }
    SBOS_LabelSetText(status, "Five taps! Use Reset.");
}

static void on_allowed(void *, int32_t, int32_t, int32_t, int32_t);

int main(void)
{
    int window = SBOS_CreateWindow(NULL, 40, 42, 384, 186,
                                   "Tap counter", SBX_WIN_DEFAULT);
    if (window == 0xff)
        return 1;

    status = SBOS_CreateLabel(window, 12, 12, 340, 18, "Tap five times.", GAD_TOOL_DEFAULT);
    progress = SBOS_CreateProgBar(window, 12, 42, 340, 20, GAD_TOOL_DEFAULT);
    CGGadget allow = SBOS_CreateCheckbox(window, 12, 76, 200, 22,
                                          "Allow taps", 1, GAD_TOOL_DEFAULT);
    tap_button = SBOS_CreateButton(window, 12, 114, 150, 28, "Tap +1", GAD_TOOL_DEFAULT);
    CGGadget reset = SBOS_CreateButton(window, 176, 114, 150, 28, "Reset", GAD_TOOL_DEFAULT);
    if (status == 0 || progress == 0 || allow == 0 || tap_button == 0 || reset == 0) {
        SBOS_CloseWindow(window);
        return 2;
    }
    SBOS_ProgressbarSetMinMax(progress, 0, 100);
    SBOS_ProgressbarSetValue(progress, 0);
    if (SBOS_GadgetSetCallBack(tap_button, on_tap, NULL) != 0 ||
        SBOS_GadgetSetCallBack(reset, &on_reset, NULL) != 0 ||
        SBOS_GadgetSetCallBack(allow, NULL, on_allowed) != 0) {
        SBOS_CloseWindow(window);
        return 3;
    }
    return 0;
}

static void on_allowed(void *gadget, int32_t checked, int32_t b, int32_t c, int32_t d)
{
    allowed = checked;
    if (taps == 5)
        return;
    SBOS_GadgetEnabled(tap_button, allowed);
    if (allowed)
        SBOS_LabelSetText(status, "Tap five times.");
    else
        SBOS_LabelSetText(status, "Counting paused.");
}
