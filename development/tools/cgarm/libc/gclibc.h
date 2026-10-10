#ifndef CGARM_GCLIBC_H
#define CGARM_GCLIBC_H

/* CGARM freestanding C runtime; this header is internal to the SDK.
 * Applets should continue to use <stdio.h>, <stdlib.h>, <string.h>, etc.
 * The toolchain's C headers provide normal standard-library declarations.
 */
#ifndef SIDBOX_APPLET_V2
#error "CGARM libc sources must be built only for the V2/CGARM applet target"
#endif

#define CGARM_LIBC_VERSION_MAJOR 0
#define CGARM_LIBC_VERSION_MINOR 1

#endif
