#include "apis.h"
#include "apicore.h"

#include <stddef.h>

typedef uint8_t (*CreateWindow)(uint8_t *, int16_t, int16_t, uint16_t, uint16_t,
                                const char *, uint32_t);
typedef uint32_t (*CreateTextGadget)(uint8_t, int16_t, int16_t, int16_t, int16_t,
                                     const char *, uint32_t);
typedef uint32_t (*CreateTextOptionGadget)(uint8_t, int16_t, int16_t, int16_t, int16_t,
                                           const char *, uint8_t, uint32_t);
typedef uint32_t (*CreateProgressBar)(uint8_t, int16_t, int16_t, int16_t, int16_t,
                                      uint32_t);

/* Keep the export tied to the real SDK argument and return widths. */
#define CHECK_SIGNATURE(table, member, signature) \
    _Static_assert(__builtin_types_compatible_p(__typeof__(((table *)0)->member), signature), \
                   "Update the compiler binding for the new " #member " signature")

CHECK_SIGNATURE(API_GUI_Windows, window_create, CreateWindow);
CHECK_SIGNATURE(API_GUI_GADGETS, label_create, CreateTextGadget);
CHECK_SIGNATURE(API_GUI_GADGETS, button_create, CreateTextGadget);
CHECK_SIGNATURE(API_GUI_GADGETS, checkbox_create, CreateTextOptionGadget);
CHECK_SIGNATURE(API_GUI_GADGETS, textbox_create, CreateTextOptionGadget);
CHECK_SIGNATURE(API_GUI_GADGETS, progbar_create, CreateProgressBar);
CHECK_SIGNATURE(API_GUI_GADGETS, label_set_text, uint32_t (*)(uint32_t, const char *));
CHECK_SIGNATURE(API_GUI_GADGETS, textbox_set_text, void (*)(uint32_t, const char *));
CHECK_SIGNATURE(API_GUI_GADGETS, checkbox_set_state, void (*)(uint32_t, uint8_t));
CHECK_SIGNATURE(API_GUI_GADGETS, checkbox_get_state, int8_t (*)(uint32_t));
CHECK_SIGNATURE(API_GUI_GADGETS, progressbar_set_minmax, void (*)(uint32_t, int16_t, int16_t));
CHECK_SIGNATURE(API_GUI_GADGETS, progressbar_set_value, void (*)(uint32_t, int16_t));
CHECK_SIGNATURE(API_GUI_GADGETS, set_focus, void (*)(uint32_t));
CHECK_SIGNATURE(API_GUI_GADGETS, set_callback, uint32_t (*)(uint32_t, fnCallback, fnCallback));
CHECK_SIGNATURE(API_GUI_GADGETS, enabled, void (*)(uint32_t, uint8_t));
CHECK_SIGNATURE(API_GUI_GADGETS, button_set_text, void (*)(uint32_t, const char *, int8_t));
CHECK_SIGNATURE(API_GUI_Windows, window_close, void (*)(uint8_t));
CHECK_SIGNATURE(API_SYS_TIMERS, create, uint8_t (*)(void));
CHECK_SIGNATURE(API_SYS_TIMERS, set, int (*)(uint8_t, uint32_t, uint32_t, SBOS_TimerCB, void *));
CHECK_SIGNATURE(API_SYS_TIMERS, cancel, void (*)(uint8_t));
CHECK_SIGNATURE(API_SYS_TIMERS, free, void (*)(uint8_t));
CHECK_SIGNATURE(API_GUI_Windows, set_proc, void (*)(CGWindow, MSGWndProc));
CHECK_SIGNATURE(API_GUI_Windows, to_front, void (*)(CGWindow));
CHECK_SIGNATURE(API_GUI_Windows, set_focus, void (*)(CGWindow));
CHECK_SIGNATURE(API_GUI_Windows, set_app_title, void (*)(CGWindow, const char *));
CHECK_SIGNATURE(API_GUI_GADGETS, move, void (*)(CGGadget, int16_t, int16_t));
CHECK_SIGNATURE(API_GUI_GADGETS, resize, void (*)(CGGadget, int16_t, int16_t));
CHECK_SIGNATURE(API_GUI_GADGETS, repaint, void (*)(CGGadget));
CHECK_SIGNATURE(API_GUI_GADGETS, bitmapview_create,
                CGGadget (*)(CGWindow, int16_t, int16_t, int16_t, int16_t,
                             int16_t, int16_t, uint32_t, GAD_TOOL_FLAGS));
CHECK_SIGNATURE(API_GUI_GADGETS, bitmapview_set_bitmap, void (*)(CGGadget, void *));
CHECK_SIGNATURE(API_GUI_GADGETS, bitmapview_set_size, void (*)(CGGadget, uint16_t, uint16_t));
CHECK_SIGNATURE(API_GUI_GADGETS, canvas_create,
                CGGadget (*)(CGWindow, int16_t, int16_t, int16_t, int16_t, CNV_FLAGS_T, GAD_TOOL_FLAGS));
CHECK_SIGNATURE(API_GUI_GADGETS, set_fpen, void (*)(CGGadget, uint8_t));
CHECK_SIGNATURE(API_GUI_GADGETS, set_bpen, void (*)(CGGadget, uint8_t));
_Static_assert(__builtin_types_compatible_p(fnCallback,
                   void (*)(void *, int32_t, int32_t, int32_t, int32_t)),
               "Update the gadget callback signature");
_Static_assert(__builtin_types_compatible_p(SBOS_TimerCB, void (*)(void *)),
               "Update the timer callback signature");
_Static_assert(__builtin_types_compatible_p(MSGWndProc,
                   CGWindowProcRes (*)(CGWindow, const CGMessage_t *)),
               "Update the window callback signature");
_Static_assert(sizeof(CGWindowProcRes) == 1 && (CGWindowProcRes)-1 == UINT8_MAX,
               "The compiler emits an unsigned byte result for window callbacks");
#define CHECK_FIELD(field, type) \
    _Static_assert(__builtin_types_compatible_p(__typeof__(((CGMessage_t *)0)->field), type), \
                   "Update the window message binding for " #field)
CHECK_FIELD(mtype, uint32_t);
CHECK_FIELD(winhnd, uint8_t);
CHECK_FIELD(gadget, uint32_t);
CHECK_FIELD(eventClass, uint32_t);
CHECK_FIELD(a, int32_t);
CHECK_FIELD(b, int32_t);
CHECK_FIELD(c, int32_t);
CHECK_FIELD(d, int32_t);
_Static_assert(sizeof(CGMessage_t) <= 4096, "Window message exceeds immediate offset range");
_Static_assert(sizeof(void *) == 4, "Export with ARM GCC");
_Static_assert((uintptr_t)NULL == 0, "The SDK requires a zero null pointer");

/* Shared CGWindow, x, y, width and height arguments for gadget creation. */
#define GADGET_BOUNDS SIDC_API_U8, SIDC_API_S16, SIDC_API_S16, SIDC_API_S16, SIDC_API_S16
#define GUI_OFFSETS(group, table, member) \
    {offsetof(API_Root, gui), offsetof(API_GUI, group), offsetof(table, member)}
#define GUI_CALL(group, table, sdk_name, member, return_type, ...) \
    {.name = #sdk_name, \
     .offsets = GUI_OFFSETS(group, table, member), \
     .arity = sizeof((uint8_t[]){__VA_ARGS__}), \
     .result = return_type, .params = {__VA_ARGS__}}
#define GADGET_CALL(sdk_name, member, return_type, ...) \
    GUI_CALL(gadgets, API_GUI_GADGETS, sdk_name, member, return_type, __VA_ARGS__)
#define SDK_CONSTANT(name) {#name, name}

enum { CALL_COUNT = 34, CONSTANT_COUNT = 37 };
_Static_assert((unsigned)CALL_COUNT <= SIDC_API_CALLS &&
                   (unsigned)CONSTANT_COUNT <= SIDC_API_CONSTANTS,
               "API export exceeds compiler capacity");

static const struct {
    SidcApiHeader header;
    SidcApiCall calls[CALL_COUNT];
    SidcApiConstant constants[CONSTANT_COUNT];
    SidcApiMessage message;
} apicore __attribute__((section(".sidc_apicore"), used)) = {
    .header = {SIDC_APICORE_MAGIC, SIDBOX_API_BASE, CALL_COUNT, CONSTANT_COUNT},
    .calls = {
        {
            .name = "SBOS_CreateWindow",
            .offsets = GUI_OFFSETS(windows, API_GUI_Windows, window_create),
            .arity = 7,
            .result = SIDC_API_U8,
            .params = {SIDC_API_WINDOW_REF, SIDC_API_S16, SIDC_API_S16, SIDC_API_U16,
                       SIDC_API_U16, SIDC_API_STRING, SIDC_API_U32}
        },
        GADGET_CALL(SBOS_CreateLabel, label_create, SIDC_API_U32,
                    GADGET_BOUNDS, SIDC_API_STRING, SIDC_API_U32),
        GADGET_CALL(SBOS_CreateButton, button_create, SIDC_API_U32,
                    GADGET_BOUNDS, SIDC_API_STRING, SIDC_API_U32),
        GADGET_CALL(SBOS_CreateCheckbox, checkbox_create, SIDC_API_U32,
                    GADGET_BOUNDS, SIDC_API_STRING, SIDC_API_U8, SIDC_API_U32),
        GADGET_CALL(SBOS_CreateTextBox, textbox_create, SIDC_API_U32,
                    GADGET_BOUNDS, SIDC_API_STRING, SIDC_API_U8, SIDC_API_U32),
        GADGET_CALL(SBOS_CreateProgBar, progbar_create, SIDC_API_U32,
                    GADGET_BOUNDS, SIDC_API_U32),
        GADGET_CALL(SBOS_LabelSetText, label_set_text, SIDC_API_U32,
                    SIDC_API_U32, SIDC_API_STRING),
        GADGET_CALL(SBOS_TextBoxSetText, textbox_set_text, SIDC_API_VOID,
                    SIDC_API_U32, SIDC_API_STRING),
        GADGET_CALL(SBOS_CheckboxSetState, checkbox_set_state, SIDC_API_VOID,
                    SIDC_API_U32, SIDC_API_U8),
        GADGET_CALL(SBOS_CheckboxGetState, checkbox_get_state, SIDC_API_S8,
                    SIDC_API_U32),
        GADGET_CALL(SBOS_ProgressbarSetMinMax, progressbar_set_minmax, SIDC_API_VOID,
                    SIDC_API_U32, SIDC_API_S16, SIDC_API_S16),
        GADGET_CALL(SBOS_ProgressbarSetValue, progressbar_set_value, SIDC_API_VOID,
                    SIDC_API_U32, SIDC_API_S16),
        GADGET_CALL(SBOS_GadgetSetFocus, set_focus, SIDC_API_VOID, SIDC_API_U32),
        GADGET_CALL(SBOS_GadgetSetCallBack, set_callback, SIDC_API_U32,
                    SIDC_API_U32, SIDC_API_GADGET_CALLBACK, SIDC_API_GADGET_CALLBACK),
        GADGET_CALL(SBOS_GadgetEnabled, enabled, SIDC_API_VOID, SIDC_API_U32, SIDC_API_U8),
        GADGET_CALL(SBOS_ButtonSetText, button_set_text, SIDC_API_VOID,
                    SIDC_API_U32, SIDC_API_STRING, SIDC_API_S8),
        GUI_CALL(windows, API_GUI_Windows, SBOS_CloseWindow, window_close,
                 SIDC_API_VOID, SIDC_API_U8),
        {
            .name = "SBOS_CreateTimer",
            .offsets = GUI_OFFSETS(timers, API_SYS_TIMERS, create),
            .result = SIDC_API_U8
        },
        GUI_CALL(timers, API_SYS_TIMERS, SBOS_TimerSet, set, SIDC_API_S32,
                 SIDC_API_U8, SIDC_API_U32, SIDC_API_U32, SIDC_API_TIMER_CALLBACK, SIDC_API_NULL),
        GUI_CALL(timers, API_SYS_TIMERS, SBOS_TimerCancel, cancel, SIDC_API_VOID, SIDC_API_U8),
        GUI_CALL(timers, API_SYS_TIMERS, SBOS_FreeTimer, free, SIDC_API_VOID, SIDC_API_U8),
        GUI_CALL(windows, API_GUI_Windows, SBOS_SetWindowProc, set_proc,
                 SIDC_API_VOID, SIDC_API_U8, SIDC_API_WINDOW_CALLBACK),
        GUI_CALL(windows, API_GUI_Windows, SBOS_WindowToFront, to_front, SIDC_API_VOID, SIDC_API_U8),
        GUI_CALL(windows, API_GUI_Windows, SBOS_WindowSetFocus, set_focus, SIDC_API_VOID, SIDC_API_U8),
        GUI_CALL(windows, API_GUI_Windows, SBOS_WindowSetApplicationTitle, set_app_title,
                 SIDC_API_VOID, SIDC_API_U8, SIDC_API_STRING),
        GADGET_CALL(SBOS_GadgetMove, move, SIDC_API_VOID, SIDC_API_U32, SIDC_API_S16, SIDC_API_S16),
        GADGET_CALL(SBOS_GadgetResize, resize, SIDC_API_VOID, SIDC_API_U32, SIDC_API_S16, SIDC_API_S16),
        GADGET_CALL(SBOS_GadgetRepaint, repaint, SIDC_API_VOID, SIDC_API_U32),
        GADGET_CALL(SBOS_CreateBitmapView, bitmapview_create, SIDC_API_U32,
                    GADGET_BOUNDS, SIDC_API_S16, SIDC_API_S16, SIDC_API_U32, SIDC_API_U32),
        GADGET_CALL(SBOS_BitmapviewSetBitmap, bitmapview_set_bitmap, SIDC_API_VOID,
                    SIDC_API_U32, SIDC_API_BYTE_BUFFER),
        GADGET_CALL(SBOS_BitmapviewSetImageSize, bitmapview_set_size, SIDC_API_VOID,
                    SIDC_API_U32, SIDC_API_U16, SIDC_API_U16),
        GADGET_CALL(SBOS_CreateCanvas, canvas_create, SIDC_API_U32,
                    GADGET_BOUNDS, SIDC_API_U32, SIDC_API_U32),
        GADGET_CALL(SBOS_GadgetSetFPen, set_fpen, SIDC_API_VOID, SIDC_API_U32, SIDC_API_U8),
        GADGET_CALL(SBOS_GadgetSetBPen, set_bpen, SIDC_API_VOID, SIDC_API_U32, SIDC_API_U8)
    },
    .constants = {
        SDK_CONSTANT(SBX_WIN_DEFAULT),
        SDK_CONSTANT(GAD_TOOL_DEFAULT),
        SDK_CONSTANT(CGTIMER_INVALID),
        SDK_CONSTANT(CGMSG_GADGET),
        SDK_CONSTANT(CGMSG_WINDOW),
        SDK_CONSTANT(CGMSG_KEY),
        SDK_CONSTANT(CGMSG_MOUSE),
        SDK_CONSTANT(CGEVT_GAD_ACTIVATED),
        SDK_CONSTANT(CGEVT_GAD_CHECKBOX_CHANGED),
        SDK_CONSTANT(CGEVT_GAD_SLIDERVAL_CHANGED),
        SDK_CONSTANT(CGEVT_WIN_CLOSE_REQUEST),
        SDK_CONSTANT(CGEVT_WIN_MOVE),
        SDK_CONSTANT(CGEVT_WIN_MOVED),
        SDK_CONSTANT(CGEVT_WIN_RESIZE),
        SDK_CONSTANT(CGEVT_WIN_RESIZED),
        SDK_CONSTANT(CGEVT_WIN_GOTFOCUS),
        SDK_CONSTANT(CGEVT_WIN_LOSTFOCUS),
        SDK_CONSTANT(CGEVT_KEY_PRESSED),
        SDK_CONSTANT(CGEVT_MOUSE_MOVED),
        SDK_CONSTANT(CGEVT_MOUSE_PRESSED),
        SDK_CONSTANT(CGEVT_MOUSE_RELEASED),
        SDK_CONSTANT(SBINPUT_MOUSE_LEFT),
        SDK_CONSTANT(SBINPUT_MOUSE_RIGHT),
        SDK_CONSTANT(SBINPUT_MOUSE_TOUCH),
        SDK_CONSTANT(CGPROC_DEFAULT),
        SDK_CONSTANT(CGPROC_NORMAL),
        SDK_CONSTANT(CGPROC_HANDLED),
        SDK_CONSTANT(CGPROC_END),
        SDK_CONSTANT(GAD_TOOL_NOBORDER),
        SDK_CONSTANT(GAD_TOOL_INSET),
        SDK_CONSTANT(BVF_SRC_ROWMAJOR),
        SDK_CONSTANT(BVF_PAN),
        SDK_CONSTANT(BVF_WRAP),
        SDK_CONSTANT(CNV_LINE),
        SDK_CONSTANT(CNV_RECT),
        SDK_CONSTANT(CNV_BEVEL),
        SDK_CONSTANT(CNV_RECTF)
    },
    .message = {
        .offsets = {
            [SIDC_MSG_MTYPE] = offsetof(CGMessage_t, mtype),
            [SIDC_MSG_WINHND] = offsetof(CGMessage_t, winhnd),
            [SIDC_MSG_GADGET] = offsetof(CGMessage_t, gadget),
            [SIDC_MSG_EVENT] = offsetof(CGMessage_t, eventClass),
            [SIDC_MSG_A] = offsetof(CGMessage_t, a),
            [SIDC_MSG_B] = offsetof(CGMessage_t, b),
            [SIDC_MSG_C] = offsetof(CGMessage_t, c),
            [SIDC_MSG_D] = offsetof(CGMessage_t, d)
        },
        .size = sizeof(CGMessage_t)
    }
};
