#ifndef SIDC_COMPILER_H
#define SIDC_COMPILER_H

/* Firmware applets must use the SD-backed backend.  Some SidboxIDE project
   builds do not propagate compiler.extraFlags consistently; when targeting
   the ARM/Thumb processor, select streaming here in the shared header so
   compiler.c and main.c cannot silently fall back to the 1 MiB RAM backend.
   Desktop/host builds without SIDC_STREAM_BUILD retain the legacy mode for
   byte-for-byte regression testing. */
#if !defined(SIDC_STREAM_BUILD) && (defined(__arm__) || defined(__thumb__))
#define SIDC_STREAM_BUILD 1
#endif

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

/* SD-backed code generation. Offsets for image writes include the 64-byte
   V2 header; initializer scratch offsets start at zero. Return 0 on I/O error.
   The callbacks must provide read-your-writes semantics. */
typedef struct {
    void *context;
    int (*write)(void *context, int initializer, uint32_t offset,
                 const void *bytes, uint32_t length);
    int (*read)(void *context, int initializer, uint32_t offset,
                void *bytes, uint32_t length);
} SidcStreamIO;

/* Optional progress reporting. The compiler calls this synchronously on
   discrete milestones (not for every instruction). completed/total are
   bytes for parsing and CRC, and references for link patching.
   total == 0 indicates a stage announcement without a percentage. */
#ifdef SIDC_STREAM_BUILD
typedef void (*SidcProgress)(void *context, const char *phase,
                             uint32_t completed, uint32_t total);
void sidc_set_progress_callback(SidcProgress callback, void *context);

/* Cooperative SD build: begin once, call step from a GUI timer, then end.
   step: 0 = working, 1 = complete, -1 = diagnostic/I/O failure.
   All input buffers must stay valid until end() is called. */
int sidc_job_begin(const SidcSource *sources,
                   const char *const *source_paths, uint32_t count,
                   SidcReadApiCore read_apicore, SidcReadHeader read_header,
                   const SidcStreamIO *io, SidcDiagnostic *diagnostic);
int sidc_job_step(uint32_t work_budget, uint32_t *file_bytes);
void sidc_job_end(void);
#endif

/* Write a complete validated V2 file via SD-backed random-access callbacks.
   The output file is committed only after this returns nonzero. */
uint32_t sidc_compile_project_stream(const SidcSource *sources,
                            const char *const *source_paths, uint32_t count,
                            SidcReadApiCore read_apicore, SidcReadHeader read_header,
                            const SidcStreamIO *io, SidcDiagnostic *diagnostic);

#ifndef SIDC_STREAM_BUILD
/* Legacy in-memory mode is retained for host byte-comparison testing. */
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

#endif /* !SIDC_STREAM_BUILD */
#endif
