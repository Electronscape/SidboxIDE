#include "apis.h"
static CGWindow window;
static CGWindowProcRes window_proc(CGWindow w, const CGMessage_t *msg)
{
    if (msg->mtype == CGMSG_WINDOW && msg->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        API.gui->windows->window_close(w);
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}
static uint8_t scratch[524288] = {0};
int main(void)
{
    CGGadget info;
    int passed = (scratch[0] == 0 && scratch[262144] == 0 && scratch[524287] == 0);
    scratch[262144] = 97;
    if (scratch[262144] != 97) passed = 0;
    window = API.gui->windows->window_create(&window, 28, 30, 398, 148,
        "Large BSS buffer", SBX_WIN_DEFAULT);
    if (!window) return 2;
    API.gui->windows->set_proc(window, window_proc);
    if (passed)
        info = API.gui->gadgets->label_create(window, 14, 22, 360, 30,
            "PASS: 512 KiB RAM array verified", GAD_TOOL_DEFAULT);
    else
        info = API.gui->gadgets->label_create(window, 14, 22, 360, 30,
            "FAIL: large RAM array mismatch", GAD_TOOL_DEFAULT);
    return passed ? 0 : 3;
}
