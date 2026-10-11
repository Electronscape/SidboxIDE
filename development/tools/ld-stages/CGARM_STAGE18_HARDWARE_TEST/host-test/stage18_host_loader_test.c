/* Host-side reimplementation of cmd_v2_launch_test's binary handling using
 * the *actual* firmware SBV2_ValidateHeader, CRC32 and RelocateWord functions.
 * This does NOT execute Thumb machine code; actual success needs SIDBOX.
 */
#include "applet_v2_format.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void die(const char *what) { fprintf(stderr, "FAIL: %s\n", what); exit(1); }
static uint32_t rd32(const void *p) { uint32_t v; memcpy(&v, p, 4); return v; }

static int load_at(const uint8_t *file, size_t file_len, uint32_t base, int mutate) {
    SBV2Header h;
    if (file_len < 64 || file_len > 1024*1024) return 0;
    memcpy(&h, file, sizeof(h));
    if (!SBV2_ValidateHeader(&h, (uint32_t)file_len, 256*1024, 512*1024)) return 0;
    if (h.memory_size > 0x600000u || base < 0xD0500000u ||
        base > 0xD0600000u - h.memory_size) return 0;

    uint8_t *memory = (uint8_t *)calloc(1, h.memory_size);
    if (!memory) die("cannot allocate host shadow RAM");
    memcpy(memory, file + 64, h.image_size);
    if (mutate == 1) memory[3] ^= 1; /* CRC corruption */
    if (SBV2_CRC32(memory, h.image_size) != h.image_crc32) {
        free(memory); return 0;
    }
    if (h.relocation_count != 1) { free(memory); return 0; } /* Stage18 probe */
    uint32_t prev=0;
    for (uint32_t i=0; i<h.relocation_count; ++i) {
        uint32_t site=rd32(file+h.relocation_offset+i*4u);
        if ((i && site<=prev) || (site&3u) || h.image_size<4 || site>h.image_size-4) {
            free(memory); return 0;
        }
        prev=site;
        if (mutate==2) {
            /* Recompute image CRC as a malicious/corrupted-but-otherwise-valid file would. */
            uint32_t outside = h.link_base + h.memory_size + 32u;
            memcpy(memory+site,&outside,4);
        }
        if (!SBV2_RelocateWord((uint32_t *)(void *)(memory+site),site,&h,base)) {
            free(memory); return 0;
        }
        uint32_t pointer=rd32(memory+site);
        if (pointer<base || pointer-base>h.image_size-4u ||
            rd32(memory+(pointer-base))!=0x18C0FFEEu) {
            free(memory); return 0;
        }
    }
    /* Firmware RAM_ClearRange() clears the BSS/stack/heap before copying. */
    for (uint32_t i=h.image_size; i<h.memory_size; ++i)
        if (memory[i]!=0) { free(memory); return 0; }
    free(memory);
    return 1;
}

int main(int argc,char **argv) {
    if (argc!=3) die("usage: stage18_host_loader_test CGARM.app LLVM.app");
    for (int n=1;n<argc;++n) {
        FILE *fp=fopen(argv[n],"rb"); if (!fp) die("cannot open applet");
        if (fseek(fp,0,SEEK_END)) die("seek end");
        long sz=ftell(fp); if (sz<0 || sz>1024*1024) die("applet size");
        rewind(fp); uint8_t *file=(uint8_t*)malloc((size_t)sz);
        if (!file) die("malloc file");
        if (fread(file,1,(size_t)sz,fp)!=(size_t)sz) die("read applet");
        fclose(fp);
        SBV2Header hdr; memcpy(&hdr,file,sizeof(hdr));
        printf("Applet: %s (%ld bytes; image=%u; RAM=%u; stack=%u; heap=%u; runtime relocs=%u)\n",
               argv[n],sz,hdr.image_size,hdr.memory_size,hdr.reserved,hdr.heap_size,hdr.relocation_count);
        if(!load_at(file,(size_t)sz,0xD0500000u,0)) die("firmware contract failed at SDRAM floor");
        if(!load_at(file,(size_t)sz,0xD05F0000u,0)) die("firmware contract failed at alternate SDRAM base");
        if(load_at(file,(size_t)sz,0xD0500000u,1)) die("CRC corruption not rejected");
        if(load_at(file,(size_t)sz,0xD0500000u,2)) die("out-of-range relocated pointer not rejected");
        printf("  PASS: firmware-format header, image CRC, exact relocated probe pointer, two bases, zero RAM, two negative tests\n");
        free(file);
    }
    puts("PASS: Both Stage 18 applets match the supplied firmware's binary loader contract.\n"
         "NOTE: Host shadow RAM does NOT execute ARM code. Hardware result remains untested.");
    return 0;
}
