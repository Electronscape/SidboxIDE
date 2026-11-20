#include "apis.h"
#include "apicore.h"

#include <stddef.h>

/* Export only symbols supplied by the installed public SDK headers.
 * Do not fabricate display flags or other constants here. When the SDK
 * publishes more definitions, include them from that SDK and audit them. */

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
/* Graphics EBI ABI snapshot from firmware Core/api/api_gfx_engine.h
 * (FIRMWARE - 03-11-2026 - 0947).  Many installed idelibs/api/apis.h
 * versions only FORWARD-DECLARE the gfx table types.  Such incomplete
 * declarations cannot be used with offsetof or __typeof__.
 *
 * Keep these names PRIVATE to the exporter to avoid colliding with SDK
 * structs if a future SDK eventually includes complete graphics types.
 * Every slot is represented in its original order. Reserved fields are
 * raw pointer-sized slots, solely for calculating 32-bit EBI offsets.
 * The selected function signatures below remain statically checked.
 */

/* Native hardware ABI: API_Root.hwl is a DIRECT two-level table.
 * This layout is present in the firmware used by working native games.
 * The generated compiler understands 0xffff as the unused third hop.
 * Do NOT add a third pointer dereference or change the firmware table.
 */
typedef struct {
    void (*gamemode)(uint32_t);
    void (*exitgamemode)(void);
    uint32_t (*getTicks)(void);
    void (*dbug)(char *);
    uint8_t (*getmousepos)(int16_t *, int16_t *);
    void (*setmousepos)(int16_t, int16_t);
    void (*getmousedelta)(int32_t *, int32_t *);
    void (*clrmousedelta)(void);
    uint8_t (*getjoyport)(void);
} SidcHwABI;
_Static_assert(sizeof(void *) == 4 &&
               offsetof(SidcHwABI, getTicks) == 8 &&
               offsetof(SidcHwABI, getjoyport) == 32,
               "Original hardware table offsets have changed");
typedef struct {
    const void *hgfx;
    const void *primatives; /* firmware spelling is intentionally retained */
} SidcGfxRootABI;
typedef struct {
    void (*displaynow)(void);
    void *vidmem;
    void *ledbrightness;
    void (*lcdwait)(void);
    void *setlcd;
    void (*setdisplaymode)(int, int, int, int, int);
    void (*usebuffer)(gfx_bitmap_t *);
    void (*showfbuffer)(gfx_bitmap_t *);
    void (*showbbuffer)(gfx_bitmap_t *);
    void (*dispfbuffers)(gfx_bitmap_t *, gfx_bitmap_t *);
    void (*dispbbuffers)(gfx_bitmap_t *, gfx_bitmap_t *);
    void (*scrollf)(int, int);
    void (*scrollb)(int, int);
    gfx_bitmap_t *(*getdrawbuffer)(void);
    gfx_bitmap_t *(*getshowbuffer)(void);
    gfx_bitmap_t *(*getfbuffer1)(void);
    gfx_bitmap_t *(*getfbuffer2)(void);
    gfx_bitmap_t *(*getbbuffer1)(void);
    gfx_bitmap_t *(*getbbuffer2)(void);
    void (*usepalettef)(uint32_t *);
    void (*usepaletteb)(uint32_t *);
    void *palcycleon;
    void *palcycleoff;
    void (*palcycleset)(uint8_t);
    void (*palcyclerange)(uint8_t, uint8_t);
    void (*palcyclerate)(uint8_t);
    void *blitchunk;
    void *createSprite;
    void *submitSprite;
    void *popSprites;
    void *palcycleonb;
    void *palcycleoffb;
    void *palcyclesetb;
    void *palcyclerangeb;
    void *palcyclerateb;
} SidcGfxHardwareABI;
typedef struct {
    void (*cls)(void);
    void (*rectf)(int16_t, int16_t, int16_t, int16_t);
    void (*plot)(int16_t, int16_t);
    void (*setcolour)(uint8_t);
    void *getsprite;
    void *blitcell;
    void (*blit)(uint8_t *, int16_t, int16_t, uint16_t, uint16_t);
    void (*blitw)(uint8_t *, int16_t, int16_t, uint16_t, uint16_t, uint16_t);
    void *tcollide;
    void *drawbob;
    void *bcollide;
    void (*drawtext)(long, long, const char *);
    void (*drawtextf)(long, long, const char *, uint8_t, uint8_t);
    void *drawtextfc;
    void (*circle)(int16_t, int16_t, int16_t);
    void (*circlef)(int16_t, int16_t, int16_t);
    void (*drawline)(int16_t, int16_t, int16_t, int16_t);
} SidcGfxPrimitivesABI;

_Static_assert(sizeof(SidcGfxRootABI) == 8, "Graphics root must be two ARM pointers");
_Static_assert(sizeof(SidcGfxHardwareABI) == 35 * 4, "Graphics hardware EBI layout changed");
_Static_assert(sizeof(SidcGfxPrimitivesABI) == 17 * 4, "Graphics primitives EBI layout changed");
_Static_assert(offsetof(SidcGfxRootABI, primatives) == 4, "Graphics primitive pointer moved");
_Static_assert(offsetof(SidcGfxHardwareABI, getfbuffer1) == 15 * 4,
               "Graphics front buffer offset changed");
_Static_assert(offsetof(SidcGfxHardwareABI, usepalettef) == 19 * 4,
               "Graphics palette offset changed");
_Static_assert(offsetof(SidcGfxPrimitivesABI, drawtext) == 11 * 4,
               "Graphics text offset changed");
#define GFX_HW_CHECK(member, signature) CHECK_SIGNATURE(SidcGfxHardwareABI, member, signature)
#define GFX_PRIM_CHECK(member, signature) CHECK_SIGNATURE(SidcGfxPrimitivesABI, member, signature)
GFX_HW_CHECK(displaynow, void (*)(void));
GFX_HW_CHECK(lcdwait, void (*)(void));
GFX_HW_CHECK(setdisplaymode, void (*)(int, int, int, int, int));
GFX_HW_CHECK(scrollf, void (*)(int, int));
GFX_HW_CHECK(scrollb, void (*)(int, int));
GFX_HW_CHECK(getfbuffer1, gfx_bitmap_t *(*)(void));
GFX_HW_CHECK(getfbuffer2, gfx_bitmap_t *(*)(void));
GFX_HW_CHECK(getbbuffer1, gfx_bitmap_t *(*)(void));
GFX_HW_CHECK(getbbuffer2, gfx_bitmap_t *(*)(void));
GFX_HW_CHECK(getdrawbuffer, gfx_bitmap_t *(*)(void));
GFX_HW_CHECK(getshowbuffer, gfx_bitmap_t *(*)(void));
GFX_HW_CHECK(usebuffer, void (*)(gfx_bitmap_t *));
GFX_HW_CHECK(dispfbuffers, void (*)(gfx_bitmap_t *,gfx_bitmap_t *));
GFX_HW_CHECK(dispbbuffers, void (*)(gfx_bitmap_t *,gfx_bitmap_t *));
GFX_HW_CHECK(showfbuffer, void (*)(gfx_bitmap_t *));
GFX_HW_CHECK(showbbuffer, void (*)(gfx_bitmap_t *));
GFX_HW_CHECK(usepalettef, void (*)(uint32_t *));
GFX_HW_CHECK(usepaletteb, void (*)(uint32_t *));
GFX_HW_CHECK(palcycleset, void (*)(uint8_t));
GFX_HW_CHECK(palcyclerange, void (*)(uint8_t, uint8_t));
GFX_HW_CHECK(palcyclerate, void (*)(uint8_t));
GFX_PRIM_CHECK(cls, void (*)(void));
GFX_PRIM_CHECK(rectf, void (*)(int16_t,int16_t,int16_t,int16_t));
GFX_PRIM_CHECK(plot, void (*)(int16_t,int16_t));
GFX_PRIM_CHECK(setcolour, void (*)(uint8_t));
GFX_PRIM_CHECK(blit, void (*)(uint8_t *,int16_t,int16_t,uint16_t,uint16_t));
GFX_PRIM_CHECK(blitw, void (*)(uint8_t *,int16_t,int16_t,uint16_t,uint16_t,uint16_t));
GFX_PRIM_CHECK(circle, void (*)(int16_t,int16_t,int16_t));
GFX_PRIM_CHECK(circlef, void (*)(int16_t,int16_t,int16_t));
GFX_PRIM_CHECK(drawline, void (*)(int16_t,int16_t,int16_t,int16_t));
GFX_PRIM_CHECK(drawtext, void (*)(long,long,const char *));
GFX_PRIM_CHECK(drawtextf, void (*)(long,long,const char *,uint8_t,uint8_t));
/* Desktop suspend/restore are not exported by this table.  The SDK's
 * API_SYSTEMS is likewise often only forward-declared, so do not access it. */
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
    {.name = "API.gui->" #group "->" #member, \
     .offsets = GUI_OFFSETS(group, table, member), \
     .arity = sizeof((uint8_t[]){__VA_ARGS__}), \
     .result = return_type, .params = {__VA_ARGS__}}
#define GADGET_CALL(sdk_name, member, return_type, ...) \
    GUI_CALL(gadgets, API_GUI_GADGETS, sdk_name, member, return_type, __VA_ARGS__)
#define GFX_OFFSETS(group, table, member) \
    {offsetof(API_Root, gfx), offsetof(SidcGfxRootABI, group), offsetof(table, member)}
#define GFX_CALL(group, table, sdk_name, member, return_type, ...) \
    {.name = "API.gfx->" #group "->" #member, .offsets = GFX_OFFSETS(group, table, member), \
     .arity = sizeof((uint8_t[]){__VA_ARGS__}), .result = return_type, \
     .params = {__VA_ARGS__}}
#define GFX_HW(sdk_name, member, return_type, ...) \
    GFX_CALL(hgfx, SidcGfxHardwareABI, sdk_name, member, return_type, __VA_ARGS__)
#define GFX_PRIM(sdk_name, member, return_type, ...) \
    GFX_CALL(primatives, SidcGfxPrimitivesABI, sdk_name, member, return_type, __VA_ARGS__)
#define HW_CALL(sdk_name, member, return_type) \
    {.name = "API.hwl->" #member, .offsets = {offsetof(API_Root, hwl), \
     offsetof(SidcHwABI, member), 0xffffu}, \
     .arity = 0, .result = return_type}
#define SDK_CONSTANT(name) {#name, name}

enum { CALL_COUNT = 68, CONSTANT_COUNT = 37 };
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
            .name = "API.gui->windows->window_create",
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
            .name = "API.gui->timers->create",
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
        GADGET_CALL(SBOS_GadgetSetBPen, set_bpen, SIDC_API_VOID, SIDC_API_U32, SIDC_API_U8),
        GFX_HW(SBOS_GFXDisplayNow, displaynow, SIDC_API_VOID),
        GFX_HW(SBOS_GFXWaitLCD, lcdwait, SIDC_API_VOID),
        GFX_HW(SBOS_GFXSetDisplayMode, setdisplaymode, SIDC_API_VOID, SIDC_API_S32,SIDC_API_S32,SIDC_API_S32,SIDC_API_S32,SIDC_API_S32),
        GFX_HW(SBOS_GFXScrollFront, scrollf, SIDC_API_VOID, SIDC_API_S32,SIDC_API_S32),
        GFX_HW(SBOS_GFXScrollBack, scrollb, SIDC_API_VOID, SIDC_API_S32,SIDC_API_S32),
        GFX_HW(SBOS_GFXGetFrontBuffer1, getfbuffer1, SIDC_API_U32),
        GFX_HW(SBOS_GFXGetFrontBuffer2, getfbuffer2, SIDC_API_U32),
        GFX_HW(SBOS_GFXGetBackBuffer1, getbbuffer1, SIDC_API_U32),
        GFX_HW(SBOS_GFXGetBackBuffer2, getbbuffer2, SIDC_API_U32),
        GFX_HW(SBOS_GFXGetDrawBuffer, getdrawbuffer, SIDC_API_U32),
        GFX_HW(SBOS_GFXGetShowBuffer, getshowbuffer, SIDC_API_U32),
        GFX_HW(SBOS_GFXFrontBuffers, dispfbuffers, SIDC_API_VOID, SIDC_API_U32,SIDC_API_U32),
        GFX_HW(SBOS_GFXBackBuffers, dispbbuffers, SIDC_API_VOID, SIDC_API_U32,SIDC_API_U32),
        GFX_HW(SBOS_GFXUseDrawBuffer, usebuffer, SIDC_API_VOID, SIDC_API_U32),
        GFX_HW(SBOS_GFXShowFrontBuffer, showfbuffer, SIDC_API_VOID, SIDC_API_U32),
        GFX_HW(SBOS_GFXShowBackBuffer, showbbuffer, SIDC_API_VOID, SIDC_API_U32),
        GFX_HW(SBOS_GFXLoadFrontPalette, usepalettef, SIDC_API_VOID, SIDC_API_WORD_BUFFER),
        GFX_HW(SBOS_GFXLoadBackPalette, usepaletteb, SIDC_API_VOID, SIDC_API_WORD_BUFFER),
        GFX_HW(SBOS_GFXPaletteCycle, palcycleset, SIDC_API_VOID, SIDC_API_U8),
        GFX_HW(SBOS_GFXPaletteCycleRange, palcyclerange, SIDC_API_VOID, SIDC_API_U8,SIDC_API_U8),
        GFX_HW(SBOS_GFXPaletteCycleRate, palcyclerate, SIDC_API_VOID, SIDC_API_U8),
        GFX_PRIM(SBOS_GFXClear, cls, SIDC_API_VOID),
        GFX_PRIM(SBOS_GFXRectFill, rectf, SIDC_API_VOID, SIDC_API_S16,SIDC_API_S16,SIDC_API_S16,SIDC_API_S16),
        GFX_PRIM(SBOS_GFXPlot, plot, SIDC_API_VOID, SIDC_API_S16,SIDC_API_S16),
        GFX_PRIM(SBOS_GFXSetColour, setcolour, SIDC_API_VOID, SIDC_API_U8),
        GFX_PRIM(SBOS_GFXBlit, blit, SIDC_API_VOID, SIDC_API_BYTE_BUFFER,SIDC_API_S16,SIDC_API_S16,SIDC_API_U16,SIDC_API_U16),
        GFX_PRIM(SBOS_GFXBlitStride, blitw, SIDC_API_VOID, SIDC_API_BYTE_BUFFER,SIDC_API_S16,SIDC_API_S16,SIDC_API_U16,SIDC_API_U16,SIDC_API_U16),
        GFX_PRIM(SBOS_GFXCircle, circle, SIDC_API_VOID, SIDC_API_S16,SIDC_API_S16,SIDC_API_S16),
        GFX_PRIM(SBOS_GFXCircleFill, circlef, SIDC_API_VOID, SIDC_API_S16,SIDC_API_S16,SIDC_API_S16),
        GFX_PRIM(SBOS_GFXDrawLine, drawline, SIDC_API_VOID, SIDC_API_S16,SIDC_API_S16,SIDC_API_S16,SIDC_API_S16),
        GFX_PRIM(SBOS_GFXDrawText, drawtext, SIDC_API_VOID, SIDC_API_S32,SIDC_API_S32,SIDC_API_STRING),
        GFX_PRIM(SBOS_GFXDrawTextScaled, drawtextf, SIDC_API_VOID, SIDC_API_S32,SIDC_API_S32,SIDC_API_STRING,SIDC_API_U8,SIDC_API_U8),
        /* Original hardware EBI fields, unchanged. */
        HW_CALL(SBOS_HWGetJoyPort, getjoyport, SIDC_API_U8),
        HW_CALL(SBOS_HWGetCpuCycles, getTicks, SIDC_API_U32)
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
