/* Host test for exact format logic shared with Core/os/cmd.c. No hardware. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "applet_v2_format.h"

static void die(const char *why){ fprintf(stderr, "FAIL: %s\n",why); exit(1); }
#define REQUIRE(x) do { if (!(x)) die(#x); } while(0)

static unsigned char *load(const char *filename, uint32_t *size){
    FILE *f=fopen(filename, "rb");
    long bytes;
    unsigned char *out;
    if (!f) die("open app");
    REQUIRE(fseek(f,0,SEEK_END)==0);
    bytes=ftell(f); REQUIRE(bytes>64 && bytes<1024*1024);
    REQUIRE(fseek(f,0,SEEK_SET)==0);
    out=(unsigned char*)malloc((size_t)bytes); REQUIRE(out!=NULL);
    REQUIRE(fread(out,1,(size_t)bytes,f)==(size_t)bytes);
    fclose(f); *size=(uint32_t)bytes;
    return out;
}
static void test_relocate(const unsigned char *raw,const SBV2Header *h,uint32_t addr){
    unsigned char *mem=(unsigned char*)calloc(h->memory_size,1);
    uint32_t prev=0;
    REQUIRE(mem!=NULL);
    memcpy(mem,raw+64,h->image_size);
    REQUIRE(SBV2_CRC32(mem,h->image_size)==h->image_crc32);
    for (uint32_t i=0;i<h->relocation_count;i++){
        uint32_t site, before, after;
        memcpy(&site,raw+h->relocation_offset+4u*i,4);
        REQUIRE((i==0 || site>prev) && (site & 3u)==0u && site <= h->image_size-4u);
        prev=site;
        memcpy(&before,mem+site,4);
        REQUIRE(SBV2_RelocateWord((uint32_t*)(void*)(mem+site),site,h,addr));
        memcpy(&after,mem+site,4);
        REQUIRE(after == before - h->link_base + addr);
        REQUIRE((before & 1u)==(after & 1u));
    }
    free(mem);
}
int main(int argc,char **argv){
    uint32_t size;
    unsigned char *raw;
    SBV2Header h;
    if (argc!=2){fprintf(stderr,"Usage: v2_format_test <sample.app>\n"); return 2;}
    raw=load(argv[1], &size);
    memcpy(&h,raw,sizeof(h));
    REQUIRE(sizeof(h)==64);
    REQUIRE(SBV2_ValidateHeader(&h,size,256u*1024u,512u*1024u));
    REQUIRE(h.relocation_count>0u);
    test_relocate(raw,&h,0xD0500000u);
    test_relocate(raw,&h,0xD0580000u);
    /* Regression: corrupted/truncated/malicious header fields must fail. */
    {SBV2Header corrupted=h; corrupted.image_size=corrupted.memory_size+1;
     REQUIRE(!SBV2_ValidateHeader(&corrupted,size,256u*1024u,512u*1024u));}
    {SBV2Header corrupted=h; corrupted.relocation_count=0xffffffffu;
     REQUIRE(!SBV2_ValidateHeader(&corrupted,size,256u*1024u,512u*1024u));}
    {SBV2Header corrupted=h; corrupted.entry_offset=2u;
     REQUIRE(!SBV2_ValidateHeader(&corrupted,size,256u*1024u,512u*1024u));}
    {SBV2Header corrupted=h; corrupted.relocation_offset=0u;
     REQUIRE(!SBV2_ValidateHeader(&corrupted,size,256u*1024u,512u*1024u));}
    {SBV2Header corrupted=h; corrupted.file_size=size+4;
     REQUIRE(!SBV2_ValidateHeader(&corrupted,size,256u*1024u,512u*1024u));}
    raw[64]^=1u;
    REQUIRE(SBV2_CRC32(raw+64,h.image_size)!=h.image_crc32);
    free(raw);
    puts("PASS: shared C format validation, CRC, Thumb relocations at two SDRAM addresses, corrupted headers rejected");
    return 0;
}
