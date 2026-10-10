#ifndef SBAPI_SYS_TIMERS_H
#define SBAPI_SYS_TIMERS_H

#include <stdint.h>

typedef struct API_TIMERS {
    void     (*timer1ctrl) (uint16_t ctrlbits);
    void     (*timer1duty) (uint16_t period, uint16_t prescaler);
    void     (*timer1isr)  (void (*isr)(void));
    uint16_t (*timer1val)  (void);

    void     (*timer2ctrl) (uint16_t ctrlbits);
    void     (*timer2duty) (uint16_t period, uint16_t prescaler);
    void     (*timer2isr)  (void (*isr)(void));
    uint16_t (*timer2val)  (void);
} API_TIMERS;

/*
    Timer control bits for timer1ctrl()/timer2ctrl().

    ENABLE:
        Start the timer. Clear this bit to stop it.

    IRQ_ENABLE:
        Call the registered timer ISR on period overflow. The ISR is set with
        timer1isr()/timer2isr(). If this bit is clear, the timer can still run
        without calling app code.

    ONESHOT:
        Stop the timer after the next period overflow. This can be combined with
        IRQ_ENABLE when the app wants a callback at the end of the one-shot.

    RESET:
        Reset the counter to 0 while applying the new control state. This bit is
        an action only; it is not stored as part of the running control state.

    timerXduty(period, prescaler):
        Sets the 16-bit auto-reload period and prescaler. The counter counts up
        from 0 to period, then wraps back to 0 unless ONESHOT stops it.

    timerXval():
        Returns the current 16-bit counter value.

    Timing formula:
        interrupt_hz = timer_clock_hz / ((prescaler + 1) * (period + 1))

        TIM16/TIM17 are on APB2. With the current firmware clock setup,
        PCLK2 is 240 MHz and the APB2 timer clock is 240 MHz.

        If the main clock setup changes, recalculate these values. The values
        passed to timerXduty() are the register values, so they are one less
        than the divider/count lengths.

    Example settings at 240 MHz:
        The same values work for timer2; swap timer1* for timer2*.

        1 second / 1 Hz interrupt:
            timer1isr(my_isr);
            timer1duty(9999, 23999);
            timer1ctrl(API_TIMER_CTRL_RESET |
                       API_TIMER_CTRL_ENABLE |
                       API_TIMER_CTRL_IRQ_ENABLE);

        50 Hz interrupt:
            timer1duty(19999, 239);
            timer1ctrl(API_TIMER_CTRL_RESET |
                       API_TIMER_CTRL_ENABLE |
                       API_TIMER_CTRL_IRQ_ENABLE);

        60 Hz interrupt:
            timer1duty(9999, 399);
            timer1ctrl(API_TIMER_CTRL_RESET |
                       API_TIMER_CTRL_ENABLE |
                       API_TIMER_CTRL_IRQ_ENABLE);

        100 Hz interrupt / 10 ms tick:
            timer1duty(9999, 239);

        1 kHz interrupt / 1 ms tick:
            timer1duty(999, 239);

        One-shot 1 second callback:
            timer1duty(9999, 23999);
            timer1ctrl(API_TIMER_CTRL_RESET |
                       API_TIMER_CTRL_ENABLE |
                       API_TIMER_CTRL_IRQ_ENABLE |
                       API_TIMER_CTRL_ONESHOT);

        1 MHz free-running counter, no app ISR:
            timer1duty(0xffff, 239);
            timer1ctrl(API_TIMER_CTRL_RESET | API_TIMER_CTRL_ENABLE);
*/
#define API_TIMER_CTRL_ENABLE      0x0001u
#define API_TIMER_CTRL_IRQ_ENABLE  0x0002u
#define API_TIMER_CTRL_ONESHOT     0x0004u
#define API_TIMER_CTRL_RESET       0x0008u

#define APITimers                  (API->hwl->timers)

#define timer1ctrl(ctrlbits)       (APITimers->timer1ctrl(ctrlbits))
#define timer1duty(period, presc)  (APITimers->timer1duty(period, presc))
#define timer1isr(isr)             (APITimers->timer1isr(isr))
#define timer1val()                (APITimers->timer1val())

#define timer2ctrl(ctrlbits)       (APITimers->timer2ctrl(ctrlbits))
#define timer2duty(period, presc)  (APITimers->timer2duty(period, presc))
#define timer2isr(isr)             (APITimers->timer2isr(isr))
#define timer2val()                (APITimers->timer2val())

#endif // SBAPI_SYS_TIMERS_H
