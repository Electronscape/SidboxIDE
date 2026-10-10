// Standard System Calls, 
// needed for basic applet softwares.

//############################################################################################################//
//#                                                                                                          #//
//#   SIDBOX APPLET RUNTIME — SYSTEM CALL STUBS + APPLET ENTRY                                               #//
//#                                                                                                          #//
//#   Purpose: Provide the minimum libc/syscall glue required for applets to link and run                    #//
//#            under SIDBOX without a full POSIX environment.                                                #//
//#                                                                                                          #//
//#   Notes:                                                                                                 #//
//#   • These syscalls are intentionally minimal / stubbed.                                                  #//
//#   • Many functions return "not supported" by design (ENOSYS), or dummy success where safe.               #//
//#   • Applets enter through applet_entry(argc, argv) which dispatches to main().                           #//
//#                                                                                                          #//
//#   Memory model:                                                                                          #//
//#   • Applet image provides __app_end (end of loaded program) which is used as the heap base.              #//
//#   • SDRAM is used for heap expansion and large allocations.                                              #//
//#   • _sbrk() implements a basic bump allocator for malloc/newlib.                                         #//
//#                                                                                                          #//
//#   SDEX metadata:                                                                                         #//
//#   • .header contains an "SDEXPROG" signature for loader identification.                                  #//
//#   • .thestart exposes the runtime start address for the loader / debugger.                               #//
//#                                                                                                          #//
//#   Warning (intentional constraints):                                                                     #//
//#   • _exit() traps forever: SIDBOX applets do not "return to an OS shell" via POSIX semantics.            #//
//#   • _write() is a no-op stub here: printing should go through the SIDBOX API (API.sys->printf, etc.).    #//
//#   • If you need full file IO, use the SIDBOX filesystem APIs rather than these stubs.                    #//
//#                                                                                                          #//
//############################################################################################################//


#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include "apis.h"



#ifdef SIDBOX_APPLET_V2
/* V2 heap begins beyond .bss + stack reserve. Firmware has allocated the
 * additional heap bytes from SBV2Header.heap_size and keeps that range owned
 * by this applet. It cannot grow into the next applet or the RAM disk. */
extern uint8_t __v2_heap_start__;
#define HEAP_START ((uintptr_t)&__v2_heap_start__)
#ifndef SIDBOX_V2_HEAP_BYTES
#define SIDBOX_V2_HEAP_BYTES (16u * 1024u)
#endif
#define HEAP_END   (HEAP_START + (uintptr_t)SIDBOX_V2_HEAP_BYTES)
#else
#define HEAP_START ((uintptr_t)&__app_end)
#define HEAP_END   ((uintptr_t)(SDRAM_BASE + SDRAM_SIZE))
#endif

static uintptr_t heap_end_u = 0;


extern uint32_t  _appstart;
extern uint8_t   __app_end;

#define SDRAM_BASE      0xD0000000
#define SDRAM_SIZE      (6 * 1024 * 1024) // 6MB total 
#define SDRAM_END       (SDRAM_BASE + SDRAM_SIZE)

void disable_irq(void)
{
    __asm volatile ("cpsid i" : : : "memory");
}

void enable_irq(void)
{
    __asm volatile ("cpsie i" : : : "memory");
}

static inline uint32_t irq_save(void)
{
    uint32_t primask;
    __asm volatile ("mrs %0, primask" : "=r"(primask) :: "memory");
    __asm volatile ("cpsid i" : : : "memory");
    return primask;
}

static inline void irq_restore(uint32_t primask)
{
    __asm volatile ("msr primask, %0" : : "r"(primask) : "memory");
}

extern int main(int argc, char *argv[]);    // our program entry point

#ifdef SIDBOX_APPLET_V2
void* heap_base = NULL; /* set at runtime; symbol can be exactly one past .bss+.stack */
#else
void* heap_base = (void*)(&__app_end);
#endif
uint32_t heap_size;

extern char _end; // defined in linker script


int ExitTimer = 0;
int ExitCode(){  
    return(0);
}



// example test
void doPrintTest(){
    API->gui->console->printf(0, "APPLET TEST V3");
}

void doWriteTest(){
    API->gui->console->writec(0, "hello write c\n", 14);
}

//---------------------------------------------------------------------------//


///////////////// [ SIDBOX STDLIB ] ////////////////////////////////////////////////////////////////////////
void initMalloc(){
#ifdef SIDBOX_APPLET_V2
    heap_size = SIDBOX_V2_HEAP_BYTES;
    heap_base = (void*)HEAP_START;
#else
    heap_size = (SDRAM_BASE + SDRAM_SIZE) - (uint32_t)&__app_end;
#endif
}

#ifndef SIDBOX_STARTUP_HEADER_IN_ASM
__attribute__((section(".header")))
const char sdex_header[8] = { 'S', 'B', 'A', 'P', 'X', '5', 'O', '2' };
#endif

#ifndef SIDBOX_APPLET_V2
__attribute__((section(".thestart")))
const uint32_t sdex_startaddr = (uint32_t)&_appstart;
#endif

extern void __libc_init_array(void);
__attribute__((section(".text.applet_entry")))
int applet_entry(int argc, char *argv[]) {
#ifdef SIDBOX_APPLET_V2
    initMalloc();
#endif
#ifndef SIDBOX_APPLET_V2
    // Preserve the existing legacy V1 stdio initialisation unchanged.
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
#else
    // V2 stays freestanding: setbuf() would pull in Newlib's non-PIC
    // _impure_ptr/stdio state even for a simple GUI with no printf calls.
    // Use CoderGirl's console APIs for V2 diagnostic output.
#endif
    return main(argc, argv);
}



int _write(int fd, const void *buf, size_t count) {
    if (fd != 1 && fd != 2) { errno = EBADF; return -1; }
    if (!buf || !count) return 0;

    //API->gui->console->writec(0, (const char*)buf, (uint32_t)count);

    // -- no longer crashes ---
    static volatile int in_write = 0;
    if (in_write) return (int)count;
    in_write = 1;
    API->gui->console->writec(0, (const char*)buf, (uint32_t)count);
    in_write = 0;
    // -------------------

    return (int)count;
}

// If your newlib uses re-entrant syscalls (very common)
int _write_r(void *r, int fd, const void *buf, size_t count) {
    (void)r;
    return _write(fd, buf, count);
}

int _read(int fd, void *buf, size_t count) {
    errno = ENOSYS;
    return -1;
}

int _close(int fd) {
    return -1;
}

int _fstat(int fd, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _lseek(int fd, int ptr, int dir) {
    return 0;
}

/*
void *_sbrk(ptrdiff_t incr) {
    extern char _end; // defined in linker script
    static char *heap_end;
    if (!heap_end) heap_end = &_end;
    char *prev_heap_end = heap_end;
    heap_end += incr;
    return prev_heap_end;
}
*/

void *_sbrk(ptrdiff_t incr)
{
    if (heap_end_u == 0) {
        heap_end_u = (HEAP_START + 7u) & ~((uintptr_t)7u);
    }

    uintptr_t prev = heap_end_u;
    intptr_t inc = (intptr_t)incr;

    uintptr_t next;
#ifdef SIDBOX_APPLET_V2
    if (inc >= 0) {
        if ((uintptr_t)inc > HEAP_END - heap_end_u) {
            errno = ENOMEM;
            return (void*)-1;
        }
        next = heap_end_u + (uintptr_t)inc;
    } else {
        /* Avoid UB on PTRDIFF_MIN and do not subtract beyond heap start. */
        uintptr_t dec = (uintptr_t)(-(inc + 1)) + 1u;
        if (dec > heap_end_u - HEAP_START) {
            errno = ENOMEM;
            return (void*)-1;
        }
        next = heap_end_u - dec;
    }
#else
    /* Preserve the legacy bump allocator exactly in V1 applets. */
    if (inc >= 0) {
        next = heap_end_u + (uintptr_t)inc;
    } else {
        uintptr_t dec = (uintptr_t)(-inc);
        next = heap_end_u - dec;
    }
#endif

    if (next < HEAP_START || next > HEAP_END) {
        errno = ENOMEM;
        return (void*)-1;
    }

    heap_end_u = next;
    return (void*)prev;
}

void *_sbrk_r(void *reent, ptrdiff_t incr)
{
    (void)reent;
    return _sbrk(incr);
}



int _isatty(int fd) {
    return 1;
}

void _exit(int code) {
    (void)code;
    while (1); // Trap here forever
}

int _getpid(void) {
    return 1;
}

int _kill(int pid, int sig) {
    (void)pid;
    (void)sig;
    return -1;
}


//------------------------------------------------------------------------------------------------------------//
//  Supported / Stubbed System Calls (SIDBOX Applet Runtime)
//
//  This runtime does NOT implement a full POSIX environment.
//  The functions below exist solely to satisfy libc/newlib linkage
//  and to provide minimal compatibility where safe.
//
//  Applet authors MUST use the SIDBOX APIs for real functionality.
//
//  ┌─────────────┬────────────────────────────────────────────┐
//  │ Function    │ Behaviour                                  │
//  ├─────────────┼────────────────────────────────────────────┤
//  │ _write()    │ Stub: returns count, data is discarded     │
//  │             │ Use: API.sys->printf / API.gui->console    │
//  │             │                                            │
//  │ _read()     │ Not supported (ENOSYS)                     │
//  │ _close()    │ Not supported                              │
//  │ _lseek()    │ Stub: returns 0                            │
//  │ _fstat()    │ Stub: reports character device             │
//  │ _isatty()   │ Always true                                │
//  │ _getpid()   │ Stub: returns 1                            │
//  │ _kill()     │ Not supported                              │
//  │             |                                            │
//  │ _sbrk()     │ Minimal heap bump allocator                │
//  │             │ Heap starts at __app_end and grows upward  │
//  │             │ Uses SDRAM region                          │
//  │             |                                            │
//  │ _exit()     │ Trap forever (no process teardown)         │
//  └─────────────┴────────────────────────────────────────────┘
//
//  Important:
//  • These calls are NOT thread-safe.
//  • File I/O must be performed through SIDBOX FS APIs.
//  • Printing through printf()/puts() is discouraged.
//  • Applets are expected to be cooperative and well-behaved.
//
//------------------------------------------------------------------------------------------------------------//
