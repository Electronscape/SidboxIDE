#ifndef SIDBOX_APPLET_V2_FORMAT_H
#define SIDBOX_APPLET_V2_FORMAT_H

/*
 * Experimental SIDBOX GUI applet v2 disk header.
 * This header intentionally uses only C99/stdint so the exact validation and
 * byte relocations can be tested on a desktop before touching hardware.
 * NOT a general ELF loader. Only packer-validated R_ARM_RELATIVE sites are used.
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define SBV2_HEADER_SIZE 64u
#define SBV2_VERSION 2u
#define SBV2_ALIGN 32u
#define SBV2_MAGIC_BYTES "SBAPV2\0\0"
/* Opt-in automatic process stack. Original v2 files have flags=reserved=0. */
#define SBV2_FLAG_PRIVATE_PSP 0x00000001u
#define SBV2_STACK_MIN_BYTES 4096u

typedef struct {
    uint8_t magic[8];
    uint32_t version;
    uint32_t header_size;
    uint32_t file_size;
    uint32_t image_size;
    uint32_t memory_size;
    uint32_t entry_offset;
    uint32_t link_base;
    uint32_t relocation_offset;
    uint32_t relocation_count;
    uint32_t alignment;
    uint32_t heap_size;
    uint32_t reserved;  /* stack bytes ONLY with SBV2_FLAG_PRIVATE_PSP; otherwise 0 */
    uint32_t flags;
    uint32_t image_crc32;
} SBV2Header;

typedef char sbv2_header_must_be_64_bytes[(sizeof(SBV2Header) == SBV2_HEADER_SIZE) ? 1 : -1];

static inline uint32_t SBV2_CRC32(const void *data, uint32_t count)
{
    uint32_t crc = 0xffffffffu;
    const uint8_t *p = (const uint8_t *)data;
    for (uint32_t i = 0; i < count; ++i) {
        crc ^= p[i];
        for (uint32_t bit = 0; bit < 8u; ++bit)
            crc = (crc >> 1) ^ ((crc & 1u) ? 0xedb88320u : 0u);
    }
    return ~crc;
}

/* Validate every untrusted size before an SDRAM write or a seek. */
static inline int SBV2_ValidateHeader(const SBV2Header *h, uint32_t actual_file_size,
                                       uint32_t max_image_bytes, uint32_t max_memory_bytes)
{
    if (memcmp(h->magic, SBV2_MAGIC_BYTES, 8) != 0 ||
        h->version != SBV2_VERSION || h->header_size != SBV2_HEADER_SIZE ||
        h->file_size != actual_file_size ||
        h->alignment != SBV2_ALIGN ||
        (h->flags != 0u && h->flags != SBV2_FLAG_PRIVATE_PSP))
        return 0;

    if (h->image_size == 0u || h->image_size > max_image_bytes ||
        h->memory_size == 0u || h->memory_size > max_memory_bytes ||
        (h->memory_size & 31u) != 0u || h->image_size > h->memory_size ||
        h->heap_size > h->memory_size - h->image_size)
        return 0;

    if (h->flags == 0u) {
        if (h->reserved != 0u) return 0;
    } else {
        /* Require a declared, aligned stack, physically disjoint from the
         * initialized image and the heap. Legacy v2 remains unchanged. */
        if (h->reserved < SBV2_STACK_MIN_BYTES ||
            (h->reserved & 31u) != 0u || (h->heap_size & 31u) != 0u ||
            h->reserved > h->memory_size - h->heap_size ||
            h->reserved > h->memory_size - h->heap_size - h->image_size)
            return 0;
    }

    if (h->entry_offset == 0u || (h->entry_offset & 1u) == 0u ||
        (h->entry_offset & ~1u) >= h->image_size)
        return 0;

    /* Image is copied at image base, NOT including the on-disk header. */
    if (h->relocation_offset < SBV2_HEADER_SIZE ||
        h->image_size > h->relocation_offset - SBV2_HEADER_SIZE ||
        h->relocation_offset > actual_file_size ||
        (h->relocation_offset & 3u) != 0u)
        return 0;

    if ((actual_file_size - h->relocation_offset) % 4u != 0u ||
        h->relocation_count != (actual_file_size - h->relocation_offset) / 4u)
        return 0;

    /* Original link-time addresses must not overflow 32-bit arithmetic. */
    if (h->link_base < 0xd0000000u || h->link_base >= 0xd0600000u ||
        h->memory_size > 0xd0600000u - h->link_base)
        return 0;
    return 1;
}

/* Relocation source is a 32-bit word within the initialized image.
 * Only applet-internal 32-bit addresses are allowed, including Thumb pointers.
 */
static inline int SBV2_RelocateWord(uint32_t *dst, uint32_t site_offset,
                                   const SBV2Header *h, uint32_t actual_base)
{
    uint32_t original;
    uint32_t target;
    uint32_t thumb;
    uint32_t offset;

    if ((site_offset & 3u) != 0u || h->image_size < 4u ||
        site_offset > h->image_size - 4u ||
        actual_base > 0xffffffffu - h->memory_size)
        return 0;

    memcpy(&original, dst, sizeof(original));
    thumb = original & 1u;
    target = original & ~1u;
    if (target < h->link_base)
        return 0;
    offset = target - h->link_base;
    if (offset >= h->memory_size)
        return 0;
    target = (actual_base + offset) | thumb;
    memcpy(dst, &target, sizeof(target));
    return 1;
}

#endif
