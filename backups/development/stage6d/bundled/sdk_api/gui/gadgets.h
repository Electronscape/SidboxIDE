#ifndef SBAPI_GADGETS_H
#define SBAPI_GADGETS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef uint32_t    CNV_FLAGS_T;
typedef uint32_t    BMV_FLAGS_T;
typedef uint32_t    GAD_TOOL_FLAGS;
typedef uint32_t    CGGadget;

/*
 * Public layout of the caller-owned CoderGirl ItemList model.
 * Keep this binary-identical to firmware cg_itemlist.h.
 */
typedef struct ItemLists_t {
    void     **items;
    uint16_t count;
    uint16_t cap;
} ItemLists_t;

typedef void (*fnCallback)(void *gadget, int32_t a, int32_t b, int32_t c, int32_t d);

// control types
typedef enum GADGET_CLASS_T {
    GAD_NULL        = 0,
    GAD_BITMAPVIEW,
    GAD_BUTTON,
    GAD_CANVAS,
    GAD_CHECKBOX,
    GAD_GRIDSELECT,
    GAD_LABEL,
    GAD_LISTBOX,
    GAD_PROGBAR,
    GAD_RADIO,
    GAD_SCROLLBAR,
    GAD_SLIDER,
    GAD_TEXTBOX,
    GAD_TEXTAREA
} GADGET_CLASS_T;


typedef struct API_GUI_GADGETS {
    void     (*init)                  (void);

    CGGadget (*bitmapview_create)     (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, int16_t bmp_w, int16_t bmp_h, uint32_t bv_flags, GAD_TOOL_FLAGS flags);
    CGGadget (*button_create)         (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, GAD_TOOL_FLAGS flags);
    CGGadget (*canvas_create)         (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, CNV_FLAGS_T drawtype, GAD_TOOL_FLAGS flags);
    CGGadget (*checkbox_create)       (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, uint8_t initial_checked, GAD_TOOL_FLAGS flags);
    CGGadget (*gridselect_create)     (CGWindow win, int16_t x, int16_t y, int16_t cell_size_x, int16_t cell_size_y, uint8_t cells_x, uint8_t cells_y, uint32_t gridflags, GAD_TOOL_FLAGS flags);
    CGGadget (*label_create)          (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, GAD_TOOL_FLAGS flags);
    CGGadget (*listbox_create)        (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, GAD_TOOL_FLAGS flags);
    CGGadget (*progbar_create)        (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, GAD_TOOL_FLAGS flags);
    CGGadget (*radiobutton_create)    (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, uint8_t group, uint8_t checked, GAD_TOOL_FLAGS flags);
    CGGadget (*scrollbar_create)      (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t orient, int16_t min, int16_t max, int16_t step_small, int16_t step_large, GAD_TOOL_FLAGS flags);
    CGGadget (*slider_create)         (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t orient, int16_t min, int16_t max, GAD_TOOL_FLAGS flags);
    CGGadget (*textbox_create)        (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, uint8_t tbFlags, GAD_TOOL_FLAGS flags);
    CGGadget (*textarea_create)       (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, uint8_t taFlags, GAD_TOOL_FLAGS flags);

    CGGadget (*get_id)                (void *src);
    void     (*move)                  (CGGadget hnd, int16_t newx, int16_t newy);
    void     (*resize)                (CGGadget hnd, int16_t neww, int16_t newh);
    void     (*set_bpen)              (CGGadget hnd, uint8_t bpen);
    void     (*set_fpen)              (CGGadget hnd, uint8_t fpen);
    void     (*set_hpen)              (CGGadget hnd, uint8_t hpen);
    void     (*enabled)               (CGGadget h, uint8_t enable);
    void     (*destroy)               (CGGadget h);
    void     (*repaint)               (CGGadget gadgetId);
    void     (*set_focus)             (CGGadget gadget);
    uint32_t (*set_callback)          (CGGadget h, fnCallback fnOnActive, fnCallback fnOnChange);
    void     (*set_group_visible)     (CGWindow hwin, uint8_t groupid, uint8_t visible);
    void     (*set_group_id)          (CGGadget gad, uint8_t newgroupid);
    uint8_t  (*get_group_id)          (CGGadget gad);
    uint32_t (*textarea_get_text)     (CGGadget hTa, char *out, uint32_t outCap);
    void     (*bitmapview_set_bitmap) (CGGadget bitmapview, void *bitmap);
    void     (*bitmapview_set_size)   (CGGadget bitmapview, uint16_t width, uint16_t height);

    /* Appended in API vNext: existing member offsets remain unchanged. */
    uint32_t (*gridselect_set_cell_text)(CGGadget grid, const char *text, int16_t cellindex);
    void     (*progressbar_set_value)  (CGGadget progress, int16_t value);
    void     (*progressbar_set_minmax) (CGGadget progress, int16_t minimum, int16_t maximum);

    /* Appended ListBox model API; all earlier offsets remain unchanged. */
    void     (*itemlist_init)          (ItemLists_t *list);
    void     (*itemlist_deinit)        (ItemLists_t *list);
    int      (*itemlist_add)           (ItemLists_t *list, const char *text, uint32_t flags);
    int16_t  (*listbox_attach_itemlist)(CGGadget listbox, ItemLists_t *list);

    /* Appended for virtual TabGroup pressed-state selection; ABI offsets stable. */
    void     (*button_set_toggle)       (CGGadget button, uint8_t pressed);

    /* Appended GUI runtime controls. NEVER insert above existing members. */
    void        (*textbox_set_text)        (CGGadget textbox, const char *text);
    const char* (*textbox_get_text)        (CGGadget textbox);
    uint16_t    (*textbox_get_length)      (CGGadget textbox);
    void        (*textbox_set_caret)       (CGGadget textbox, uint16_t pos);
    uint16_t    (*textbox_get_caret)       (CGGadget textbox);
    void        (*textarea_set_text)       (CGGadget textarea, const char *text);
    void        (*textarea_insert_text)    (CGGadget textarea, const char *text);
    void        (*textarea_set_caret)      (CGGadget textarea, uint32_t line, uint32_t col);
    void        (*textarea_get_caret)      (CGGadget textarea, uint32_t *line, uint32_t *col);
    uint32_t    (*textarea_line_count)     (CGGadget textarea);
    uint32_t    (*label_set_text)          (CGGadget label, const char *text);
    uint32_t    (*label_set_colour)        (CGGadget label, int16_t fpen, int16_t bpen);
    void        (*button_set_text)         (CGGadget button, const char *text, int8_t cycle_index);
    void        (*checkbox_set_state)      (CGGadget checkbox, uint8_t checked);
    int8_t      (*checkbox_get_state)      (CGGadget checkbox);
    void        (*slider_set_value)        (CGGadget slider, uint16_t value);
    uint16_t    (*slider_get_value)        (CGGadget slider);
    void        (*scrollbar_set_value)     (CGGadget scrollbar, uint16_t value);
    int16_t     (*scrollbar_get_value)     (CGGadget scrollbar);

} API_GUI_GADGETS;

typedef API_GUI_GADGETS API_GUI_Gadgets;

//extern const API_GUI_GADGETS API_gui_gadgets;

//// Gadget Control flags
#define GAD_TOOL_DEFAULT        (1 << 0)    // nothing special
#define GAD_TOOL_DOCKED_RIGHT   (1 << 1)    // right dock used
#define GAD_TOOL_DOCKED_BOTTOM  (1 << 2)    // bottom dock used
#define GAD_TOOL_CYCLEBUTTON    (1 << 3)    // button cycle flag
#define GAD_TOOL_SCROLLARROWS   (1 << 4)    // enable the arrows on the scrollbars
#define GAD_TOOL_NOBORDER       (1 << 5)    // no border around gadgets
#define GAD_TOOL_INSET          (1 << 6)    // invert the bevel on gadgets
#define GAD_TOOL_MOUSEMOVE      (1 << 7)    // allows to receive mouse move over the gadget
#define GAD_TOOL_ICON           (1 << 8)    // enable images in gadgets
#define GAD_TOOL_ALIGN_BELOW    (1 << 9)    // align the text below the gadget
#define GAD_TOOL_ALIGN_LEFT     (1 << 10)   // align the text below the gadget
#define GAD_TOOL_ALIGN_RIGHT    (1 << 11)   // align the text below the gadget
#define GAD_TOOL_ALIGN_TOP      (1 << 12)   // align the text below the gadget
#define GAD_TOOL_OPAQUE_TEXT    (1 << 13)   // make the text background opaque
#define GAD_TOOL_TOGGLE         (1 << 14)   // allows for toggling
#define GAD_TOOL_LATCHDOWN      (1 << 15)   // keep pressed visual latched until owner clears it
#define GAD_TOOL_TRANSPARENT    (1 << 16)   // transparent backgrounds

//// BITMAP VIEW FLAGS
#define BVF_SHOW_FRAME          (1 << 0)
#define BVF_PAN                 (1 << 1)
#define BVF_SRC_ROWMAJOR        (1 << 2)    // src = pixels[y*stride + x]
#define BVF_SRC_XMAJOR          (1 << 3)    // src = pixels[x*stride + y]
#define BVF_WRAP                (1 << 4)
#define BVF_PERSISTANT          (1 << 5)    // slower UI-rendered path; normal dirty/compositor behaviour
#define BVF_PERSISTENT          BVF_PERSISTANT

//// Gadget Canvas draw type
#define CNV_LINE                (0)
#define CNV_RECT                (1)
#define CNV_BEVEL               (2)    // historical firmware value; keep stable
#define CNV_RECTF               (3)    // filled rectangle must be distinct from bevel


//CGGadget SBOS_CreateButton     (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, GAD_TOOL_FLAGS flags);



/*

typedef struct {
    CGGadget (*gad_button_create)    (CGWindow win, int16_t x, int16_t y, int16_t w, int16_t h, const char *text, GAD_TOOL_FLAGS flags);

} API_GUI_Gadgets;
*/

///////////-------------- HELPERS -----------------//////
/////////////////// API SYSTEM LEVEL ################
#define GUICoderGirl      (API->gui)
/////////////////////////////////////////////////////////

//#define SBOS_CreateButton(win, x, y, w, h, text, flags) (GUICoderGirl->gadgets->button_create(__VA_ARGS__))
#define SBOS_CreateButton(win, x, y, w, h, text, flags) \
    (GUICoderGirl->gadgets->button_create(win, x, y, w, h, text, flags))

#define SBOS_CreateLabel(win, x, y, w, h, text, flags) \
    (GUICoderGirl->gadgets->label_create(win, x, y, w, h, text, flags))

#define SBOS_CreateTextArea(win, x, y, w, h, text, text_flags, flags) \
    (GUICoderGirl->gadgets->textarea_create(win, x, y, w, h, text, text_flags, flags))

#define SBOS_CreateBitmapView(win, x, y, w, h, bmp_w, bmp_h, bv_flags, flags) \
    (GUICoderGirl->gadgets->bitmapview_create(win, x, y, w, h, bmp_w, bmp_h, bv_flags, flags))

#define SBOS_CreateCanvas(win, x, y, w, h, drawtype, flags) \
    (GUICoderGirl->gadgets->canvas_create(win, x, y, w, h, drawtype, flags))

#define SBOS_DestroyGadget(gadget) \
    (GUICoderGirl->gadgets->destroy(gadget))

#define SBOS_GadgetRepaint(gadget) \
    (GUICoderGirl->gadgets->repaint(gadget))

#define SBOS_GadgetSetFocus(gadget) \
    (GUICoderGirl->gadgets->set_focus(gadget))


#define SBOS_GadgetSetCallBack(h, fnOnActive, fnOnChange) \
    (GUICoderGirl->gadgets->set_callback(h, fnOnActive, fnOnChange))

#define SBOS_TextAreaGetText(hTa, out, outCap) \
    (GUICoderGirl->gadgets->textarea_get_text(hTa, out, outCap))

#define SBOS_BitmapviewSetBitmap(bitmapview, bitmap) \
    (GUICoderGirl->gadgets->bitmapview_set_bitmap(bitmapview, bitmap))

#define SBOS_BitmapviewSetImageSize(bitmapview, width, height) \
    (GUICoderGirl->gadgets->bitmapview_set_size(bitmapview, width, height))

#define SBOS_GridSelectSetCellText(grid, text, cellindex) \
    (GUICoderGirl->gadgets->gridselect_set_cell_text(grid, text, cellindex))

#define SBOS_ProgressbarSetValue(progress, value) \
    (GUICoderGirl->gadgets->progressbar_set_value(progress, value))

#define SBOS_ProgressbarSetMinMax(progress, minimum, maximum) \
    (GUICoderGirl->gadgets->progressbar_set_minmax(progress, minimum, maximum))

#define SBOS_Itemlist_Init(list) \
    (GUICoderGirl->gadgets->itemlist_init(list))

#define SBOS_Itemlist_Deinit(list) \
    (GUICoderGirl->gadgets->itemlist_deinit(list))

#define SBOS_Itemlist_Add(list, text, flags) \
    (GUICoderGirl->gadgets->itemlist_add(list, text, flags))

#define SBOS_ListboxAttachItemlist(listbox, list) \
    (GUICoderGirl->gadgets->listbox_attach_itemlist(listbox, list))


/* ---- GUI SDK constructors not previously exposed as convenient macros ---- */
#define SBOS_CreateTextBox(win, x, y, w, h, text, tb_flags, flags) \
    (GUICoderGirl->gadgets->textbox_create((win), (x), (y), (w), (h), (text), (tb_flags), (flags)))
#define SBOS_CreateCheckbox(win, x, y, w, h, text, checked, flags) \
    (GUICoderGirl->gadgets->checkbox_create((win), (x), (y), (w), (h), (text), (checked), (flags)))
#define SBOS_CreateGridSelect(win, x, y, cell_w, cell_h, cells_x, cells_y, grid_flags, flags) \
    (GUICoderGirl->gadgets->gridselect_create((win), (x), (y), (cell_w), (cell_h), (cells_x), (cells_y), (grid_flags), (flags)))
#define SBOS_CreateListBox(win, x, y, w, h, flags) \
    (GUICoderGirl->gadgets->listbox_create((win), (x), (y), (w), (h), (flags)))
#define SBOS_CreateProgBar(win, x, y, w, h, flags) \
    (GUICoderGirl->gadgets->progbar_create((win), (x), (y), (w), (h), (flags)))
#define SBOS_CreateRadioButton(win, x, y, w, h, text, group, checked, flags) \
    (GUICoderGirl->gadgets->radiobutton_create((win), (x), (y), (w), (h), (text), (group), (checked), (flags)))
#define SBOS_CreateScrollbar(win, x, y, w, h, orient, min_value, max_value, step_small, step_large, flags) \
    (GUICoderGirl->gadgets->scrollbar_create((win), (x), (y), (w), (h), (orient), (min_value), (max_value), (step_small), (step_large), (flags)))
#define SBOS_CreateSlider(win, x, y, w, h, orient, min_value, max_value, flags) \
    (GUICoderGirl->gadgets->slider_create((win), (x), (y), (w), (h), (orient), (min_value), (max_value), (flags)))

/* ---- Firmware-backed setters/readers; firmware must be updated FIRST. ---- */
/* TextBox returns a borrowed pointer. Copy it if retaining beyond the gadget lifetime. */
#define SBOS_TextBoxSetText(h, text)      (GUICoderGirl->gadgets->textbox_set_text((h), (text)))
#define SBOS_TextBoxGetText(h)            (GUICoderGirl->gadgets->textbox_get_text((h)))
#define SBOS_TextBoxGetLen(h)             (GUICoderGirl->gadgets->textbox_get_length((h)))
#define SBOS_TextBoxSetCaret(h, pos)      (GUICoderGirl->gadgets->textbox_set_caret((h), (pos)))
#define SBOS_TextBoxGetCaret(h)           (GUICoderGirl->gadgets->textbox_get_caret((h)))
#define SBOS_TextAreaSetText(h, text)     (GUICoderGirl->gadgets->textarea_set_text((h), (text)))
#define SBOS_TextAreaInsertText(h, text)  (GUICoderGirl->gadgets->textarea_insert_text((h), (text)))
#define SBOS_TextAreaSetCaret(h, l, c)    (GUICoderGirl->gadgets->textarea_set_caret((h), (l), (c)))
#define SBOS_TextAreaGetCaret(h, l, c)    (GUICoderGirl->gadgets->textarea_get_caret((h), (l), (c)))
#define SBOS_TextAreaLineCount(h)         (GUICoderGirl->gadgets->textarea_line_count((h)))
#define SBOS_LabelSetText(h, text)        (GUICoderGirl->gadgets->label_set_text((h), (text)))
#define SBOS_LabelSetColour(h, fg, bg)    (GUICoderGirl->gadgets->label_set_colour((h), (fg), (bg)))
#define SBOS_ButtonSetText(h, text, ci)   (GUICoderGirl->gadgets->button_set_text((h), (text), (ci)))
#define SBOS_CheckboxSetState(h, checked) (GUICoderGirl->gadgets->checkbox_set_state((h), (checked)))
#define SBOS_CheckboxGetState(h)          (GUICoderGirl->gadgets->checkbox_get_state((h)))
#define SBOS_SliderSetValue(h, value)     (GUICoderGirl->gadgets->slider_set_value((h), (value)))
#define SBOS_SliderGetValue(h)            (GUICoderGirl->gadgets->slider_get_value((h)))
#define SBOS_ScrollbarSetValue(h, value)  (GUICoderGirl->gadgets->scrollbar_set_value((h), (value)))
#define SBOS_ScrollbarGetValue(h)         (GUICoderGirl->gadgets->scrollbar_get_value((h)))

/* Short aliases for setting text after a FileRequester selection, etc. */
#define SBOS_SetTextBox(h, text)          SBOS_TextBoxSetText((h), (text))
#define SBOS_SetTextArea(h, text)         SBOS_TextAreaSetText((h), (text))

/* ---- Previously available gadget API members without SDK helpers ---- */
#define SBOS_GadgetMove(h, x, y)          (GUICoderGirl->gadgets->move((h), (x), (y)))
#define SBOS_GadgetResize(h, w, ht)       (GUICoderGirl->gadgets->resize((h), (w), (ht)))
#define SBOS_GadgetSetBPen(h, pen)        (GUICoderGirl->gadgets->set_bpen((h), (pen)))
#define SBOS_GadgetSetFPen(h, pen)        (GUICoderGirl->gadgets->set_fpen((h), (pen)))
#define SBOS_GadgetSetHPen(h, pen)        (GUICoderGirl->gadgets->set_hpen((h), (pen)))
#define SBOS_GadgetEnabled(h, state)      (GUICoderGirl->gadgets->enabled((h), (state)))
#define SBOS_GadgetSetGroupVisable(win, group, visible) \
    (GUICoderGirl->gadgets->set_group_visible((win), (group), (visible)))
#define SBOS_GadgetSetGroupId(h, id)      (GUICoderGirl->gadgets->set_group_id((h), (id)))
#define SBOS_GadgetGetGroupId(h)          (GUICoderGirl->gadgets->get_group_id((h)))
#define SBOS_ButtonSetToggle(h, pressed)  (GUICoderGirl->gadgets->button_set_toggle((h), (pressed)))


#ifdef __cplusplus
}
#endif
#endif
