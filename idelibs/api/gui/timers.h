#ifndef SBAPI_TIMERS_H
#define SBAPI_TIMERS_H

#include <stdint.h>
#include "window.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t CGTimer;

/*
    call back functions must be in static
    to make timers work in GUI, a window must be created first (windows handle OS events)
static void tmrcallbackproc(void *user){
}

*/

#define CGTIMER_INVALID         ((CGTimer)0xFF)
#define SBOS_MAX_TIMERS         32
#define SBOS_TIMER_SYS_RESERVED 4

typedef void (*SBOS_TimerCB)(void *user);

// System OS Timers call //
typedef struct API_SYS_TIMERS {
    CGTimer (*create) (void);
    void    (*free)   (CGTimer t);
    int     (*set)    (CGTimer t, uint32_t delay_ms, uint32_t period_ms, SBOS_TimerCB cb, void *user);
    void    (*cancel) (CGTimer t);
} API_SYS_TIMERS;

/* @brief Allocates a GUI/OS timer and returns its timer handle. */
#define SBOS_CreateTimer()  (GUICoderGirl->timers->create())
/* @brief Releases a previously allocated GUI/OS timer. */
#define SBOS_FreeTimer(timer)  (GUICoderGirl->timers->free(timer))

/* @brief Starts/configures a timer with delay, repeat period, callback and user pointer. */
#define SBOS_TimerSet(timer, delay_ms, period_ms, callback, user)  (GUICoderGirl->timers->set(timer, delay_ms, period_ms, callback, user))

/* @brief Cancels a running GUI/OS timer without freeing its handle. */
#define SBOS_TimerCancel(timer)  (GUICoderGirl->timers->cancel(timer))

#ifdef __cplusplus
}
#endif

#endif // SBAPI_TIMERS_H
