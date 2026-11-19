#ifndef SIDC_COMPILER_H
#define SIDC_COMPILER_H

#include <stdint.h>

#define SIDC_SOURCE_LIMIT 8192u

typedef struct {
    const char *message;
    uint32_t line;
    uint32_t column;
} SidcDiagnostic;

typedef uint32_t (*SidcReadApiCore)(void *buffer, uint32_t capacity);

/* The image is valid until the next compile. A return of zero is an error. */
uint32_t sidc_compile(const char *source, uint32_t length,
                      SidcReadApiCore read_apicore,
                      const void **app, SidcDiagnostic *diagnostic);

#endif
