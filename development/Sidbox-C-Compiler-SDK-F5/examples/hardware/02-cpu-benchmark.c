/* Hardware timing demonstration: executes 25,000 integer rounds on a button
 * and displays the difference between two getTicks() readings in hexadecimal.
 * Raw clock units are deliberately not called milliseconds or CPU cycles.
 */
#include "apis.h"
static CGWindow win;
static CGGadget result;
static uint8_t display[20];
static int checksum;

static void bench(void *g, int32_t a, int32_t b, int32_t c, int32_t d)
{
    int start = API.hwl->getTicks();
    int i; int n = checksum + 7; int end; int delta; int digit;
    for (i = 0; i < 25000; i++) n = ((n * 33) ^ (n >> 3)) + i;
    checksum = n;
    end = API.hwl->getTicks();
    delta = end - start;
    for (i = 0; i < 8; i++) {
        digit = (delta >> ((7 - i) * 4)) & 15;
        if (digit < 10) display[10 + i] = '0' + digit;
        else display[10 + i] = 'A' + digit - 10;
    }
    API.gui->gadgets->label_set_text(result, display);
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
    int i;
    CGGadget button;
    win = API.gui->windows->window_create(&win, 40, 35, 380, 195,
                                         "Integer benchmark", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    button = API.gui->gadgets->button_create(win, 16, 20, 185, 30,
                                            "Run 25,000 rounds", GAD_TOOL_DEFAULT);
    result = API.gui->gadgets->label_create(win, 16, 70, 320, 22,
                                           "Press button to benchmark", GAD_TOOL_DEFAULT);
    display[0]='R'; display[1]='A'; display[2]='W'; display[3]=' ';
    display[4]='T'; display[5]='I'; display[6]='C'; display[7]='K'; display[8]='S'; display[9]=' ';
    for (i = 10; i < 18; i++) display[i]='0';
    display[18]=0;
    API.gui->gadgets->set_callback(button, bench, NULL);
    return 0;
}
