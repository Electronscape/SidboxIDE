#include <stdint.h>
#include "apis.h"
#include "crt.h"

#define bool uint8_t



static inline void CRT_put_pixel(int16_t x, int16_t y, uint8_t colour, uint8_t *crt_pixel_buffer)
{
    if (x < 0 || y < 0 || x >= (int16_t)API_CRT_WIDTH || y >= (int16_t)API_CRT_HEIGHT) {
        return;
    }

    crt_pixel_buffer[((uint32_t)x * API_CRT_HEIGHT) + (uint32_t)y] = (uint8_t)(colour & 0x0Fu);
}

void CRT_DrawImage(uint8_t *src, int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t *crt_pixel_buffer)
{
    if (!src || !crt_pixel_buffer) return;

    // Early exit if completely off-screen
    if (x >= (int16_t)API_CRT_WIDTH || y >= (int16_t)API_CRT_HEIGHT || 
        (x + (int16_t)width) <= 0 || (y + (int16_t)height) <= 0) {
        return;
    }

    uint32_t src_idx = 0;

    for (uint16_t py = 0; py < height; py++) {
        int16_t target_y = y + py;
        bool y_valid = (target_y >= 0 && target_y < (int16_t)API_CRT_HEIGHT);

        for (uint16_t px = 0; px < width; px += 2) {
            uint8_t packed_byte = src[src_idx++];

            if (y_valid) {
                // Pixel 1 (lower 4 bits)
                int16_t target_x1 = x + px;
                if (target_x1 >= 0 && target_x1 < (int16_t)API_CRT_WIDTH) {
                    crt_pixel_buffer[((uint32_t)target_x1 * API_CRT_HEIGHT) + (uint32_t)target_y] = packed_byte & 0x0Fu;
                }

                // Pixel 2 (upper 4 bits)
                if ((px + 1) < width) {
                    int16_t target_x2 = target_x1 + 1;
                    if (target_x2 >= 0 && target_x2 < (int16_t)API_CRT_WIDTH) {
                        crt_pixel_buffer[((uint32_t)target_x2 * API_CRT_HEIGHT) + (uint32_t)target_y] = (packed_byte >> 4) & 0x0Fu;
                    }
                }
            }
        }
    }
}


// this was changed: corrected row-major source layout iteration to prevent horizontal split/mirroring
void CRT_FrameImage(uint8_t *src, uint8_t *crt_pixel_buffer)
{
    if (!src || !crt_pixel_buffer) return;

    uint32_t src_idx = 0;

    for (uint16_t py = 0; py < API_CRT_HEIGHT; py++) {
        for (uint16_t px = 0; px < API_CRT_WIDTH; px += 2) {
            uint8_t packed_byte = src[src_idx++];

            // Unpack lower 4 bits (Pixel 1) and upper 4 bits (Pixel 2)
            uint8_t p1 = packed_byte & 0x0Fu;
            uint8_t p2 = (packed_byte >> 4) & 0x0Fu;

            // Target column-major offsets: (x * API_CRT_HEIGHT) + y
            uint32_t col_offset1 = ((uint32_t)px * API_CRT_HEIGHT) + py;
            uint32_t col_offset2 = (((uint32_t)px + 1) * API_CRT_HEIGHT) + py;

            // Store directly into column-major CRT framebuffer
            crt_pixel_buffer[col_offset1] = p1;
            if ((px + 1) < API_CRT_WIDTH) {
                crt_pixel_buffer[col_offset2] = p2;
            }
        }
    }
}