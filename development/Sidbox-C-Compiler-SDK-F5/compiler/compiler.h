#ifndef SIDC_COMPILER_H
#define SIDC_COMPILER_H

#include <stdint.h>

#define SIDC_SOURCE_LIMIT (1024u * 1024u)
#define SIDC_MAX_SOURCES 16u

typedef struct {
    const char *message;
    uint32_t line;
    uint32_t column;
    uint32_t file_index;  /* source index, zero for single-file compilation */
    const char *path;    /* non-NULL for errors inside an included header */
} SidcDiagnostic;

typedef uint32_t (*SidcReadApiCore)(void *buffer, uint32_t capacity);

/* Resolve a quoted include relative to the including source/header path.
   buffer == NULL requests path resolution without opening a file.
   On success, supply the canonical project path in resolved_path. */
typedef int (*SidcReadHeader)(const char *including_path,
                              const char *header_name,
                              char *buffer, uint32_t capacity,
                              uint32_t *length,
                              char *resolved_path, uint32_t path_capacity);

typedef struct {
    const char *source;
    uint32_t length;
} SidcSource;

/* The image is valid until the next compile. A return of zero is an error. */
uint32_t sidc_compile(const char *source, uint32_t length,
                      SidcReadApiCore read_apicore,
                      const void **app, SidcDiagnostic *diagnostic);

/* Source buffers must remain valid for the entire call. The 1 MiB limit
   applies to the sum of all input sources. */
uint32_t sidc_compile_sources(const SidcSource *sources, uint32_t count,
                              SidcReadApiCore read_apicore,
                              const void **app, SidcDiagnostic *diagnostic);

/* Like sidc_compile_sources, with local quoted-header support. Source names
   are full source paths, valid for the duration of the compilation. */
uint32_t sidc_compile_project(const SidcSource *sources,
                              const char *const *source_paths, uint32_t count,
                              SidcReadApiCore read_apicore,
                              SidcReadHeader read_header,
                              const void **app, SidcDiagnostic *diagnostic);

#endif
