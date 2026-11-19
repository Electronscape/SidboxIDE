#include "apis.h"

/* Linked into each generated applet. The loader's normal window ownership
 * keeps the image alive until the user closes its primary window. */
int sidbox_message(const char *message)
{
    CGWindow win = SBOS_CreateWindow(NULL, 24, 58, 432, 124, "C program",
        SBX_WF_VISIBLE | SBX_WF_CLOSE | SBX_WF_TITLE_BAR |
        SBX_WF_MOVEABLE | SBX_WF_SCREENBOUND);
    if (win == 0xffu || win == 0u)
        return -1;
    if (SBOS_CreateLabel(win, 8, 8, 404, 76, message, GAD_TOOL_DEFAULT) == 0) {
        SBOS_CloseWindow(win);
        return -1;
    }
    return (int)win;
}

int sidbox_ticks(void)
{
    return (int)getTicks();
}

int sidbox_buttons(void)
{
    return (int)getjoyport();
}
