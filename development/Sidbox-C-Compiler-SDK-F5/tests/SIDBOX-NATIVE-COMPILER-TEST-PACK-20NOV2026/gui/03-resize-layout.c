/* Window resize event, gadget move/resize, focus and window titles. */
#include "apis.h"
static CGWindow win;
static CGGadget caption;
static CGGadget anchored;
static CGGadget textbox;

static void clicked(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    API.gui->windows->set_app_title(win, "Button callback OK");
    API.gui->gadgets->set_focus(textbox);
    API.gui->gadgets->label_set_text(caption, "Textbox has focus");
}

static CGWindowProcRes window_proc(CGWindow w, const CGMessage_t *m)
{
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        API.gui->windows->window_close(w);
        return CGPROC_HANDLED;
    }
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_RESIZED) {
        /* The SDK reports window resize dimensions in event parameters. */
        int width = m->a;
        int height = m->b;
        if (width < 150) width = 150;
        if (height < 100) height = 100;
        API.gui->gadgets->move(anchored, width - 150, height - 88);
        API.gui->gadgets->resize(caption, width - 32, 20);
    }
    return CGPROC_DEFAULT;
}

int main(void)
{
    win = API.gui->windows->window_create(&win, 35, 25, 370, 240,
                                         "Resize me", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    caption = API.gui->gadgets->label_create(win, 15, 12, 320, 20,
                                            "Resize this window; button follows", GAD_TOOL_DEFAULT);
    textbox = API.gui->gadgets->textbox_create(win, 15, 52, 185, 24,
                                              "Type here", 0, GAD_TOOL_DEFAULT);
    anchored = API.gui->gadgets->button_create(win, 205, 146, 130, 25,
                                               "Focus textbox", GAD_TOOL_DEFAULT);
    API.gui->gadgets->set_callback(anchored, clicked, NULL);
    return 0;
}
