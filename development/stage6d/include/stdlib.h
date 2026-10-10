#ifndef SIDBOX_STAGE5B_HOST_SHIM_STDLIB_H
#define SIDBOX_STAGE5B_HOST_SHIM_STDLIB_H
#include <stddef.h>
void *malloc(size_t);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void free(void *);
#endif
