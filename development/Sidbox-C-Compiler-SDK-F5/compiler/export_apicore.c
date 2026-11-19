#include "apis.h"
#include "apicore.h"

#include <stddef.h>

/* Fail the export if the SDK changes the call's calling convention. */
typedef uint8_t (*CreateWindow)(uint8_t *, int16_t, int16_t, uint16_t, uint16_t,
                                const char *, uint32_t);
_Static_assert(__builtin_types_compatible_p(
                   __typeof__(((API_GUI_Windows *)0)->window_create), CreateWindow),
               "Update the compiler binding for the new window_create signature");
typedef uint32_t (*CreateLabel)(uint8_t, int16_t, int16_t, int16_t, int16_t,
                                const char *, uint32_t);
_Static_assert(__builtin_types_compatible_p(
                   __typeof__(((API_GUI_GADGETS *)0)->label_create), CreateLabel),
               "Update the compiler binding for the new label_create signature");
_Static_assert(sizeof(void *) == 4, "Export with ARM GCC");
_Static_assert((uintptr_t)NULL == 0, "The SDK requires a zero null pointer");

static const struct {
    SidcApiHeader header;
    SidcApiCall calls[2];
    SidcApiConstant constants[2];
} apicore __attribute__((section(".sidc_apicore"), used)) = {
    .header = {SIDC_APICORE_MAGIC, SIDBOX_API_BASE, 2, 2},
    .calls = {{
        .name = "SBOS_CreateWindow",
        .offsets = {
            offsetof(API_Root, gui),
            offsetof(API_GUI, windows),
            offsetof(API_GUI_Windows, window_create)
        },
        .arity = 7,
        .result = SIDC_API_U8,
        .params = {SIDC_API_NULL, SIDC_API_S16, SIDC_API_S16, SIDC_API_U16,
                   SIDC_API_U16, SIDC_API_STRING, SIDC_API_U32}
    }, {
        .name = "SBOS_CreateLabel",
        .offsets = {
            offsetof(API_Root, gui),
            offsetof(API_GUI, gadgets),
            offsetof(API_GUI_GADGETS, label_create)
        },
        .arity = 7,
        .result = SIDC_API_U32,
        .params = {SIDC_API_U8, SIDC_API_S16, SIDC_API_S16, SIDC_API_S16,
                   SIDC_API_S16, SIDC_API_STRING, SIDC_API_U32}
    }},
    .constants = {
        {"SBX_WIN_DEFAULT", SBX_WIN_DEFAULT},
        {"GAD_TOOL_DEFAULT", GAD_TOOL_DEFAULT}
    }
};
