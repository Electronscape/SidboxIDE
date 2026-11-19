#ifndef SIDC_APICORE_H
#define SIDC_APICORE_H

#include <stdint.h>

#define SIDC_APICORE_PATH "tfcard:/dev/apicore/apis.bin"
#define SIDC_APICORE_MAGIC "SBAPI01"

enum {
    SIDC_API_CALLS = 8,
    SIDC_API_CONSTANTS = 16,
    SIDC_API_NAME = 32,
    SIDC_API_PARAMS = 7,
    SIDC_API_OFFSETS = 3
};

enum {
    SIDC_API_NULL = 1,
    SIDC_API_STRING,
    SIDC_API_S16,
    SIDC_API_U16,
    SIDC_API_U32,
    SIDC_API_U8
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
    uint8_t reserved;
} SidcApiCall;

typedef struct {
    char name[SIDC_API_NAME];
    uint32_t value;
} SidcApiConstant;

_Static_assert(sizeof(SidcApiHeader) == 20, "API header layout");
_Static_assert(sizeof(SidcApiCall) == 48, "API call layout");
_Static_assert(sizeof(SidcApiConstant) == 36, "API constant layout");

#endif
