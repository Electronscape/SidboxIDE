/* Textarea, textbox, caret, read/write buffer, line counting. */
#include "apis.h"
static CGWindow win;
static CGGadget input;
static CGGadget edit;
static CGGadget label;
static uint8_t text[128];

static void add_line(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    API.gui->gadgets->textarea_insert_text(edit, "\nNative line appended");
    API.gui->gadgets->label_set_text(label, "Appended a line");
}
static void copy_input(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    if (API.gui->gadgets->textbox_get_length(input))
        API.gui->gadgets->label_set_text(label, "Textbox has text");
    else
        API.gui->gadgets->label_set_text(label, "Textbox is empty");
}
static void read_back(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    int count = API.gui->gadgets->textarea_get_text(edit, text, sizeof(text));
    if (count) API.gui->gadgets->label_set_text(label, "Textarea buffer read OK");
    else API.gui->gadgets->label_set_text(label, "Textarea returned empty");
}
static CGWindowProcRes window_proc(CGWindow w, const CGMessage_t *m)
{
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        API.gui->windows->window_close(w);
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}
int main(void)
{
    CGGadget a; CGGadget b; CGGadget c;
    win = API.gui->windows->window_create(&win, 20, 20, 435, 280,
                                         "Native text tools", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    input = API.gui->gadgets->textbox_create(win, 10, 10, 200, 24,
                                            "Text from textbox ", 0, GAD_TOOL_DEFAULT);
    edit = API.gui->gadgets->textarea_create(win, 10, 46, 388, 130,
                                            "Editable text area", 0, GAD_TOOL_DEFAULT);
    a = API.gui->gadgets->button_create(win, 10, 187, 120, 25, "Append line", GAD_TOOL_DEFAULT);
    b = API.gui->gadgets->button_create(win, 139, 187, 115, 25, "Check input", GAD_TOOL_DEFAULT);
    c = API.gui->gadgets->button_create(win, 263, 187, 120, 25, "Read buffer", GAD_TOOL_DEFAULT);
    label = API.gui->gadgets->label_create(win, 10, 223, 380, 18, "Type or press buttons", GAD_TOOL_DEFAULT);
    API.gui->gadgets->set_callback(a, add_line, NULL);
    API.gui->gadgets->set_callback(b, copy_input, NULL);
    API.gui->gadgets->set_callback(c, read_back, NULL);
    return 0;
}
