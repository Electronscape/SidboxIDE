/* Menus, dialog boxes and menu callbacks. Close the window to quit. */
#include "apis.h"
static CGWindow win;
static CGGadget status;
static int menu;
static int about_item;
static int info_item;
static int ask_item;

static void selected(int m, int item, void *user)
{
    if (item == about_item) {
        API.gui->dialogs->messagebox(win, "About", "Native C compiler menu works!", MSGBOXF_OK);
        API.gui->gadgets->label_set_text(status, "About selected");
    } else if (item == info_item) {
        API.gui->dialogs->infobox(win, "Information", "Compiled on Sidbox.");
        API.gui->gadgets->label_set_text(status, "Information selected");
    } else {
        API.gui->dialogs->messagebox(win, "Question", "Still testing the GUI?", MSGBOXF_OKCANCEL);
        API.gui->gadgets->label_set_text(status, "Question selected");
    }
}

static void button_pressed(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    API.gui->dialogs->messagebox(win, "Hello!", "A compiled button invoked a native dialog.", MSGBOXF_OK);
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
    CGGadget b;
    win = API.gui->windows->window_create(&win, 45, 35, 370, 210,
                                         "Menu and dialogs", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    status = API.gui->gadgets->label_create(win, 15, 15, 305, 22,
                                           "Open the Tests menu", GAD_TOOL_DEFAULT);
    b = API.gui->gadgets->button_create(win, 15, 60, 180, 30,
                                       "Open a dialog", GAD_TOOL_DEFAULT);
    API.gui->gadgets->set_callback(b, button_pressed, NULL);
    menu = API.gui->menus->create_title("Tests");
    about_item = API.gui->menus->create_item(&menu, 0, "About");
    info_item = API.gui->menus->create_item(&menu, 0, "Info box");
    ask_item = API.gui->menus->create_item(&menu, 0, "Question");
    API.gui->menus->set_callback(about_item, selected, NULL);
    API.gui->menus->set_callback(info_item, selected, NULL);
    API.gui->menus->set_callback(ask_item, selected, NULL);
    API.gui->menus->attach_to_window(menu, win);
    return 0;
}
