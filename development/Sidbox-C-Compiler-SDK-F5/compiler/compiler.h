#ifndef SIDC_COMPILER_H
#define SIDC_COMPILER_H

#include <stdint.h>

#define SIDC_SOURCE_LIMIT (128u * 1024u)
#define SIDC_MAX_SOURCES 16u

typedef struct {
    const char *message;
    uint32_t line;
    uint32_t column;
    uint32_t file_index;  /* source index, zero for single-file compilation */
} SidcDiagnostic;

typedef uint32_t (*SidcReadApiCore)(void *buffer, uint32_t capacity);

typedef struct {
    const char *source;
    uint32_t length;
} SidcSource;

/* The image is valid until the next compile. A return of zero is an error. */
uint32_t sidc_compile(const char *source, uint32_t length,
                      SidcReadApiCore read_apicore,
                      const void **app, SidcDiagnostic *diagnostic);

/* Source buffers must remain valid for the entire call. The 128 KiB limit
   applies to the sum of all input sources. */
uint32_t sidc_compile_sources(const SidcSource *sources, uint32_t count,
                              SidcReadApiCore read_apicore,
                              const void **app, SidcDiagnostic *diagnostic);

#endif
