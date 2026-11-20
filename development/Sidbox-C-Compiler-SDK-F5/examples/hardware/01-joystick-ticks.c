/* Read-only hardware EBI test: joystick bits + raw getTicks hex display.
 * Does not enter game mode or touch any framebuffer.
 */
#include "apis.h"
static CGWindow win;
static CGGadget result;
static CGGadget decoded;
static uint8_t timer;
static uint8_t info[22];

static void update(void *unused)
{
    int joy = API.hwl->getjoyport();
    int ticks = API.hwl->getTicks();
    int digit; int i;
    digit = (joy >> 4) & 15;
    if (digit < 10) info[4] = '0' + digit;
    else info[4] = 'A' + digit - 10;
    digit = joy & 15;
    if (digit < 10) info[5] = '0' + digit;
    else info[5] = 'A' + digit - 10;
    for (i = 0; i < 8; i++) {
        digit = (ticks >> ((7 - i) * 4)) & 15;
        if (digit < 10) info[13 + i] = '0' + digit;
        else info[13 + i] = 'A' + digit - 10;
    }
    API.gui->gadgets->label_set_text(result, info);
    if (joy & 1) API.gui->gadgets->label_set_text(decoded, "FIRE");
    else if (joy & 2) API.gui->gadgets->label_set_text(decoded, "FIRE 2");
    else if (joy & 4) API.gui->gadgets->label_set_text(decoded, "UP");
    else if (joy & 8) API.gui->gadgets->label_set_text(decoded, "DOWN");
    else if (joy & 16) API.gui->gadgets->label_set_text(decoded, "LEFT");
    else if (joy & 32) API.gui->gadgets->label_set_text(decoded, "RIGHT");
    else API.gui->gadgets->label_set_text(decoded, "No direction/button");
}
static CGWindowProcRes window_proc(CGWindow w, const CGMessage_t *m)
{
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        API.gui->timers->cancel(timer);
        API.gui->timers->free(timer);
        API.gui->windows->window_close(w);
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}
int main(void)
{
    int i;
    win = API.gui->windows->window_create(&win, 40, 30, 395, 200,
                                         "Hardware joystick / ticks monitor", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    result = API.gui->gadgets->label_create(win, 14, 22, 360, 24,
                                           "Starting...", GAD_TOOL_DEFAULT);
    decoded = API.gui->gadgets->label_create(win, 14, 72, 340, 24,
                                            "Press joystick buttons", GAD_TOOL_DEFAULT);
    info[0]='J'; info[1]='O'; info[2]='Y'; info[3]=' ';
    info[6]=' '; info[7]='T'; info[8]='I'; info[9]='C'; info[10]='K'; info[11]='S'; info[12]=' ';
    for (i = 4; i < 6; i++) info[i]='0';
    for (i = 13; i < 21; i++) info[i]='0';
    info[21]=0;
    timer = API.gui->timers->create();
    if (timer == CGTIMER_INVALID) { API.gui->windows->window_close(win); return 2; }
    /* Timer-set return-code convention is not assumed by this test. */
    API.gui->timers->set(timer, 100, 100, update, NULL);
    return 0;
}
