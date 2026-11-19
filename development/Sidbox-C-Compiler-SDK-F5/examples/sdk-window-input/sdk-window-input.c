#include "apis.h"

static CGWindow window = 0xff;
static CGGadget hint;
static CGGadget marker;
static CGGadget left_button;
static CGGadget right_button;
static int marker_x = 144;
static int marker_limit = 340;

static void move_marker(int step)
{
    int next = marker_x + step;
    if (next < 12)
        next = 12;
    if (next > marker_limit)
        next = marker_limit;
    if (next == marker_x)
        return;

    SBOS_GadgetRepaint(marker);
    marker_x = next;
    SBOS_GadgetMove(marker, marker_x, 48);
    SBOS_GadgetRepaint(marker);
}

static CGWindowProcRes on_window(CGWindow win, const CGMessage_t *m)
{
    if (m == NULL || m->winhnd != win)
        return CGPROC_DEFAULT;

    if (m->mtype == CGMSG_WINDOW) {
        if (m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
            SBOS_CloseWindow(win);
            return CGPROC_HANDLED;
        }
        if (m->eventClass == CGEVT_WIN_RESIZED) {
            marker_limit = m->a - 40;
            if (marker_limit < 12)
                marker_limit = 12;
            int hint_width = m->a - 26;
            if (hint_width > 0) {
                SBOS_GadgetRepaint(hint);
                SBOS_GadgetResize(hint, hint_width, 18);
                SBOS_GadgetRepaint(hint);
            }
            move_marker(0);
        }
    }

    if (m->mtype == CGMSG_KEY && m->eventClass == CGEVT_KEY_PRESSED) {
        if (m->a == 'a' || m->a == 'A') {
            move_marker(-16);
            return CGPROC_HANDLED;
        }
        if (m->a == 'd' || m->a == 'D') {
            move_marker(16);
            return CGPROC_HANDLED;
        }
    }

    if (m->mtype == CGMSG_GADGET && m->eventClass == CGEVT_GAD_ACTIVATED) {
        if (m->gadget == left_button) {
            move_marker(-16);
            return CGPROC_HANDLED;
        }
        if (m->gadget == right_button) {
            move_marker(16);
            return CGPROC_HANDLED;
        }
    }
    return CGPROC_DEFAULT;
}

int main(void)
{
    if (SBOS_CreateWindow(&window, 45, 48, 380, 180, "Window input", SBX_WIN_DEFAULT) == 0xff)
        return 1;

    hint = SBOS_CreateLabel(window, 12, 12, 354, 18, "Press A or D, or tap Left / Right",
                            GAD_TOOL_DEFAULT);
    marker = SBOS_CreateLabel(window, marker_x, 48, 28, 18, "[X]", GAD_TOOL_DEFAULT);
    left_button = SBOS_CreateButton(window, 12, 90, 76, 26, "Left", GAD_TOOL_DEFAULT);
    right_button = SBOS_CreateButton(window, 100, 90, 76, 26, "Right", GAD_TOOL_DEFAULT);
    if (hint == 0 || marker == 0 || left_button == 0 || right_button == 0) {
        SBOS_CloseWindow(window);
        return 2;
    }

    SBOS_SetWindowProc(window, on_window);
    SBOS_WindowSetApplicationTitle(window, "Window input");
    SBOS_WindowToFront(window);
    SBOS_WindowSetFocus(window);
    return 0;
}
