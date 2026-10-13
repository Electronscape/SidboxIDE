#ifndef SIDBOX_API_IPC_H
#define SIDBOX_API_IPC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Stage 25: small, bounded, nonblocking inter-applet mailbox.
 * This API is appended to API_ROOT; existing V1/V2 root offsets are unchanged.
 * Applets must use updated SDK headers to access API.ipc.
 * Poll in your own applet/window/timer callback; IPC never invokes receiver
 * code on the sender's stack, and never uses the GUI event queue.
 */
#define SIDBOX_IPC_MAX_DATA       64u
#define SIDBOX_IPC_QUEUE_DEPTH    8u

#define SIDBOX_IPC_OK              0
#define SIDBOX_IPC_EMPTY           1
#define SIDBOX_IPC_BAD_ARG        (-1)
#define SIDBOX_IPC_NO_CONTEXT     (-2)
#define SIDBOX_IPC_NO_RECIPIENT   (-3)
#define SIDBOX_IPC_QUEUE_FULL     (-4)
#define SIDBOX_IPC_NO_MEMORY      (-5)

/* Applet instance IDs, NOT registry slot numbers. A closed/restarted applet
 * has a different ID, preventing sends to a newly reused registry slot. */
typedef struct SIDBOX_IPC_MESSAGE {
    uint32_t sender;  /* sending applet's instance ID; 0 = invalid */
    uint32_t type;    /* application-defined message type */
    uint32_t length;  /* 0..SIDBOX_IPC_MAX_DATA */
    uint8_t  data[SIDBOX_IPC_MAX_DATA];
} SIDBOX_IPC_MESSAGE;

typedef struct API_IPC {
    uint32_t (*self)(void);
    /* Accepts an applet launch path (normalized like CMD launch paths).
     * Returns instance ID or zero if none; no duplicate launches assumed. */
    uint32_t (*find)(const char *path);
    /* On success, makes an OS-owned copy of data. No pointer is shared. */
    int32_t  (*send)(uint32_t recipient, uint32_t type,
                     const void *data, uint32_t length);
    /* Non-blocking: IPC_EMPTY if none, otherwise copies and removes message. */
    int32_t  (*receive)(SIDBOX_IPC_MESSAGE *message);
    /* Number of queued messages for the currently executing applet. */
    uint32_t (*pending)(void);
} API_IPC;

#ifdef __cplusplus
}
#endif
#endif
