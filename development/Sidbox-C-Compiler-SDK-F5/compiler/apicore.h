#ifndef SIDC_APICORE_H
#define SIDC_APICORE_H

#include <stdint.h>

/* Compiler definitions live in the firmware-created Sidbox library directory. */
#define SIDC_APICORE_PATH "tfcard:/sidbox/l/clibs.library"
#define SIDC_APICORE_MAGIC_V1 "SBAPI01"
#define SIDC_APICORE_MAGIC_V2 "SBAPI02"
#define SIDC_APICORE_MAGIC "SBAPI05"

enum {
    SIDC_API_CALLS = 160,
    SIDC_API_CONSTANTS = 192,
    SIDC_API_NAME = 64,
    SIDC_API_CONST_NAME = 32,
    SIDC_API_PARAMS_V2 = 8,
    SIDC_API_PARAMS = 12,
    SIDC_API_OFFSETS = 3
};

enum {
    SIDC_API_NULL = 1,
    SIDC_API_STRING,
    SIDC_API_S16,
    SIDC_API_U16,
    SIDC_API_U32,
    SIDC_API_U8,
    SIDC_API_VOID,
    SIDC_API_S8,
    SIDC_API_GADGET_CALLBACK,
    SIDC_API_TIMER_CALLBACK,
    SIDC_API_S32,
    SIDC_API_WINDOW_CALLBACK,
    SIDC_API_WINDOW_REF,
    SIDC_API_BYTE_BUFFER,
    SIDC_API_WORD_BUFFER,
    SIDC_API_U16_RESULT,
    SIDC_API_S16_RESULT,
    SIDC_API_WORD_REF,
    SIDC_API_STRUCT_REF,
    SIDC_API_MENU_CALLBACK,
    SIDC_API_DATA_PTR,
    SIDC_API_POINTER_VALUE
};

enum {
    SIDC_MSG_MTYPE, SIDC_MSG_WINHND, SIDC_MSG_GADGET, SIDC_MSG_EVENT,
    SIDC_MSG_A, SIDC_MSG_B, SIDC_MSG_C, SIDC_MSG_D, SIDC_MSG_FIELDS
};

typedef struct {
    char magic[8];
    uint32_t base;
    uint32_t call_count;
    uint32_t constant_count;
} SidcApiHeader;

typedef struct {
    char name[SIDC_API_NAME];
    uint16_t offsets[SIDC_API_OFFSETS];
    uint8_t arity;
    uint8_t result;
    uint8_t params[SIDC_API_PARAMS];
} SidcApiCall;

typedef struct {
    char name[SIDC_API_CONST_NAME];
    uint32_t value;
} SidcApiConstant;

/* Stored after the constants starting in SBAPI02. The offsets come from the SDK. */
typedef struct {
    uint16_t offsets[SIDC_MSG_FIELDS];
    uint16_t size;
    uint16_t reserved;
} SidcApiMessage;

_Static_assert(sizeof(SidcApiHeader) == 20, "API header layout");
_Static_assert(sizeof(SidcApiCall) == 84, "API call layout");
_Static_assert(sizeof(SidcApiConstant) == 36, "API constant layout");
_Static_assert(sizeof(SidcApiMessage) == 20, "API message layout");

#endif
