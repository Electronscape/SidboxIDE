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
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include "apis.h"



#define HEAP_START   ((uintptr_t)&__app_end)
#define HEAP_END     ((uintptr_t)(SDRAM_BASE + SDRAM_SIZE))

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

void* heap_base = (void*)(&__app_end);
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
    heap_size = (SDRAM_BASE + SDRAM_SIZE) - (uint32_t)&__app_end;
}

__attribute__((section(".header")))
const char sdex_header[8] = { 'S', 'B', 'A', 'P', 'X', '5', 'O', '2' };

__attribute__((section(".thestart")))
const uint32_t sdex_startaddr = (uint32_t)&_appstart;

extern void __libc_init_array(void);
__attribute__((section(".text.applet_entry")))
int applet_entry(int argc, char *argv[]) {
    setbuf(stdout, NULL); // might need these
    setbuf(stderr, NULL);
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
    if (inc >= 0) {
        next = heap_end_u + (uintptr_t)inc;
    } else {
        uintptr_t dec = (uintptr_t)(-inc);
        next = heap_end_u - dec;
    }

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
