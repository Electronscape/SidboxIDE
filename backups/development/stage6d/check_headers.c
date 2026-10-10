#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "applet_v2_format.h"
static int load(const char *name, SBV2Header *h, uint8_t **img) {
    FILE *f=fopen(name,"rb");if(!f)return 0;
    fseek(f,0,SEEK_END);long n=ftell(f);rewind(f);
    if(n<64 || fread(h,1,64,f)!=64){fclose(f);return 0;}
    if(!SBV2_ValidateHeader(h,(uint32_t)n,256*1024,512*1024)){fclose(f);return 0;}
    *img=malloc(h->image_size);if(!*img){fclose(f);return 0;}
    if(fread(*img,1,h->image_size,f)!=h->image_size){free(*img);fclose(f);return 0;}
    fclose(f);return 1;
}
int main(int argc,char **argv){
    if(argc!=3)return 2;
    for(int k=1;k<3;++k){SBV2Header h;uint8_t *img=NULL;
        if(!load(argv[k],&h,&img)){fprintf(stderr,"Invalid image: %s\n",argv[k]);return 1;}
        if(h.flags!=SBV2_FLAG_PRIVATE_PSP || h.reserved!=8192 || h.heap_size!=4096 ||
           h.memory_size-h.heap_size-h.reserved<h.image_size ||
           SBV2_CRC32(img,h.image_size)!=h.image_crc32) return 1;
        // Simulate all relocation records at two destinations.
        FILE *f=fopen(argv[k],"rb");
        for(int b=0;b<2;b++){
            uint32_t base=b?0xd0580000u:0xd0500000u;
            fseek(f,h.relocation_offset,SEEK_SET);
            uint32_t prev=0;
            for(uint32_t i=0;i<h.relocation_count;i++){
                uint32_t off; if(fread(&off,4,1,f)!=1 || off+4>h.image_size || (i&&off<=prev)) return 1;
                uint32_t value;memcpy(&value,img+off,4);
                if(!SBV2_RelocateWord(&value,off,&h,base)) return 1;
                if((value&~1u)<base || (value&~1u)>=base+h.memory_size) return 1;
                prev=off;
            }
        }
        fclose(f);
        SBV2Header bad=h;bad.reserved=h.memory_size;
        if(SBV2_ValidateHeader(&bad,h.file_size,256*1024,512*1024))return 1;
        bad=h;bad.flags=8u;
        if(SBV2_ValidateHeader(&bad,h.file_size,256*1024,512*1024))return 1;
        // Original V2 remains compatible.
        bad=h;bad.flags=0;bad.reserved=0;
        if(!SBV2_ValidateHeader(&bad,h.file_size,256*1024,512*1024))return 1;
        free(img);
        printf("PASS: %s metadata/CRC and two simulated relocation bases\n",argv[k]);
    }
    return 0;
}
