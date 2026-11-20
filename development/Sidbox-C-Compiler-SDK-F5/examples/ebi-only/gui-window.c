/* SDK-only EBI GUI example. The OS owns the event loop and applet lifetime. */
#include "apis.h"

static int window_id = 255;

static void close_clicked(void *gadget, int32_t a, int32_t b, int32_t c, int32_t d)
{
    API.gui->windows->window_close(window_id);
}

int main(void)
{
    int heading;
    int message;
    int close_button;

    window_id = API.gui->windows->window_create(
        NULL, 70, 48, 340, 176, "SIDBOX EBI-only GUI", SBX_WIN_DEFAULT);
    if (window_id == 255)
        return 1;

    heading = API.gui->gadgets->label_create(
        window_id, 16, 24, 308, 22,
        "Hello from the SIDBOX C compiler!", GAD_TOOL_DEFAULT);
    message = API.gui->gadgets->label_create(
        window_id, 16, 56, 308, 22,
        "This window stays open until you close it.", GAD_TOOL_DEFAULT);
    close_button = API.gui->gadgets->button_create(
        window_id, 16, 100, 122, 26,
        "Close window", GAD_TOOL_DEFAULT);

    if (!heading || !message || !close_button) {
        API.gui->windows->window_close(window_id);
        return 2;
    }

    if (API.gui->gadgets->set_callback(close_button, close_clicked, NULL) != 0) {
        API.gui->windows->window_close(window_id);
        return 3;
    }

    API.gui->windows->to_front(window_id);
    API.gui->windows->set_focus(window_id);
    return 0;
}
