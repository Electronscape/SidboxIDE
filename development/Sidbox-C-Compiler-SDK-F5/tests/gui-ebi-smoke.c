#include "apis.h"

static CGWindow window;
static CGGadget status;
static CGGadget slider;
static CGGadget textbox;
static int menubar;
static int menuitem;

static void on_button(void *gadget, int32_t a, int32_t b, int32_t c, int32_t d)
{
    API.gui->gadgets->label_set_text(status, "Button callback OK");
}

static void on_menu(int menu, int item, void *userdata)
{
    API.gui->dialogs->messagebox(window, "Menus", "Menu callback OK", MSGBOXF_OK);
}

static CGWindowProcRes on_window(CGWindow win, const CGMessage_t *message)
{
    if (message->mtype == CGMSG_WINDOW && message->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        API.gui->windows->window_close(win);
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

int main(void)
{
    CGGadget button;
    window = API.gui->windows->window_create(&window, 35, 30, 395, 245,
               "Native GUI EBI test", SBX_WIN_DEFAULT);
    if (!window) return 1;
    API.gui->windows->set_proc(window, on_window);

    status = API.gui->gadgets->label_create(window, 10, 10, 270, 18,
               "New GUI bindings loaded", GAD_TOOL_DEFAULT);
    button = API.gui->gadgets->button_create(window, 10, 44, 130, 24,
               "Click me", GAD_TOOL_DEFAULT);
    API.gui->gadgets->set_callback(button, on_button, NULL);

    slider = API.gui->gadgets->slider_create(window, 10, 92, 245, 18,
               0, 0, 100, GAD_TOOL_DEFAULT);
    API.gui->gadgets->slider_set_value(slider, 42);
    textbox = API.gui->gadgets->textbox_create(window, 10, 130, 180, 24,
               "Text input", 0, GAD_TOOL_DEFAULT);
    API.gui->gadgets->textbox_set_caret(textbox, 4);

    menubar = API.gui->menus->create_title("Actions");
    menuitem = API.gui->menus->create_item(&menubar, 0, "Show dialog");
    API.gui->menus->set_callback(menuitem, on_menu, NULL);
    API.gui->menus->attach_to_window(menubar, window);
    return 0;
}
