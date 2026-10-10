/* SIDBOX relocatable dual GUI test - EXPERIMENTAL STAGE 4.
 * This deliberately avoids newlib, malloc and the normal v1 startup.
 * It should create a window with a Button and Label; clicking changes the Label.
 * Both label storage and callback code live inside the relocatable image.
 */
#include <stdint.h>
#include "apis.h"

/* The V2 SDK's SIDBOX_API_BASE remains fixed at 0x2001F000;
 * no override necessary. This deliberately tests the public SDK macro. */

#define CGWIN_INVALID ((CGWindow)0xFFu)
static CGWindow demo_window = CGWIN_INVALID;
static CGGadget demo_button;
static CGGadget demo_label;
static volatile uint32_t click_count;
#ifdef STAGE4_APP_A
static char msg_before[] = "APP A: press the button";
static char msg_after[] = "APP A CALLBACK OK!";
static char title[] = "V2 APP A - independent";
static char button_text[] = "CLICK A!";
#define DEMO_X 24
#define DEMO_Y 22
#elif defined(STAGE4_APP_B)
static char msg_before[] = "APP B: press the button";
static char msg_after[] = "APP B CALLBACK OK!";
static char title[] = "V2 APP B - independent";
static char button_text[] = "CLICK B!";
#define DEMO_X 125
#define DEMO_Y 95
#else
#error "Build with STAGE4_APP_A or STAGE4_APP_B"
#endif

static CGWindowProcRes demo_proc(CGWindow win, const CGMessage_t *m)
{
    if (!m) return CGPROC_DEFAULT;
    if (m->mtype == CGMSG_GADGET &&
        (m->eventClass == CGEVT_GAD_PRESSED || m->eventClass == CGEVT_GAD_ACTIVATED) &&
        m->gadget == demo_button) {
        ++click_count;
        /* This is the real CoderGirl GUI text API, not a local mock. */
        SBOS_LabelSetText(demo_label, msg_after);
        return CGPROC_HANDLED;
    }
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        SBOS_CloseWindow(win);
        demo_window = CGWIN_INVALID;
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

/* Set up a relocated function pointer in .data, forcing one R_ARM_RELATIVE. */
static MSGWndProc volatile demo_callback = demo_proc;

__attribute__((visibility("hidden")))
int applet_entry(int argc, char **argv)
{
    (void)argc; (void)argv;
    if (demo_window != CGWIN_INVALID) return 0;
    CGWindow h = CGWIN_INVALID;
    SBOS_CreateWindow(&h, DEMO_X, DEMO_Y, 290, 150, title,
                      SBX_WF_VISIBLE | SBX_WF_CLOSE |
                      SBX_WF_TITLE_BAR | SBX_WF_MOVEABLE | SBX_WF_ZORDER);
    if (h == CGWIN_INVALID) return 31;
    demo_window = h;
    SBOS_SetWindowProc(h, demo_callback);
    demo_label = SBOS_CreateLabel(h, 20, 42, 245, 20, msg_before, GAD_TOOL_DEFAULT);
    demo_button = SBOS_CreateButton(h, 20, 84, 105, 26, button_text, GAD_TOOL_DEFAULT);
    SBOS_WindowToFront(h);
    return 0;
}
