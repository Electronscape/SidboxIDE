#include <stdint.h>

/* Stage 18: a loader/relocation probe, NO OS calls, NO libc, NO windows.
 * Distinct return codes are UART-debug only; the firmware logs them after return.
 */
static volatile uint32_t stage18_init_word = UINT32_C(0x18C0FFEE);
static volatile uint32_t stage18_zero_word;
static volatile uint32_t stage18_zero_array[8];
static volatile uint32_t * volatile stage18_rebased_pointer = &stage18_init_word;

__attribute__((used, section(".text.applet_entry")))
int applet_entry(int argc, char **argv) {
    (void)argc;
    (void)argv;
    if (stage18_rebased_pointer != &stage18_init_word) return -1801;
    if (*stage18_rebased_pointer != UINT32_C(0x18C0FFEE)) return -1802;
    if (stage18_zero_word != 0) return -1803;
    for (unsigned i = 0; i < 8; ++i)
        if (stage18_zero_array[i] != 0) return -1804;
    stage18_zero_word = UINT32_C(0xBA5E0018);
    stage18_zero_array[7] = UINT32_C(0x13572468);
    if (stage18_zero_word != UINT32_C(0xBA5E0018) ||
        stage18_zero_array[7] != UINT32_C(0x13572468)) return -1805;
    return 1818;
}
