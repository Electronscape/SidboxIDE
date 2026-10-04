#ifndef SBAPI_WINDOW_H
#define SBAPI_WINDOW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t CGWindow;
typedef uint32_t CGGadget;

typedef uint32_t CGMsgType;
#define CGMSG_NONE                  0x00u
#define CGMSG_GADGET                0x10u
#define CGMSG_WINDOW                0x20u
#define CGMSG_TIMER                 0x30u
#define CGMSG_MOUSE                 0x40u
#define CGMSG_KEY                   0x50u
#define CGMSG_SYSTEM                0x60u
#define CGMSG_MENU                  0x70u

typedef uint32_t CGEventType;

#define CGEVT_GAD_PRESSED           0x100u
#define CGEVT_GAD_ACTIVATED         0x101u
#define CGEVT_GAD_FOCUS_LOST        0x102u
#define CGEVT_GAD_FOCUS_GAINED      0x103u
#define CGEVT_GAD_KEY               0x104u
#define CGEVT_GAD_MOUSE_MOVE        0x105u
#define CGEVT_GAD_MOUSE_DOWN        CGEVT_GAD_PRESSED
#define CGEVT_GAD_MOUSE_UP          0x107u

#define CGEVT_GAD_GRID_CHANGED      0x200u
#define CGEVT_GAD_LISTBOX_CHANGED   0x300u
#define CGEVT_GAD_LISTBOX_SCROLLED  0x301u
#define CGEVT_GAD_RADIO_CHANGED     0x400u
#define CGEVT_GAD_CHECKBOX_CHANGED  0x500u
#define CGEVT_GAD_SLIDERVAL_CHANGED 0x600u
#define CGEVT_GAD_CARET_MOVED       0x700u
#define CGEVT_GAD_TEXT_CHANGED      CGEVT_GAD_CARET_MOVED
#define CGEVT_GAD_KEYPRESS_DOWN     0x702u
#define CGEVT_GAD_KEYPRESS_UP       0x703u
#define CGEVT_GAD_KEYPRESSED        0x704u

#define CGEVT_MENU_SELECTED         0x900u

#define CGEVT_WIN_CLOSE_REQUEST     0x1000u
#define CGEVT_WIN_MOVE              0x1001u
#define CGEVT_WIN_MOVED             0x1002u
#define CGEVT_WIN_RESIZE            0x1003u
#define CGEVT_WIN_RESIZED           0x1004u
#define CGEVT_WIN_ZORDER            0x1005u
#define CGEVT_WIN_MAXRESTORED       0x1006u
#define CGEVT_WIN_MINIMISE          0x1007u
#define CGEVT_WIN_GOTFOCUS          0x1008u
#define CGEVT_WIN_LOSTFOCUS         0x1010u

#define CGEVT_KEY_PRESSED           0x2000u
#define CGEVT_KEY_RELEASED          0x2001u

#define CGEVT_SYS_FILERQ_DONE       0x8000u
#define CGEVT_SYS_FILERQ_CHANGED    0x8001u
#define CGEVT_SYS_MSGBOX_DONE       0x8002u
#define CGEVT_SYS_INFOBOX_DONE      0x8003u
#define CGEVT_SYS_REPAINT           0x8004u

typedef struct CGMessage_t {
    CGMsgType       mtype;
    CGWindow        winhnd;
    CGGadget        gadget;
    CGEventType     eventClass;
    int32_t         a, b, c, d;
} CGMessage_t;

#define MSG_PTR(p)      ((int32_t)(uintptr_t)(p))
#define MSG_AS_PTR(t,p) ((t*)(uintptr_t)(p))

typedef enum {
    CGPROC_DEFAULT = 0x00u,
    CGPROC_NORMAL  = 0x01u,
    CGPROC_HANDLED = 0xF0u,
    CGPROC_END     = 0xFFu
} CGWindowProcRes;

typedef CGWindowProcRes (*MSGWndProc)(CGWindow win, const CGMessage_t *m);

//// API ----------------------------------------------------------------------------------------------------
#define    SBX_WF_VISIBLE          0x00000001u   // window button frame settings
#define    SBX_WF_NOBORDER         0x00000002u
#define    SBX_WF_CLOSE            0x00000004u
#define    SBX_WF_TITLE_BAR        0x00000008u
#define    SBX_WF_TITLE_BAR_FLAT   0x00000010u
#define    SBX_WF_ZORDER           0x00000020u
#define    SBX_WF_MINIMISE         0x00000040u
#define    SBX_WF_MAXRESTORE       0x00000080u
#define    SBX_WF_SCREENBOUND      0x00000100u  // window behaviour
#define    SBX_WF_MOVEABLE         0x00000200u
#define    SBX_WF_RESIZABLE        0x00000400u
#define    SBX_WF_NOFOCUS          0x00000800u
#define    SBX_WF_NOAUTOZORDER     0x00001000u
#define    SBX_WF_ALWAYS_TO_BACK   0x00002000u
#define    SBX_WF_ALWAYS_TO_FRONT  0x00004000u
#define    SBX_WF_DOCKRIGHT        0x00008000u
#define    SBX_WF_DOCKBOTTOM       0x00010000u
#define    SBX_WF_DISABLE          0x00020000u

#define    SBX_WF_BASE_ZERO        (SBX_WF_VISIBLE | SBX_WF_ALWAYS_TO_BACK | SBX_WF_NOBORDER | SBX_WF_TITLE_BAR_FLAT) // For a blank window

#define    SBX_WIN_DEFAULT         (SBX_WF_MOVEABLE   |\
                                    SBX_WF_VISIBLE    |\
                                    SBX_WF_CLOSE      |\
                                    SBX_WF_TITLE_BAR  |\
                                    SBX_WF_ZORDER     |\
                                    SBX_WF_MINIMISE   |\
                                    SBX_WF_MAXRESTORE |\
                                    SBX_WF_RESIZABLE  |\
                                    SBX_WF_SCREENBOUND)



typedef struct {
    CGWindow (*window_create) (CGWindow *WinHandle, int16_t x, int16_t y, uint16_t width, uint16_t height, const char *title, uint32_t flags);
    void     (*window_close)  (CGWindow id);
    void     (*set_proc)      (CGWindow win, MSGWndProc proc);
    void     (*to_front)      (CGWindow id);
    void     (*to_back)       (CGWindow id);
    void     (*set_focus)     (CGWindow id);
    void     (*set_app_title) (CGWindow win, const char *newtext);
    void     (*busymouse)            (void);
    void     (*normalmouse)          (void);
    void     (*window_mouse_busy)    (CGWindow win, uint8_t busy);
    uint8_t  (*window_mouse_is_busy) (CGWindow win);
} API_GUI_Windows;


///////////-------------- HELPERS -----------------//////
/////////////////// API SYSTEM LEVEL ################
#define GUICoderGirl      (API->gui)
/////////////////////////////////////////////////////////

#define SBOS_CreateWindow(...)  (GUICoderGirl->windows->window_create(__VA_ARGS__))
#define SBOS_CloseWindow(id)    (GUICoderGirl->windows->window_close(id))
#define SBOS_SetWindowProc(win, proc) (GUICoderGirl->windows->set_proc(win, proc))
#define SBOS_WindowToFront(id)  (GUICoderGirl->windows->to_front(id))
#define SBOS_WindowToBack(id)   (GUICoderGirl->windows->to_back(id))
#define SBOS_WindowSetFocus(id) (GUICoderGirl->windows->set_focus(id))
#define SBOS_WindowSetApplicationTitle(win, text) (GUICoderGirl->windows->set_app_title(win, text))
#define SetApplicationTitle(win, text)            SBOS_WindowSetApplicationTitle(win, text)
#define SetMouseBusy()          (GUICoderGirl->windows->busymouse())
#define SetMouseNormal()        (GUICoderGirl->windows->normalmouse())
#define WindowMouseBusy(win, busy)   (GUICoderGirl->windows->window_mouse_busy((win), (busy)))
#define WindowMouseIsBusy(win)       (GUICoderGirl->windows->window_mouse_is_busy(win))


#ifdef __cplusplus
}
#endif
#endif
