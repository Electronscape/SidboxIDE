#ifndef SIDBOX_API_SYS_UART1_H
#define SIDBOX_API_SYS_UART1_H
#include <stdint.h>
/* Append-only EBI extension. Existing applets remain binary compatible. */
#define SIDBOX_UART1_PARITY_NONE 0u
#define SIDBOX_UART1_PARITY_EVEN 1u
#define SIDBOX_UART1_PARITY_ODD 2u
#define SIDBOX_UART1_OK 0
#define SIDBOX_UART1_BUSY (-1)
#define SIDBOX_UART1_NOT_OWNER (-2)
#define SIDBOX_UART1_INVALID_CONFIG (-3)
#define SIDBOX_UART1_HARDWARE_ERROR (-4)
typedef struct API_SYS_UART1 {
    int32_t (*open)(uint32_t baud, uint8_t dataBits, uint8_t parity, uint8_t stopBits);
    int32_t (*close)(void);
    int32_t (*read)(uint8_t *dst, uint32_t count);
    int32_t (*write)(const uint8_t *src, uint32_t count);
    int32_t (*available)(void);
} API_SYS_UART1;
/* These macros require apis.h's API pointer to be visible. */
#define SBOS_UART1_Open(baud,bits,parity,stops) (API->uart1->open((baud),(bits),(parity),(stops)))
#define SBOS_UART1_Close() (API->uart1->close())
#define SBOS_UART1_Read(ptr,count) (API->uart1->read((ptr),(count)))
#define SBOS_UART1_Write(ptr,count) (API->uart1->write((ptr),(count)))
#define SBOS_UART1_Available() (API->uart1->available())

#endif /* SIDBOX_API_SYS_UART1_H */
