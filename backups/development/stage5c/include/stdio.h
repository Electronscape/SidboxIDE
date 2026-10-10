#ifndef STAGE5_TEST_STDIO_H
#define STAGE5_TEST_STDIO_H
#include <stddef.h>
typedef struct FILE FILE;
extern FILE *stdout;
extern FILE *stderr;
void setbuf(FILE *stream, char *buffer);
#endif
