/* GUI CONTROL PANEL: button, checkbox, slider, progress and callbacks. */
#include "apis.h"

static CGWindow win;
static CGGadget status;
static CGGadget slider;
static CGGadget progress;
static CGGadget check;
static int clicks;

static void activated(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    clicks++;
    if (clicks & 1)
        API.gui->gadgets->label_set_text(status, "Button pressed: ON");
    else
        API.gui->gadgets->label_set_text(status, "Button pressed: OFF");
    API.gui->gadgets->checkbox_set_state(check, clicks & 1);
    API.gui->gadgets->slider_set_value(slider, (clicks * 13) % 101);
    API.gui->gadgets->progressbar_set_value(progress, (clicks * 13) % 101);
}

static void changed(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    int value = API.gui->gadgets->slider_get_value(slider);
    API.gui->gadgets->progressbar_set_value(progress, value);
    if (value > 50)
        API.gui->gadgets->label_set_text(status, "Slider above halfway");
    else
        API.gui->gadgets->label_set_text(status, "Slider below halfway");
}

static CGWindowProcRes window_proc(CGWindow w, const CGMessage_t *msg)
{
    if (msg->mtype == CGMSG_WINDOW && msg->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        API.gui->windows->window_close(w);
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

int main(void)
{
    CGGadget button;
    win = API.gui->windows->window_create(&win, 30, 25, 380, 246,
                                         "Controls: compiler test", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    status = API.gui->gadgets->label_create(win, 12, 12, 335, 20,
                                           "Press button or drag slider", GAD_TOOL_DEFAULT);
    button = API.gui->gadgets->button_create(win, 12, 45, 135, 26,
                                            "Cycle values", GAD_TOOL_DEFAULT);
    check = API.gui->gadgets->checkbox_create(win, 175, 45, 170, 24,
                                               "Button state", 0, GAD_TOOL_DEFAULT);
    slider = API.gui->gadgets->slider_create(win, 12, 95, 310, 20,
                                             0, 0, 100, GAD_TOOL_DEFAULT);
    progress = API.gui->gadgets->progbar_create(win, 12, 140, 310, 19,
                                                GAD_TOOL_DEFAULT);
    API.gui->gadgets->progressbar_set_minmax(progress, 0, 100);
    API.gui->gadgets->set_callback(button, activated, NULL);
    API.gui->gadgets->set_callback(slider, NULL, changed);
    return 0;
}
